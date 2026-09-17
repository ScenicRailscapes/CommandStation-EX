// Toggled met de 3-weg wissel tussen schaduwstation, helix binnen, helixbuiten en yard
ONBUTTON(SWITCH_1)
  PRINT ("Button 1")
  IF(ROUTE_90) // 90 geselecteerd, nu naar 91 toggle
    RESET(ROUTE_90)
    RESET(ROUTE_92)
    RESET(ROUTE_93)
    SET(ROUTE_91)
    PRINT("Route 91 geselecteerd")
    DONE
  ENDIF
  IF(ROUTE_91) // 91 geselecteerd, nu naar 92 toggle
    RESET(ROUTE_90)
    RESET(ROUTE_91)
    RESET(ROUTE_93)
    SET(ROUTE_92)
    PRINT("Route 92 geselecteerd")
    DONE
  ENDIF
  IF(ROUTE_92) // 92 geselecteerd, nu naar 93 toggle
    RESET(ROUTE_90)
    RESET(ROUTE_91)
    RESET(ROUTE_92)
    SET(ROUTE_93)
    PRINT("Route 93 geselecteerd")
    DONE
  ENDIF
  IF(ROUTE_93) // 93 geselecteerd, nu naar 90 toggle
    RESET(ROUTE_91)
    RESET(ROUTE_92)
    RESET(ROUTE_93)
    SET(ROUTE_90)
    PRINT("Route 90 geselecteerd")
    DONE
  ENDIF
DONE

ONBUTTON(SWITCH_2)
  PRINT ("Button 2")
  TOGGLE_TURNOUT(1006) // S06 
DONE

ONBUTTON(SWITCH_3)
  PRINT ("Button 3")
  TOGGLE_TURNOUT(1007) // S07
DONE

ONBUTTON(SWITCH_4)
  PRINT ("Button 4")  
  TOGGLE_TURNOUT(1018) // S18
DONE

ONBUTTON(SWITCH_5)
  PRINT ("Button 5")
  TOGGLE_TURNOUT(1019) // S19
DONE

ONBUTTON(SWITCH_6)
  PRINT ("Button 6")
  TOGGLE_TURNOUT(1020) // S20
DONE

ONBUTTON(SWITCH_7)
  PRINT ("Button 7")
  TOGGLE_TURNOUT(1021) // S21
DONE

ONBUTTON(SWITCH_8)
  PRINT ("Button 8")
  TOGGLE_TURNOUT(1022) // S22
DONE

ONBUTTON(SWITCH_9)
  PRINT ("Button 9")
  TOGGLE_TURNOUT(1023) // S23
DONE

ONBUTTON(SWITCH_10)
  PRINT ("Button 10")
  TOGGLE_TURNOUT(1024) // S24
DONE

ONBUTTON(SWITCH_11)
  PRINT ("Button 11")
  TOGGLE_TURNOUT(1025) // S25
DONE

ONBUTTON(SWITCH_12)
  PRINT ("Button 12")
  TOGGLE_TURNOUT(1013) // S13
DONE

// Schaduwstation wissels

ONBUTTON(SWITCH_13)   // schaduwstation spoor #1 en #2
  PRINT("Button 13") 
  THROW(1017)
  THROW(1016)
  THROW(1015)

  CLOSE(1009)
  CLOSE(1010)
  CLOSE(1011)  
DONE

ONBUTTON(SWITCH_14)   // schaduwstation spoor #3 en #4
  PRINT("Button 14")
  THROW(1017)
  THROW(1016)
  CLOSE(1015)

  THROW(1009)
  CLOSE(1010)
  CLOSE(1011)
DONE

ONBUTTON(SWITCH_15)   // schaduwstation spoor #5
  PRINT("Button 15")
  THROW(1017)
  CLOSE(1016)
  CLOSE(1015)

  THROW(1009)
  THROW(1010)
  CLOSE(1011)
DONE

ONBUTTON(SWITCH_16) // schaduwstation doorrijspoor
  PRINT("Button 16")
  CLOSE(1017)
  CLOSE(1016)
  CLOSE(1015)
  
  THROW(1009)
  THROW(1010)
  THROW(1011)
DONE

