# ROS package to publish multiple RangeMsgs
- A ROS package for multiple ultrasonic sensor running simultaneously
- Publishing range msgs at around 5 hz
- Hardware: MB7380 HRXL-MaxSonar-WRT as ultrasonic sensor and Raspberry Pi as a main controller
- WiringPi Lib is used to create threads for each ultrasonic sensor
- UTs are connected to pi3 at pins
  - S0: Echo-17, Trig-27
  - S1: Echo-22, Trig-05
  - S2: Echo-06, Trig-13
  - S1: Echo-19, Trig-26
  - S1: Echo-21, Trig-20
- where: S0 is the left most and S4 is the right most

#### NOTE : *this package requires super-user permission to work because it is using WiringPi Library to crearte thresds for each ultrasonic sensor*
