#ifndef _TIMERPERIODICINTERRUPT_H_
#define _TIMERPERIODICINTERRUPT_H_

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



// Timer handler
void
Timer2BIntHandler(void);

// Timer initialization
void
TimerInit(void);

#endif

