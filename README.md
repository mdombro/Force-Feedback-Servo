# Force Feedback Servo

An Arduino library to add force feedback to RC servos. With some additional hardware to measure the force applied to a servo arm, the Force Feedback Servo library will move a servo (or servos and multiple force sensors) in response to the measured force(s). 

The main application of this library is to allow the development of a RC plane control system that gives realtime force-feeback to the pilot's control joystick - to give the effect of flying an actual airplane. 

More details can be found at the Hackaday.io project [RC Plane Force-Feedback System](https://hackaday.io/project/164194-rc-plane-force-feedback-system). 

# Function Guide

### FFServo(num_servos, dt, velocity_gain, pos_lower_bound, pos_upper_bound)

**num_servos:** the number of servos to use in the system

**dt:** the interval of time between system updates - servo position commands/sensor readings

**pos_lower_bound:** the lower bound of the position to use for the servo control. (for example if using the Arduino servo library this value might be 0)

**pos_upper_bound:** the upper bound of the position to use for the servo control. (for Arduino servo library this might be 180)

<library usage guide soon> 

