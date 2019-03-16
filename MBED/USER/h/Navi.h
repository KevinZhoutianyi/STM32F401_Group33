#ifndef NAVI_H
#define NAVI_H
#include "mbed.h"
#include "Motor.h"

//AnalogIn s1(A0);
//AnalogIn s2(A1);
//AnalogIn s3(A2);
//AnalogIn s4(A3);
//AnalogIn s5(A4);
//AnalogIn s6(A5);

//DigitalOut c1(PA_5);
//DigitalOut c2(PA_6);
//DigitalOut c3(PA_7);


class Navigation
{
private:
		AnalogIn s1,s2,s3,s4,s5,s6;
		DigitalOut out_en,mid_en,in_en;
		float position;
		MotorController* motorLeft;
		MotorController* motorRight;
		Ticker calculatePosTicker,getSpeedPIDTicker;
		
public:
    Navigation(PinName s1_,PinName s2_,PinName s3_,PinName s4_,PinName s5_,PinName s6_,PinName out,
									PinName mid,PinName in,MotorController* left,MotorController* right);
		void calculatePos(void);
		void getSpeedPID(void);
    


};

#endif


