#include "mbed.h"
#include "Motor.h"
#include "QEI.h"
#include "MotorPID.h"



int main() {
    
    MotorController* motorController = new MotorController(PB_8,PB_6);//PB8leftpwm PB9rightpwm PB6leftBipolarEnable PC7rightBipolarEnable are used to give signal to motor board
    QEI leftWheel(PA_7, PA_6, NC, 256); //encoder obj to get the speed of the motor
    MotorPID* motorPID = new MotorPID(0.5f,0,0);//P,I,D
    
    float dutyCycle;
    
    
    motorController->LeftPwmDutyCycle(0.3f);
    dutyCycle = 0.5f;
  
    while(1){
        wait(0.5f);
       // motorController->LeftPwmDutyCycle(0.4f);
       dutyCycle += motorPID->MotorPIDFun(-1000,leftWheel.getRotationSpeed());
       printf("%f\n",dutyCycle);
       dutyCycle = dutyCycle>0.95f?0.95f:dutyCycle;
       dutyCycle = dutyCycle<0.05f?0.05f:dutyCycle;
        
        motorController->LeftPwmDutyCycle(dutyCycle);//parameter from 0-1, control the speed and direction of the wheel
       printf("****%f\n",leftWheel.getRotationSpeed());
    }
}
