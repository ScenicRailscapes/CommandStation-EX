/* ToDo: de dorpbranchlijn west klopt eigenlijk niet, het 2 pixel deel is dat kleine
   stuk (west) na de 1006 Wissel tot aan de 1007 wissel 
   even nadenken, sensoren zijn onzin, het west deel is in principe niet 
   te gebruiken als er op de buitenring gereden wordt en de wissel 1006 naar dorp staat
   maar ook niet als BD_D_5 bezet is. Kortom oplossen in code   
   
   ToDo: zou leuk zijn als ik de CW of CCW visueel kan maken. Dus via een running light ofzo
   de richting?. Zal via Stealth moeten en dus vinden hoe neopixels via Stealth aangestuurd kunnen worden
   
   */

// waar is het stuk tussen S19 en dorp geplaatst? aan DB_D_1_1??




/* ====================================================================
   MIMIC PANEL NEOPIXEL: PERCENTAGE OMREKENING & HELDERHEID
   ==================================================================== */
#define PCT(val) (((val) * 255) / 100)

// Globale helderheidsinstelling voor het Mimic board (in %)
#define BRIGHTNESS 7 

/* ====================================================================
   GENERIEKE MIMIC BINDING MACRO'S
   ==================================================================== */

// Wissel-indicatie op het mimic board
#define BIND_TURNOUT_MIMIC(TURNOUT_ID, VPIN_NEO, COUNT) \
  ONTHROW(TURNOUT_ID) \
    NEOPIXEL(VPIN_NEO, PCT(BRIGHTNESS), 0, 0, COUNT) /* Rood */ \
  DONE \
  ONCLOSE(TURNOUT_ID) \
    NEOPIXEL(VPIN_NEO, 0, PCT(BRIGHTNESS), 0, COUNT) /* Groen */ \
  DONE
  
#define BIND_TURNOUT_MIMIC_REVERSE(TURNOUT_ID, VPIN_NEO, COUNT) \
  ONCLOSE(TURNOUT_ID) \
    NEOPIXEL(VPIN_NEO, PCT(BRIGHTNESS), 0, 0, COUNT) /* Rood */ \
  DONE \
  ONTHROW(TURNOUT_ID) \
    NEOPIXEL(VPIN_NEO, 0, PCT(BRIGHTNESS), 0, COUNT) /* Groen */ \
  DONE

// IR Sensor / Bezetmelder op 1 VPIN-reeks
#define BIND_SENSOR_MIMIC_IR(SENSOR_ID, VPIN_NEO, COUNT) \
  ONSENSOR(SENSOR_ID) \
    IF(SENSOR_ID) \
      NEOPIXEL(VPIN_NEO, PCT(BRIGHTNESS), 0, 0, COUNT) /* Rood */ \
    ELSE \
      NEOPIXEL(VPIN_NEO, 0, PCT(BRIGHTNESS), 0, COUNT) /* Groen */ \
    ENDIF \
  DONE

// IR Sensor / Bezetmelder op 1 VPIN-reeks
#define BIND_SENSOR_MIMIC(SENSOR_ID, VPIN_NEO, COUNT) \
  ONSENSOR(SENSOR_ID) \
    IF(SENSOR_ID) \
      NEOPIXEL(VPIN_NEO, PCT(BRIGHTNESS), 0, 0, COUNT) /* Rood */ \
      BLINK(VPIN_NEO, 350, 350) \
    ELSE \
      NEOPIXEL(VPIN_NEO, 0, PCT(BRIGHTNESS), 0, COUNT) /* Groen */ \
      SET(VPIN_NEO) \
    ENDIF \
  DONE  

// Sensor met Neoplixels niet aansluitend op verschillende VPINs
#define BIND_SENSOR_MIMIC_DUAL(SENSOR_ID, VPIN_1, COUNT1, VPIN_2, COUNT2) \
  ONSENSOR(SENSOR_ID) \
    IF(SENSOR_ID) \
      NEOPIXEL(VPIN_1, PCT(BRIGHTNESS), 0, 0, COUNT1) /* Rood */ \
      NEOPIXEL(VPIN_2, PCT(BRIGHTNESS), 0, 0, COUNT2) /* Rood */ \
    ELSE \
      NEOPIXEL(VPIN_1, 0, PCT(BRIGHTNESS), 0, COUNT1) /* Groen */ \
      NEOPIXEL(VPIN_2, 0, PCT(BRIGHTNESS), 0, COUNT2) /* Groen */ \
    ENDIF \
  DONE

/* ====================================================================
   MIMIC PANEL CONFIGURATIE (EXRAIL)
   ==================================================================== */

/* --------------------------------------------------------------------
   1. WISSELS (ONTHROW = Rood, ONCLOSE = Groen)
   -------------------------------------------------------------------- */
BIND_TURNOUT_MIMIC(1002, 11137, 1)
BIND_TURNOUT_MIMIC_REVERSE(1003, 11136, 1)
BIND_TURNOUT_MIMIC_REVERSE(1006, 11060, 4)
BIND_TURNOUT_MIMIC(1007, 11106, 4)
BIND_TURNOUT_MIMIC(1023, 11030, 4)
BIND_TURNOUT_MIMIC_REVERSE(1024, 11124, 4)
BIND_TURNOUT_MIMIC_REVERSE(1033, 11081, 3)
BIND_TURNOUT_MIMIC(1034, 11079, 2)
BIND_TURNOUT_MIMIC(1035, 11066, 4)
BIND_TURNOUT_MIMIC_REVERSE(1036, 11074, 2)
BIND_TURNOUT_MIMIC_REVERSE(1037, 11092, 4)
BIND_TURNOUT_MIMIC(1038, 11072, 2)
BIND_TURNOUT_MIMIC_REVERSE(1039, 11076, 3)

// Speciale wissel 1040
ONCLOSE(1040)
  NEOPIXEL(11020, 0, PCT(BRIGHTNESS), 0, 2)
  NEOPIXEL(11048, 0, PCT(BRIGHTNESS), 0, 2)
  NEOPIXEL(11018, PCT(BRIGHTNESS), PCT(BRIGHTNESS), PCT(BRIGHTNESS), 2)
  NEOPIXEL(11050, PCT(BRIGHTNESS), PCT(BRIGHTNESS), PCT(BRIGHTNESS), 2)
DONE

ONTHROW(1040)
  NEOPIXEL(11018, PCT(BRIGHTNESS), 0, 0, 2)
  NEOPIXEL(11020, PCT(BRIGHTNESS), 0, 0, 2)
  NEOPIXEL(11048, PCT(BRIGHTNESS), PCT(BRIGHTNESS), PCT(BRIGHTNESS), 2)
  NEOPIXEL(11050, PCT(BRIGHTNESS), PCT(BRIGHTNESS), PCT(BRIGHTNESS), 2)
DONE


/* --------------------------------------------------------------------
   2. BLOKDETECTORS (BEZET = Rood, VRIJ = Groen)
   -------------------------------------------------------------------- */
BIND_SENSOR_MIMIC_DUAL(BD_D_1_BEZET,   11111, 13, 11088, 4)
BIND_SENSOR_MIMIC(     BD_D_2_BEZET,   11052, 6)
BIND_SENSOR_MIMIC(     BD_D_3_BEZET,   11022, 6)
BIND_SENSOR_MIMIC(     BD_D_4_BEZET,   11006, 12)
BIND_SENSOR_MIMIC_DUAL(BD_D_5_BEZET,   11036, 12, 11104, 2)
BIND_SENSOR_MIMIC_DUAL(BD_HBI_1_BEZET, 11000, 2,  11028, 2)

// BD_HBU_1 stuurt 3 losse segmenten aan en heeft meerdere seinen, hier een blocksein
ONSENSOR(BD_HBU_1_BEZET)
  IF(BD_HBU_1_BEZET)
    NEOPIXEL(11058, PCT(BRIGHTNESS), 0, 0, 2)
    NEOPIXEL(11138, PCT(BRIGHTNESS), 0, 0, 3)
    NEOPIXEL(11110, PCT(BRIGHTNESS), 0, 0, 1)
    RED(110)
  ELSE
    NEOPIXEL(11058, 0, PCT(BRIGHTNESS), 0, 2)
    NEOPIXEL(11138, 0, PCT(BRIGHTNESS), 0, 3)
    NEOPIXEL(11110, 0, PCT(BRIGHTNESS), 0, 1)
    GREEN(110)
  ENDIF
DONE

/* --------------------------------------------------------------------
   3. INFRA ROOD (IR) SENSOREN
   -------------------------------------------------------------------- */
BIND_SENSOR_MIMIC_IR(IR_D_1_1_BEZET, 11112, 1)
BIND_SENSOR_MIMIC_IR(IR_D_1_2_BEZET, 11119, 1)
BIND_SENSOR_MIMIC_IR(IR_D_1_3_BEZET, 11106, 1)
BIND_SENSOR_MIMIC_IR(IR_D_1_4_BEZET, 11077, 1)
BIND_SENSOR_MIMIC_IR(IR_D_1_5_BEZET, 11043, 1)

BIND_SENSOR_MIMIC_IR(IR_D_2_1_BEZET, 11058, 1)
BIND_SENSOR_MIMIC_IR(IR_D_2_2_BEZET, 11052, 1)

BIND_SENSOR_MIMIC_IR(IR_D_3_1_BEZET, 11027, 1)
BIND_SENSOR_MIMIC_IR(IR_D_3_2_BEZET, 11022, 1)

BIND_SENSOR_MIMIC_IR(IR_D_4_1_BEZET, 11006, 1)
BIND_SENSOR_MIMIC_IR(IR_D_4_2_BEZET, 11011, 1)


/* --------------------------------------------------------------------
   4. SPECIALE VRIJ/BEZET INDICATIES
   -------------------------------------------------------------------- */
#define HAVEN_VRIJ                    NEOPIXEL(11084, 0, PCT(BRIGHTNESS), 0, 2) /* Groen */
#define HAVEN_BEZET                   NEOPIXEL(11084, PCT(BRIGHTNESS), 0, 0, 2)  /* Rood */
#define LOKLOODS_VRIJ                 NEOPIXEL(11086, 0, PCT(BRIGHTNESS), 0, 2) /* Groen */
#define LOKLOODS_BEZET                NEOPIXEL(11086, PCT(BRIGHTNESS), 0, 0, 2)  /* Rood */
#define BERGSTATION_VRIJ              NEOPIXEL(11034, 0, PCT(BRIGHTNESS), 0, 2) /* Groen */
#define BERGSTATION_BEZET             NEOPIXEL(11034, PCT(BRIGHTNESS), 0, 0, 2)  /* Rood */
#define BROUWERIJ_VRIJ                NEOPIXEL(11128, 0, PCT(BRIGHTNESS), 0, 2) /* Groen */
#define BROUWERIJ_BEZET               NEOPIXEL(11128, PCT(BRIGHTNESS), 0, 0, 2)  /* Rood */
#define DORPBRANCHWEST_VRIJ           NEOPIXEL(11064, 0, PCT(BRIGHTNESS), 0, 2) /* Groen */
#define DORPBRANCHWEST_BEZET          NEOPIXEL(11064, PCT(BRIGHTNESS), 0, 0, 2)  /* Rood */
#define SCHADUWSTATION_RECHTS_VRIJ    NEOPIXEL(11070, 0, PCT(BRIGHTNESS), 0, 2) /* Groen */
#define SCHADUWSTATION_RECHTS_BEZET   NEOPIXEL(11070, PCT(BRIGHTNESS), 0, 0, 2)  /* Rood */
#define SCHADUWSTATION_LINKS_VRIJ     NEOPIXEL(11098, 0, PCT(BRIGHTNESS), 0, 2) /* Groen */
#define SCHADUWSTATION_LINKS_BEZET    NEOPIXEL(11098, PCT(BRIGHTNESS), 0, 0, 2)  /* Rood */
#define YARD_DAL_VRIJ                 NEOPIXEL(11130, 0, PCT(BRIGHTNESS), 0, 6) /* Groen */
#define YARD_DAL_BEZET                NEOPIXEL(11130, PCT(BRIGHTNESS), 0, 0, 6)  /* Rood */
#define DAL_ROUTE_VRIJ                NEOPIXEL(11148, 0, PCT(BRIGHTNESS), 0, 3) /* Groen */
#define DAL_ROUTE_BEZET               NEOPIXEL(11148, PCT(BRIGHTNESS), 0, 0, 3)  /* Rood */
// Speciale 3-weg wissel werkt met routes IPV ONTHROW/ONCLOSE
#define MIMIC_ROUTE_90_ACTIVE         NEOPIXEL(11100, 0, PCT(BRIGHTNESS), 0, 4) /* Groen 3-weg Wissel SCHADUWSTAION */
#define MIMIC_ROUTE_90_INACTIVE       NEOPIXEL(11100, PCT(BRIGHTNESS), 0, 0, 4)  /* Rood 3-weg Wissel SCHADUWSTAION */
#define MIMIC_ROUTE_91_ACTIVE         NEOPIXEL(11002, 0, PCT(BRIGHTNESS), 0, 4) /* Groen 3-weg Wissel HELIX DAL BINNENRING */
#define MIMIC_ROUTE_91_INACTIVE       NEOPIXEL(11002, PCT(BRIGHTNESS), 0, 0, 4)  /* Rood 3-weg Wissel HELIX DAL BINNENRING */
#define MIMIC_ROUTE_92_ACTIVE         NEOPIXEL(11144, 0, PCT(BRIGHTNESS), 0, 4) /* Groen 3-weg Wissel HELIX DAL BUITENRING */
#define MIMIC_ROUTE_92_INACTIVE       NEOPIXEL(11144, PCT(BRIGHTNESS), 0, 0, 4)  /* Rood 3-weg Wissel HELIX DAL BUITENRING */
