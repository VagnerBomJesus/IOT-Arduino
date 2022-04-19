

const int relayPin = D1;
const long interval = 2000;  // pause for two seconds

int relayState = LOW; //
unsigned long previousMillis = 0; //


void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.println(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  // if enough millis have elapsed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // toggle the relay
    relayState = !relayState;
    digitalWrite(relayPin, relayState); 
  }
}
