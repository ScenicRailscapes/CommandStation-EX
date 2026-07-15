/* Tijdelijke code
      Temp voor visuele output identificatie Blockdetect
*/

// Snelheidscompensatie macro per loc
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

AUTOMATION(1650, "AutoRoute: Start dal CCW")
  IFROUTE_ACTIVE(1650) 
    ROUTE_INACTIVE(1650)
    ROUTE_CAPTION(1650,"Start")
  ELSE  
    ROUTE_ACTIVE(1650)
    ROUTE_CAPTION(1650,"Stop")
  ENDIF
    // 1. OPSTARTEN
    SET_LOCO_SPEED(30)         // Zet de gecorrigeerde start-snelheid
    FON(0)                     // Lichten aan (F0)
    FON(1)                     // Interne verlichting aan of sound aan (F1)
    PRINT("AutoRit: Gestart vanaf Rangeerterrein, richting BD_D_4")
    //LOCO_HANDOVER(cab_now, 1660)

    // 2. BENADEREN BLOK BD_D_4
    SAVE_SPEED
    IFRED(105) PRINT("Sein op rood, wacht")
    ELSE PRINT("Sein op groen, verder")
    ENDIF
    WAIT_WHILE_RED(105) // Wacht tot het sein op groen staat (Blok BD_D_4 is bezet)
    RESTORE_SPEED 
    PRINT("AutoRit: Blok BD_D_4 binnen rijden")

    // Als we CCW binnenkomen, dan keuze maken voor wissel. 
    AT (IR_D_4_1_BEZET)
      PRINT("Debug: IR 4 1 bezet")
      AFTER(IR_D_4_1_BEZET)
        PRINT("Debug: IR 4 1 voorbij")
        DELAY(3000)
        PRINT("Debug: IR 4 1 wacht voorbij")

    // 3. WISSELS GOED ZETTEN NA VERLATEN BD_D_4
    // Rit eerst over hoofdspoor #1, dan naar dorp
    PRINT("AutoRit: Gaan BD_D_4 verlaten. Wissels omzetten voor Hoofdspoor #1")
    THROW(1038)   // S23 Haven / main #1
    THROW(1035)   // S20 Main #1 / schaduwstation
    //RANDOM_FOLLOW(1660,1661)
    CALL(ROUTE_1)
    
  // Als we hier komen is de automatisering rit klaar
  SPEED(0)  // remmen
  DELAY(6000) // Geef remtijd
  PRINT ("Einde automation")
DONE  // nu even done, als ik ga werken met calls ipv follow dan iets anders verzinnen

/* ====================================================================
   ROUTE ROUTE_1 (Alias voor 1660): Hoofdspoor #1 (CCW) 
   ==================================================================== */
ROUTE(ROUTE_1,"Route #1 CCW Hoofdspoor #1")
  IFROUTE_ACTIVE(ROUTE_1) 
    ROUTE_INACTIVE(ROUTE_1)
    ROUTE_CAPTION(ROUTE_1,"Start")
  ELSE  
    ROUTE_ACTIVE(ROUTE_1)
    ROUTE_CAPTION(ROUTE_1,"Stop")
  ENDIF
  PRINT("AutoRit: Route #1 CCW Hoofdspoor #1")
  CLOSE(1040)   // S25 main #1 / main #2
  // 1. Hoofdspoor #1 : SNELHEID VERLAGEN BIJ 1E IR DETECTOR (nog niet geplaatst)
  //WAIT_WHILE_RED(102)

  // AT wacht tot de sensor actief (1) wordt
  AT(IR_D_2_2_BEZET)
  PRINT("AutoRit: IR_D_2_2 dal geraakt, snelheid naar 25")
  SAVE_SPEED
  SLOWDOWN(5)

  // 2. Hoofdspoor #1 : BINNENKOMST HELIX (Blok BD_HBI_1)
  AT(IR_D_2_1_BEZET)
    PRINT("AutoRit: IR_D_2_1 berg geraakt")
    // Voor nu nog geen keuzes, later dorp - yard of dorp - station en keerlus
    // Wissels omzetten om de helix halverwege te verlaten richting het dorp
    THROW(1006)   // S06 Helix buitenring / dorp
    CLOSE(1007)   // S08 Branchlijn hoofdstation / Haven-dorp
  // 3a. Helix Berg sensor 
  AT (IR_H_3_BEZET)
    PRINT("AutoRit: Helix buitenring")
  // 3b. Helix Midden sensor 
  AFTER(IR_H_2_BEZET)
    PRINT("AutoRit: Helix verlaten")
  // 4. BINNENKOMST DORP (Blok BD_D_5)
    SAVE_SPEED
    IFRED(108) PRINT("Sein op rood, wacht")
    ELSE PRINT("Sein op groen, verder")
    ENDIF
    WAIT_WHILE_RED(108) // Wacht tot het sein op groen staat (Blok BD_D_4 is bezet)
    RESTORE_SPEED       // terug naar de snelheid die we hadden opgeslagen 

  AT(BD_D_5_BEZET)
    PRINT("AutoRit: Blok BD_D_5 bereikt. Snelheid terug naar 30")
    DELAY(5000)
    CLOSE(1006)         // S06 Helix buitenring / dorp
    PRINT("AutoRit: Wissel S06 omgezet naar Helix buitenring")
  
  // Keuzes maken: Nog een rondje, of hoofdspoor #2 of via keerlus 
    //RANDOM_FOLLOW(1660,1661)
      //PRINT("AutoRit ERROR Returned from RANDOM_FOLLOW")
ROUTE_INACTIVE(ROUTE_1) 
RETURN



/* ====================================================================
   ROUTE 1660: Hoofdspoor #1 (CCW) 
   ==================================================================== */
/*   
ROUTE(ROUTE_1,"Route #1 CCW Hoofdspoor #1")
  ROUTE_ACTIVE(ROUTE_1)
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
    // Voor nu nog geen keuzes, later dorp - yard of dorp - station en keerlus
    // Wissels omzetten om de helix halverwege te verlaten richting het dorp
    THROW(1006)   // S06 Helix buitenring / dorp
    CLOSE(1007)   // S08 Branchlijn hoofdstation / Haven-dorp

  // 6. BINNENKOMST DORP (Blok BD_D_5)
  SAVE_SPEED
  IFRED(108) PRINT("Sein op rood, wacht")
  ELSE PRINT("Sein op groen, verder")
  ENDIF
  WAIT_WHILE_RED(108) // Wacht tot het sein op groen staat (Blok BD_D_4 is bezet)
  RESTORE_SPEED // terug naar de snelheid die we hadden opgeslagen 

  AT(BD_D_5_BEZET)
    PRINT("AutoRit: Blok BD_D_5 bereikt. Snelheid terug naar 30")
    DELAY(5000)
    CLOSE(1006)   // S06 Helix buitenring / dorp
    PRINT("AutoRit: Wissel S06 omgezet naar Helix buitenring")
  
  // Keuzes maken: Nog een rondje of hoofdspoor #2  
    RANDOM_FOLLOW(1660,1661)
      PRINT("AutoRit ERROR Returned from RANDOM_FOLLOW")
ROUTE_INACTIVE(ROUTE_1) 
DONE
*/

/* ====================================================================
   ROUTE ROUTE_2 (1661): Hoofdspoor #2 (CCW)
   ==================================================================== */
ROUTE(ROUTE_2,"Route #2 CCW Hoofdspoor #2")
  ROUTE_ACTIVE(ROUTE_2)
  PRINT("AutoRit: Route #2 CCW Hoofdspoor #2")
  // hmmm, moet ik hier eerst kijken waar de trein vandaan komt?, soms dus op verkeerde binnenkomst en dan is throw niet goed
  CLOSE(1040)   // S25 main #1 / main #2
  // 4. Hoofdspoor #2 : SNELHEID VERLAGEN BIJ 1E IR DETECTOR
  //WAIT_WHILE_RED(102)
  // AT wacht tot de sensor actief (1) wordt
  AT(IR_D_3_2_BEZET)
  PRINT("AutoRit: IR_D_3_2 dal geraakt, snelheid naar 25")
  SAVE_SPEED
  SLOWDOWN(5)
  //PRINT("AutoRit: Hoofdspoor #2 bereikt, we geven Blok 5 handmatig vrij")
  //RESET(BD_D_5_BEZET)   // tijdelijk tot IR sensor IR_D_1_5 geplaatst is...
  //RESET(BD_D_5_CCW) 
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
ROUTE_INACTIVE(ROUTE_2)       
DONE
    
    // Voor nu nog geen keuzes, vanuit dal naaar dorp - station - keerlus / dal - hoofdspoor 2 / dal - schaduwstation
    // schaduw station, keuzes doorrij track of trein wisselen.
    // Als ik keerlus heb gebruikt dan het probleem dat trein niet meer CCW kan rijden. In toekomst schaduwnstation gebruiken
    // en andere trein kiezen, dan handmatig trein omkeren en were in schaduw station plaatsen voor toekomstige CCW ritten    

  /* ====================================================================
  ROUTE ROUTE_3 (1662): Dorp - station (wachten) - haven dorp #1 (CCW) 
  ==================================================================== */
SEQUENCE(ROUTE_3)
  ROUTE_ACTIVE(ROUTE_3)
  PRINT("AutoRit: Route #3 CW Dorp-Station-Haven")
  // hier iets maken als er 1 of twee rondes geweest zijn, een melding op scherm en parkeren op yard ofzo om loc om te keren
ROUTE_INACTIVE(ROUTE_3)  
DONE

  /* ====================================================================
  ROUTE ROUTE_3 (1663): Dorp - haven dorp - Station (wachten) (CCW) 
  ==================================================================== */
SEQUENCE(ROUTE_4)
  ROUTE_ACTIVE(ROUTE_4)
  PRINT("AutoRit: Route #4 CCW Dorp-Haven-Station")
  // hier iets maken als er 1 of twee rondes geweest zijn, een melding op scherm en parkeren op yard ofzo om loc om te keren
ROUTE_INACTIVE(ROUTE_4)  
DONE


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