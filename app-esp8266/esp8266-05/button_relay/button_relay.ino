


const int relayPin = D1;

int relayState = LOW; // estado do relay
const int buttonPin = D3;

int buttonState = 0;
int aux_buttonState = 0;


void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(relayPin, OUTPUT);

  // set initial state, LED off
  Serial.begin(9600);
}

void loop() {
  // read button state, HIGH when pressed, LOW when not
  buttonState = digitalRead(buttonPin);

  // if the push button pressed, switch on the LED
  if (aux_buttonState != buttonState) {

    if (buttonState == HIGH) {

      Serial.println("RElAY on");
      delay(500);
    } else {
      Serial.println("RElAY off");
      relayState = ! relayState;
      digitalWrite(relayPin, relayState); // relay
      delay(500);
    }


  }
  aux_buttonState = buttonState;
  
}
