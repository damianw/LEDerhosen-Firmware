#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            0
#define NUMPIXELS      240
#define BAUD_RATE      57600

#define OPCODE_HELLO   0
#define OPCODE_SET     1
#define OPCODE_CLEAR   2
#define OPCODE_ROTATE  3
#define OPCODE_COMMIT  127

#define RESPONSE_OK    127

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  pixels.begin();
  Serial.begin(BAUD_RATE);
}

void commitChanges() {
  pixels.show();
  Serial.write(RESPONSE_OK);
}

void hello() {
  Serial.write(RESPONSE_OK);
}

void clearStrip() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
  }
}

void updatePixelColor() {
  int r = Serial.parseInt();
  int g = Serial.parseInt();
  int b = Serial.parseInt();
  int pixelCount = Serial.parseInt();
  for (int i = 0; i < pixelCount; i++) {
    int pixel = Serial.parseInt();
    if (pixel < NUMPIXELS) {
      pixels.setPixelColor(pixel, r, g, b);
    }
  }
}

void loop() {
  if (!Serial.available()) return;

  switch (Serial.read()) {
    case OPCODE_HELLO:
      hello();
      break;
    case OPCODE_SET:
      updatePixelColor();
      break;
    case OPCODE_CLEAR:
      clearStrip();
      break;
    case OPCODE_COMMIT:
      commitChanges();
      break;
  }
}
