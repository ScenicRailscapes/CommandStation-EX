/* ===============================================================================
   Dit bestand bevat de sensoren en scripts om aan te bieden aan het control
   station via SHARED_SENSOR()
   =============================================================================== */


// Analoge BlockDetector Sensors alias (voor in Stealth code)
ALIAS(BD_D_4_SENSOR, 36)   // GPIO36
ALIAS(BD_D_5_SENSOR, 39)
// GPIO 34, 35 ADC nog over.


// IR Sensoren via I2C IO-Extender #3 (340-355). Intern voor Node gebruik, extern naar control station via bezet melding
// IR Sensors (infrarood) voor blok detectie
ALIAS (IR_L_1, 341)                 // IR Sensor Liechtenstein spoor eindpunt
ALIAS (IR_L_2, 345)                 // IR Sensor Liechtenstein spoor station midden
ALIAS (IR_L_3, 346)                 // IR Sensor Liechtenstein spoorstation berg
ALIAS (IR_D_1_5, 342)               // IR Sensor Visserdorp - dorp hoofdspoor
ALIAS (IR_D_4_1, 349)               // IR Sensor Connectie spoor #1 Dorp 
ALIAS (IR_D_4_2, 348)               // IR Sensor Connectie spoor #1 Dal
ALIAS (IR_D_1_4, 352)               // IR Sensor Haven - dorp hoofdspoor


// HeartBeat 
HAL(Bitmap,2502,1)
ALIAS(HEARTBEAT_NODE_3, 2502)
SHARED_SENSOR(HEARTBEAT_NODE_3)

// Share status naar nodes en control station (Alias gedefinieerd in myAliases)
SHARED_SENSOR(2003,2)   // 2003-2004 BlockDetectors BD_D_4_Bezet en BD_D_5_Bezet
SHARED_SENSOR(2062,4)   // 2060-2065 IR Node 3 bezetmelders 
SHARED_SENSOR(2068,5)   // 2068-2072 IR Node 3 bezetmelders
SHARED_SENSOR(2095,3)   // 2095-2097 BD_D4 en BD_D5 status voor mimicpanel sync

// Vanaf node 1, voor in blockdetect BD_D_5 IR_D_1_3 vPin 2012
REMOTE_SENSOR(2012)