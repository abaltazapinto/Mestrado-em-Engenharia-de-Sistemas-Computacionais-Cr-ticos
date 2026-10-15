
# COMCS — 13 de outubro de 2026

**Fonte primária:** `comcs.srt`
**Fonte secundária:** `notas.md`

A aula tem uma estrutura bastante clara apesar de a transcrição automática ter vários erros de termos técnicos. O percurso foi essencialmente:

**Sliding Window / ACKs → controlo de congestão → comunicações wireless → princípios físicos da transmissão rádio → representação de informação em sinais.**

As tuas notas captaram corretamente vários dos pontos-chave: timers por frame, SACK, congestion window, Additive Increase, Slow Start, requisitos de wireless, antenas e início da modulação. notas notas

---

# 1. Reconstrução da aula

## 1.1 Sliding Window — continuação da aula anterior

A aula começa já no meio da explicação de **Sliding Window**.

A ideia apresentada é que o transmissor não envia indefinidamente. Existe uma janela que determina quantas frames/mensagens podem estar em trânsito sem ainda terem sido confirmadas.

Exemplo usado pelo professor:

- tamanho da janela ≈ 5;
- o transmissor pode enviar as primeiras 5 mensagens;
- não pode simplesmente continuar com a sexta;
- quando chega um **ACK**, a janela pode avançar;
- passa então a existir espaço para enviar outra frame.

O professor refere explicitamente variáveis como:

- **Sending Window Size — SWS**
- números de sequência;
- identificação da última frame enviada;
- identificação da última frame reconhecida.

### Ideia visual

```text
Sender

[1][2][3][4][5]  6  7  8 ...
 └──── window ────┘

          ↓ ACK

   [2][3][4][5][6]  7  8 ...
      └── window ──┘
```

A janela **desliza** quando chegam acknowledgements.

Um ACK pode ainda permitir que a janela avance mais de uma posição, dependendo do mecanismo de acknowledgement utilizado.

---

## 1.2 Timers e retransmissão

O professor relaciona depois Sliding Window com **timers**.

Cada mensagem/frame enviada pode ter associado um timer.

Mentalmente:

```text
frame 1 → timer 1
frame 2 → timer 2
frame 3 → timer 3
...
```

Se a confirmação não aparecer dentro do intervalo esperado, o protocolo pode concluir que ocorreu uma perda e desencadear retransmissão.

Também houve uma pequena discussão sobre timers implementados pelo sistema operativo/kernel e sobre precisão temporal.

⚠️ Os detalhes concretos sobre resoluções dos timers ficaram muito degradados no SRT.

**Not clearly covered in the lecture** de forma suficientemente fiável para extrair valores exatos.

A tua nota:

> "the sender associates a timer with each frame it transmits"

representa corretamente a ideia apresentada. notas

---

# 1.3 Latência, perda e comunicação de voz

O professor introduziu um trade-off importante:

> Nem sempre retransmitir é melhor.

Em aplicações como **voz**, esperar pela retransmissão de um pacote perdido pode introduzir atraso prejudicial à comunicação.

A aula refere que, a partir de determinado atraso — foi mencionado aproximadamente **200 ms** — começamos a perceber que a conversação não está natural.

Daí o exemplo de protocolos sem garantia de retransmissão para voz:

```text
pacote recebido → reproduzir
pacote perdido  → perda momentânea

em vez de:

pacote perdido
      ↓
esperar retransmissão
      ↓
aumentar latência
```

A mensagem importante da aula não é decorar o número, mas perceber:

> **Reliability e latency podem estar em conflito.**

---

# 1.4 Mecanismos de acknowledgement

Foram discutidas três formas/mecanismos de acknowledgement.

## Negative Acknowledgement — NACK

Serve para indicar explicitamente que determinada informação **não foi recebida**.

Exemplo intuitivo:

```text
recebido: 1 2 _ 4

Receiver → "falta 3"
Sender   → retransmite 3
```

Isto pode evitar esperar simplesmente que o timer expire.

---

## Additional / Duplicate ACK

O professor descreveu o envio de acknowledgements adicionais/duplicados quando o recetor recebe informação posterior mas continua a faltar uma frame anterior.

A repetição de ACKs pode fornecer ao transmissor evidência de que algo se perdeu.

Isto liga posteriormente ao conceito de **Fast Retransmit**.

---

## Selective Acknowledgement — SACK

Este recebeu atenção especial.

O recetor consegue informar o transmissor **quais frames/segmentos foram efetivamente recebidos**.

Exemplo:

```text
Enviados:

1  2  3  4  5

Recebidos:

_  2  3  4  _

SACK → "2–4 recebidos"
```

O transmissor pode então perceber que determinados elementos estão em falta sem retransmitir indiscriminadamente tudo.

Esta interpretação coincide com a tua nota sobre SACK. notas

### Mental model

**ACK normal:**

> "Cheguei até aqui."

**SACK:**

> "Recebi especificamente estes blocos."

---

# 1.5 De Sliding Window para Congestion Control

Aqui ocorre uma mudança importante.

Sliding Window não resolve sozinho o problema de **congestão da rede**.

O professor deu contexto histórico: equipamentos de rede têm buffers limitados. Se chegam pacotes mais rapidamente do que podem ser processados/transmitidos:

```text
pacotes
 ↓↓↓↓↓↓↓
┌──────────┐
│  buffer  │ ← enche
└──────────┘
     ↓
 capacidade de saída limitada
```

Quando o buffer fica cheio:

**pacotes começam a ser descartados.**

Portanto, o transmissor precisa de adaptar a quantidade de dados que injeta na rede.

---

# 1.6 Congestion Window — CWND

É introduzida uma janela dinâmica associada ao congestion control.

A lógica apresentada é:

```text
rede parece saudável
        ↓
aumentar janela
        ↓
enviar mais
        ↓
testar capacidade da rede
```

Se aparecer evidência de congestionamento:

```text
packet loss
    ↓
reduzir janela
    ↓
enviar menos dados
```

Assim:

> **CWND adapta a quantidade de dados em trânsito às condições da rede.**

Nas tuas notas isto aparece como **Congestion window**. notas

O professor indicou ainda que o limite efetivo envolve a congestion window e a **receiver window**.

A ideia a reter nesta fase é:

\[
\text{effective window} \approx \min(CWND,\ ReceiverWindow)
\]

---

# 1.7 Additive Increase

Primeiro mecanismo de adaptação:

## Additive Increase

Se a comunicação está a funcionar corretamente, aumenta-se gradualmente a janela.

Mental model:

```text
CWND

4
5
6
7
8
9
...
```

Isto corresponde à ideia anotada de adicionar capacidade progressivamente à sending window. notas

O objetivo é **sondar/testar a capacidade disponível da rede** sem aumentar agressivamente para sempre.

---

# 1.8 Multiplicative Decrease

Quando aparece congestão/perda, a janela é reduzida significativamente.

Mental model:

```text
CWND = 20

packet loss
    ↓

CWND ≈ 10
```

O valor exato/regra matemática **não ficou claramente estabelecido no SRT**, portanto não devemos inventar uma fórmula específica para esta aula.

O conceito é:

> aumento progressivo quando tudo corre bem; redução forte quando aparece congestionamento.

Isto forma a conhecida lógica:

### AIMD

**Additive Increase + Multiplicative Decrease**

---

# 1.9 Slow Start

Depois aparece um nome inicialmente contraintuitivo.

## Slow Start

O próprio professor diz aproximadamente:

> "Slow Start na realidade é um fast start."

Porquê?

Porque inicialmente o crescimento da congestion window é **rápido/exponencial**, em contraste com o crescimento linear do Additive Increase.

Mentalmente:

```text
1 → 2 → 4 → 8 → 16 ...
```

e não:

```text
1 → 2 → 3 → 4 → 5 ...
```

Portanto:

```text
Slow Start
    ↓
crescimento rápido/exponencial

Congestion Avoidance
    ↓
crescimento mais lento/linear
```

As tuas notas registaram precisamente esta ideia. notas

---

# 1.10 Congestion Avoidance e Recovery

O professor mostrou um gráfico de evolução da janela.

A interpretação da explicação é aproximadamente:

```text
CWND
 ^
 |                    / / / /
 |                  /
 |                /
 |             __/
 |          __/
 |       __/
 |    __/
 | __/
 +--------------------------> tempo
   Slow Start     Congestion
                  Avoidance
```

No **Slow Start**, crescimento rápido.

Depois passa-se para **Congestion Avoidance**, onde a janela continua a crescer, mas mais linearmente/devagar.

Quando é detetada perda:

```text
CWND
 ^
 |          /
 |        /
 |      /
 |    / |
 |  /   ↓ perda
 | /    └── redução
 +--------------------> tempo
```

Foi ainda mencionada uma fase de **recovery**.

Os detalhes completos do algoritmo de recovery:

**Not clearly covered in the lecture.**

---

# 1.11 Transição: Wireless Communications

Aos ~21 minutos a aula muda de assunto:

# Comunicações em redes sem fios

O professor começa pelos requisitos de protocolos wireless.

A escolha do protocolo depende muito do **produto final**.

Um sensor de temperatura que transmite poucos bytes não tem as mesmas necessidades de um sistema que transmite imagens.

Foram destacados:

- simplicidade;
- segurança;
- baixo consumo energético;
- baixo poder computacional necessário;
- baixo custo.

As tuas notas captam estes requisitos. notas

---

# 1.12 Segurança em wireless

Foi utilizado Wi-Fi como exemplo histórico.

A ideia transmitida:

> segurança deve ser considerada desde o desenho do protocolo/sistema.

O professor menciona protocolos iniciais de segurança Wi-Fi que posteriormente se verificou serem vulneráveis, obrigando à evolução/substituição.

⚠️ O nome concreto do protocolo está mal reconhecido pelo SRT.

**Not clearly covered in the lecture** com qualidade suficiente para atribuir o nome a partir da transcrição.

---

# 1.13 Energia e recursos computacionais

Wireless é particularmente importante em dispositivos com:

- bateria;
- CPU limitada;
- memória limitada;
- requisitos de baixo custo.

O professor discute ainda que receber informação também consome energia e que não se pode assumir simplesmente que **transmitir é sempre a operação dominante**.

A tua nota regista:

> "em redes normais gasta-se mais na receção que no envio"

notas

Convém não generalizar isto universalmente. O ponto da aula é que **TX/RX e processamento do protocolo têm custos energéticos relevantes e dependentes do sistema**.

---

# 1.14 Protocolos que serão estudados

O professor identifica como tecnologias relevantes:

- **IEEE 802.11 / Wi-Fi**
- **Bluetooth**
- **Bluetooth Low Energy**
- **Zigbee**

Isto está também refletido nas tuas notas. notas

São mencionadas outras tecnologias short-range e long-range, mas o professor diz explicitamente que não haverá tempo para estudar tudo.

---

# 1.15 Radio Transmission Principles

A segunda grande parte de wireless começa com fundamentos físicos.

Pergunta central:

> **What is a signal?**

notas

Para comunicar sem fios, a informação tem de ser transportada através de **ondas eletromagnéticas**.

O professor usa analogias com ondas na água para construir intuição sobre propagação.

O ponto principal:

> o meio físico influencia o que conseguimos transmitir.

---

# 1.16 Porque não transmitir simplesmente uma onda quadrada?

Este é um dos conceitos importantes desta aula.

Um sinal digital ideal pode ser imaginado como:

```text
    ┌──────┐
    │      │
────┘      └──────
```

Mas mudanças instantâneas/abruptas são problemáticas num meio físico real.

O professor usa a analogia de tentar propagar formas abruptas numa onda na água.

A ideia introdutória é:

```text
bits digitais
     ↓
não são simplesmente "atirados para o ar"
     ↓
precisamos representar a informação
num sinal fisicamente transmissível
```

A explicação espectral/matemática completa **não foi desenvolvida nesta aula**.

---

# 1.17 Cadeia de transmissão

Nas notas aparece uma boa síntese da cadeia apresentada:

```text
informação
    ↓
encoder
    ↓
modulador
    ↓
amplificador
    ↓
antena TX
    ↓
ondas eletromagnéticas
    ↓
antena RX
    ↓
amplificador
    ↓
demodulador
    ↓
decoder
    ↓
informação
```

notas

### Encoder

Transforma a informação numa representação/código apropriado.

### Modulator

Coloca essa informação sobre um sinal adequado à transmissão.

### Antenna

Converte entre o sinal elétrico e a propagação eletromagnética — e vice-versa na receção.

---

# 1.18 Espectro eletromagnético

O professor refere vários sistemas que partilham o espectro eletromagnético:

- AM;
- FM;
- televisão;
- satélite;
- comunicações wireless.

notas

Daí a necessidade de organizar/dividir o espectro em diferentes bandas.

Foi ainda mencionado que a audição/voz humana ocupa frequências muito inferiores às frequências carrier usadas nas comunicações rádio.

A nota menciona cerca de **20 kHz**, mas isto aparece de forma demasiado ambígua entre "voz" e limite auditivo. notas

**Not clearly covered in the lecture** para afirmar exatamente a que intervalo o professor se referia.

---

# 1.19 Carrier e modulação

No final da aula começa a aparecer **modulação**.

A ideia introduzida é uma onda sinusoidal **carrier** sobre a qual é colocada/codificada a informação.

Mental model:

```text
informação
   ↓
modulador ← carrier
   ↓
sinal modulado
   ↓
antena
```

Foi mencionado **AM**, e as notas terminam precisamente quando começa **FSK**. notas

Logo:

### AM

A informação é representada através de alterações associadas à amplitude da carrier.

### FSK

É apenas iniciado no fim do material.

**Not clearly covered in the lecture** além da introdução; não faz sentido aprofundá-lo ainda.

---

# 2. Partes difíceis explicadas simplesmente

## Sliding Window

Imagina uma passadeira com **5 caixas permitidas simultaneamente**.

```text
TX → 📦 📦 📦 📦 📦 → RX
```

Enquanto nenhuma caixa for confirmada, não colocas uma sexta.

RX confirma uma:

```text
              ← ACK
```

Libertaste uma posição:

```text
TX → 📦 📦 📦 📦 📦 → RX
      nova ↑
```

Isto permite ter várias mensagens em trânsito sem esperar ACK depois de cada mensagem.

---

## Congestion Window

Sliding Window pergunta:

> **Quantos dados posso ter em trânsito nesta ligação?**

Congestion Window acrescenta:

> **Quantos dados é seguro colocar agora na rede sem a congestionar?**

É como entrar numa autoestrada:

```text
pouco trânsito → aumentar velocidade/fluxo
muito trânsito → reduzir fluxo
```

---

## AIMD

É uma estratégia de exploração:

```text
tudo bem → + pouco
tudo bem → + pouco
tudo bem → + pouco

PERDA!

→ reduzir bastante
```

Assim o transmissor procura continuamente uma capacidade sustentável da rede.

---

## Slow Start

O nome engana.

Não significa "crescer devagar".

Significa começar com uma janela pequena e **crescer muito rapidamente**:

```text
1
2
4
8
16
...
```

Depois de determinada fase, passa-se para crescimento mais conservador.

---

## Modulação

Os bits:

```text
10110010
```

não "voam".

Precisamos de um sinal físico.

Então usamos uma **carrier**:

```text
~~~~~~~ sinusóide ~~~~~~~
```

e modificamos alguma característica dela para representar informação.

É isto que abre o caminho para AM, FM, FSK e outras modulações.

---

# 3. Problemas/correções nas notas

Há cinco pontos que corrigiria já.

| Nota                                          | Correção                                                                                                |
| --------------------------------------------- | --------------------------------------------------------------------------------------------------------- |
| `Addictive increase`                        | **Additive Increase**                                                                               |
| `add one packet every received ACK to SWND` | A ideia é crescimento progressivo da congestion window; esta formulação literal não deve ser decorada |
| `Slow start = fast start`                   | Boa intuição do professor, mas o nome correto continua a ser**Slow Start**                        |
| `gasta-se mais na receção que no envio`   | Não generalizar como regra universal; depende do hardware/protocolo                                      |
| `voz max 20 kHz`                            | Ambíguo no SRT;**not clearly covered in the lecture**                                              |

A estrutura das notas, porém, identificou corretamente os principais tópicos: SACK → congestion window → Additive Increase → Multiplicative Decrease → Slow Start → wireless → requisitos → radio principles → antenas → espectro → modulação. notas

---

# 4. 📓 Resumo para escrever no caderno — ~30 min

## Sliding Window

- Permite várias frames em trânsito.
- `SWS` = Sending Window Size.
- Frames têm **sequence numbers**.
- ACK faz a janela avançar.
- Cada frame pode ter timer associado.
- Timeout pode provocar retransmissão.

### ACK mechanisms

**NACK**

- informa explicitamente uma perda.

**Duplicate/Additional ACK**

- ACK repetido pode indicar frame perdida.

**SACK — Selective Acknowledgement**

- informa especificamente quais segmentos foram recebidos.
- evita retransmitir informação já recebida.

---

## Latency vs Reliability

- Retransmissão aumenta reliability.
- Mas também pode aumentar latency.
- Voz é sensível a atraso.
- Em alguns sistemas, perder um pacote pode ser preferível a esperar retransmissão.

---

## Congestion Control

Problema:

```text
input > capacidade da rede
→ buffers enchem
→ packet loss
```

### Congestion Window — CWND

- janela dinâmica;
- controla quantidade de dados em trânsito;
- aumenta quando rede suporta tráfego;
- diminui perante congestão/perda.

\[
Window_{effective} \approx \min(CWND,RWND)
\]

---

## AIMD

### Additive Increase

- crescimento gradual/linear;
- testa capacidade disponível da rede.

### Multiplicative Decrease

- perante congestão:
- reduzir significativamente CWND.

```text
healthy → increase slowly
loss    → decrease strongly
```

---

## Slow Start

- começa com CWND pequena;
- crescimento rápido/exponencial;

```text
1 → 2 → 4 → 8 → 16
```

Depois:

### Congestion Avoidance

- crescimento mais lento/linear.

Perda:

```text
CWND ↓
→ recovery
```

---

# Wireless Communications

Requisitos dependem da aplicação.

Principais:

- simplicity;
- security;
- low power consumption;
- low computational requirements;
- low cost.

Tecnologias referidas:

- IEEE 802.11 / Wi-Fi;
- Bluetooth;
- BLE;
- Zigbee.

---

# Radio Transmission Principles

Wireless usa **electromagnetic waves**.

Um sinal digital ideal não é simplesmente transmitido como uma onda quadrada perfeita.

Precisamos de:

```text
Data
 ↓
Encoder
 ↓
Modulator
 ↓
Amplifier
 ↓
TX Antenna
 ↓
EM wave
 ↓
RX Antenna
 ↓
Amplifier
 ↓
Demodulator
 ↓
Decoder
 ↓
Data
```

---

## Spectrum

Vários sistemas utilizam o espectro eletromagnético:

- AM
- FM
- TV
- satellite
- wireless networks

→ espectro é dividido/organizado em bandas.

---

## Carrier

Carrier = sinal base usado para transportar informação.

Normalmente apresentada como sinusóide:

\[
s(t)=A\sin(2\pi ft+\phi)
\]

Características:

- amplitude \(A\)
- frequency \(f\)
- phase \(\phi\)

Modulação = alterar propriedades da carrier para representar informação.

### AM

Informação associada à **amplitude**.

### FSK

Introduzido no final.

**Not clearly covered in the lecture.**

---

# 5. Core Concepts — apenas os difíceis

### 1. Sliding Window ≠ Congestion Window

Esta distinção vale a pena fixar já:

**Sliding Window** → mecanismo para controlar frames em trânsito/ACKs.

**Congestion Window** → adapta o volume enviado às condições da rede.

São conceitos relacionados, mas **não são a mesma janela**.

---

### 2. SACK

Em vez de apenas:

> "Recebi até X."

o recetor consegue dizer:

> "Recebi especificamente estes blocos."

Isso permite retransmissões mais seletivas.

---

### 3. AIMD

É uma forma de encontrar dinamicamente a capacidade da rede:

```text
aumentar cuidadosamente
        ↓
detetar congestionamento
        ↓
reduzir bastante
        ↓
voltar a explorar
```

---

### 4. Slow Start

Não memorizes "slow = lento".

Memoriza:

> **small start, fast growth.**

Começa pequeno, mas cresce exponencialmente.

---

### 5. Modulação

A informação digital não é o mesmo que a onda rádio.

```text
bits → representação → modulação → onda EM
```

A carrier é o "veículo"; a informação é aquilo que queremos transportar.

---

# 6. Essential Exam Questions — 5

### Q1 — Conceptual

**Qual a finalidade de uma Sliding Window?**

**Resposta:** Permitir várias frames em trânsito simultaneamente, mantendo controlo sobre quais foram enviadas e confirmadas.

**Raciocínio:** Os ACKs fazem a janela avançar e libertam espaço para novas transmissões.

---

### Q2 — Conceptual

**Qual a diferença fundamental entre Additive Increase e Slow Start?**

**Resposta:** Additive Increase aumenta a janela gradualmente/linearmente; Slow Start apresenta crescimento rápido/exponencial.

**Raciocínio:** Slow Start encontra rapidamente uma região útil de operação; depois o crescimento torna-se mais conservador.

---

### Q3 — Aplicada

Foram enviadas frames `1 2 3 4 5`. O recetor informa através de SACK que recebeu `2–4`.

**O que pode o transmissor inferir?**

**Resposta:** Que `2, 3 e 4` chegaram e que existem lacunas relativamente a `1` e `5`.

**Raciocínio:** SACK identifica explicitamente blocos recebidos.

---

### Q4 — Aplicada

A congestion window está a crescer e começa a ocorrer packet loss.

**Qual deve ser a reação geral do congestion control discutido?**

**Resposta:** Reduzir significativamente a congestion window.

**Raciocínio:** A perda é interpretada como sinal de que a capacidade disponível pode ter sido ultrapassada.

---

### Q5 — Multiple Choice

**Qual sequência representa melhor Slow Start?**

A. `1 → 2 → 3 → 4 → 5`
B. `1 → 2 → 4 → 8 → 16`
C. `16 → 8 → 4 → 2 → 1`
D. `1 → 1 → 1 → 1`

**Resposta: B.**

**Raciocínio:** Na explicação da aula, Slow Start corresponde a crescimento exponencial da janela.

---

# 7. Common Pitfalls

1. **Confundir Sliding Window com Congestion Window.** Uma gere o mecanismo de frames/ACKs; a outra adapta transmissão à congestão.
2. **Pensar que Slow Start significa crescimento lento.** O professor salientou exatamente o contrário: começa pequeno, mas cresce rapidamente.
3. **Pensar que retransmissão é sempre desejável.** Em tráfego sensível a latência, como voz, esperar pela retransmissão pode ser pior do que tolerar alguma perda.
4. **Pensar que bits digitais são diretamente "enviados pelo ar".** É necessária uma representação física do sinal, incluindo modulação e transmissão através da antena.
5. **Decorar já FSK/modulações avançadas.** A aula apenas começa esse assunto no final. **Not clearly covered in the lecture** para ir além da introdução.

## 📓 Guardar no caderno

A ligação conceptual mais importante desta aula é:

```text
Sliding Window
      ↓
ACK / NACK / SACK / timers
      ↓
retransmission & reliability
      ↓
Congestion Control
      ↓
CWND
      ↓
Slow Start → Congestion Avoidance
      ↓
AIMD
```

e depois começa um **novo capítulo**:

```text
Wireless
   ↓
requirements
   ↓
physical signal
   ↓
electromagnetic wave
   ↓
encoder → modulator → antenna
   ↓
carrier / spectrum / modulation
```

Essa separação entre os dois blocos torna a aula muito mais fácil de organizar mentalmente.
