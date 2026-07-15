/* Tijdelijke code
      Temp voor visuele output identificatie Blockdetect
*/





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