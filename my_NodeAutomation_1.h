AUTOSTART
  LCD(0, "SilberBachTalBahn node #1")
  LCD(1,"")
  LCD(2,"")
  SCREEN(1, 1, "Status Display")
  PARSE("<C WIFI ON>")
  //PARSE("<C WIFI NODE>") // Disable show on Engine Driver screen
  DELAY(5000)
  PRINT("We kunnen verder")
  PARSE("<D NODE OFF>") // voor nu even, anders wordt alle node info gedumpt
  DELAY(500)
  CALIBRATE_BLOCKSENSOREN()
DONE

// --- Continue loop voor uitlezen blockdetectors analoge ports
AUTOSTART SEQUENCE(2)
  // 2. Verwerk alle analoge ingangen in C++ (supersnel)
  PROCESS_BLOCKSENSOREN()
  DELAY(1000) 
FOLLOW(2)

AUTOSTART SEQUENCE(3)
  // Zet heartbeat signaal aan voor naar command station
  BLINK(HEARTBEAT_NODE_1,500,500)
  DELAYMINS(2)
  RESET(HEARTBEAT_NODE_1)
FOLLOW(3)

AUTOSTART SEQUENCE(4)
  // regelmatig broadcast alle shared sensors en wissels
  PARSE("<D SHARE>")
  DELAYMINS(7)
FOLLOW(4)

ROUTE (990, "Calibrate BlockSensoren")
  CALIBRATE_BLOCKSENSOREN()
DONE