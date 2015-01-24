#include "RC.h"
#include "sensorlib/UartConsole.h"
#include <math.h>

//___________________________   RC Moduel Reading functions ____________________________
//
//	This file contains functions, which convert RC receiver readings
//	into SetValues for PID stabilization regulators



//*********************************************************************************************
//*********************************************************************************************

//
//	this variables store time in [us]
//
volatile int Timer0A, Timer0B, Timer1A, Timer1B, Timer3A;
float throttleTmp;


//
//  this temporary boolean variable is responsible for arming RC
//
volatile bool tmp1=false;


//
// SetValues for PID regulators
//
 float SetValueRoll, SetValuePitch, SetValueYaw;

extern float 			ControlEngine1, ControlEngine2,
									ControlEngine3,	ControlEngine4;
//

//*********************************************************************************************
//*********************************************************************************************




void delay()
{
	int tmp=1000;
	while(tmp){--tmp;}
}

//________________________ GPIO_PA4 Interrupt Handler ______________________________
		
void
GPIOAIntHandler(void)
{
	
	 GPIOIntClear(GPIO_PORTA_BASE,GPIO_PIN_4);
	
	
	
	// 	Check type of interrupt 
	// 	if pin_state=high -> rising edge
	// 	else falling edge 
	//	have to shift 4 times, because it's pin PA4
	if(GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_4)>>4)
	{
		//	Rising edge 
		//	Should start to count time
		IntEnable(INT_TIMER0A);
		TimerEnable(TIMER0_BASE, TIMER_A);

	}
	else
	{
		// 	Falling edge 
		//	Should stop counting time and write RC readings to set value
		TimerDisable(TIMER0_BASE, TIMER_A);
		SetValueRoll=(Timer0A-100)/2;

		Timer0A=0;
	}
	
	
  
}

// 	This is timer interrupt function handler
//	Timer count every 10 us
void 
Timer0AIntHnadler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	
	Timer0A+=1;
	
}



//________________________ GPIO_PB6 Interrupt Handler ______________________________

void
GPIOBIntHandler(void)
{
	
	
	GPIOIntClear(GPIO_PORTB_BASE,GPIO_PIN_6);
	
	
	// 	Check type of interrupt 
	// 	if pin_state=high -> rising edge
	// 	else falling edge 
	//	have to shift 6 times, because it's pin PB6
	if(GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_6)>>6)
	{
		
		//	Rising edge 
		//	Should start to count time
		IntEnable(INT_TIMER0B);
		TimerEnable(TIMER0_BASE, TIMER_B);
	}
	else
	{
		// 	Falling edge 
		//	Should stop counting time and write RC readings to set value
		TimerDisable(TIMER0_BASE, TIMER_B);
		SetValuePitch=(Timer0B-100)/2-25;
		if(fabs(SetValuePitch)<1.5)
			SetValuePitch=0;
		
		Timer0B=0;
	
	}
	
   
}


// 	This is timer interrupt function handler
//	Timer count every 10 us
void 
Timer0BIntHnadler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	
	Timer0B+=1;
	
}


//________________________ GPIO_PC7 Interrupt Handler ______________________________
void
GPIOCIntHandler(void)
{
	
	GPIOIntClear(GPIO_PORTC_BASE,GPIO_PIN_7);
	
	
	// 	Check type of interrupt 
	// 	if pin_state=high -> rising edge
	// 	else falling edge 
	//	have to shift 7 times, because it's pin P7
	if(GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_7)>>7)
	{
		//	Rising edge 
		//	Should start to count time
		IntEnable(INT_TIMER1A);
		TimerEnable(TIMER1_BASE, TIMER_A);
		
	}
	else
	{
		// 	Falling edge 
		//	Should stop counting time and write RC readings to set value
		TimerDisable(TIMER1_BASE, TIMER_A);
		SetValueYaw=(Timer1A-100)/2-25;
		
		Timer1A=0;
		
	}
	
	
  
}

// 	This is timer interrupt function handler
//	Timer count every 10 us
void 
Timer1AIntHnadler(void)
{
	TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	
	Timer1A+=1;
	
}


//________________________ GPIO_PD8 Interrupt Handler ______________________________

void
GPIODIntHandler(void)
{

	GPIOIntClear(GPIO_PORTD_BASE,GPIO_PIN_6); 
	
	
	// 	Check type of interrupt 
	// 	if pin_state=high -> rising edge
	// 	else falling edge 
	//	have to shift 6 times, because it's pin PD6
	if(GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_6)>>6)
	{
		//	Rising edge 
		//	Should start to count time
		IntEnable(INT_TIMER1B);
		TimerEnable(TIMER1_BASE, TIMER_B);
	}
	else
	{
		// 	Falling edge 
		//	Should stop counting time and write RC readings to set value
		TimerDisable(TIMER1_BASE, TIMER_B);
		throttleTmp =(Timer1B-100)*0.8;
		if(throttleTmp<10) throttleTmp=10;
		
		
		Timer1B=0;
		
	
	}
	
  
}

// 	This is timer interrupt function handler
//	Timer count every 10 us
void
Timer1BIntHnadler(void)
{
	TimerIntClear(TIMER1_BASE, TIMER_TIMB_TIMEOUT);
	
	Timer1B+=1;
	
}


//
//__________________________ Initialization Procedure _____________________________________
//

void
RC_Init(void)
{
		// ****************	GPIO initialization	************************
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		delay();
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB );
		delay();
		SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOC );
		delay();
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
		delay();
		SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
		delay();
		SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
		delay();
	
		//GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_4 );
		//GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,GPIO_PIN_6 );
		GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,GPIO_PIN_7 );
		GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_6 );

	
		//GPIOIntRegister(GPIO_PORTA_BASE, GPIOAIntHandler);
		//GPIOIntRegister(GPIO_PORTB_BASE, GPIOBIntHandler);
		GPIOIntRegister(GPIO_PORTC_BASE, GPIOCIntHandler);
		GPIOIntRegister(GPIO_PORTD_BASE, GPIODIntHandler);
		
		//GPIOIntTypeSet(GPIO_PORTA_BASE,  GPIO_PIN_4 , GPIO_BOTH_EDGES);
		//GPIOIntTypeSet(GPIO_PORTB_BASE,  GPIO_PIN_6 , GPIO_BOTH_EDGES);
		GPIOIntTypeSet(GPIO_PORTC_BASE,  GPIO_PIN_7 , GPIO_BOTH_EDGES);
		GPIOIntTypeSet(GPIO_PORTD_BASE,  GPIO_PIN_6 , GPIO_BOTH_EDGES);
	
	
		//IntEnable(INT_GPIOA );
		//IntEnable(INT_GPIOB );
		IntEnable(INT_GPIOC );
		IntEnable(INT_GPIOD);
		

	
    IntMasterEnable();
	
		//GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_4 );
		//GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_6 );
		GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_7 );
		GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_6 );

		TimerConfigure(TIMER0_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC |TIMER_CFG_B_PERIODIC));
		TimerConfigure(TIMER1_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC |TIMER_CFG_B_PERIODIC));
		
		//TimerIntRegister(TIMER0_BASE, TIMER_A,Timer0AIntHnadler);
		//TimerIntRegister(TIMER0_BASE, TIMER_B,Timer0BIntHnadler);
		TimerIntRegister(TIMER1_BASE, TIMER_A,Timer1AIntHnadler);
		TimerIntRegister(TIMER1_BASE, TIMER_B,Timer1BIntHnadler);
		
		// Set timer period = 10us
		///TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / 100000);
		//TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet() / 100000);
		TimerLoadSet(TIMER1_BASE, TIMER_A, SysCtlClockGet() / 100000);
		TimerLoadSet(TIMER1_BASE, TIMER_B, SysCtlClockGet() / 100000);
		
		//TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
		//TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
		TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
		TimerIntEnable(TIMER1_BASE, TIMER_TIMB_TIMEOUT);
}

void
Timer3AIntHnadler(void)
{
	if(tmp1)
		Timer3A+=1;
	else
		Timer3A=0;
	
	TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
	
}

//
//			This function arms RC 
void 
RC_Arm(void)
{	
	
	bool RC_not_armed=true;
	// Timer configuration
	// has to count time during arming RC
	// counts every 0.001s
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
	delay();
	TimerConfigure(TIMER3_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC ));
	TimerIntRegister(TIMER3_BASE, TIMER_A,Timer3AIntHnadler);
	TimerLoadSet(TIMER3_BASE, TIMER_A, SysCtlClockGet() / 1000);
	TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
	
	IntEnable(INT_TIMER3A);
	TimerEnable(TIMER3_BASE, TIMER_A);
	
	while(RC_not_armed)
	{	
		
		if((ControlEngine1<15) & (SetValueYaw>18))
		{
			tmp1=true;
			UARTprintf("d");
		}
		else 
		{
			tmp1=false;
		}
		
		if(Timer3A>2000)
			RC_not_armed=false;

	}
		
	IntDisable(INT_TIMER3A);
	TimerDisable(TIMER3_BASE, TIMER_A);
	
	
}

