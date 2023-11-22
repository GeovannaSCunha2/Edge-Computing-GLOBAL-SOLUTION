# HealthPartner - Projeto de avaliação de exames e armazenamento de sinais vitais
<div align="center">
  <img src="https://github.com/fernandakaory/gs-edge2/assets/126582859/f5df60d0-94ee-4a6e-b8cb-9a3c695df211" width="300"  alt="logotipo">
</div>

## Integrantes
- Geovanna Silva Cunha – RM 551104
- Mirella de Rossi Imenez – RM 551143

## Link da simulação no Wokwi
https://wokwi.com/projects/382035673837105153


## Qual o problema em questão?
<p>Após a pandemia causada pela proliferação do coronavírus SARS-COV-19, os cuidados com a saúde aumentaram consideravelmente, visto que se trata de uma doença transmissível, portanto, a população passou a priorizar os cuidados com higiene e contato físico, sendo uma conduta importantíssima para contribuição do fim da pandemia e retorno as atividades cotidianas. Mas e referente a doenças não transmissíveis ou crônicas? Quais os cuidados da população?</p>

<p>Em anos antecedentes a 2019, verificou-se que certa de 54% dos óbitos registrados no Brasil, são originados de doenças não transmissíveis ou crônicas e 11,2% destes óbitos foram causados devido a agravos das condições destas pessoas, que são fortemente influenciados pela qualidade de vida dos indivíduos, como hábitos de tabagismo, consumo de álcool, alimentação desregulada, sedentarismos e fatores naturais.</p>

<p>Em alguns casos, determinadas pessoas possuem maior probabilidade de diagnóstico de doenças cardiovasculares, câncer, diabetes, hipertensão ou doenças respiratórias devido a questões genéticas, porém em determinados casos, o paciente não procura acompanhar sua saúde ou buscar por indícios de desenvolvimento de doenças crônicas, não transmissíveis ou transmissíveis, sendo por falta de recursos ou conscientização sobre a importância de cuidado a saúde e prevenção de doenças.</p>

<p>Portando, são realizados frequentemente projetos de Promoção a saúde, como eventos gratuitos promovidos por redes particulares ou convênios, para monitoramento de sinais vitais e orientações clínicas, assim como conscientizar e estimular visitas constantes a médicos e realização de exames de rotina/anuais. Para cooperar com estas ações, é necessário a melhoria da qualidade dos atendimentos hospitalares, seja público ou particular, assim como facilitar o acesso a métodos de diagnósticos e atendimentos. </p>


## Solução
<p>Mediante a necessidade de estimular o acompanhamento médico e identificação de sintomas para prevenção de doenças, desenvolveu-se a plataforma HealthPartner.</p>

<p>Esta plataforma utiliza algoritmos para analisar exames médicos, desde simples análises de sangue até imagens de ressonância magnética. A inteligência artificial é empregada para identificar padrões, correlacionar dados e fornecer interpretações precisas. </p>

<p>Essa capacidade de análise automatizada agiliza o processo diagnóstico, permitindo uma resposta mais rápida e eficaz por parte dos profissionais de saúde. O usuário poderá salvar a leitura feita do exame, de forma que tenha acesso posteriormente e possa acompanhar a evolução e comparar quando realizado outros procedimentos, assim como o médico poderá acompanhar estes exames e diagnósticos diretamente pela plataforma, sem a necessidade de encontros presenciais.</p>

<p>Com isso, a plataforma orienta o usuário referente a necessidade de retorno em prazo estipulado pelo médico ou retorno imediato para avaliação e estudo do caso.</p>

<p>O armazenamento de sinais vitais é uma funcionalidade crucial desta plataforma. Ela oferece uma solução segura e centralizada para o registro de dados como pressão arterial, frequência cardíaca, níveis de glicose e outros indicadores vitais, assim como registros de realização de exercícios físicos e tempo de duração. Essa abordagem não apenas simplifica o acesso aos históricos médicos, mas também possibilita a criação de gráficos e relatórios personalizados para melhor acompanhamento da saúde do paciente, automatizando os registros e auxiliando na análise de exames.</p>

<p>Por exemplo, o armazenamento frequente da pressão arterial, junto a análise dos procedimentos realizado, facilita o diagnóstico de uma possível Hipertensão, visto que com a retirada do resultado dos exames já haverá as estatísticas das alterações de pressão.</p>


## Solução e IOT
<p>Nossa proposta é desenvolver um aplicativo que integra a Internet das Coisas (IoT) e sensores de frequência cardíaca para otimizar a experiência do usuário no gerenciamento de sua saúde. O aplicativo oferece uma plataforma segura e centralizada para o registro e armazenamento de sinais vitais, frequência cardíaca e outros indicadores vitais Além disso, incorporamos um código que registra o horário UTC de
cada leitura dos sensores, proporcionando um registro temporal preciso das informações coletadas.</p>

<p>Através do uso de sensores de frequência cardíaca e tecnologia IoT, os usuários podem monitorar continuamente sua saúde e registrar automaticamente esses dados no aplicativo. Isso não apenas simplifica o acesso aos históricos médicos, mas também possibilita a criação de gráficos e relatórios personalizados para um melhor acompanhamento da saúde do paciente.</p>

<p>Por exemplo, o monitoramento contínuo da frequência cardíaca pode ajudar a detectar anomalias cardíacas precocemente. Com a retirada do resultado dos exames, já haverá as estatísticas das alterações da frequência cardíaca, permitindo uma intervenção médica mais rápida e eficaz.</p>


## Implementação do Sistema IoT
<div align="center">
  <img src="https://github.com/fernandakaory/gs-edge2/assets/126582859/ea62233a-8d31-4f4e-8f86-4b610dd76d58" width="600" >
</div>
<h3>Hardware </h3>
- <b>Placa ESP 32:</b> Esta placa, equipada com dois núcleos de 32 bits, permite a conexão Wi-Fi ou Bluetooth, possibilitando a implementação da Internet das Coisas (IoT) em nosso protótipo.
- <b>Gerador de pulso:</b> Este dispositivo é usado para simular a captação de batimentos cardíacos.

<h3>Back-end</h3>
No back-end do projeto, empregamos o Fiware, uma plataforma de código aberto que disponibiliza uma infraestrutura robusta e padronizada para o desenvolvimento de aplicações e serviços inteligentes baseados em IoT. O Fiware facilita a coleta, armazenamento e transporte de dados capturados pelo sensor de batimento cardíaco. Esses dados são então integrados à nossa aplicação de front-end, onde são apresentados aos usuários de maneira clara e intuitiva, proporcionando uma experiência prática.
<div align="center">
  <img src="https://github.com/fernandakaory/sprint3-edge/assets/126582859/dcd4980b-f53f-444d-99d6-4925a6668d87" >
</div>
<h3>Front-end</h3>
Para o front-end, estamos utilizando o <a href=https://freeboard.io/> Freeboard </a>, uma plataforma que fornece todos os recursos necessários para a visualização de dados transmitidos via MQTT a partir do Fiware Orion. Além disso, o Freeboard facilita a interpretação dos dados, permitindo aos usuários compreender facilmente as informações capturadas pelo sensor. 

<div align="center">
  <img src="https://github.com/fernandakaory/gs-edge2/assets/126582859/2198455c-be5d-4d0b-8d7f-f610aeefe1d8" width="600" >
</div>


## Requisitos do projeto
- Docker e docker compose.
- Fiware.
- Postman.
- Em caso de construção física, uma ESP 32, display lcd I2C e um gerador de pulso.
- Em caso de prototipação virtual, as ferramentas podem ser encontradas e usadas no <a href="https://wokwi.com/"> Wokwi </a>.
- Ambiente de desenvolvimento como Arduino IDE ou Wokwi.
- Conectividade Wifi ou blutooth.
- Ambiente front-end, como o <a href=https://freeboard.io/> Freeboard </a>.
  
## Configuração e reprodução
1. Instalação de uma máquina virtual Linux.
2. Instalação do docker e do docker compose como especificado <a href=https://docs.docker.com/engine/install/ubuntu/> aqui </a>.
3. Instalação do <a href=https://github.com/fabiocabrini/fiware>Fiware</a>.
4. Instalação do Postman.
5. Importar as collection para o Fiware e executar os métodos HTTP de Health Check.
6. Provisionar os sensores como dispositivos virtuais (como no arquivo json acima), definindo id, protocolo de comunicação, comandos e atributos.
7. Registrar esses dispositivos  (como no arquivo json acima).
8. Montar os sensores físicos na ESP 32 de acordo com a imagem acima:
9. Montar o código desses sensores para enviar por MQTT os dados. (importar também bibliotecas PubSubClient, LiquidCrystal I2C).
10. Realizar a subscrição e métodos GET para receber os dados desejados.
11. Configurar <a href=https://freeboard.io/> Freeboard</a>.
12. Configurar os dashboards e gráficos desejados.