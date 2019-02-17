#include "mbed.h"
#include "Motor.h"


int main()
{

    MotorController* motorControllerLeft = new MotorController(PB_8,PB_5,PB_4,0.5f,0,0,'L');//pwm,CH1,CH2,P,I,D,NAME
    MotorController* motorControllerRight = new MotorController(PB_9,PB_10,PA_8,0.5f,0,0,'\n');//PB8leftpwm PB9rightpwm PB6leftBipolarEnable PC7rightBipolarEnable are used to give signal to motor board


    wait(7);
    motorControllerLeft->SetTargetSpeed(2000);//degree/sec
    motorControllerRight->SetTargetSpeed(2000);
    wait(10);
    motorControllerLeft->SetTargetSpeed(1500);
    motorControllerRight->SetTargetSpeed(-1500);

    while(1) {




    }
}

