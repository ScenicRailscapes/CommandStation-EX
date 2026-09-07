/* ===============================================================================
   Dit bestand bevat de sensoren en scripts om aan te bieden aan het control
   station via SHARED_SENSOR()
   =============================================================================== */


// Analoge BlockDetector Sensors alias (voor in Stealth code)
ALIAS(BD_HBU_SENSOR, 36)   // GPIO36
ALIAS(BD_HBI_SENSOR, 39)
ALIAS(BD_DORP_STATION_SENSOR, 34)
// GPIO 33, 35, 32 ADC nog over.

// IR Sensoren via I2C IO-Extender #1 (300-315). Intern voor Node gebruik, extern naar control station via bezet melding
// vrij 306, 307, 312, 313, 314
ALIAS (IR_HBU_B, 300)     // IR Sensor Helix dal niveau buitenring
ALIAS (IR_HBI_B, 301)     // IR Sensor Helix berg niveau binnenring
ALIAS (IR_HBU_M, 302)     // IR Sensor Helix midden niveau buitenring
ALIAS (IR_HBI_M, 303)     // IR Sensor Helix berg niveau buitenring
ALIAS (IR_HBU_D, 304)     // IR Sensor Helix dal niveau binnenring
ALIAS (IR_HBI_D, 305)     // IR Sensor Helix midden niveau binnenring
ALIAS (IR_D_1_1, 308)     // IR Sensor Dorp branchlijn west (berg)
ALIAS (IR_D_1_2, 309)     // IR Sensor Dorp branchlijn station
ALIAS (IR_D_1_3, 310)     // IR Sensor hoofdspoor dorp - haven
ALIAS(RELAIS_DCC_REVERSE, 315)   // Relais - DCC reverse loop relais, draait de fase van het DCC signal om in een keerlus

// HeartBeat 
HAL(Bitmap,2500,1)
ALIAS(HEARTBEAT_NODE_1, 2500)
SHARED_SENSOR(HEARTBEAT_NODE_1)

// Share status naar nodes en control station (Alias gedefinieerd in myAliases)
SHARED_SENSOR(2000,5)   // 2000-2004 BlockDetectors HBI, HBU en D_1 Bezet 
SHARED_SENSOR(2010,3)   // 2010-2012 IR Node 1 bezetmelders
SHARED_SENSOR(2015,12)  // 2015-2026 IR Node 1 bezetmelders 
SHARED_SENSOR(2080,3)   // 2080-2082 HBI, HBI en D_1 status voor mimicpanel sync
SHARED_WRITE_VPINS(RELAIS_DCC_REVERSE,1)    // KEERLUS Relais sharen met CS en nodes