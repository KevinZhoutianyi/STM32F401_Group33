#include "Navi.h"
#define COEF1 1000
#define COEF2 1500
#define COEF3 2000


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
	PIDoutMax=2000;//maximum of the wheel speed
	getSpeedPIDTicker.attach(callback(this,&Navigation::setSpeed),0.01f);
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
	position = COEF1*(s4.read()-s3.read())+COEF2*(s5.read()-s2.read())+COEF3*(s6.read()-s1.read());
	speedDiff = speedDiffPID(position);
	
	motorLeft->SetTargetSpeed(500-speedDiff);
	motorRight->SetTargetSpeed(500+speedDiff);
	
	
}
float Navigation::getPos(void)
{
	return position;
}

void Navigation::PrintSensors(void)
{
			printf("\r\n***%f***%f***%f***%f***%f***%f",s4.read(),s3.read(),s5.read(),s2.read(),s6.read(),s1.read());
}