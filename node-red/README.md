# Vigia Cocó · Parte 4: painel e histórico (Node-RED)

Painel que recebe por MQTT as leituras do ESP32 simulado no Wokwi, mostra o estado do ponto e grava o histórico em CSV.

O que tem no painel:

- **Indicador do ponto**: identificador do ponto e estado (normal, alerta, prioridade alta ou sem sinal).
- **Medidores** de temperatura e de gás, com a faixa vermelha a partir do limite.
- **Gráficos temporais** de temperatura e de gás, com a linha do limite.
- **Aviso automático** na tela quando o estado muda, dizendo qual ponto verificar.
- **Histórico em CSV** com as colunas `ponto, ts, temp_c, gas_adc, estado`, um único cabeçalho, contador de leituras e tabela com as 10 mais recentes.

## Como rodar no seu computador

1. Instale o **Node.js 22.9 ou mais recente** (versão LTS em https://nodejs.org). Para conferir: `node -v`. Testado com as versões 22, 24 e 26.
2. Abra o terminal **dentro desta pasta** (no Windows: clique na barra de endereço do Explorador, digite `cmd` e aperte Enter).
3. Rode, só na primeira vez (leva alguns minutos):

   ```
   npm install
   ```

4. Rode sempre que quiser abrir o painel:

   ```
   npm start
   ```

5. Abra no navegador:
   - Painel: http://127.0.0.1:1880/dashboard/vigia-coco
   - Editor do fluxo: http://localhost:1880

Para parar, aperte `Ctrl+C` no terminal.

## Como testar sem o Wokwi

1. Abra o editor (http://localhost:1880) e vá na aba **Simulador (teste sem o Wokwi)**.
2. Clique no quadradinho à esquerda de **Roteiro: os 5 testes do guia (22 leituras)**.
3. Olhe o painel. Em 22 segundos ele passa por: normal, pico isolado (continua normal), alerta, prioridade alta, alerta e volta ao normal.

O simulador publica no mesmo broker e nos mesmos tópicos do ESP32, então o teste passa pelo caminho completo (MQTT, painel e CSV). Não use o simulador com o Wokwi ligado: as leituras se misturam.

## Como usar com o Wokwi

1. Deixe o painel rodando (`npm start`).
2. Abra o projeto no Wokwi e inicie a simulação.
3. O painel já usa o mesmo broker e os mesmos tópicos do firmware:

   | Item | Valor |
   |---|---|
   | Broker | `broker.hivemq.com`, porta `1883`, sem usuário e sem senha |
   | Telemetria | `parquecoco/ponto1/temperatura` |
   | Aviso do ESP32 | `parquecoco/ponto1/alerta` |

Antes de gravar as leituras que vão para o relatório, apague ou renomeie o CSV de teste. Um arquivo novo é criado sozinho na próxima leitura.

## Onde fica o CSV

`<sua pasta de usuário>/vigia-coco/leituras_vigia_coco.csv`

No Windows: `C:\Users\SEU_USUARIO\vigia-coco\leituras_vigia_coco.csv`. O painel mostra o caminho completo.

- Não deixe o arquivo aberto no Excel enquanto o painel grava (o painel avisa na tela se não conseguir gravar). Copie o arquivo e abra a cópia.
- O separador é vírgula e o decimal é ponto. No Excel em português, use **Dados > De Texto/CSV** para abrir com as colunas certas.
- `ts` é o horário em UTC (3 horas à frente de Fortaleza). A tabela do painel mostra o horário local.

## Regra de alerta

Fica no nó **Regra de alerta** e segue a página 4 do guia da equipe:

- 3 leituras seguidas com gás acima de `3000` ativam o estado `alerta`.
- Em alerta, temperatura acima de `40 °C` eleva para `prioridade_alta`.
- 3 leituras seguidas com gás no limite ou abaixo voltam para `normal`.
- Um pico isolado não muda o estado.

Se ficar 20 segundos sem leitura, o indicador mostra **SEM SINAL**.

Se o firmware passar a enviar o campo `estado`, o painel usa o estado do firmware e não recalcula.

## Formatos de JSON aceitos

O painel aceita os dois formatos e grava sempre com os nomes do guia.

| | Firmware atual (Wokwi) | Contrato do guia |
|---|---|---|
| Exemplo | `{"ponto":"1","temperatura":24.5,"gas":573}` | `{"ponto":"ponto01","ts":"2026-11-20T21:00:00Z","temp_c":38.5,"gas_adc":2900,"estado":"alerta"}` |
| `ponto` | `"1"` vira `ponto1` | usado como veio |
| `ts` | não vem: vale a hora em que a mensagem chegou | usado como veio |
| `estado` | não vem: o painel calcula pela regra | usado como veio |

Mensagens que não são JSON ou com valores impossíveis (temperatura fora de -40 a 125 °C, gás fora de 0 a 4095) são ignoradas e não vão para o CSV.

## Se a equipe mudar alguma coisa

| O que mudou | Onde alterar |
|---|---|
| Broker | nó de configuração **HiveMQ público** (abra qualquer nó MQTT e clique no lápis ao lado do servidor) |
| Tópicos | nós **Telemetria do ESP32** e **Aviso do ESP32 (LED e buzzer)**; na aba Simulador, **Simular o firmware** e **Publicar no tópico de telemetria** |
| Limites ou quantidade de leituras seguidas | nó **Regra de alerta**; depois ajuste a faixa vermelha dos dois medidores e o **Texto da regra (fixo)** |

Depois de alterar, clique em **Deploy**. O arquivo `flows.json` desta pasta é atualizado sozinho: é ele o fluxo exportado.

## Importar só o fluxo em outro Node-RED

1. Em **Manage palette**, instale `@flowfuse/node-red-dashboard`.
2. Menu **Import**, selecione o `flows.json` e clique em **Deploy**.

## Problemas comuns

| Sintoma | Causa provável e solução |
|---|---|
| `npm` não roda no PowerShell ("execução de scripts foi desabilitada") | Use o Prompt de Comando (`cmd`) em vez do PowerShell |
| `npm install` termina avisando de vulnerabilidades | São de dependências internas do Node-RED. Pode seguir. Não rode `npm audit fix --force`: ele troca versões e pode quebrar o painel |
| `npm start` reclama da versão do Node.js | Instale o Node.js LTS atual, feche e abra o terminal e rode `npm install` de novo |
| Painel mostra **Broker MQTT: conectando...** | Sem internet ou a rede bloqueia a porta 1883 (comum em rede de faculdade ou empresa). Teste em outra rede, por exemplo no roteador do celular |
| Leituras chegam e param | Duas simulações do Wokwi abertas ao mesmo tempo: as duas usam o mesmo identificador de cliente e uma derruba a outra |
| Aviso "Não foi possível gravar ou ler o CSV" | O arquivo está aberto em outro programa. Feche e aguarde a próxima leitura |
| Porta 1880 ocupada | No `cmd`: `set PORT=1881` e depois `npm start`. Use a porta 1881 nos endereços |

## Arquivos desta pasta

| Arquivo | Para que serve |
|---|---|
| `flows.json` | Fluxo exportado do Node-RED (painel, histórico e simulador) |
| `package.json` e `package-lock.json` | Versões usadas: Node-RED 5.0.9 e FlowFuse Dashboard 1.36.1 |
| `settings.js` | Configuração do Node-RED para este projeto (só este computador acessa o editor) |
| `scripts/verificar.js` | Confere a versão do Node.js antes de iniciar |
