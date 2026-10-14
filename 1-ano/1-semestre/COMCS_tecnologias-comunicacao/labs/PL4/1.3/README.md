# COMCS PL4 — 1.3 ESPAsyncWebServer

## Objetivo

Criar um Access Point Wi-Fi no ESP32-S3 e disponibilizar um servidor HTTP assíncrono para controlar o NeoPixel onboard.

---

## Hardware

- ESP32-S3
- NeoPixel onboard no GPIO 38

---

## Bibliotecas

- `WiFi`
- `AsyncTCP`
- `ESPAsyncWebServer`
- `Adafruit_NeoPixel`

Versões usadas no laboratório:

- Async TCP 3.5.0
- ESP Async WebServer 3.12.1
- Adafruit NeoPixel 1.15.5
- ESP32 core 3.3.10

---

## Arquitetura

```text
PC / Smartphone
      |
      | Wi-Fi
      v
ESP32-S3 Access Point
      |
      | HTTP over TCP
      v
ESPAsyncWebServer
      |
      | callback da rota
      v
NeoPixel GPIO 38
```

---

## ESP32 como Access Point

O ESP32-S3 não precisa de um router externo neste exercício.

Ele próprio cria a rede Wi-Fi:

```cpp
WiFi.softAP(ssid, password);
```

O endereço IP obtido foi:

```text
192.168.4.1
```

Logo o browser liga diretamente ao ESP32:

```text
http://192.168.4.1/
```

Importante:

```text
ESP32 como Access Point != ESP32 ligado à Internet
```

O ESP32 está a criar uma rede local própria.

---

## Servidor HTTP

Foi criado um servidor HTTP na porta 80:

```cpp
AsyncWebServer server(80);
```

A porta 80 é a porta convencional usada para HTTP.

As rotas utilizadas foram:

```cpp
server.on("/", HTTP_GET, ...);
server.on("/on", HTTP_GET, ...);
server.on("/off", HTTP_GET, ...);
```

Fluxo:

```text
GET /
→ apresenta página HTML

GET /on
→ callback /on
→ liga NeoPixel

GET /off
→ callback /off
→ desliga NeoPixel
```

---

## Síncrono vs Assíncrono

### Exercício 1.2 — `WiFiServer`

No exercício anterior o programa tratava manualmente cada cliente.

```text
loop()
  ↓
server.available()
  ↓
client.connected()
  ↓
client.read()
  ↓
construir pedido HTTP
  ↓
procurar GET /H ou GET /L
```

O próprio programa fazia polling e parsing manual do pedido HTTP.

Exemplo:

```cpp
if (currentLine.endsWith("GET /H")) {
    ...
}
```

### Exercício 1.3 — `ESPAsyncWebServer`

Agora as rotas são registadas previamente:

```cpp
server.on("/on", HTTP_GET, ...);
```

Quando chega um pedido:

```text
HTTP GET /on
      ↓
ESPAsyncWebServer
      ↓
callback associado a /on
      ↓
ação sobre o LED
```

O código deixa de ter de ler manualmente todos os bytes do cliente.

Por isso o `loop()` pode ficar vazio:

```cpp
void loop() {
}
```

Isto não significa que o ESP32 esteja parado.

O stack de rede e a biblioteca continuam a tratar eventos e executam os callbacks quando chegam pedidos.

---

## NeoPixel no ESP32-S3

O exemplo genérico do laboratório usa um LED simples:

```cpp
digitalWrite(LED_BUILTIN, HIGH);
```

Mas nesta board ESP32-S3 o LED onboard é um NeoPixel RGB no GPIO 38.

Configuração:

```cpp
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 38
#define NUM_PIXELS 1

Adafruit_NeoPixel pixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_RGB + NEO_KHZ800);
```

Inicialização:

```cpp
pixel.begin();
pixel.clear();
pixel.show();
```

Ligar LED:

```cpp
pixel.setPixelColor(0, pixel.Color(255, 0, 0));
pixel.show();
```

Desligar LED:

```cpp
pixel.clear();
pixel.show();
```

Logo:

```text
PL4 original:
HTTP → digitalWrite() → LED simples

ESP32-S3:
HTTP → Adafruit_NeoPixel → GPIO 38 → LED RGB
```

---

## Data flow completo

Quando o utilizador carrega em ON:

```text
Browser
  ↓
HTTP GET /on
  ↓
TCP
  ↓
IP
  ↓
Wi-Fi
  ↓
ESP32 Access Point
  ↓
ESPAsyncWebServer
  ↓
callback /on
  ↓
Adafruit_NeoPixel
  ↓
GPIO 38
  ↓
LED ON
```

Quando o utilizador carrega em OFF:

```text
Browser
  ↓
HTTP GET /off
  ↓
TCP/IP
  ↓
Wi-Fi
  ↓
ESP32
  ↓
callback /off
  ↓
pixel.clear()
  ↓
LED OFF
```

---

## Problema encontrado com as bibliotecas

Inicialmente estavam instaladas:

```text
AsyncTCP          1.1.4
ESPAsyncWebServer 3.1.0
```

Com ESP32 core 3.3.10 a compilação falhava com erros relacionados com mbedTLS:

```text
mbedtls_md5_starts_ret was not declared
mbedtls_md5_update_ret was not declared
mbedtls_md5_finish_ret was not declared
```

O erro vinha da biblioteca:

```text
ESPAsyncWebServer/src/WebAuthentication.cpp
```

e não do sketch `1.3.ino`.

Foram então instaladas versões atuais:

```text
Async TCP           3.5.0
ESP Async WebServer 3.12.1
```

Depois disso o programa compilou corretamente.

---

## Arduino CLI

Board usada:

```text
ESP32-S3
```

FQBN:

```text
esp32:esp32:esp32s3
```

Como a comunicação Serial usa a USB nativa do ESP32-S3, foi necessário:

```text
CDCOnBoot=cdc
```

Compilação:

```bash
arduino-cli compile --fqbn esp32:esp32:esp32s3 --board-options CDCOnBoot=cdc .
```

Upload:

```bash
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 --board-options CDCOnBoot=cdc .
```

Serial Monitor:

```bash
arduino-cli monitor -p /dev/ttyACM0 -c baudrate=9600
```

---

## Conceitos principais

### Access Point

Um ESP32 pode funcionar como:

```text
Wi-Fi Station
```

ou:

```text
Wi-Fi Access Point
```

Station:

```text
ESP32
  ↓
liga-se a router/AP existente
```

Access Point:

```text
Phone / PC
    ↓
liga-se ao ESP32
```

### HTTP

HTTP é um protocolo de aplicação.

Exemplo:

```text
GET /on
```

significa:

```text
Método: GET
Recurso: /on
```

A rota `/on` é uma escolha da aplicação.

### TCP

HTTP neste laboratório funciona sobre TCP.

```text
HTTP
 ↓
TCP
 ↓
IP
 ↓
Wi-Fi
```

Portanto:

```text
Wi-Fi != IP != TCP != HTTP
```

São camadas/funções diferentes.

### Callback

Um callback é uma função executada quando ocorre determinado evento.

Exemplo:

```cpp
server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    ...
});
```

Significa:

```text
se chegar HTTP GET /on
→ executar este código
```

### Assíncrono

Assíncrono não significa apenas "mais rápido".

Significa que o programa não precisa de ficar bloqueado à espera de um cliente e a processar cada pedido sequencialmente dentro do `loop()`.

A biblioteca reage a eventos e chama os handlers adequados.

---

## 📓 Guardar no caderno

### ESP32 como Access Point

```text
WiFi.softAP(ssid, password)
```

cria uma rede Wi-Fi diretamente no ESP32.

O dispositivo pode funcionar sem router e sem Internet.

### Estrutura da comunicação

```text
Browser
→ HTTP
→ TCP
→ IP
→ Wi-Fi
→ ESP32
→ callback
→ hardware
```

### Servidor síncrono

```text
loop()
→ esperar cliente
→ ler dados
→ interpretar pedido
→ responder
```

### Servidor assíncrono

```text
definir rotas
→ pedido chega
→ callback executado
```

Exemplo:

```cpp
server.on("/on", HTTP_GET, ...);
```

### NeoPixel ESP32-S3

```text
GPIO 38
```

Inicializar:

```cpp
pixel.begin();
pixel.clear();
pixel.show();
```

Ligar:

```cpp
pixel.setPixelColor(0, pixel.Color(255, 0, 0));
pixel.show();
```

Desligar:

```cpp
pixel.clear();
pixel.show();
```

---

## Possibilidades práticas

O ESP32 pode criar uma pequena rede local e disponibilizar uma interface web sem depender de Internet.

```text
Smartphone
    |
    | Wi-Fi
    v
ESP32
    |
    +-- sensores
    +-- relés
    +-- motores
    +-- LEDs
    +-- configuração
    +-- diagnóstico
    +-- API HTTP
```

Aplicações possíveis:

- configuração inicial de dispositivos;
- controlo de rega;
- controlo de relés;
- monitorização de sensores;
- interface de manutenção;
- configuração de credenciais Wi-Fi;
- painel local para equipamentos;
- diagnóstico de sistemas embedded;
- pequenos gateways IoT.

O conceito importante é que o ESP32 não é apenas um microcontrolador com Wi-Fi.

Ele pode atuar simultaneamente como:

```text
microcontrolador
+
Access Point
+
servidor TCP
+
servidor HTTP
+
interface com hardware
```
