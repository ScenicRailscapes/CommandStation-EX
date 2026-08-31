/* ===============================================================================
   Dit bestand bevat de sensoren en scripts om aan te bieden aan het control
   station via SHARED_SENSOR()
   =============================================================================== */


// Analoge BlockDetector Sensors alias (voor in Stealth code)
ALIAS(BD_D_2_SENSOR, 36)   // GPIO36
ALIAS(BD_D_3_SENSOR, 39)
ALIAS(BD_S_1_SENSOR, 34)
ALIAS(BD_S_2_SENSOR, 35)
ALIAS(BD_S_3_SENSOR, 32)
ALIAS(BD_S_4_SENSOR, 33)

// Bitmaps Analoge blockdetectors bezetmelders 
HAL(Bitmap,2110,6)         // create flags 2110..2115 // blockdetect latches
ALIAS(BD_D_2, 2110)        // Flag to indicate Helix Buitenring is occupied
ALIAS(BD_D_3,  2111)       // Helix binnenring
ALIAS(BD_S_1, 2112)        // Branchlijn dorp - station - havendorp
ALIAS(BD_S_2, 2113)        // Yard dal - havendorp
ALIAS(BD_S_3, 2114)        // Branchlijn dorp - havendorp
ALIAS(BD_S_4, 2115)        // Branchlijn dorp - havendorp


// HeartBeat 
HAL(Bitmap,2501,1)
ALIAS(HEARTBEAT_NODE_2, 2501)
// IR Sensoren, die worden wel lokaal verwerkt en als bezet status doorgegeven.

SHARED_SENSOR(2110,5)      // en share bovenstaande naar de nodes en control station
SHARED_SENSOR(HEARTBEAT_NODE_2)

