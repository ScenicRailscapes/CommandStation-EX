/* 
  This file contains (general) automation setups and automations itselfs
*/

// Include files, order is important
#include "myHal.h"
#include "myAliases_stm32.h"
#include "myMacros.h"
#include "myLedsandLights.h"
#include "myBlocksAndSignals.h"
#include "myReverseLoopAutomation.h"
#include "myRoutes.h"
#include "mySounds_stm32.h"
#include "mySwitches.h"
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
  LCD(3,"")
  PARSE("<C WIFI ON>")
  //PARSE("<C WIFI \"Nijlstroom_24\" \"52694646\">")
  //PARSE("<C WIFI HOSTNAME \"SilberBachTalBahn\">")
  PRINT("Alles goed zetten")
  UNLATCH(POWER_ON) // Unlatch power on
  DELAY(1000) // even wachten
  RESET(300, 16) // Reset I2C I/O #1 expander
  RESET(320, 16) // Reset I2C I/O #2 expander
  RESET(340, 16) // Reset I2C I/O #3 expander

  SET(455)  // Lichtenstein dorp leds aan
  SET(454)  // locoshed verlichting aan
  THROW(1023) // Wissel bergdorp naar binnenbaan

  SET_TRACK(A,MAIN)
  SET_TRACK(B,MAIN)
  POWERON
  HAL(TM1638, 600, TM1638_CLOCK, TM1638_STROBE, TM1638_DATA)  // Init de TM1683 LED/Key matrix hier ivm blokkeren init.
  DELAY(10000)
  GREEN(101)  // Sein BD_D_2 op groen zetten
  GREEN(102)  // Sein BD_D_3 op groen zetten
  GREEN(105)  // Sein BD_D_4 op groen zetten
  GREEN(108)  // Sein BD_D_5 op groen zetten
  ROUTE_HIDDEN(ROUTE_1)
  ROUTE_HIDDEN(ROUTE_2)
  ROUTE_HIDDEN(ROUTE_3)
  ROUTE_HIDDEN(ROUTE_4)
DONE

/*                 * * * * * Automation hier staan algemene routines * * * * * *    */

/* Shows current locos running and direction on screen 2 */
STEALTH_GLOBAL(
  extern int cab_now;                   // gedefinieerd in myhall.cpp buiten deze routine anders wordt deze iedere loop opnieuw gereset
  void updateLocoScreen() {

    byte row=1;
    const byte maxRows=3;
    for (auto loco=LocoSlot::getFirst();loco && row<maxRows;loco=loco->getNext(),row++) {
      auto speed = loco->getTargetSpeed();
      auto direction = (speed & 0x80) ? 'V' : 'A';
      speed &=0x7F;
      if (speed > 0) speed --;
      StringFormatter::lcd2(1, row, F("Loco: %2d %3d %c"), loco->getLoco(), speed, direction);
      cab_now = loco->getLoco();
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



// OLED Info Screen Sequence; Cabs, Track Power, sound On/Off en welke routes 
// LCD Macro kan alleen statische teksten, met stealth directe C++ code ingrijpend op de onderliggende DCC-EX code
// AUTOSTART SEQUENCE(10)
//   STEALTH(  // Vervang lijn 3, de Power status
//         extern int cab_now;                   // gedefinieerd in myhall.cpp buiten deze routine anders wordt deze iedere loop opnieuw gereset
//         bool sound = flags[255] & LATCH_FLAG; // 99 = Sound on/off latch in myAliases.h
//         bool elec  = flags[224] & LATCH_FLAG; // 65 = Manual select Elec train vanuit 3e systeem (ESPHome)           
//         bool steam = flags[225] & LATCH_FLAG; // 66 = Manual select Steam train vanuit 3e systeem (ESPHome)
//         bool dies  = flags[226] & LATCH_FLAG; // 67 = Manual select Dies 'BR290 DB' train vanuit 3e systeem (ESPHome)   
//         // bij meer treinen misschien de DCC nummers gebruiken in plaats van steam, elec en diesel        
//         bool main=TrackManager::getMainPower()==POWERMODE::ON;  // Status Main track power
//         bool prog=TrackManager::getProgPower()==POWERMODE::ON;  // Status Prog track power
//         bool dfplayer_busy= IODevice::read(10000);              // Status (* achter Snd) van DFPlayer #1
//         //bool dfplayer_busy= IODevice::read(10010);              // Status (* achter Snd) van DFPlayer #2
//         const char* const locname[]= {                         // CAB tabel
//           "DCC0", "DCC1", "DCC2", "DCC3", // DCC 0-3 (leeg)
//           "E32 ",                         // DCC 4 - E32 elec loc
//           "4800",                         // DCC 5 - 4800 steam loc
//           "290 "                          // DCC 6 - BR290 diesel loc
//         };
//         // Uitleg: Via directe calls wordt de status van de track power opgevraagd en de status van de sound latch (99). Met wat slimme test en replace wordt dit op 1 lijn geregeld
//         // Met ? en : wordt getest op een true of false, dus de bewering main == 1 wordt true of false. In true:false kan dan een replacement voor de bool gezet worden
//         StringFormatter::lcd2(0,2,F("%S %S%c Loc:%S"),main==true && prog ==false ?F("Main"): main==false && prog ==true ?F("Prog") : (main==true && prog ==true ?F("Join") : F("Off ") ), sound ?F("Snd") : F("   "), dfplayer_busy ? '*' : ' ',
//         elec==true && steam==false && dies==false ?F("E32-103"): elec==false && steam==true && dies==false ?F("4800") : elec==false && steam==false && dies==true ?F("BR190") : F("-"));         

//         for (int cab = 4; cab<=6; cab++){             // welke loc is aan het rijden? (loc DCC #4-6)  
//             if(DCC::getThrottleSpeed(cab) > 0){       // snelheid >0 ?
//               cab_now = cab;                          // sla deze extern op
//             }
//         }    
//         StringFormatter::lcd2(0,6,F("Loc:%4S Speed:%2d %S"), locname[cab_now], DCC::getThrottleSpeed(cab_now), DCC::getThrottleDirection(cab_now) ? F("Fw") : F("Rv") );                     
//         // Gelijk Latch 298 (Poweron status) zetten voor gebruik in EXRail
//         if (main) {
//           setFlag(254, LATCH_FLAG);  // latch 254 (Power_On = true)
//         } else{
//           setFlag(254,0,LATCH_FLAG); // Unlatch 254 (Power_on = false
//         }        
//     ) // end stealth

//   IF (AUTOROUTE_1) // autoroute info
//     STEALTH(  // Route bepalen en tonen
//       bool wacht = flags[212] & LATCH_FLAG;   // 52 = Wacht bij station latch
//       bool trace = flags[213] & LATCH_FLAG;   // 53 = Binnen of buitenroute latch
//       bool yard  = flags[214] & LATCH_FLAG;   // 54 = Yard route, dan moet BINNEN_ROUTE uit staan      
//       StringFormatter::lcd2(0,7,F("Trace:%S Station:%S"), trace==true && yard ==false ?F("1"): trace==false && yard ==false ?F("2") : (trace==false && yard ==true ?F("3") : F("??? ") ), wacht ==true ? F("Stop") : F("Pass") );
//     )
//   ENDIF // autoroute
// DELAY (500) // niet teveel updates naar LCD, de LCD heeft tijd nodig om scherm op te bouwen
// FOLLOW(10)
// DONE

// /*
//   Timed events
// */ 
// // Hour chimes
// ONCLOCKTIME(25,0) // hh: 25 is ieder uur, mm: 0 is iedere 0 minuut
//   PLAYSND(1,1,2,15) // Play sound (player 1, folder 1, track 2, volume 18) // chapel church bell
//   PLAYSND(2,1,5,11) // Play sound (player 2, folder 1, track 5, volume 12) // distant church bell
// DONE

// ONCLOCKTIME(25,30) // hh: 25 is ieder uur, mm: 0 is iedere 0 minuut
//   PLAYSND(1,1,3,15) // Play sound (player 1, folder 1, track 2, volume 18)
// DONE

