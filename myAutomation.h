/* 
  This file contains (general) automation setups and automations itselfs
*/

// Include files, order is important
#include "myHal.h"
#include "myAliases_stm32.h"
#include "myMacros.h"
#include "myLedsandLights.h"
#include "myBlocksAndSignals.h"
//#include "mySignals.h"
#include "myReverseLoopAutomation.h"
#include "mySounds.h"
#include "myRoutes.h"
#include "mySwitches.h"
#include "myMimicPanel.h"
#include "myServosAndMotors.h"
#include "myTestExrailKladboek.h"


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
  UNLATCH(POWER_ON) // Unlatch power on
  RESET(2000,50)  // Geen idee of dit nodig is of werkt, de bezetmelders resetten voor het mimicpanel

  DELAY(1000) // even wachten
  RESET(300, 16) // Reset I2C I/O #1 expander
  RESET(320, 16) // Reset I2C I/O #2 expander
  RESET(340, 16) // Reset I2C I/O #3 expander

  SET(455)  // Lichtenstein dorp leds aan
  SET(454)  // locoshed verlichting aan
  
  SET_TRACK(A,MAIN)
  SET_TRACK(B,MAIN)
  POWERON
  HAL(TM1638, 600, TM1638_CLOCK, TM1638_STROBE, TM1638_DATA)  // Init de TM1683 LED/Key matrix hier ivm blokkeren init.
  DELAY(2000)
  GREEN(101)  // Sein BD_D_2 op groen zetten
  GREEN(102)  // Sein BD_D_3 op groen zetten
  GREEN(105)  // Sein BD_D_4 op groen zetten
  GREEN(108)  // Sein BD_D_5 op groen zetten

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
  CLOSE(1035)
  CLOSE(1036)
  CLOSE(1037)
  CLOSE(1038)
  CLOSE(1039)
  CLOSE(1040)
  CALL(92) // 3-weg wissel op route buitenring helix 
  IFNOT(BD_HBI_1) SET (BD_HBI_1_BEZET) RESET (BD_HBI_1_BEZET) ENDIF
  IFNOT(BD_HBU_1) SET (BD_HBU_1_BEZET) RESET (BD_HBU_1_BEZET) ENDIF
  IF(BD_D_1)   RESET (BD_D_1_BEZET)   ENDIF // probeersel met if ipx ifnot
  IF(BD_D_2)   RESET (BD_D_2_BEZET)   ENDIF
  IF(BD_D_3)   RESET (BD_D_3_BEZET)   ENDIF
  IF(BD_D_4)   RESET (BD_D_4_BEZET)   ENDIF
  IFNOT(BD_D_5)   RESET (BD_D_5_BEZET)   ENDIF
  IFNOT(BD_S_1)   RESET (BD_S_1_BEZET)   ENDIF
  IFNOT(BD_S_2)   RESET (BD_S_2_BEZET)   ENDIF
  IFNOT(BD_S_3)   RESET (BD_S_3_BEZET)   ENDIF
  IFNOT(BD_S_4)   RESET (BD_S_4_BEZET)   ENDIF
  IFNOT(BD_S_5)   RESET (BD_S_5_BEZET)   ENDIF
  IFNOT(BD_S_RIJ) RESET (BD_S_RIJ_BEZET) ENDIF

DONE

/*                 * * * * * Automation hier staan algemene routines * * * * * *    */

/* Shows current locos running and direction on screen 2 */ 
STEALTH_GLOBAL(
  extern int cab_now;                   // gedefinieerd in myhall.cpp
  
  void updateLocoScreen() {
    byte row = 1;
    const byte maxRows = 3;
    
    // We onthouden de status van maximaal 2 locomotieven (voor rij 1 en rij 2 op het scherm)
    // We slaan op: [loco_address, target_speed_with_direction_bit]
    static int last_loco_id[3] = {0, 0, 0};
    static byte last_raw_speed[3] = {0, 0, 0};
    
    bool change_detected = false;
    
    // Eerste ronde: We lopen door de actieve locs om te controleren of er IETS veranderd is
    byte check_row = 0;
    for (auto loco = LocoSlot::getFirst(); loco && check_row < (maxRows - 1); loco = loco->getNext(), check_row++) {
      int current_loco = loco->getLoco();
      byte current_raw = loco->getTargetSpeed(); // Bevat zowel snelheid als de 0x80 richting-bit
      
      // Als de loc op deze positie is veranderd, OF zijn snelheid/richting is veranderd:
      if (last_loco_id[check_row] != current_loco || last_raw_speed[check_row] != current_raw) {
        change_detected = true;
        
        // Sla de nieuwe status direct op in ons geheugen
        last_loco_id[check_row] = current_loco;
        last_raw_speed[check_row] = current_raw;
      }
    }
    
    // Als er absoluut geen verandering is gedetecteerd, breken we hier direct af.
    // Geen LCD-output, dus ook geen terminal-ruis!
    if (!change_detected) {
      return;
    }
    
    // Tweede ronde: Er is een verandering gedetecteerd, dus we schrijven het scherm opnieuw
    for (auto loco = LocoSlot::getFirst(); loco && row < maxRows; loco = loco->getNext(), row++) {
      auto speed = loco->getTargetSpeed();
      auto direction = (speed & 0x80) ? 'V' : 'A';
      speed &= 0x7F;
      if (speed > 0) speed--;
      
      // Update het LCD scherm (nu met rostername en maximaal 8 characters)
      //StringFormatter::lcd2(1, row, F("Loco: %2d %3d %c"), loco->getLoco(), speed, direction);
      StringFormatter::lcd2(1, row, F("%s %3d %c"), 
        String(RMFT2::getRosterName(loco->getLoco())).substring(0, 8).c_str(), 
        speed, direction);      
    }
  }  
)

/* Shows status of pre-defined routes on screen 2, only on state change */
AUTOSTART SEQUENCE(40)
    STEALTH(
      // De route ID's staan in myAliases_stm32.h
      // 1. Vaste 'static' variabelen om de vorige status te onthouden tussen de loops door
      static bool last_state_1 = false;
      static bool last_state_2 = false;
      static bool last_state_3 = false;
      static bool last_state_4 = false;

      // 2. Haal de huidige status op (true = actief, false = inactief)
      bool current_state_1 = RMFT2::ifRouteState(ROUTE_1, 1);
      bool current_state_2 = RMFT2::ifRouteState(ROUTE_2, 1);
      bool current_state_3 = RMFT2::ifRouteState(ROUTE_3, 1);
      bool current_state_4 = RMFT2::ifRouteState(ROUTE_4, 1);

      // 3. Controleer of er iets is veranderd ten opzichte van de vorige meting
      if (current_state_1 != last_state_1 || 
          current_state_2 != last_state_2 || 
          current_state_3 != last_state_3 || 
          current_state_4 != last_state_4) {

          // Er is een verandering! Update het LCD scherm (en dus eenmalig de terminal)
          StringFormatter::lcd2(1, 0, F("Route 1:%1s 2:%1s 3:%1s 4:%1s"),
              current_state_1 ? F("*") : F("-"),
              current_state_2 ? F("*") : F("-"),
              current_state_3 ? F("*") : F("-"),
              current_state_4 ? F("*") : F("-")
          );

          // 4. Sla de nieuwe status op voor de volgende vergelijking
          last_state_1 = current_state_1;
          last_state_2 = current_state_2;
          last_state_3 = current_state_3;
          last_state_4 = current_state_4;
      }
    )
    DELAY(2500) // Wacht 5 seconden voor de volgende snelle check
FOLLOW(40)

HAL(UserAddin,updateLocoScreen,2000)


/*
  Timed events
*/ 
// Hour chimes
ONCLOCKTIME(25,0) // hh: 25 is ieder uur, mm: 0 is iedere 0 minuut
  SOUND_KERKKLOKKEN_DISTANT
  SOUND_KERKKLOKKEN_NEAR
DONE

ONCLOCKTIME(25,30) // hh: 25 is ieder uur, mm: 0 is iedere 0 minuut
  SOUND_KERKKLOKKEN_TING
DONE