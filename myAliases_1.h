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
   
// BlockSignal 100 (Seinpaal 100)
ALIAS(SIG_100_J4, 25)  // GPIO 25
ALIAS(SIG_100_J3, 26)
ALIAS(SIG_100_J1, 27)

// BlockSignal 101 (Seinpaal 101) - Deze zit op de PWM controller
ALIAS(SIG_101_J4, 415) 
ALIAS(SIG_101_J3, 414)
ALIAS(SIG_101_J1, 413)

// EntrySignal 110
ALIAS(SIG_110_J4, 14) // GPIO 14
ALIAS(SIG_110_J3, 12)

// EntrySignal 111
ALIAS(SIG_111_J4, 2)  // GPIO 2
ALIAS(SIG_111_J3, 15)

// EntrySignal 112
ALIAS(SIG_112_J4, 16) // GPIO 16
ALIAS(SIG_112_J3, 4)

// ExitSignal 120 
ALIAS(SIG_120_J4, 19) // GPIO 19
ALIAS(SIG_120_J3, 18)
ALIAS(SIG_120_J2, 5)
ALIAS(SIG_120_J1, 17)


// Bitmaps (Latches )voor bezet / vrij 
HAL(Bitmap,2000,5) // create flags 2000..2005 // Block bezet flags/latches
// node 1
ALIAS(BD_HBI_1_BEZET, 2000)         // Block #1 occupied latch
ALIAS(BD_HBU_1_BEZET, 2001)         // Block #2 occupied latch
ALIAS(BD_D_1_BEZET, 2002)           // Block #3 occupied latch

HAL(Bitmap,2010,17)                 // create flags 2010..2026 // IR bezet flags/latches
ALIAS(IR_D_1_1_BEZET, 2010)         // IR Sensor Dorp branchlijn west (berg) bezet latch
ALIAS(IR_D_1_2_BEZET, 2011)         // IR Sensor Dorp branchlijn station bezet latch
ALIAS(IR_D_1_3_BEZET, 2012)         // IR Sensor hoofdspoor dorp - haven bezet latch
ALIAS(IR_HBI_M_BEZET, 2015)         // IR Sensor Helix midden niveau binnenring bezet latch
ALIAS(IR_HBI_B_BEZET, 2016)         // IR Sensor Helix berg niveau binnenring bezet latch
ALIAS(IR_HBI_D_BEZET, 2017)         // IR Sensor Helix dal niveau binnenring bezet latch
ALIAS(IR_HBU_D_BEZET, 2018)         // IR Sensor Helix dal niveau buitenring bezet latch
ALIAS(IR_HBU_M_BEZET, 2019)         // IR Sensor Helix midden niveau buitenring bezet latch
ALIAS(IR_HBU_B_BEZET, 2020)         // IR Sensor Helix berg niveau buitenring bezet latch

ALIAS(BD_D_1_CW, 2021)              // Trein rijdt Clockwise door blok 1
ALIAS(BD_D_1_CCW, 2022)             // Trein rijdt Counter Clockwise door blok 1
ALIAS(BD_HBI_1_CW, 2023)            // Trein rijdt Clockwise door blok HBI
ALIAS(BD_HBI_1_CCW, 2024)           // Trein rijdt Counter Clockwise door blok HBI
ALIAS(BD_HBU_1_CW, 2025)            // Trein rijdt Clockwise door blok HBU
ALIAS(BD_HBU_1_CCW, 2026)           // Trein rijdt Counter Clockwise door blok HBU

/// ****** NODIG *****
// Bitmaps Analoge blockdetectors melders (onbewerkt voor in Stealth, wordt ook voor mimic panel gebruik op CS)
HAL(Bitmap,2080,5)                  // create flags 2080..2085 // blockdetect latches
ALIAS(BD_HBU, 2080)                 // Flag to indicate Helix Buitenring is occupied
ALIAS(BD_HBI, 2081)                 // Helix binnenring
ALIAS(BD_DORP_STATION, 2082)        // Branchlijn dorp-station

HAL(Bitmap,2075,5) // create flags 2075..2079 // General purpose latches
ALIAS(REVERSE_SIGNAL_ACTIVE, 2075)  // Flag to indicate reverse signal is active on DCC track keerlus
ALIAS(DORP_STATION_DETECT, 2076)    // Flag to indicate dorp station sensor detected train
ALIAS(DORP_WEST_DETECT, 2077)       // Flag to indicate dorp west sensor detected train