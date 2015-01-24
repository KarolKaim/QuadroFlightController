#ifndef _UARTCONSOLE_H
#define _UARTCONSOLE_H


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "drivers/rgb.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#define PRINT_SKIP_COUNT        10



extern uint32_t g_ui32PrintSkipCounter=0;

extern uint32_t g_pui32Colors[3];

void
ConfigureUART(void);

void
WriteConsoleTable(void);

void 
RgbInit(void);

#endif 