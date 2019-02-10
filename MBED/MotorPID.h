#ifndef MOTORPID_H
#define MOTORPID_H
#include "mbed.h"



class MotorPID{
    private:
        int target_,feed_,currentDiff_,Pout,Iout,Dout,PIDout;
        int IoutMax,PIDoutMax;
        float P,I,D;
        
         
    public: 
        MotorPID(float p,float i,float d):P(p),I(i),D(d){
            target_=0;feed_=0;currentDiff_=0;Pout=0;Iout=0;Dout=0;PIDout=0;
            IoutMax=99999999;PIDoutMax=10000;
        
        }
        float MotorPIDFun(int target,int feed)
        {
            target_ = target;
            feed_ = feed;
            currentDiff_ = target_ - feed_;  
            
            Pout = P * currentDiff_;
        
            Iout += I * currentDiff_;
            Iout = Iout > IoutMax ? IoutMax : Iout;
            Iout = Iout < -IoutMax ? -IoutMax : Iout;
            
            PIDout = (Pout + Iout + Dout);
            
            PIDout = PIDout > PIDoutMax ? PIDoutMax : PIDout;
            PIDout = PIDout < -PIDoutMax ? -PIDoutMax : PIDout;
            return -(float)PIDout/(float)PIDoutMax/2.0f;
        }

};

#endif

