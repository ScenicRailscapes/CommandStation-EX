/************************************************************************
 Matrix Signalen gekoppeld aan de GPIO vPins van een ESP32 DCC-EX NODE
 ***********************************************************************/

/* Hoe te gebruiken ... 
  RED(152)    // Zet Exit Signal 152 op Dubbel Rood (Aspect 0)
  GREEN(152)  // Zet Exit Signal 152 op Groen (Aspect 1)
  AMBER(152)  // Zet Exit Signal 152 op Geel/Groen (Aspect 2)
  
  Wil je het sein op Rood+Wit (Rangeer-aspect) zetten?
  dan aanroepen met; SET_SHUNting_SIGNAL(SIG_152_J4, SIG_152_J3, SIG_152_J2, SIG_152_J1)
*/

/* Alle gebruikte macros zijn gedefinieerd in myMacros.h */
#include "myMacros_3.h"

/* --------------------------------------------------------------------
   SEIN DECLARATIES (Maakt automatisch alle VIRTUAL_SIGNALs aan)
   -------------------------------------------------------------------- */

// Blokseinen (3 pinnen)
DEFINE_BLOCK_SIGNAL(100, SIG_100_J4, SIG_100_J3, SIG_100_J1)   //  BD_D_5
DEFINE_BLOCK_SIGNAL(101, SIG_101_J4, SIG_101_J3, SIG_101_J1)   //  BD_D_1 
//DEFINE_BLOCK_SIGNAL(102, SIG_102_J4, SIG_102_J3, SIG_102_J1)   //
//DEFINE_BLOCK_SIGNAL(103, SIG_103_J4, SIG_103_J3, SIG_103_J1)   // 

// Inrijsein (2 pinnen)
DEFINE_ENTRY_SIGNAL(110, SIG_110_J4, SIG_110_J3)    // Entry/exit berg vanuit dorp
DEFINE_ENTRY_SIGNAL(111, SIG_111_J4, SIG_111_J3)    // BD_D_4 dal
DEFINE_ENTRY_SIGNAL(112, SIG_112_J4, SIG_112_J3)    // BD_HBI dal

// Uitrijsein (4 pinnen)
DEFINE_EXIT_SIGNAL(120, SIG_120_J4, SIG_120_J3, SIG_120_J2, SIG_120_J1) // DB_HBU dal + rangeer sein yard dal
