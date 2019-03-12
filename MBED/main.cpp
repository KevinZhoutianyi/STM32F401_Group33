#include "mbed.h"
#include "Motor.h"
#include "SoftSerial.h"
#define TESTSPEED 1800
#define test 0.5f
#define testTime 0.8f



int main()
{

  MotorController* motorControllerLeft = new MotorController(PC_8,PB_5,PB_4,0.6f,0,0,'L',PA_5,256);//pwm,CH1,CH2,P,I,D,NAME
  MotorController* motorControllerRight = new MotorController(PC_6,PB_3,PB_10,0.65f,0,0,'\n',PA_6,256);//PB8leftpwm PB9rightpwm PB6leftBipolarEnable PC7rightBipolarEnable are used to give signal to motor board
	
	Serial hm10(PA_11,PA_12); 
	
	DigitalOut en(PB_6);
	char c;
	
	en.write(1);
	hm10.baud(9600);
	
	
	
	
	
	motorControllerLeft->encoderReset();
	motorControllerRight->encoderReset();

	
//	for(int j = 0;j<=1;j++){
//			motorControllerLeft->SetTargetSpeed(TESTSPEED);//max 1600
//			motorControllerRight->SetTargetSpeed(TESTSPEED*test);
//			wait(testTime);
//			motorControllerLeft->SetTargetSpeed(TESTSPEED*test);//max 1600
//			motorControllerRight->SetTargetSpeed(TESTSPEED);
//			wait(testTime*0.8f);
//		
//		

//	}
//		motorControllerLeft->SetTargetSpeed(0);//max 1600
//	motorControllerRight->SetTargetSpeed(0);
//wait(1);
//	for(int j = 0;j<=1;j++){
//		
//			motorControllerLeft->SetTargetSpeed(-TESTSPEED*test);//max 1600
//			motorControllerRight->SetTargetSpeed(-TESTSPEED);
//			wait(testTime);
//				motorControllerLeft->SetTargetSpeed(-TESTSPEED);//max 1600
//			motorControllerRight->SetTargetSpeed(-TESTSPEED*test);
//			wait(testTime*0.8f);
//	}
//	motorControllerLeft->SetTargetSpeed(0);//max 1600
//	motorControllerRight->SetTargetSpeed(0);
//	

	motorControllerLeft->SetTargetSpeed(0);
					motorControllerRight->SetTargetSpeed(0);
  while(1) {
		
		if (hm10.readable()) {
				c=hm10.getc();
					
    }
        if(c=='0')
				{
					motorControllerLeft->SetTargetSpeed(0);
					motorControllerRight->SetTargetSpeed(0);
				}
				else if(c=='1')
				{
					motorControllerLeft->SetTargetSpeed(500);
					motorControllerRight->SetTargetSpeed(500);
				}
				else if(c=='2')
				{
					motorControllerLeft->SetTargetSpeed(1000);
					motorControllerRight->SetTargetSpeed(1000);
				}
				else if(c=='3')
				{
					motorControllerLeft->SetTargetSpeed(-500);
					motorControllerRight->SetTargetSpeed(-500);
				}
				else if(c=='4')
				{
					motorControllerLeft->SetTargetSpeed(-1000);
					motorControllerRight->SetTargetSpeed(-1000);
				}
		
		
		
		//	wait(0.2f);
		//	printf(" %c**speed:%f***speed_test:%f",motorControllerLeft->getName(),motorControllerLeft->getRotationSpeed(),motorControllerLeft->getRotationSpeed_test());
		//			printf(" %c**speed:%f***speed_test:%f",motorControllerRight->getName(),motorControllerRight->getRotationSpeed(),motorControllerRight->getRotationSpeed_test());
		
		


  }
}

