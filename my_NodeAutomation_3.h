AUTOSTART
  LCD(0, "SilberBachTalBahn node #3")
  LCD(1,"")
  LCD(2,"")
  SCREEN(1, 1, "Status Display")
  PARSE("<C WIFI ON>")
  DELAY(500)
  PRINT("We kunnen verder")
  PARSE("<D NODE OFF>") // voor nu even, anders wordt alle node info gedumpt
  // Zet de analoge porten als input. Zonder dit lijkt het of 0 of het hangt
  IFLT(BD_HBU_SENSOR, 255)          ENDIF
  IFLT(BD_HBI_SENSOR, 255)          ENDIF
  IFLT(BD_DORP_STATION_SENSOR, 255) ENDIF
  IFLT(BD_D_4_SENSOR, 255)          ENDIF
  IFLT(BD_D_5_SENSOR, 255)          ENDIF
  DELAY(500)
  CALIBRATE_BLOCKSENSOREN()

  // Zet heartbeat signaal aan voor naar command station
  BLINK(HEARTBEAT_NODE_3,500,500)
DONE

// --- Continue loop voor uitlezen blockdetectors analoge ports
AUTOSTART SEQUENCE(2)
  // 2. Verwerk alle analoge ingangen in C++ (supersnel)
  PROCESS_BLOCKSENSOREN()
  DELAY(1000) 
FOLLOW(2)