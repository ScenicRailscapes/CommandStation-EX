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

// Deze zijn ingewikkelder.. moet keuzes laten maken welk spoor dus een toggle werkt niet
// Dat betekent dus een close voor beide is bv de bovenste route en en throw voor beide de lagere route ofzo
// kortom, uitzoeken voor bv spoor 1 of de S06 en S15 een close of throw moeten zijn
ONBUTTON(SWITCH_13)
  PRINT ("Button 13") 
  TOGGLE_TURNOUT(1009) // S09
  TOGGLE_TURNOUT(1015) // S15
DONE

ONBUTTON(SWITCH_14)
  PRINT ("Button 14")
  TOGGLE_TURNOUT(1010) // S10
  TOGGLE_TURNOUT(1016) // S16
DONE

ONBUTTON(SWITCH_15)
  PRINT ("Button 15")
  TOGGLE_TURNOUT(1011) // S11
  TOGGLE_TURNOUT(1017) // S17
DONE

ONBUTTON(SWITCH_16)
  PRINT ("Button 16")
  TOGGLE_TURNOUT(1012) // S12
  TOGGLE_TURNOUT(1018) // S18
DONE

