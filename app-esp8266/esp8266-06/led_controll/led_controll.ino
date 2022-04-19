int  valorpot = 0;
float luminosidade = 0;
void setup()
{
  pinMode(D4, OUTPUT);
  Serial.begin(115200);
  Serial.println("Estado do led");
}
void loop()
{

  for (int i = 0; i < 255; i++ ) {
    analogWrite(D4, i);
    delay(20);
  }

  for (int i = 255; i > 0; i--) {
    analogWrite(D4, i);
    delay(20);
  }
}
