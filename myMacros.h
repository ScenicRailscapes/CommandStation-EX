// myMacros.h
#ifndef MY_MACROS_H
#define MY_MACROS_H

// macro voor de DF_Players (Gecorrigeerd zonder backslash bij comment)
#define PLAYSND(player, folder, track, volume) \
    PLAY_FOLDER(player+10000,folder) \
    PLAY_TRACK(player+10000,track,volume)

// macro voor de 7-segment display 
#define CLEARSEG7(firstVpin) \
  SEG7(firstVpin,0,4R) \
  SEG7(firstVpin+4,0,4R)

/* ====================================================================
   CENTRALE MACRO VOOR BLOKBEVEILIGING MET IR EN RICHTING
   ==================================================================== */
#define CONCAT_INTERNAL(x, y) x##y
#define CONCAT(x, y) CONCAT_INTERNAL(x, y)

#define SETUP_IR_BLOCK_WITH_AMBER(BLOCK_NUM, BD_SENSOR, IR_1, IR_2, BITMAP_BEZET, BITMAP_CW, BITMAP_CCW, DEBOUNCE_DELAY, BACKUP_DELAY, AMBER_DELAY, ACTIE_RED, ACTIE_AMBER, ACTIE_GREEN) \
                                                                        \
    /* 1. Vrijgave via zijde 2 (CW Uitgang) -> Sein naar GROEN */        \
    SEQUENCE(CONCAT(10, BLOCK_NUM))                                     \
        DELAY(DEBOUNCE_DELAY)                                           \
        RESET(BITMAP_BEZET)                                             \
        RESET(BITMAP_CW)                                                \
        ACTIE_GREEN                                                     \
        PRINT("Blok " #BLOCK_NUM ": Vertrokken via CW-zijde (Groen)")   \
        FREE(BLOCK_NUM)                                                 \
    DONE                                                                \
                                                                        \
    /* 2. Vrijgave via zijde 1 (CCW Uitgang) -> Sein naar GROEN */       \
    SEQUENCE(CONCAT(20, BLOCK_NUM))                                     \
        DELAY(DEBOUNCE_DELAY)                                           \
        RESET(BITMAP_BEZET)                                             \
        RESET(BITMAP_CCW)                                               \
        ACTIE_GREEN                                                     \
        PRINT("Blok " #BLOCK_NUM ": Vertrokken via CCW-zijde (Groen)")  \
        FREE(BLOCK_NUM)                                                 \
    DONE                                                                \
                                                                        \
    /* 3. Stroommelder Back-up */                                       \
    SEQUENCE(CONCAT(30, BLOCK_NUM))                                     \
        DELAY(BACKUP_DELAY)                                             \
        IFNOT(BITMAP_BEZET)                                             \
            SET(BITMAP_BEZET)                                           \
            ACTIE_RED                                                   \
            PRINT("Blok " #BLOCK_NUM ": HARDWAREMATIG bezet (Back-up)") \
            RESERVE(BLOCK_NUM)                                          \
        ENDIF                                                           \
    DONE                                                                \
                                                                        \
    /* 4. Timer voor AMBER bij CW-binnenkomst */                        \
    SEQUENCE(CONCAT(40, BLOCK_NUM))                                     \
        IF(BITMAP_BEZET)                                                \
            DELAY(AMBER_DELAY)                                          \
            ACTIE_AMBER                                                 \
            PRINT("Blok " #BLOCK_NUM ": Trein is IR_1 gepasseerd")      \
            FREE(BLOCK_NUM)                                             \
        ENDIF                                                           \
    DONE                                                                \
                                                                        \
    /* 5. Timer voor AMBER bij CCW-binnenkomst */                       \
    SEQUENCE(CONCAT(50, BLOCK_NUM))                                     \
        IF(BITMAP_BEZET)                                                \
            DELAY(AMBER_DELAY)                                          \
            ACTIE_AMBER                                                 \
            PRINT("Blok " #BLOCK_NUM ": Trein is IR_2 gepasseerd")      \
            FREE(BLOCK_NUM)                                             \
        ENDIF                                                           \
    DONE                                                                \
                                                                        \
    /* 6. Hardware trigger zijde 1 */                                   \
    ONSENSOR(IR_1)                                                      \
        IF(IR_1)                                                        \
            IF(BITMAP_CCW)                                              \
                START(CONCAT(20, BLOCK_NUM))                            \
            ENDIF                                                       \
            IFNOT(BITMAP_CW)                                            \
                IFNOT(BITMAP_CCW)                                       \
                    SET(BITMAP_BEZET)                                   \
                    SET(BITMAP_CW)                                      \
                    ACTIE_RED                                           \
                    PRINT("Blok " #BLOCK_NUM ": BINNEN via CW (Rood)")  \
                    RESERVE(BLOCK_NUM)                                  \
                ENDIF                                                   \
            ENDIF                                                       \
        ENDIF                                                           \
        IFNOT(IR_1)                                                     \
            IF(BITMAP_CW)                                               \
                START(CONCAT(40, BLOCK_NUM))                            \
            ENDIF                                                       \
        ENDIF                                                           \
    DONE                                                                \
                                                                        \
    /* 7. Hardware trigger zijde 2 */                                   \
    ONSENSOR(IR_2)                                                      \
        IF(IR_2)                                                        \
            IF(BITMAP_CW)                                               \
                START(CONCAT(10, BLOCK_NUM))                            \
            ENDIF                                                       \
            IFNOT(BITMAP_CCW)                                           \
                IFNOT(BITMAP_CW)                                        \
                    SET(BITMAP_BEZET)                                   \
                    SET(BITMAP_CCW)                                     \
                    ACTIE_RED                                           \
                    PRINT("Blok " #BLOCK_NUM ": BINNEN via CCW (Rood)") \
                    RESERVE(BLOCK_NUM)                                  \
                ENDIF                                                   \
            ENDIF                                                       \
        ENDIF                                                           \
        IFNOT(IR_2)                                                     \
            IF(BITMAP_CCW)                                              \
                START(CONCAT(50, BLOCK_NUM))                            \
            ENDIF                                                       \
        ENDIF                                                           \
    DONE                                                                \
                                                                        \
    /* 8. Hardware trigger Stroommelder */                              \
    ONSENSOR(BD_SENSOR)                                                 \
        IF(BD_SENSOR)                                                   \
            START(CONCAT(30, BLOCK_NUM))                                \
        ENDIF                                                           \
    DONE

/* ====================================================================
   MACRO VOOR SCHADUWSTATION PARKEERSPOREN (1 IR + STROOMMELDER)
   ==================================================================== */
#define SETUP_YARD_BLOCK(BLOCK_NUM, BD_SENSOR, IR_STOP, BITMAP_BEZET, RELEASE_DELAY, BACKUP_DELAY) \
                                                                        \
    /* 1. Vrijgave sequence: start zodra de stroommelder afvalt */      \
    SEQUENCE(CONCAT(70, BLOCK_NUM))                                     \
        DELAY(RELEASE_DELAY)                                            \
        /* Als na de delay de stroommelder én de IR-sensor nog steeds vrij zijn */ \
        IFNOT(BD_SENSOR)                                                \
            IFNOT(IR_STOP)                                              \
                RESET(BITMAP_BEZET)                                     \
                PRINT("Parkeerspoor " #BLOCK_NUM ": Volledig VRIJ")     \
                FREE(BLOCK_NUM)                                         \
            ENDIF                                                       \
        ENDIF                                                           \
    DONE                                                                \
                                                                        \
    /* 2. Stroommelder trigger: activeert bij binnenrijden */           \
    ONSENSOR(BD_SENSOR)                                                 \
        IF(BD_SENSOR)                                                   \
            DELAY(BACKUP_DELAY)                                         \
            IFNOT(BITMAP_BEZET)                                         \
                SET(BITMAP_BEZET)                                       \
                PRINT("Parkeerspoor " #BLOCK_NUM ": Binnenrijden")      \
                RESERVE(BLOCK_NUM)                                      \
            ENDIF                                                       \
        ENDIF                                                           \
        IFNOT(BD_SENSOR)                                                \
            IF(BITMAP_BEZET)                                            \
                START(CONCAT(70, BLOCK_NUM))                            \
            ENDIF                                                       \
        ENDIF                                                           \
    DONE                                                                \
                                                                        \
    /* 3. IR Stop-melder trigger */                                     \
    ONSENSOR(IR_STOP)                                                   \
        IF(IR_STOP)                                                     \
            SET(BITMAP_BEZET)                                           \
            PRINT("Parkeerspoor " #BLOCK_NUM ": Trein op STOP!")        \
        ENDIF                                                           \
    DONE


/* ====================================================================
   CENTRALE MACRO VOOR STANDAARD DEBOUNCED IR-SENSOREN
   ==================================================================== */
#define SETUP_IR_SENSOR(SENSOR_ID, BITMAP_BEZET, DEBOUNCE_DELAY, TEXT_MSG) \
                                                                        \
    ONSENSOR(SENSOR_ID)                                                 \
        AT(SENSOR_ID)                                                   \
            IFNOT(BITMAP_BEZET)                                         \
                SET(BITMAP_BEZET)                                       \
                PRINT(TEXT_MSG " sensor active")                        \
            ENDIF                                                       \
            AFTER(SENSOR_ID, DEBOUNCE_DELAY)                            \
                IF(BITMAP_BEZET)                                        \
                    RESET(BITMAP_BEZET)                                 \
                    PRINT(TEXT_MSG " sensor inactive")                  \
                ENDIF                                                   \
            DONE                                                        \
        DONE                                                            \
    DONE    

/* ====================================================================
   CENTRALE MACRO VOOR SEINLOGICA EN ASPECTEN
   ==================================================================== */
#define NO_SIGNAL(pin)        DELAY(0)
#define SIGNAL_2A_RED(pin)    RED(pin)
#define SIGNAL_2A_GREEN(pin)  GREEN(pin)
#define SIGNAL_3A_RED(pin)    RED(pin)
#define SIGNAL_3A_AMBER(pin)  AMBER(pin)
#define SIGNAL_3A_GREEN(pin)  GREEN(pin)    

/* ====================================================================
   LIVE DEFINITIE VAN DE KEERLUS SEQUENCES
   ==================================================================== */
// We sturen de pinnen direct aan via de macro-expansie!
#define LOOP_ENTRY_WEST \
    SET(REVERSE_SIGNAL_ACTIVE) \
    RESET(RELAIS_DCC_REVERSE) \
    BLINK(600,500,500)

#define LOOP_ENTRY_EAST \
    RESET(REVERSE_SIGNAL_ACTIVE) \
    DELAY(8000) /* even wachten tot de trein het keerlusdeel heeft verlaten */ \
    SET(RELAIS_DCC_REVERSE) \
    RESET(600)

// // moet nog iets maken wat het actieve loco address oppikt.. Kan met een STEALTH en locoAddr
#define LOCO_HANDOVER(loconum, sequencenum) \
  SENDLOCO(loconum,sequencenum)             \
  DONE


/* =========================================================================
   Geen sound maar wat speciale functies bij locs (downlights, baangeluiden)
   ========================================================================= */
  
 #define LOCO_SPECIAL_STARTUP                         \
  IFLOCO(17,13,19)                                    \
    IFLOCO(17) FON(8)  FON(4)  ENDIF                  \
    IFLOCO(13) FON(10) FON(14) FON(22) FON(23) ENDIF  \
    IFLOCO(19) FON(7)  FON(10) FON(15) FON(18) ENDIF  \
  ENDIF  


/* ====================================================================
   MACRO VOOR HET SYNCHRONISEREN / SYNCEN VAN SENSOREN
   fysieke SENSOR vergelijken met zijn virtuele _BEZET vlag of andere naam
   ==================================================================== */
#define SYNC_SENSOR_EXPLICIT(SENSOR, BEZET_FLAG) \
  IF(SENSOR) \
    RESET(BEZET_FLAG) \
    DELAY(100) \
    SET(BEZET_FLAG) \
  ELSE \
    SET(BEZET_FLAG) \
    DELAY(100) \
    RESET(BEZET_FLAG) \
  ENDIF

/* ====================================================================
   EXRAIL MACRO'S VOOR ANALOGE BLOKDETECTIE
   ==================================================================== */

// Macro om kalibratie uit te voeren
#define CALIBRATE_ADS1115() STEALTH( calibrateAnalogSensors(); )

// Macro om alle sensoren 1 keer uit te lezen
#define PROCESS_ADS1115()   STEALTH( processAnalogSensors(); )

/* ====================================================================
   EXRAIL ANALOGE BLOKDETECTIE DIAGNOSE MACRO'S
   ==================================================================== */

// Print eenmalig de status van alle analoge poorten naar de Seriële Monitor
#define DIAG_ADS1115()        STEALTH( printADS1115Diagnostics(); )

// Herkalibreer alle sensoren handmatig (bijv. als er geen treinen op de baan staan)
#define RECALIBRATE_ADS1115() STEALTH( calibrateAnalogSensors(); )

/* ====================================================================
   CENTRALE MACRO VOOR SEINLOGICA EN ASPECTEN
   ==================================================================== */
#define NO_SIGNAL(pin)        DELAY(0)
#define SIGNAL_2A_RED(pin)    RED(pin)
#define SIGNAL_2A_GREEN(pin)  GREEN(pin)
#define SIGNAL_3A_RED(pin)    RED(pin)
#define SIGNAL_3A_AMBER(pin)  AMBER(pin)
#define SIGNAL_3A_GREEN(pin)  GREEN(pin)    

/* ====================================================================
   CENTRALE MACRO MATRIX SEIN VIA IO EXTENDER
   ==================================================================== */

// --------------------------------------------------------------------
// 1. BLOCK SIGNAL (3 draden/pinnen: J4, J3, J1)
// Matrix:
// - Rood (color0)  : J4=HIGH, J3=HIGH, J1=LOW
// - Groen (color1) : J4=LOW,  J3=LOW,  J1=HIGH
// - Geel (color2)  : J4=LOW,  J3=HIGH, J1=HIGH
// --------------------------------------------------------------------
#define DEFINE_BLOCK_SIGNAL(SIG_ID, PIN_J4, PIN_J3, PIN_J1) \
  VIRTUAL_SIGNAL(SIG_ID) \
    ONRED(SIG_ID) \
      SET(PIN_J4) \
      SET(PIN_J3) \
      RESET(PIN_J1) \
    DONE \
    ONGREEN(SIG_ID) \
      RESET(PIN_J4) \
      RESET(PIN_J3) \
      SET(PIN_J1) \
    DONE \
    ONAMBER(SIG_ID) \
      RESET(PIN_J4) \
      SET(PIN_J3) \
      SET(PIN_J1) \
    DONE

// --------------------------------------------------------------------
// 2. ENTRY SIGNAL (Inrijsein - 2 draden/pinnen: J4, J3)
// Matrix:
// - Rood (color0)  : J4=HIGH, J3=LOW
// - Groen (color1) : J4=LOW,  J3=HIGH
// --------------------------------------------------------------------
#define DEFINE_ENTRY_SIGNAL(SIG_ID, PIN_J4, PIN_J3) \
  VIRTUAL_SIGNAL(SIG_ID) \
    ONRED(SIG_ID) \
      SET(PIN_J4) \
      RESET(PIN_J3) \
    DONE \
    ONGREEN(SIG_ID) \
      RESET(PIN_J4) \
      SET(PIN_J3) \
    DONE

// --------------------------------------------------------------------
// 3. EXIT SIGNAL (Uitrijsein - 4 draden/pinnen: J4, J3, J2, J1)
// Matrix:
// - Dubbel Rood (color0)  : J4=HIGH, J3=LOW,  J2=LOW,  J1=HIGH
// - Groen (color1)        : J4=LOW,  J3=LOW,  J2=HIGH, J1=LOW
// - Geel + Groen (color2) : J4=LOW,  J3=HIGH, J2=HIGH, J1=LOW
// - Rood + Wit (color3)   : J4=HIGH, J3=HIGH, J2=LOW,  J1=HIGH
// --------------------------------------------------------------------
#define DEFINE_EXIT_SIGNAL(SIG_ID, PIN_J4, PIN_J3, PIN_J2, PIN_J1) \
  VIRTUAL_SIGNAL(SIG_ID) \
    ONRED(SIG_ID) /* Color 0: Dubbel Rood */ \
      SET(PIN_J4) \
      RESET(PIN_J3) \
      RESET(PIN_J2) \
      SET(PIN_J1) \
    DONE \
    ONGREEN(SIG_ID) /* Color 1: Groen */ \
      RESET(PIN_J4) \
      RESET(PIN_J3) \
      SET(PIN_J2) \
      RESET(PIN_J1) \
    DONE \
    ONAMBER(SIG_ID) /* Color 2: Geel + Groen */ \
      RESET(PIN_J4) \
      SET(PIN_J3) \
      SET(PIN_J2) \
      RESET(PIN_J1) \
    DONE 

 /* ====================================================================
   CUSTOM SEINBEELD MACRO'S VOOR AFWIJKENDE ASPECTEN (WIT / RANGEREN)
   ==================================================================== */

// Zet een ExitSignal expliciet op Rood + Wit (Color 3)
#define SET_EXIT_SIGNAL_WHITE(PIN_J4, PIN_J3, PIN_J2, PIN_J1) \
  SET(PIN_J4) \
  SET(PIN_J3) \
  RESET(PIN_J2) \
  SET(PIN_J1)

// Of gekoppeld aan het Sein ID via een custom macro:
#define SET_SIG_170_WHITE() SET_EXIT_SIGNAL_WHITE(SIG_170_J4, SIG_170_J3, SIG_170_J2, SIG_170_J1)   

/* ==================================================================== */
#endif // MY_MACROS_H