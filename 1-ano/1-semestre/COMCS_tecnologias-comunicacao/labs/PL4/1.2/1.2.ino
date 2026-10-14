#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LED_BUILTIN 2

const char *ssid = "comcs2627m1agXX";
const char *password = "12345678";

WiFiServer server(80);

void setup() {
    delay(5000);

    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);
    Serial.println();
    Serial.println("Configuring access point...");

    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();

    Serial.print("AP IP address: ");
    Serial.println(myIP);

    server.begin();

    Serial.println("Server started");
}

void loop() {
    String currentLine;

    WiFiClient client = server.available();

    if (client) {
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();

                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
                        client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

                        client.println();
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }

                if (currentLine.endsWith("GET /H")) {
                    digitalWrite(LED_BUILTIN, HIGH);
                }

                if (currentLine.endsWith("GET /L")) {
                    digitalWrite(LED_BUILTIN, LOW);
                }
            }
        }

        client.stop();
    }
}
