/*  ======================================================================
    Remote Sensors via Nodes
    ====================================================================== */
    
// Remote (NODE) heartbeat on/offline sensoren
REMOTE_SENSOR(2500,3) // HeartBeat vPin Node #1, Node #2 en Node #3
ALIAS(REMOTE_NODE_1, 2500)
ALIAS(REMOTE_NODE_2, 2501)
ALIAS(REMOTE_NODE_3, 2502)
// On/Offline status
HAL(Bitmap,2505,3)                      // create flags 2505-2508 Remote Node On/Offline
ALIAS(REMOTE_NODE_1_STATUS, 2505)       // Bitmap Node 1 on/offline status
ALIAS(REMOTE_NODE_2_STATUS, 2506)       // Bitmap Node 2 on/offline status
ALIAS(REMOTE_NODE_3_STATUS, 2507)       // Bitmap Node 3 on/offline status
ALIAS(REMOTE_NODES_ONLINE_SET, 2508)    // Zijn ze allemaal al een keer online geweets? ivm wissels zetten
  
// Node 1 Remote Sensors
REMOTE_SENSOR(2000,5)   // 2000-2004 BlockDetectors HBI, HBU en D_1 Bezet 
REMOTE_SENSOR(2010,3)   // 2010-2012 IR Node 1 bezetmelders
REMOTE_SENSOR(2015,12)  // 2015-2026 IR Node 1 bezetmelders 
REMOTE_SENSOR(2080,3)   // 2080-2082 HBI, HBI en D_1 status voor mimicpanel sync
// Relais: Let op: deze zijn inverted signal. Aanzetten met 'RESET' en uit met 'SET' commando
// Relais op node 1 pin 315 shared via SHARED_WRITE_VPIN
ALIAS(RELAIS_DCC_REVERSE, 315)   // Relais - DCC reverse loop relais, draait de fase van het DCC signal om in een keerlus

// Node 2 Remote Sensors
REMOTE_SENSOR(2100,8)   // 2100-2107 BlockDetectors BD_D_2_Bezet en BD_D_3_Bezet, Parkeerspoor 1-5 en rijspoor bezetmelders
REMOTE_SENSOR(2030,6)   // 2030-2035 BlockDetectors BD_S_1_Bezet t/m BD_S_6_Bezet
REMOTE_SENSOR(2045,14)  // 2045-2059 BlockDetectors BD_S_5_Bezet t/m BD_S_RIJ_Bezet en de IR Bezetmelders

REMOTE_SENSOR(2066)     // IR_D_3_2
REMOTE_SENSOR(2067)     // IR_D_2_2
REMOTE_SENSOR(2013)     // IR_D_2_1
REMOTE_SENSOR(2014)     // IR_D_3_1
REMOTE_SENSOR(2062)     // IR_S_RIJ

// Node 3 Remote Sensors
REMOTE_SENSOR(2003,2)   // 2003-2004 BlockDetectors BD_D_4_Bezet en BD_D_5_Bezet
REMOTE_SENSOR(2062,4)   // 2060-2065 IR Node 3 bezetmelders 
REMOTE_SENSOR(2068,5)   // 2068-2072 IR Node 3 bezetmelders
REMOTE_SENSOR(2095,3)   // 2095-2097 BD_D4 en BD_D5 status voor mimicpanel sync
REMOTE_SENSOR(2190,4)   // 2190-2193 3-weg wissel routes

// even misbruiken voor export juist in plaats van import
// SHARED_SENSOR(2030,40)  // 2030-2069 exporteer alle IR en blockdetect bezetmelders

// als node 2 werkt: shared sensor 2030 weg, comment node 2 weg