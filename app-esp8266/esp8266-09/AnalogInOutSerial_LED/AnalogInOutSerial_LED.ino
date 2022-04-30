
// These constants won't change. They're used to give names to the pins used:
const int sensorPin = A0;  // Analog input pin that the potentiometer is attached to

int LedPin = D1; // Pin para ligar o led
int sensorValor = 0;

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  Serial.begin(9600); // Define a porta serie para comunicação
  pinMode(LedPin, OUTPUT);
}

void loop() {
  int sensorValor = analogRead(sensorPin); // Lê o valor fornecido pelo LDR
  Serial.println(sensorValor); //Imprime os valores provenientes do sensor na ecrã
  // Caso o valor lido na porta analógica A5 seja maior do que
  // 800, acende o LED
  // Ajuste o valor abaixo de acordo com o circuito
  if (sensorValor < 570)
  {
    digitalWrite(LedPin, HIGH);
  }
  else if(sensorValor > 580) //Caso contrário, apaga o led
  {
    digitalWrite(LedPin, LOW);
  }
  delay(100);
}
