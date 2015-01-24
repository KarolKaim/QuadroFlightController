#include "TimerPeriodicInterrupt.h"

//
// Counters, which acumulate time.
//
volatile uint32_t 	MadgwickCounter = 0, 			UartCounter = 0,	MagnetometerCounter=0;	
										
//
// Boolean variables, which control the main loop
//
volatile bool 			TimeToMadgwick	= false , 	TimeToUart 	= false, TimeToMag = false;	
										

void
Timer2BIntHandler(void)
{
    //
    // Clear the timer interrupt flag.
    //
    TimerIntClear(TIMER2_BASE, TIMER_TIMB_TIMEOUT);

    //
    // Update the periodic interrupt counter.
    //
    MadgwickCounter++;
		UartCounter++;
		MagnetometerCounter++;

		//
		//	Timer counts each 1ms
    if(MadgwickCounter == 8)
    {
			TimeToMadgwick	= true; 
    }
		
		if(UartCounter == 2500)
		{
			TimeToUart = true;
		}
		
			if(MagnetometerCounter == 80)
		{
			TimeToMag = true;
		}
		
		
}


void
TimerInit(void)
{
   

    //
    // The Timer0 peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

    //
   
    //
    // Configure Timer0B as a 16-bit periodic timer.
    //
    TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);

    //
    // Set the Timer0B load value to 1ms.
    //
    TimerLoadSet(TIMER2_BASE, TIMER_B, SysCtlClockGet()/1000);

    //
    // Enable processor interrupts.
    //
    IntMasterEnable();

    //
    // Configure the Timer0B interrupt for timer timeout.
    //
    TimerIntEnable(TIMER2_BASE, TIMER_TIMB_TIMEOUT);

    //
    // Enable the Timer0B interrupt on the processor (NVIC).
    //
    IntEnable(INT_TIMER2B);
		
		//
		IntPrioritySet(INT_TIMER2B,0x50);

    //
    // Initialize the interrupt counter.
    //
    MadgwickCounter = 0;
		UartCounter = 0;
		MagnetometerCounter=0;
    //
    // Enable Timer0B.
    //
    TimerEnable(TIMER2_BASE, TIMER_B);


		
}

