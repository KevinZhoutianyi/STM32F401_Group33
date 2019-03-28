#ifndef NAVI_H
#define NAVI_H
#include "mbed.h"
#include "Motor.h"



class Navigation
{
private:
		AnalogIn s1,s2,s3,s4,s5,s6;
		DigitalOut out_en,mid_en,in_en;
		float position;
		MotorController* motorLeft;
		MotorController* motorRight;
		Ticker getSpeedPIDTicker;

    float targetSpeed;
    float target_,feed_,currentDiff_,lastDiff_,Pout,Iout,Dout,PIDout;
    float IoutMax,PIDoutMax;
    float P,I,D;
		float speedDiff;
		float average;
		float deviation;
		
public:
    Navigation(PinName s1_,PinName s2_,PinName s3_,PinName s4_,PinName s5_,PinName s6_,PinName out,
									PinName mid,PinName in,MotorController* left,MotorController* right,float p,float i,float d);


		float speedDiffPID(float feed);
		void setSpeed(void);
		float getPos(void);
		void PrintSensors(void);
		void detachh(void);
		void retachh(void);
		float Abs(float x);
		
    
};

#endif


