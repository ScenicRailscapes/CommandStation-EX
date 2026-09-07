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

// Blok BD4: Connectie dorp
SETUP_IR_BLOCK_WITH_AMBER(4, BD_D_4, IR_D_4_2_BEZET, IR_D_4_1_BEZET, BD_D_4_BEZET, BD_D_4_CW, BD_D_4_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))
// Blok BD5: Branchlijn yard - dorp
SETUP_IR_BLOCK_WITH_AMBER(5, BD_D_5, IR_D_1_5_BEZET, IR_D_1_3_BEZET, BD_D_5_BEZET, BD_D_5_CW, BD_D_5_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))

// --- Blok 4 Dal - Yard detectie Sensoren ---
SETUP_IR_SENSOR(IR_D_4_1, IR_D_4_1_BEZET, 2000, "IR_D_4_1:Connectie spoor #1 Dal")
SETUP_IR_SENSOR(IR_D_4_2, IR_D_4_2_BEZET, 2000, "IR_D_4_2:Connectie spoor #1 Dorp")

// --- Block 5 Berg - Dorp / Haven detectie Sensoren ---
//SETUP_IR_SENSOR(IR_D_1_3, IR_D_1_3_BEZET, 3000, "IR_D_1_3:Hoofdspoor dorp - haven") // deze naar deze node halen van node 1 af
SETUP_IR_SENSOR(IR_D_1_4, IR_D_1_4_BEZET, 2000, "IR_D_1_4:Haven - dorp hoofdspoor")
SETUP_IR_SENSOR(IR_D_1_5, IR_D_1_5_BEZET, 2000, "IR_D_1_5:Visserdorp - dorp hoofdspoor")