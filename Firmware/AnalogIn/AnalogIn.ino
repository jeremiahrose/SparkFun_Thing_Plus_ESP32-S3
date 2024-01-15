/*
 
*/

int pin_analogA0 = 10;
int pin_analogA1 = 14;
int pin_analogA2 = 15;
int pin_analogA3 = 16;
int pin_analogA4 = 17;
int pin_analogA6 = 18;


void setup()
{
  Serial.begin(115200);
  while (Serial == false); //Wait for serial monitor to connect before printing anything
}

void loop()
{
  int analogValue = analogRead(analogInPin);

  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  delay(100);
}
