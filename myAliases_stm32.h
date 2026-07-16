/*
 This file contains aliases for sensors, locs, switches, relays, motors, servos, latches and other items 
 used in the DCC-EX Command Station setup for the Silberbacktal Bahn model railroad.
*/

// Roster setup for known locs/trains
ROSTER(4,"E32 103","Lights///Shunting")
ROSTER(5,"4800","Lights/Burner")
ROSTER(6,"V290","Lights///Shunting")
ROSTER(7,"BR 89","F0///Shunting")
ROSTER(8,"Tandrad LichtensteinBahn","F0///Shunting")
ROSTER(9,"Glaskasten","Lights/Steam/Whistle Long/*Whistle/Bell/Water/Shunting/Air")
ROSTER(10,"BR 78","Lights/Steam/*Whistle/Bell/Water/Air/Shunting")
ROSTER(11,"BR 53","Lights///Shunting")
ROSTER(12,"18 201","Lights/Steam/////Shunting")
ROSTER(13,"V60","Lights/Sound/*Horn/Smoke/*Coupler/Lights Off F/Lights Off R/Cab Lights/Shunting/*Sec Horn/DownLights/Brake/Radio#1/Heavy/Dash Lights/Bell/Train Brakes/Hand Brakes/Heater/Indusi/Sanding/Compressor/Wissel geluid/Baan geluid/Air release/Fuel pump/Bocht geluid/Whistle/Radio #2/Radio #3/Muting/")
ROSTER(14,"BR 86 LichtensteinBahn","////Shunting")
ROSTER(15,"Kittel Steam tram","Lights/Cabine//Shunting")
ROSTER(17,"OBB 691","Lights/Sound/*Horn/Bell/Fire/*Coupler//Shunting/DownLights/Whistle/Pump/Station #1/Station #2/Language/Volume/TunnelMode/Steam Release/Long Whistle/Airpump/Waterpump/Sanding/Firebox Feed//Brakes/Emergency Brakes")
ROSTER(18,"OBB 2060","Lights///Shunting")
// Aliassen - LET OP: De aliassen werken het beste met echte vPin, niet de ID's, wissels werken wel goed met ID's
// Sensors
/*
  Time of Flight distance sensor VL53L0X.
  In hal.cpp two distances are defined: 200 and 250mm, the first will trigger is within range (vPin is high), the second will trigger if out of range
*/
// ALIAS(VL53L0X_STATION, 650) // VL53L0X distance sensor
/*
  Block detect via DCC Accessory decoder
*/

// Aangesloten op I2C I/O #1 expander 300-315
// IR Sensors (infrarood) voor blok detectie
ALIAS (IR_H_1, 300)                 // IR Sensor Helix dal niveau
ALIAS (IR_H_2, 301)                 // IR Sensor Helix midden niveau
ALIAS (IR_H_3, 302)                 // IR Sensor Helix berg niveau
ALIAS (IR_D_1_1, 308)               // IR Sensor Dorp branchlijn west (berg)
ALIAS (IR_D_1_2, 309)               // IR Sensor Dorp branchlijn station
ALIAS (IR_D_1_3, 310)               // IR Sensor hoofdspoor dorp - haven
ALIAS (IR_D_2_1, 312)               // IR Sensor Hoofdspoor #1 Berg
ALIAS (IR_D_3_1, 311)               // IR Sensor Hoofdspoor #2 Berg
// Block detectors (negatief voor block occupied)
ALIAS(BD_HBU_1, -304)               // Block #1 Helix buitenring op vPin 304 (pin 4 I2C I/O #1)
ALIAS(BD_HBI_1, -305)               // Block #2 Helix binnenring op vPin 305 (pin 5 I2C I/O #1)
ALIAS(BD_D_1, -306)                 // Block #3 Branchlijn / dorpspoor 

// Aangesloten op I2C I/O #2 expander 320-335
// IR Sensors (infrarood) voor blok detectie
ALIAS (IR_S_1, 330)                 // IR Stop sensor parkeerspoor #1
ALIAS (IR_S_2, 331)                 // IR Stop sensor parkeerspoor #2
ALIAS (IR_S_3, 332)                 // IR Stop sensor parkeerspoor #3
ALIAS (IR_S_4, 333)                 // IR Stop sensor parkeerspoor #4
ALIAS (IR_S_5, 334)                 // IR Stop sensor parkeerspoor #5
// Block detectors (negatief voor block occupied)
// let op moet dit negatief zijn? op BD_S_1  ??
ALIAS(BD_S_1, 320)                  // Block #4 Parkeerspoor #1
ALIAS(BD_S_2, -321)                 // Block #5 Parkeerspoor #2
ALIAS(BD_S_3, -322)                 // Block #6 Parkeerspoor #3
ALIAS(BD_S_4, -323)                 // Block #7 Parkeerspoor #4
ALIAS(BD_S_5, -324)                 // Block #8 Parkeerspoor #5
ALIAS(BD_S_RIJ, -325)               // Block #9 Doorrij spoor
ALIAS(BD_D_4, -326)                 // Block #10 Connectie dorp en hoofdsporen naar yard en helix dal 
ALIAS(BD_D_2, -327)                 // Block #11 Hoofdspoor #1
ALIAS(BD_D_3, -328)                 // Block #12 Hoofdspoor #2
ALIAS(BD_D_5, -329)                 // Block #13 yard vissersdorp /dorp branchlijn

// Aangesloten op I2C I/O #3 expander 340-355
// IR Sensors (infrarood) voor blok detectie
ALIAS (IR_S_RIJ, 340)               // IR Stop sensor doorrij spoor
ALIAS (IR_L_1, 341)                 // IR Sensor Liechtenstein spoor eindpunt
ALIAS (IR_L_2, 345)                 // IR Sensor Liechtenstein spoor station midden
ALIAS (IR_L_3, 346)                 // IR Sensor Liechtenstein spoorstation berg
ALIAS (IR_D_1_5, 342)               // IR Sensor Visserdorp - dorp hoofdspoor
ALIAS (IR_D_4_1, 349)               // IR Sensor Connectie spoor #1 Dorp 
ALIAS (IR_D_4_2, 348)               // IR Sensor Connectie spoor #1 Dal
ALIAS (IR_D_3_2, 350)               // IR Sensor Hoofdspoor #2 Dorp
ALIAS (IR_D_2_2, 351)               // IR Sensor Hoofdspoor #1 Dorp
ALIAS (IR_D_1_4, 352)               // IR Sensor Haven - dorp hoofdspoor
// Block detectors (negatief voor block occupied)


// Bitmaps (Latches )voor bezet / vrij 
HAL(Bitmap,2000,50) // create flags 2000..2029 // Block bezet flags/latches
ALIAS(BD_HBI_1_BEZET, 2000)         // Block #1 occupied latch
ALIAS(BD_HBU_1_BEZET, 2001)         // Block #2 occupied latch
ALIAS(BD_D_1_BEZET, 2002)           // Block #3 occupied latch
ALIAS(BD_D_2_BEZET, 2003)           // Block #4 occupied latch
ALIAS(BD_D_3_BEZET, 2004)           // Block #5 occupied latch
ALIAS(BD_D_4_BEZET, 2005)           // Block #6 occupied latch
ALIAS(BD_S_1_BEZET, 2006)           // Block #7 occupied latch
ALIAS(BD_S_2_BEZET, 2007)           // Block #8 occupied latch
ALIAS(BD_S_3_BEZET, 2008)           // Block #9 occupied latch
ALIAS(BD_S_4_BEZET, 2009)           // Block #10 occupied latch
ALIAS(BD_S_5_BEZET, 2010)           // Block #11 occupied latch
ALIAS(BD_S_RIJ_BEZET, 2011)         // Block #12 occupied latch
ALIAS(BD_D_5_BEZET, 2012)           // Block #13 occupied latch
ALIAS(BLOCK_14_BEZET, 2013)         // Block #14 gereserveerd
ALIAS(BD_D_1_CW, 2014)              // Trein rijdt Clockwise door blok 1
ALIAS(BD_D_1_CCW, 2015)             // Trein rijdt Counter Clockwise door blok 1
ALIAS(BD_D_2_CW, 2016)              // Trein rijdt Clockwise door blok 2
ALIAS(BD_D_2_CCW, 2017)             // Trein rijdt Counter Clockwise door blok 2
ALIAS(BD_D_3_CW, 2018)              // Trein rijdt Clockwise door blok 3
ALIAS(BD_D_3_CCW, 2019)             // Trein rijdt Counter Clockwise door blok 3
ALIAS(BD_D_4_CW, 2020)              // Trein rijdt Clockwise door blok 4
ALIAS(BD_D_4_CCW, 2021)             // Trein rijdt Counter Clockwise door blok 4
ALIAS(BD_D_5_CW, 2022)              // Trein rijdt Clockwise door blok 5
ALIAS(BD_D_5_CCW, 2023)             // Trein rijdt Counter Clockwise door blok 5
ALIAS(IR_D_1_1_BEZET, 2024)         // IR Sensor Dorp branchlijn west (berg) bezet latch
ALIAS(IR_D_1_2_BEZET, 2025)         // IR Sensor Dorp branchlijn station bezet latch
ALIAS(IR_D_1_3_BEZET, 2026)         // IR Sensor hoofdspoor dorp - haven bezet latch
ALIAS(IR_D_2_1_BEZET, 2027)         // IR Sensor Hoofdspoor #1 Berg bezet latch
ALIAS(IR_D_3_1_BEZET, 2028)         // IR Sensor Hoofdspoor #2 Berg bezet latch
ALIAS(IR_D_3_2_BEZET, 2029)         // IR Sensor Hoofdspoor #2 Dorp bezet latch
ALIAS(IR_D_2_2_BEZET, 2030)         // IR Sensor Hoofdspoor #1 Dorp bezet latch
ALIAS(IR_D_1_4_BEZET, 2031)         // IR Sensor Haven - dorp hoofdspoor bezet latch
ALIAS(IR_D_1_5_BEZET, 2032)         // IR Sensor Visserdorp - dorp hoofdspoor bezet latch
ALIAS(IR_D_4_1_BEZET, 2033)         // IR Sensor Connectie spoor #1 Dorp bezet latch
ALIAS(IR_D_4_2_BEZET, 2034)         // IR Sensor Connectie spoor #1 Dal bezet latch
ALIAS(IR_H_1_BEZET, 2035)           // IR Sensor Helix dal niveau bezet latch
ALIAS(IR_H_2_BEZET, 2036)           // IR Sensor Helix midden niveau bezet latch
ALIAS(IR_H_3_BEZET, 2037)           // IR Sensor Helix berg niveau bezet latch
ALIAS(IR_S_1_BEZET, 2038)           // IR Stop sensor parkeerspoor #1 bezet latch
ALIAS(IR_S_2_BEZET, 2039)           // IR Stop sensor parkeerspoor #2 bezet latch
ALIAS(IR_S_3_BEZET, 2040)           // IR Stop sensor parkeerspoor #3 bezet latch
ALIAS(IR_S_4_BEZET, 2041)           // IR Stop sensor parkeerspoor #4 bezet latch
ALIAS(IR_S_5_BEZET, 2042)           // IR Stop sensor parkeerspoor #5 bezet latch
ALIAS(IR_S_RIJ_BEZET, 2043)         // IR Stop sensor doorrij spoor bezet latch
ALIAS(BD_HBI_1_CW, 2044)            // Trein rijdt Clockwise door blok HBI
ALIAS(BD_HBI_1_CCW, 2045)           // Trein rijdt Counter Clockwise door blok HBI
ALIAS(BD_HBU_1_CW, 2046)            // Trein rijdt Clockwise door blok HBU
ALIAS(BD_HBU_1_CCW, 2047)           // Trein rijdt Counter Clockwise door blok HBU  


// Branchelijn dorp - reverse loop
HAL(Bitmap,2050,5) // create flags 2050..2055 // General purpose latches
ALIAS(REVERSE_SIGNAL_ACTIVE, 2050)  // Flag to indicate reverse signal is active on DCC track keerlus
ALIAS(DORP_STATION_DETECT, 2051)    // Flag to indicate dorp station sensor detected train
ALIAS(DORP_WEST_DETECT, 2052)       // Flag to indicate dorp west sensor detected train

// Routes
ALIAS(ROUTE_1,1660)                 // Alias voor route 1660 
ALIAS(ROUTE_2,1661)                 // Alias voor route 1661
ALIAS(ROUTE_3,1662)                 // Alias voor route 1662
ALIAS(ROUTE_4,1663)                 // Alias voor route 1663

// Sequences en routes 
ALIAS(BRANCH_DORP_KEERLUS,1600)     // Branchlijn dorp van oost naar west automation
ALIAS(BRANCH_DORP_WEST_OOST,1601)   // Branchlijn dorp van west naar oost automation
ALIAS(KEERLUS_NORMAAL,1900)         // Sequence to set reverse loop to normaal dcc signal
ALIAS(KEERLUS_REVERSE,1901)         // Sequence to set reverse loop to reverse dcc signal


// Relais: Let op: deze zijn inverted signal. Aanzetten met 'RESET' en uit met 'SET' commandp
ALIAS(RELAIS_DCC_REVERSE, RELAIS_KEERLUS)   // Relais - DCC reverse loop relais, draait de fase van het DCC signal om in een keerlus

// Leds


// Motors

// Oud, van kerstbaan, hergebruiken voor iets anders
// Virtual (Latches), de pennen boven de 40 bestaan niet op de ESP. Let op: WEL op de STM32


ALIAS(POWER_ON,254)                // Er is nog geen EXRail poweron status dus LATCH maken            

// temp
VIRTUAL_TURNOUT( 9102,"Sound")
VIRTUAL_TURNOUT( 9103,"Sound")
VIRTUAL_TURNOUT( 9104,"Sound")
