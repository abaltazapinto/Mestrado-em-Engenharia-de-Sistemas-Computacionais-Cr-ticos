#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 38
#define NUM_PIXELS 1

Adafruit_NeoPixel pixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_RGB + NEO_KHZ800);

int redValue, greenValue, blueValue;

void updatePixel() {
    pixel.setPixelColor(0, pixel.Color(redValue, greenValue, blueValue));
    pixel.show();
}

void setup() {
    delay(2000);
    Serial.begin(9600);

    redValue = 0;
    greenValue = 0;
    blueValue = 0;

    updatePixel();
}

void loop() {
    redValue = 255;
    updatePixel();
    Serial.println("LED:On");
    delay(1000);

    redValue = 0;
    updatePixel();
    Serial.println("LED:Off");
    delay(1000);
}
