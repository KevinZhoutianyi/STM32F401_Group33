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

public:
    MotorController(PinName pwm,PinName CH1,PinName CH2,float p,float i,float d,char whichMotor):motorPwm(pwm),dutyCycle(0.5f),encoder(CH1,CH2,NC,256),P(p),I(i),D(d),name_(whichMotor)
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

        motorPwm.period_ms(10);

        motorPIDTicker.attach(callback(this,&MotorController::TickerFunct),0.1f);
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
        return -(float)PIDout/(float)PIDoutMax/2.0f;
    }

    void TickerFunct(void)
    {
        dutyCycle +=  MotorPIDFun(targetSpeed,encoder.getRotationSpeed());
        dutyCycle  =dutyCycle>0.95f?0.95f:dutyCycle;
        dutyCycle=dutyCycle<0.05f?0.05f:dutyCycle;
        motorPwm.write(dutyCycle);
        
        printf(" %c**speed:%f ",name_,encoder.getRotationSpeed());
    }
    
    void SetTargetSpeed(float x)
    {
        targetSpeed = x;
    }


};

#endif


