#ifndef FFServo_h
#define FFServo_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


// This class calculates the a force feedback position for some number of servos
// All servos under an instance of this calss will be set to the same position
// Create more instances for different 'channels' or dimensions of movement
class FFServo {
	private:
		byte _numServos;
		int _posLowerBound;
		int _posUpperBound;
		float _sensorValue[64] = {0};
		//float lastSensorValue[64] = {0};
		float _centerValue[64] = {0};
		int _numAverageSamples[64] = {0}; // the number of samples being averaged to find the centerpoint for each servo
		int _forceDirection[64] = {0};
		int _forceDeadband = 10;
		float _dt = 0.02;
		float _velocityGain = 3.0;
		float _filterAlpha = 0.99;
		float _pos; 
		
	
	public: 
		// inputs: the number of servos in the system, the update period between samples
		// the gain used to modify force into a velocity
		// the lower and upper bounds allowed for the servo position
		// Set the initial configurations of the force feedback unit
		// ToDo: make the bounds floats to go with how the pos is a float
		FFServo(byte num_servos, float dt, float velocity_gain, int pos_lower_bound=0, int pos_upper_bound=180);
		
		FFServo();
		
		virtual ~FFServo();
		// ToDo: make sure order of arguments is consistent
		void begin(byte num_servos, float dt, float velocity_gain, int pos_lower_bound, int pos_upper_bound);
		
		void set_LPF(float alpha); // 0 - no updates to measurement, most filtering 1 - no filtering
		
		void set_force_deadband(int force);
		
		void servo_calibrate(int force_reading, byte servo_id);
		
		void force_update(int force_reading, byte servo_id); 

		float pos_update(void);
		
		void config_servo(byte servo_id, int force_direction); 
		
		float get_sensor_value(byte servo_id);

};

#endif // FFServo