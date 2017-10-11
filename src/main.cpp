#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <wiringPi.h>

#include "ros/ros.h"
#include "ros/time.h"
#include "sensor_msgs/Range.h"

#define ECHO_0 0
#define ECHO_1 3
#define ECHO_2 22
#define ECHO_3 24
#define ECHO_4 29

#define FOV 0.5

volatile double distance0 = 0.0;
volatile double distance1 = 0.0;
volatile double distance2 = 0.0;
volatile double distance3 = 0.0;
volatile double distance4 = 0.0;

//volatile int x = 0;
//volatile int y = 0;
//volatile int z = 0;

sensor_msgs::Range rangeMsg0;
sensor_msgs::Range rangeMsg1;
sensor_msgs::Range rangeMsg2;
sensor_msgs::Range rangeMsg3;
sensor_msgs::Range rangeMsg4;

void sonarCheck0 (void)
{
	volatile static double distance0_P = 0.30;
        volatile static long startTime0 = 0.0;
        if(digitalRead(ECHO_0) == HIGH){
	        startTime0 = micros();
		return;
	}

	if(digitalRead(ECHO_0) == LOW){
	        long travelTime0 = micros() - startTime0;
	        distance0 = travelTime0 / 1000.0;
		if (distance0 < 0.30) distance0 = 0.30;
		else if (distance0 > 5.00) distance0 = distance0_P;
		distance0_P = distance0;
	       //x = 1;
	}
}

void sonarCheck1 (void)
{
	volatile static double distance1_P = 0.30;
        volatile static long startTime1 = 0.0;
        if(digitalRead(ECHO_1) == HIGH){
	        startTime1 = micros();
		return;
	}

	if(digitalRead(ECHO_1) == LOW){
	        long travelTime1 = micros() - startTime1;
	        distance1 = travelTime1 / 1000.0;
			if (distance1 < 0.30) distance1 = 0.30;
			else if (distance1 > 5.00) distance1 = distance1_P;
			distance1_P =distance1;
	       //x = 1;
	}
}

void sonarCheck2 (void)
{
	volatile static double distance2_P = 0.30;
	volatile static long startTime2 = 0.0;
        if(digitalRead(ECHO_2) == HIGH){
	        startTime2 = micros();
		return;
	}

	if(digitalRead(ECHO_2) == LOW){
	        long travelTime2 = micros() - startTime2;
	        distance2 = travelTime2 / 1000.0;
			if (distance2 < 0.30) distance2 = 0.30;
			else if (distance2 > 5.00) distance2 = distance2_P;
			distance2_P = distance2;
	       //x = 1;
	}
}

void sonarCheck3 (void)
{
	volatile static double distance3_P = 0.30;
        volatile static long startTime3 = 0.0;
        if(digitalRead(ECHO_3) == HIGH){
	        startTime3 = micros();
		return;
	}

	if(digitalRead(ECHO_3) == LOW){
	        long travelTime3 = micros() - startTime3;
	        distance3 = travelTime3 / 1000.0;
			if (distance3 < 0.30) distance3 = 0.30;
			else if (distance3 > 5.00) distance3 = distance3_P;
			distance3_P = distance3;
	       //x = 1;
	}
}

void sonarCheck4 (void)
{
	volatile static double distance4_P = 0.30;
        volatile static long startTime4 = 0.0;
        if(digitalRead(ECHO_4) == HIGH){
	        startTime4 = micros();
		return;
	}

	if(digitalRead(ECHO_4) == LOW){
	        long travelTime4 = micros() - startTime4;
	        distance4 = travelTime4 / 1000.0;
			if (distance4 < 0.30) distance4 = 0.30;
			else if (distance4 > 5.00) distance4 = distance4_P;
			distance4_P = distance4;
	       //x = 1;
	}
}

void setupRangeMsg0(void){
		//sensor_msgs::Range rangeMsg0;
		rangeMsg0.header.stamp = ros::Time::now();
		rangeMsg0.header.frame_id = "/sonar0";
		rangeMsg0.radiation_type = 0,                     //0=ultrasonic, 1=IR
		rangeMsg0.field_of_view = FOV;
		rangeMsg0.min_range = 0.0;
		rangeMsg0.max_range = 5.0;
}

void setupRangeMsg1(void){
		//sensor_msgs::Range rangeMsg1;
		rangeMsg1.header.stamp = ros::Time::now();
		rangeMsg1.header.frame_id = "/sonar1";
		rangeMsg1.radiation_type = 0,                     //0=ultrasonic, 1=IR
		rangeMsg1.field_of_view = FOV;
		rangeMsg1.min_range = 0.0;
		rangeMsg1.max_range = 5.0;
}

void setupRangeMsg2(void){
		//sensor_msgs::Range rangeMsg2;	
		rangeMsg2.header.stamp = ros::Time::now();
		rangeMsg2.header.frame_id = "/sonar2";
		rangeMsg2.radiation_type = 0,                     //0=ultrasonic, 1=IR
		rangeMsg2.field_of_view = FOV;
		rangeMsg2.min_range = 0.0;
		rangeMsg2.max_range = 5.0;
}

void setupRangeMsg3(void){
		//sensor_msgs::Range rangeMsg3;	
		rangeMsg3.header.stamp = ros::Time::now();
		rangeMsg3.header.frame_id = "/sonar3";
		rangeMsg3.radiation_type = 0,                     //0=ultrasonic, 1=IR
		rangeMsg3.field_of_view = FOV;
		rangeMsg3.min_range = 0.0;
		rangeMsg3.max_range = 5.0;
}

void setupRangeMsg4(void){
		//sensor_msgs::Range rangeMsg4;	
		rangeMsg4.header.stamp = ros::Time::now();
		rangeMsg4.header.frame_id = "/sonar4";
		rangeMsg4.radiation_type = 0,                     //0=ultrasonic, 1=IR
		rangeMsg4.field_of_view = FOV;
		rangeMsg4.min_range = 0.0;
		rangeMsg4.max_range = 5.0;
}

void setupWiringPi(void) {
        wiringPiSetup();
        pinMode(ECHO_0, INPUT);
        pinMode(ECHO_1, INPUT);
        pinMode(ECHO_2, INPUT);
        pinMode(ECHO_3, INPUT);
        pinMode(ECHO_4, INPUT);

        wiringPiISR (ECHO_0, INT_EDGE_BOTH, &sonarCheck0);
        wiringPiISR (ECHO_1, INT_EDGE_BOTH, &sonarCheck1);
        wiringPiISR (ECHO_2, INT_EDGE_BOTH, &sonarCheck2);
        wiringPiISR (ECHO_3, INT_EDGE_BOTH, &sonarCheck3);
        wiringPiISR (ECHO_4, INT_EDGE_BOTH, &sonarCheck4);
}

int main(int argc, char **argv) 
{
	setupWiringPi();

	ros::init(argc, argv, "range_msg");
	ros::NodeHandle nh;

	ros::Publisher sonar0_pub = nh.advertise<sensor_msgs::Range>("sonar0", 5);
	ros::Publisher sonar1_pub = nh.advertise<sensor_msgs::Range>("sonar1", 5);
	ros::Publisher sonar2_pub = nh.advertise<sensor_msgs::Range>("sonar2", 5);
	ros::Publisher sonar3_pub = nh.advertise<sensor_msgs::Range>("sonar3", 5);
	ros::Publisher sonar4_pub = nh.advertise<sensor_msgs::Range>("sonar4", 5);

	ros::Rate loop_rate(10);
	

	while (ros::ok())
	{
/*	sensor_msgs::Range rangeMsg;	
	rangeMsg.header.stamp = ros::Time::now();
	rangeMsg.header.frame_id = "/sonar0";
	rangeMsg.radiation_type = 0,                     //0=ultrasonic, 1=IR
	rangeMsg.field_of_view = 0.05;
	rangeMsg.min_range = 0.0;
	rangeMsg.max_range = 5.0;
	rangeMsg.range = distance0;
      //broadcastTransform(threadName)
      //RangeSensorPub.publish(rangeMsg)
*/

		setupRangeMsg0();
		setupRangeMsg1();
		setupRangeMsg2();
		setupRangeMsg3();
		setupRangeMsg4();

		rangeMsg0.range = distance0;
		rangeMsg1.range = distance1;
		rangeMsg2.range = distance2;
		rangeMsg3.range = distance3;
		rangeMsg4.range = distance4;

		sonar0_pub.publish(rangeMsg0);
		sonar1_pub.publish(rangeMsg1);
		sonar2_pub.publish(rangeMsg2);
		sonar3_pub.publish(rangeMsg3);
		sonar4_pub.publish(rangeMsg4);

    	ros::spinOnce();
    	loop_rate.sleep();
    }

	return 0;
}
