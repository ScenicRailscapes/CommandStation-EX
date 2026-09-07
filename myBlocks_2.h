/*
  This file contains EXRAIL setup and automations for block and signal control
  Blocks are defined by block detectors using current sensors attached to an ADS1115.
  IR sensors are used for detecting the direction and for stopping the train.

  Due to the repeative nature of the block definitions, macros are used to define the blocks.
*/

/* ====================================================================
   DE ACTUAL BLOKKEN MET HUN SPECIFIEKE SEINEN
   ====================================================================
   FORMAT: SETUP_IR_BLOCK_WITH_AMBER(BLOCKDETECT SENSOR ALIAS, IR1 BEZET DETECTOR, IR2 BEZET DETECTOR, FLAG_BEZET, FLAG_CW, FLAG_CCW, DEBOUNCE, BACKUP_TIMEOUT)
   LET OP: We zetten de volgorde van sensoren alsof de trein in CW richting ze tegenkomt in de prompt.
*/

// Blok BD2: Hoofdspoor #1 
SETUP_IR_BLOCK_WITH_AMBER(2, BD_D_2, IR_D_2_1_BEZET, IR_D_2_2_BEZET, BD_D_2_BEZET, BD_D_2_CW, BD_D_2_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))
// Blok BD3: Hoofdspoor #2
SETUP_IR_BLOCK_WITH_AMBER(3, BD_D_3, IR_D_3_1_BEZET, IR_D_3_2_BEZET, BD_D_3_BEZET, BD_D_3_CW, BD_D_3_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))


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

// --- Schaduwstation (Yard) Stop Sensoren ---
SETUP_IR_SENSOR(IR_S_1,   IR_S_1_BEZET,   2000, "Parkeerspoor 1 stop")
SETUP_IR_SENSOR(IR_S_2,   IR_S_2_BEZET,   2000, "Parkeerspoor 2 stop")
SETUP_IR_SENSOR(IR_S_3,   IR_S_3_BEZET,   2000, "Parkeerspoor 3 stop")
SETUP_IR_SENSOR(IR_S_4,   IR_S_4_BEZET,   2000, "Parkeerspoor 4 stop")
SETUP_IR_SENSOR(IR_S_5,   IR_S_5_BEZET,   2000, "Parkeerspoor 5 stop")
SETUP_IR_SENSOR(IR_S_RIJ, IR_S_RIJ_BEZET, 2000, "Doorrij spoor stop") //voor nu even via node 1

// // --- Hoofdspoor #1 Sensoren ---
SETUP_IR_SENSOR(IR_D_2_1, IR_D_2_1_BEZET, 2000, "IR_D_2_1:Hoofdspoor #1 Berg")
SETUP_IR_SENSOR(IR_D_2_2, IR_D_2_2_BEZET, 3000, "IR_D_2_2:Hoofdspoor #1 Dorp")

// // --- Hoofdspoor #2 Sensoren ---
SETUP_IR_SENSOR(IR_D_3_1, IR_D_3_1_BEZET, 2000, "IR_D_3_1:Hoofdspoor #2 Berg")
SETUP_IR_SENSOR(IR_D_3_2, IR_D_3_2_BEZET, 3000, "IR_D_3_2:Hoofdspoor #2 Dorp")
