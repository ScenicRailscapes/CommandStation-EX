/* ===============================================================================
   Dit bestand bevat de sensoren en scripts om aan te bieden aan het control
   station via SHARED_SENSOR()
   =============================================================================== */


// Analoge BlockDetector Sensors alias (voor in Stealth code)
ALIAS(BD_S_5_SENSOR, 36)   // GPIO36
ALIAS(BD_S_RIJ_SENSOR, 39)

// GPIO 34, 35, 32, 33 ADC nog over.

// Bitmaps Analoge blockdetectors bezetmelders 
HAL(Bitmap,2120,5)                  // create flags 2100..2105 // blockdetect latches
ALIAS(BD_S_5, 2120)                 // Flag to indicate Helix Buitenring is occupied
ALIAS(BD_S_RIJ, 2121)               // Helix binnenring


// HeartBeat 
HAL(Bitmap,2502,1)
ALIAS(HEARTBEAT_NODE_3, 2502)
// IR Sensoren, die worden wel lokaal verwerkt en als bezet status doorgegeven.

SHARED_SENSOR(2120,5)               // en share bovenstaande naar de nodes en control station
SHARED_SENSOR(HEARTBEAT_NODE_3)

