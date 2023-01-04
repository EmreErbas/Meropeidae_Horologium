# How to Program ESP32-S3
## ESP32-S3 
<dl>
<dt>2.4 GHz WiFi + Bluetooth-LE SoC</dt>
<dt>Supporting IEEE 802.11b/g/n (2.4 GHz WiFi) and Bluetooth ® 5 (LE)</dt>
</dl>

<img src="https://github.com/EmreErbas/Nixie/blob/main/Documents/Notes/Pictures/ESP32-S3-MINI.png" width="1000" />

[ESP32-S3](https://cdn-shop.adafruit.com/product-files/5477/esp32-s3_datasheet_en.pdf) is a low-power MCU-based system-on-chip (SoC) that supports 2.4 GHz Wi-Fi and Bluetooth® Low Energy (Bluetooth LE). It consists of high-performance dual-core microprocessor (Xtensa® 32-bit LX7), a lowpower coprocessor, a Wi-Fi baseband, a Bluetooth LE baseband, RF module, and peripherals.

### FEATURES
#### WiFi
* IEEE 802.11 b/g/n-compliant
* Supports 20 MHz, 40 MHz bandwidth in 2.4 GHz band
* 1T1R mode with data rate up to 150 Mbps
* Wi-Fi Multimedia (WMM)
* TX/RX A-MPDU, TX/RX A-MSDU
* Immediate Block ACK
* Fragmentation and defragmentation
* Automatic Beacon monitoring (hardware TSF)
* 4 × virtual Wi-Fi interfaces
* Simultaneous support for Infrastructure BSS in Station, SoftAP, or Station + SoftAP modes Note that when ESP32-S3 scans in Station mode, the SoftAP channel will change along with the Station channel
* Antenna diversity
* 802.11mc FTM
* External PA is supported 
#### Bluetooth
* Bluetooth LE: Bluetooth 5, Bluetooth mesh
* High power mode (20 dBm, share the same PA with Wi-Fi)
* Speed: 125 Kbps, 500 Kbps, 1 Mbps, 2 Mbps
* Advertising extensions
* Multiple advertisement sets
* Channel selection algorithm #2
* Internal co-existence mechanism between Wi-Fi and Bluetooth to share the same antenna 
#### CPU and Memory
* Xtensa® dual-core 32-bit LX7 microprocessor, up to 240 MHz
* CoreMark® 
    score:
    - 1 core at 240 MHz: 613.86 CoreMark; 2.56 CoreMark/MHz    
    - 2 cores at 240 MHz: 1181.60 CoreMark; 4.92 CoreMark/MHz
* 128-bit data bus and SIMD commands
* 384 KB ROM
* 512 KB SRAM
* 16 KB SRAM in RTC
* SPI, Dual SPI, Quad SPI, Octal SPI, QPI and OPI interfaces that allow connection to multiple flash and external RAM
* Flash controller with cache is supported
* Flash in-Circuit Programming (ICP) is supported
#### Advanced Peripheral Interfaces
* 45 × programmable GPIOs
* Digital 
    interfaces:
    - 4 × SPI
    - 1 × LCD interface (8-bit ~16-bit parallel RGB, I8080 and MOTO6800), 
        - supporting conversion between RGB565, YUV422, YUV420 and YUV411
    - 1 × DVP 8-bit ~16-bit camera interface
    - 3 × UART
    - 2 × I2C
    - 2 × I2S
    - 1 × RMT (TX/RX)
    - 1 × pulse counter
    - LED PWM controller, up to 8 channels
    - 1 × full-speed USB OTG
    - 1 × USB Serial/JTAG controller
    - 2 × MCPWM
    - 1 × SDIO host controller with 2 slots
    - General DMA controller (GDMA), with 5 transmit channels and 5 receive channels
    - 1 × TWAI® controller, compatible with ISO 11898-1 (CAN Specification 2.0)
* Analog 
    interfaces:
    - 2 × 12-bit SAR ADCs, up to 20 channels
    - 1 × temperature sensor
    - 14 × touch sensing IOs
* Timers
    :
    - 4 × 54-bit general-purpose timers
    - 1 × 52-bit system timer
    - 3 × watchdog timers
Low Power Management
* Power Management Unit with five power modes
* Ultra-Low-Power (ULP) 
    coprocessors:
    - ULP-RISC-V coprocessor
    - ULP-FSM coprocessor
Security
* Secure boot
* Flash encryption
* 4-Kbit OTP, up to 1792 bits for users
* Cryptographic hardware 
    acceleration:
    - AES-128/256 (FIPS PUB 197)
    - Hash (FIPS PUB 180-4)
    - RSA
    - Random Number Generator (RNG)
    - HMAC
    - Digital signature

### DEVELOPMENT BOARDS

#### [Adafruit ESP32-S3 Feather](https://learn.adafruit.com/adafruit-esp32-s3-feather)
<img src="https://cdn-shop.adafruit.com/970x728/5323-05.jpg" width="500">

##### Features:
* ESP32-S3 Dual Core 240MHz Tensilica processor the next generation of ESP32-Sx, with native USB so it can act like a keyboard/mouse, MIDI device, disk drive, etc!
* Mini module has FCC/CE certification and comes with either 8 MByte of Flash, no PSRAM or 4MByte of Flash, and 2MB PSRAM (depending on the Feather you purchased)
* Power options - USB type C or Lipoly battery
* Built-in battery charging when powered over USB-C
* LiPoly battery monitor - LC709203 chip actively monitors your battery for voltage and state of charge / percentage reporting over I2C
* Reset and DFU (BOOT0) buttons to get into the ROM bootloader (which is a USB serial port so you don't need a separate cable!)
* Serial debug output pin (optional, for checking the hardware serial debug console)
* STEMMA QT connector for I2C devices, with switchable power, so you can go into low power mode.
* On/Charge/User LEDs + status NeoPixel with pin-controlled power for low power usage
* Low Power friendly! In deep sleep mode we can get down to ~100uA of current draw from the Lipoly connection. Quiescent current is from the power regulator, ESP32-S3 chip, and Lipoly monitor. Turn off the NeoPixel and external I2C power for the lowest quiescent current draw.

<img src="https://github.com/EmreErbas/Nixie/blob/main/Documents/Notes/Pictures/ESP32-S3-Feather-Pinout.png" width="1000" />

##### Arduino IDE
Check the [Guide](https://learn.adafruit.com/adafruit-esp32-s3-feather/arduino-ide-setup)
