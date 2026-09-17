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