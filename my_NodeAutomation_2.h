AUTOSTART
  LCD(0, "SilberBachTalBahn node #2")
  LCD(1,"")
  LCD(2,"")
  SCREEN(1, 1, "Status Display")
  PARSE("<C WIFI ON>")
  DELAY(500)
  PRINT("We kunnen verder")
  PARSE("<D NODE OFF>") // voor nu even, anders wordt alle node info gedumpt
  // Zet de analoge porten als input. Zonder dit lijkt het of 0 of het hangt
  IFLT(BD_D_2_SENSOR, 255) ENDIF
  IFLT(BD_D_3_SENSOR, 255) ENDIF
  IFLT(BD_S_1_SENSOR, 255) ENDIF
  IFLT(BD_S_2_SENSOR, 255) ENDIF
  IFLT(BD_S_3_SENSOR, 255) ENDIF
  IFLT(BD_S_4_SENSOR, 255) ENDIF
  DELAY(500)
  CALIBRATE_BLOCKSENSOREN()

  // Zet heartbeat signaal aan voor naar command station
  BLINK(HEARTBEAT_NODE_2,500,500)
DONE

// --- Continue loop voor uitlezen blockdetectors analoge ports
AUTOSTART SEQUENCE(2)
  // 2. Verwerk alle analoge ingangen in C++ (supersnel)
  PROCESS_BLOCKSENSOREN()
  DELAY(1000) 
FOLLOW(2)


//testje voor andere node heartbeat..
AUTOSTART SEQUENCE(3)
  ALIAS(REMOTE_NODE_1, 2500)
  HAL(Bitmap,2505,3)                // create flags 2505-2507 Remote Node On/Offline
  ALIAS(REMOTE_NODE_1_STATUS, 2505) // Bitmap Node 1 on/offline status
  ALIAS(REMOTE_NODE_1_LED, 15) //

  REMOTE_SENSOR(2500) // Heartbeat node 1
DONE

// simpele HeartBeat node 1 monitoring via led
// ONSENSOR(REMOTE_NODE_1)
//   IF(REMOTE_NODE_1) SET(REMOTE_NODE_1_LED) ELSE RESET(REMOTE_NODE_1_LED) ENDIF
// DONE

// Testje voor later met timeout functies
AUTOSTART SEQUENCE(5)
	ATTIMEOUT(REMOTE_NODE_1, 1000)
	  SET(REMOTE_NODE_1_LED)	// Node online
	IFTIMEOUT RESET(REMOTE_NODE_1_LED) PRINT("Node 1 offline")ENDIF // Node offline
	DELAY(500)
FOLLOW(5)