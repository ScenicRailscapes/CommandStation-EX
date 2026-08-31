/* 
  This file contains (general) automation setups and automations itselfs
*/

// Include files, order is important
#include "myHal.h"
#include "myAliases_stm32.h"
#include "myMacros.h"
#include "myStealthCode.h"
#include "myLedsandLights.h"
#include "myBlocks.h"
#include "mySignals.h"
#include "myReverseLoopAutomation.h"
#include "mySounds.h"
#include "myRoutes.h"
#include "mySwitches.h"
#include "myMimicPanel.h"
#include "myServosAndMotors.h"
#include "myTestExrailKladboek.h"
#include "myRemoteSensors.h"


AUTOSTART

DELAY(1000)
DONE  // Done met auto start

// Even dingen goed zetten
AUTOSTART SEQUENCE(1) 
  LCD(0, " SilberBachTalBahn")
  LCD(1,"")
  LCD(2,"")
  SCREEN(1, 1, "Status Display")
  PARSE("<C WIFI ON>")
  //PARSE("<C WIFI \"Nijlstroom_24\" \"52694646\">")
  //PARSE("<C WIFI HOSTNAME \"SilberBachTalBahn\">")
  PRINT("Alles goed zetten")
  RESET(2000,50)  // Geen idee of dit nodig is of werkt, de bezetmelders resetten voor het mimicpanel

  DELAY(1000) // even wachten
  RESET(300, 16) // Reset I2C I/O #1 expander
  RESET(320, 16) // Reset I2C I/O #2 expander
  RESET(340, 16) // Reset I2C I/O #3 expander
  RESET(360, 16) // Reset I2C I/O #3 expander

  SET(455)  // Lichtenstein dorp leds aan
  SET(454)  // locoshed verlichting aan
  
  SET_TRACK(A,MAIN)
  SET_TRACK(B,MAIN)
  POWERON
  DELAY(500)
  PARSE("<D NODE OFF>") // voor nu even, anders wordt alle node info gedumpt

  // REMOTE SENSORS via Nodes
  REMOTE_SENSOR(2100,5) // BlockDetect sensors Node #1
  REMOTE_SENSOR(2500,3) // HeartBeat vPin Node #1, Node #2 en Node #3

  // 1. Kalibreer de ADS1115 nul-waarden direct bij opstart (later de nodes)
  DELAY(3000)
  CALIBRATE_ADS1115()
  DELAY(2000)
  NEOPIXEL(11000,30,30,30,200)
  DELAY(1000)
  ROUTE_HIDDEN(ROUTE_1)
  ROUTE_HIDDEN(ROUTE_2)
  ROUTE_HIDDEN(ROUTE_3)
  ROUTE_HIDDEN(ROUTE_4)
  ROUTE_HIDDEN(ROUTE_5)
  CLOSE(1002)
  CLOSE(1003)
  CLOSE(1004)
  CLOSE(1005)
  CLOSE(1006)
  CLOSE(1007)
  CLOSE(1020)
  CLOSE(1021)
  CLOSE(1022)
  THROW(1023) // Wissel bergdorp naar binnenbaan
  CLOSE(1024)
  CLOSE(1030)
  CLOSE(1031)
  CLOSE(1032)
  CLOSE(1033)
  CLOSE(1034)
  THROW(1035)
  CLOSE(1036)
  CLOSE(1037)
  CLOSE(1038)
  CLOSE(1039)
  CLOSE(1040)
  CALL(92) // 3-weg wissel op route buitenring helix 

  // Trigger status naar Mimic panel
  DELAY(1000)
  CALL(46)  // Schedule Sync bezetmelders met flag status
DONE

/*                 * * * * * Automation hier staan algemene routines * * * * * *    */

HAL(UserAddin,updateLocoScreen,2000)

/*
  Timed events
*/ 
// Hour chimes
ONCLOCKTIME(25,0) // hh: 25 is ieder uur, mm: 0 is iedere 0 minuut
  SOUND_KERKKLOKKEN_DISTANT
  SOUND_KERKKLOKKEN_NEAR
DONE

ONCLOCKTIME(25,30) // hh: 25 is ieder uur, mm: 30 is ieder half uur
  SOUND_KERKKLOKKEN_TING
DONE

SEQUENCE(46)
  PRINT("Sync Bezetmelders met flag")
  CALL(45)  // Sync bezetmelders met flag status
  DELAYMINS(1)
FOLLOW(46)

// Handmatige herkalibratie route
ROUTE(990,"ReCalibrate Blockdetectors")
  CALIBRATE_ADS1115() // later hernoemen naar RECALIBRATE_BLOCKSENSORS
DONE

// simpele HeartBeat node 1 monitoring via led
// ONSENSOR(REMOTE_NODE_1)
//   IF(REMOTE_NODE_1) SET(REMOTE_NODE_1_LED) ELSE RESET(REMOTE_NODE_1_LED) ENDIF
// DONE

// Testje voor later met timeout functies
AUTOSTART SEQUENCE(5)
	ATTIMEOUT(REMOTE_NODE_1, 500)
	  SET(REMOTE_NODE_1_LED)	// Node online
	IFTIMEOUT RESET(REMOTE_NODE_1_LED) ENDIF // Node offline
	DELAY(500)
FOLLOW(5)