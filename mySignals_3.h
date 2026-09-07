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
DEFINE_BLOCK_SIGNAL(102, SIG_102_J4, SIG_102_J3, SIG_102_J1)   //  BD_D_5 oost zijde

// Inrijsein (2 pinnen)
DEFINE_ENTRY_SIGNAL(113, SIG_113_J4, SIG_113_J3)    // Entry/exit berg vanuit dorp
DEFINE_ENTRY_SIGNAL(114, SIG_114_J4, SIG_114_J3)    // BD_D_4 dal
DEFINE_ENTRY_SIGNAL(115, SIG_115_J4, SIG_115_J3)    // BD_HBI dalx
DEFINE_ENTRY_SIGNAL(116, SIG_116_J4, SIG_116_J3)    // BD_HBI dalx

// Uitrijsein (4 pinnen)
DEFINE_EXIT_SIGNAL(121, SIG_121_J4, SIG_121_J3, SIG_121_J2, SIG_121_J1) // Branchlijn Dorp / Rangeer Yard haven