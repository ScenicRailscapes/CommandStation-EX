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
#include "myMacros_2.h"

/* --------------------------------------------------------------------
   SEIN DECLARATIES (Maakt automatisch alle VIRTUAL_SIGNALs aan)
   -------------------------------------------------------------------- */

// Inrijsein (2 pinnen)
DEFINE_ENTRY_SIGNAL(117, SIG_117_J4, SIG_117_J3)    // Entry berg vanuit hoofdspoor #1
DEFINE_ENTRY_SIGNAL(118, SIG_118_J4, SIG_118_J3)    // Entry berg vanuit hoofdspoor #2
