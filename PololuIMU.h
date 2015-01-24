#ifndef __SENSORLIB_PololuIMU_H_
#define __SENSORLIB_PololuIMU_H_


#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "sensorlib/hw_mpu9150.h"
#include "sensorlib/hw_ak8975.h"
#include "sensorlib/i2cm_drv.h"
#include "sensorlib/ak8975.h"
#include "sensorlib/mpu9150.h"
#include "sensorlib/comp_dcm.h"
#include "drivers/rgb.h"

#include "sensorlib/hw_lsm303dlhc.h"
#include "sensorlib/lsm303dlhc_mag.h"
#include "sensorlib/lsm303dlhc_accel.h"
#include "sensorlib/l3gd20h.h"
#include "sensorlib/hw_l3gd20h.h"

//
// I2C Address.
//
#define LSM303DLHCMag_I2C_ADDRESS     	0x1E
#define LSM303DLHCAccel_I2C_ADDRESS     0x19
#define L3GD20H_I2C_ADDRESS							0x6B



//
//  Imu Initialization
//
bool 
PololuIMU_Init(void);



void
IMU10I2CIntHandler(void);



void
IMU10CallBack(void *pvCallbackData, uint_fast8_t ui8Status);


//
//	Accelerometer reading function 
//
void 
AccelRead( float * ReadingsDestination);

//
// Magnetometer reading function 
//
void 
MagnetRead( float * ReadingsDestination);

//
//	 Gyroscope reading function 
//
void 
GyroRead( float * ReadingsDestination);

//
// Conversion to eulera angles
//
void 
QuaternionToEulerAngles(float q0,	float q1,	float q2,	float q3,	float * EulerAngles);



#endif 
