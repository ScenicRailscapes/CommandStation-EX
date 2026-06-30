// Sounds on SD
// Player Folder  File  Description
//  1     01      001   Depart Electric
//  1     01      002   Pass
//  1     01      003   Arrive
//  1     01      004   Arrive 2 breaks
//  1     01      005   Depart 2 wistle and station sounds
//  1     01      007   Pass 2 (long with bells)

//  1     02      001   Depart Steam
//  1     02      002   Pass
//  1     02      003   Arrive
//  1     02      004   Stop
//  1     02      005   Pass 2
//  1     02      006   Depart 2
//  1     02      007   Pass 3

//  1     03      001   Whistle Steam mountain
//  1     03      002   Whistle Steam mountain
//  1     03      003   Whistle Steam passbye 
//  1     03      004   Whistle Steam small
//  1     03      005   Whistle electric 
//  1     03      006   Horn Diesel

//  1     04      001   
//  1     04      002   Pass Diesel
//  1     04      003   Arrive Diesel

// Secuence 150 play Departure
SEQUENCE(150)
  IF (SOUND)
    IF (ELEC_LOC_ACTIVE)
      IFRANDOM(50)
        PLAYSND(10000,1,1,18)              // Set folder to 01 player 1, play 001 (Departure Elec loco)
      ELSE
        PLAYSND(10000,1,5,18)             // Set folder to 01 player 1, play 005 (Departure Elec loco)  
      ENDIF
    ENDIF
    IF (STOOM_LOC_ACTIVE)
      IFRANDOM(50) 
        PLAYSND(10000,2,1,16)             // Set folder to 02 player 1, play 001 (PassThrough Elec loco)
      ELSE
        PLAYSND(10000,2,6,16)              // Set folder to 02 player 1, play 006 (PassThrough Elec loco)
      ENDIF
    ENDIF
  ENDIF // sound
RETURN

// Secuence 151 play Pass Through station
SEQUENCE(151)
  IF(SOUND)
    IF (ELEC_LOC_ACTIVE)
      IFRANDOM(50)    
        PLAYSND(10000,1,2,18)             // Set folder to 01 player 1, play 002 (PassThrough Elec loco)
      ELSE
        PLAYSND(10000,1,7,18)              // Set folder to 01 player 1, play 007 (PassThrough Elec loco)      
      ENDIF
    ENDIF
    IF (STOOM_LOC_ACTIVE)
      IFRANDOM(50) // kan naar 33% en een 3e pass geluid
        PLAYSND(10000,2,2,16)     // Set folder to 02 player 1
        PLAYSND(10000,2,15,16)      // Play 002 (PassThrough Elec loco)
      ELSE
        PLAYSND(10000,2,2,16)     // Set folder to 02 player 1
        PLAYSND(10000,2,14,16)      // Play 005 (PassThrough Elec loco)  
      ENDIF
    ENDIF
    IF (DIESEL_LOC_ACTIVE)
      PLAYSND(10000,4,2,18)      // Play 002 (PassThrough Diesel loco)
    ENDIF    
  ENDIF // sound
RETURN

// Secuence 152 play arrival
SEQUENCE(152)
  IF(SOUND)
    IF (ELEC_LOC_ACTIVE)
      IFRANDOM(50)
        PLAYSND(10000,1,3,18)              // Set folder to 01 player 1, play 003 (Arrival Elec loco)
      ELSE
        PLAYSND(10000,1,4,18)              // Set folder to 01 player 1, play 004 (Arrival Elec loco)      
      ENDIF
    ENDIF
    IF (STOOM_LOC_ACTIVE)
      PLAYSND(10000,2,3,16)     // Set folder to 02 player 1
      PLAYSND(10000,2,18,16)      // Play 003 (Arrival Steam loco)
    ENDIF
    IF (DIESEL_LOC_ACTIVE)
      PLAYSND(10000,4,3,18)      // Play 003 (Arrival Diesel loco)
    ENDIF        
  ENDIF // sound
RETURN

// Secuence 153 play stop
SEQUENCE(153)
  IF(SOUND)
    //  IF (ELEC_LOC_ACTIVE)
    //   PLAYSOUND(10000,0,1,FOLDER)     // Set folder to 01 player 1
    //   PLAYSOUND(10000,4,15,PLAY)      // Play 043 (Stop Elec loco)
    //  ENDIF
    IF (STOOM_LOC_ACTIVE)
      PLAYSND(10000,2,2,16)     // Set folder to 02 player 1
      PLAYSND(10000,2,10,16)      // Play 004 (Stop Steam loco)
    ENDIF
  ENDIF // sound
RETURN



// Test troep voor de I2CDFPlayer, werkt nu alleen op Uart 0 helaas
ONTHROW(9102)    
  PRINT("Play folder 1 Eloks")
  PLAYSND(10000,1,15,18)
  //WAITFOR(10000)                 // wait for playing stops 
  DELAY(6000)
  PRINT("Play folder 2 Steam")
  PLAYSND(10000,2,15,16) 
  DELAY(6000)
  PRINT("Play folder 3 Diesel")
  PLAYSND(10000,4,15,18)   
DONE
ONCLOSE(9102)
  PRINT("DFPLayer")
  PLAY_RESET(10000) // stop playing
  DELAY(1000)
DONE

ONTHROW(9103)
  PRINT("Play folder 2 Steam, #1")
  PLAYSND(10001,2,1,16) 
  DELAY(9000)
  PRINT("Play folder 2 Steam, #2")
  PLAYSND(10001,2,2,16) 
  DELAY(9000)
  PRINT("Play folder 2 Steam, #3")
  PLAYSND(10001,2,3,16) 
  DELAY(9000)
  PRINT("Play folder 2 Steam, #4")
  PLAYSND(10001,2,4,16) 
  DELAY(9000)
  PRINT("Play folder 2 Steam, #5")
  PLAYSND(10001,2,5,16) 
  DELAY(9000)
  PRINT("Play folder 2 Steam, #6")
  PLAYSND(10001,2,6,16) 
  DELAY(9000)     
  PRINT("Play folder 3 Steam, #1")
  PLAYSND(10001,3,1,20)        
DONE
ONCLOSE(9103)
  PRINT("DFPLayer")
  PLAY_RESET(10001) // stop playing
  DELAY(1000)
DONE


ONTHROW(9104)
  PRINT("Play folder 2 Steam, #1")
  PLAYSND(10002,1,6,20) 
  DELAY(9000)
  PRINT("Play folder 2 Steam, #2")
  PLAYSND(10002,1,7,20) 
  DELAY(9000)
  PRINT("Play folder 2 Steam, #3")
  PLAYSND(10002,1,8,20) 
  DELAY(9000)
  PRINT("Play folder 2 Steam, #4")
  PLAYSND(10002,1,9,20) 
  DELAY(9000)
  PRINT("Play folder 2 Steam, #5")
  PLAYSND(10002,2,5,20) 
  DELAY(9000)
  PRINT("Play folder 2 Steam, #6")
  PLAYSND(10002,1,4,16) 
  DELAY(9000)     
  PRINT("Play folder 3 Steam, #1")
  PLAYSND(10002,1,5,20)        
DONE
ONCLOSE(9104)
  PRINT("DFPLayer")
  PLAY_RESET(10002) // stop playing
  DELAY(1000)
DONE