# Vigia Cocó

Projeto da disciplina F054 — Fundamentos de IoT (Unifor). O protótipo simula um ponto de monitoramento no Parque Estadual do Cocó. O ESP32 lê temperatura e nível de gás no Wokwi, acende um LED quando detecta uma alteração persistente e envia leituras por MQTT. O Node-RED exibe os dados e registra o histórico em CSV.

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
