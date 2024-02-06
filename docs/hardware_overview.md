Let's take a closer look at the ESP32-S3 module and other hardware present on this Thing Plus board.

## ESP32-S3 Module

This Thing Plus uses the ESP32-S3-MINI1 wireless module from espressif. The ESP32-S3 is built around the extremely powerful Xtensa<sup>&reg;</sup> dual-core 32-bit LX7 microprocessor with a wireless stack that supports 2.4 GHz WiFi and Bluetooth<sup>&reg;</sup> 5 (LE) with an integrated PCB antenna.

<figure markdown>
[![Photo highlighting ESP32-S3 module.](./assets/){ width="600"}](./assets/ "Click to enlarge")
</figure>

The ESP32-S3-MINI1 

## Power Components

The Thing Plus ESP32-S3 includes several options for powering including USB-C, LiPo battery with on-board battery charging and monitoring circuits as well as direct power inputs.

<figure markdown>
[![Photo highlighting power components/pins.](./assets/){ width="600"}](./assets/ "Click to enlarge")
</figure>

### USB-C Connector

The USB-C connector on the board acts as the primary serial interface for the ESP32-S3 module as well as a power input. It connects directly to the ESP32-S3's USB serial converter. The <b>5V</b> USB input voltage is regulated down to <b>3.3V</b> through a voltage regulator with a max current of <b>500mA@3.3V</b>.

### 2-Pin JST Connector, Battery Charger, & Fuel Gauge

The board has a 2-pin JST connector to connect a single-cell Lithium Ion (LiPo) battery for battery-powered applications. It also has an MCP73831 battery charger to charge an attached battery and a MAX17048 fuel gauge to monitor battery voltage levels. The charge rate is set to <b>214mA@3.3V</b>. The MCP73831 receives power from the V_USB line so it only is powered when <b>5V</b> is provided either over USB or the V_USB PTH pin. If applying voltage directly to the V_USB pin make sure it does not exceed <b>5.5V</b>.

## Pinout & Qwiic Connector

Thing Plus boards break out a large number of GPIO and interface pins to a pair of 0.1"-spaced plated through-hole (PTH) headers and also has a Qwiic connector for easy integration into SparkFun's [Qwiic ecosystem](https://www.sparkfun.com/qwiic).

<figure markdown>
[![Photo highlighting through-hole pinouts.](./assets/){ width="600"}](./assets/ "Click to enlarge")
</figure>

### PTH Headers



### Qwiic Connector

The Qwiic connector is tied to the ESP32-S3's I<sup>2</sup>C bus (IO8/SDA and IO9/SCL). The Qwiic connector provides connections for SDA, SCL, 3.3V, and Ground.

## &micro;SD Card Slot

The board has a &micro;SD card slot that connects to the ESP32-S3's SDIO-4 pins. It is a fricton-fit connector so no "clicking" and "unclicking" is necessary. Just plug it in nice and snug. We chose to tie the SD card the SDIO interface instead of the dedicated SPI bus as we found it to be reliably faster for read/write speeds averaging roughly 2-3MB/s (read) and ~5-7MB/s (write) though speeds vary depending on the card used.

## Buttons

There are two buttons on the board labeled <b>RESET</b> and <b>BOOT</b>. The RESET button is tied to the ESP32-S3's Enable (EN) pin and resets the module when pressed. The BOOT button puts the ESP32-S3 into bootloader mode when held down during power on or reset.

<figure markdown>
[![Photo highlighting solder jumpers.](./assets/){ width="600"}](./assets/ "Click to enlarge")
</figure>

## LEDs

This Thing Plus has three LEDs labeled <b>PWR</b>, <b>CHG</b>, and <b>STAT</b>. The red Power (PWR) LED indicates whenever the <b>3.3V</b> circuit is powered. The yellow Charge (CHG) LED indicates whenever the MCP73831 is charging a connected LiPo battery. The WS2812 RGB Status (STAT) LED connects the LED's Data In signal to IO46.

<figure markdown>
[![Photo highlighting solder jumpers.](./assets/Thing_Plus_S3-LEDs.jpg){ width="600"}](./assets/ "Click to enlarge")
</figure>

## Solder Jumpers

