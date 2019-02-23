#ifndef MOTOR_H
#define MOTOR_H
#include "mbed.h"
#include "QEI.h"


class MotorController
{
private:
    PwmOut motorPwm;
    float dutyCycle;

    QEI encoder;

    float targetSpeed;
    
    int target_,feed_,currentDiff_,Pout,Iout,Dout,PIDout;
    int IoutMax,PIDoutMax;
    float P,I,D;

    Ticker motorPIDTicker;
    
    char name_;

		DigitalOut enable;

public:
    MotorController(PinName pwm,PinName CH1,PinName CH2,float p,float i,float d,char whichMotor,PinName en):motorPwm(pwm),dutyCycle(0.5f),encoder(CH1,CH2,NC,256),P(p),I(i),D(d),name_(whichMotor),enable(en)
    {
        targetSpeed = 0;

        target_=0;
        feed_=0;
        currentDiff_=0;
        Pout=0;
        Iout=0;
        Dout=0;
        PIDout=0;
        IoutMax=99999999;
        PIDoutMax=10000;

        motorPwm.period_us(100);

        motorPIDTicker.attach(callback(this,&MotorController::TickerFunct),0.01f);
			
				enable.write(1);
    }


    float MotorPIDFun(int target,int feed)
    {
        target_ = target;
        feed_ = feed;
        currentDiff_ = target_ - feed_;

        Pout = P * currentDiff_;

        Iout += I * currentDiff_;
        Iout = Iout > IoutMax ? IoutMax : Iout;
        Iout = Iout < -IoutMax ? -IoutMax : Iout;

        PIDout = (Pout + Iout + Dout);

        PIDout = PIDout > PIDoutMax ? PIDoutMax : PIDout;
        PIDout = PIDout < -PIDoutMax ? -PIDoutMax : PIDout;
        return (float)PIDout/(float)PIDoutMax/2.0f;
    }

    void TickerFunct(void)
    {
        dutyCycle +=  MotorPIDFun(targetSpeed,encoder.getRotationSpeed());
        dutyCycle  =dutyCycle>0.90f?0.9f:dutyCycle;
        dutyCycle=dutyCycle<0.1f?0.1f:dutyCycle;
        motorPwm.write(dutyCycle);
        
		
    }
    
    void SetTargetSpeed(float x)
    {
        targetSpeed = x;
    }
		void print(void)
		{
			
				//printf(" %c**speed:%d ",name_,encoder.getPulses());
        printf(" %c**speed:%f ",name_,encoder.getRotationSpeed());
		}


};

#endif


