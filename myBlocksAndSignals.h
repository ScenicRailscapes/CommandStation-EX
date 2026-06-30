/*
  This file contains EXRAIL setup and automations for block and signal control
  Blocks are defined by block detectors using current sensors attached to an ESP32.
  The output from the blockdetection is fed into the DCC-EX controller via I2C I/O expander.
  IR sensors are used for detecting the direction and for stopping the train.
  Signals are defined by DCC Accessory decoders
  A VL53L0X distance sensor is defined here for very precise distance measurements to any object in front of the sensor
  Timed events such as hour chimes are also defined here
*/


/* 
  Block Aspects (signals) via DCC Accessory decoder
*/
DCCX_SIGNAL(100,0,2,1)  // Test: Aspect address 100, color 0 = Red, 2= Amber, 1 = Green. Can be called using RED(100), AMBER(100), GREEN(100)
DCCX_SIGNAL(101,0,2,1)  // Test: Aspect address 101, color 0 = Red, 2= Amber, 1 = Green. Can be called using RED(101), AMBER(101), GREEN(101)
DCCX_SIGNAL(102,0,2,1)  // Test: Aspect address 102, color 0 = Red, 2= Amber, 1 = Green. Can be called using RED(102), AMBER(102), GREEN(102)
//Entry aspects 
DCCX_SIGNAL(105,0,0,1)  // Test: Aspect address 105, color 0 = Red, no amber, 1 = Green. Can be called using RED(105), GREEN(105)
DCCX_SIGNAL(106,0,0,1)  // Test: Aspect address 106, color 0 = Red, no amber, 1 = Green. Can be called using RED(165), GREEN(106)
//Exit aspects
DCCX_SIGNAL(108,0,2,1)  // Test: Aspect address 108, color 0 = Red, 2= Amber, 1 = Green. It has a forth color, that is controlled using something different

/*
  Crossing signals via DCC Accesory decoder: (Alles boven de ADEM+5 of BLINK+5 is het aantal keer fade of blink)
  Example: ASPECT(CROSSING_1,ADEM+FAST)   // fade fast, ASPECT(CROSSING_1,KNIPPER+5)   // blink 5x
*/
// Alissen nog verplaatsen naar myAliases_stm32.h
ALIAS(CROSSING_1, 110)  // Crossing signals
ALIAS(CROSSING_2, 111)  // Crossing signals
ALIAS(ADEM, 10)  // Fade
ALIAS(KNIPPER,0) // Blink
ALIAS(SLOW, 1)   // Slow 
ALIAS(FAST, 2)   // Fast 
ALIAS(OFF, 0)    // Off

/* Block detection */
ONSENSOR(BD_HBI_1) // Block detect Helix binnenring
  IF(BD_HBI_1)
    PRINT("BD_HBI_1:Helix binnenring bezet")
    //RED(102)
    // en natuurlijk de reservering van het block
    SET(BD_HBI_1_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_HBI_1)
    PRINT("BD_HBI_1:Helix binnenring vrij")
    //GREEN(102)
    // en natuurlijk de unreservering van het block
    RESET(BD_HBI_1_BEZET) // flag dat het block vrij is
  ENDIF
DONE

ONSENSOR(BD_HBU_1) // Block detect Helix buitenring
  IF(BD_HBU_1)
    PRINT("BD_HBU_1:Helix buitenring bezet")
    //RED(103)
    // en natuurlijk de reservering van het block
    SET(BD_HBU_1_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_HBU_1)
    PRINT("BD_HBU_1:Helix buitenring vrij")
    //GREEN(103)
    // en natuurlijk de unreservering van het block
    RESET(BD_HBU_1_BEZET) // flag dat het block vrij is
  ENDIF
DONE

ONSENSOR(BD_S_1) // Block detect Station parkeerspoor #1
  IF(BD_S_1)
    PRINT("Parkeerspoor 1 bezet")
    //RED(104)
    // en natuurlijk de reservering van het block
    SET(BD_S_1_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_S_1)
    PRINT("Parkeerspoor 1 vrij")
    //GREEN(104)
    // en natuurlijk de unreservering van het block
    RESET(BD_S_1_BEZET) // flag dat het block vrij is
  ENDIF
DONE

ONSENSOR(BD_S_2) // Block detect Station parkeerspoor #2
  IF(BD_S_2)
    PRINT("Parkeerspoor 2 bezet")
    //RED(105)
    // en natuurlijk de reservering van het block
    SET(BD_S_2_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_S_2)
    PRINT("Parkeerspoor 2 vrij")
    //GREEN(105)
    // en natuurlijk de unreservering van het block
    RESET(BD_S_2_BEZET) // flag dat het block vrij is
  ENDIF
DONE

ONSENSOR(BD_S_3) // Block detect Station parkeerspoor #3
  IF(BD_S_3)
    PRINT("Parkeerspoor 3 bezet")
    //RED(106)
    // en natuurlijk de reservering van het block
    SET(BD_S_3_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_S_3)
    PRINT("Parkeerspoor 3 vrij")
    //GREEN(106)
    // en natuurlijk de unreservering van het block
    RESET(BD_S_3_BEZET) // flag dat het block vrij is
  ENDIF
DONE  

ONSENSOR(BD_S_4) // Block detect Station parkeerspoor #4
  IF(BD_S_4)
    PRINT("Parkeerspoor 4 bezet")
    //RED(107)
    // en natuurlijk de reservering van het block
    SET(BD_S_4_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_S_4)
    PRINT("Parkeerspoor 4 vrij")
    //GREEN(107)
    // en natuurlijk de unreservering van het block
    RESET(BD_S_4_BEZET) // flag dat het block vrij is
  ENDIF
DONE

ONSENSOR(BD_S_5) // Block detect Station parkeerspoor #5
  IF(BD_S_5)
    PRINT("Parkeerspoor 5 bezet")
    //RED(108)
    // en natuurlijk de reservering van het block
    SET(BD_S_5_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_S_5)
    PRINT("Parkeerspoor 5 vrij")
    //GREEN(108)
    // en natuurlijk de unreservering van het block
    RESET(BD_S_5_BEZET) // flag dat het block vrij is
  ENDIF
DONE

ONSENSOR(BD_S_RIJ) // Block detect Station doorrij spoor
  IF(BD_S_RIJ)
    PRINT("Doorrij spoor bezet")
    //RED(109)
    // en natuurlijk de reservering van het block
    SET(BD_S_RIJ_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_S_RIJ)
    PRINT("Doorrij spoor vrij")
    //GREEN(109)
    // en natuurlijk de unreservering van het block
    RESET(BD_S_RIJ_BEZET) // flag dat het block vrij is
  ENDIF
DONE

/* Block detection voor BD_D_1 met Bitmap Vpin 2002 */

ONSENSOR(BD_D_1)
  IF(BD_D_1)
    // DIRECT BEZET LOGICA
    SET(BD_D_1_BEZET) 
    RED(105)
    PRINT("BD_D_1: Branchlijn dorp bezet")
    
    // Start de bewakings-sequence (als deze nog niet liep)
    START(1900)
  ENDIF

SEQUENCE(1900)
  // We maken een loop die blijft draaien zolang er activiteit is
  // Door 'FOLLOW(1900)' springt de sequence aan het einde weer naar zijn eigen begin
  
  DELAY(3000) // Wacht 3 seconden
  
  IF(BD_D_1)
    // Als de sensor TIJDENS of aan het EINDE van de 3 seconden weer even bezet was,
    // dan starten we de 3 seconden gewoon direct opnieuw door de sequence te herhalen.
    FOLLOW(1900) 
  ENDIF
  
  IFNOT(BD_D_1)
    // Als de sensor na 3 seconden nog steeds onafgebroken vrij is:
    RESET(BD_D_1_BEZET) // Geef de bitmap vrij
    GREEN(105)          // Sein op groen
    PRINT("BD_D_1: Branchlijn dorp DEFINITIEF vrij")
    // De sequence stopt hier automatisch omdat we GEEN FOLLOW aanroepen
  ENDIF
DONE
  // Merk op: We doen nu HELEMAAL NIETS bij 'IFNOT(BD_D_1)' in de ONSENSOR!
  // De ONSENSOR reageert alleen op de binnenkomst. De sequence (102) regelt de uitgang.
DONE

/*
  Andere benadering?
  Een block heeft ook altijd een IR begin en IR eind.
  We kunnen het dus ook benaderen dat als een block bezet raakt, en een IR begin of IR eind sensor wordt geactiveerd, dat we dan de bezet status van het block veranderen. Dat is misschien wel een betere benadering, 
  omdat we dan ook de richting van de trein kunnen bepalen.
  Dus.. als een block bezet raakt en IR begin wordt geactiveerd, dan is de trein in de richting van IR eind aan het rijden. Als een block bezet raakt en IR eind wordt geactiveerd, dan is de trein in de richting van IR begin aan het rijden.

*/



// ONSENSOR(BD_D_1) // Block detect Branchlijn dorp - station
//   IF(BD_D_1)
//     PRINT("BD_D_1:Branchlijn dorp bezet")
//     RED(105)
//     // en natuurlijk de reservering van het block
//     SET(BD_D_1_BEZET) // flag dat het block bezet is
//   ENDIF
//   IFNOT(BD_D_1)
//     PRINT("BD_D_1:Branchlijn dorp vrij")
//     GREEN(105)
//     // en natuurlijk de unreservering van het block
//     RESET(BD_D_1_BEZET) // flag dat het block vrij is
//   ENDIF
// DONE

ONSENSOR(BD_D_2) // Block detect Hoofdspoor #1
  IF(BD_D_2)
    PRINT("BD_D_2:Hoofdspoor #1 bezet")
    //RED(106)
    // en natuurlijk de reservering van het block
    SET(BD_D_2_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_D_2)
    PRINT("BD_D_2:Hoofdspoor #1 vrij")
    //GREEN(106)
    // en natuurlijk de unreservering van het block
    RESET(BD_D_2_BEZET) // flag dat het block vrij is
  ENDIF
DONE

ONSENSOR(BD_D_3) // Block detect Hoofdspoor #2
  IF(BD_D_3)
    PRINT("BD_D_3:Hoofdspoor #2 bezet")
    //RED(107)
    // en natuurlijk de reservering van het block
    SET(BD_D_3_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_D_3)
    PRINT("BD_D_3:Hoofdspoor #2 vrij")
    //GREEN(107)
    // en natuurlijk de unreservering van het block
    RESET(BD_D_3_BEZET) // flag dat het block vrij is
  ENDIF
DONE

ONSENSOR(BD_D_4) // Block detect Connectie dorp en hoofdsporen naar yard en helix dal 
  IF(BD_D_4)
    PRINT("BD_D_4:Connectie dorp en hoofdsporen naar yard en helix dal bezet")
    //RED(108)
    // en natuurlijk de reservering van het block
    SET(BD_D_4_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_D_4)
    PRINT("BD_D_4:Connectie dorp en hoofdsporen naar yard en helix dal vrij")
    //GREEN(108)
    // en natuurlijk de unreservering van het block
    RESET(BD_D_4_BEZET) // flag dat het block vrij is
  ENDIF
DONE

ONSENSOR(BD_D_5) // Block detect Branchlijn yard - dorp
  IF(BD_D_5)
    PRINT("BD_D_5:Branchlijn yard - dorp bezet")
    AMBER(101)      // hier nog iets dat als dorp d4 richting de d5 rijdt, het signaal op rood gaat
    // en natuurlijk de reservering van het block
    SET(BD_D_5_BEZET) // flag dat het block bezet is
  ENDIF
  IFNOT(BD_D_5)
    PRINT("BD_D_5:Branchlijn yard - dorp vrij")
    GREEN(101)
    // en natuurlijk de unreservering van het block
    RESET(BD_D_5_BEZET) // flag dat het block vrij is
  ENDIF
DONE

/* IR Detection */

// IR Detectie sensoren 
ONSENSOR(IR_H_1)  // IR Sensor Helix dal niveau
  IF(IR_H_1)
    PRINT("Helix dal niveau sensor active")
  ENDIF
  IFNOT(IR_H_1)
    PRINT("Helix dal niveau sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_H_2)  // IR Sensor Helix midden niveau
  IF(IR_H_2)
    PRINT("Helix midden niveau sensor active")
  ENDIF
  IFNOT(IR_H_2)
    PRINT("Helix midden niveau sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_H_3)  // IR Sensor Helix berg niveau
  IF(IR_H_3)
    PRINT("Helix berg niveau sensor active")
  ENDIF
  IFNOT(IR_H_3)
    PRINT("Helix berg niveau sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_S_1) // IR Stop sensor parkeerspoor #1
  IF(IR_S_1)
    PRINT("Parkeerspoor 1 stop sensor active")
  ENDIF
  IFNOT(IR_S_1)
    PRINT("Parkeerspoor 1 stop sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_S_2) // IR Stop sensor parkeerspoor #2
  IF(IR_S_2)
    PRINT("Parkeerspoor 2 stop sensor active")
  ENDIF
  IFNOT(IR_S_2)
    PRINT("Parkeerspoor 2 stop sensor inactive")
  ENDIF
DONE  

ONSENSOR(IR_S_3) // IR Stop sensor parkeerspoor #3
  IF(IR_S_3)
    PRINT("Parkeerspoor 3 stop sensor active")
  ENDIF
  IFNOT(IR_S_3)
    PRINT("Parkeerspoor 3 stop sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_S_4) // IR Stop sensor parkeerspoor #4
  IF(IR_S_4)
    PRINT("Parkeerspoor 4 stop sensor active")
  ENDIF
  IFNOT(IR_S_4)
    PRINT("Parkeerspoor 4 stop sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_S_5) // IR Stop sensor parkeerspoor #5
  IF(IR_S_5)
    PRINT("Parkeerspoor 5 stop sensor active")
  ENDIF
  IFNOT(IR_S_5)
    PRINT("Parkeerspoor 5 stop sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_S_RIJ) // IR Stop sensor doorrij spoor
  IF(IR_S_RIJ)
    PRINT("Doorrij spoor stop sensor active")
  ENDIF
  IFNOT(IR_S_RIJ)
    PRINT("Doorrij spoor stop sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_D_4_1) // IR Sensor Connectie spoor #1 Dal
  IF(IR_D_4_1)
    PRINT("IR_D_4_1:Connectie spoor #1 Dal sensor active")
  ENDIF
  IFNOT(IR_D_4_1)
    PRINT("IR_D_4_1:Connectie spoor #1 Dal sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_D_4_2) // IR Sensor Connectie spoor #1 Dorp
  IF(IR_D_4_2)
    PRINT("IR_D_4_2:Connectie spoor #1 Dorp sensor active")
  ENDIF 
  IFNOT(IR_D_4_2)
    PRINT("IR_D_4_2:Connectie spoor #1 Dorp sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_D_2_2) // IR Sensor Hoofdspoor #1 Dorp
  IF(IR_D_2_2)
    PRINT("IR_D_2_2:Hoofdspoor #1 Dorp sensor active")
  ENDIF
  IFNOT(IR_D_2_2)
    PRINT("IR_D_2_2:Hoofdspoor #1 Dorp sensor inactive") 
  ENDIF
DONE

ONSENSOR(IR_D_2_1) // IR Sensor Hoofdspoor #1 Berg
  IF(IR_D_2_1)
    PRINT("IR_D_2_1:Hoofdspoor #1 Berg sensor active")
  ENDIF
  IFNOT(IR_D_2_1)
    PRINT("IR_D_2_1:Hoofdspoor #1 Berg sensor inactive")
  ENDIF
DONE  

ONSENSOR(IR_D_3_1) // IR Sensor Hoofdspoor #2 Berg
  IF(IR_D_3_1)
    PRINT("IR_D_3_1:Hoofdspoor #2 Berg sensor active")
  ENDIF
  IFNOT(IR_D_3_1)
    PRINT("IR_D_3_1:Hoofdspoor #2 Berg sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_D_3_2) // IR Sensor Hoofdspoor #2 Dorp
  IF(IR_D_3_2)
    PRINT("IR_D_3_2:Hoofdspoor #2 Dorp sensor active")
  ENDIF
  IFNOT(IR_D_3_2)
    PRINT("IR_D_3_2:Hoofdspoor #2 Dorp sensor inactive")
  ENDIF
DONE

ONSENSOR(IR_D_1_3) // IR Sensor hoofdspoor dorp - haven
  IF(IR_D_1_3)
    PRINT("IR_D_1_3:Hoofdspoor dorp - haven sensor active")
  ENDIF
  IFNOT(IR_D_1_3)
    PRINT("IR_D_1_3:Hoofdspoor dorp - haven sensor inactive")
  ENDIF
DONE  

ONSENSOR(IR_D_1_4) // IR Sensor Haven - dorp hoofdspoor
  IF(IR_D_1_4)
    PRINT("IR_D_1_4:Haven - dorp hoofdspoor sensor active")
  ENDIF
  IFNOT(IR_D_1_4)
    PRINT("IR_D_1_4:Haven - dorp hoofdspoor sensor inactive")
  ENDIF
DONE 

  IF(IR_S_1)
    PRINT("Parkeerspoor 1 stop sensor active")
  ENDIF
  IFNOT(IR_S_1)
    PRINT("Parkeerspoor 1 stop sensor inactive")
  ENDIF
DONE

// Automations
// Branchlijn dorp - reverse loop automation
ONSENSOR(IR_D_1_1) // IR Sensor Dorp branchlijn west (berg)
  IF(IR_D_1_1)
    PRINT("IR_D_1_1:Dorp west sensor active")
    AT(IR_D_1_1) 
      SET(DORP_WEST_DETECT)
  ENDIF
DONE

ONSENSOR(IR_D_1_2) // IR Sensor Dorp branchlijn station
  IF(IR_D_1_2)
    PRINT("IR_D_1_2:Dorp station sensor active")
    AT(IR_D_1_2)
      SET(DORP_STATION_DETECT)
  ENDIF
DONE
