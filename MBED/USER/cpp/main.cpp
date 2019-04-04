#include "mbed.h"
#include "Motor.h"
#include "Navi.h"

/* speed should be set less than 2000*/
//			motorControllerLeft->SetTargetSpeed(x);
//			motorControllerRight->SetTargetSpeed(x);

//AnalogIn s1(A0);
//AnalogIn s2(A1);
//AnalogIn s3(A2);
//AnalogIn s4(A3);
//AnalogIn s5(A4);
//AnalogIn s6(A5);

//DigitalOut c1(PA_5);
//DigitalOut c2(PA_6);
//DigitalOut c3(PA_7);


int main()
{

  MotorController* motorControllerLeft = new MotorController(PC_8,PB_5,PB_4,0.06f,0,0.03,'L',PA_5,256);//pwm,CH1,CH2,P,I,D,NAME,enable
  MotorController* motorControllerRight = new MotorController(PC_6,PB_3,PB_10,0.06f,0,0.03,'\n',PA_6,256);//PB8leftpwm PB9rightpwm PB6leftBipolarEnable PC7rightBipolarEnable are used to give signal to motor board
	
	Navigation *navi = new Navigation(A0,A1,A2,A3,A4,A5,PB_13,PB_14,PB_15,motorControllerLeft,motorControllerRight,0.35f,0,42.0f);
	
	Serial hm10(PA_11,PA_12); 
	
	DigitalOut en(PB_6);//motor board enable
	char c;
	                    
	                    
	en.write(1);
	
	
	hm10.baud(9600);//bluetooth baudrate 9600
	
	motorControllerLeft->encoderReset();
	motorControllerRight->encoderReset();

	motorControllerLeft->SetTargetSpeed(0);
	motorControllerRight->SetTargetSpeed(0);
	
  while(1) {

		navi->PrintSensors();
		
		c = hm10.getc();
				if(c=='t')
				{
					navi->detachh();
					motorControllerLeft->SetTargetSpeed(0);
					motorControllerRight->SetTargetSpeed(0);
					wait(0.5f);
					motorControllerLeft->SetTargetSpeed(500);
					motorControllerRight->SetTargetSpeed(-500);
					wait(1.4f);
					navi->retachh();
					c='1';
					
				}
					
   
		
	//	printf("\r\n***%f",navi->getPos());
		//navi->PrintSensors();
	//	printf("\r\n***L::%f",motorControllerLeft->getRotationSpeed());
	//	printf("\r\n***R::%f",motorControllerRight->getRotationSpeed());
        

  }
}

