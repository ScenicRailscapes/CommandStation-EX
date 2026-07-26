/* ====================================================================
                     AUTOMATISCHE RIJDEN ROUTES
   ==================================================================== */

// Snelheidscompensatie macro op basis van procentuele schaling per loc
#define SET_LOCO_SPEED(target_speed)                  \
    SPEED(target_speed)                               \
    IFLOCO(13) /* V60 */                              \
        SPEED_REL(200) /* 200% van snelheid */        \
    ENDIF                                             \
    IFLOCO(15) /* kittel steam tram */                \
        SPEED_REL(90)  /* 80% van snelheid */         \
    ENDIF                                             \
    IFLOCO(6)                                         \
        SPEED_REL(90) /* 80% van snelheid */          \
    ENDIF   

/* ====================================================================
                          AUTOMATISCHE RIT
   ==================================================================== */

AUTOMATION(1650, "AutoRoute: Start dal CCW")
    // 1. OPSTARTEN
    FON(0)                     // Lichten aan (F0)
    FON(1)                     // Interne verlichting aan of sound aan (F1)
    LOCO_SPECIAL_STARTUP       // Zet wat speciale functies aan
    SOUND_BELL                 // Vertrek
    DELAY(3000)
    SOUND_OPTREKKEN            // Optrekken
    DELAY(3000)
    SET_LOCO_SPEED(10)         // Zet de gecorrigeerde start-snelheid
    DELAY(3500)
    SET_LOCO_SPEED(30)         // Zet de gecorrigeerde start-snelheid
    PRINT("AutoRit: Gestart vanaf Rangeerterrein, richting BD_D_4")

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
        SET(BD_D_4_UITRIT)

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
  // Waar komen we vandaan?, BD_D_4 of BD_D_5
  IFTHROWN(1038) CLOSE(1038) ENDIF
  IFTHROWN(1039) CLOSE(1039) ENDIF
  // Kruisen van Hoofdspoor #2 naar #1
  THROW(1040)   // S25 main #1 / main #2
  // 1. Hoofdspoor #1 : SNELHEID VERLAGEN BIJ 1E IR DETECTOR (nog niet geplaatst)
  //WAIT_WHILE_RED(102) // Is er nu nog niet als sein

  // 1. Rijden Hoofdspoor #1 op
  AT(IR_D_2_2_BEZET)
    PRINT("AutoRit: IR_D_2_2 dal geraakt, snelheid naar 25")
    SAVE_SPEED
    SLOWDOWN(5)

  // 2. Hoofdspoor #1 : BINNENKOMST HELIX (Blok BD_HBI_1)
  AT(IR_D_2_1_BEZET)
    PRINT("AutoRit: IR_D_2_1 berg geraakt")
    // Wissels omzetten om de helix halverwege te verlaten richting het dorp
    SOUND_RIJDEN
    THROW(1006)   // S06 Helix buitenring / dorp
    CLOSE(1007)   // S08 Branchlijn hoofdstation / Haven-dorp
    RESTORE_SPEED
    DELAYRANDOM(3000, 6000)    // Even wachten voor Whistle/Horn
    SOUND_HORN   // Whistle / horn voor binnenrijden

  // 3a. Helix Berg sensor
  AT (IR_H_3_BEZET)
    PRINT("AutoRit: Helix buitenring")

  // 3b. Helix Midden sensor 
  AT(IR_H_2_BEZET)
    PRINT("AutoRit: Helix verlaten")
    DELAYRANDOM(2000, 5000)    // Even wachten voor Whistle/Horn
    SOUND_HORN_LONG // Whistle / horn voor verlaten

  // 4. BINNENKOMST DORP (Blok BD_D_5)
    SAVE_SPEED
    IFRED(108) PRINT("Sein op rood, wacht")
    ELSE PRINT("Sein op groen, verder")
    ENDIF
    WAIT_WHILE_RED(108) // Wacht tot het sein op groen staat (Blok BD_D_4 is bezet)
    RESTORE_SPEED       // terug naar de snelheid die we hadden opgeslagen 

  // 5. Rijden nu op dorp branchlijn 
  AT(BD_D_5_BEZET)
    PRINT("AutoRit: Blok BD_D_5 bereikt. Snelheid terug naar 30")
    DELAY(5000)
    SOUND_RIJDEN        // Rijgeluiden 
    CLOSE(1006)         // S06 Helix buitenring / dorp
    SET(BD_D_5_UITRIT)  // flag dat we op de BD_D_5 rijden
    PRINT("AutoRit: Wissel S06 omgezet naar Helix buitenring")
  
  // 6. Keuzes maken: Nog een rondje, of hoofdspoor #2 of via keerlus 
    RANDOM_FOLLOW(ROUTE_2,ROUTE_1, ROUTE_1, ROUTE_4)

  // Als we hier komen is de automatisering rit klaar
  SPEED(0)  // remmen
  DELAY(6000) // Geef remtijd
  PRINT ("Einde automation")
ROUTE_INACTIVE(ROUTE_1) 
ROUTE_CAPTION(ROUTE_1,"Niet actief")
RETURN

/* ====================================================================
   ROUTE ROUTE_2 (1661): Hoofdspoor #2 (CCW)
   ==================================================================== */
ROUTE(ROUTE_2,"Route #2 CCW Hoofdspoor #2")
  IFROUTE_ACTIVE(ROUTE_1)       // Later controleren of er een andere automation rijdt
    ROUTE_INACTIVE(ROUTE_1)     // Zet route #1 in-active voor op het scherm
    ROUTE_CAPTION(ROUTE_1,"Niet actief")
  ENDIF  
  ROUTE_ACTIVE(ROUTE_2)
  ROUTE_CAPTION(ROUTE_2,"Active")
  PRINT("AutoRit: Route #2 CCW Hoofdspoor #2")
  IFCLOSED(1038) THROW(1038) ENDIF
  IFCLOSED(1035) THROW(1035) ENDIF
  // Eventueel vanuit de BD_D_5 komende 
  IF(BD_D_5_UITRIT)
    IFTHROWN(1039) CLOSE(1039) ENDIF
    CLOSE(1040)
  ELSE
    THROW(1040)   // S25 main #1 / main #2
  ENDIF
  // 4. Hoofdspoor #2 : SNELHEID VERLAGEN BIJ 1E IR DETECTOR
  //WAIT_WHILE_RED(102)
  // AT wacht tot de sensor actief (1) wordt

// 1. Rijden Hoofdspoor #2 op
  AT(IR_D_3_2_BEZET)
  PRINT("AutoRit: IR_D_3_2 dal geraakt, snelheid naar 25")
  SAVE_SPEED
  SLOWDOWN(5)

  // 2a. Helix Berg sensor 
  AT(IR_D_3_1_BEZET)
    PRINT("AutoRit: IR_D_3_1 berg geraakt")
    RESTORE_SPEED // terug naar de snelheid die we hadden opgeslagen
    SOUND_RIJDEN
    PRINT("AutoRit: Verlaat Hoofdspoor #2, rijdt Helix Binnenring (BD_HBI_1) binnen")
    DELAYRANDOM(3000, 6000)    // Even wachten voor Whistle/Horn
    SOUND_HORN // Whistle / horn voor binnenrijden

  AT(BD_HBI_1_BEZET)
    PRINT("AutoRit: Rijden in helix")
  AT (IR_H_3_BEZET)
    PRINT("AutoRit: Helix binnenring")
  // 3b. Helix Midden sensor 
  AT(IR_H_2_BEZET)
    PRINT("AutoRit: Helix midden")
    SOUND_HORN_LONG // Whistle / horn voor in de berg
  // 3c. Helix Dal sensor 
  AT(IR_H_1_BEZET)
    PRINT("AutoRit: Helix verlaten")
    DELAYRANDOM(3000, 6000)    // Even wachten voor Whistle/Horn
    SOUND_HORN // Whistle / horn voor verlaten

    // 4. Keuzes maken: Nog een rondje of hoofdspoor #1    
    RANDOM_FOLLOW(ROUTE_1,ROUTE_2)

  // Als we hier komen is de automatisering rit klaar
  SPEED(0)  // remmen
  DELAY(6000) // Geef remtijd
  PRINT ("Einde automation")
  ROUTE_INACTIVE(ROUTE_2)  
  ROUTE_CAPTION(ROUTE_2,"Niet actief")     
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
ROUTE(ROUTE_3,"Dorp - station")
  IFROUTE_ACTIVE(ROUTE_1)       // Kan alleen hier komen vanuit route #1
    ROUTE_INACTIVE(ROUTE_1)     // Zet route #1 in-active voor op het scherm
    ROUTE_CAPTION(ROUTE_1,"Niet actief")
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
  ROUTE_CAPTION(ROUTE_3,"Niet actief")
DONE


// let op nu anderte routes inactief maken anders lijkt het op 2 routes 
  /* ====================================================================
  ROUTE ROUTE_4 (1663): Dorp - haven dorp - Station (wachten) (CCW) 
  ==================================================================== */
ROUTE(ROUTE_4,"Dorp - haven dorp - Station")
  IFROUTE_ACTIVE(ROUTE_1)       // Kan alleen hier komen vanuit route #1
    ROUTE_INACTIVE(ROUTE_1)     // Zet route #1 in-active voor op het scherm
    ROUTE_CAPTION(ROUTE_1,"Niet actief")
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
    SPEED_REL(50)
    SOUND_AFREMMEN
    DELAY(5000) // uitrijden // maak dit snelheid afhankelijk
    PRINT("AutoRit: Station - wachten")
    SAVE_SPEED
    SPEED(0)      // Remmen
    SOUND_HORN    
    DELAYRANDOM(10000,20000)  // Wachten tussen 5 en 10s
    SOUND_CONDUCTOR_WHISTLE_1 // Vertrek instappen
    DELAY(2000)
    SOUND_BELL                // Bell
    DELAY(2000)
    SOUND_OPTREKKEN           // Optrekken
    SPEED(15)
    DELAY(2500)    
    SPEED(30)
  // 2. Dorpbranch CW: Helix buitenring naar berg
    // hier nog checks of de helix vrij is, later ook met seinen if_red enzo
  AT(IR_D_1_1_BEZET)
    PRINT("AutoRit: verlaten dorp, helix in")
  // 3. Helix berg nadert
  AT(IR_H_3_BEZET)
      PRINT("AutoRit: verlaten helix, parade hoofdspoor #1")
  AT(IR_D_2_1_BEZET)
      SAVE_SPEED
      SLOWDOWN(10)  // rustig naar beneden
  // 4. Einde hoofdspoor #1
  AT(IR_D_2_2_BEZET)
      RESTORE_SPEED
      PRINT("AutoRit: verlaten hoofdspoor #1")
      SOUND_HORN
      // KEUZES, nog rondje dorp of via dal (close is via dal)
      CLOSE(1036)
      // controleren of BD_4 vrij is..
  AT(IR_D_4_2_BEZET)
      CALL (92) // route naar helix, later nog aanpassen met keuzes
  AT(IR_D_4_1_BEZET)
      SPEED_REL(60)
      DELAY(2000)
      SPEED_REL(40)
      /* ***********************************************************/
      DELAY(8000)  // tijdelijk, nog de route afmaken geen zin meer
      /* ***********************************************************/



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
    ROUTE_CAPTION(ROUTE_4,"Niet actief")
DONE

ROUTE(ROUTE_5,"Keer om via keerlus dorp")
    // We rijden branchlijn havendorp richting helix
    AT(IR_D_1_3_BEZET)   // we zijn voorbij de wissel station/havendorp
        SOUND_BELL
        DELAY(3000)
        SOUND_BELL
        // 1. Horn en wissels omzetten
        THROW(1007) // S08 Branchlijn hoofdstation / Haven-dorp
        THROW(1024) // Wissel brouwerij
        // 2. Rij achteruit
        REV(10)
    // 3. Voorbij station, zet wissel weer om
    AT (IR_D_1_2_BEZET)
        THROW(1007) // S08 Branchlijn hoofdstation / Haven-dorp
        CLOSE(1036) // S21 Dorp / dal
        THROW(1037) // S22 Dorp / havendorp
    // 4. Voorbij de yard/haven / branchlijn
    AT(IR_D_1_4_BEZET) // lang wachten 
        SOUND_HORN
    AT(IR_D_1_5_BEZET)  // voorbij de bocht
        CLOSE(1039) // Havendorp - hoodroute #2
        DELAY(5000)      // beginnen met 12 sec, later afhankelijk van snelheid maken
        REV(0)  // voor nu even stop, kijken waar we zijn
    // 5. We rijden nu weer CCW op hoofdroute #2

RETURN
DONE


