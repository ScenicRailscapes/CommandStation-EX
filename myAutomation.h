/* 
  This file contains (general) automation setups and automations itselfs
*/

// Include files, order is important
#include "myHal.h"
#include "myAliases_stm32.h"
#include "myRemoteSensors.h"
#include "myMacros.h"
#include "myStealthCode.h"
#include "myLedsandLights.h"
//#include "myBlocks.h" // naar nodes
#include "mySignals.h"
#include "myReverseLoopAutomation.h"
#include "mySounds.h"
#include "mySwitches.h"
#include "myMimicPanel.h"
//#include "myServosAndMotors.h"  // naar nodes
#include "myRoutes.h"
#include "myTestExrailKladboek.h"

AUTOSTART

DELAY(1000)
DONE  // Done met auto start

// Even dingen goed zetten
AUTOSTART SEQUENCE(1)
  SET(320,15) // RESET de I2C GPIO Expander
  LCD(0, " SilberBachTalBahn")
  LCD(1,"")
  LCD(2,"")
  SCREEN(1, 1, "Status Display")
  PARSE("<C WIFI ON>")
  PRINT("Alles goed zetten")
  RESET(2000,90)  // Geen idee of dit nodig is of werkt, de bezetmelders resetten voor het mimicpanel
  DELAY(500) // even wachten
  SET_TRACK(A,MAIN)
  SET_TRACK(B,MAIN)
  POWERON
  DELAY(500)
  PARSE("<D NODE OFF>") // voor nu even, anders wordt alle node info gedumpt
  DELAY(500)
  NEOPIXEL(11000,30,30,30,200)  // even alle pixels aanzetten
  RESET(11167)  // behalve deze, pixel teveel
  DELAY(500)
  ROUTE_HIDDEN(ROUTE_1)
  ROUTE_HIDDEN(ROUTE_2)
  ROUTE_HIDDEN(ROUTE_3)
  ROUTE_HIDDEN(ROUTE_4)
  ROUTE_HIDDEN(ROUTE_5)
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

// Testje voor later met timeout functies
AUTOSTART SEQUENCE(5)
	ATTIMEOUT(REMOTE_NODE_1, 500)
	  RESET(REMOTE_NODE_1_LED)	  // Node online
    SET(REMOTE_NODE_1_STATUS) 
	IFTIMEOUT SET(REMOTE_NODE_1_LED) RESET(REMOTE_NODE_1_STATUS) ENDIF // Node offline
	DELAY(500)
FOLLOW(5)

AUTOSTART SEQUENCE(6)
	ATTIMEOUT(REMOTE_NODE_2, 500)
	  RESET(REMOTE_NODE_2_LED)	// Node online
    SET(REMOTE_NODE_2_STATUS)     
	IFTIMEOUT SET(REMOTE_NODE_2_LED) RESET(REMOTE_NODE_2_STATUS) ENDIF // Node offline
	DELAY(500)
FOLLOW(6)

AUTOSTART SEQUENCE(7)
	ATTIMEOUT(REMOTE_NODE_3, 500)
	  RESET(REMOTE_NODE_3_LED)	// Node online
    SET(REMOTE_NODE_3_STATUS)     
	IFTIMEOUT SET(REMOTE_NODE_3_LED) RESET(REMOTE_NODE_3_STATUS) ENDIF // Node offline
	DELAY(500)
FOLLOW(7)

// ALs alle nodes online zijn, wissels en seinen zetten
AUTOSTART SEQUENCE(8)
  IF_ALL(REMOTE_NODE_1_STATUS, REMOTE_NODE_2_STATUS, REMOTE_NODE_3_STATUS)
    IFNOT(REMOTE_NODES_ONLINE_SET) // nog niet eerder gezet
      LCD(7,"Nodes online")
      SET(REMOTE_NODES_ONLINE_SET)
      CLOSE(1002)
      CLOSE(1003)
      CLOSE(1004)
      CLOSE(1005)
      CLOSE(1006)
      CLOSE(1007)
      CLOSE(1009)
      CLOSE(1010)
      CLOSE(1011)
      THROW(1012) // Wissel bergdorp naar binnenbaan
      CLOSE(1013)
      CLOSE(1015)
      CLOSE(1016)
      CLOSE(1017)
      CLOSE(1018)
      CLOSE(1019)
      THROW(1020)
      CLOSE(1021)
      CLOSE(1022)
      CLOSE(1023)
      CLOSE(1024)
      CLOSE(1025)
      CALL(92) // 3-weg wissel op route buitenring helix 
      SET(455)  // Lichtenstein dorp leds aan
      SET(454)  // locoshed verlichting aan
    ENDIF    
    DONE
  ELSE
    DELAY(1000)
    LCD(7,"Nodes OFFLINE!")
  FOLLOW(8)
ENDIF // is dit nodig of kan het zonder



// tijdelijke print en check op echte blockdetector output, dus met ONSENDOR of ONBITMAP HBU, D2 enz om te kijken of deze wel
// goed bezet/niet bezet melden.. soms blijft mimic of bezet 'hangen'

// wat is het verschil tussen ON_SENSOR en ON_BITMAP... alles wat op CS binnenkomt is bitmap sets, dus is bv voor mimicpanel ON_BITMAP beter?
// Oke: ONSENSOR(vPin) triggers if bitmap goes to or from 0
// ONBITMAP(vpin) triggers if bitmap changes... denk dat deze beter is dus.