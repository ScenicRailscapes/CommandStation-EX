/* =======================================================================================
   Dit bestand bevat de (EXRAIL) setups voor de schakelaars, relais en track statusdisplay
   Ook de schakelaars van bv de TM1638 decoder en LED display worden hier geconfigureerd
  ======================================================================================== */
#include "myMacros.h"

ONBUTTON(CS_F_SWITCH_1)
  PRINT("Functie Switch 1")
DONE

ONBUTTON(CS_F_SWITCH_2)
  PRINT("Functie Switch 2")
DONE

ONBUTTON(CS_F_SWITCH_3)
  PRINT("Functie Switch 3")
DONE

ONBUTTON(CS_F_SWITCH_4)
  PRINT("Functie Switch 4")
DONE


