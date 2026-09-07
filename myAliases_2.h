/*/**********************************************************************
 This file contains aliases for sensors, locs, switches, relays, motors, 
 servos, latches and other items used in the DCC-EX Command Station 
 setup for the Silberbacktal Bahn model railroad.
/********************************************************************** */

/*
  Block detect via ADC GPIO's van deze DCC-EX Node 
*/

/* ====================================================================
   SEIN CONFIGURATIE (EXRAIL)
   ==================================================================== */

// --------------------------------------------------------------------
// ALIAS DEFINITIES VOOR DE SEINEN AANGESLOTEN OP DEZE NODE
// --------------------------------------------------------------------

// EntrySignal 117
ALIAS(SIG_117_J4, 25) // GPIO 25
ALIAS(SIG_117_J3, 26)

// EntrySignal 118
ALIAS(SIG_118_J4, 27)  // GPIO 27
ALIAS(SIG_118_J3, 14)


// Bitmaps Analoge blockdetectors bezetmelders 
HAL(Bitmap,2100,6)         // create flags 2110..2115 // blockdetect latches
ALIAS(BD_D_2, 2100)        // Flag to indicate Helix Buitenring is occupied
ALIAS(BD_D_3, 2101)        // Helix binnenring
ALIAS(BD_S_1, 2102)        // Branchlijn dorp - station - havendorp
ALIAS(BD_S_2, 2103)        // Yard dal - havendorp
ALIAS(BD_S_3, 2104)        // Branchlijn dorp - havendorp
ALIAS(BD_S_4, 2105)        // Branchlijn dorp - havendorp
ALIAS(BD_S_5, 2106)        // Block #8 Parkeerspoor #5
ALIAS(BD_S_RIJ, 2107)      // Block #9 Doorrij spoor

HAL(Bitmap,2013,2)                  // create flags 2013-2014 // IR bezet flags/latches
ALIAS(IR_D_2_1_BEZET, 2013)         // IR Sensor Hoofdspoor #1 Berg bezet latch
ALIAS(IR_D_3_1_BEZET, 2014)         // IR Sensor Hoofdspoor #2 Berg bezet latch

// Bitmaps (Latches )voor bezet / vrij 
HAL(Bitmap,2030,6)                  // create flags 2000..2035 // Block bezet flags/latches
ALIAS(BD_D_2_BEZET, 2030)           // Block #4 occupied latch 
ALIAS(BD_D_3_BEZET, 2031)           // Block #5 occupied latch
ALIAS(BD_S_1_BEZET, 2032)           // Block #7 occupied latch
ALIAS(BD_S_2_BEZET, 2033)           // Block #8 occupied latch
ALIAS(BD_S_3_BEZET, 2034)           // Block #9 occupied latch
ALIAS(BD_S_4_BEZET, 2035)           // Block #10 occupied latch
HAL(Bitmap,2045,14)                 // create flags 2045..2059 // Block bezet flags/latches
ALIAS(BD_S_5_BEZET, 2045)           // Block #11 occupied latch
ALIAS(BD_S_RIJ_BEZET, 2046)         // Block #12 occupied latch

ALIAS(IR_S_1_BEZET, 2047)           // IR Stop sensor parkeerspoor #1 bezet latch
ALIAS(IR_S_2_BEZET, 2048)           // IR Stop sensor parkeerspoor #2 bezet latch
ALIAS(IR_S_3_BEZET, 2049)           // IR Stop sensor parkeerspoor #3 bezet latch
ALIAS(IR_S_4_BEZET, 2050)           // IR Stop sensor parkeerspoor #4 bezet latch
ALIAS(IR_S_5_BEZET, 2051)           // IR Stop sensor parkeerspoor #5 bezet latch

ALIAS(BD_D_2_CW, 2053)              // Trein rijdt Clockwise door blok 2
ALIAS(BD_D_2_CCW, 2054)             // Trein rijdt Counter Clockwise door blok 2
ALIAS(BD_D_3_CW, 2055)              // Trein rijdt Clockwise door blok 3
ALIAS(BD_D_3_CCW, 2056)             // Trein rijdt Counter Clockwise door blok 3

HAL(Bitmap,2062,1)                  // create flags 2062 // Block bezet flags/latches (deze later weg)
ALIAS(IR_S_RIJ_BEZET, 2062)         // IR Stop sensor doorrij spoor bezet latch

HAL(Bitmap,2066,2)                  // create flags 2066-2067 // IR bezet flags/latches
ALIAS(IR_D_3_2_BEZET, 2066)         // IR Sensor Hoofdspoor #2 Dorp bezet latch
ALIAS(IR_D_2_2_BEZET, 2067)         // IR Sensor Hoofdspoor #1 Dorp bezet latch




/* 
  Aangesloten op I2C I/O #1 expander 300-315
  IR Sensors (infrarood) voor blok detectie
//Laten aanbieden via SHARED_SENSOR
*/
/*
ALIAS (IR_HBU_D, 300)               // IR Sensor Helix dal niveau buitenring
ALIAS (IR_HBU_M, 301)               // IR Sensor Helix midden niveau buitenring
ALIAS (IR_HBI_B, 302)               // IR Sensor Helix berg niveau buitenring
ALIAS (IR_D_1_1, 308)               // IR Sensor Dorp branchlijn west (berg)
ALIAS (IR_D_1_2, 309)               // IR Sensor Dorp branchlijn station
ALIAS (IR_D_1_3, 310)               // IR Sensor hoofdspoor dorp - haven
ALIAS (IR_D_2_1, 312)               // IR Sensor Hoofdspoor #1 Berg
ALIAS (IR_D_3_1, 311)               // IR Sensor Hoofdspoor #2 Berg
ALIAS (IR_HBI_D, 313)               // IR Sensor Helix dal niveau binnenring
ALIAS (IR_HBI_M, 314)               // IR Sensor Helix midden niveau binnenring
ALIAS (IR_HBU_B, 315)               // IR Sensor Helix berg niveau binnenring

// Aangesloten op I2C I/O #2 expander 320-335 OF op de node zelf, zijn er niet veel
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
*/