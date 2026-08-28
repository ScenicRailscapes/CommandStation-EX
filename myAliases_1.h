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

// BlockSignal 100 (Pool 100)
ALIAS(SIG_100_J4, 25)  // GPIO 25
ALIAS(SIG_100_J3, 26)
ALIAS(SIG_100_J1, 27)

// BlockSignal 101 (Pool 101)
ALIAS(SIG_101_J4, 16) // GPIO 16
ALIAS(SIG_101_J3, 4)
ALIAS(SIG_101_J1, 0)

// EntrySignal 110
ALIAS(SIG_110_J4, 14) // GPIO 14
ALIAS(SIG_110_J3, 12)

// EntrySignal 111
ALIAS(SIG_111_J4, 23) // GPIO 22
ALIAS(SIG_111_J3, 22)

ALIAS(SIG_112_J4, 2)  // GPIO 2
ALIAS(SIG_112_J3, 15)

// ExitSignal 120 
ALIAS(SIG_120_J4, 19) // GPIO 19
ALIAS(SIG_120_J3, 18)
ALIAS(SIG_120_J2, 5)
ALIAS(SIG_120_J1, 17)

// Bitmaps (Latches )voor bezet / vrij 
// HAL(Bitmap,2000,60) // create flags 2000..2060 // Block bezet flags/latches
// // node 1
// ALIAS(BD_HBI_1_BEZET, 2000)         // Block #1 occupied latch
// ALIAS(BD_HBU_1_BEZET, 2001)         // Block #2 occupied latch
// ALIAS(BD_D_1_BEZET, 2002)           // Block #3 occupied latch
// ALIAS(BD_D_4_BEZET, 2003)           // Block #6 occupied latch
// ALIAS(BD_D_5_BEZET, 2004)           // Block #13 occupied latch

// ALIAS(IR_D_1_1_BEZET, 2010)         // IR Sensor Dorp branchlijn west (berg) bezet latch
// ALIAS(IR_D_1_2_BEZET, 2011)         // IR Sensor Dorp branchlijn station bezet latch
// ALIAS(IR_D_1_3_BEZET, 2012)         // IR Sensor hoofdspoor dorp - haven bezet latch
// ALIAS(IR_D_2_1_BEZET, 2013)         // IR Sensor Hoofdspoor #1 Berg bezet latch
// ALIAS(IR_D_3_1_BEZET, 2014)         // IR Sensor Hoofdspoor #2 Berg bezet latch
// ALIAS(IR_HBI_M_BEZET, 2015)         // IR Sensor Helix midden niveau binnenring bezet latch
// ALIAS(IR_HBI_B_BEZET, 2016)         // IR Sensor Helix berg niveau binnenring bezet latch
// ALIAS(IR_HBI_D_BEZET, 2017)         // IR Sensor Helix dal niveau binnenring bezet latch
// ALIAS(IR_HBU_D_BEZET, 2018)         // IR Sensor Helix dal niveau buitenring bezet latch
// ALIAS(IR_HBU_M_BEZET, 2019)         // IR Sensor Helix midden niveau buitenring bezet latch
// ALIAS(IR_HBU_B_BEZET, 2020)         // IR Sensor Helix berg niveau buitenring bezet latch


// node 2
// ALIAS(BD_D_2_BEZET, 2030)           // Block #4 occupied latch 
// ALIAS(BD_D_3_BEZET, 2031)           // Block #5 occupied latch
// ALIAS(BD_S_1_BEZET, 2032)           // Block #7 occupied latch
// ALIAS(BD_S_2_BEZET, 2033)           // Block #8 occupied latch
// ALIAS(BD_S_3_BEZET, 2034)           // Block #9 occupied latch
// ALIAS(BD_S_4_BEZET, 2035)           // Block #10 occupied latch

// ALIAS(IR_S_1_BEZET, 2040)           // IR Stop sensor parkeerspoor #1 bezet latch
// ALIAS(IR_S_2_BEZET, 2041)           // IR Stop sensor parkeerspoor #2 bezet latch
// ALIAS(IR_S_3_BEZET, 2042)           // IR Stop sensor parkeerspoor #3 bezet latch
// ALIAS(IR_S_4_BEZET, 2043)           // IR Stop sensor parkeerspoor #4 bezet latch
// ALIAS(IR_S_5_BEZET, 2044)           // IR Stop sensor parkeerspoor #5 bezet latch
// Rest nog ruimte voor 1 of 2 seinen, bv voor hoofdspoor

// node 3
// ALIAS(BD_S_5_BEZET, 2050)           // Block #11 occupied latch
// ALIAS(BD_S_RIJ_BEZET, 2051)         // Block #12 occupied latch

// ALIAS(IR_S_RIJ_BEZET, 2052)         // IR Stop sensor doorrij spoor bezet latch
// ALIAS(IR_D_1_5_BEZET, 2053)         // IR Sensor Visserdorp - dorp hoofdspoor bezet latch
// ALIAS(IR_D_4_1_BEZET, 2054)         // IR Sensor Connectie spoor #1 Dorp bezet latch
// ALIAS(IR_D_4_2_BEZET, 2055)         // IR Sensor Connectie spoor #1 Dal bezet latch
// ALIAS(IR_D_3_2_BEZET, 2056)         // IR Sensor Hoofdspoor #2 Dorp bezet latch
// ALIAS(IR_D_2_2_BEZET, 2057)         // IR Sensor Hoofdspoor #1 Dorp bezet latch
// ALIAS(IR_D_1_4_BEZET, 2058)         // IR Sensor Haven - dorp hoofdspoor bezet latch



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