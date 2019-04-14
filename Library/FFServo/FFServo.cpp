#include <Arduino.h>
#include <FFServo.h>

FFServo::FFServo(byte num_servos, float dt, float velocity_gain, int pos_lower_bound, int pos_upper_bound) {
	begin(num_servos, dt, velocity_gain, pos_lower_bound, pos_upper_bound);	
}


FFServo::FFServo() {
}

FFServo::~FFServo() {
}

void FFServo::begin(byte num_servos, float dt, float velocity_gain, int pos_lower_bound, int pos_upper_bound) {
	_numServos = num_servos;
	_dt=dt;
	_velocityGain = velocity_gain;
	_posLowerBound = pos_lower_bound;
	_posUpperBound = pos_upper_bound;
	_pos = ((float)pos_lower_bound + (float)pos_upper_bound) / 2.0;
	
	for (int i = 1; i < 64; i++) {
		_forceDirection[i] = 1;
	}
}

void FFServo::servo_calibrate(int force_reading, byte servo_id) {
	_centerValue[servo_id] = ((float)force_reading + (float)_numAverageSamples[servo_id]*_centerValue[servo_id])/((float)_numAverageSamples[servo_id]+1.0);
	_numAverageSamples[servo_id] += 1;
} 

void FFServo::force_update(int force_reading, byte servo_id) {
	float force = (float)_forceDirection[servo_id] * ((float)force_reading - _centerValue[servo_id]);
	_sensorValue[servo_id] = _sensorValue[servo_id] + _filterAlpha*(force-_sensorValue[servo_id]);
	//lastSensorValue[servo_id] = sensorValue[servo_id];
	//sensorValue[servo_id] = force_reading;
}

float FFServo::pos_update(void) {
	float F = 0;
	float v;
	
	for (int i = 0; i < _numServos; i++) {
		F += _sensorValue[i+1];
	}
	
	if (fabs(F) < (float)_forceDeadband) {
		F = 0;  // Stop the system from jogging slowly from noise
	}
	
	v = F*_velocityGain;
	_pos = _pos + _dt*v; 
	_pos = constrain(_pos, _posLowerBound, _posUpperBound);
	return _pos;
}

void FFServo::set_LPF(float alpha) {
	_filterAlpha = alpha;
}

void FFServo::set_force_deadband(int force) {
	_forceDeadband = force;
}

void FFServo::config_servo(byte servo_id, int force_direction) {
	_forceDirection[servo_id] = force_direction;
}

float FFServo::get_sensor_value(byte servo_id) {
	return _sensorValue[servo_id];
}

float fabs(float number) {
	if (number > 0) {
		return number;
	} else { 
		return -1.0*number;
	}
}

byte FFServo::getnum() {
	return _numServos;
}