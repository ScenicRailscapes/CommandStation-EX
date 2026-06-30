/* 
   This file contains automations for handling a reverse loop on the branch line in the model railway layout.
   It uses IR sensors to detect the train's position and activates or deactivates the reverse loop accordingly.
   It also includes button controls for track power and sound playback.
*/

/* 
  Wissel detectie mbt reverse loop branchlijn dorp
*/
ONTHROW(1007) // Branchlijn hoofdstation / Haven-dorp naar dorp
  CALL(KEERLUS_REVERSE) // set reverse loop when wissel to station is thrown
DONE
ONCLOSE(1007) // Branchlijn hoofdstation / Haven-dorp naar dorp
  CALL(KEERLUS_NORMAAL) // reset reverse loop when wissel to haven/yard is closed  
DONE  
ONTHROW(1034) // Yard dorp - dorp branchlijn naar dorp
  CALL(KEERLUS_NORMAAL) // set reverse loop when wissel to station is thrown
DONE
ONCLOSE(1034) // Yard dorp - dorp branchlijn naar dorp
  CALL(KEERLUS_REVERSE) // reset reverse loop when wissel to haven/yard is closed
DONE

/* 
  Uitleg: van west naar oost (richting haven/yard) is het signal reversed
  Van oost naar west (richting helix) is het signal normal
  Door de wissel aan de west zijde te schakelen naar station zal het signaal moeten omkeren. De wissel aan de oostzijde zal het signaal op normaal zetten.
  Bij passeren van west naar oost zal het signaal dus weer terug naar normaal gezet moeten worden. Dat wordt door de IR sensor detecties gedaan. 
*/

AUTOSTART SEQUENCE(BRANCH_DORP_KEERLUS) // Branchlijn dorp - reverse loop automation - richting helix
  IF(DORP_WEST_DETECT)            // West sensor gedetecteerd
    IF(REVERSE_SIGNAL_ACTIVE)     // Is het Signaal reversed?, zou moeten om in te kunnen rijden
      IFNOT(DORP_STATION_DETECT)  // Niet vanuit station komende trein?
        PRINT("West->Oost normaal signaal")
        DELAY(2000)               // wait a moment to allow train to fully enter the section
        CALL(KEERLUS_NORMAAL)     // Set naar normaal signaal om aan oostkant uit te rijden
      ENDIF
      RESET(DORP_WEST_DETECT)     // reset west detectie
      RESET(DORP_STATION_DETECT)  // reset station detectie (voor de zekerheid)
    ENDIF

    IFNOT(REVERSE_SIGNAL_ACTIVE)
      IF(DORP_STATION_DETECT)
        PRINT("Oost->West reverse signaal")
        CALL(KEERLUS_REVERSE) // set reverse signaal
      ENDIF
      RESET(DORP_WEST_DETECT)     // reset west detectie
      RESET(DORP_STATION_DETECT)  // reset station detectie
    ENDIF
  ENDIF  
FOLLOW(BRANCH_DORP_KEERLUS)  


/* The actual DCC signal reversal control sequence */
SEQUENCE(KEERLUS_REVERSE)        // Sequence to set reverse loop
  PRINT("Reversing DCC track signal")
  SET(REVERSE_SIGNAL_ACTIVE)     // set bitmap that reverse loop is active
  RESET(RELAIS_DCC_REVERSE_A)    // set reverse loop relais deel A
  RESET(RELAIS_DCC_REVERSE_B)    // set reverse loop relais deel B  
  BLINK(600,500,500)             // light the first led    
RETURN

SEQUENCE(KEERLUS_NORMAAL)        // Sequence to reset reverse loop
  PRINT("Normal DCC track signal")
  RESET(REVERSE_SIGNAL_ACTIVE)   // reset bitmap that reverse loop is active
  SET(RELAIS_DCC_REVERSE_A)      // reset reverse loop relais deel A
  SET(RELAIS_DCC_REVERSE_B)      // reset reverse loop relais deel B
  RESET(600)                     // light the first led
RETURN

// test om beetje visiueel te maken wat er gebeurt met de IR sensoren

ONSENSOR(DORP_WEST_DETECT)  // IR Sensor dorp west
  IF(DORP_WEST_DETECT)
    SET(601) // light second led
  ELSE
    RESET(601) // turn off second led
  ENDIF
DONE  
ONSENSOR(DORP_STATION_DETECT)  // IR Sensor dorp station
  IF(DORP_STATION_DETECT)
    SET(602) // light second led
  ELSE
    RESET(602) // turn off second led
  ENDIF
DONE
