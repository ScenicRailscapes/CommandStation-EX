// // * * * * * * * * * * * * * * EXRAIL Automation routes * * * * * * * * * * * * * *

// // Start met </ START CAB# 100>
// ROUTE(100,"Automatisch rijden volledige baan")
//   PRINT("Auto rijden")
//   LCD(4," ")
//   LCD(5," ")
//   LCD(6," ")
//   FWD(17)
//   LATCH(AUTOROUTE_1)
//   DELAY(500)
//   IFLOCO(STOOM) LATCH (STOOM_LOC_ACTIVE) ENDIF
//   IFLOCO(ELEC) LATCH(ELEC_LOC_ACTIVE) ENDIF
//   IFLOCO(DIESEL) LATCH (DIESEL_LOC_ACTIVE) ENDIF
//   CALL(155)       // Reset de DFPlayers
//   IF (CCW)        // CCW rijden     // moeten dit geen follow worden?, komt hier toch niet terug?
//     CALL(80)
//   ELSE
//     FOLLOW(85)    // CW rijden
//   ENDIF
// DONE


// // CW Automatic station Route sequence 
// // Bij CW route nog een gave 3e route mogelijk-> naar de Yard.. Rijden.. stop .. watervullen wanneer stoomloc.. terugrijden voorbij IR3, wissel om en verder
// SEQUENCE(85)
//   IF (STOOM_LOC_ACTIVE) SETLOCO(STOOM) ENDIF  // Lijkt af en toe de loco in de routine te verliezen
//   IF (ELEC_LOC_ACTIVE) SETLOCO(ELEC) ENDIF
//   IF (DIESEL_LOC_ACTIVE) SETLOCO(DIESEL) ENDIF
//   IFNOT(TREIN_AANKOMST)
//     DELAY(100)
//     //PRINT("LOOP")
//     FOLLOW (85)
//   ELSE
//   AT(IR1_STATION_1)       // Op het station
//     PRINT("Op IR Station")
//     IF(WACHT)
//       PRINT("Wachten")
//       LCD(4,"- - - -STOP - - - -")
//       STOP                // stop the train
//       CALL(153)           // stop the train sound
//       DELAYRANDOM(9000,20000) // delay somewhere between 5 and 20 seconds
//       LCD(4,"- - Vertrekken - -")
//       CALL(150)           // Departure sound
//       PRINT("Snel Optrekken")           
//       IF(STOOM_LOC_ACTIVE)
//         FWD(20)           // Gas erop door de tunnel   
//       ENDIF
//       IF(ELEC_LOC_ACTIVE)
//         FWD(30)           // Gas erop door de tunnel   
//       ENDIF
//       IF(DIESEL_LOC_ACTIVE)
//         FWD(15)           // Gas erop door de tunnel   
//       ENDIF        
//     ELSE  // doorrijden
//       PRINT("Snel doorrijden")
//       IF(STOOM_LOC_ACTIVE)
//         FWD(20)           // Gas erop door de tunnel   
//       ENDIF
//       IF(ELEC_LOC_ACTIVE)
//         FWD(30)           // Gas erop door de tunnel   
//       ENDIF
//       IF(DIESEL_LOC_ACTIVE)
//         FWD(15)           // Gas erop door de tunnel   
//       ENDIF                   
//     ENDIF
//     AFTER(IR1_STATION_1)
//       PRINT("Voorbij IR station")
//       UNLATCH(TREIN_AANKOMST)
//       CALL(86)            // Keuzes route en wacht of stop bij station       
//       DELAY(9000)
//       PRINT("Vertragen na station")
//       IF(STOOM_LOC_ACTIVE)
//         FWD(15) 
//       ENDIF
//       IF(ELEC_LOC_ACTIVE)
//         FWD(20)
//       ENDIF
//       IF(DIESEL_LOC_ACTIVE)
//         FWD(12)          
//       ENDIF               
// // staat deze goed of nog een indent ?
//   IF (AUTOROUTE_1)      // Do we still want to continue (latch Autoroute on)
//       PRINT("Nog een rondje")
//       DELAY(100)
//       LCD(4," ")
//       LCD(5," ")
//       FOLLOW (85)       // And again
//   ELSE
//       PRINT("Route gestopt")
//       LCD(4," ")
//       LCD(5," ")
//       LCD(6," ")
//       LCD(7," ")
//       // clean up latches, in use or not
//       UNLATCH(TREIN_AANKOMST)
//       UNLATCH(BINNEN_ROUTE)
//       UNLATCH(WACHT)
//       UNLATCH(STOOM_LOC_ACTIVE)
//       UNLATCH(ELEC_LOC_ACTIVE)
//       UNLATCH(DIESEL_LOC_ACTIVE)
//     ENDIF
//   ENDIF // IF treinaankomst
//   PRINT("Terug van seq 85")
//   IF(AUTOROUTE_1) PRINT("Autoroute nog aan") ENDIF
//   IF(TREIN_AANKOMST) PRINT("Trein aankomst nog aan") ENDIF          
// DONE //RETURN

// // Keuze sequence behorend bij seq 85 CW rijden
// SEQUENCE(86)
//   // Kies alvast een langszaam doorrij of stop bij station keuze. De Stoom met passagiers heeft 505 kans, de Elec goederen 30%
//   IF (STOOM_LOC_ACTIVE) SETLOCO(STOOM) ENDIF  // Lijkt af en toe de loco in de routine te verliezen
//   IF (ELEC_LOC_ACTIVE) SETLOCO(ELEC) ENDIF  
//   IF (DIESEL_LOC_ACTIVE) SETLOCO(DIESEL) ENDIF  
//   IFLOCO(STOOM)
//     PRINT("Stoom loco")
//     IFRANDOM(50)          // 50% kans
//       LATCH (WACHT)       // Wacht bij station latch
//     ELSE
//       UNLATCH(WACHT)      // niet wachten doorrijden
//     ENDIF
//   ENDIF
//   IFLOCO(ELEC)
//     PRINT("Elec loco")
//     IFRANDOM(30)          // 30% kans
//       LATCH (WACHT)       // Wacht bij station latch
//     ELSE
//       UNLATCH(WACHT)      // niet wachten doorrijden
//     ENDIF
//   ENDIF
//   IFLOCO(DIESEL)
//     PRINT("Diesel loco")
//     IFRANDOM(30)          // 30% kans
//       LATCH (WACHT)       // Wacht bij station latch
//     ELSE
//       UNLATCH(WACHT)      // niet wachten doorrijden
//     ENDIF
//   ENDIF  
// // welke route de volgende ronde? 1= Binnenbaan, 2= Buitenbaan, 3=Naar Yard/Groot rondje toekomst
//   PRINT("Even route kiezen")
//   IFRANDOM(60)            // 60% kans route 1
//     LATCH(BINNEN_ROUTE)
//     //LCD(5,"Binnen Route") 
//     CLOSE(TURN_STATION)
//     CLOSE(TURN_BINBUITRING)                 
//   ELSE                    // 40% kans route 2
//     UNLATCH(BINNEN_ROUTE)
//     //LCD(5,"Buiten Route") 
//     THROW(TURN_STATION)
//     THROW(TURN_BINBUITRING)
//     // Nog extra keuze, een route naar de Yard maken
//     // Op dit moment alleen als de YARD niet bezet is ()
//     IFNOT(YARD_BEZET)
//         IFRANDOM(40)     // 40% kans route 3
//           LATCH(YARD_ROUTE)
//           CLOSE(TURN_YARD)
//         ELSE
//           PRINT ("Niet naar de Yard")
//           UNLATCH(YARD_ROUTE)
//           THROW(TURN_YARD)
//         ENDIF // if random yard 
//     ENDIF // ifnot yard bezet
//   ENDIF // ifrandom 
// RETURN

// // - - - - - - - IR Sensor acties zoals baanvak reserveren, versnellen, vertragen, sounds wanneer CW gereden wordt - - - - - - -
// // CW Rijden; route en alle IR sensoren bekijken, baan reserveringen en autoroute acties bij sensors
// AUTOSTART SEQUENCE(51)
//   IFNOT (CCW)                               // Met klok mee, niet de standaard stand
//     IF(IR2_BINRNG_1)                        // komend vanuit dorp binnenring
//       LATCH(TREIN_AANKOMST)                 // Trein op baanvak binnenring - station          
//       IFNOT(AUTOROUTE_1) 
//         IFNOT(TREIN_AANKOMST)
//           LCD(4, "Binnenrijden Station")    // Display message on LCD/OLED
//           PRINT( "Binnenrijden Station") 
//         ENDIF
//       ELSE
//         IF(WACHT)
//           CALL(152)           // arrival sound 
//         ELSE
//           AFTER(IR2_BINRNG_1)           // veranderd om niet steeds de sound te herstarten, geen idee of dit blokking is)
//             CALL(151)           // Passthrough sound 
//         ENDIF // wacht        
//       ENDIF // ifnot autoroute  
//     ENDIF // binnenring
//     IF(IR3_BUIRNG_1)                        // komend vanuit buitenring
//       LATCH(TREIN_AANKOMST)
//       IFTHROWN(TURN_YARD)                   // wissel op baanvak buitenring - station?
//         IFNOT(AUTOROUTE_1) 
//           IFNOT(TREIN_AANKOMST)
//             LCD(4, "Binnenrijden Station")  // Display message on LCD/OLED
//             PRINT( "Binnenrijden Station") 
//           ENDIF
//         ELSE                                // Autoroute is bezig
//           IF(STOOM_LOC_ACTIVE)
//             SETLOCO(STOOM)
//             FWD(30)                         // sneller om door alle wissels te komen
//           ENDIF
//           IF(ELEC_LOC_ACTIVE)
//             SETLOCO(ELEC)
//             FWD(20)
//           ENDIF
//           IF(DIESEL_LOC_ACTIVE)
//             SETLOCO(DIESEL)
//             FWD(15)
//           ENDIF          
//           IF(WACHT)
//             DELAY(2000)
//             CALL(152)           // arrival sound 
//           ELSE
//             AFTER(IR3_BUIRNG_1)           // veranderd om niet steeds de sound te herstarten door trein met meerdere wagons, geen idee of dit blokking is)
//               DELAY(2000)
//               CALL(151)           // Passthrough sound 
//           ENDIF // wacht
//         ENDIF  // ifnot autoroute 
//       ENDIF // wissel naar station
//       IFCLOSED(TURN_YARD)       // Naar de Yard..
//         IFTHROWN(TURN_SUMTRACK) // controle op summertrack gesloten want anders (toekomst) doorrijden
//           CALL(53)   // Yard sequence summertrack gesloten
//         ENDIF // Summertrack
//       ENDIF // Wissel naar Yard 
//     ENDIF // buitenring
//     IF(IR1_STATION_1)
//       //DELAY(1000)
//       AFTER(IR1_STATION_1)
//         UNLATCH(TREIN_AANKOMST)    
//     ENDIF
//     IF(IR4_BRUG)
//       IF(AUTOROUTE_1)                       // Automatic route in progress
//       // helaas zijn commandos zoals IFLOCO en FWD/SPEED alleen in een actuele route te gebruiken hier dus een latch gebruiken
//         IF(STOOM_LOC_ACTIVE)
//           SETLOCO(STOOM)
//           DELAY(4000)                       // voorbij fotograaf
//           PRINT("Versnellen stoom")
//           FWD(30)                           // Speed up for decending track and turnout
//           IF (BINNEN_ROUTE)
//             DELAY(12000)
//           ELSE
//             DELAY(16000)
//           ENDIF
//           PRINT("Vertragen stoom")
//           FWD(15)                           // hopefully through the mountain and turnout so slowdown 
//         ENDIF
//         IF(ELEC_LOC_ACTIVE)
//           SETLOCO(ELEC)
//           PRINT("Versnellen elec")
//           FWD(30)
//           DELAY(5000)
//           FWD(35)                           // Speed up for decending track and turnout
//           DELAY(3500)
//           PRINT("Vertragen elec")
//           FWD(25)
//           DELAY(5000)
//           FWD(20)                           // hopefully through the mountain and turnout so slowdown 
//         ENDIF 
//         // voor de diesel niets nodig, die gaat wel  
//       ENDIF // if autoroute
//     ENDIF // if IR4
//   ENDIF // ifnot ccw
// FOLLOW(51)
// DONE


// SEQUENCE(53)  // Yard sequence summertrack gesloten
//   IF (STOOM_LOC_ACTIVE)  SETLOCO(STOOM)  ENDIF  // Lijkt af en toe de loco in de routine te verliezen
//   IF (ELEC_LOC_ACTIVE)   SETLOCO(ELEC)   ENDIF  
//   IF (DIESEL_LOC_ACTIVE) SETLOCO(DIESEL) ENDIF  
//   UNLATCH(IR5_YARD)         // Soms wordt de Latch niet gereleased
//   DELAY(3000)
//   IFLOCO(STOOM)
//     FWD(12)
//   ENDIF
//   IFLOCO(ELEC)
//     FWD(20)
//   ENDIF
//   IFLOCO(DIESEL)
//     FWD(10) // misschen nog met een FON(3) voor crawl snelheid?
//   ENDIF  
//   // Later nog eens kijken voor een Yard Bezet optie dan delay OF stoppen bij IR sensor
//   // IF (YARD_BEZET)
//   //      DELAY(iets)
//   //      enz..
//   //    ELSE
//   // Voorlopig maak ik een YARD_BEZET onderdeel van de random keuze voor trace 3.. Bezet = geen trace 3. 
//   // Mooier zou zijn dat trace 3 gebruikt wordt in de auto route als tijdelijke parkeer en dat de 2e trein dan verder kan gaan.. Toekomst
//   ATTIMEOUT(IR5_YARD,35000) // Eind bereikt, voor de zekerheid een timeout
//     STOP
//     DELAYRANDOM(20000,60000)
//     CALL(150)               // Voor nu een departure, later iets van stoomfluit ofzo
//     IFLOCO(STOOM)
//       REV(15)               // Ga terug
//     ENDIF
//     IFLOCO(ELEC)
//       REV(25)
//     ENDIF
//     IFLOCO(DIESEL)
//       REV(10)
//     ENDIF        
//     IFTHROWN(WATERKRAAN)
//       CLOSE(WATERKRAAN)
//     ENDIF
//     AFTER(IR3_BUIRNG_1)     // Voorbij de tunnel sensor
//       IFLOCO(DIESEL)        // Diesel is langszamer, duurt langer voorbij de sensor
//         DELAY(7000)
//       ELSE
//         DELAY(3000)
//       ENDIF
//       STOP
//       UNLATCH(IR5_YARD)
//       UNLATCH(YARD_BEZET)      
//       DELAY(5000)
//       THROW(TURN_YARD)      // Zet wissel om
//       FWD(20)               // hierna richting station waar de routes weer opnieuw bepaald worden
// RETURN