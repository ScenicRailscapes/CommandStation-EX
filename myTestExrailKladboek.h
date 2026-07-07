/* Tijdelijke code
      Temp voor visuele output identificatie Blockdetect
*/

// Eind tijdelijke code
// Snelheidscompensatie macro (Gecorrigeerd zonder accolades)
#define SET_LOCO_SPEED(target_speed)                  \
    IFLOCO (13)                                       \
        IF(target_speed == 30)                        \
            SPEED(60)                                 \
        ENDIF                                         \
        IF(target_speed == 25)                        \
            SPEED(50)                                 \
        ENDIF                                         \
    ELSE                                              \
        SPEED(target_speed)                           \
    ENDIF

/* ====================================================================
   AUTOMATISCHE RIT: RONDE 1 (Volledig conform EX-RAIL Instructieset)
   ==================================================================== */

AUTOMATION(1650, "Route #1 CCW Start Rangeerterrein")
    // 1. OPSTARTEN
    SET_LOCO_SPEED(30)         // Zet de gecorrigeerde start-snelheid
    FON(0)                     // Lichten aan (F0)
    FON(1)                     // Interne verlichting aan (F1)
    PRINT("AutoRit: Gestart vanaf Rangeerterrein, richting BD_D_4")

    // 2. BENADEREN BLOK BD_D_4
    SAVE_SPEED
    WAIT_WHILE_RED(105) // Wacht tot het sein op groen staat (Blok BD_D_4 is bezet)
    RESTORE_SPEED 
    PRINT("AutoRit: Blok BD_D_4 binnengereden")

    // We wachten tot de trein duidelijk CW rijdt.
    AFTER(BD_D_4_CCW)

    // 3. WISSELS GOED ZETTEN NA VERLATEN BD_D_4
    PRINT("AutoRit: BD_D_4 verlaten. Wissels omzetten voor Hoofdspoor #1")
    THROW(1038)   // S23 Haven / main #1
    THROW(1035)   // S20 Main #1 / schaduwstation

    // 4. Keuze maken: Hoofdspoor #1 of Hoofdspoor #2
    RANDOM_FOLLOW(1660,1661)
    PRINT("AutoRit ERROR Returned from RANDOM_FOLLOW")
  DONE


/* ====================================================================
   ROUTE 1660: Hoofdspoor #1 (CCW) 
   ==================================================================== */
SEQUENCE(1660)
  PRINT("AutoRit: Route #1 CCW Hoofdspoor #1")
  CLOSE(1040)   // S25 main #1 / main #2
  // 4. Hoofdspoor #1 : SNELHEID VERLAGEN BIJ 1E IR DETECTOR
  //WAIT_WHILE_RED(102)
  // AT wacht tot de sensor actief (1) wordt
  AT(IR_D_2_2_BEZET)
  PRINT("AutoRit: IR_D_2_2 dal geraakt, snelheid naar 25")
  SAVE_SPEED
  SLOWDOWN(5)

  // 5. Hoofdspoor #1 : BINNENKOMST HELIX (Blok BD_HBI_1)
  AT(IR_D_2_1_BEZET)
    PRINT("AutoRit: IR_D_2_1 berg geraakt")
    RESET(BD_D_5_BEZET)   // tijdelijk tot IR sensor IR_D_1_5 geplaatst is...
    RESET(BD_D_5_CCW) 
    // Voor nu nog geen keuzes, later dorp - yard of dorp - station en keerlus
    // Wissels omzetten om de helix halverwege te verlaten richting het dorp
    THROW(1006)   // S06 Helix buitenring / dorp
    CLOSE(1007)   // S08 Branchlijn hoofdstation / Haven-dorp

  // 6. BINNENKOMST DORP (Blok BD_D_5)
  WAIT_WHILE_RED(108) // Wacht tot het sein op groen staat (Blok BD_D_5 is bezet)
  AT(BD_D_5_BEZET)
    PRINT("AutoRit: Blok BD_D_5 bereikt. Snelheid terug naar 30")
    RESTORE_SPEED // terug naar de snelheid die we hadden opgeslagen
    DELAY(5000)
    CLOSE(1006)   // S06 Helix buitenring / dorp
    PRINT("AutoRit: Wissel S06 omgezet naar Helix buitenring")
  
  // Keuzes maken: Nog een rondje of hoofdspoor #2  
    RANDOM_FOLLOW(1660,1661)
      PRINT("AutoRit ERROR Returned from RANDOM_FOLLOW")
DONE

/* ====================================================================
   ROUTE 1661: Hoofdspoor #2 (CCW)
   ==================================================================== */
SEQUENCE(1661)
  PRINT("AutoRit: Route #1 CCW Hoofdspoor #2")
  THROW(1040)   // S25 main #1 / main #2
  // 4. Hoofdspoor #2 : SNELHEID VERLAGEN BIJ 1E IR DETECTOR
  //WAIT_WHILE_RED(102)
  // AT wacht tot de sensor actief (1) wordt
  AT(IR_D_3_2_BEZET)
  PRINT("AutoRit: IR_D_3_2 dal geraakt, snelheid naar 25")
  SAVE_SPEED
  SLOWDOWN(5)
  PRINT("AutoRit: Hoofdspoor #2 bereikt, we geven Blok 5 handmatig vrij")
  RESET(BD_D_5_BEZET)   // tijdelijk tot IR sensor IR_D_1_5 geplaatst is...
  RESET(BD_D_5_CCW) 
  // 5. Hoofdspoor #2 : BINNENKOMST HELIX (Blok BD_HBI_1)
  AT(IR_D_3_1_BEZET)
    PRINT("AutoRit: IR_D_3_1 berg geraakt")
    RESTORE_SPEED // terug naar de snelheid die we hadden opgeslagen
    PRINT("AutoRit: Verlaat Hoofdspoor #2, rijdt Helix Binnenring (BD_HBI_1) binnen")
    AFTER(BD_HBI_1_BEZET)

  // 6. Terug in dal
      PRINT("AutoRit: Helix Binnenring is weer vrij")
  // Keuzes maken: Nog een rondje of hoofdspoor #1    
      RANDOM_FOLLOW(1660,1661)
      PRINT("AutoRit ERROR Returned from RANDOM_FOLLOW")
DONE
    
    // Voor nu nog geen keuzes, vanuit dal naaar dorp - station - keerlus / dal - hoofdspoor 2 / dal - schaduwstation
    // schaduw station, keuzes doorrij track of trein wisselen.
    // Als ik keerlus heb gebruikt dan het probleem dat tein niet meer CCW kan rijden. In toekomst schaduwnstation gebruiken
    // en andere trein kiezen, dan handmatig trein omkeren en were in schaduw station plaatsen voor toekomstige CCW ritten    



// /* ====================================================================
//    AUTOMATISCHE RIT: RONDE 1 (Volledig conform EX-RAIL Instructieset)
//    ==================================================================== */

// AUTOMATION(1650, "Hoofdspoor #1 CCW Start Rangeerterrein")
//     // 1. OPSTARTEN
//     SET_LOCO_SPEED(30)         // Zet de gecorrigeerde start-snelheid
//     FON(0)                     // Lichten aan (F0)
//     FON(1)                     // Interne verlichting aan (F1)
//     PRINT("AutoRit: Gestart vanaf Rangeerterrein, richting BD_D_4")

//     // 2. BENADEREN BLOK BD_D_4
//     SAVE_SPEED
//     WAIT_WHILE_RED(105) // Wacht tot het sein op groen staat (Blok BD_D_4 is bezet)
//     RESTORE_SPEED 
//     PRINT("AutoRit: Blok BD_D_4 binnengereden")

//     // We wachten tot de trein duidelijk CW rijdt.
//     AFTER(BD_D_4_CCW)

//     // 3. WISSELS GOED ZETTEN NA VERLATEN BD_D_4
//     PRINT("AutoRit: BD_D_4 verlaten. Wissels omzetten voor Hoofdspoor #1")
//     THROW(1038)   // S23 Haven / main #1
//     THROW(1035)   // S20 Main #1 / schaduwstation
//     CLOSE(1040)   // S25 main #1 / main #2 
    
//     // 4. Hoofdspoor #1 : SNELHEID VERLAGEN BIJ 1E IR DETECTOR
//     //WAIT_WHILE_RED(102)
//     // AT wacht tot de sensor actief (1) wordt
//     AT(IR_D_2_2_BEZET)
//     PRINT("AutoRit: IR_D_2_2 geraakt, snelheid naar 25")
//     SAVE_SPEED 
//     //SET_LOCO_SPEED(25)
//     SLOWDOWN(5) 

//     // 5. DOORRIJDEN NAAR HELIX BUITENRING
//     AT(IR_D_2_1_BEZET)
//     PRINT("AutoRit: Verlaat Hoofdspoor #1, rijdt Helix Buitenring (BD_HBU_1) binnen")

//     // Wissels omzetten om de helix halverwege te verlaten richting het dorp
//     THROW(1006)   // S06 Helix buitenring / dorp
//     CLOSE(1007)   // S08 Branchlijn hoofdstation / Haven-dorp

//     // 6. BINNENKOMST DORP (Blok BD_D_5)
//     WAIT_WHILE_RED(108) // Wacht tot het sein op groen staat (Blok BD_D_5 is bezet)
//     AT(BD_D_5_BEZET)
//     PRINT("AutoRit: Blok BD_D_5 bereikt. Snelheid terug naar 30")
//     //SET_LOCO_SPEED(30)
//     //SPEEDUP(5)
//     RESTORE_SPEED // terug naar de snelheid die we hadden opgeslagen

//     // Na 5 seconden wissel 1040 omzetten voor de volgende ronde naar Hoofdspoor #2
//     DELAY(5000)
//     CLOSE(1040)   // S25 main #1 / main #2
//     PRINT("AutoRit: Wissel S25 omgezet naar Hoofdspoor #2")

//     // BACK-UP LOGICA VOOR ONTBREKENDE EXIT-SENSOR BLOK 5:
//     // Wacht tot de stroom- of IR-melder van Hoofdspoor 2 aanspringt
//     AT(BD_D_3_BEZET)
    
//     PRINT("AutoRit: Hoofdspoor #2 bereikt, we geven Blok 5 handmatig vrij")
//     RESET(BD_D_5_BEZET) 
//     RESET(BD_D_5_CCW)   

//     // 7. HOOFDSPOOR #2 EN HELIX BINNENRING
//     PRINT("AutoRit: Rijden op Hoofdspoor #2 met snelheid 25")
//     //SET_LOCO_SPEED(25)
//     SLOWDOWN(5)

//     // We wachten tot de trein in de Helix binnenring (BD_HBI_1) wordt gedetecteerd
//     AT(BD_HBI_1_BEZET)
//     PRINT("AutoRit: Trein bevindt zich in Helix Binnenring (dalwaarts)")

//     // Wacht tot de Helix binnenring weer volledig vrij is (vlag wordt 0)
//     AFTER(BD_HBI_1_BEZET)

//     // 8. EINDE RONDE 1
//     PRINT("AutoRit: Einde Ronde 1. We staan weer voor Blok BD_D_4!")
// DONE

// // Test automation 1e poging
// // werkt niet goed, veel valse meldingen van bezet en vrije blockdetectors. Daar moet iets mee gedaan worden, misschien een soort debounce ofzo, of misschien is er een fout in de mapping van de blockdetectors waardoor er valse meldingen komen. Voor nu even testen met de automation zonder de bezetmeldingen van de blockdetectors, en later debuggen wat daar het probleem is.

// AUTOMATION(1650,"Hoofdspoor #1 CCW Start Rangeerterein")
//       FWD(30)
//       FON(0)
//       DELAY(1000)
//       FON(1)
//       // Ronde 1  (dal - main #1 - helix - dal)
//       PRINT ("Ronde 1: dal - main #1 - helix - dal")
//       IF(BD_D_4_BEZET) // Block #6 Connectie dorp en hoofdsporen naar yard en helix dal
//         PRINT("Auto 1650 - Bezet: dal naar visserdorp lijn")
//       ENDIF
//       AT (IR_D_4_1) // IR Sensor Connectie spoor #1 Dal
//             PRINT("Auto 1650 - Ronde 1: IR Sensor dal #1")
//             THROW(1038) // S23 Haven / main #1
//             PRINT ("Auto 1650 - Wissel 1038")
//             DELAY(1000)
//             THROW(1035) // S20 hoofdspoor 1 / schaduwstation
//             PRINT ("Auto 1650 - Wissel 1035")   
//             DELAY(1000)
//             CLOSE(1040) // S25 main #1 / main #2 kruiswissel
//             PRINT ("Auto 1650 - Wissel 1040")
//       IF(BD_D_2_BEZET) // Block #4 Hoofdspoor #1
//         PRINT("Auto 1650 - Bezet: hoofdspoor #1")
//       ENDIF
//       // de after misschien IN de block detection zetten?
//       AFTER(IR_D_2_2) // IR Sensor Hoofdspoor #1 Dorp
//         PRINT("Auto 1650 - Hoofdspoor #1 dorp sensor active")
//         FWD(25)       // Iets langzamer voor de paraderoute 

//         // hmm berg sensor reageert niet, fout? desnoods IR_H_3 gebruiken in de helix berg niveau
//       AFTER(IR_D_2_1) // IR Sensor Hoofdspoor #1 Berg
//         PRINT("Auto 1650 - Hoofdspoor #1 berg sensor active")
//         IF (BD_HBU_1_BEZET) // Block #2 Helix buitenring
//             PRINT("Auto 1650 - Bezet: helix buitenring")
//             THROW(1006) // S6 Helix buitenring - dal  (naar dorp)
//             PRINT("Auto 1650 - Wissel 1006")
//             CLOSE(1007) // S7 vissersdorp - dorp branchlijn (naar visserdorp)
//             PRINT("Auto 1650 - Wissel 1007")
//         ENDIF
//       // IFNOT (BD_HBU_1_BEZET)
//       //   PRINT("Auto 1650 - Helix verlaten")
//       // ENDIF
//               // dit is te vroeg, de ronde is nog niet klaar, pas bij uitgaan van de helix..
//       // Ronde 2 (dal - main #1 - helix - dorp)
//       PRINT ("Auto 1650 - Ronde 2: dal - main #1 - helix - dorp")
//       // IR Detectors buitenring voor positie van de trein in de helix, zodat er niet te vroeg of te laat versneld wordt
//       IF(BD_D_5_BEZET) // Block #13 yard vissersdorp /dorp branchlijn
//         PRINT("Auto 1650 - Bezet: yard vissersdorp /dorp branchlijn")
//         THROW(1038) // S23 Haven / main #1
//         PRINT ("Auto 1650 - Wissel 1038")
//         DELAY(1000)
//         CLOSE(1039) // S24 Haven - dorp / main #2
//         PRINT ("Auto 1650 - Wissel 1039")
//         DELAY(1000)
//         THROW(1040) // S25 main #1 / main #2 kruiswissel
//         PRINT ("Auto 1650 - Wissel 1040")
//         DELAY(1000)
//       ENDIF
//       AT(IR_D_2_2) // IR Sensor Hoofdspoor #1 Dorp
//         PRINT("Auto 1650 - Hoofdspoor #1 Dorp sensor active")
//         FWD(30)    // iets versnellen voor helling
//       AFTER(IR_D_2_2) // IR Sensor Hoofdspoor #1 Dorp
//         PRINT("Auto 1650 - Hoofdspoor #1 Berg sensor active")
//         FWD(25)       // Iets langzamer voor de paraderoute
//       AFTER(IR_D_2_1) // IR Sensor Hoofdspoor #1 Berg
//         PRINT("Auto 1650 - Hoofdspoor #1 berg sensor active")
//         IF (BD_HBU_1_BEZET) // Block #2 Helix buitenring
//             PRINT("Auto 1650 - Bezet: helix buitenring")
//             THROW(1006) // S6 Helix buitenring - dal  (naar dorp)
//             PRINT("Auto 1650 - Wissel 1006")
//             CLOSE(1007) // S7 vissersdorp - dorp branchlijn (naar visserdorp)
//             PRINT("Auto 1650 - Wissel 1007")
//         ENDIF        

//       // Hier zou ronde 3 moeten komen
//       DELAY(5000)    // temp omdat de automation nog niet af is en anders direct weer versneld in het begin van de automation wordt.
//       PRINT("Auto 1650 - Temp: herhaal automation")
//       // ...
//       // Ronde 3 (dorp - main #1 - helix - dorp - keerlus)
//       // komt later eerst dit testen
//       // later ook extras om te bepalen wat voor loc er rijdt, en bv met sound dan ook FON commandos voor geluiden etc. 
//       // Bij geen sound loc dan rijgeluiden via de dfplayers
// FOLLOW(1650)

// // Test voor distance sensor, led gaat knipperen afgaande op de afstand. Later gebruiken voor vertragen en stoppen van treinen
// AUTOSTART SEQUENCE(801)
//   ATLT(VL53L0X_STATION, 300 / 0.75)
//     BLINK(602,500,500)  // blink the second led
//   ATLT(VL53L0X_STATION, 250 / 0.75)
//     BLINK(602,300,300)  // blink the second led
//   ATLT(VL53L0X_STATION, 200 / 0.75)
//       BLINK(602,100,100)  // blink the second led
//   ATLT(VL53L0X_STATION, 150 / 0.75)
//       SET(602)
//   AFTER(VL53L0X_STATION) RESET(602)
//   // STEALTH(
//   //   StringFormatter::send(&USB_SERIAL,
//   //     F("Distance: %d\n|"), IODevice::readAnalogue(VL53L0X_STATION) );
//   // ) 
//   DELAY(100)  // small delay
// FOLLOW(801)


// Oke hier het probleem dat er waarschijnlijk geen mapping (bug) zit tussen de pin definities en namen (A10 hangt nergens aan)
// Als ik een digitale variant neem, het pin nummer van A10 = 29 bv dan krijg ik de fout dat deze niet geinitaliseerd (als analog) is.
// voor nu stopt het dus even
//IFGTE(29,500) ENDIF
//IFGTE(28,500) ENDIF
//IFGTE(13,500) ENDIF
//IFGTE(12,500) ENDIF

// misschien moet hier nog een autostart op
//AUTOSTART SEQUENCE(456)
//STEALTH(
//  StringFormatter::send(&USB_SERIAL,
//    F("Value of A10: %d, A9: %d, A8:  %d, A7: %d\n|"),
//    IODevice::readAnalogue(A10),
//    IODevice::readAnalogue(A9),
//    IODevice::readAnalogue(A8),
//    IODevice::readAnalogue(A7) );

//)
//DELAY(1000)
//FOLLOW(456)

/* Oud
    // STEALTH(
    //     // CAB 4 = E32 BR   // speed & 0x80 komt een 1 of 0 uit, 1=Forward 0= Reverse 
    //     int speed = DCC::speedTable[0].speedCode;
    //     // org code: StringFormatter::lcd2(0,6,F("Loco:%d Speed:%2d %c"), DCC::speedTable[0].loco,speed & 0x7f, speed & 0x80 ? 'F' : 'R');
    //     // Hieronder mooi de CAB 4 (nummer 0 in de tabel) vervangen door typenummer E32 (Elec loc duitse spoorwegen)
    //     StringFormatter::lcd2(0,6,F("Loc:%S Speed:%2d %c"), DCC::speedTable[0].loco == '4' ?F("----") : F("E32 "),speed & 0x7f, speed & 0x80 ? 'F' : 'R');
    //     // CAB 5 = 4600 Steam 
    //     speed = DCC::speedTable[1].speedCode;
    //     StringFormatter::lcd2(0,7,F("Loc:%S Speed:%2d %c"), DCC::speedTable[1].loco == '5' ?F("----") : F("4600"),speed & 0x7f, speed & 0x80 ? 'F' : 'R');
    // )
*/

        // temp
        //bool bezet=flags[51]& LATCH_FLAG;   // 51 = Yard bezet
        //bool ir5=flags[32] & LATCH_FLAG;
        //StringFormatter::lcd2(0,3,F("Bezet:%c IR:%c"), bezet ? '*' : '-', ir5 ? '*' : '-');         
  //)
  // IFNOT(AUTOROUTE_1)
  //   STEALTH(  // Status CABs, snelheid en richting
  //     const char* const locname[4]= { // CAB tabel (denk eraan dat DCC adres bij 4 begint)
  //       "E32 ",   // DCC 4 - E32 elec loc
  //       "4800",   // DCC 5 - 4800 steam loc
  //       "290 "    // DCC 6 - BR290 diesel loc
  //     };

  //     for (int cab = 4; cab<=6; cab++){             // welke loc is aan het rijden? (loc DCC #4-6)
  //         if(DCC::getThrottleSpeed(cab) > 0){       // snelheid >0 ?
  //           StringFormatter::lcd2(0,6,F("Loc:%4S Speed:%2d %S"), locname[cab-4], DCC::getThrottleSpeed(cab), DCC::getThrottleDirection(cab) ? F("Fw") : F("Rv") );
  //         }
  //     } 
  //   )
  //ENDIF
  // IF (AUTOROUTE_1) // wel autoroute
  //   STEALTH(
  //       bool steam=flags[60] & LATCH_FLAG;  // 60 = Stoom loc is actief in de route automation
  //       bool elec=flags[61] & LATCH_FLAG;   // 61 = Elec loc is actief in de route automation
  //       bool diesel=flags[62] & LATCH_FLAG; // 62 = Diesel loc is actief in de route automation
  //       int cab;
  //       String name;
  //       if (steam){ // zou ook met slimme logic op de StringFormatter kunnen maar dit leest makkelijker
  //         cab = 5; // Steamloco 4800
  //         name = "4800";
  //       }
  //       if (elec){
  //         cab = 4; // Elecloco E32
  //         name = "E32 ";          
  //       }
  //       if (diesel){
  //         cab = 6; // Dieselloco BR290
  //         name = "290 ";          
  //       }        
  //       StringFormatter::lcd2(0,6,F("Loc:%4S Speed:%2d %S"), name, DCC::getThrottleSpeed(cab), DCC::getThrottleDirection(cab) ? F("Fw") : F("Rv") );
  //   )
