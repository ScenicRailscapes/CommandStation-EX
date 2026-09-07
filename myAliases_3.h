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

// BlockSignal 102 (Pool 100)
ALIAS(SIG_102_J4, 27)  // GPIO 27
ALIAS(SIG_102_J3, 14)
ALIAS(SIG_102_J1, 12)

// EntrySignal 113
ALIAS(SIG_113_J4, 19) // GPIO 19
ALIAS(SIG_113_J3, 18)

// EntrySignal 114
ALIAS(SIG_114_J4, 5)  // GPIO 5
ALIAS(SIG_114_J3, 17)

// EntrySignal 115
ALIAS(SIG_115_J4, 16) // GPIO 16
ALIAS(SIG_115_J3, 4)

// EntrySignal 116
ALIAS(SIG_116_J4, 2) // GPIO 2
ALIAS(SIG_116_J3, 15)

// ExitSignal 121
ALIAS(SIG_121_J4, 32) // GPIO 32
ALIAS(SIG_121_J3, 33)
ALIAS(SIG_121_J2, 25)
ALIAS(SIG_121_J1, 26)


// Bitmaps (Latches )voor bezet / vrij 
HAL(Bitmap,2003,2) // create flags 2003..2004 // Block bezet flags/latches
ALIAS(BD_D_4_BEZET, 2003)           // Block #6 occupied latch
ALIAS(BD_D_5_BEZET, 2004)           // Block #13 occupied latch

//Bitmaps (Latches )voor bezet / vrij 
// node 1 (remote sensor vPin)
HAL(Bitmap,2012,1)                  // create flags 2012 // IR bezet flags/latches
ALIAS(IR_D_1_3_BEZET, 2012)         // IR Sensor hoofdspoor dorp - haven bezet latch
// node 3
HAL(Bitmap,2062,13) // create flags 2062..2075 // Block bezet flags/latches
ALIAS(IR_S_RIJ_BEZET, 2062)         // IR Stop sensor doorrij spoor bezet latch
ALIAS(IR_D_1_5_BEZET, 2063)         // IR Sensor Visserdorp - dorp hoofdspoor bezet latch
ALIAS(IR_D_4_1_BEZET, 2064)         // IR Sensor Connectie spoor #1 Dorp bezet latch
ALIAS(IR_D_4_2_BEZET, 2065)         // IR Sensor Connectie spoor #1 Dal bezet latch
// ALIAS(IR_D_3_2_BEZET, 2066)         // IR Sensor Hoofdspoor #2 Dorp bezet latch
// ALIAS(IR_D_2_2_BEZET, 2067)         // IR Sensor Hoofdspoor #1 Dorp bezet latch
ALIAS(IR_D_1_4_BEZET, 2068)         // IR Sensor Haven - dorp hoofdspoor bezet latch

ALIAS(BD_D_4_CW, 2069)              // Trein rijdt Clockwise door blok 4
ALIAS(BD_D_4_CCW, 2070)             // Trein rijdt Counter Clockwise door blok 4
ALIAS(BD_D_5_CW, 2071)              // Trein rijdt Clockwise door blok 5
ALIAS(BD_D_5_CCW, 2072)             // Trein rijdt Counter Clockwise door blok 5

/// ****** NODIG *****
// Bitmaps Analoge blockdetectors melders (onbewerkt voor in Stealth, wordt ook voor mimic panel gebruik op CS)
HAL(Bitmap,2095,3)                  // create flags 2095..2097 // blockdetect latches
ALIAS(BD_D_5, 2095)                 // Block #13 yard vissersdorp /dorp branchlijn
ALIAS(BD_D_4, 2096)                 // Block #10 Connectie dorp en hoofdsporen naar yard en helix dal 