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
  #include "myReverseLoopAutomation.h"
#elif NODENUM == 2
  #include "myHal_2.h"
  #include "myAliases_2.h"
  #include "myMacros_2.h"
  #include "myStealthCode.h"
  #include "mySignals_2.h"
  #include "myNodeSensoren_2.h"
  #include "myServosAndMotors_2.h"
  #include "myBlocks_2.h"
  #include "my_NodeAutomation_2.h"
#else // node 3
  #include "myHal_3.h"
  #include "myAliases_3.h"
  #include "myMacros_3.h"
  #include "myStealthCode.h"
  #include "mySignals_3.h"
  #include "myNodeSensoren_3.h"
  #include "myServosAndMotors_3.h"
  #include "myBlocks_3.h"
  #include "my_NodeAutomation_3.h"
#endif

/* 
  De rest van de myAutomation scripts staan in de 'myNodeAutomation_<nodenummer>.h" bestanden
*/