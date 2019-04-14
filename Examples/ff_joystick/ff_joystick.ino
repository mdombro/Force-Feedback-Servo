#include <Servo.h>
#include <FFServo.h>

const int sensor1 = A0;
const int sensor2 = A1;

float dt = 0.0167;
byte s1 = 1;
byte s2 = 2; 
float pos = 0;

Servo S1;
Servo S2; 

FFServo ff(2, dt, 1.5, 0, 180); 

void setup() {
	Serial.begin(9600);
  ff.config_servo(s1, -1);
  //ff.config_servo(s2, -1);
  
	// Initialize 2 servos and center them
	S1.attach(9);
	S2.attach(10);
	
	S1.write(90);
	S2.write(90);
	delay(200);  // wait for the servos to center
	
	for (int i = 0; i < 500; i++) {
		ff.servo_calibrate(analogRead(sensor1), s1);
		ff.servo_calibrate(analogRead(sensor2), s2);
		delay(10);
	}
	
}

void loop() {
	ff.force_update(analogRead(sensor1), s1);
	ff.force_update(analogRead(sensor2), s2);
	
	pos = ff.pos_update();
	
	S1.write(pos);
	S2.write(pos);
  Serial.println(analogRead(sensor2));
  Serial.print(" ");
	delayMicroseconds(16700);
}
