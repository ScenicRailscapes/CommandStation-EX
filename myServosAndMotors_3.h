/*
  This file contains EXRAIL setup and scripts for servos, motors, and other pwm hardware control such as lights and signals.
  It defines hardware abstraction layer (HAL) for various components like PCA9685 PWM driver,
*/


// Servos via PC9685 #1 (400-415)
SERVO_TURNOUT(1000, 400, 240, 160, Fast, HIDDEN) // links af deel 3-weg wissel - hidden voor alleen in route gebruik. Kan beschadigen al links en rechts elkaar tegen werken
SERVO_TURNOUT(1001, 401, 240, 160, Fast, HIDDEN) // rechtsaf deel 3-weg wissel
SERVO_TURNOUT(1002, 402, 260, 170, Fast, "S02 Yard dal - Helix buitenring")             // S02
SERVO_TURNOUT(1003, 403, 255, 180, Fast, "S03 Yard dal") // yard dal - terug naar havendorp   // S03
SERVO_TURNOUT(1004, 404, 250, 160, Fast, "S04 Yard oost")
SERVO_TURNOUT(1005, 405, 270, 200, Fast, "S05 Yard west")
SERVO_TURNOUT(1006, 406, 390, 330, Fast, "S06 Helix buitenring / dorp")                 // S06
SERVO_TURNOUT(1007, 407, 410, 250, Fast, "S07 Branchlijn hoofdstation / Haven-dorp")    // S07