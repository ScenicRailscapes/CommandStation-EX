// /* 
//    This file contains automations for handling a reverse loop on the branch line in the model railway layout.
//    It uses IR sensors to detect the train's position and activates or deactivates the reverse loop accordingly.
//    It also includes button controls for track power and sound playback.
// */
#include "myMacros.h"
/* 
  Uitleg: van west naar oost (richting haven/yard) is het signal reversed
  Van oost naar west (richting helix) is het signal normal
  Door de wissel aan de west zijde te schakelen naar station zal het signaal moeten omkeren. De wissel aan de oostzijde zal het signaal op normaal zetten.
  Bij passeren van west naar oost zal het signaal dus weer terug naar normaal gezet moeten worden. Dat wordt door de IR sensor detecties gedaan. 
*/
/* 
  Wissel detectie mbt reverse loop branchlijn dorp
*/

ONTHROW(1007) // Branchlijn hoofdstation / Haven-dorp naar dorp
  LOOP_ENTRY_WEST // set reverse loop when wissel to station is thrown
DONE
ONCLOSE(1007) // Branchlijn hoofdstation / Haven-dorp naar dorp
  LOOP_ENTRY_EAST // reset reverse loop when wissel to haven/yard is closed  
DONE  
ONTHROW(1034) // Yard dorp - dorp branchlijn naar dorp
  LOOP_ENTRY_WEST // set reverse loop when wissel to station is thrown
DONE
ONCLOSE(1034) // Yard dorp - dorp branchlijn naar dorp
  LOOP_ENTRY_EAST // reset reverse loop when wissel to haven/yard is closed
DONE

// // test om beetje visiueel te maken wat er gebeurt met de IR sensoren

// ONSENSOR(DORP_WEST_DETECT)  // IR Sensor dorp west
//   IF(DORP_WEST_DETECT)
//     SET(601) // light second led
//   ELSE
//     RESET(601) // turn off second led
//   ENDIF
// DONE  
// ONSENSOR(DORP_STATION_DETECT)  // IR Sensor dorp station
//   IF(DORP_STATION_DETECT)
//     SET(602) // light second led
//   ELSE
//     RESET(602) // turn off second led
//   ENDIF
// DONE
