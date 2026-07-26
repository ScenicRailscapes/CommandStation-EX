/* DFPLAYER Folder en file structuur. In de Effect ID's zijn de filenamen (of volgorde) op de SD kaart
   dus file 001.mp3 is altijd een horn/whistle. In de folder structuur wordt bepaald wat voor loc het is
   dus loc #6 is een diesel en in folder 6 staat een file 001.mp3 die hier een horn geluid is. 
   In de folder #15 staan de files voor een stoomtrein waarbij nu 001.mp3 een steamwhistle is.

   Gebruik: in EXRAIL de effectnaam oproepen eg: 'SOUND_BELL' 
   In de centrale sound engine wordt dan bekeken of het een soundloc is of DFPlayer.
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

  // Effects voor soundlocs 
#define SOUND_EFFECT(effect_id, duration_ms, volume, dfplayervpin) \
    STEALTH( playSoundEffect(loco, effect_id, duration_ms, volume, dfplayervpin); )

//      Effectnaam (EXRAIL Commando)          Effect ID   FON-FOFF delay DFPlayer volume, DFPlayervPIN   
#define SOUND_BELL                  SOUND_EFFECT(FX_BELL,      2000,     20, 10000)
#define SOUND_HORN                  SOUND_EFFECT(FX_WHISTLE_1, 2000,     25, 10000)
#define SOUND_BRAKE                 SOUND_EFFECT(FX_BRAKE,     0,        20, 10000)
#define SOUND_BLOWOUT               SOUND_EFFECT(FX_BLOWOUT,   1500,     20, 10000)

// Effects extra voor DFPlayer loc sounds. Bv een 2e whistle die via RANDOM opgeroepen kan worden
#define SOUND_HORN_LONG             SOUND_EFFECT(FX_WHISTLE_2, 4000,     25, 10000)
#define SOUND_CONDUCTOR_WHISTLE_1   SOUND_EFFECT(FX_CON_WHISTLE_1, 0,    25, 10000)
#define SOUND_CONDUCTOR_WHISTLE_2   SOUND_EFFECT(FX_CON_WHISTLE_2, 0,    25, 10000)
#define SOUND_OPTREKKEN             SOUND_EFFECT(FX_ACCEL,         0,    25, 10000)
#define SOUND_RIJDEN                SOUND_EFFECT(FX_CRUISE,        0,    25, 10000)
#define SOUND_AFREMMEN              SOUND_EFFECT(FX_DECEL,         0,    11, 10000)
#define SOUND_REMMEN                SOUND_EFFECT(FX_BRAKE,         0,    20, 10000)

// Effects voor dorpen en andere geluiden   Player#, folder, effect, volume
#define SOUND_KERKKLOKKEN_DISTANT   PLAYSND(1, 1, FX_CHURCHBELLS_1, 18)
#define SOUND_KERKKLOKKEN_NEAR      PLAYSND(2, 1, FX_CHURCHBELLS_2, 20)
#define SOUND_KERKKLOKKEN_TING      PLAYSND(1 , 1, FX_CHURCHBELLS_3, 15)


/* -------------------------------------------------------------
                      Centrale Sound-Engine
   ------------------------------------------------------------- */
STEALTH_GLOBAL(
  void playSoundEffect(uint16_t locoAddr, int effectId, int durationMs, int volume, int dfPlayerVpin) {
    if (locoAddr == 0) return; // Veiligheidscheck: geen loc actief

    // -------------------------------------------------------------
    // 1. CONTROLEREN OF HET EEN DCC SOUND-LOC IS (Functie mapping)
    //    Bij LOC #17 is dus een BELL functie 3 ->FON(3) 
    //    en bij LOC #13 Functie 15 =>FON(15)
    // -------------------------------------------------------------
    int soundFunc = -1; // -1 betekent: Geen DCC sound, gebruik DFPlayer

    switch (locoAddr) {
      case 17:
        if (effectId == FX_BELL)      soundFunc = 3;
        if (effectId == FX_WHISTLE_1) soundFunc = 17;
        if (effectId == FX_WHISTLE_2) soundFunc = 17;
        break;
      case 13:
        if (effectId == FX_BELL)      soundFunc = 15;
        if (effectId == FX_WHISTLE_1) soundFunc = 8;
        if (effectId == FX_WHISTLE_2) soundFunc = 8;
        break;
      case 10:
        if (effectId == FX_BELL)      soundFunc = 3;
        if (effectId == FX_WHISTLE_1) soundFunc = 2;
        if (effectId == FX_WHISTLE_2) soundFunc = 2;
        break;
      case 9:
        if (effectId == FX_BELL)      soundFunc = 4;
        if (effectId == FX_WHISTLE_1) soundFunc = 2;
        if (effectId == FX_WHISTLE_2) soundFunc = 2;
        break;
    }

    // -------------------------------------------------------------
    // 2. UITVOEREN: Fysieke Sound-loc OF DFPlayer
    // -------------------------------------------------------------
    if (soundFunc != -1) {
      // Het is een Sound-loc: Stuur DCC functie AAN (FON(#))
      DCC::setFn(locoAddr, soundFunc, true);

      // Als er een tijdsduur is opgegeven, na de delay weer UITzetten (FOFF(#))
      if (durationMs > 0) {
        delay(durationMs);
        DCC::setFn(locoAddr, soundFunc, false);
      }
    } 
    else {
      // Het is GEEN sound-loc: Gebruik de DFPlayer via IODevice
      // SD-Kaart structuur: Folder = LocAdres (/04, /05, /11 etc.), Track = /001.mp3, /002.mp3
      int track = effectId;
      //VPIN dfPlayerVpin; //= 10000; // VPin van de eerste DFPlayer

      // 1. Stel eerst de folder in: Folder = locoAddr
      IODevice::writeAnalogue(dfPlayerVpin, 0, locoAddr, DFPlayerBase::DF_FOLDER);

      // 2. Speel het geluid af: Track = track
      IODevice::writeAnalogue(dfPlayerVpin, track, volume, DFPlayerBase::DF_PLAY);
      // even controleren weer wat er zou moeten gebeuren, later verwijderen.
      //StringFormatter::lcd2(1, 6, F("Play: %3d Fol: %3d"), track, locoAddr); // debug
    }
  }
)