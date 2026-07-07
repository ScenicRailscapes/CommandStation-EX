/* 
  This file contains (general) automation setups and automations itselfs
*/

// /*
//   ** Macros en defines.. order is belangrijk, deze moeten voor de includes staan
// */
// // macro voor de DF_Players
// #define PLAYSND(player, folder, track, volume) \
//     PLAY_FOLDER(player+10000,folder) \
//     PLAY_TRACK(player+10000,track,volume)  // Play track  / 

//     // macro voor de 7-segment display 
// #define CLEARSEG7(firstVpin) \
//   SEG7(firstVpin,0,4R) \
//   SEG7(firstVpin+4,0,4R)

// Include files, order is important
#include "myHal.h"
#include "myAliases_stm32.h"
#include "myMacros.h"
#include "myLedsandLights.h"
#include "myBlocksAndSignals.h"
#include "myReverseLoopAutomation.h"
//#include "myRoutes_stm32.h"
//#include "myRoutes_CCW_stm32.h"
#include "mySounds_stm32.h"
#include "mySwitches.h"
#include "myServosAndMotors.h"
#include "myTestExrailKladboek.h"

AUTOSTART

DELAY(1000)
DONE  // Done met auto start

// Even dingen goed zetten
AUTOSTART SEQUENCE(1) 
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
  DELAY(10000)
  GREEN(101)  // Sein BD_D_2 op groen zetten
  GREEN(102)  // Sein BD_D_3 op groen zetten
  GREEN(105)  // Sein BD_D_4 op groen zetten
  GREEN(108)  // Sein BD_D_5 op groen zetten
DONE

/*                 * * * * * Automation hier staan algemene routines * * * * * *    */

// Stealth code voor het tonen van de loconamen op de LCD
STEALTH_GLOBAL(
  void myFilter(Print * stream, byte & opcode, byte & paramCount, int16_t p[]) {
    (void)stream;
    // use command <U locoId> to display name from roster
    if (opcode == 'U' && paramCount == 1) {
      auto locoId=p[0];
      auto name=RMFT2::getRosterName(locoId);
      if (!name) return; // caller will <X> this
      opcode=0; // caller can now ignore this
      StringFormatter::lcd2(7, 0, F("Loco %d %S"), locoId, name);
    }
  }
)
// Update logo screen every 500ms with the current loco speeds
// HAL(UserAddin,updateLocoScreen,500)
// HAL(HALDisplay<OLED>, 2, 0x3d, 128, 64)

// STEALTH_GLOBAL(
//   void updateLocoScreen() {
//     const byte loco_slots=8;
//     static byte current_slot=loco_slots-1;
//     static byte shown_speed[loco_slots]; // remember what's already shown
//     static bool first_call=true;

//     if (first_call) {
//       first_call=false;
//       for (int i=0; i<loco_slots; i++) shown_speed[i]=127;
//     }

//     // switch to next row
//     current_slot= (current_slot + 1) % loco_slots;
//     loco=DCC::speedTable[current_slot].loco;
//     if (loco<0) return; // this slot is no longetr used
//     if (loco==0) return; // we are beyond the last loco

//     speed = DCC::speedTable[current_slot].speedCode;
//     if (speed== shown_speed[current_slot]) return; // no change in speed
//     shown_speed[current_slot] = speed; // remember speed for next time

//     auto direction = (speed & 0x80) ? 'F' : 'R';
//     speed = speed & 0x7f;
//     if (speed > 0) speed = speed - 1; // make it look like JMRI
//     StringFormatter::lcd2(2, current_slot+2, F("Loco:%4d %3d %c"), loco, speed, direction);
//   }
// )

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

