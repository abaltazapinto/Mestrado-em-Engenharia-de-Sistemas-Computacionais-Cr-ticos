
Sim. E há uma conclusão importante logo à partida: **esta PL3 não foi desenhada para ser autónoma**.

O próprio guião manda reutilizar o **UDP server da PL1** e o **TCP client da PL2**. Portanto, não faz sentido tentares compreender PL3 sem recuperar pelo menos essas duas peças. Isto encaixa exatamente na estratégia de catch-up que definiste: recuperar primeiro os conceitos necessários para acompanhar a aula atual, não todas as aulas anteriores por ordem. PROJECT_CONTEXT_Mestrado_Sistem…

> **Nota sobre a fonte primária:** tenho o áudio `COMCS.mp3`, mas não tenho uma transcrição SRT textual fiável deste áudio. Portanto, não vou fingir que determinadas frases foram ditas pelo professor. A reconstrução abaixo é baseada no **guião oficial da PL3**; sempre que seria necessário confirmar algo especificamente no discurso da aula, marco como **“Not clearly covered in the lecture”**.

# 1. Reconstruct the Lecture — PL3 COMCS

## 1.1 O objetivo real desta PL

O título diz praticamente tudo:

**Arduino setup + UDP + TCP protocols**

Mas pedagogicamente há uma progressão:

```text
ESP32 / Arduino
      ↓
GPIO + Serial
      ↓
Wi-Fi
      ↓
UDP client
      ↓
ESP32 controla LED através da rede
      ↓
TCP server
      ↓
ESP32 controla LED através de comandos TCP
```

Portanto, **o Arduino/ESP32 não é o objetivo final**. É a plataforma onde vais aplicar comunicação de rede.

---

## 1.2 Arduino e ESP32

O guião começa por apresentar Arduino como plataforma de prototipagem baseada em:

- microcontrolador;
- hardware de desenvolvimento;
- Arduino IDE;
- programação essencialmente em C/C++ simplificado.

Depois passa rapidamente para o **ESP32**, que é mais interessante para COMCS porque já fornece:

- Wi-Fi;
- Bluetooth;
- GPIO;
- UART;
- SPI;
- I²C;
- CAN/TWAI;
- ADC/DAC;
- timers;
- PWM.

### Ideia importante

Nesta PL, o ESP32 é simultaneamente:

```text
microcontrolador
+
dispositivo de rede
```

Isto permite fazer:

```text
PC/SRV01  ←──── Wi-Fi/IP ────→  ESP32
                               │
                               └── GPIO → LED
```

É a primeira ligação clara entre **networking e embedded systems**.

---

# 1.3 Arduino execution model: `setup()` e `loop()`

Este é um conceito fundamental da PL.

Um programa Arduino tem essencialmente:

```cpp
void setup() {
    // executado uma vez
}

void loop() {
    // executado repetidamente
}
```

Mentalmente:

```text
POWER ON / RESET
       ↓
    setup()
       ↓
   ┌→ loop()
   │    ↓
   └────┘
```

`setup()` é usado para inicialização:

- Serial;
- GPIO;
- Wi-Fi;
- servidor TCP;
- outras configurações.

`loop()` representa o comportamento contínuo do dispositivo.

---

# 1.4 Exercício 1 — Blink

O primeiro exercício serve para provar três coisas:

1. o ESP32 está corretamente configurado;
2. conseguimos fazer upload de firmware;
3. conseguimos controlar hardware através de GPIO.

A sequência lógica é:

```text
pinMode(..., OUTPUT)

HIGH
 ↓
LED ON
 ↓
delay
 ↓
LOW
 ↓
LED OFF
 ↓
delay
 ↓
repeat
```

O guião também distingue o ESP32 convencional do **ESP32-S3**, onde determinadas boards usam um LED RGB/WS2812 em vez de um LED GPIO simples.

Isso é importante porque:

> **“ESP32” não identifica completamente o hardware.**

É preciso saber **qual é a board e qual é o pinout**.

---

# 1.5 Exercício 2 — Serial / Hello World

Agora entra o segundo mecanismo de debugging:

```cpp
Serial.begin(9600);
Serial.println("Hello World");
```

O fluxo é:

```text
ESP32
 │
 │ USB / Serial
 ▼
PC
 │
 ▼
Serial Monitor
```

O objetivo é poderes observar o estado interno do programa.

Isto torna-se particularmente importante quando entrares em Wi-Fi:

```text
Connecting...
Connected
IP address: ...
Sending UDP...
Received...
```

Sem Serial Monitor, estás praticamente a programar às cegas.

---

# 1.6 Exercício 3 — juntar GPIO + debugging

Agora:

```text
LED ON  → Serial: "LED:On"

LED OFF → Serial: "LED:Off"
```

Parece trivial, mas estabelece uma prática importante:

```text
ação física
+
observabilidade por software
```

Ou seja, não basta mudar o estado do hardware; também queremos conseguir observar/debuggar o comportamento.

---

# 1.7 A grande mudança — exercício 4: UDP

Aqui começa realmente a parte de **Tecnologias de Comunicação**.

E aqui aparece a primeira dependência explícita:

### ⚠️ Dependência da PL1

O guião diz para executar na `SRV01`:

**`udp_srv.c` — Lab01.ex02**

Portanto:

```text
PL1
UDP server em C
        ↑
        │ UDP/IP
        │
PL3     │
ESP32 UDP client
```

Arquitetura:

```text
             Wi-Fi / IP

ESP32                             SRV01
UDP CLIENT                       UDP SERVER
    │                                │
    │ "hello world"                  │
    ├───────────────────────────────►│ :9999
    │                                │
    │            response            │
    │◄───────────────────────────────┤
```

Isto é provavelmente **o conceito central da primeira metade da PL3**.

---

# 1.8 O ESP32 entra na rede Wi-Fi

Primeiro:

```cpp
WiFi.begin(ssid, pwd);
```

Depois espera:

```cpp
while (WiFi.status() != WL_CONNECTED)
```

Quando obtém conectividade:

```cpp
WiFi.localIP()
```

Agora o ESP32 deixou de ser apenas um microcontrolador.

Passou a ser um **host numa rede IP**.

Por exemplo:

```text
ESP32
IP: 192.168.x.y

SRV01
IP: 192.168.x.z
Port: 9999
```

Para comunicarem, a configuração de rede tem de permitir reachability entre os dois.

---

# 1.9 Enviar um datagrama UDP

O núcleo do código é:

```cpp
udp.beginPacket(udpAddress, udpPort);
udp.write(buffer, 11);
udp.endPacket();
```

Mentalmente:

```text
beginPacket()
     ↓
"quero enviar para IP X, porta 9999"
     ↓
write()
     ↓
"estes são os dados"
     ↓
endPacket()
     ↓
envia datagrama UDP
```

O destino não é apenas um IP.

É:

```text
IP + PORT
```

Por exemplo:

```text
192.168.1.20:9999
```

---

# 1.10 Receção UDP

Depois:

```cpp
udp.parsePacket();
udp.read(buffer, 50);
```

Fluxo completo:

```text
ESP32                            SRV01

beginPacket()
write("hello world")
endPacket()
       ────────────────────────►

                                processa

       ◄────────────────────────
parsePacket()
read()
Serial.println()
```

---

# 1.11 Por que existe `memset()`?

Depois de enviar:

```cpp
memset(buffer, 0, 50);
```

O mesmo buffer vai ser utilizado para receber dados.

Portanto:

```text
ANTES

buffer:
[h][e][l][l][o][ ][w][o][r][l][d][...]


memset()


DEPOIS

buffer:
[0][0][0][0][0][0][0][0][0][0]...
```

Isto evita que conteúdo anterior permaneça no buffer e seja confundido com a nova resposta.

---

# 1.12 Exercício 5 — Error Handling

Aqui aparece uma melhoria importante relativamente ao exemplo inicial.

O programa original praticamente assume:

```text
Wi-Fi OK
UDP OK
envio OK
```

Mas sistemas reais precisam de verificar erros.

O guião pede essencialmente:

```text
WiFi connected?
       │
      NO → erro
       │
      YES
       ↓
beginPacket() succeeded?
       │
      NO → erro
       │
      YES
       ↓
send
```

Isto já começa a aproximar o laboratório de engenharia real.

---

# 1.13 Exercício 6 — UDP passa a controlar hardware

Agora juntamos tudo.

O servidor deve responder `"LightOn"` a cada 10 requests.

ESP32:

```text
UDP request
     ↓
UDP response
     ↓
"LightOn" ?
   /     \
 YES      NO
  │        │
LED ON   LED OFF
```

Aqui tens finalmente:

```text
NETWORK MESSAGE
      ↓
SOFTWARE DECISION
      ↓
PHYSICAL OUTPUT
```

Este é um padrão fundamental em IoT/embedded.

---

# 1.14 Segunda grande parte — TCP

Aqui aparece a segunda dependência.

### ⚠️ Dependência da PL2

Agora acontece o contrário.

Na PL3:

```text
ESP32 = TCP SERVER
```

e reutilizas da PL2:

```text
PC = TCP CLIENT
```

Arquitetura:

```text
PL2                              PL3

TCP CLIENT                    ESP32 TCP SERVER
   │                                │
   │──── connection ───────────────►│ :8080
   │                                │
   │──── "hello" ─────────────────►│
   │                                │
   │◄──── "hello" ─────────────────│
```

O ESP32 implementa inicialmente um **echo server**.

Tudo o que recebe devolve.

---

# 1.15 `WiFiServer` e `WiFiClient`

O servidor é criado:

```cpp
WiFiServer server(8080);
```

Depois:

```cpp
server.begin();
```

No `loop()`:

```cpp
WiFiClient client = server.available();
```

Mentalmente:

```text
server
  │
  │ espera cliente
  ▼
client connects
  │
  ▼
client.available()
  │
  ▼
readString()
  │
  ▼
process
  │
  ▼
reply
```

Isto já é diferente do UDP.

TCP trabalha com uma **conexão** entre cliente e servidor.

---

# 1.16 Exercício final — TCP controla LED

O laboratório termina juntando praticamente tudo:

```text
PC TCP client
      │
      │ "on"
      ▼
ESP32 TCP server
      │
      ├── interpreta comando
      │
      ▼
   LED ON
      │
      ▼
reply "success"
```

E:

```text
"off"
  ↓
LED OFF
  ↓
response
```

Portanto, a evolução completa da PL é:

```text
blink
 ↓
serial
 ↓
Wi-Fi
 ↓
UDP communication
 ↓
UDP → GPIO
 ↓
TCP communication
 ↓
TCP → GPIO
```

---

# 2. Explicação simples das partes difíceis

## UDP vs TCP

Pensa assim:

### UDP = enviar uma carta

```text
ESP32 ─── datagrama ───► Server
```

Envias e não existe uma conexão permanente.

Não tens garantia intrínseca de:

- entrega;
- ordem;
- retransmissão.

### TCP = chamada telefónica

Primeiro estabeleces uma ligação:

```text
Client ═════════ Server
```

Depois os dados circulam através dessa conexão.

Para esta PL basta esta distinção. Não precisamos ainda de aprofundar mecanismos internos.

---

## Client vs Server

Não depende de ser PC ou ESP32.

Depende do papel.

Na parte UDP:

```text
ESP32 = client
SRV01 = server
```

Na parte TCP:

```text
PC = client
ESP32 = server
```

Isto é deliberadamente útil: demonstra que **ESP32 pode assumir ambos os papéis**.

---

## IP vs porta

Mental model:

```text
IP = prédio
PORT = apartamento
```

O IP encontra a máquina.

A porta encontra o serviço/processo dentro dessa máquina.

```text
192.168.1.20:9999
               ↑
              UDP server
```

---

# 3. Issues / inconsistências / pontos pouco claros

Há alguns pontos no material que convém não memorizar literalmente.

**1. `Serial.begin(9600)`** — o documento descreve 9600 como `"Character encoder"`. Isso é enganador. É a configuração da velocidade da comunicação série, tradicionalmente expressa em baud; não é um “character encoder”.

**2. “Arduino IDE uses simplified C++”** — útil pedagogicamente, mas simplificado demais. O código Arduino é essencialmente C++ com framework/core Arduino e preprocessing/build abstraído pela IDE.

**3. `udp.parsePacket()` imediatamente seguido de `udp.read()`** — o exemplo é didático, mas não constitui um protocolo robusto de request/response. Não existe ali uma espera robusta por resposta, timeout/retry bem definido etc. Para esta PL, segue-se o exemplo; não devemos extrapolá-lo como arquitetura de produção.

**4. “ESP32-S3 doesn't have a built-in LED”** — depende da **development board**, não simplesmente do SoC ESP32-S3. O próprio guião já mostra que é necessário confirmar o pinout da board.

**5. Memória/partition tables** — aparecem várias informações sobre OTA, SPIFFS, NVS, Flash etc., mas não parecem ser o centro dos exercícios UDP/TCP. **Not clearly covered in the lecture** quanto à profundidade exigida para avaliação.

---

# O que precisas recuperar das PLs anteriores

Aqui é onde eu concentraria o catch-up.

```text
PL1
└── UDP
    ├── socket
    ├── server
    ├── IP
    ├── port
    ├── recv/send
    └── udp_srv.c
           │
           ▼
          PL3
           │
           └── ESP32 UDP client


PL2
└── TCP
    ├── client
    ├── connection
    ├── IP
    ├── port
    ├── connect
    ├── send/recv
    └── TCP client
           │
           ▼
          PL3
           │
           └── ESP32 TCP server
```

### Prioridade

Não recuperaria PL1 e PL2 inteiras.

Recuperaria somente:

**PL1 → `udp_srv.c`**
**PL2 → TCP client**

Isso é suficiente para desbloquear os exercícios 4–10 desta PL.

---

# 4. 📓 30-Min Notebook Summary

## PL3 — Arduino + UDP + TCP

### ESP32

- MCU 32-bit.
- Wi-Fi integrado.
- GPIO + UART + SPI + I²C + CAN/TWAI etc.
- Confirmar sempre **board + pinout**.

### Arduino program

```text
reset
 ↓
setup() → 1×
 ↓
loop() → ∞
```

`setup()`:

- Serial
- GPIO
- Wi-Fi
- servers

`loop()`:

- comportamento repetitivo

### GPIO

```text
pinMode(pin, OUTPUT)
digitalWrite(pin, HIGH) → ON
digitalWrite(pin, LOW)  → OFF
```

### Serial

```text
Serial.begin(9600)
Serial.println(...)
```

Uso principal nesta PL:

**debug / observabilidade**

---

## Networking

Endpoint:

```text
IP + PORT
```

Mesma rede/reachability necessária.

### UDP — PL1 + PL3

```text
ESP32 CLIENT → SRV01 SERVER :9999
```

ESP32:

```text
WiFi.begin()
 ↓
WL_CONNECTED
 ↓
beginPacket(IP,port)
 ↓
write()
 ↓
endPacket()
 ↓
parsePacket()
 ↓
read()
```

UDP:

- datagramas;
- connectionless;
- baixo overhead;
- entrega não garantida pelo protocolo.

`memset()`:

- limpa buffer antes da receção.

Error handling:

- verificar Wi-Fi;
- verificar `beginPacket`;
- verificar envio;
- reportar erros.

---

## UDP → hardware

```text
Server → "LightOn"
           ↓
         ESP32
           ↓
        LED ON
```

Rede controla estado físico.

---

## TCP — PL2 + PL3

```text
PC CLIENT → ESP32 SERVER :8080
```

ESP32:

```text
WiFiServer server(8080)
 ↓
server.begin()
 ↓
server.available()
 ↓
WiFiClient
 ↓
client.available()
 ↓
read
 ↓
reply
```

TCP:

- orientado à conexão;
- comunicação como stream;
- cliente estabelece conexão ao servidor.

---

## TCP → hardware

```text
client: "on"
      ↓
ESP32 server
      ↓
LED ON
      ↓
response
```

### Relação das PLs

```text
PL1 UDP server ─┐
                ├──► PL3 ESP32 networking + GPIO
PL2 TCP client ─┘
```

**Ideia central:**

```text
network input → embedded processing → physical output
```

---

# 5. Core Concepts — apenas os mais importantes

### 1. ESP32 como host de rede

Não penses nele apenas como “Arduino”.

Nesta PL:

```text
ESP32 = MCU + Wi-Fi + IP stack + application
```

Pode enviar/receber dados como outro computador da rede.

### 2. Client/server é um papel

Não é:

```text
PC = server
ESP32 = client
```

Pode inverter:

```text
UDP: ESP32 client → PC server
TCP: PC client → ESP32 server
```

### 3. Endpoint = IP + porta

```text
IP → máquina
porta → serviço
```

Os dois são necessários para chegar à aplicação correta.

### 4. UDP vs TCP

```text
UDP → datagrams / sem conexão
TCP → stream / conexão
```

Nesta fase, isto é suficiente.

### 5. Comunicação → ação física

É provavelmente a ideia mais interessante da PL:

```text
packet
 ↓
software
 ↓
decision
 ↓
GPIO
 ↓
physical world
```

Isto é a base de muito **IoT, automação e sistemas embebidos distribuídos**.

---

# 6. Essential Exam Questions — 5

### Q1 — Conceptual

**Qual é a diferença entre `setup()` e `loop()`?**

**Resposta:** `setup()` executa uma vez após boot/reset; `loop()` executa repetidamente.

**Raciocínio:** inicialização fica normalmente em `setup`; comportamento contínuo em `loop`.

---

### Q2 — Conceptual

**Qual a principal diferença entre UDP e TCP demonstrada nesta PL?**

**Resposta:** UDP envia datagramas sem estabelecer uma conexão; TCP estabelece uma conexão entre cliente e servidor.

**Raciocínio:** o exemplo UDP usa `beginPacket/write/endPacket`; TCP trabalha com `WiFiClient` ligado ao `WiFiServer`.

---

### Q3 — Practical

**O ESP32 envia UDP para `192.168.1.20:9999`, mas o servidor está a ouvir em `192.168.1.20:8888`. Funciona?**

**Resposta:** Não.

**Raciocínio:** o endpoint inclui **IP e porta**; a aplicação está a ouvir noutra porta.

---

### Q4 — Practical

**O servidor UDP responde `"LightOn"`. O que deve fazer o ESP32 no exercício 6?**

**Resposta:** identificar a resposta e colocar o GPIO/LED no estado ON; para outras respostas, desligá-lo.

**Raciocínio:** o exercício converte uma mensagem de rede numa ação física.

---

### Q5 — Multiple choice

No exercício TCP, qual é a arquitetura correta?

**A)** ESP32 client → PC server
**B)** ESP32 server ← PC client
**C)** dois UDP servers
**D)** não existe client/server

**Resposta: B.**

**Raciocínio:** o ESP32 executa `WiFiServer(8080)` e o cliente da PL2 conecta-se a ele.

---

# 7. Common Pitfalls

- **Confundir client/server com dispositivo.** Um ESP32 pode ser cliente numa experiência e servidor noutra.
- **Esquecer a porta.** Conhecer o IP não chega: `IP + port` identifica o endpoint da aplicação.
- **Começar logo pelo TCP/UDP sem validar hardware.** Primeiro Blink → Serial → Wi-Fi → networking.
- **Não verificar se os dispositivos conseguem comunicar pela rede.** Estarem ambos ligados a “alguma Wi-Fi” não prova reachability.
- **Tentar fazer PL3 sem PL1/PL2.** Os exercícios reutilizam explicitamente `udp_srv.c` da PL1 e o TCP client da PL2.

## Ação

Antes de aprofundarmos esta PL3, o próximo passo útil é **ir buscar PL1 e PL2**. Não precisamos de estudar tudo: quero localizar especificamente o **`udp_srv.c` da PL1** e o **TCP client da PL2** e reconstruir apenas o conhecimento necessário para esta PL3. Isso transforma estas três PLs numa sequência única, em vez de três práticas soltas.
