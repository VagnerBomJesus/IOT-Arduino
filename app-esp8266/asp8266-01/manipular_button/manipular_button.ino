
const int buttonPin = D3;
const int ledPin = BUILTIN_LED;

int buttonState = 0;
int newData = 0;

void setup() {

  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial sttate, Led off
  digitalWrite(ledPin, buttonState);
 
}

void loop() {

  // read button sate, HIGH when pressed, LOW when not
    
    buttonState = digitalRead(buttonPin);

  if (newData != buttonState) {
    if (buttonState == HIGH) {
      digitalWrite(ledPin, LOW);  // LED on
      Serial.println("LED on");
    } else {
      digitalWrite(ledPin, HIGH ); // LED off
      Serial.println("LED off");
    }
    newData = buttonState;
    delay(500);
  }

}
