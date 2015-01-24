#include "sensorlib/UartConsole.h"



void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
		GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}



void
WriteConsoleTable(void)
{
		UARTprintf("\033[2J\033[H");
    UARTprintf("MPU9150 9-Axis Simple Data Application Example\n\n");
    UARTprintf("\033[20GX\033[31G|\033[43GY\033[54G|\033[66GZ\n\n");
    UARTprintf("Accel\033[8G|\033[31G|\033[54G|\n\n");
    UARTprintf("Gyro\033[8G|\033[31G|\033[54G|\n\n");
    UARTprintf("Mag\033[8G|\033[31G|\033[54G|\n\n");
    UARTprintf("\n\033[20GRoll\033[31G|\033[43GPitch\033[54G|\033[66GYaw\n\n");
    UARTprintf("Eulers\033[8G|\033[31G|\033[54G|\n\n");

    UARTprintf("\n\033[17GQ1\033[26G|\033[35GQ2\033[44G|\033[53GQ3\033[62G|"
               "\033[71GQ4\n\n");
    UARTprintf("Q\033[8G|\033[26G|\033[44G|\033[62G|\n\n");
}


void 
RgbInit(void)
	{
		g_pui32Colors[RED] = 0x8000;
		g_pui32Colors[BLUE] = 0x8000;
		g_pui32Colors[GREEN] = 0x0000;


    // Initialize RGB driver.
    //
		
    RGBInit(0);
    RGBColorSet(g_pui32Colors);
    RGBIntensitySet(0.5f);
    RGBEnable();
		
}