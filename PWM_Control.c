#include "PWM_Control.h"

extern float 			ControlEngine1, ControlEngine2,
									ControlEngine3,	ControlEngine4;



void
PWM_Init(void)
{
	
	unsigned long ulPeriod;

  
 

   //Configure PWM Clock to match system
   SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

   // Enable the peripherals used by this program.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);  //The Tiva Launchpad has two modules (0 and 1). Module 1 covers the LED pins
    ulPeriod = 100000; //PWM frequency 400HZ

    //Configure PF1,PF2,PF3 Pins as PWM
		GPIOPinConfigure(GPIO_PE4_M1PWM2);
    GPIOPinConfigure(GPIO_PE5_M1PWM3);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);
		GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    //Configure PWM Options
    //PWM_GEN_2 Covers M1PWM4 and M1PWM5
    //PWM_GEN_3 Covers M1PWM6 and M1PWM7 See page 207 4/11/13 DriverLib doc
		PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    //PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC); 
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC); 

    //Set the Period (expressed in clock ticks)
		PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ulPeriod);
    //PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ulPeriod);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ulPeriod);

    //Set PWM duty
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2,ulPeriod*0.4);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3,ulPeriod*0.4);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,ulPeriod*0.4);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,ulPeriod*0.4);

    // Enable the PWM generator
		PWMGenEnable(PWM1_BASE, PWM_GEN_1);
    //PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);

    // Turn on the Output pins
    PWMOutputState(PWM1_BASE,PWM_OUT_2_BIT | PWM_OUT_3_BIT |PWM_OUT_6_BIT|PWM_OUT_7_BIT, true);

	
}





void 
SetSpeed(void)

{
	// 	PWM width modulation
	//  0 % of Engine control 	= 0.001 sec of PWM = 40% of PWM
	//  100 % of Engine control = 0.00195 sec of PWM = 78% of PWM
	//	PWM frequency = 400Hz -	= 0.0025 sec
	  
	//  40000 SysTicks = 40% of PWM
	//  80000 SysTicks = 78% of PWM
	
	//  ControlEngine equals between 0 to 100 
	
	//  PWMSet = 40000 + EngineControl*400
	//  that gives 1 % of accuracy
	
	
//********************* Engine1 - Set Speed Between 5-87.5 % 
	
	if((40000 + ControlEngine1*400)>43000 & (40000 + ControlEngine1*400)<70000)
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2,40000 + ControlEngine1*400);
	
	else if ((40000 + ControlEngine1*400)>70000)
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2,70000);
	
	else 
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2,43000);
	
	
	
//********************* Engine2 - Set Speed Between 5-87.5 %
		
	if((40000 + ControlEngine2*400)>43000 & (40000 + ControlEngine2*400)<70000)
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3,40000 + ControlEngine2*400);
	
	else if ((40000 + ControlEngine2*400)>70000)
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3,70000);
	
	else 
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3,43000);
	
//********************* Engine3- Set Speed Between 5-87.5 %	
	
	if((40000 + ControlEngine3*400)>43000 & (40000 + ControlEngine3*400)<70000)
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,40000 + ControlEngine3*400);
	
	else if ((40000 + ControlEngine3*400)>70000)
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,70000);
	
	else 
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,43000);
	
//********************* Engine4 - Set Speed Between 5-87.5 %
		
	if((40000 + ControlEngine4*400)>43000 & (40000 + ControlEngine4*400)<70000)
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,40000 + ControlEngine4*400);
	
	else if ((40000 + ControlEngine4*400)>70000)
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,70000);
	
	else 
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,43000);

}