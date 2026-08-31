/* ===============================================================================
   Dit bestand bevat de sensoren en scripts om aan te bieden aan het control
   station via SHARED_SENSOR()
   =============================================================================== */


// Analoge BlockDetector Sensors alias (voor in Stealth code)
ALIAS(BD_HBU_SENSOR, 36)   // GPIO36
ALIAS(BD_HBI_SENSOR, 39)
ALIAS(BD_DORP_STATION_SENSOR, 34)
ALIAS(BD_D_4_SENSOR, 35)
ALIAS(BD_D_5_SENSOR, 32)
// GPIO 33 ADC nog over.

// IR Sensoren via I2C IO-Extender #1 (300-315). Intern voor Node gebruik, extern naar control station via bezet melding
ALIAS (IR_HBU_D, 300)     // IR Sensor Helix dal niveau buitenring
ALIAS (IR_HBU_M, 301)     // IR Sensor Helix midden niveau buitenring
ALIAS (IR_HBI_B, 302)     // IR Sensor Helix berg niveau buitenring
ALIAS (IR_D_1_1, 308)     // IR Sensor Dorp branchlijn west (berg)
ALIAS (IR_D_1_2, 309)     // IR Sensor Dorp branchlijn station
ALIAS (IR_D_1_3, 310)     // IR Sensor hoofdspoor dorp - haven
ALIAS (IR_D_2_1, 312)     // IR Sensor Hoofdspoor #1 Berg
ALIAS (IR_D_3_1, 311)     // IR Sensor Hoofdspoor #2 Berg
ALIAS (IR_HBI_D, 313)     // IR Sensor Helix dal niveau binnenring
ALIAS (IR_HBI_M, 314)     // IR Sensor Helix midden niveau binnenring
ALIAS (IR_HBU_B, 315)     // IR Sensor Helix berg niveau binnenring

// HeartBeat 
HAL(Bitmap,2500,1)
ALIAS(HEARTBEAT_NODE_1, 2500)

// Share status naar nodes en control station (Alias gedefinieerd in myAliases)
//SHARED_SENSOR(2000,5)   // Share BlockDetect status
//SHARED_SENSOR(2010,10)  // Share IR status
SHARED_SENSOR(2100,5)     // share status BlockDetect naar de nodes en control station <--- Hmmm, denk alleen de bezet melding sharen... niet deze
SHARED_SENSOR(HEARTBEAT_NODE_1)

