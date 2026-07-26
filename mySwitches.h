/* 
   Dit bestand bevat de (EXRAIL) setups voor de schakelaars, relais en track statusdisplay
   Ook de schakelaars van bv de TM1638 decoder en LED display worden hier geconfigureerd
*/
#include "myMacros.h"

/* TM1638 Button and LED module setup */
ONBUTTON(600)   // Reverse loop toggle switch
    IFNOT(REVERSE_SIGNAL_ACTIVE)
      LOOP_ENTRY_WEST             // Set naar normaal signaal om aan oostkant uit te rijden
      RESET(DORP_STATION_DETECT)  // reset station detectie
      RESET(DORP_WEST_DETECT)     // reset west detectie
    ELSE
      LOOP_ENTRY_EAST             // Set naar normaal signaal om aan oostkant uit te rijden
      RESET(DORP_STATION_DETECT)  // reset station detectie
      RESET(DORP_WEST_DETECT)     // reset west detectie      
    ENDIF
  DONE

ONBUTTON(604) // Testing, play some sounds
  BLINK(604,500,500)  // blink the second led
  SEG7(600,"Soun"_s7,4R) SEG7(604,"d"_s7,4R) // write Sound to the display (start Vpin 600, split over 2 segments
  PLAYSND(2,1,7,20)  // Set folder to 01 player 1, play 007 (Pass 3 Steam loco) 
  PLAYSND(0,1,3,18)  // Play 003 (Arrival Elec loco) 
  PLAYSND(1,1,3,18)  // Play 003 (Arrival Steam loco)
  DELAY(10000)
  RESET(604)
  CLEARSEG7(600)         // clear the display
  DONE

 ONBUTTON(606) //  Track power on/off MAIN A + MAIN B
  IFNOT(POWER_ON)
    SET_TRACK(A,MAIN)
    SET_TRACK(B,MAIN) 
    POWERON             // turn track power on
    SET(606)            // light the seventh led
    SEG7(600,"ON"_s7,4R) SEG7(604,"AB"_s7,4R) // write Track to the display (start Vpin 600, split over 2 segments
    SET(POWER_ON) // tijdelijk, uitzoeken hoe poweron status opgevraagd kan worden
  ELSE 
    POWEROFF                  // turn track power off
    RESET(606)                // off the seventh led
    CLEARSEG7(600)            // clear the display
    RESET(POWER_ON)
  ENDIF
  DONE 

ONBUTTON(607)
  SOUND_KERKKLOKKEN_1
DONE
  // hoe de status van power on/off uit te lezen?
// ONBUTTON(607) //  Track power on/off MAIN A
//   IFNOT(POWER_ON) 
//     POWERON                   // turn track power on
//     SET(607)                  // light the seventh led
//     SEG7(600,"ON"_s7,4R) SEG7(604,"A "_s7,4R) // write Track to the display (start Vpin 600, split over 2 segments
//     SET(POWER_ON)
//   ELSE
//     POWEROFF                  // turn track power off
//     RESET(607)                // off the seventh led
//     CLEARSEG7(600)            // clear the display
//     RESET(POWER_ON)
//   ENDIF
//   DONE


// ONBUTTON(602)
//   ASPECT(CROSSING_1,ADEM+FAST)   // fade slow
//   DELAY(5000)
//   ASPECT(CROSSING_1,KNIPPER+FAST)   // blink fast
//   AT(601) ASPECT(CROSSING_1,OFF) // stop
// DONE



