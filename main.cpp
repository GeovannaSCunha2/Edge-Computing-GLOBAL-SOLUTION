
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

LiquidCrystal_I2C LCD(0x27, 20, 4);

// Define para usar código de tempo UTC
#define NTP_SERVER     "a.ntp.br"
#define UTC_OFFSET     0
#define UTC_OFFSET_DST 0

#define PULSE_PER_BEAT    1           // Número de pulsos por batimento cardíaco
#define INTERRUPT_PIN     5           // Pino de interrupção
#define SAMPLING_INTERVAL 1000        // Intervalo de amostragem em milissegundos

// Define de id MQTT e tópicos para publicação e subscrição denominado TEF (Telemetria e Monitoramento de Equipamentos)
#define TOPICO_SUBSCRIBE    "/TEF/heartRate002/cmd"        // Tópico MQTT de escuta
#define TOPICO_PUBLISH      "/TEF/heartRate002/attrs"      // Tópico MQTT de envio de informações para o Broker
#define TOPICO_PUBLISH_2    "/TEF/heartRate002/attrs/bpm"   // Tópico de envio do batimento
#define TOPICO_PUBLISH_3    "/TEF/heartRate002/attrs/h"     // Tópico de envio do horário

#define ID_MQTT  "fiware_hp" // Id MQTT (para identificação de sessão)

// WIFI
const char* SSID = "Wokwi-GUEST"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "";        // Senha da rede WI-FI que deseja se conectar

// MQTT
const char* BROKER_MQTT = "46.17.108.113"; // URL do broker MQTT que deseja utilizar
int BROKER_PORT = 1883;                      // Porta do Broker MQTT

// Variáveis e objetos globais
WiFiClient espClient;               // Cria o objeto espClient
PubSubClient MQTT(espClient);        // Instancia o Cliente MQTT passando o objeto espClient
char EstadoSaida = '0';              // Variável que armazena o estado atual da saída

volatile uint16_t pulse;            // Variável que será incrementada na interrupção
uint16_t count;                     // Variável para armazenar o valor atual de pulse

float heartRate;                    // Frequência cardíaca calculada a partir de count

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;  // Mutex para garantir acesso seguro a pulse

void IRAM_ATTR HeartRateInterrupt() {
  portENTER_CRITICAL_ISR(&mux);    // Entra em uma seção crítica de interrupção
  pulse++;                          // Incrementa a variável pulse de maneira segura
  portEXIT_CRITICAL_ISR(&mux);     // Sai da seção crítica de interrupção
}

void setup() {
  // Inicializações:
  initSerial();                     // Inicializa a comunicação serial
  initWiFi();                       // Inicializa a conexão Wi-Fi
  initMQTT();                       // Inicializa o cliente MQTT
  delay(5000);
  MQTT.publish(TOPICO_PUBLISH, "s|on");  // Publica uma mensagem indicando o status no tópico
  initLCD();                        // Inicializa o display LCD
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), HeartRateInterrupt, RISING);  // Configura a interrupção no pino
}

void initSerial() {
  Serial.begin(115200);
  while (!Serial) {
    // Aguarda a inicialização da porta serial
  }
}

void initLCD() {
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Connecting to ");
  LCD.setCursor(0, 1);
  LCD.print("WiFi ");

  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    spinner();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.println("Online");
  LCD.setCursor(0, 1);
  LCD.println("Updating time...");

  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}

void initWiFi() {
  delay(10);
  Serial.println("------Conexao WI-FI------");
  Serial.print("Conectando-se na rede: ");
  Serial.println(SSID);
  Serial.println("Aguarde");
   
  reconectWiFi();
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);   // Informa qual broker e porta deve ser conectado
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado com sucesso ao broker MQTT!");
      MQTT.subscribe(TOPICO_SUBSCRIBE); 
    } else {
      Serial.println("Falha ao reconectar no broker.");
      Serial.println("Haverá nova tentativa de conexão em 2s");
      delay(5000);
    }
  }
}

void reconectWiFi() {
  // Se já está conectado à rede WI-FI, nada é feito. 
  // Caso contrário, são efetuadas tentativas de conexão
  if (WiFi.status() == WL_CONNECTED)
    return;
     
  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
 
  Serial.println();
  Serial.print("Conectado com sucesso na rede ");
  Serial.print(SSID);
  Serial.println(" IP obtido: ");
  Serial.println(WiFi.localIP());
}

void VerificaConexoesWiFIEMQTT(void) {
  if (!MQTT.connected()) 
    reconnectMQTT(); // Se não há conexão com o Broker, a conexão é refeita
   
  reconectWiFi();     // Se não há conexão com o WiFI, a conexão é refeita
}

// Configura figura de spinner no LCD
void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdb";
  LCD.setCursor(15, 1);
  LCD.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}

// Função para exibição da data e horário UTC
struct tm timeinfo;
void printLocalTime() {
  if (!getLocalTime(&timeinfo)) {
    LCD.setCursor(0, 1);
    LCD.println("Connection Err");
    return;
  }

  // Ajustar o deslocamento horário para UTC -3 (AST/BRT)
  timeinfo.tm_hour -= 3;
  if (timeinfo.tm_hour < 0) {
    timeinfo.tm_hour += 24;  // Garantir que o valor de hora seja positivo
  }

  LCD.setCursor(8, 0);
  LCD.println(&timeinfo, "%H:%M:%S");

  LCD.setCursor(0, 1);
  LCD.println(&timeinfo, "%d/%m/%Y   %Z");

  // Exibe a frequência cardíaca abaixo da data e hora
  LCD.setCursor(0, 2);
  LCD.print("Heart Rate: ");
  LCD.print(heartRate);
  LCD.println(" BPM");
}

void loop() {
  HeartRate();
  printLocalTime();
  delay(250);

  // Garante funcionamento das conexões Wi-Fi e ao broker MQTT
  VerificaConexoesWiFIEMQTT();
 
  // Keep-alive da comunicação com broker MQTT
  MQTT.loop();
  delay(100);
}

void HeartRate() {
  char heartRateBuffer[6];
  char timeBuffer[20];

  static unsigned long startTime;
  if (millis() - startTime < SAMPLING_INTERVAL) return;   // Intervalo de amostragem
  startTime = millis();

  portENTER_CRITICAL(&mux);  // Entra em uma seção crítica
  count = pulse;  // Salva o valor atual de pulse e zera pulse
  pulse = 0;
  portEXIT_CRITICAL(&mux);   // Sai da seção crítica

  // Ajuste na fórmula para mapear a faixa de 0 Hz a 220 Hz para a frequência cardíaca em BPM
  heartRate = map(count, 0, 220, 0, 220);  // Mapeia a contagem para a faixa desejada
  dtostrf(heartRate, 4, 2, heartRateBuffer);
  strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

  MQTT.publish(TOPICO_PUBLISH_2, heartRateBuffer);
  MQTT.publish(TOPICO_PUBLISH_3, timeBuffer);

  Serial.println("Heart Rate: " + String(heartRate, 2) + " BPM");
}
