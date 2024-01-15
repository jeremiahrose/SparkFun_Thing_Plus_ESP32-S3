/*
  ESP32 core v2.0.14

  This demonstrates SPI interface to SD, write and read speed averages. We found
  2.5MB/s to ~4.1MB/s on various microSD cards 1GB to 32GB.

  These exmaples are written not to demonstrate the absolute extremes that a library
  may be capable. Instead, we try to emulate normal user experiences, with basic read/writes.

  Shockingly, sdFat performed as fast, or faster than the SDIO 4-bit interface.

  This depends a lot on how fast you can run the SPI clock (obviously).
  
  Interstingly, SPI inteface allows faster small writes (10k, 100k) as opposed to SDIO mode.

  Dedicated SPI is very much required to achieve fast speed. If you don't have a dedicated
  SPI interface, consider SDIO, or using a micro that has multiple SPI ports.

  sdFat over SPI also supports exFat for very large SD cards (up to 1TB) where as the ESP32
  SDIO library support only FAT32 up to 32GB cards.
*/

#include <SPI.h>
#include "SdFat.h" //http://librarymanager/All#sdfat_exfat by Bill Greiman. At time of writing: v2.1.1

SdFat SD;

//ESP32 Thing Plus
int pin_spiSCK = 18;
int pin_spiPICO = 23; //microSD SDI
int pin_spiPOCI = 19; //microSD SDO
int pin_spiCS = 5;

//ESP32-S3 Thing Plus
//int pin_spiSCK = 38;
//int pin_spiPICO = 34; //microSD SDI
//int pin_spiPOCI = 39; //microSD SDO
//int pin_spiCS = 33;

void setup()
{
  Serial.begin(115200);
  while (Serial == false);

  delay(250);
  Serial.println("SPI bench test");

  runTestsSPI();
}

void loop()
{
  if (Serial.available()) ESP.restart();
}

void runTestsSPI()
{
  SPI.begin(pin_spiSCK, pin_spiPOCI, pin_spiPICO, pin_spiCS);

  //if (!SD.begin(SdSpiConfig(pin_spiCS, SHARED_SPI, SD_SCK_MHZ(50))
//  if (!SD.begin(SdSpiConfig(pin_spiCS, DEDICATED_SPI, SD_SCK_MHZ(30)))) //Fails on ESP32 Thing Plus
  if (!SD.begin(SdSpiConfig(pin_spiCS, DEDICATED_SPI, SD_SCK_MHZ(25))))
  {
    Serial.println("SD failed!");
    return;
  }

  float avgWriteSpeed = 0.0;
  float avgReadSpeed = 0.0;
  int avgAmount = 10;

  for (int i = 0 ; i < avgAmount ; i++)
  {
    //10k and 100k report a little more slow writes
    avgWriteSpeed += fileWriteTest("/test.txt", 500000); //500k is a little slower but mostly indicative of 5MB
    avgReadSpeed += fileReadTest("/test.txt");
  }
  avgWriteSpeed /= avgAmount;
  avgReadSpeed /= avgAmount;

  Serial.printf("avgWriteSpeed: %0.2f avgReadSpeed: %0.2f", avgWriteSpeed, avgReadSpeed);
}

float fileWriteTest(const char *path, uint32_t bytesToWrite)
{
  static uint8_t buf[512];

  //Remove test file if it exists
  SD.remove(path);

  File file = SD.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("Failed to open file for writing");
    return (0.0);
  }

  randomSeed(micros());

  //Fill buffer with random bytes
  for (int x = 0 ; x < sizeof(buf) ; x++)
    buf[x] = random(0, 256); //Inclusive, exclusive

  unsigned long startTime = millis();
  uint32_t bytesLeftToWrite = bytesToWrite;

  while (bytesLeftToWrite > 0)
  {
    uint16_t bytesWritten = 512;
    if (bytesWritten > bytesLeftToWrite)
      bytesWritten = bytesLeftToWrite;

    bytesWritten = file.write(buf, bytesWritten);

    bytesLeftToWrite -= bytesWritten;
  }

  unsigned long writeTime = millis() - startTime;

  float writeSpeed = bytesToWrite / 1000000. / (writeTime / 1000.);

  Serial.printf("Write Test: %0.2f MB = %0.2f MB/s ", bytesToWrite / 1000000., writeSpeed);

  file.close();

  return (writeSpeed);
}

//Read a given file and print the time taken as well as MB/s
float fileReadTest(const char * path)
{
  File file = SD.open(path);
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return (0.0);
  }

  unsigned long bytesLeftToRead = file.size();
  unsigned long fileSize = bytesLeftToRead;
  static uint8_t buf[512];

  unsigned long startTime = millis();
  while (bytesLeftToRead > 0)
  {
    size_t toRead = bytesLeftToRead;
    if (toRead > 512)
      toRead = 512;
    file.read(buf, toRead);
    bytesLeftToRead -= toRead;
  }

  unsigned long readTime = millis() - startTime;

  float readSpeed = fileSize / 1000000. / (readTime / 1000.);
  Serial.printf("Read Test: %0.2f MB = %0.2f MB/s\r\n", fileSize / 1000000., readSpeed);

  file.close();

  return (readSpeed);
}
