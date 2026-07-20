/* Alternatief plan om met Matrix Signalen te werken ipv de ESP32 die als DCC-Accessorie decoder staat
   met een I2C GPIO Expander de verschillende signal matrixen direct op de pinnen aansluiten.
   In principe kunnen er 4 blockSignals & 2 exitSignals of 3 blockSignals, 1 exit en 1 entrySignal op
   een 16 poort GPIO extender
*/

/* Hoe te gebruiken ... 
  RED(152)    // Zet Exit Signal 152 op Dubbel Rood (Aspect 0)
  GREEN(152)  // Zet Exit Signal 152 op Groen (Aspect 1)
  AMBER(152)  // Zet Exit Signal 152 op Geel/Groen (Aspect 2)
  
  Wil je het sein op Rood+Wit (Rangeer-aspect) zetten?
  dan aanroepen met; SET_SHUNting_SIGNAL(SIG_152_J4, SIG_152_J3, SIG_152_J2, SIG_152_J1)
*/

/* ====================================================================
   MATRIX MACRO'S VOOR SEINEN OP GPIO EXPANDER
   ==================================================================== */

// 1. Block Signal (3 aspecten: Rood, Groen, Geel+Groen / 3 pinnen)
#define SETUP_MATRIX_BLOCK_SIGNAL(SIG_ID, PIN_A, PIN_B, PIN_C) \
    VIRTUAL_SIGNAL(SIG_ID)                                     \
    ONRED(SIG_ID)                                              \
        SET(PIN_A)                                             \
        SET(PIN_B)                                             \
        RESET(PIN_C)                                           \
    DONE                                                       \
    ONGREEN(SIG_ID)                                            \
        RESET(PIN_A)                                           \
        RESET(PIN_B)                                           \
        SET(PIN_C)                                             \
    DONE                                                       \
    ONAMBER(SIG_ID)                                            \
        RESET(PIN_A)                                           \
        SET(PIN_B)                                             \
        SET(PIN_C)                                             \
    DONE

// 2. Entry Signal (2 aspecten: Rood, Groen / 2 pinnen)
#define SETUP_MATRIX_ENTRY_SIGNAL(SIG_ID, PIN_A, PIN_B)        \
    VIRTUAL_SIGNAL(SIG_ID)                                     \
    ONRED(SIG_ID)                                              \
        SET(PIN_A)                                             \
        RESET(PIN_B)                                           \
    DONE                                                       \
    ONGREEN(SIG_ID)                                            \
        RESET(PIN_A)                                           \
        SET(PIN_B)                                             \
    DONE

// 3. Exit Signal (4 aspecten / 4 pinnen)
#define SETUP_MATRIX_EXIT_SIGNAL(SIG_ID, PIN_A, PIN_B, PIN_C, PIN_D) \
    VIRTUAL_SIGNAL(SIG_ID)                                     \
    ONRED(SIG_ID)                                              \
        SET(PIN_A)                                             \
        RESET(PIN_B)                                           \
        RESET(PIN_C)                                           \
        SET(PIN_D)                                             \
    DONE                                                       \
    ONGREEN(SIG_ID)                                            \
        RESET(PIN_A)                                           \
        RESET(PIN_B)                                           \
        SET(PIN_C)                                             \
        RESET(PIN_D)                                           \
    DONE                                                       \
    ONAMBER(SIG_ID)                                            \
        RESET(PIN_A)                                           \
        SET(PIN_B)                                             \
        SET(PIN_C)                                             \
        RESET(PIN_D)                                           \
    DONE

// 4. Losse inline actie om een Exit sein handmatig op Rood+Wit te dwingen
#define SET_SHUNting_SIGNAL(PIN_A, PIN_B, PIN_C, PIN_D) \
    SET(PIN_A)                                          \
    SET(PIN_B)                                          \
    RESET(PIN_C)                                        \
    SET(PIN_D)

// 1. DEFINIEER ALIASEN (GPIO Expander Vpins)
// blockSignals // j4, j3, j1 on led board inside aspect pole 
ALIAS(SIG_150_J4, 320)
ALIAS(SIG_150_J3, 321)
ALIAS(SIG_150_J1, 322)

ALIAS(SIG_151_J4, 323)
ALIAS(SIG_151_J3, 324)
ALIAS(SIG_151_J1, 325)

ALIAS(SIG_152_J4, 328)
ALIAS(SIG_152_J3, 329)
ALIAS(SIG_152_J1, 330)

// entrySignals // j4, j3 on led board inside aspect pole 
ALIAS(SIG_153_J4,  326)
ALIAS(SIG_153_J3,  327)

// exitSignals  // j4, j3, j2, j1 on led board inside aspect pole 
ALIAS(SIG_154_J4,  331)
ALIAS(SIG_154_J3,  332)
ALIAS(SIG_154_J2,  333)
ALIAS(SIG_154_J1,  334)


// 2. MAAK DE SEINEN AAN VIA DE NIEUWE MACRO'S

// Maak een Block Signal (ID 150)
SETUP_MATRIX_BLOCK_SIGNAL(150, SIG_150_J4, SIG_150_J3, SIG_150_J1)
// Maak een Block Signal (ID 151)
SETUP_MATRIX_BLOCK_SIGNAL(151, SIG_151_J4, SIG_151_J3, SIG_151_J1)
// Maak een Block Signal (ID 152)
SETUP_MATRIX_BLOCK_SIGNAL(152, SIG_152_J4, SIG_152_J3, SIG_152_J1)

// Maak een Entry Signal (ID 153)
SETUP_MATRIX_ENTRY_SIGNAL(153, SIG_153_J4, SIG_153_J3)

// Maak een Exit Signal (ID 154)
SETUP_MATRIX_EXIT_SIGNAL(154, SIG_154_J4, SIG_154_J3, SIG_154_J2, SIG_154_J1)    
