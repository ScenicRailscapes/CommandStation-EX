/* ===============================================================================
   Dit bestand bevat de sensoren en scripts om aan te bieden aan het control
   station via SHARED_SENSOR()
   =============================================================================== */


// Analoge BlockDetector Sensors alias (voor in Stealth code)
ALIAS(BD_D_2_SENSOR,  36)      // GPIO36
ALIAS(BD_D_3_SENSOR,  39)
ALIAS(BD_S_1_SENSOR,  34)
ALIAS(BD_S_2_SENSOR,  35)
ALIAS(BD_S_3_SENSOR,  32)
ALIAS(BD_S_4_SENSOR,  33)
ALIAS(BD_S_5_SENSOR,  500)    // GPIO 500 (virtueel) tijdelijk op ADS1115
ALIAS(BD_S_RIJ_SENSOR, 501)   // GPIO 501 (virtueel) tijdelijk op ADS1115


// Aangesloten op vrij GPIO's van node 2. Intern voor Node gebruik, extern naar control station via bezet melding
// IR Sensors (infrarood) voor blok detectie
ALIAS (IR_S_1, 25)      // IR Stop sensor parkeerspoor #1
ALIAS (IR_S_2, 26)      // IR Stop sensor parkeerspoor #2
ALIAS (IR_S_3, 27)      // IR Stop sensor parkeerspoor #3
ALIAS (IR_S_4, 14)      // IR Stop sensor parkeerspoor #4
ALIAS (IR_S_5, 13)      // IR Stop sensor parkeerspoor #5
ALIAS (IR_S_RIJ, 19)    // IR Stop sensor doorrij spoor
ALIAS (IR_D_2_1, 18)    // IR Sensor Hoofdspoor #1 Dal
ALIAS (IR_D_2_2, 5)     // IR Sensor Hoofdspoor #1 Dal
ALIAS (IR_D_3_1, 17)    // IR Sensor Hoofdspoor #2 Berg
ALIAS (IR_D_3_2, 16)    // IR Sensor Hoofdspoor #2 Berg

// HeartBeat 
HAL(Bitmap,2501,1)
ALIAS(HEARTBEAT_NODE_2, 2501)
SHARED_SENSOR(HEARTBEAT_NODE_2)

// Share status naar nodes en control station (Alias gedefinieerd in myAliases)
SHARED_SENSOR(2100,6)   // 2100-2101 BlockDetectors BD_D_2_Bezet en BD_D_3_Bezet, Parkeerspoor 1-5 en rijspoor bezetmelders
SHARED_SENSOR(2030,6)   // 2030-2035 BlockDetectors BD_S_1_Bezet t/m BD_S_6_Bezet
SHARED_SENSOR(2045,14)  // 2045-2059 BlockDetectors BD_S_5_Bezet t/m BD_S_RIJ_Bezet en de IR Bezetmelders
SHARED_SENSOR(2066)     // IR_D_3_2
SHARED_SENSOR(2067)     // IR_D_2_2
SHARED_SENSOR(2013)     // IR_D_2_1
SHARED_SENSOR(2014)     // IR_D_3_1
SHARED_SENSOR(2062)     // IR_S_RIJ