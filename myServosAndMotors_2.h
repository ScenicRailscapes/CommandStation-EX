/*
  This file contains EXRAIL setup and scripts for servos, motors, and other pwm hardware control such as lights and signals.
  It defines hardware abstraction layer (HAL) for various components like PCA9685 PWM driver,
*/


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
