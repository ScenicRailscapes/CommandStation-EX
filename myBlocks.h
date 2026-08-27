/*
  This file contains EXRAIL setup and automations for block and signal control
  Blocks are defined by block detectors using current sensors attached to an ADS1115.
  IR sensors are used for detecting the direction and for stopping the train.

  Due to the repeative nature of the block definitions, macros are used to define the blocks.
*/
// ToDo: opruimen signal code uit macros en iets anders voor loop_entry_ maken.. Signals nu via eigen monitor routines, dit was te simpel.

/* ====================================================================
   DE ACTUAL BLOKKEN MET HUN SPECIFIEKE SEINEN
   ====================================================================
   FORMAT: SETUP_IR_BLOCK_WITH_AMBER(BLOCKDETECT SENSOR ALIAS, IR1 BEZET DETECTOR, IR2 BEZET DETECTOR, FLAG_BEZET, FLAG_CW, FLAG_CCW, DEBOUNCE, BACKUP_TIMEOUT)
   LET OP: We zetten de volgorde van sensoren alsof de trein in CW richting ze tegenkomt in de prompt.
*/

/* Blok 1 (Keerlus): 
   Als de trein via West (IR_D_1_1) binnenkomt (CW), activeert hij LOOP_ENTRY_WEST.
   Als de trein via Oost (IR_D_1_2) binnenkomt (CCW), activeert hij LOOP_ENTRY_EAST. */
SETUP_IR_BLOCK_WITH_AMBER(1, BD_DORP_STATION, IR_D_1_2_BEZET, IR_D_1_1_BEZET, BD_D_1_BEZET, BD_D_1_CW, BD_D_1_CCW, 2000, 500, 0, LOOP_ENTRY_WEST, NO_SIGNAL(0), LOOP_ENTRY_EAST)
// Blok BD2: Hoofdspoor #1 
SETUP_IR_BLOCK_WITH_AMBER(2, BD_D_2, IR_D_2_2_BEZET, IR_D_2_1_BEZET, BD_D_2_BEZET, BD_D_2_CW, BD_D_2_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))
// Blok BD3: Hoofdspoor #2
SETUP_IR_BLOCK_WITH_AMBER(3, BD_D_3, IR_D_3_2_BEZET, IR_D_3_1_BEZET, BD_D_3_BEZET, BD_D_3_CW, BD_D_3_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))
// Blok BD4: Connectie dorp
SETUP_IR_BLOCK_WITH_AMBER(4, BD_D_4, IR_D_4_2_BEZET, IR_D_4_1_BEZET, BD_D_4_BEZET, BD_D_4_CW, BD_D_4_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))
// Blok BD5: Branchlijn yard - dorp
SETUP_IR_BLOCK_WITH_AMBER(5, BD_D_5, IR_D_1_5_BEZET, IR_D_1_3_BEZET, BD_D_5_BEZET, BD_D_5_CW, BD_D_5_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))
// Blok HBI: Helix binnenbaan 
SETUP_IR_BLOCK_WITH_AMBER(6, BD_HBI, IR_HBI_D_BEZET, IR_HBI_B_BEZET, BD_HBI_1_BEZET, BD_HBI_1_CW, BD_HBI_1_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))
// Blok HBU: Helix buitenbaan
SETUP_IR_BLOCK_WITH_AMBER(7, BD_HBU, IR_HBU_D_BEZET, IR_HBU_B_BEZET, BD_HBU_1_BEZET, BD_HBU_1_CW, BD_HBU_1_CCW, 2000, 500, 0, NO_SIGNAL(0), NO_SIGNAL(0), NO_SIGNAL(0))


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
SETUP_IR_SENSOR(IR_HBI_D, IR_HBI_D_BEZET, 4000, "Helix dal niveau binnenring")
SETUP_IR_SENSOR(IR_HBI_M, IR_HBI_M_BEZET, 2000, "Helix midden niveau binnenring")
SETUP_IR_SENSOR(IR_HBI_B, IR_HBI_B_BEZET, 4000, "Helix berg niveau binnenring")
SETUP_IR_SENSOR(IR_HBU_D, IR_HBU_D_BEZET, 4000, "Helix dal niveau buitenring")
SETUP_IR_SENSOR(IR_HBU_M, IR_HBU_M_BEZET, 2000, "Helix midden niveau buitenring")
SETUP_IR_SENSOR(IR_HBU_B, IR_HBU_B_BEZET, 4000, "Helix berg niveau buitenring")

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
SETUP_IR_SENSOR(IR_D_2_2, IR_D_2_2_BEZET, 3000, "IR_D_2_2:Hoofdspoor #1 Dorp")

// --- Hoofdspoor #2 Sensoren ---
SETUP_IR_SENSOR(IR_D_3_1, IR_D_3_1_BEZET, 2000, "IR_D_3_1:Hoofdspoor #2 Berg")
SETUP_IR_SENSOR(IR_D_3_2, IR_D_3_2_BEZET, 3000, "IR_D_3_2:Hoofdspoor #2 Dorp")

// --- Dorp / Haven Verbindings-sensoren ---
SETUP_IR_SENSOR(IR_D_1_3, IR_D_1_3_BEZET, 3000, "IR_D_1_3:Hoofdspoor dorp - haven")
SETUP_IR_SENSOR(IR_D_1_4, IR_D_1_4_BEZET, 2000, "IR_D_1_4:Haven - dorp hoofdspoor")
SETUP_IR_SENSOR(IR_D_1_5, IR_D_1_5_BEZET, 2000, "IR_D_1_5:Visserdorp - dorp hoofdspoor")

// --- Dorp - Hoofdstation Sensoren ---
SETUP_IR_SENSOR(IR_D_1_1, IR_D_1_1_BEZET, 2000, "IR_D_1_1:Dorp branchlijn west (berg)")
SETUP_IR_SENSOR(IR_D_1_2, IR_D_1_2_BEZET, 2000, "IR_D_1_2:Dorp branchlijn station")


// --- Continue loop voor uitlezen blockdetectors analoge ports
AUTOSTART SEQUENCE(2)
  // 2. Verwerk alle analoge ingangen in C++ (supersnel)
  PROCESS_ADS1115()
  DELAY(1000) 
FOLLOW(2)

// --- Synchroniseer de status van bezet flags met MIMIC panel leds
SEQUENCE(45)
  PRINT("EXRAIL: Bezetmelders en Mimic Panel synchroniseren...")
  // Helix
  SYNC_SENSOR_EXPLICIT(BD_HBI, BD_HBI_1_BEZET)
  SYNC_SENSOR_EXPLICIT(BD_HBU, BD_HBU_1_BEZET)

  // Dorp / Hoofdspoor
  SYNC_SENSOR_EXPLICIT(BD_DORP_STATION,  BD_D_1_BEZET)
  SYNC_SENSOR_EXPLICIT(BD_D_2,   BD_D_2_BEZET)
  SYNC_SENSOR_EXPLICIT(BD_D_3,   BD_D_3_BEZET)
  SYNC_SENSOR_EXPLICIT(BD_D_4,   BD_D_4_BEZET)
  SYNC_SENSOR_EXPLICIT(BD_D_5,   BD_D_5_BEZET)

  // Schaduwstation
  SYNC_SENSOR_EXPLICIT(BD_S_1,   BD_S_1_BEZET)
  SYNC_SENSOR_EXPLICIT(BD_S_2,   BD_S_2_BEZET)
  SYNC_SENSOR_EXPLICIT(BD_S_3,   BD_S_3_BEZET)
  SYNC_SENSOR_EXPLICIT(BD_S_4,   BD_S_4_BEZET)
  SYNC_SENSOR_EXPLICIT(BD_S_5,   BD_S_5_BEZET)
  SYNC_SENSOR_EXPLICIT(BD_S_RIJ, BD_S_RIJ_BEZET)
RETURN

