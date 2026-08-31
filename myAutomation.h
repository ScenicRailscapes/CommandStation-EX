/***********************************************************************
  This file contains (general) automation setups and automations itselfs
  ***********************************************************************/

// Include files, order is important
#if NODENUM == 1 // Defined in config.h
  #include "myHal_1.h"
  #include "myAliases_1.h"
  #include "myMacros_1.h"
  #include "myStealthCode.h"
  #include "mySignals_1.h"
  #include "myNodeSensoren_1.h"
  #include "myServosAndMotors_1.h"
  #include "myBlocks_1.h"  
  #include "my_NodeAutomation_1.h"
#elif NODENUM == 2
  #include "myHal_2.h"
  #include "myAliases_2.h"
  #include "myMacros_2.h"
  #include "myStealthCode.h"
  #include "mySignals_2.h"
  #include "myNodeSensoren_2.h"
  #include "myServosAndMotors_2.h"
//#include "myBlocks_2.h"
  #include "my_NodeAutomation_2.h"
#else // node 3
  #include "myHal_3.h"
  #include "myAliases_3.h"
  #include "myMacros_3.h"
  #include "myStealthCode.h"
  #include "mySignals_3.h"
  #include "myNodeSensoren_3.h"
  #include "myServosAndMotors_3.h"
//#include "myBlocks_3.h"
  #include "my_NodeAutomation_3.h"
#endif

/* 
  De rest van de myAutiomation scripts staan in de 'myNodeAutomation_<nodenummer>.h" bestanden
*/

// AUTOSTART
//   LCD(0, "SilberBachTalBahn node #1")
//   LCD(1,"")
//   LCD(2,"")
//   SCREEN(1, 1, "Status Display")
//   PARSE("<C WIFI ON>")
//   DELAY(500)
//   PRINT("We kunnen verder")
//   PARSE("<D NODE OFF>") // voor nu even, anders wordt alle node info gedumpt
//   // Zet de analoge porten als input. Zonder dit lijkt het of 0 of het hangt
//   IFLT(BD_HBU_SENSOR, 255)          ENDIF
//   IFLT(BD_HBI_SENSOR, 255)          ENDIF
//   IFLT(BD_DORP_STATION_SENSOR, 255) ENDIF
//   IFLT(BD_D_4_SENSOR, 255)          ENDIF
//   IFLT(BD_D_5_SENSOR, 255)          ENDIF
//   DELAY(500)
//   CALIBRATE_BLOCKSENSOREN()

//   // Zet heartbeat signaal aan voor naar command station
//   BLINK(HEARTBEAT_NODE_1,500,500)
// DONE

// // --- Continue loop voor uitlezen blockdetectors analoge ports
// AUTOSTART SEQUENCE(2)
//   // 2. Verwerk alle analoge ingangen in C++ (supersnel)
//   PROCESS_BLOCKSENSOREN()
//   DELAY(1000) 
// FOLLOW(2)

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