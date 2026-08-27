/* DFPLAYER Folder en file structuur. In de Effect ID's zijn de filenamen (of volgorde) op de SD kaart
   dus file 001.mp3 is altijd een horn/whistle. In de folder structuur wordt bepaald wat voor loc het is
   dus loc #6 is een diesel en in folder 6 staat een file 001.mp3 die hier een horn geluid is. 
   In de folder #15 staan de files voor een stoomtrein waarbij nu 001.mp3 een steamwhistle is.

   Gebruik: in EXRAIL de effectnaam oproepen eg: 'SOUND_BELL' 
   In de centrale sound engine wordt dan bekeken of het een soundloc is of DFPlayer.

   ToDO: de DCC::setFn(19, 2, true); werkt niet, heel vreemd want de console log geeft
   exact dezelfde output <l 19 0 128 4> als dat je het via FON(19 2 1) geeft of via een throttle. Waarom werkt dit niet?
*/
  //    Effect ID's       Filenaam (.mp3)
#define FX_WHISTLE_1      1
#define FX_WHISTLE_2      2
#define FX_BELL           3
#define FX_CON_WHISTLE_1  4
#define FX_CON_WHISTLE_2  5
#define FX_BLOWOUT        7
#define FX_ACCEL          8
#define FX_CRUISE         9
#define FX_DECEL          10
#define FX_BRAKE          11
#define FX_CHURCHBELLS_1  5
#define FX_CHURCHBELLS_2  1
#define FX_CHURCHBELLS_3  3

#define SOUND_EFFECT(effect_id, duration_ms, volume, dfplayervpin) \
    STEALTH( playSoundEffect(loco, effect_id, volume, dfplayervpin, true); ) \
    DELAY(duration_ms) \
    STEALTH( playSoundEffect(loco, effect_id, volume, dfplayervpin, false); )


//      Effectnaam (EXRAIL Commando)          Effect ID   FON-FOFF delay DFPlayer volume, DFPlayervPIN   
#define SOUND_BELL                  SOUND_EFFECT(FX_BELL,           5000, 20, 10000)
#define SOUND_HORN                  SOUND_EFFECT(FX_WHISTLE_1,      2000, 25, 10000)
#define SOUND_BRAKE                 SOUND_EFFECT(FX_BRAKE,          5000, 20, 10000)
#define SOUND_BLOWOUT               SOUND_EFFECT(FX_BLOWOUT,        1500, 20, 10000)
#define SOUND_HORN_LONG             SOUND_EFFECT(FX_WHISTLE_2,      5000, 25, 10000)
#define SOUND_CONDUCTOR_WHISTLE_1   SOUND_EFFECT(FX_CON_WHISTLE_1,  2000, 25, 10000)
#define SOUND_CONDUCTOR_WHISTLE_2   SOUND_EFFECT(FX_CON_WHISTLE_2,  2000, 25, 10000)

// Effects extra voor DFPlayer loc sounds. Bv een 2e whistle die via RANDOM opgeroepen kan worden
// Voor effecten die continu moeten spelen of geen auto-off nodig hebben
#define SOUND_START(effect_id, volume, dfplayervpin) \
    STEALTH( playSoundEffect(loco, effect_id, volume, dfplayervpin, true); )

#define SOUND_STOP(effect_id, dfplayervpin) \
    STEALTH( playSoundEffect(loco, effect_id, 0, dfplayervpin, false); )

#define SOUND_OPTREKKEN             SOUND_START(FX_ACCEL, 25, 10000)
#define SOUND_RIJDEN                SOUND_START(FX_CRUISE, 25, 10000)
#define SOUND_AFREMMEN              SOUND_START(FX_DECEL, 11, 10000)
#define SOUND_REMMEN                SOUND_START(FX_BRAKE, 20, 10000)

// Effects voor dorpen en andere geluiden   Player#, folder, effect, volume
#define SOUND_KERKKLOKKEN_DISTANT   PLAYSND(1, 1, FX_CHURCHBELLS_1, 18)
#define SOUND_KERKKLOKKEN_NEAR      PLAYSND(2, 1, FX_CHURCHBELLS_2, 20)
#define SOUND_KERKKLOKKEN_TING      PLAYSND(1 , 1, FX_CHURCHBELLS_3, 15)
