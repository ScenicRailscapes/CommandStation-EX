/* 
  This file contains (general) automation setups and automations itselfs
*/

// Include files, order is important
#include "myHal.h"
#include "myAliases_stm32.h"
#include "myMacros.h"
#include "myStealthCode.h"
// #include "myLedsandLights.h"
//#include "myBlocks.h"
#include "mySignals.h"
#include "myNodeSensoren.h"
// #include "myReverseLoopAutomation.h"
// #include "mySounds.h"
// #include "myRoutes.h"
// #include "mySwitches.h"
// #include "myMimicPanel.h"
// #include "myServosAndMotors.h"
// #include "myTestExrailKladboek.h"

AUTOSTART
  LCD(0, " SilberBachTalBahn node #1")
  LCD(1,"")
  LCD(2,"")
  SCREEN(1, 1, "Status Display")
  PARSE("<C WIFI ON>")

  DELAY(500)
  IFLT(34,255) ENDIF  // blijkbaar nodig om een analoge port als input te krijgen..
  DELAY(500)
  PRINT("We kunnen verder")
  PARSE("<D NODE OFF>") // voor nu even, anders wordt alle node info gedumpt
  // Zet de analoge porten als input. Zonder dit lijkt het of 0 of het hangt
  IFLT(BD_HBU_SENSOR, 255)          ENDIF
  IFLT(BD_HBI_SENSOR, 255)          ENDIF
  IFLT(BD_DORP_STATION_SENSOR, 255) ENDIF
  IFLT(BD_D_4_SENSOR, 255)          ENDIF
  IFLT(BD_D_5_SENSOR, 255)          ENDIF
  DELAY(500)
  CALIBRATE_BLOCKSENSOREN()
DONE

// --- Continue loop voor uitlezen blockdetectors analoge ports
AUTOSTART SEQUENCE(2)
  // 2. Verwerk alle analoge ingangen in C++ (supersnel)
  PROCESS_BLOCKSENSOREN()
  DELAY(1000) 
FOLLOW(2)

// Misschien nog iets van een truukje om te controleren of een NODE online is door het setten en resetten van een bitmap die door de command station
// opgepikt wordt, hopelijk later iets van een watchdog ofzo


/*
#define SHARED_SENSOR(vpin,count...)
///brief Defines multiple sensor vpins to be shared to other nodes
///param vpin first vpin number
///param count... Number of consecutive VPINS. Default 1.

#define REMOTE_SENSOR(vpin,count...)
///brief Defines multiple sensor vpins shared by other nodes.
///param vpin first vpin number
///param count... Number of consecutive VPINS. Default 1.

#define SHARED_WRITE_VPINS(vpin,count)
///brief Marks a range of VPINS as shared, so that any node can write to them

#define START_SHARED(sequence_id)
///brief Starts a new task at the given route/animation/sequence and share current loco with it
*/