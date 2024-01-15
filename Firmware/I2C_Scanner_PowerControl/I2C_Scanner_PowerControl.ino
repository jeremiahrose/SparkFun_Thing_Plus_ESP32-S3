/*
 This shows how to control the power to the Qwiic connector.

 This example also shows the Fuel Gauge IC at address 0x36.
 */

#include <Wire.h>

int pin_qwiicPower = 45; //Thing Plus S3 45 is connected to the v-reg that controls the Qwiic power

void setup()
{
  Serial.begin(115200);
  while (Serial == false); //Wait for serial monitor to connect before printing anything

  Serial.println("I2C Scanner");

  //Power on Qwiic connector
  pinMode(pin_qwiicPower, OUTPUT);
  digitalWrite(pin_qwiicPower, HIGH);

  Wire.begin();
}

void loop()
{
  //Toggle the power on the Qwiic connector
  digitalWrite(pin_qwiicPower, LOW);
  delay(2000); //Power LED on a Qwiic board should now be off
  digitalWrite(pin_qwiicPower, HIGH);
  delay(1000); //Power LED on a Qwiic board should now be on

  Serial.println();
  for (byte address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0)
    {
      Serial.print("Device found at address 0x");
      if (address < 0x10)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  Serial.println("Done");
  delay(100);
}
