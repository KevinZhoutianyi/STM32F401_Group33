#ifndef MOTOR_H
#define MOTOR_H
#include "mbed.h"

class MotorController{
    private:
        PwmOut leftMotorPwm;
        DigitalOut leftBipolarSel;
         
    public: 
        MotorController(PinName leftPwm,PinName leftSel):leftMotorPwm(leftPwm),leftBipolarSel(leftSel){
            leftBipolarSel.write(1);
        }
        void LeftPwmDutyCycle(float percent)
        {
            
            leftMotorPwm.period_ms(10);
            leftMotorPwm.write(percent);
        }

};

#endif

