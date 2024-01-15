//int gpios[] = {43, 44, 8, 9, 13, 11, 12, 10, 14, 15, 16, 17, 18, 21, 7, 6, 5, 4, 2, 1, 42};
int gpios[] = {48}; //Card detect
//int gpios[] = {45}; //Qwiic power control
//int gpios[] = {0}; //STAT LED

void setup()
{
  Serial.begin(115200);
  while (Serial == false); //Wait for serial monitor to connect before printing anything
  Serial.println("GPIO test");

  int spotTest = 0;

  while (1)
  {
    int pinTest = gpios[spotTest];

    pinMode(pinTest, OUTPUT);

    Serial.printf("Testing pin %d. Press any key to move to next test.\r\n", pinTest);
    
    while (Serial.available()) Serial.read();
    
    while (1)
    {
      Serial.printf("Pin %d low\r\n", pinTest);
      digitalWrite(pinTest, LOW);
      delay(2000);
      if (Serial.available())
        break;

      Serial.printf("Pin %d high\r\n", pinTest);
      digitalWrite(pinTest, HIGH);
      delay(2000);
      if (Serial.available())
        break;
    }

    digitalWrite(pinTest, HIGH);
    pinMode(pinTest, INPUT);

    spotTest++;
    if (spotTest >= (sizeof(gpios) / sizeof(int)))
      break;
  }
  Serial.println("Done");

  delay(100);
  while (Serial.available()) Serial.read();
}

void loop()
{

}
