#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "src/FFServo/FFServo.h"

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

const int sensor1 = A0;
const int sensor2 = A1;

float dt = 0.0167;
byte s1 = 1;
byte s2 = 2; 
float pos = 0;

FFServo ff(1, dt, 1.5, SERVOMIN, SERVOMAX); 

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  ff.config_servo(s1, -1);
  
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  // Initialize 2 servos and center them
  pwm.setPWM(5,0,(SERVOMIN+SERVOMAX)/2.0);
  pwm.setPWM(6,0,(SERVOMIN+SERVOMAX)/2.0);
  delay(200);  // wait for the servos to center
  
  for (int i = 0; i < 500; i++) {
    ff.servo_calibrate(analogRead(sensor1), s1);
    //ff.servo_calibrate(analogRead(sensor2), s2);
    delay(10);
  }
  
}

void loop() {
  ff.force_update(analogRead(sensor1), s1);
  //ff.force_update(analogRead(sensor2), s2);
  
  pos = ff.pos_update();
  
  pwm.setPWM(5, 0, pos);
  pwm.setPWM(6, 0, pos);
  delayMicroseconds(16700);
}
