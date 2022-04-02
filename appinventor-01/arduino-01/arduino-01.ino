
#define LED_PIN 13

char receivedChar;
boolean newData = false;

void setup() {
 pinMode(LED_PIN, OUTPUT);
 digitalWrite(LED_PIN, LOW);
 Serial.begin(9600);

}

void loop() {
   if(Serial.available() > 0){

      receivedChar = Serial.read();
      newData = true;
     
   }

   if(newData == true){
      if(receivedChar == '0'){
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED: OFF");
      }else if(receivedChar == '1'){
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED: ON");
      }
      newData = false;
   }

}
