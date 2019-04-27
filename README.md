# Force Feedback Servo

An Arduino library to add force feedback to RC servos. With some additional hardware to measure the force applied to a servo arm, the Force Feedback Servo library will move a servo (or servos and multiple force sensors) in response to the measured force(s). 

The main application of this library is to allow the development of a RC plane control system that gives realtime force-feeback to the pilot's control joystick - to give the effect of flying an actual airplane. 

More details can be found at the Hackaday.io project [RC Plane Force-Feedback System](https://hackaday.io/project/164194-rc-plane-force-feedback-system). 

# Function Guide

### FFServo(byte num_servos, float dt, float velocity_gain, int pos_lower_bound, int pos_upper_bound)
Initializes the instance of the class. Note a maximum of 63 servos can be used per class instance.

**num_servos:** The number of servos to use in the system

**dt:** The interval of time between system updates - servo position commands/sensor readings

**velocity_gain:** Proportionality coefficient for the force on a servo. This value controls how quickly a servo will react to a particular force. 

**pos_lower_bound:** The lower bound of the position to use for the servo control. (for example if using the Arduino servo library this value might be 0)

**pos_upper_bound:** The upper bound of the position to use for the servo control. (for Arduino servo library this might be 180)

### void config_servo(byte servo_id, int force_direction)
Setup each servo in the system to rotate correctly with respect to the force sensor. The servo may be set up so that there is a positive feedback loop - the servo rotates into the force sensor, causing higher force readings, driving the servo harder, etc. 

**servo_id:** Every servo and force sensor pair has an ID to keep track of configuration and force updates. Servo IDs are determined solely from the number of servos specified for the system. IDs start from 1. 
Note that nothing explicitly ties a servo ID back to a physical servo or pin number or some such. The association can be kept track with variable names or possibly an array or struct with the correct values. 

**force_direction:** Set the servo rotation direction with respect to the force direction. Has a value of 1 or -1. This argument controls the sign of the force measurements, virtually swapping the direction of force readings from the sensor. 
Note: This may later be turned into direction and also a gain setting, or the gain setting may be added as a seperate argument

Needed: A method to reverse the actual servo rotation direction, in case the control direction is swapped. 

### void servo_calibrate(int force_reading, byte servo_id)
At startup a measurement is done for the unloaded readings of the force sensor. This is to get the 'midpoint' of the force sensor. This value will be subtracted from future readings to get both the direction and magnitude of the actual force on the servo. 

**force_reading:** Raw force sensor reading. In general this will be an Arduinno ADC reading. 

**servo_id:** ID of the servo and force sensor pair. 

### void force_update(int force_reading, byte servo_id)
Updates the force measurements for all servos in the system. This function must be called for each servo defined for the system first before calling pos_update, otherwise not all the force readings will be taken into consideration. 

**force_reading:** Raw force sensor measurement. Midpoint compensation is handled by the class. 

**servo_id:** ID of the servo and force sensor pair. 

### float pos_update()
Computes the new servo position given the force sensor updates and returns a number between pos_lower_bound and pos_upper_bound. Note that all servos in the system always have the same position, so this value will be written to all servos by whatever method you choose. 

### void set_LPF(float alpha)
There is an internal low pass filter on the force readings to help smooth out the readings a bit. This function sets the strength of the low pass filter. Setting alpha to 0 means complete filtering and no updates will ever be made to the force readings. Setting alpha to 1 means absolutely no filtering and only the raw force sensor values will be used. Values in between will be a mix of the two extremes. 

**alpha:** Low pass filter coefficient. Vlaue between 0 and 1, 0 for all filtering, 1 for on filtering. 

### void set_force_deadband(int force)
Sets the width of the deadband around the measured midpoint value. This is to help minimize the system jogging slowly due to measurement noise and other randomness. The 'units' of this value will be the same as the force sensor. 

**force:** Desired maximum force to be ignored when computing new servo positions. 

### float get_sensor_value(byte servo_id)
Returns the force sensor value for a particular servo. Useful for debugging. 

**servo_id:** ID of the servo and force sensor pair. 

<library usage guide soon> 

