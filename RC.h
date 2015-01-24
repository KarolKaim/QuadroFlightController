#ifndef _PWMGENERATOR_H_
#define _PWMGENERATOR_H_


#include <stdbool.h>
#include <stdint.h>
#include "driverlib/timer.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#define PD7              		0x0080  // GPIO pin A2
#define PD6              		0x0040  // GPIO pin A3
#define PC7              		0x0080  // GPIO pin A4
#define PC6              		0x0040  // GPIO pin A5

#define Engine1On             	0x00000004  // GPIO pin 2 set On
#define Engine2On              	0x00000008  // GPIO pin 3 set On
#define Engine3On               0x00000010  // GPIO pin 4 set On
#define Engine4On               0x00000020  // GPIO pin 5 set On

#define EngineOff								0x00000000	// GPIO off

//
//	Timer Interrupt Handlers for 4 channels of RC .
//
void
Timer0AIntHnadler(void);
void
Timer0BIntHnadler(void);
void
Timer1AIntHnadler(void);
void
Timer1BIntHnadler(void);

//
// GPIO interrupt handlers funtioncs.
//
void
GPIOAIntHandler(void);
void
GPIOBIntHandler(void);
void
GPIOCIntHandler(void);
void
GPIODIntHandler(void);

//
// RC reading module initialization.
//
void
RC_Init(void);

//
// RC arm function.
//
void 
RC_Arm(void);

#endif

