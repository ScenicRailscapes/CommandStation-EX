/* ===============================================================================
   Dit bestand bevat de meeste Stealth code. , AKA code/functies in C++ die
   niet in EXRAIL zitten en/of kunnen
   =============================================================================== */

/* Shows current locos running and direction on screen 2 */ 
STEALTH_GLOBAL(
  extern int cab_now;                   // gedefinieerd in myhall.cpp
  
  void updateLocoScreen() {
    byte row = 1;
    const byte maxRows = 3;
    
    // We onthouden de status van maximaal 2 locomotieven (voor rij 1 en rij 2 op het scherm)
    // We slaan op: [loco_address, target_speed_with_direction_bit]
    static int last_loco_id[3] = {0, 0, 0};
    static byte last_raw_speed[3] = {0, 0, 0};
    
    bool change_detected = false;
    
    // Eerste ronde: We lopen door de actieve locs om te controleren of er IETS veranderd is
    byte check_row = 0;
    for (auto loco = LocoSlot::getFirst(); loco && check_row < (maxRows - 1); loco = loco->getNext(), check_row++) {
      int current_loco = loco->getLoco();
      byte current_raw = loco->getTargetSpeed(); // Bevat zowel snelheid als de 0x80 richting-bit
      
      // Als de loc op deze positie is veranderd, OF zijn snelheid/richting is veranderd:
      if (last_loco_id[check_row] != current_loco || last_raw_speed[check_row] != current_raw) {
        change_detected = true;
        
        // Sla de nieuwe status direct op in ons geheugen
        last_loco_id[check_row] = current_loco;
        last_raw_speed[check_row] = current_raw;
      }
    }
    
    // Als er absoluut geen verandering is gedetecteerd, breken we hier direct af.
    // Geen LCD-output, dus ook geen terminal-ruis!
    if (!change_detected) {
      return;
    }
    
    // Tweede ronde: Er is een verandering gedetecteerd, dus we schrijven het scherm opnieuw
    for (auto loco = LocoSlot::getFirst(); loco && row < maxRows; loco = loco->getNext(), row++) {
      auto speed = loco->getTargetSpeed();
      auto direction = (speed & 0x80) ? 'V' : 'A';
      speed &= 0x7F;
      if (speed > 0) speed--;
      
      // Update het LCD scherm (nu met rostername en maximaal 8 characters)
      //StringFormatter::lcd2(1, row, F("Loco: %2d %3d %c"), loco->getLoco(), speed, direction);
      StringFormatter::lcd2(1, row, F("%s %3d %c"), 
        String(RMFT2::getRosterName(loco->getLoco())).substring(0, 8).c_str(), 
        speed, direction);      
    }
  }  
)

/* Shows status of pre-defined routes on screen 2, only on state change */
AUTOSTART SEQUENCE(40)
    STEALTH(
      // De route ID's staan in myAliases_stm32.h
      // 1. Vaste 'static' variabelen om de vorige status te onthouden tussen de loops door
      static bool last_state_1 = false;
      static bool last_state_2 = false;
      static bool last_state_3 = false;
      static bool last_state_4 = false;

      // 2. Haal de huidige status op (true = actief, false = inactief)
      bool current_state_1 = RMFT2::ifRouteState(ROUTE_1, 1);
      bool current_state_2 = RMFT2::ifRouteState(ROUTE_2, 1);
      bool current_state_3 = RMFT2::ifRouteState(ROUTE_3, 1);
      bool current_state_4 = RMFT2::ifRouteState(ROUTE_4, 1);

      // 3. Controleer of er iets is veranderd ten opzichte van de vorige meting
      if (current_state_1 != last_state_1 || 
          current_state_2 != last_state_2 || 
          current_state_3 != last_state_3 || 
          current_state_4 != last_state_4) {

          // Er is een verandering! Update het LCD scherm (en dus eenmalig de terminal)
          StringFormatter::lcd2(1, 0, F("Route 1:%1s 2:%1s 3:%1s 4:%1s"),
              current_state_1 ? F("*") : F("-"),
              current_state_2 ? F("*") : F("-"),
              current_state_3 ? F("*") : F("-"),
              current_state_4 ? F("*") : F("-")
          );

          // 4. Sla de nieuwe status op voor de volgende vergelijking
          last_state_1 = current_state_1;
          last_state_2 = current_state_2;
          last_state_3 = current_state_3;
          last_state_4 = current_state_4;
      }
    )
    DELAY(2500) // Wacht 2.5 seconden voor de volgende snelle check
FOLLOW(40)

/* ====================================================================
   De C++ Kalibratie & Detector Handler voor ADS1115 blockdetectors
   ==================================================================== */
STEALTH_GLOBAL(
  struct AnalogBlockSensor {
    uint16_t analogVpin;   // VPIN van de ADS1115
    uint16_t digitalVpin;  // Virtuele VPIN voor de bezetmelder
    uint16_t threshold;    // Drempelwaarde boven baseline
    uint16_t hysteresis;   // Marge voor uitschakelen
    uint32_t onDelayMs;    // INSCHAKELVERTRAGING (filtert korte pieken/storing)
    uint32_t offDelayMs;   // UITSCHAKELVERTRAGING (filtert slecht contact)
    uint16_t baseLine;     // Nul-referentie bij start
    bool isOccupied;       // Huidige status (bezet/vrij)
    uint32_t riseTimeMs;   // Interne timer voor inschakelen
    uint32_t dropTimeMs;   // Interne timer voor uitschakelen
  };

  // Configuratie per sensor: 
  // { Analog VPIN, Digital VPIN, Threshold, Hysteresis, OnDelay(ms), OffDelay(ms), BaseLine, InitialState, RiseTime, DropTime }
  static AnalogBlockSensor analogSensors[] = {
    {500, BD_HBU,           300, 150, 300, 2000, 0, false, 0, 0}, // 150ms inschakelfilter, 1.5s afvalvertraging
    {501, BD_HBI,           300, 150, 300, 2000, 0, false, 0, 0}, // 200ms inschakelfilter (gevoelige lijn)
    {502, BD_DORP_STATION,  300, 150, 300, 2000, 0, false, 0, 0}
  };

  const byte NUM_ANALOG_SENSORS = sizeof(analogSensors) / sizeof(analogSensors[0]);

  // Kalibratie bij start
  void calibrateAnalogSensors() {
    DIAG(F("ADS1115: Starten met automatische kalibratie..."));
    
    const byte SAMPLES = 50;
    uint32_t totals[NUM_ANALOG_SENSORS] = {0};

    for (byte s = 0; s < SAMPLES; s++) {
      for (byte i = 0; i < NUM_ANALOG_SENSORS; i++) {
        totals[i] += IODevice::readAnalogue(analogSensors[i].analogVpin);
      }
      delay(10);
    }

    for (byte i = 0; i < NUM_ANALOG_SENSORS; i++) {
      analogSensors[i].baseLine = totals[i] / SAMPLES;
      analogSensors[i].riseTimeMs = 0;
      analogSensors[i].dropTimeMs = 0;
      
      DIAG(F("Sensor VPIN %d -> Baseline: %d | Aanslag op: >= %d | On-Delay: %d ms | Off-Delay: %d ms"), 
           analogSensors[i].analogVpin, 
           analogSensors[i].baseLine,
           analogSensors[i].baseLine + analogSensors[i].threshold,
           (int)analogSensors[i].onDelayMs,
           (int)analogSensors[i].offDelayMs);
    }
    DIAG(F("ADS1115: Kalibratie voltooid!"));
  }

  // Continu verwerkingsproces met dubbele filtering
  void processAnalogSensors() {
    uint32_t now = millis();

    for (byte i = 0; i < NUM_ANALOG_SENSORS; i++) {
      uint16_t currentVal = IODevice::readAnalogue(analogSensors[i].analogVpin);
      uint16_t triggerLevel = analogSensors[i].baseLine + analogSensors[i].threshold;
      uint16_t releaseLevel = triggerLevel - analogSensors[i].hysteresis;

      // SITUATIE 1: Signaal meet BOVEN de inschakeldrempel maar kleiner dan foutwaarde
      if (currentVal >= triggerLevel && currentVal < 65000) {
        analogSensors[i].dropTimeMs = 0; // Reset afvaltimer

        if (!analogSensors[i].isOccupied) {
          // Eerste sample die boven de drempel komt: start inschakeltimer
          if (analogSensors[i].riseTimeMs == 0) {
            analogSensors[i].riseTimeMs = now;
          } 
          // Pas als het signaal ononderbroken lang genoeg 'HOOG' blijft -> BEZET
          else if (now - analogSensors[i].riseTimeMs >= analogSensors[i].onDelayMs) {
            analogSensors[i].isOccupied = true;
            analogSensors[i].riseTimeMs = 0;
            IODevice::write(analogSensors[i].digitalVpin, HIGH);
          }
        }
      } 
      // SITUATIE 2: Signaal meet ONDER de uitschakeldrempel
      else if (currentVal < releaseLevel) {
        analogSensors[i].riseTimeMs = 0; // Korte storingspiek overgewaaid, reset inschakeltimer!

        if (analogSensors[i].isOccupied) {
          // Start afvaltimer
          if (analogSensors[i].dropTimeMs == 0) {
            analogSensors[i].dropTimeMs = now;
          } 
          // Pas als het signaal lang genoeg 'LAAG' blijft -> VRIJ
          else if (now - analogSensors[i].dropTimeMs >= analogSensors[i].offDelayMs) {
            analogSensors[i].isOccupied = false;
            analogSensors[i].dropTimeMs = 0;
            IODevice::write(analogSensors[i].digitalVpin, LOW);
          }
        }
      }
    }
  }
)


/* ====================================================================
                      Centrale Sound-Engine
   ==================================================================== */
STEALTH_GLOBAL(
  void playSoundEffect(uint16_t locoAddr, int effectId, int durationMs, int volume, int dfPlayerVpin) {
    if (locoAddr == 0) return; // Veiligheidscheck: geen loc actief

    // -------------------------------------------------------------
    // 1. CONTROLEREN OF HET EEN DCC SOUND-LOC IS (Functie mapping)
    //    Bij LOC #17 is dus een BELL functie 3 ->FON(3) 
    //    en bij LOC #13 Functie 15 =>FON(15)
    // -------------------------------------------------------------
    int soundFunc = -1; // -1 betekent: Geen DCC sound, gebruik DFPlayer

    switch (locoAddr) {
      case 19:
        if (effectId == FX_BELL)          soundFunc = 9;
        if (effectId == FX_WHISTLE_1)     soundFunc = 2;
        if (effectId == FX_WHISTLE_2)     soundFunc = 2;
        if (effectId == FX_CON_WHISTLE_1) soundFunc = 16;
        break;      
      case 17:
        if (effectId == FX_BELL)          soundFunc = 3;
        if (effectId == FX_WHISTLE_1)     soundFunc = 2;
        if (effectId == FX_WHISTLE_2)     soundFunc = 17;
        if (effectId == FX_CON_WHISTLE_1) soundFunc = 9;
        break;
      case 13:
        if (effectId == FX_BELL)      soundFunc = 15;
        if (effectId == FX_WHISTLE_1) soundFunc = 8;
        if (effectId == FX_WHISTLE_2) soundFunc = 8;
        break;
      case 10:
        if (effectId == FX_BELL)      soundFunc = 3;
        if (effectId == FX_WHISTLE_1) soundFunc = 2;
        if (effectId == FX_WHISTLE_2) soundFunc = 2;
        break;
      case 9:
        if (effectId == FX_BELL)      soundFunc = 4;
        if (effectId == FX_WHISTLE_1) soundFunc = 2;
        if (effectId == FX_WHISTLE_2) soundFunc = 2;
        break;
    }

    // -------------------------------------------------------------
    // 2. UITVOEREN: Fysieke Sound-loc OF DFPlayer
    // -------------------------------------------------------------
    if (soundFunc != -1) {
      // Het is een Sound-loc: Stuur DCC functie AAN (FON(#))
      DCC::setFn(locoAddr, soundFunc, true);

      // Als er een tijdsduur is opgegeven, na de delay weer UITzetten (FOFF(#))
      if (durationMs > 0) {
        delay(durationMs);
        DCC::setFn(locoAddr, soundFunc, false);
      }
    } 
    else {
      // Het is GEEN sound-loc: Gebruik de DFPlayer via IODevice
      // SD-Kaart structuur: Folder = LocAdres (/04, /05, /11 etc.), Track = /001.mp3, /002.mp3
      int track = effectId;
  
      // 1. Stel eerst de folder in: Folder = locoAddr
      IODevice::writeAnalogue(dfPlayerVpin, 0, locoAddr, DFPlayerBase::DF_FOLDER);

      // 2. Speel het geluid af: Track = track
      IODevice::writeAnalogue(dfPlayerVpin, track, volume, DFPlayerBase::DF_PLAY);
      // even controleren weer wat er zou moeten gebeuren, later verwijderen.
      //StringFormatter::lcd2(1, 6, F("Play: %3d Fol: %3d"), track, locoAddr); // debug
    }
  }
)