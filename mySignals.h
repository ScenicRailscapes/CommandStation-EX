/* Alle seinen aangesloten via remote Nodes. Op de nodes staan ook de definities (VIRTUAL_SIGNALs).
*/

/* Hoe te gebruiken ... 
  RED(152)    // Zet Exit Signal 152 op Dubbel Rood (Aspect 0)
  GREEN(152)  // Zet Exit Signal 152 op Groen (Aspect 1)
  AMBER(152)  // Zet Exit Signal 152 op Geel/Groen (Aspect 2)
  
  Wil je het sein op Rood+Wit (Rangeer-aspect) zetten?
  dan aanroepen met; SET_SHUNting_SIGNAL(SIG_152_J4, SIG_152_J3, SIG_152_J2, SIG_152_J1)
*/

/* Alle gebruikte macros zijn gedefinieerd in myMacros.h */
#include "myMacros.h"

// /* --------------------------------------------------------------------
//    SEIN DECLARATIES (Maakt automatisch alle VIRTUAL_SIGNALs aan)
//    -------------------------------------------------------------------- */

// // Blokseinen (3 pinnen)
// DEFINE_BLOCK_SIGNAL(100, SIG_100_J4, SIG_100_J3, SIG_100_J1)   //  BD_D_5
// DEFINE_BLOCK_SIGNAL(101, SIG_101_J4, SIG_101_J3, SIG_101_J1)   //  BD_D_1 
// //DEFINE_BLOCK_SIGNAL(102, SIG_102_J4, SIG_102_J3, SIG_102_J1)   //
// //DEFINE_BLOCK_SIGNAL(103, SIG_103_J4, SIG_103_J3, SIG_103_J1)   // 

// // Inrijsein (2 pinnen)
// DEFINE_ENTRY_SIGNAL(110, SIG_110_J4, SIG_110_J3)    // Entry/exit berg vanuit dorp
// DEFINE_ENTRY_SIGNAL(111, SIG_111_J4, SIG_111_J3)    // BD_D_4 dal
// DEFINE_ENTRY_SIGNAL(112, SIG_112_J4, SIG_112_J3)    // BD_HBI dal

// // Uitrijsein (4 pinnen)
// DEFINE_EXIT_SIGNAL(120, SIG_120_J4, SIG_120_J3, SIG_120_J2, SIG_120_J1) // DB_HBU dal + rangeer sein yard dal


/* misschien macros met alleen een Sensor, maar wel met verschillende signalen die gezet kunnen worden en eventueel timeouts
   voor bv amber en aansturing aan de hand van CCW of CW rijden zoiets als bv..
   
   #define BIND_SENSOR_SIGNALS(SENSOR_ID, SIG_1, SIG_2, SIG_3, AMBER_TIMEOUT, CCW)
   als er een amber timeout is, dan is er dus een amber signal. Misschien later intelligenter maken zoals in het echt
   dat as het volgende block bezet is, dan pas amber
   BIND_SENSOR_SIGNALS(BD_D_1_BEZET,   100, 0, 0, 5000, 1) ??
*/

// voor nu even testje en simpele if then zonder macros

// Sein 100
ONSENSOR(BD_D_5_BEZET)
    IF(BD_D_5_BEZET)
        RED(100)
        DELAY(5000)
        AMBER(100)  
    ELSE
        GREEN(100)
  ENDIF
DONE

// Sein 101
ONSENSOR(BD_D_1_BEZET)
    IF(BD_D_1_BEZET)
        RED(101)
        AFTER(IR_D_1_2_BEZET) // station
            AMBER(101)  
    ELSE
        GREEN(101)
  ENDIF
DONE

// Sein 120 en 110
ONSENSOR(BD_HBU_1_BEZET)
    IF(BD_HBU_1_BEZET)
        RED(120)
        RED(110)
        AFTER(IR_HBU_M_BEZET)
            GREEN(110)      // entry dorp->berg vrij want voorbij dorp CCW of CW maakt niet uit
            IF(BD_HBU_1_CW) // rijden ClockWise dus naar boven)
                AMBER(120)  // dan mag er beneden verder gereden worden na passeren midden helix
            ENDIF
    ELSE
        GREEN(120)
        GREEN(110)
  ENDIF
DONE

// Sein 111
ONSENSOR(BD_D_4_BEZET)
    IF(BD_D_4_BEZET)
        RED(111)
    ELSE
        GREEN(111)
  ENDIF
DONE

// Sein 112
ONSENSOR(BD_HBI_1_BEZET)
    IF(BD_HBI_1_BEZET)
        RED(112)
    ELSE
        GREEN(112)
  ENDIF
DONE
