/*
 HAL drivers, moved from myhal.cpp
 Voor drivers die direct (v)Pins gebruiken is er in config.m een lijst met defines aanwezig die de vPin nummers van de gebruikte hardware bevatten. 
 Daarmee kan de code in de drivers generiek blijven, en kan de gebruiker zelf de vPin nummers aanpassen in config.m specifiek voor bv een ESP32 / Nucleo
 */
/* 2nd OLED screen */
//HAL(HALDisplay<OLED>,1, 0x3c, 128, 64)

//#include "IO_PCA9555.h"     // 16-bit I/O expander (NXP & Texas Instruments).
  //=======================================================================
  // The following directive defines a TM1638 8-digit 7-segment display
  // with 8 buttons.
  //=======================================================================
  // The parameters are:
  //   First Vpin=600
  //   Clock pin=PC6
  //   Data pin=PC5
  //   Strobe pin=PC8

  //	TM1638::create(600, PC6,PC5,PC8); // org HAL code
  
  // Als test HAL init verplaatst naar myAutomation aan einde. lijkt erop dat op de ESP32 de TM1638 driver de init blokeert
  //HAL(TM1638, 600, TM1638_CLOCK, TM1638_STROBE, TM1638_DATA)

  //=======================================================================
  // The following directive defines a DS1307 RTC
  //=======================================================================
  // The parameters are:
  //   First Vpin=700
  //   I2C address=0x68
  //   SDA pin=PC4
  //   SCL pin=PC3
  //   Set clock with (example) <z 630 14 29 30>
  //   bij melding <* DS1307 clock in standby *> is de klok niet goed ingesteld
  //HAL(DS1307,630, {I2CMux_1, SubBus_1, 0x68})
  //HAL(DS1307,630, 0x68)
  
  //=======================================================================
  // The following directive defines a VL53L0X distance sensor
  //=======================================================================
  // The parameters are:
  //   VPIN=650
  //   Number of VPINs=1
  //   I2C address=0x29 (default for this chip)
  //   Minimum trigger range=200mm (VPIN goes to 1 when <20cm)
  //   Maximum trigger range=250mm (VPIN goes to 0 when >25cm)
  //HAL(VL53L0X,650, 1, 0x29, 200, 250)

//=======================================================================
// The following directive defines a PCA9685 PWM Servo driver module.
//=======================================================================
// The parameters are:
//   First Vpin=100
//   Number of VPINs=16 (numbered 100-115)
//   I2C address of module=0x40

HAL(PCA9685,400, 16, 0x40)
// HAL(PCA9685,420, 16, 0x41)
// HAL(PCA9685,440, 16, 0x42)
// HAL(PCA9685,360, 16, 0x45) // #1 Seinen set 1

//=======================================================================
// The following directive defines an PCF8574 8-port I2C GPIO Extender module.
//=======================================================================
// The parameters are:
//   First Vpin=300
//   Number of VPINs=8 (numbered 300-307)
//   I2C address of module=0x22

// HAL(PCF8574,300, 8, 0x22)
// HAL(PCF8575,308, 8, 0x23)

//=======================================================================
// The following directive defines an PCF8575 16-port I2C GPIO Extender module.
//=======================================================================
// The parameters are:
//   First Vpin=200
//   Number of VPINs=16 (numbered 200-215)
//   I2C address of module=0x23

HAL(PCF8575,300, 16, 0x20) // #1


//=======================================================================
// Play mp3 player DFPlayer Mini
//=======================================================================
  // DFPlayer via NXP SC16IS752 I2C Dual UART.
  // I2C address range 0x48 - 0x57
  // 
  // Generic format: 
  // I2CDFPlayer::create(1st vPin, vPins, I2C address);
  // or HAL(DFPlayer,vPin, 1, {I2CMux_1, SubBus_1, address})
  // Parameters:
  // 1st vPin     : First virtual pin that EX-Rail can control to play a sound, use PLAYSOUND command (alias of ANOUT)
  // vPins        : Total number of virtual pins allocated (1 vPin is supported currently)
  //                1st vPin for UART 0
  // I2C Address  : I2C address of the serial controller, in 0x format

// HAL(DFPlayer,10000, 1, 0x54)
// HAL(DFPlayer,10001, 1, 0x49)
// HAL(DFPlayer,10002, 1, 0x4C)

/* =======================================================================
  The following directive defines an ADS1115 4-port I2C Analog module.
  =======================================================================
  ADS1115 address selectie   
  ADDR + GND: 0x48 (Default)
  ADDR + VDD (or VCC): 0x49
  ADDR + SDA: 0x4
  ADDR + ASCL: 0x4B
*/

HAL(ADS111x,500, 4, 0x48)  // #1 four-input ADS1115 on pins 500..503
//HAL(ADS111x,505, 4, 0x49)  // #2 four-input ADS1115 on pins 505..508
//HAL(ADS111x,510, 4, 0x4A)  // #3 four-input ADS1115 on pins 510..513
//HAL(ADS111x,515, 4, 0x4B)  // #4 four-input ADS1115 on pins 515..518

/* =======================================================================
  The following directive defines an Adafruit NEOPIXEL driver
  =======================================================================

      HAL(neoPixel, firstVpin, numberOfPixels [, mode [, i2caddress])
      Where mode is selected from the various pixel string types which have varying
      colour order or refresh frequency. For MOST strings this mode will be NEO_GRB but for others refer to the comments in IO_NeoPixel.h
      If omitted the node and i2caddress default to NEO_GRB, 0x60

      <o vpin>   switches pixel on  (same as <z vpin>) e.g. <o 1005>
      Helderheid: De aansturing staat standaard op volle brightness. Het beste is een kleur te defineren en dan
      de kleur value delen door 4. Dus bv rood = 255,0,0 dat is te fel, maak dat 63,0,0 
      Orange is bv 255, 120, 4 maak dat 63, 30, 1 
      NEOPIXEL(11020 ,63, 30, 1, 10) zet 10 pixels op goed zichtbaar oranje
*/  
    // Let op de vPin nummer en de aantallen pixels dat deze niet een andere vPin overschrijven. 160 pixels per meter 
//HAL(NeoPixel,11000,160,NEO_GRB,0x60)
