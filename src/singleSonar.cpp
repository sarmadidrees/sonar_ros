#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <wiringPi.h>

#include "ros/ros.h"
#include "ros/time.h"
#include "sensor_msgs/Range.h"

#define ECHO_0 0
#define ECHO_1 22
#define ECHO_2 06
#define ECHO_3 19
#define ECHO_4 21

volatile double distance0 = 0.0;
volatile double distance1 = 0.0;
volatile double distance2 = 0.0;
volatile double distance3 = 0.0;
volatile double distance4 = 0.0;
//volatile int x = 0;
//volatile int y = 0;
//volatile int z = 0;


void sonarCheck0 (void)
{
        volatile static long startTime = 0.0;
        if(digitalRead(ECHO_0) == HIGH){
	        startTime = micros();
		return;
	}

	if(digitalRead(ECHO_0) == LOW){
	        long travelTime = micros() - startTime;
	        distance0 = travelTime / 1000.0;
	       //x = 1;
	}
}

int setupWiringPi(void) {
        wiringPiSetup();
        pinMode(ECHO_0, INPUT);
        wiringPiISR (ECHO_0, INT_EDGE_BOTH, &sonarCheck0);
}

int main(int argc, char **argv) 
{
	setupWiringPi();

	ros::init(argc, argv, "range_msg");
	ros::NodeHandle nh;

	ros::Publisher sonar0_pub = nh.advertise<sensor_msgs::Range>("sonar0", 5);
	ros::Rate loop_rate(10);

	while (ros::ok())
	{
	sensor_msgs::Range rangeMsg;	
	rangeMsg.header.stamp = ros::Time::now();
	rangeMsg.header.frame_id = "/sonar0";
	rangeMsg.radiation_type = 0,                     //0=ultrasonic, 1=IR
	rangeMsg.field_of_view = 0.05;
	rangeMsg.min_range = 0.0;
	rangeMsg.max_range = 5.0;
	rangeMsg.range = distance0;
      //broadcastTransform(threadName)
      //RangeSensorPub.publish(rangeMsg)
	
	sonar0_pub.publish(rangeMsg);
    	ros::spinOnce();
    	loop_rate.sleep();
    	}

	return 0;
}
