#include "mbed.h"
#include "Motor.h"




int main()
{

  MotorController* motorControllerLeft = new MotorController(PB_9,PB_5,PB_4,0.5f,0,0,'L',PA_5,256);//pwm,CH1,CH2,P,I,D,NAME
  MotorController* motorControllerRight = new MotorController(PB_8,PB_10,PA_8,0.3f,0,0,'\n',PA_6,256);//PB8leftpwm PB9rightpwm PB6leftBipolarEnable PC7rightBipolarEnable are used to give signal to motor board
	
	DigitalOut en(PB_6);
	en.write(1);

	

//	for(int i = -16; i<=16;i++)
//	{
//		
//	
//		motorControllerLeft->SetTargetSpeed(0.5*i*100);//max 800
//		motorControllerRight->SetTargetSpeed(0.5*i*100);
//		wait(2);
//		
//	}
	for(int j = 0;j<=2;j++){
motorControllerLeft->SetTargetSpeed(400);//max 1600
	motorControllerRight->SetTargetSpeed(400);
	wait(3);
	motorControllerLeft->SetTargetSpeed(-400);//max 1600
	motorControllerRight->SetTargetSpeed(-400);
	wait(3);
	}
	
		motorControllerLeft->SetTargetSpeed(0);//max 1600
	motorControllerRight->SetTargetSpeed(0);
	

	
  while(1) {
		
	


  }
}

