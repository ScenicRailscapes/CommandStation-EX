/*
 This file contains aliases for sensors, locs, switches, relays, motors, servos, latches and other items 
 used in the DCC-EX Command Station setup for the Silberbacktal Bahn model railroad.
*/

// Roster setup for known locs/trains
ROSTER(4,"E32 103","Lights///Shunting")
ROSTER(5,"4800","Lights/Burner")
ROSTER(6,"V290","Lights///Shunting")
ROSTER(7,"BR 89","F0///Shunting")
ROSTER(8,"Tandrad LichtensteinBahn","F0///Shunting")
ROSTER(9,"Glaskasten","Lights/Steam/Whistle Long/*Whistle/Bell/Water/Shunting/Air")
ROSTER(10,"BR 78","Lights/Steam/*Whistle/Bell/Water/Air/Shunting")
ROSTER(11,"BR 53","Lights///Shunting")
ROSTER(12,"18 201","Lights/Steam/////Shunting")
ROSTER(13,"V60","Lights/Sound/*Horn/Smoke/*Coupler/Lights Off F/Lights Off R/Cab Lights/Shunting/*Sec Horn/DownLights/Brake/Radio#1/Heavy/Dash Lights/Bell/Train Brakes/Hand Brakes/Heater/Indusi/Sanding/Compressor/Wissel geluid/Baan geluid/Air release/Fuel pump/Bocht geluid/Whistle/Radio #2/Radio #3/Muting/")
ROSTER(14,"BR 86 LichtensteinBahn","Lights///Shunting")
ROSTER(15,"Kittel tram","Lights/Cabine//Shunting")
ROSTER(17,"OBB 691","Lights/Sound/*Horn/Bell/Fire/*Coupler//Shunting/DownLights/Conductor Whistle/Pump/Station #1/Station #2/Language/Volume/TunnelMode/Steam Release/Long Whistle/Airpump/Waterpump/Sanding/Firebox Feed//Brakes/Emergency Brakes")
ROSTER(18,"OBB 2060","Lights///Shunting")
ROSTER(19,"BR 78","Lights/Sound/*Whistle/Smoke/Coupler/Lights Off F/Lights Off R/Cab Lights/Shunting/Bell/Fire/Cylinder Smoke/Brakes sound off/3rd Headlight/Heavy Load/DownLights/*Conductor Whistle/Waterpump slow/Bochten geluid/*Steam Release/Hand Brakes/Airpump/Injector/Announcement #2/Announcement #3/Braking/Water vullen/Idling/Tunnelmodus/Announcement #4/High pressure steam off/*Security Valve")
// Aliassen - LET OP: De aliassen werken het beste met echte vPin, niet de ID's, wissels werken wel goed met ID's


// On/Offline warning led
// Via GPIO Expander vPin 320-335
ALIAS(REMOTE_NODE_1_LED, 330)  
ALIAS(REMOTE_NODE_2_LED, 329)
ALIAS(REMOTE_NODE_3_LED, 328)     

// Functiie switches CS front panel voor diverse functies
ALIAS(CS_F_SWITCH_1, 324)
ALIAS(CS_F_SWITCH_2, 325)
ALIAS(CS_F_SWITCH_3, 326)
ALIAS(CS_F_SWITCH_4, 327)

// Remote Sensor mapping naar lokale bitmaps
// Bitmaps (Latches )voor bezet / vrij 
HAL(Bitmap,2000,70) // create flags 2000..2060 // Block bezet flags/latches
// node 1
ALIAS(BD_HBI_1_BEZET, 2000)         // Block #1 occupied latch
ALIAS(BD_HBU_1_BEZET, 2001)         // Block #2 occupied latch
ALIAS(BD_D_1_BEZET, 2002)           // Block #3 occupied latch
ALIAS(BD_D_4_BEZET, 2003)           // Block #6 occupied latch
ALIAS(BD_D_5_BEZET, 2004)           // Block #13 occupied latch

ALIAS(IR_D_1_1_BEZET, 2010)         // IR Sensor Dorp branchlijn west (berg) bezet latch
ALIAS(IR_D_1_2_BEZET, 2011)         // IR Sensor Dorp branchlijn station bezet latch
ALIAS(IR_D_1_3_BEZET, 2012)         // IR Sensor hoofdspoor dorp - haven bezet latch
ALIAS(IR_HBI_M_BEZET, 2015)         // IR Sensor Helix midden niveau binnenring bezet latch
ALIAS(IR_HBI_B_BEZET, 2016)         // IR Sensor Helix berg niveau binnenring bezet latch
ALIAS(IR_HBI_D_BEZET, 2017)         // IR Sensor Helix dal niveau binnenring bezet latch
ALIAS(IR_HBU_D_BEZET, 2018)         // IR Sensor Helix dal niveau buitenring bezet latch
ALIAS(IR_HBU_M_BEZET, 2019)         // IR Sensor Helix midden niveau buitenring bezet latch
ALIAS(IR_HBU_B_BEZET, 2020)         // IR Sensor Helix berg niveau buitenring bezet latch

ALIAS(BD_D_1_CW, 2021)              // Trein rijdt Clockwise door blok 1
ALIAS(BD_D_1_CCW, 2022)             // Trein rijdt Counter Clockwise door blok 1
ALIAS(BD_HBI_1_CW, 2023)            // Trein rijdt Clockwise door blok HBI
ALIAS(BD_HBI_1_CCW, 2024)           // Trein rijdt Counter Clockwise door blok HBI
ALIAS(BD_HBU_1_CW, 2025)            // Trein rijdt Clockwise door blok HBU
ALIAS(BD_HBU_1_CCW, 2026)           // Trein rijdt Counter Clockwise door blok HBU

// Bitmaps Analoge blockdetectors bezetmelders
HAL(Bitmap,2080,19)                 // create flags 2080..2085 // blockdetect latches
ALIAS(BD_HBU, 2080)                 // Flag to indicate Helix Buitenring is occupied
ALIAS(BD_HBI, 2081)                 // Helix binnenring
ALIAS(BD_DORP_STATION, 2082)        // Branchlijn dorp-station

// node 2
ALIAS(BD_D_2_BEZET, 2030)           // Block #4 occupied latch 
ALIAS(BD_D_3_BEZET, 2031)           // Block #5 occupied latch
ALIAS(BD_S_1_BEZET, 2032)           // Block #7 occupied latch
ALIAS(BD_S_2_BEZET, 2033)           // Block #8 occupied latch
ALIAS(BD_S_3_BEZET, 2034)           // Block #9 occupied latch
ALIAS(BD_S_4_BEZET, 2035)           // Block #10 occupied latch
ALIAS(BD_S_5_BEZET, 2045)           // Block #11 occupied latch
ALIAS(BD_S_RIJ_BEZET, 2046)         // Block #12 occupied latch

ALIAS(IR_S_1_BEZET, 2047)           // IR Stop sensor parkeerspoor #1 bezet latch
ALIAS(IR_S_2_BEZET, 2048)           // IR Stop sensor parkeerspoor #2 bezet latch
ALIAS(IR_S_3_BEZET, 2049)           // IR Stop sensor parkeerspoor #3 bezet latch
ALIAS(IR_S_4_BEZET, 2050)           // IR Stop sensor parkeerspoor #4 bezet latch
ALIAS(IR_S_5_BEZET, 2051)           // IR Stop sensor parkeerspoor #5 bezet latch
ALIAS(IR_S_RIJ_BEZET, 2062)         // IR Stop sensor doorrij spoor bezet latch

ALIAS(IR_D_2_1_BEZET, 2013)         // IR Sensor Hoofdspoor #1 Berg bezet latch
ALIAS(IR_D_3_1_BEZET, 2014)         // IR Sensor Hoofdspoor #2 Berg bezet latch
ALIAS(IR_D_3_2_BEZET, 2066)         // IR Sensor Hoofdspoor #2 Dorp bezet latch
ALIAS(IR_D_2_2_BEZET, 2067)         // IR Sensor Hoofdspoor #1 Dorp bezet latch

ALIAS(BD_D_2_CW, 2053)              // Trein rijdt Clockwise door blok 2
ALIAS(BD_D_2_CCW, 2054)             // Trein rijdt Counter Clockwise door blok 2
ALIAS(BD_D_3_CW, 2055)              // Trein rijdt Clockwise door blok 3
ALIAS(BD_D_3_CCW, 2056)             // Trein rijdt Counter Clockwise door blok 3

// Bitmaps Analoge blockdetectors bezetmelders
HAL(Bitmap,2100,8)         // create flags 2100..2107 // blockdetect latches
ALIAS(BD_D_2, 2100)        // Flag to indicate Helix Buitenring is occupied
ALIAS(BD_D_3, 2101)        // Helix binnenring
ALIAS(BD_S_1, 2102)        // Branchlijn dorp - station - havendorp
ALIAS(BD_S_2, 2103)        // Yard dal - havendorp
ALIAS(BD_S_3, 2104)        // Branchlijn dorp - havendorp
ALIAS(BD_S_4, 2105)        // Branchlijn dorp - havendorp
ALIAS(BD_S_5, 2106)        // Block #8 Parkeerspoor #5
ALIAS(BD_S_RIJ, 2107)      // Block #9 Doorrij spoor

// node 3
ALIAS(IR_D_1_5_BEZET, 2063)         // IR Sensor Visserdorp - dorp hoofdspoor bezet latch
ALIAS(IR_D_4_1_BEZET, 2064)         // IR Sensor Connectie spoor #1 Dorp bezet latch
ALIAS(IR_D_4_2_BEZET, 2065)         // IR Sensor Connectie spoor #1 Dal bezet latch
ALIAS(IR_D_1_4_BEZET, 2068)         // IR Sensor Haven - dorp hoofdspoor bezet latch

ALIAS(BD_D_4_CW, 2069)              // Trein rijdt Clockwise door blok 4
ALIAS(BD_D_4_CCW, 2070)             // Trein rijdt Counter Clockwise door blok 4
ALIAS(BD_D_5_CW, 2071)              // Trein rijdt Clockwise door blok 5
ALIAS(BD_D_5_CCW, 2072)             // Trein rijdt Counter Clockwise door blok 5

// Bitmaps Analoge blockdetectors bezetmelders
HAL(Bitmap,2095,3)                  // create flags 2095..2097 // blockdetect latches
ALIAS(BD_D_5, 2095)                 // Block #13 yard vissersdorp /dorp branchlijn
ALIAS(BD_D_4, 2096)                 // Block #10 Connectie dorp en hoofdsporen naar yard en helix dal 

// Bitmaps 3-weg wissel routes
HAL(Bitmap,2190,4)                  // create flags 2190..2193 // route latches
ALIAS(ROUTE_90, 2190)                // Route 90 Schaduwstation
ALIAS(ROUTE_91, 2191)                // Route 91 Helix binnenring
ALIAS(ROUTE_92, 2192)                // Route 92 Helix buitenring
ALIAS(ROUTE_93, 2193)                // Route 93 Yard dal

// Routes
ALIAS(ROUTE_1,1660)                 // Alias voor route 1660 
ALIAS(ROUTE_2,1661)                 // Alias voor route 1661
ALIAS(ROUTE_3,1662)                 // Alias voor route 1662
ALIAS(ROUTE_4,1663)                 // Alias voor route 1663
ALIAS(ROUTE_5,1664)                 // Alias voor route 1664
ALIAS(BD_D_4_UITRIT,1670)           // Alias voor komende van BD_D_4 
ALIAS(BD_D_5_UITRIT,1671)           // Alias voor komende van BD_D_5 

// Sequences en routes 
// ALIAS(BRANCH_DORP_KEERLUS,1600)     // Branchlijn dorp van oost naar west automation
// ALIAS(BRANCH_DORP_WEST_OOST,1601)   // Branchlijn dorp van west naar oost automation
// ALIAS(KEERLUS_NORMAAL,1900)         // Sequence to set reverse loop to normaal dcc signal
// ALIAS(KEERLUS_REVERSE,1901)         // Sequence to set reverse loop to reverse dcc signal

// Leds


// Motors