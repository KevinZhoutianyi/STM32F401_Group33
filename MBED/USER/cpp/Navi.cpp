#include "Navi.h"
#define COEF1 1000
#define COEF2 5000
#define COEF3 30000
//#define COEF3 500000
//make it to 0.5 V
#define S1 s1.read()*4.065f
#define S2 s2.read()*3.906f
#define S3 s3.read()*2.7027f
#define S4 s4.read()*2.463f
#define S5 s5.read()*2.841f
#define S6 s6.read()*2.2727f
#define ABS(x) x>0?x:-x


Navigation::Navigation(PinName s1_,PinName s2_,PinName s3_,PinName s4_,PinName s5_,PinName s6_,PinName out,
PinName mid,PinName in,MotorController* left,MotorController* right,float p,float i,float d):s1(s1_),s2(s2_),s3(s3_),s4(s4_),s5(s5_),s6(s6_),
out_en(out),mid_en(mid),in_en(in),motorLeft(left),motorRight(right),P(p),I(i),D(d)
{
	out_en.write(1);
	mid_en.write(1);
	in_en.write(1);
	speedDiff = 0;
	target_=0;//in middle
	feed_=0;
	currentDiff_=0;
	lastDiff_=0;
	Pout=0;
	Iout=0;
	Dout=0;
	PIDout=0;
	IoutMax=999999;
	PIDoutMax=20000000;
	average = 0;
	deviation = 0;
	getSpeedPIDTicker.attach(callback(this,&Navigation::setSpeed),0.001f);
}

float Navigation::speedDiffPID(float feed)
{
		feed_ = feed;
		currentDiff_ = target_ - feed_;

		Pout = P * currentDiff_;

		Iout += I * currentDiff_;
		Iout = Iout > IoutMax ? IoutMax : Iout;
		Iout = Iout < -IoutMax ? -IoutMax : Iout;
	
		Dout = D * (currentDiff_-lastDiff_);

		lastDiff_ = currentDiff_;
	
		PIDout = (Pout + Iout + Dout);

		PIDout = PIDout > PIDoutMax ? PIDoutMax : PIDout;
		PIDout = PIDout < -PIDoutMax ? -PIDoutMax : PIDout;
	
		return PIDout;
}


void Navigation::setSpeed(void)
{
	average = (S1+ S2 + S3+ S4+ S5+ S6)/6.0f;
	deviation = (Abs(S1 - average) + Abs(S2 - average) + Abs(S3 - average) + Abs(S4 - average) + Abs(S5 - average) + Abs(S6 - average))*1000 ;
	if(deviation>180)
//	if(1)
	{
		
		position =COEF1*(S4-S3)+COEF2*(S5-S2)+COEF3*(S6-S1);
		speedDiff = speedDiffPID(position);
		
		motorLeft->SetTargetSpeed(2300-speedDiff);
		motorRight->SetTargetSpeed(2300+speedDiff);
	}
	else
	{
		position =COEF1*(S4-S3)+COEF2*(S5-S2)+COEF3*(S6-S1);
		motorLeft->resIout();
		motorRight->resIout();
		motorLeft->SetTargetSpeed(0);
		motorRight->SetTargetSpeed(0);
	}
	
	
}
float Navigation::getPos(void)
{
	return position;
}

void Navigation::PrintSensors(void)
{
	//printf("\r\n***%f***%f***%f***%f***%f***%f",S1,S2,S3,S4,S5,S6);
	//printf("\r\n%f",position);
	printf("\r\n%f",deviation);
	//printf("\r\n%lf",speedDiff);
}
void Navigation::detachh(void){
	getSpeedPIDTicker.detach();
}

void Navigation::retachh(void){
	getSpeedPIDTicker.attach(callback(this,&Navigation::setSpeed),0.001f);
}

float Navigation::Abs(float x)
{
	if(x>0)
	{
		return x;
	}
	else
	{
		return -x;
	}
}