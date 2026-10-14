#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 38
#define NUM_PIXELS 1

Adafruit_NeoPixel pixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_RGB + NEO_KHZ800);

const char *ssid = "comcs26271200209";
const char *password = "12345678";

AsyncWebServer server(80);

void setup() {
    delay(2000);
    Serial.begin(9600);

    pixel.begin();
    pixel.clear();
    pixel.show();

    WiFi.softAP(ssid, password);

    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html",
                      "<a href=\"/on\">LED ON</a><br>"
                      "<a href=\"/off\">LED OFF</a>");
    });

    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        pixel.setPixelColor(0, pixel.Color(255, 0, 0));
        pixel.show();
        request->send(200, "text/plain", "LED ON");
    });

    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        pixel.clear();
        pixel.show();
        request->send(200, "text/plain", "LED OFF");
    });

    server.begin();
}

void	loop() {
}

