// Dit bestand bevat de setup en routines voor alles wat met Leds en lichten te maken heeft
// Eerst alle setups voor EXRAIL






// // Flashing LED sequence voor tracks leds
// AUTOSTART SEQUENCE(60)
//    // Afgesloten summertrack
//    IFTHROWN(TURN_SUMTRACK)
//      FADE(SIG_YARD, 50, 200)
//      FADE(SIG_SUMMER, 1500,200)   
//      DELAY(500)
//      FADE(SIG_YARD, 1500, 200)
//      FADE(SIG_SUMMER, 50,200)  
//      DELAY(400)
//    ENDIF
//    IF(AUTOROUTE_1)
//       IFCLOSED (TURN_BINBUITRING) // Binnenring
//         AMBER(513)    // buitenring led UIT
//         GREEN(515)  // binnenring LED
//         DELAY(300)
//         AMBER(515)  // niet bestaand dus uit
//         DELAY(200)
//       ELSE
//         AMBER(513)    // buitenring led UIT
//         RED(515)      // buitenring - station wissel AAN
//         DELAY(300)
//         AMBER(515)
//         DELAY(200)
//       ENDIF
//       IFCLOSED(TURN_YARD)       //  Yard/Station ring
//         AMBER(515)
//         GREEN(513)  // yard track led
//         DELAY(300)
//         AMBER(513)
//         DELAY(200)
//       ELSE
//         AMBER(515)
//         RED(513)    // buitenring led
//         DELAY(300)
//         AMBER(513)
//         DELAY(200)
//       ENDIF
//    ENDIF // if autoroute
//    IFNOT(AUTOROUTE_1)
//       IF(POWER_ON)
//         IFCLOSED (TURN_BINBUITRING)
//           GREEN(515)
//           AMBER(513)
//         ELSE
//           RED(515)
//           RED(513)
//         ENDIF // if closed
//         IFCLOSED(TURN_YARD)
//           GREEN(513)
//         ENDIF
//       ELSE // Poweroff
//         AMBER(513)
//         AMBER(515)
//       ENDIF // if poweron
//     ENDIF // ifnot autoroute   
// DELAY(100)
// FOLLOW(60)   
// DONE

// // Zwaailicht op kieper
// AUTOSTART SEQUENCE(62)
//    IF(KIEPER_OPERATING)
//      SET(ZWAAILICHT_KIEPER)     
//      DELAY(300)
//      RESET(ZWAAILICHT_KIEPER) 
//      DELAY(300)  
//      FOLLOW(62)
//    ELSE
//      DELAY(100)
//      FOLLOW(62)
//    ENDIF
// DONE

// AUTOSTART SEQUENCE(71)  // randomize timer voor straatlamp storing
//   DELAYRANDOM(60000,300000)
//   IF(STRAATLAMP_KNIPPER)
//     UNLATCH(STRAATLAMP_KNIPPER)
//   ELSE
//     LATCH(STRAATLAMP_KNIPPER)
//   ENDIF
// FOLLOW(71)


// // 1 straatlantaren laten flikkeren
// AUTOSTART SEQUENCE(70)
//   IF(STRAATLAMP_KNIPPER) 
//     FADE(STRAATLAMP_1, 100, 50)   DELAYRANDOM(200,800) // Use an Amber or Red LED
//     FADE(STRAATLAMP_1, 500, 30)   DELAYRANDOM(200,1000)
//     FADE(STRAATLAMP_1,  75, 75)   DELAYRANDOM(200,400)
//     FADE(STRAATLAMP_1, 750, 30)   DELAYRANDOM( 50,500)
//     FADE(STRAATLAMP_1,  75,100)   DELAYRANDOM(100,1500)
//     FADE(STRAATLAMP_1, 250,100)   DELAYRANDOM(100,600)
//     FADE(STRAATLAMP_1,  75, 75)   DELAYRANDOM(200,1000)
//     FADE(STRAATLAMP_1, 400, 30)   DELAYRANDOM( 50,600)
//     FADE(STRAATLAMP_1,  75,100)   DELAYRANDOM(200,1500)
//     FADE(STRAATLAMP_1, 1000,10)   DELAYRANDOM( 50,250)
//   ELSE
//     SET(STRAATLAMP_1)
//   ENDIF
//    FOLLOW(70)
// DONE   

// // Wissels en wissel signalen (rood/groen)
// ONCLOSE(TURN_BINBUITRING) 
//   IFCLOSED (TURN_BINBUITRING) // wacht tot echt om
//     GREEN(115)
//     PRINT("Trace: Binnen")
//     IFNOT(AUTOROUTE_1) LCD(5," ") ENDIF
//     IFNOT(AUTOROUTE_1) LCD(5, "Trace: Binnen") ENDIF
//   ENDIF  
// DONE

// ONTHROW(TURN_BINBUITRING)
//   IFTHROWN(TURN_BINBUITRING)
//     RED(115)
//     PRINT("Trace: Buiten")
//     IFNOT(AUTOROUTE_1) LCD(5," ") ENDIF
//     IFNOT(AUTOROUTE_1) LCD(5, "Trace: Buiten") ENDIF
//   ENDIF
// DONE

// // Yard / station wissel indication
// ONCLOSE(TURN_YARD) 
//   IFCLOSED (TURN_YARD) // wacht tot echt om
//     GREEN(113)
//     PRINT("Trace: Yard")
//     IFNOT(AUTOROUTE_1) LCD(5," ") ENDIF
//     IFNOT(AUTOROUTE_1) LCD(5, "Trace: Yard") ENDIF
//   ENDIF  
// DONE

// ONTHROW(TURN_YARD)
//   IFTHROWN(TURN_YARD)
//     RED(113)
//     PRINT("Trace: Station")
//     IFNOT(AUTOROUTE_1) LCD(5," ") ENDIF
//     IFNOT(AUTOROUTE_1) LCD(5, "Trace: Station") ENDIF
//   ENDIF
// DONE

// // Summertrack open/close warning
// ONCLOSE(TURN_SUMTRACK) 
//   IFCLOSED (TURN_SUMTRACK) // wacht tot echt om
//     RESET(SIG_SUMMER)
//     RESET(SIG_YARD)
//     PRINT("Summer trace open")
//     LCD(7," ")
//     LCD(7, "Summer trace open")
//     DELAY (5000)
//     LCD(7, " ")    
//   ENDIF  
// DONE

// ONTHROW(TURN_SUMTRACK)
//   IFTHROWN(TURN_SUMTRACK)
//     //SET(SIG_SUMMER)
//     PRINT("Summer trace closed")
//     LCD(7," ")
//     LCD(7, "Summer trace closed")
//     DELAY (5000)
//     LCD(7, " ")
//   ENDIF
// DONE

// ONTHROW(KIEPER)
//  SET(ZWAAILICHT_KIEPER)
//  LATCH(KIEPER_OPERATING)
// DONE

// ONCLOSE(KIEPER)
//  DELAY(5000)
//  RESET(ZWAAILICHT_KIEPER)
//  UNLATCH(KIEPER_OPERATING)
// DONE



// // Knipperlicht voetgangsovergang
// // Hier checken op CW of CCW, dit klopt met CW rijden, met CCW rijden of extra sensor maken of een timeout erop zetten
// AUTOSTART SEQUENCE(73)
// IF (TREIN_AANKOMST)   // Niet oversteken signaal
//    SET(OVERGANGSEIN)
//    DELAY(750)
//    RESET(OVERGANGSEIN)
//    DELAY(750)
//    FOLLOW(73)
// ELSE                  // Voorzichtig oversteken signaal
//    SET(OVERGANGSEIN)
//    DELAY(50)
//    RESET(OVERGANGSEIN)
//    //DELAY(200)
//    //SET(OVERGANGSEIN)
//    //DELAY(50)
//    //RESET(OVERGANGSEIN)
//    DELAY(3000)
//    FOLLOW(73)
// ENDIF

// // Fotograaf CCW (Normaal)
// AUTOSTART SEQUENCE(74)
// IF (CCW) // Tegen de klok in rijden
//   IF (IR2_BINRNG_1) // Baanvak dorp - brug
//     IF(AUTOROUTE_1) // Automatisch rijden is bezig
//       IF(STOOM_LOC_ACTIVE)
//         DELAY(17000)
//       ENDIF
//       IF(ELEC_LOC_ACTIVE)
//         DELAY(18000)
//       ENDIF
//     ELSE  // geen automatisch rijden
//       DELAY(15000) // nergens op gebaseerd ongeveer 10sec
//     ENDIF // if autoroute
//     CALL(76)        // Fotograaf neemt foto
//     DELAY(250)      // even wachten
//     CALL(76)        // en nog een foto
//   ENDIF // if IR
// ENDIF // if CCW
// FOLLOW(74)

// // Fotograaf CW 
// AUTOSTART SEQUENCE(75)
// IFNOT (CCW) // met de klok mee, dan kom je eerst door de tunnel
//   IF(IR4_BRUG)      // Baanvak tunnel - brug - dorp
//     DELAY(3600)
//     CALL(76)        // Fotograaf neemt foto
//     DELAY(250)      // even wachten
//     CALL(76)        // en nog een foto
//   ENDIF
// ENDIF  
// FOLLOW(75)

// // flitser simulatie 
// SEQUENCE(76)
//   SET(FLITSER)
//   DELAY(50)
//   RESET(FLITSER)
//   DELAY(100)
//   SET(FLITSER)
//   DELAY(50)
//   RESET(FLITSER)
//   DELAY(100)
//   SET(FLITSER)
//   DELAY(50)
//   RESET(FLITSER)
//   DELAY(250)
//   SET(FLITSER)
//   DELAY(300)
//   RESET(FLITSER)
//   DELAY(1500)   
// RETURN

// // Tardis sequences
// AUTOSTART SEQUENCE(77)
// IF(TARDIS_WACHT)
//   UNLATCH(TARDIS_AANKOMST)
//   SET(TARDIS)
//   DELAY(100)
//   RESET(TARDIS)
//   DELAY(2000)
// ENDIF  
// FOLLOW(77)

// AUTOSTART SEQUENCE(78)
// IF(TARDIS_AANKOMST)
//   UNLATCH(TARDIS_WACHT)
//   CALL(79)
//   DELAY(1000)
// ENDIF  
// FOLLOW(78)

// // Tardis aankomst LED
// SEQUENCE(79)
//   FADE(TARDIS, 50, 200)
//   FADE(TARDIS, 1500,200)   
//   DELAY(500)
//   FADE(TARDIS, 1500, 200)
//   FADE(TARDIS, 50,200)  
//   DELAY(500)
// RETURN


// /* OUD
// // Info lijn op OLED scherm. Erg omslachtig maar de LCD macro kan geen dynamische teksten ondersteunen grr
// AUTOSTART SEQUENCE(64)
//   IFNOT(AUTOROUTE_1)  // weet niet of dit werkt, geen idee of EXRail buiten een sequence de trein kan zien
//     IFLOCO(STOOM) LCD(7,"Steam") ENDIF
//     IFLOCO(ELEC) LCD(7,"Electric") ENDIF
//     STEALTH(
//         // CAB 4
//         int speed = DCC::speedTable[0].speedCode;
//         StringFormatter::lcd2(0,6,F("Loco:%d Speed:%2d %c"), DCC::speedTable[0].loco,speed & 0x7f, speed & 0x80 ? 'F' : 'R');
//         // CAB 5
//         speed = DCC::speedTable[1].speedCode;
//         StringFormatter::lcd2(0,7,F("Loco:%d Speed:%2d %c"), DCC::speedTable[1].loco,speed & 0x7f, speed & 0x80 ? 'F' : 'R');        
//     )
//   ENDIF
//   IF (AUTOROUTE_1) // wel autoroute
//     IF(STOOM_LOC_ACTIVE)
//       STEALTH(
//           int speed = DCC::speedTable[1].speedCode;
//           StringFormatter::lcd2(0,6,F("Loco:%d Speed:%2d %c"), DCC::speedTable[1].loco,speed & 0x7f, speed & 0x80 ? 'F' : 'R');        
//       )    
//       IF(WACHT) // stoppen bij station
//         IF(BINNEN_ROUTE)
//           LCD(7,"Route 1 Steam Stop")
//         ELSE
//           LCD(7,"Route 2 Steam Stop")
//         ENDIF
//       ELSE // passthrough station
//         IF(BINNEN_ROUTE)
//           LCD(7,"Route 1 Steam Pass")
//         ELSE
//           LCD(7,"Route 2 Steam Pass")
//         ENDIF
//       ENDIF
//     ENDIF // if stoom_loc
//     IF(ELEC_LOC_ACTIVE)
//       STEALTH(
//           int speed = DCC::speedTable[0].speedCode;
//           StringFormatter::lcd2(0,6,F("Loco:%d Speed:%2d %c"), DCC::speedTable[0].loco,speed & 0x7f, speed & 0x80 ? 'F' : 'R');   
//       )    
//       IF(WACHT) // stoppen bij station
//         IF(BINNEN_ROUTE)
//           LCD(7,"Route 1 Elec Stop")
//         ELSE
//           LCD(7,"Route 2 Elec Stop")
//         ENDIF
//       ELSE // passthrough station
//         IF(BINNEN_ROUTE)
//           LCD(7,"Route 1 Elec Pass")
//         ELSE
//           LCD(7,"Route 2 Elec Pass")
//         ENDIF
//       ENDIF  
//     ENDIF // if elec loc
//   ENDIF // autoroute
// DELAY (1000)
// FOLLOW(64)
// DONE
// */