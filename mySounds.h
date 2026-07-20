// Sounds on SD
// Player Folder  File  Description
  //0 2 1 20 is long whistle steam
  //0 3 1 20 is long horn diesel
  //0 4 1 20 is break
  //0 5 1 20 is whistle, station sound en vertrek diesel
  //0 6 1 20 is meerdere horn, voorbijgaand diesel
  //0 1 2 20 is vertek steam
  //0 2 2 20 is meerdere whistle, voorbijgaand stoom
  //0 3 2 20 zelfde als voorgaand heel snel
  //0 4 2 20 stoomrelease
  //0 5 2 20 hufpuf voorbij
  //0 6 2 20 hufpuf vertrek
  //0 7 2 20 overgang ding ding, voorbijgaande steam
  //0 1 3 20 mountain steam whistle
  //0 2 3 20 mountain steam whistle 
  //0 3 3 20 long whistle steam
  //0 4 3 20 whistle steam
  //0 5 3 20 whistle steam
  //0 6 3 20 short horn diesel / electric
  //0 2 4 20 lomg horn diesel ding ding voorbijgaand

/* ====================================================================
   Sound Bell mogelijkheden en register per loc, bv functie 3 (FON(3)) 
   op de Pico OBB loc is de bell, terwijl dat op de V60 functie 15 is.
  ===================================================================== */
#define LOCO_SOUND_BELL                           \
  /* 1. Reset eerst de diesel-vlag */             \
  RESET(BIT_DIESEL)                               \
  RESET(BIT_SOUNDLOC)                             \  
                                                  \
  /* 2. Individuele loc bell-functies */          \
  IFLOCO(17,13,10,9)  /* SoundLocs */             \
    SET(BIT_SOUNDLOC)                             \
    IFLOCO(17) FON(3)  DELAY(2000) FOFF(3)  ENDIF \
    IFLOCO(13) FON(15) DELAY(2000) FOFF(15) ENDIF \
    IFLOCO(10) FON(3)  DELAY(2000) FOFF(3)  ENDIF \
    IFLOCO(9)  FON(4)  DELAY(2000) FOFF(4)  ENDIF \
  ENDIF                                           \
                                                  \
  /* 3. Markeer de diesels en zet de vlag */      \
  IFLOCO(4,6,8,18)                                \
    IFNOT(BIT_SOUNDLOC)                           \
      SET(BIT_DIESEL)                             \
      PLAYSND(0,3,6,20) DELAY(300) PLAYSND(0,3,6,20)\
    ENDIF                                         \
  ENDIF                                           \
                                                  \
  /* 4. Als het geen diesel was, is het stoom */  \
  IFNOT(BIT_DIESEL)                               \
    IFNOT(BIT_SOUNDLOC)                           \
      PLAYSND(0,2,1,20)                           \
    ENDIF                                         \
  ENDIF

/* ====================================================================
   Sound Long Horn mogelijkheden en register per loc, bv functie 15 (FON(15)) 
   op de Pico OBB loc is de long horn, terwijl dat op de V60 functie 8 is.
   ==================================================================== */
 #define LOCO_SOUND_HORN                           \
   /* 1. Reset eerst de diesel-vlag */             \
  RESET(BIT_DIESEL)                                \
  RESET(BIT_SOUNDLOC)                              \
                                                   \
  /* 2. Individuele loc bell-functies */           \
  IFLOCO(17,13,10,9)  /* SoundLocs */              \
    SET(BIT_SOUNDLOC)                              \
    IFLOCO(17) FON(17) DELAY (2000) FOFF(17) ENDIF \
    IFLOCO(13) FON(8)  DELAY (2000) FOFF(8)  ENDIF \
    IFLOCO(10) FON(2)  DELAY (2000) FOFF(2)  ENDIF \
    IFLOCO(9)  FON(2)  DELAY (2000) FOFF(2)  ENDIF \
  ENDIF                                            \
                                                   \
  /* 3. Markeer de diesels en zet de vlag */       \
  IFLOCO(4,6,8,18)                                 \
    IFNOT(BIT_SOUNDLOC)                            \
      SET(BIT_DIESEL)                              \
      PRINT("Diesel geluiden hier")                \
      PLAYSND(0,1,3,20)                        \
    ENDIF                                          \
  ENDIF                                            \
                                                   \
  /* 4. Als het geen diesel was, is het stoom */   \
  IFNOT(BIT_DIESEL)                                \
    IFNOT(BIT_SOUNDLOC)                            \
      PRINT("Stoom geluiden hier")                 \
      PLAYSND(0,1,2,20)                        \
    ENDIF                                          \
  ENDIF



/* =========================================================================
   Geen sound maar wat speciale functies bij locs (downlights, baangeluiden)
   ========================================================================= */
  
 #define LOCO_SPECIAL_SET                             \
  IFLOCO(17,13)                                       \
    IFLOCO(17) FON(8) FON(4) ENDIF                    \
    IFLOCO(13) FON(10) FON(14) FON(22) FON(23)  ENDIF \
  ENDIF