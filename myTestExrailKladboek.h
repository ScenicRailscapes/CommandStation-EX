/* Tijdelijke code
      Temp voor visuele output identificatie Blockdetect
*/

// Eind tijdelijke code


// Test automation 1e poging
// werkt niet goed, veel valse meldingen van bezet en vrije blockdetectors. Daar moet iets mee gedaan worden, misschien een soort debounce ofzo, of misschien is er een fout in de mapping van de blockdetectors waardoor er valse meldingen komen. Voor nu even testen met de automation zonder de bezetmeldingen van de blockdetectors, en later debuggen wat daar het probleem is.

AUTOMATION(1650,"Hoofdspoor #1 CCW Start Rangeerterein")
      FWD(30)
      FON(0)
      DELAY(1000)
      FON(1)
      // Ronde 1  (dal - main #1 - helix - dal)
      PRINT ("Ronde 1: dal - main #1 - helix - dal")
      IF(BD_D_4_BEZET) // Block #6 Connectie dorp en hoofdsporen naar yard en helix dal
        PRINT("Auto 1650 - Bezet: dal naar visserdorp lijn")
      ENDIF
      AT (IR_D_4_1) // IR Sensor Connectie spoor #1 Dal
            PRINT("Auto 1650 - Ronde 1: IR Sensor dal #1")
            THROW(1038) // S23 Haven / main #1
            PRINT ("Auto 1650 - Wissel 1038")
            DELAY(1000)
            THROW(1035) // S20 hoofdspoor 1 / schaduwstation
            PRINT ("Auto 1650 - Wissel 1035")   
            DELAY(1000)
            CLOSE(1040) // S25 main #1 / main #2 kruiswissel
            PRINT ("Auto 1650 - Wissel 1040")
      IF(BD_D_2_BEZET) // Block #4 Hoofdspoor #1
        PRINT("Auto 1650 - Bezet: hoofdspoor #1")
      ENDIF
      // de after misschien IN de block detection zetten?
      AFTER(IR_D_2_2) // IR Sensor Hoofdspoor #1 Dorp
        PRINT("Auto 1650 - Hoofdspoor #1 dorp sensor active")
        FWD(25)       // Iets langzamer voor de paraderoute 

        // hmm berg sensor reageert niet, fout? desnoods IR_H_3 gebruiken in de helix berg niveau
      AFTER(IR_D_2_1) // IR Sensor Hoofdspoor #1 Berg
        PRINT("Auto 1650 - Hoofdspoor #1 berg sensor active")
        IF (BD_HBU_1_BEZET) // Block #2 Helix buitenring
            PRINT("Auto 1650 - Bezet: helix buitenring")
            THROW(1006) // S6 Helix buitenring - dal  (naar dorp)
            PRINT("Auto 1650 - Wissel 1006")
            CLOSE(1007) // S7 vissersdorp - dorp branchlijn (naar visserdorp)
            PRINT("Auto 1650 - Wissel 1007")
        ENDIF
      // IFNOT (BD_HBU_1_BEZET)
      //   PRINT("Auto 1650 - Helix verlaten")
      // ENDIF
              // dit is te vroeg, de ronde is nog niet klaar, pas bij uitgaan van de helix..
      // Ronde 2 (dal - main #1 - helix - dorp)
      PRINT ("Auto 1650 - Ronde 2: dal - main #1 - helix - dorp")
      // IR Detectors buitenring voor positie van de trein in de helix, zodat er niet te vroeg of te laat versneld wordt
      IF(BD_D_5_BEZET) // Block #13 yard vissersdorp /dorp branchlijn
        PRINT("Auto 1650 - Bezet: yard vissersdorp /dorp branchlijn")
        THROW(1038) // S23 Haven / main #1
        PRINT ("Auto 1650 - Wissel 1038")
        DELAY(1000)
        CLOSE(1039) // S24 Haven - dorp / main #2
        PRINT ("Auto 1650 - Wissel 1039")
        DELAY(1000)
        THROW(1040) // S25 main #1 / main #2 kruiswissel
        PRINT ("Auto 1650 - Wissel 1040")
        DELAY(1000)
      ENDIF
      AT(IR_D_2_2) // IR Sensor Hoofdspoor #1 Dorp
        PRINT("Auto 1650 - Hoofdspoor #1 Dorp sensor active")
        FWD(30)    // iets versnellen voor helling
      AFTER(IR_D_2_2) // IR Sensor Hoofdspoor #1 Dorp
        PRINT("Auto 1650 - Hoofdspoor #1 Berg sensor active")
        FWD(25)       // Iets langzamer voor de paraderoute
      AFTER(IR_D_2_1) // IR Sensor Hoofdspoor #1 Berg
        PRINT("Auto 1650 - Hoofdspoor #1 berg sensor active")
        IF (BD_HBU_1_BEZET) // Block #2 Helix buitenring
            PRINT("Auto 1650 - Bezet: helix buitenring")
            THROW(1006) // S6 Helix buitenring - dal  (naar dorp)
            PRINT("Auto 1650 - Wissel 1006")
            CLOSE(1007) // S7 vissersdorp - dorp branchlijn (naar visserdorp)
            PRINT("Auto 1650 - Wissel 1007")
        ENDIF        

      // Hier zou ronde 3 moeten komen
      DELAY(5000)    // temp omdat de automation nog niet af is en anders direct weer versneld in het begin van de automation wordt.
      PRINT("Auto 1650 - Temp: herhaal automation")
      // ...
      // Ronde 3 (dorp - main #1 - helix - dorp - keerlus)
      // komt later eerst dit testen
      // later ook extras om te bepalen wat voor loc er rijdt, en bv met sound dan ook FON commandos voor geluiden etc. 
      // Bij geen sound loc dan rijgeluiden via de dfplayers
FOLLOW(1650)

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
