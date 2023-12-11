int gpios[] = {42, 43, 44, 13, 11, 12, 18, 17, 16, 15, 14, 10, 8, 9, 1, 2, 4, 5, 6, 7, 21};

void setup()
{
  Serial.begin(115200);
  delay(250);
  Serial.println("GPIO test");

  int spotTest = 0;

  while (Serial.available()) Serial.read();

  while (1)
  {
    int pinTest = gpios[spotTest];

    pinMode(pinTest, OUTPUT);

    Serial.printf("Testing pin %d. Press any key to move to next test.\r\n", pinTest);
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
