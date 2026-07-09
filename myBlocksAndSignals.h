/*
  This file contains EXRAIL setup and automations for block and signal control
  Blocks are defined by block detectors using current sensors attached to an ESP32.
  The output from the blockdetection is fed into the DCC-EX controller via I2C I/O expander.
  IR sensors are used for detecting the direction and for stopping the train.
  Signals are defined by DCC Accessory decoders
  
  Timed events such as hour chimes are also defined here

  Due to the repeative nature of the block and signal definitions, macros are used to define the blocks and signals.
*/

/* Alle gebruikte macros zijn gedefinieerd in myMacros.h */
#include "myMacros.h"

/* 
  Block Aspects (signals) via DCC Accessory decoder configureren
*/
DCCX_SIGNAL(100,0,2,1)  // Test: Aspect address 100, color 0 = Red, 2= Amber, 1 = Green. Can be called using RED(100), AMBER(100), GREEN(100)
DCCX_SIGNAL(101,0,2,1)  // Test: Aspect address 101, color 0 = Red, 2= Amber, 1 = Green. Can be called using RED(101), AMBER(101), GREEN(101)
DCCX_SIGNAL(102,0,2,1)  // Test: Aspect address 102, color 0 = Red, 2= Amber, 1 = Green. Can be called using RED(102), AMBER(102), GREEN(102)
//Entry aspects 
DCCX_SIGNAL(105,0,0,1)  // Test: Aspect address 105, color 0 = Red, no amber, 1 = Green. Can be called using RED(105), GREEN(105)
DCCX_SIGNAL(106,0,0,1)  // Test: Aspect address 106, color 0 = Red, no amber, 1 = Green. Can be called using RED(165), GREEN(106)
//Exit aspects
DCCX_SIGNAL(108,0,2,1)  // Test: Aspect address 108, color 0 = Red, 2= Amber, 1 = Green. It has a forth color, that is controlled using something different

/*
  Crossing signals via DCC Accesory decoder: (Alles boven de ADEM+5 of BLINK+5 is het aantal keer fade of blink)
  Example: ASPECT(CROSSING_1,ADEM+FAST)   // fade fast, ASPECT(CROSSING_1,KNIPPER+5)   // blink 5x
*/
// Alissen nog verplaatsen naar myAliases_stm32.h
ALIAS(CROSSING_1, 110)  // Crossing signals
ALIAS(CROSSING_2, 111)  // Crossing signals
ALIAS(ADEM, 10)  // Fade
ALIAS(KNIPPER,0) // Blink
ALIAS(SLOW, 1)   // Slow 
ALIAS(FAST, 2)   // Fast 
ALIAS(OFF, 0)    // Off


/* ====================================================================
   DE ACTUAL BLOKKEN MET HUN SPECIFIEKE SEINEN
   ==================================================================== */
/* FORMAT: SETUP_IR_BLOCK_WITH_AMBER(BLOCKDETECT SENSOR ALIAS, IR1 BEZET DETECTOR, IR2 BEZET DETECTOR, FLAG_BEZET, FLAG_CW, FLAG_CCW, DEBOUNCE, BACKUP_TIMEOUT, AMBER_TIMEOUT, ROOD_ACTIE, AMBER_ACTIE, GROEN_ACTIE)
   LET OP: We zetten de volgorde van sensoren alsof de trein in CW richting ze tegenkomt in de prompt.
   Doordat Amber geen specifieke IR detector heeft, wordt de AMBER actie getriggerd door een timer na het passeren van de IR sensor.
*/
// FORMAT: SETUP_IR_BLOCK_WITH_AMBER(BLOK_ID, STROOM, IR1, IR2, VLAG_BEZET, VLAG_CW, VLAG_CCW, DEBOUNCE, BACKUP, AMBER_TIMEOUT, ROOD_ACTIE, AMBER_ACTIE, GROEN_ACTIE)

// Blok 1 (Keerlus): 
// Als de trein via West (IR_D_1_1) binnenkomt (CW), activeert hij LOOP_ENTRY_WEST.
// Als de trein via Oost (IR_D_1_2) binnenkomt (CCW), activeert hij LOOP_ENTRY_EAST.
SETUP_IR_BLOCK_WITH_AMBER(1, BD_D_1, IR_D_1_2, IR_D_1_1, BD_D_1_BEZET, BD_D_1_CW, BD_D_1_CCW, 2000, 500, 7000, LOOP_ENTRY_WEST, NO_SIGNAL(0), LOOP_ENTRY_EAST)

// Blok BD2: Hoofdspoor #1 Op dit moment geen signaal aanwezig, dus we gebruiken NO_SIGNAL(0) en zetten de delay op 0
SETUP_IR_BLOCK_WITH_AMBER(2, BD_D_2, IR_D_2_1_BEZET, IR_D_2_2_BEZET, BD_D_2_BEZET, BD_D_2_CW, BD_D_2_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))
// Blok BD3: Hoofdspoor #2 Simpel 2-aspect sein Lang block (3-aspect sein op 108). Na het passeren van de IR-sluis duurt het 5000ms (5 seconden) voor het sein op Geel springt.
SETUP_IR_BLOCK_WITH_AMBER(3, BD_D_3, IR_D_3_2_BEZET, IR_D_3_1_BEZET, BD_D_3_BEZET, BD_D_3_CW, BD_D_3_CCW, 2000, 500, 5000, SIGNAL_3A_RED(101), SIGNAL_3A_AMBER(101), SIGNAL_3A_GREEN(101))
// Blok BD4: Connectie dorp Simpel 2-aspect sein (Geen Amber aanwezig, dus we gebruiken NO_SIGNAL(0) en zetten de delay op 0)
SETUP_IR_BLOCK_WITH_AMBER(4, BD_D_4, IR_D_4_2_BEZET, IR_D_4_1_BEZET, BD_D_4_BEZET, BD_D_4_CW, BD_D_4_CCW, 2000, 500, 0, SIGNAL_3A_RED(105), NO_SIGNAL(0), SIGNAL_3A_GREEN(105))
// Blok BD5: Branchlijn yard - dorp Lang block (3-aspect sein op 108). Na het passeren van de IR-sluis duurt het 5000ms (5 seconden) voor het sein op Geel springt.
SETUP_IR_BLOCK_WITH_AMBER(5, BD_D_5, IR_D_1_5_BEZET, IR_D_1_1_BEZET, BD_D_5_BEZET, BD_D_5_CW, BD_D_5_CCW, 2000, 500, 5000, SIGNAL_3A_RED(108), SIGNAL_3A_AMBER(108), SIGNAL_3A_GREEN(108))
// Blok HBI: Helix binnenbaan Op dit moment geen signaal aanwezig, dus we gebruiken NO_SIGNAL(0) en zetten de delay op 0
SETUP_IR_BLOCK_WITH_AMBER(6, BD_HBI_1, IR_H_1_BEZET, IR_H_3_BEZET, BD_HBI_1_BEZET, BD_HBI_1_CW, BD_HBI_1_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))
// Blok HBU: Helix buitenbaan Op dit moment geen signaal aanwezig, dus we gebruiken NO_SIGNAL(0) en zetten de delay op 0
SETUP_IR_BLOCK_WITH_AMBER(7, BD_HBU_1, IR_H_2_BEZET, IR_H_3_BEZET, BD_HBU_1_BEZET, BD_HBU_1_CW, BD_HBU_1_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))


/* ====================================================================
   CONFIGURATIE PARKEERSPOREN SCHADUWSTATION
   ==================================================================== */

/* FORMAT: SETUP_YARD_BLOCK(BLOK_ID, BLOCKDETECT SENSOR ALIAS, IR_STOP_SENSOR, BITMAP_BEZET, RELEASE_DELAY, BACKUP_DELAY)
*/

SETUP_YARD_BLOCK(1, BD_S_1, IR_S_1_BEZET, BD_S_1_BEZET, 4000, 500)
SETUP_YARD_BLOCK(2, BD_S_2, IR_S_2_BEZET, BD_S_2_BEZET, 4000, 500)
SETUP_YARD_BLOCK(3, BD_S_3, IR_S_3_BEZET, BD_S_3_BEZET, 4000, 500)
SETUP_YARD_BLOCK(4, BD_S_4, IR_S_4_BEZET, BD_S_4_BEZET, 4000, 500)
SETUP_YARD_BLOCK(5, BD_S_5, IR_S_5_BEZET, BD_S_5_BEZET, 4000, 500)
SETUP_YARD_BLOCK(6, BD_S_RIJ, IR_S_RIJ_BEZET, BD_S_RIJ_BEZET, 4000, 500)


/* ====================================================================
   CONFIGURATIE VAN ALLE IR-SENSOREN
   ==================================================================== */
/*IR sensoren en de treinen zijn nogal onvoorspelbaar. Een trein kan een IR sensor meerdere keren activeren (door verschillen in reflectie), 
  of helemaal niet. Daarom gebruiken we een bitmap latch om te voorkomen dat we teveel meldingen krijgen van dezelfde trein.
  Pas als er NA ACTIVATIE van de IR sensor een bepaalde tijd (bijvoorbeeld 2 seconden) geen activatie meer is, dan wordt de bitmap weer vrijgegeven en kan de volgende activatie weer een melding geven.
*/
/* FORMAT: SETUP_IR_SENSOR(SENSOR_ID, BITMAP_BEZET, DEBOUNCE_DELAY, "PRINT_NAAM")
*/

// --- Helix Sensoren ---
SETUP_IR_SENSOR(IR_H_1,   IR_H_1_BEZET,   4000, "Helix dal niveau")
SETUP_IR_SENSOR(IR_H_2,   IR_H_2_BEZET,   2000, "Helix midden niveau")
SETUP_IR_SENSOR(IR_H_3,   IR_H_3_BEZET,   4000, "Helix berg niveau")

// --- Schaduwstation (Yard) Stop Sensoren ---
SETUP_IR_SENSOR(IR_S_1,   IR_S_1_BEZET,   2000, "Parkeerspoor 1 stop")
SETUP_IR_SENSOR(IR_S_2,   IR_S_2_BEZET,   2000, "Parkeerspoor 2 stop")
SETUP_IR_SENSOR(IR_S_3,   IR_S_3_BEZET,   2000, "Parkeerspoor 3 stop")
SETUP_IR_SENSOR(IR_S_4,   IR_S_4_BEZET,   2000, "Parkeerspoor 4 stop")
SETUP_IR_SENSOR(IR_S_5,   IR_S_5_BEZET,   2000, "Parkeerspoor 5 stop")
SETUP_IR_SENSOR(IR_S_RIJ, IR_S_RIJ_BEZET, 2000, "Doorrij spoor stop")

// --- Blok 4 Connectie Sensoren ---
SETUP_IR_SENSOR(IR_D_4_1, IR_D_4_1_BEZET, 2000, "IR_D_4_1:Connectie spoor #1 Dal")
SETUP_IR_SENSOR(IR_D_4_2, IR_D_4_2_BEZET, 2000, "IR_D_4_2:Connectie spoor #1 Dorp")

// --- Hoofdspoor #1 Sensoren ---
SETUP_IR_SENSOR(IR_D_2_1, IR_D_2_1_BEZET, 2000, "IR_D_2_1:Hoofdspoor #1 Berg")
SETUP_IR_SENSOR(IR_D_2_2, IR_D_2_2_BEZET, 2000, "IR_D_2_2:Hoofdspoor #1 Dorp")

// --- Hoofdspoor #2 Sensoren ---
SETUP_IR_SENSOR(IR_D_3_1, IR_D_3_1_BEZET, 2000, "IR_D_3_1:Hoofdspoor #2 Berg")
SETUP_IR_SENSOR(IR_D_3_2, IR_D_3_2_BEZET, 2000, "IR_D_3_2:Hoofdspoor #2 Dorp")

// --- Dorp / Haven Verbindings-sensoren ---
SETUP_IR_SENSOR(IR_D_1_3, IR_D_1_3_BEZET, 2000, "IR_D_1_3:Hoofdspoor dorp - haven")
SETUP_IR_SENSOR(IR_D_1_4, IR_D_1_4_BEZET, 2000, "IR_D_1_4:Haven - dorp hoofdspoor")
SETUP_IR_SENSOR(IR_D_1_5, IR_D_1_5_BEZET, 2000, "IR_D_1_5:Visserdorp - dorp hoofdspoor")