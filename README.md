# Vigia Cocó

Projeto da disciplina F054 — Fundamentos de IoT (Unifor). O protótipo simula um ponto de monitoramento no Parque Estadual do Cocó. O ESP32 lê a temperatura com um DHT22, gera valores simulados de gás e envia a telemetria por MQTT. O firmware aciona um LED e um buzzer quando a temperatura passa de 40 °C ou o valor simulado de gás passa de 3000. O painel e o histórico em CSV fazem parte da integração prevista com o Node-RED.

## Protótipo e teste MQTT

- [Abrir a simulação corrigida no Wokwi](https://wokwi.com/projects/480508470512133121)
- [Abrir o MQTTX Web](https://mqttx.app/web-client)
- [Consultar o PDF com as evidências dos testes MQTT](docs/comunicacao-mqtt-prototipo.pdf)
- [Ver firmware, circuito e bibliotecas](wokwi/)

Com a simulação executando, use um cliente MQTT que aceite TCP para conectar a `broker.hivemq.com:1883` e assine `parquecoco/ponto1/#`. No firmware desta versão, `parquecoco/ponto1/temperatura` recebe um JSON com os campos `ponto`, `temperatura` e `gas`. O tópico `parquecoco/ponto1/alerta` recebe uma mensagem de texto.

Para testar apenas o envio e recebimento de JSON pelo navegador, abra duas abas do MQTTX Web, conecte ambas a `wss://broker.emqx.io:8084/mqtt` com IDs de cliente diferentes e escolha um tópico de teste exclusivo. Assine o tópico em uma aba e publique o exemplo abaixo na outra. Esse teste usa um broker separado da simulação.

```json
{"ponto": "1", "temperatura": 38.5, "gas": 2900}
```

[Documentação do MQTTX Web](https://mqttx.app/ja/docs/web/get-started) · [Configuração do broker de teste EMQX](https://www.emqx.com/en/mqtt/public-mqtt5-broker)

## Entregas da equipe

| Integrante | Parte | Onde colocar |
|---|---|---|
| 1 | Contexto, arquitetura e limitações | `docs/arquitetura.md` |
| 2 | Broker, tópico MQTT, campos JSON e evidência de teste | `docs/mqtt.md` |
| 3 | Firmware, circuito e link do Wokwi | `wokwi/` |
| 4 | Fluxo exportado do Node-RED e instruções do painel | `node-red/` |
| 5 | CSV com pelo menos 20 leituras simuladas e evidências dos testes | `dados/` e `docs/testes.md` |
| 6 | Capturas e links do Wokwi e do vídeo | `docs/` |

Criem cada pasta ao enviar o primeiro arquivo. Antes de montar o firmware e o painel, combinem o tópico e o formato JSON em `docs/mqtt.md`. Usem o mesmo tópico para acompanhar as leituras ao vivo e compartilhem o CSV para que todos possam consultar o histórico.

## Como contribuir

1. Aceite o convite do proprietário para colaborar no repositório.
2. Crie uma branch a partir de `main` com o nome da sua parte, como `firmware-wokwi` ou `painel-node-red`.
3. Adicione seus arquivos e abra um pull request para `main`. Descreva o que entregou e como conferir.
4. Peça a outro integrante que revise antes de juntar a alteração à versão principal.

Como este repositório é público, use dados simulados e mantenha senhas, tokens, matrículas e o relatório com dados pessoais fora dele. Cada integrante envia a versão final do relatório pelo AVA.
