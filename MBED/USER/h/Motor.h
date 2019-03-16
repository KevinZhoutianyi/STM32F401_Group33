#ifndef MOTOR_H
#define MOTOR_H
#include "QEI.h"
#define LIMIT 0.8f

class MotorController
{
private:
    PwmOut motorPwm;
    float dutyCycle;
    QEI encoder;
    float targetSpeed;
    float target_,feed_,currentDiff_,Pout,Iout,Dout,PIDout;
    float IoutMax,PIDoutMax;
    float P,I,D;
    Ticker motorPIDTicker;
    char name_;
		DigitalOut enable;

public:
    MotorController(PinName pwm,PinName CH1,PinName CH2,float p,float i,float d,char whichMotor,PinName en,int pls);
    float MotorPIDFun(float target,float feed);
    void TickerFunct(void);
    void SetTargetSpeed(float x);
		void encoderReset(void);
		float getRotationSpeed(void);
		char getName(void);


};

#endif


