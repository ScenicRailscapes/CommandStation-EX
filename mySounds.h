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

/* Sound Bell mogelijkheden en register per loc, bv functie 3 (FON(3)) 
   op de Pico OBB loc is de bell, terwijl dat op de V60 functie 15 is.
*/
#define LOCO_SOUND_BELL                         \
  /* 1. Reset eerst de diesel-vlag */           \
  RESET(BIT_DIESEL)                             \
                                                \
  /* 2. Individuele loc bell-functies */        \
  IFLOCO(17) FON(3)  DELAY(2000) FOFF(3)  ENDIF \
  IFLOCO(13) FON(15) DELAY(2000) FOFF(15) ENDIF \
  IFLOCO(10) FON(3)  DELAY(2000) FOFF(3)  ENDIF \
  IFLOCO(9)  FON(4)  DELAY(2000) FOFF(4)  ENDIF \
                                                \
  /* 3. Markeer de diesels en zet de vlag */    \
  IFLOCO(4,7,8,18)                              \
    SET(BIT_DIESEL)                             \
    PRINT("Diesel geluiden hier")               \
  ENDIF                                         \
                                                \
  /* 4. Als het geen diesel was, is het stoom */\
  IFNOT(BIT_DIESEL)                             \
    PRINT("Stoom geluiden hier")                \
  ENDIF

/* Sound Long Horn mogelijkheden en register per loc, bv functie 15 (FON(15)) 
   op de Pico OBB loc is de long horn, terwijl dat op de V60 functie 8 is.
*/
 #define LOCO_SOUND_HORN                         \
   /* 1. Reset eerst de diesel-vlag */           \
  RESET(BIT_DIESEL)                              \
                                                 \ 
  IFLOCO(17) FON(15) DELAY (2000) FOFF(15) ENDIF \
  IFLOCO(13) FON(8)  DELAY (2000) FOFF(8)  ENDIF \
  IFLOCO(10) FON(2)  DELAY (2000) FOFF(2)  ENDIF \
  IFLOCO(9)  FON(2)  DELAY (2000) FOFF(2)  ENDIF \
                                                 \
  /* 3. Markeer de diesels en zet de vlag */    \
  IFLOCO(4,7,8,18)                              \
    SET(BIT_DIESEL)                             \
    PRINT("Diesel geluiden hier")               \
  ENDIF                                         \
                                                \
  /* 4. Als het geen diesel was, is het stoom */\
  IFNOT(BIT_DIESEL)                             \
    PRINT("Stoom geluiden hier")                \
  ENDIF
  


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