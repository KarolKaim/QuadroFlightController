

#include "Stabilization.h"
#include "sensorlib/UartConsole.h"

//
// variables, which control engines speeds.
// take value from 0 to 100 %
//
float 						ControlEngine1 = 0, ControlEngine2 = 0,
									ControlEngine3 = 0,	ControlEngine4 = 0;

//
// value form RC 	
//
extern float 			throttleTmp;	

//
// PID regulatrs parameters 
//
volatile const float 	RollKp = 0.22, 	PitchKp = 0.22, YawKp = 0.18,		//Kp=0.22
											RollKi = 2.00,	PitchKi = 1.0, YawKi = 1.0,
											RollKd = 0.34,		PitchKd = 0.34, YawKd = 0.38;		// Kd=0.36
//
// loop sample time
//
volatile float sampleTime = 0.008;	

//
// 'Speed PID' impelentation variables
//
float pitchQ0, 	pitchQ1, 	pitchQ2;
float rollQ0, 	rollQ1, 	rollQ2;

//
// PID stored values
//
volatile float pitchU, pitchUprev, pitchError, pitchErrorPrev1, pitchErrorPrev2;
volatile float rollU, rollUprev, rollError, rollErrorPrev1, rollErrorPrev2;




//
// 'Speed PID' initialization
void PitchInit(void){
	
	pitchQ0=PitchKp*(1+PitchKd/sampleTime);
	pitchQ1=-PitchKp*(1+2*PitchKd/sampleTime);
	pitchQ2=PitchKp*PitchKd/sampleTime;
	
}

void RollInit(void){
	
	rollQ0=RollKp*(1+RollKd/sampleTime);
	rollQ1=-RollKp*(1+2*RollKd/sampleTime);
	rollQ2=RollKp*RollKd/sampleTime;
	
}



//
// Pitch	Roll	Yaw PID algorithm 
//
void PitchPID(	float * SetValue, float  *CurrnetValue)
{
	pitchUprev=pitchU;
	pitchErrorPrev2=pitchErrorPrev1;
	pitchErrorPrev1=pitchError;
	
	pitchError=(*SetValue)-(*CurrnetValue);
	
	pitchU= pitchUprev+ pitchQ0*pitchError+ pitchQ1*pitchErrorPrev1+ pitchQ2*pitchErrorPrev2;
	
	
	ControlEngine1=throttleTmp+pitchU;
	ControlEngine3=throttleTmp-pitchU;
	

	
	ControlEngine1=ControlEngine1>80?80:ControlEngine1;
	ControlEngine1=ControlEngine1<10?10:ControlEngine1;
	
	ControlEngine3=ControlEngine3>80?80:ControlEngine3;
	ControlEngine3=ControlEngine3<10?10:ControlEngine3;


}





void rollPID(	float * SetValue, float  *CurrnetValue)
{
	rollUprev=rollU;
	rollErrorPrev2=rollErrorPrev1;
	rollErrorPrev1=rollError;
	
	rollError=(*SetValue)-(*CurrnetValue);
	

		rollU= rollUprev+ rollQ0*rollError+ rollQ1*rollErrorPrev1+ rollQ2*rollErrorPrev2;	
	
	
	
	ControlEngine2=throttleTmp-rollU;
	ControlEngine4=throttleTmp+rollU;
	
	ControlEngine2=ControlEngine2>80?80:ControlEngine2;
	ControlEngine2=ControlEngine2<10?10:ControlEngine2;
	
	ControlEngine4=ControlEngine4>80?80:ControlEngine4;
	ControlEngine4=ControlEngine4<10?10:ControlEngine4;


}



