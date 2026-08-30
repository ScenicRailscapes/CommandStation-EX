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

// Bitmaps Analoge blockdetectors bezetmelders 
HAL(Bitmap,2100,5)                  // create flags 2100..2105 // blockdetect latches
ALIAS(BD_HBU, 2100)                 // Flag to indicate Helix Buitenring is occupied
ALIAS(BD_HBI, 2101)                 // Helix binnenring
ALIAS(BD_DORP_STATION, 2102)        // Branchlijn dorp - station - havendorp
ALIAS(BD_D_4, 2103)                 // Yard dal - havendorp
ALIAS(BD_D_5, 2104)                 // Branchlijn dorp - havendorp

// HeartBeat 
HAL(Bitmap,2501,1)
ALIAS(HEARTBEAT_NODE_2, 2501)
// IR Sensoren, die worden wel lokaal verwerkt en als bezet status doorgegeven.

SHARED_SENSOR(2100,5)               // en share bovenstaande naar de nodes en control station
SHARED_SENSOR(HEARTBEAT_NODE_2)

