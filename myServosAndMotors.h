/*
  This file contains EXRAIL setup and scripts for servos, motors, and other pwm hardware control such as lights and signals.
  It defines hardware abstraction layer (HAL) for various components like PCA9685 PWM driver,
*/


// Servos via PC9685 #1 (400-415)
SERVO_TURNOUT(1000, 400, 270, 200, Fast, HIDDEN) // links af deel 3-weg wissel - hidden voor alleen in route gebruik. Kan beschadigen al links en rechts elkaar tegen werken
SERVO_TURNOUT(1001, 401, 250, 160, Fast, HIDDEN) // rechtsaf deel 3-weg wissel
SERVO_TURNOUT(1002, 402, 260, 170, Fast, "S02 Yard dal - Helix buitenring")             // S02
SERVO_TURNOUT(1003, 403, 255, 180, Fast, "S03 Yard dal") // yard dal - terug naar vissersdorp   // S03
SERVO_TURNOUT(1004, 404, 250, 160, Fast, "S04 Yard oost")
SERVO_TURNOUT(1005, 405, 270, 200, Fast, "S05 Yard west")
SERVO_TURNOUT(1006, 406, 410, 310, Fast, "S06 Helix buitenring / dorp")
SERVO_TURNOUT(1007, 407, 410, 310, Fast, "S08 Branchlijn hoofdstation / Haven-dorp")    // S08

/* De 3 weg wissel heeft een speciale bediening. De servo's 1000 en 1001 moeten in specifieke volgorde worden bediend
 Links af: 1000 Close, 1001 Throw
 Rechtdoor: 1000 Throw, 1001 Close
 Rechts af: 1000 Throw, 1001 Throw
 Het beste werkt dat door 3 routes te definieren ipv de servo wissels aan te roepen, voor het gemak hier geplaatst
*/

// moeten deze een return krijgen ipv done zodat ze opgeroepen kunnen worden?
ROUTE (90,"Schaduwstation")
    THROW (1000) // links af deel 3-weg wissel
    THROW (1001) // rechts af deel 3-weg wissel
    DONE

ROUTE (91,"Helix binnenring")
    THROW (1000) // links af deel 3-weg wissel
    CLOSE (1001) // rechts af deel 3-weg wissel
    DONE
    //RETURN

ROUTE (92,"Helix buitenring")
    CLOSE (1000) // links af deel 3-weg wissel
    CLOSE (1001) // rechts af deel 3-weg wissel
    THROW (1002) // Helix buitenring
    //DONE
    RETURN

ROUTE(93, "Yard dal")
    CLOSE (1000) // links af deel 3-weg wissel
    CLOSE (1001) // rechts af deel 3-weg wissel
    CLOSE (1002) // Yard dal 
    DONE

ROUTE(94, "Rangeer op yard")
    CLOSE(1002) // Yard dal
    DONE

ROUTE(95, "Yard dal naar vissersdorp")
    CLOSE (1000) // links af deel 3-weg wissel
    CLOSE (1001) // rechts af deel 3-weg wissel
    CLOSE(1002) // Yard dal
    THROW (1003) // Yard dal naar vissersdorp
    DONE

ROUTE(96, "Helix CCW vissersdorp - hoofdstation")
    CLOSE (1007) // S08 Branchlijn hoofdstation / Haven-dorp
    CLOSE (1037) // S22 Dorp -> Vissersdorp station"
    THROW (1034) // S19 Haven -> dorp 
    THROW (1039) // 
    CLOSE (1024) // S13 -> hoofdstation
    DONE    

    // even checken
ROUTE(97, "Helix CCW dorp - hoofdstation - havendorp - helix CW")
    THROW (1007) // S08 Branchlijn hoofdstation / Haven-dorp
    CLOSE (1037) // S22 Dorp -> Vissersdorp station"
    THROW (1034) // S19 Haven -> dorp 
    THROW (1039) // 
    CLOSE (1024) // S13 -> hoofdstation
    DONE        

// Servos via PC9685 #2 (420-435)
// SERVO_TURNOUT(id, vpin, active_angle, inactive_angle, profile, "description") // profile: Instant, Fast, Medium, Slow, Bounce, NoPowerOff
SERVO_TURNOUT(1020, 420, 260, 170, Fast, "S09 SchaduwStat 1 en 2 links")
SERVO_TURNOUT(1021, 421, 270, 200, Fast, "S10 SchaduwStat 3 en 4 links")
SERVO_TURNOUT(1022, 422, 260, 190, Fast, "S11 SchaduwStat 5 en 6 links")
SERVO_TURNOUT(1023, 423, 250, 160, Fast, "S12 Helix binnenring / bergdorp station") // S12
SERVO_TURNOUT(1024, 424, 270, 170, Fast, "S13 Dorp branchlijn / brouwerij")         // S13

//CONFIGURE_SERVO(101,300,400,slow)
// Raar geval met turnigy 9g servo, lijkt 360 graden servo te zijn 150-360 ccw (360 langszaam) en 380-600 cw (380 langszaam), aanzetten met <z vpin>
// LEDS - pwm via PC9685 #2 (420-435) - EXRAIL Command: SET(vPin), terminal. command: <z vpin> 
CONFIGURE_SERVO(454, 360, 0, NoPowerOff)
CONFIGURE_SERVO(430, 1536, 0, NoPowerOff)

// Servos via PC9685 #3 (440-455)
SERVO_TURNOUT(1030, 440, 320, 210, Fast, "S15 SchaduwStat 1 en 2 rechts")   // S15
SERVO_TURNOUT(1031, 441, 290, 210, Fast, "S16 SchaduwStat 3 en 4 rechts")   // S16
SERVO_TURNOUT(1032, 442, 270, 190, Fast, "S17 SchaduwStat 5 en 6 rechts")   // S17
SERVO_TURNOUT(1033, 443, 250, 160, Fast, "S18 Locoshed / haven")            // S18
SERVO_TURNOUT(1034, 444, 330, 260, Fast, "S19 Haven - dorp branchlijn")     // S19 (defect??)
SERVO_TURNOUT(1035, 445, 350, 250, Fast, "S20 Main #1 / schaduwstation")    // S20 hoofdspoor 1 / schaduwstation
SERVO_TURNOUT(1036, 446, 280, 130, Fast, "S21 Dorp / dal")                  // S21
SERVO_TURNOUT(1037, 447, 250, 160, Fast, "S22 Dorp / Vissersdorp station")  // S22
SERVO_TURNOUT(1038, 448, 290, 220, Fast, "S23 Haven / main #1")             // S23
SERVO_TURNOUT(1039, 449, 335, 235, Fast, "S24 Haven - dorp / main #2")      // S24
SERVO_TURNOUT(1040, 450, 250, 150, Fast, "S25 main #1 / main #2")           // S25

// LEDS - pwm via PC9685 #3 (440-455) - EXRAIL Command: SET(vPin), terminal. command: <z vpin> 
CONFIGURE_SERVO(454, 2000, 0, NoPowerOff)                               // pwm lights locoshed dorp op 454
CONFIGURE_SERVO(455, 3000, 0, NoPowerOff)                               // pwm lights liechtenstein dorp op 455
// CONFIGURE_SERVO(111, 2437, 0, PCA9685::NoPowerOff)
// camservo op 454



// / Leds setup via PWM driver ... (vPin, pwm output value, 0, driver:: option)
// IODevice::configureServo(515,2048,0,PCA9685::NoPowerOff);  // Leds setup via PWM drive
// IODevice::configureServo(514,2048,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver
// IODevice::configureServo(513,2048,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver
// IODevice::configureServo(512,2048,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver
// IODevice::configureServo(511,1536,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver ---- leeg voor nu
// IODevice::configureServo(510,1536,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver 
// IODevice::configureServo(509,4095,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver
// IODevice::configureServo(506,2048,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver
// IODevice::configureServo(505,2800,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver
// // PWM Board 2 (onder plein) vpin 520-535
// IODevice::configureServo(522,1536,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver ---- leeg voor nu
// IODevice::configureServo(524,3000,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver
// IODevice::configureServo(526,700,0,PCA9685::NoPowerOff);   // Leds setup via PWM driver -- overgangssein.. iets minder fel
// IODevice::configureServo(527,1536,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver
// IODevice::configureServo(528,1536,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver
// IODevice::configureServo(529,1536,0,PCA9685::NoPowerOff);  // Leds setup via PWM driver
// IODevice::configureServo(530,1536,0,P<CA9685::NoPowerOff);  // Leds setup via PWM driver (Tardis)

// // Motors via PWM driver en LA928 motordrivers 
// // PWM Board 1 (onder pizzeria)
// IODevice::configureServo(507,3000,0,PCA9685::NoPowerOff);  // Santa motor
// IODevice::configureServo(508,250,0,PCA9685::NoPowerOff);   // Schaatsers motor op vijver. Kan ook voor servos gebruikt worden waarbij de output (PWM) aan moet blijven
// // PWM Board 2 (onder plein)
// IODevice::configureServo(520,260,0,PCA9685::NoPowerOff);   // Watermolen motor. Kan ook voor servos gebruikt worden waarbij de output (PWM) aan moet blijven
// IODevice::configureServo(521,2500,0,PCA9685::NoPowerOff);  // Skilift motor. Kan ook voor servos gebruikt worden waarbij de output (PWM) aan moet blijven
// IODevice::configureServo(525,310,0,PCA9685::NoPowerOff); // Langlauf ketting motor