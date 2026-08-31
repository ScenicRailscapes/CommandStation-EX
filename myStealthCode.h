/* ===============================================================================
   Dit bestand bevat de meeste Stealth code. , AKA code/functies in C++ die
   niet in EXRAIL zitten en/of kunnen
   =============================================================================== */

/* ====================================================================
   De C++ Kalibratie & Detector Handler voor ADS1115/ADC blockdetectors
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
  #if NODENUM == 1

    static AnalogBlockSensor analogSensors[] = {
      {BD_HBU_SENSOR, BD_HBU,                   300, 150, 300, 2000, 0, false, 0, 0},
      {BD_HBI_SENSOR, BD_HBI,                   300, 150, 300, 2000, 0, false, 0, 0},
      {BD_DORP_STATION_SENSOR, BD_DORP_STATION, 300, 150, 300, 2000, 0, false, 0, 0},
      {BD_D_4_SENSOR, BD_D_4,                   300, 150, 300, 2000, 0, false, 0, 0},
      {BD_D_5_SENSOR, BD_D_5,                   300, 150, 300, 2000, 0, false, 0, 0}
    };

  #elif NODENUM == 2

    static AnalogBlockSensor analogSensors[] = {
      {BD_D_2_SENSOR, BD_D_2,                   300, 150, 300, 2000, 0, false, 0, 0},
      {BD_D_3_SENSOR, BD_D_3,                   300, 150, 300, 2000, 0, false, 0, 0},
      {BD_S_1_SENSOR, BD_S_1,                   300, 150, 300, 2000, 0, false, 0, 0},
      {BD_S_2_SENSOR, BD_S_2,                   300, 150, 300, 2000, 0, false, 0, 0},
      {BD_S_3_SENSOR, BD_S_3,                   300, 150, 300, 2000, 0, false, 0, 0},
      {BD_S_4_SENSOR, BD_S_4,                   300, 150, 300, 2000, 0, false, 0, 0}
    };

  #elif NODENUM == 3

    static AnalogBlockSensor analogSensors[] = {
      {BD_S_5_SENSOR, BD_S_5,                   300, 150, 300, 2000, 0, false, 0, 0},
      {BD_S_RIJ_SENSOR, BD_S_RIJ,               300, 150, 300, 2000, 0, false, 0, 0}
    }; 
    
  #else
    #error "Ongeldig of niet-gedefinieerd NODENUM opgegeven!"
  #endif

  // Hier kan nog een error check, als de waarde op 0 is, dan is er waarschijnlijk een communicatie problem op de I2C
  // lijn, dan een melding maken op het LCD1 scherm ofzo, misschien iets met een LED ?
  
  const byte NUM_ANALOG_SENSORS = sizeof(analogSensors) / sizeof(analogSensors[0]);

  // Kalibratie bij start
  void calibrateAnalogSensors() {
    DIAG(F("BlockDetectSensors: Kalibratie start"));
    
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
    DIAG(F("BlockDetectSensors: Kalibratie voltooid!"));
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