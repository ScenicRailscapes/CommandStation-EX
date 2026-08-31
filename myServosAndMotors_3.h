/*
  This file contains EXRAIL setup and scripts for servos, motors, and other pwm hardware control such as lights and signals.
  It defines hardware abstraction layer (HAL) for various components like PCA9685 PWM driver,
*/


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
