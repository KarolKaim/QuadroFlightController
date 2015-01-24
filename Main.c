#include <stdint.h>
#include "PololuIMU.h"
#include "sensorlib/UartConsole.h"
#include "MadgwickAHRS.h"
#include "TimerPeriodicInterrupt.h"
#include "RC.h"
#include "sensorlib/UartConsole.h"
#include "PID_Regulatros.h"
#include "PWM_Control.h"
#include "Stabilization.h"




//
//	Global variables, required to call proper functions.
//

extern volatile float q0,q1,q2,q3;

extern volatile bool 			TimeToMadgwick, 	TimeToUart,	TimeToMag,TimeToCheckPWMState; 

extern volatile uint32_t 	MadgwickCounter, 		UartCounter, 				MagnetometerCounter;

extern   float						ControlEngine1, 		ControlEngine2,
													ControlEngine3,			ControlEngine4;

extern volatile float SetValueRoll, SetValuePitch, SetValueYaw;

extern float 			throttleTmp;	

//
// The error routine that is called if the driver library encounters an error.
//
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


//
// Initialization function - prepares all measurement instruments.
//
bool Initialization(void);


//
// Data serial port logger
//
void SendData(float * data);



//
// Main function - responsible for stabilization quadrocopter.
// Main merges all parts into one algorithm.
// 
// Initialization is the first step.
// Stabilization algorithm works into periodic loop - 125 Hz

int
main(void)
{
	
    float pfAccel[3], pfGyro[3], pfMag[3], pfEulers[3]={0,0,0};
		float SetValue=0,Proba[4],temp=0,rawEuler[3];
		bool initializationFlag=false;
		int iteration=0;

		// Initialization part
	
		initializationFlag=Initialization();	 
		
		
		while(initializationFlag)
			{
				
				// TimeToMadgwick controls algorithm - periodically changes state with 125Hz frequency.	
				
				if(TimeToMadgwick)
				{	
					// Reset variables - boolean and counter, which accumulates time.
					TimeToMadgwick=false;
				  MadgwickCounter=0;
					
					// Read measurement values.
					AccelRead(pfAccel);
					GyroRead(pfGyro);	
					//MagnetRead(pfMag);
					
					
					// Estimate orientation using Madgwick filter.
					MadgwickAHRSupdateIMU(pfGyro[0],pfGyro[1],pfGyro[2],pfAccel[0],pfAccel[1],pfAccel[2]);
			
				
					// Convert quaterniont to Euler angles.
					QuaternionToEulerAngles(q0,q1,q2,q3,pfEulers);
					
					// call PID stabilization functions.
					PitchPID(&SetValue, pfEulers+1);
					rollPID(&SetValue,pfEulers);
					
					// Set engines speed.
					SetSpeed();
					
			
				
				}
	
				// Real time data logging. 
				if(TimeToMag)
				{
					SendData(pfEulers);
				}
		
			}	

}

bool Initialization(void)
{
	
		SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |	SYSCTL_OSC_MAIN);
		TimerInit();
		PololuIMU_Init();
		ConfigureUART();
		PitchInit();
		RollInit();
		RC_Init();
		RC_Arm();
		PWM_Init();
		SysCtlDelay(10000000);SysCtlDelay(10000000);
		
		return true;
}

void SendData(float * data)
{
	TimeToMag=false;
  MagnetometerCounter=0;
	UARTprintf("\n");
	PrintSingleFloat(data);
}