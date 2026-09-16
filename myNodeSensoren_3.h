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

// Drukknoppen op Mimicpane (via MCP23017 I2C GPIO Expander). Later nog via BITMAPS aanbieden
ALIAS(SWITCH_1, 360) // GPIO 360 (virtueel) voor Switch #1
ALIAS(SWITCH_2, 361) // GPIO 361 (virtueel) voor Switch #2
ALIAS(SWITCH_3, 362) // GPIO 362 (virtueel) voor Switch #3
ALIAS(SWITCH_4, 364) // GPIO 363 (virtueel) voor Switch #4
ALIAS(SWITCH_5, 363) // GPIO 364 (virtueel) voor Switch #5
ALIAS(SWITCH_6, 365) // GPIO 365 (virtueel) voor Switch #6
ALIAS(SWITCH_7, 366) // GPIO 366 (virtueel) voor Switch #7
ALIAS(SWITCH_8, 367) // GPIO 367 (virtueel) voor Switch #8
ALIAS(SWITCH_9, 375) // GPIO 368 (virtueel) voor Switch #9
ALIAS(SWITCH_10, 374) // GPIO 369 (virtueel) voor Switch #10
ALIAS(SWITCH_11, 373) // GPIO 370 (virtueel) voor Switch #11
ALIAS(SWITCH_12, 372) // GPIO 371 (virtueel) voor Switch #12
ALIAS(SWITCH_13, 371) // GPIO 372 (virtueel) voor Switch #13
ALIAS(SWITCH_14, 370) // GPIO 373 (virtueel) voor Switch #14
ALIAS(SWITCH_15, 369) // GPIO 374 (virtueel) voor Switch #15
ALIAS(SWITCH_16, 368) // GPIO 375 (virtueel) voor Switch #16


// HeartBeat 
HAL(Bitmap,2502,1)
ALIAS(HEARTBEAT_NODE_3, 2502)
SHARED_SENSOR(HEARTBEAT_NODE_3)

// Share status naar nodes en control station (Alias gedefinieerd in myAliases)
SHARED_SENSOR(2003,2)   // 2003-2004 BlockDetectors BD_D_4_Bezet en BD_D_5_Bezet
SHARED_SENSOR(2062,4)   // 2060-2065 IR Node 3 bezetmelders 
SHARED_SENSOR(2068,5)   // 2068-2072 IR Node 3 bezetmelders
SHARED_SENSOR(2095,3)   // 2095-2097 BD_D4 en BD_D5 status voor mimicpanel sync
SHARED_SENSOR(2190,4)   // 2190-2193 3-weg wissel routes 

// Vanaf node 1, voor in blockdetect BD_D_5 IR_D_1_3 vPin 2012
REMOTE_SENSOR(2012)