#include "mbed.h"
#include "Motor.h"
#define TESTSPEED 1800
#define test 0.5f
#define testTime 0.8f



int main()
{

  MotorController* motorControllerLeft = new MotorController(PB_9,PB_5,PB_4,0.75f,0,0,'L',PA_5,256);//pwm,CH1,CH2,P,I,D,NAME
  MotorController* motorControllerRight = new MotorController(PB_8,PB_3,PB_10,0.82f,0,0,'\n',PA_6,256);//PB8leftpwm PB9rightpwm PB6leftBipolarEnable PC7rightBipolarEnable are used to give signal to motor board
	
	DigitalOut en(PB_6);
	en.write(1);
	
	
	
	motorControllerLeft->encoderReset();
	motorControllerRight->encoderReset();

	

//	for(int i = -16; i<=16;i++)
//	{
//		
//	
//		motorControllerLeft->SetTargetSpeed(0.5*i*100);//max 800
//		motorControllerRight->SetTargetSpeed(0.5*i*100);
//		wait(2);
//		
//	}
	for(int j = 0;j<=1;j++){
			motorControllerLeft->SetTargetSpeed(TESTSPEED);//max 1600
			motorControllerRight->SetTargetSpeed(TESTSPEED*test);
			wait(testTime);
			motorControllerLeft->SetTargetSpeed(TESTSPEED*test);//max 1600
			motorControllerRight->SetTargetSpeed(TESTSPEED);
			wait(testTime*0.8f);
		
		

	}
		motorControllerLeft->SetTargetSpeed(0);//max 1600
	motorControllerRight->SetTargetSpeed(0);
wait(1);
	for(int j = 0;j<=1;j++){
		
			motorControllerLeft->SetTargetSpeed(-TESTSPEED*test);//max 1600
			motorControllerRight->SetTargetSpeed(-TESTSPEED);
			wait(testTime);
				motorControllerLeft->SetTargetSpeed(-TESTSPEED);//max 1600
			motorControllerRight->SetTargetSpeed(-TESTSPEED*test);
			wait(testTime*0.8f);
	}
	motorControllerLeft->SetTargetSpeed(0);//max 1600
	motorControllerRight->SetTargetSpeed(0);
	

	
  while(1) {
		
		
		
			wait(0.2f);
			printf(" %c**speed:%f***speed_test:%f",motorControllerLeft->getName(),motorControllerLeft->getRotationSpeed(),motorControllerLeft->getRotationSpeed_test());
					printf(" %c**speed:%f***speed_test:%f",motorControllerRight->getName(),motorControllerRight->getRotationSpeed(),motorControllerRight->getRotationSpeed_test());
		
		


  }
}

