/* 
  This file contains (general) automation setups and automations itselfs
*/

// Include files, order is important
#include "myHal.h"
// #include "myAliases_stm32.h"
// #include "myMacros.h"
// #include "myStealthCode.h"
// #include "myLedsandLights.h"
// #include "myBlocks.h"
// #include "mySignals.h"
// #include "myReverseLoopAutomation.h"
// #include "mySounds.h"
// #include "myRoutes.h"
// #include "mySwitches.h"
// #include "myMimicPanel.h"
// #include "myServosAndMotors.h"
// #include "myTestExrailKladboek.h"


AUTOSTART
  LCD(0, " SilberBachTalBahn")
  LCD(1,"")
  LCD(2,"")
  SCREEN(1, 1, "Status Display")
  PARSE("<C WIFI ON>")
DONE
