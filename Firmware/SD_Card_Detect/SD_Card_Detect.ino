/*
  Detect if SD card is present

  The socket detect switch is normally open, and closed when a card is inserted.
  The switch is connected to VDD, so when a card is inserted, the switch is connected
  to 3.3V. Therefore, we use an internal pull down.
*/
int pin_sdDetect = 48;

void setup()
{
  Serial.begin(115200);
  while (Serial == false); //Wait for serial monitor to connect before printing anything
  Serial.println("SDIO test");

  pinMode(pin_sdDetect, INPUT_PULLDOWN);
}

void loop()
{
  if (Serial.available()) ESP.restart();

  if (digitalRead(pin_sdDetect) == HIGH)
    Serial.println("Card inserted");
  else
    Serial.println("No SD card");

  delay(500);
}
