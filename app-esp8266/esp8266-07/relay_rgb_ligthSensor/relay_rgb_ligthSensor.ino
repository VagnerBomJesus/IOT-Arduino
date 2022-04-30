#include <BH1750.h>
#include <Wire.h> // premite usar o i2c
#include <Adafruit_NeoPixel.h>

const int relayPin = D5; // é o pino onde esta ligado o relay
const int relayState = LOW; // estado do relay

const int ledPin = D7;

BH1750 lightMeter;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  Wire.begin();
  pixels.begin();

  lightMeter.begin();

  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, relayState); // desligar o ralay

  Serial.println(F("BH1750 Test begin"));
}

void loop() {
  float lux = lightMeter.readLightLevel();

  if (lux < 443) {


    digitalWrite(relayPin, LOW);

    setColor(0, 255, 0, 1000); //green
  } else {

    digitalWrite(relayPin, HIGH);
    setColor(0, 0, 0, 0); //deslidado o led
  }

  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
}

void setColor(int redValue, int greenValue, int blueValue, int delayValue)
{
  pixels.setPixelColor(0, pixels.Color(redValue, greenValue, blueValue));
  pixels.show();
  delay(delayValue);
}
