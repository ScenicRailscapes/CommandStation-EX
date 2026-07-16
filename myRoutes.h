/* ====================================================================
                     AUTOMATISCHE RIJDEN ROUTES
   ==================================================================== */

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
                          AUTOMATISCHE RIT
   ==================================================================== */

AUTOMATION(1650, "AutoRoute: Start dal CCW")
    // 1. OPSTARTEN
    FWD(10)
    SET_LOCO_SPEED(30)         // Zet de gecorrigeerde start-snelheid
    DELAY(1000)
    FON(0)                     // Lichten aan (F0)
    FON(1)                     // Interne verlichting aan of sound aan (F1)
    LOCO_SOUND_BELL            // testje ********************
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
    PRINT("AutoRit: Gaan BD_D_4 verlaten. Wissels richting hoofdsporen")
    THROW(1038)   // S23 Haven / main #1
    THROW(1035)   // S20 Main #1 / schaduwstation
    RANDOM_FOLLOW(ROUTE_1,ROUTE_2, ROUTE_1)
    //RANDOM_CALL(ROUTE_1,ROUTE_2) // deze komen hier terug...
    //CALL(ROUTE_1)
    
  // Als we hier komen is de automatisering rit klaar
  SPEED(0)  // remmen
  DELAY(6000) // Geef remtijd
  PRINT ("Einde automation")
DONE  // nu even done, als ik ga werken met calls ipv follow dan iets anders verzinnen

/* ====================================================================
   ROUTE ROUTE_1 (Alias voor 1660): Hoofdspoor #1 (CCW) 
   ==================================================================== */
ROUTE(ROUTE_1,"Route #1 CCW Hoofdspoor #1")
  ROUTE_ACTIVE(ROUTE_1)
  ROUTE_CAPTION(ROUTE_1,"Active")
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
    RANDOM_FOLLOW(ROUTE_2,ROUTE_1, ROUTE_1, ROUTE_4)
  // Als we hier komen is de automatisering rit klaar
  SPEED(0)  // remmen
  DELAY(6000) // Geef remtijd
  PRINT ("Einde automation")
ROUTE_INACTIVE(ROUTE_1) 
ROUTE_CAPTION(ROUTE_1,"Stop")
RETURN

/* ====================================================================
   ROUTE ROUTE_2 (1661): Hoofdspoor #2 (CCW)
   ==================================================================== */
ROUTE(ROUTE_2,"Route #2 CCW Hoofdspoor #2")
  IFROUTE_ACTIVE(ROUTE_1) // Later controleren of er een andere automation rijdt
    ROUTE_INACTIVE(ROUTE_1)
    ROUTE_CAPTION(ROUTE_1,"Active")
  ENDIF  
  ROUTE_ACTIVE(ROUTE_2)
  ROUTE_CAPTION(ROUTE_2,"Active")
  PRINT("AutoRit: Route #2 CCW Hoofdspoor #2")
  // hmmm, moet ik hier eerst kijken waar de trein vandaan komt?, soms dus op verkeerde binnenkomst en dan is throw niet goed
  // 
  //IFCLOSED(1039) Test if turnout is closed
  THROW(1040)   // S25 main #1 / main #2
  // 4. Hoofdspoor #2 : SNELHEID VERLAGEN BIJ 1E IR DETECTOR
  //WAIT_WHILE_RED(102)
  // AT wacht tot de sensor actief (1) wordt

  // 2. Hoofdspoor #2 : BINNENKOMST HELIX (Blok BD_HBI_1)
  AT(IR_D_3_1_BEZET)
    PRINT("AutoRit: IR_D_3_1 berg geraakt")
    RESTORE_SPEED // terug naar de snelheid die we hadden opgeslagen
    PRINT("AutoRit: Verlaat Hoofdspoor #2, rijdt Helix Binnenring (BD_HBI_1) binnen")
  
    AFTER(BD_HBI_1_BEZET)  
  // 3a. Helix Berg sensor 
    AT(IR_D_3_2_BEZET)
      PRINT("AutoRit: IR_D_3_2 dal geraakt, snelheid naar 25")
      SAVE_SPEED
      SLOWDOWN(5)
    AT (IR_H_3_BEZET)
      PRINT("AutoRit: Helix binnenring")
    // 3b. Helix Midden sensor 
    AT(IR_H_2_BEZET)
      PRINT("AutoRit: Helix midden")
  // 3c. Helix Dal sensor 
  AFTER(IR_H_2_BEZET)
    PRINT("AutoRit: Helix verlaten")    

  // Keuzes maken: Nog een rondje of hoofdspoor #1    
      RANDOM_FOLLOW(ROUTE_1,ROUTE_2)
  // Als we hier komen is de automatisering rit klaar
  SPEED(0)  // remmen
  DELAY(6000) // Geef remtijd
  PRINT ("Einde automation")
  ROUTE_INACTIVE(ROUTE_2)  
  ROUTE_CAPTION(ROUTE_2,"Stop")     
DONE
    
    // Voor nu nog geen keuzes, vanuit dal naaar dorp - station - keerlus / dal - hoofdspoor 2 / dal - schaduwstation
    // schaduw station, keuzes doorrij track of trein wisselen.
    // Als ik keerlus heb gebruikt dan het probleem dat trein niet meer CCW kan rijden. In toekomst schaduwnstation gebruiken
    // en andere trein kiezen, dan handmatig trein omkeren en were in schaduw station plaatsen voor toekomstige CCW ritten    

  /* ====================================================================
  ROUTE ROUTE_3 (1662): Dorp - station (wachten) - haven dorp #1 (CCW) 
  ==================================================================== */

  // Deze moet herschreven worden, de keuze om route_3 te volgen moet eerder (in de helix) genomen worden anders
  // worden de wissels niet op tijd gezet.
SEQUENCE(ROUTE_3)
  IFROUTE_ACTIVE(ROUTE_1) 
    ROUTE_INACTIVE(ROUTE_1)
    ROUTE_CAPTION(ROUTE_1,"Active")
  ENDIF  
  ROUTE_ACTIVE(ROUTE_3)
  ROUTE_CAPTION(ROUTE_3,"Active")
  PRINT("AutoRit: Route #3 CW Dorp-Station-Haven")
  // hier iets maken als er 1 of twee rondes geweest zijn, een melding op scherm en parkeren op yard ofzo om loc om te keren
    THROW (1007) // S08 Branchlijn hoofdstation / Haven-dorp
    CLOSE (1037) // S22 Dorp -> Vissersdorp station"
    THROW (1034) // S19 Haven -> dorp 
    THROW (1039) // 
    CLOSE (1024) // S13 -> hoofdstation
  
  SPEED(0)  // remmen
  DELAY(6000) // Geef remtijd
  PRINT ("Einde automation")
  ROUTE_INACTIVE(ROUTE_3)
  ROUTE_CAPTION(ROUTE_3,"Stop")
DONE


// let op nu anderte routes inactief maken anders lijkt het op 2 routes 
  /* ====================================================================
  ROUTE ROUTE_4 (1663): Dorp - haven dorp - Station (wachten) (CCW) 
  ==================================================================== */
SEQUENCE(ROUTE_4)
  IFROUTE_ACTIVE(ROUTE_1) // Kan alleen hier komen vanuit route #1
    ROUTE_INACTIVE(ROUTE_1)
    ROUTE_CAPTION(ROUTE_1,"Active")
  ENDIF  
  ROUTE_ACTIVE(ROUTE_4)
  ROUTE_CAPTION(ROUTE_4,"Active")
  PRINT("AutoRit: Route #4 CCW Dorp-Haven-Station")
  // hier iets maken als er 1 of twee rondes geweest zijn, een melding op scherm en parkeren op yard ofzo om loc om te keren
  DELAY(4000)
  PRINT("AutoRit: wissels zetten voor keerlus naar station")
  CLOSE (1007) // S08 Branchlijn hoofdstation / Haven-dorp
  CLOSE (1037) // S22 Dorp -> Vissersdorp station"
  THROW (1039) // 
  THROW (1034) // S19 Haven -> dorp 
  CLOSE (1024) // S13 -> hoofdstation
  // 1. Dorpbranch CW: Hoofdstation nadert
  AT(IR_D_1_2_BEZET)
    PRINT("AutoRit: Station - wachten")
    SAVE_SPEED
    SPEED(0)  // Remmen
    FON(2)    // Horn/Whistle en later bij geen sound locs iets via de DFplayer  
    DELAYRANDOM(5000,10000) // Wachten tussen 5 en 10s
    LOCO_SOUND_BELL // Bell
    RESTORE_SPEED
  // 2. Dorpbranch CW: Helix buitenring naar berg
    // hier nog checks of de helix vrij is, later ook met seinen if_red enzo
  AT(IR_D_1_1_BEZET)
    PRINT("AutoRit: verlaten dorp, helix in")
  // 3. Helix berg nadert
  AT(IR_H_3_BEZET)
      PRINT("AutoRit: verlaten helix, parade hoofdspoor #1")
  AFTER(IR_D_2_1_BEZET)
      SAVE_SPEED
      SLOWDOWN(10)  // rustig naar beneden

      /* ***********************************************************/
      DELAY(10000)  // tijdelijk, nog de route afmaken geen zin meer
      /* ***********************************************************/

        // Let op: komen nu beneden aan dus wanneer je op blok 4 zit aan havendorp hoogte de 3-weg wissel omzetten voor de juiste keuze
      CALL(92) // tijdelijk, buitenring naar boven

      /* ***********************************************************/
      /*
        Wat gaan we doen, we rijden nu dus clockwise en zullen uiteindelijk moeten stoppen en (handmatig) de loc moeten keren.
        We kunnen nu nog een rondje rijden via station-dorp-helix
        of de lange route langs dorp (bv even wachten bij mini station haven-dorp) en dan helix weer in
        of naar dal
        of naar schaduwstation extra rondje
        of naar schaduwstation, parkeren en handover naar andere loc
        of naar yard dal / stoppen op spoor #1 of spoor #2, melding op scherm voor omkeren en dan terug naar route/automation 1650 ofzo voor alles opnieuw?
      */

  SPEED(0)  // remmen
  DELAY(6000) // Geef remtijd
  PRINT ("Einde automation")
  ROUTE_INACTIVE(ROUTE_4)  
    ROUTE_CAPTION(ROUTE_4,"Stop")
DONE