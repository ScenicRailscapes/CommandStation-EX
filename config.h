/****************** W I F I C O N F I G ******************************
 Wifi config is nu via de commandline te doen:
 bv <C WIFI "Nijlstroom_24" "52694646">
 <C WIFI HOSTNAME "SilberBachTalBahn">
 Met <D WIFI SHOW> kan je de huidige wifi config zien.
 <C WIFI AP "SilberBachAP" "MsJmdg11"> voor AP mode
*/

/**********************************************************************

The configuration file for DCC-EX * * * * NODE * * * * * 

**********************************************************************/

/////////////////////////////////////////////////////////////////////////////////////
//
// The IP port to talk to a WIFI or Ethernet shield.
//
#define IP_PORT 2560

/////////////////////////////////////////////////////////////////////////////////////
//
// DEFINE LCD SCREEN USAGE BY THE BASE STATION
//
// Note: This feature requires an I2C enabled LCD screen using a Hitachi HD44780
//       controller and a commonly available PCF8574 based I2C 'backpack'.
// To enable, uncomment one of the #define lines below

// define LCD_DRIVER for I2C address 0x27, 16 cols, 2 rows
// #define LCD_DRIVER  0x27,16,2

//OR define OLED_DRIVER width,height[,address] in pixels (address auto detected if not supplied)
// 128x32 or 128x64 I2C SSD1306-based devices are supported.
// Use 132,64 for a SH1106-based I2C device with a 128x64 display.
#define OLED_DRIVER 0x3d,128,64

// Define scroll mode as 0, 1 or 2
//  *  #define SCROLLMODE 0 is scroll continuous (fill screen if poss),
//  *  #define SCROLLMODE 1 is by page (alternate between pages),
//  *  #define SCROLLMODE 2 is by row (move up 1 row at a time).
#define SCROLLMODE 1

// In order to avoid wasting memory the current scroll buffer is limited
// to 8 lines.  Some users wishing to display additional information
// such as TrackManager power states have requested additional rows aware
// of the warning that this will take extra RAM.  if you wish to include additional rows
// uncomment the following #define and set the number of lines you need.
#define MAX_CHARACTER_ROWS 9


/////////////////////////////////////////////////////////////////////////////////////
// DISABLE / ENABLE VDPY
//
// The Virtual display "VDPY" feature is by default enabled everywhere
// but on Uno and Nano. If you think you can fit it (for example
// having disabled some of the features above) you can enable it with
// ENABLE_VDPY. You can even disable it on all other CPUs with
// DISABLE_VDPY
//
#define DISABLE_VDPY    // stop de echoing van LCD naar serial port
// #define ENABLE_VDPY

/////////////////////////////////////////////////////////////////////////////////////
// Some newer 32bit microcontrollers boot very quickly, so powering on I2C and other
// peripheral devices at the same time may result in the CommandStation booting too
// quickly to detect them.
// To work around this, uncomment the STARTUP_DELAY line below and set a value in
// milliseconds that works for your environment, default is 3000 (3 seconds).
#define STARTUP_DELAY 1000

