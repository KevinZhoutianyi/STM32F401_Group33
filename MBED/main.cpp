#include "mbed.h"
#include "Motor.h"




int main()
{

  MotorController* motorControllerLeft = new MotorController(PB_9,PB_5,PB_4,0.5f,0,0,'L',PA_5);//pwm,CH1,CH2,P,I,D,NAME
  MotorController* motorControllerRight = new MotorController(PB_8,PB_10,PA_8,0.05f,0,0,'\n',PA_6);//PB8leftpwm PB9rightpwm PB6leftBipolarEnable PC7rightBipolarEnable are used to give signal to motor board
	
	DigitalOut en(PB_6);
	en.write(1);

	motorControllerLeft->SetTargetSpeed(0);
	motorControllerRight->SetTargetSpeed(2000);
	
	wait(10);
	
	
	motorControllerRight->SetTargetSpeed(-2000);
	
	

	
  while(1) {
		
		wait(0.1f);
motorControllerLeft->print();
motorControllerRight->print();


  }
}

