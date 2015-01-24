#include "PololuIMU.h"

//
// Global flags to alert main that IMU10 I2C transaction is complete
//
volatile uint_fast8_t I2CDoneFlag;


//
// Global flags to alert main that IMU10 I2C transaction error has occurred.
//
volatile uint_fast8_t ErrorFlag;


//
// Global flags to alert main that IMU10 data is ready to be retrieved.
//
volatile uint_fast8_t g_vui8DataFlag;


//
// Global instance structures for PloluIMU
//
 tLSM303DLHCMag sLSM303DLHCMag;
 tLSM303DLHCAccel sLSM303DLHCAccel;
 tL3GD20H sl3gd20h;

//
// Global instance structure for the I2C master driver.
//
 tI2CMInstance g_sI2CInst;


//
// Global constant values. PI and offsets for Accel and Gyro.
//
 const double PI  =3.1415926;

 const float 	GyroOffSetX 	= 0.0352, GyroOffSetY		= 0.0088, GyroOffSetZ		= 0.1124,
							AccelOffSetX 	= 0.3659, AccelOffSetY	= 0.1227, AccelOffSetZ	= 0.3808;

//
// CallBack function. Serves I2C interrupt. 
void
IMU10CallBack(void *pvCallbackData, uint_fast8_t ui8Status)
{
   
    if(ui8Status == I2CM_STATUS_SUCCESS)
    {
       I2CDoneFlag= 1;
    }

   
    ErrorFlag = ui8Status;
}

void
IMU10I2CIntHandler(void)
{
    
    I2CMIntHandler(&g_sI2CInst);
}






bool PololuIMU_Init()
{
	
		uint8_t pui8Data[5];
	 // The I2C3 peripheral must be enabled before use.
    //
		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    GPIOPinConfigure(GPIO_PD0_I2C3SCL);
    GPIOPinConfigure(GPIO_PD1_I2C3SDA);

 
    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);


    // Enable interrupts to the processor.
    //
    IntMasterEnable();

    //
    // Initialize I2C3 peripheral.
    //
    I2CMInit(&g_sI2CInst, I2C3_BASE, INT_I2C3, 0xff, 0xff,SysCtlClockGet());

   


/***************************	Accelerometer initialization **************************************/
		LSM303DLHCAccelInit(&sLSM303DLHCAccel, &g_sI2CInst, LSM303DLHCAccel_I2C_ADDRESS, 
		IMU10CallBack, &sLSM303DLHCAccel);
		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;
		
		
		LSM303DLHCAccelReadModifyWrite(&sLSM303DLHCAccel, LSM303DLHC_O_CTRL1,0x00,LSM303DLHC_CTRL1_ODR_100HZ | 
		LSM303DLHC_CTRL1_AXIS_X_EN| LSM303DLHC_CTRL1_AXIS_Y_EN | LSM303DLHC_CTRL1_AXIS_Z_EN, IMU10CallBack,0);
		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;
		SysCtlDelay(10000000);
		LSM303DLHCAccelReadModifyWrite(&sLSM303DLHCAccel, LSM303DLHC_O_CTRL2,0x00,0x00, IMU10CallBack,0);
		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;
		SysCtlDelay(10000000);	
		
/***************************	Gyroscope initialization **************************************/

		
		L3GD20HInit(&sl3gd20h, &g_sI2CInst, L3GD20H_I2C_ADDRESS, IMU10CallBack,&sl3gd20h);
		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;
		SysCtlDelay(10000000);													
		L3GD20HReadModifyWrite(&sl3gd20h, L3GD20H_O_CTRL1,0xF0,0x0F, IMU10CallBack,0);
		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;
		SysCtlDelay(10000000);	
		
		
		
		L3GD20HReadModifyWrite(&sl3gd20h, L3GD20H_O_CTRL4, ~L3GD20H_CTRL4_FS_M,
		L3GD20H_CTRL4_FS_500DPS, IMU10CallBack,0);
		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;
		SysCtlDelay(10000000);
		
		
		L3GD20HRead(&sl3gd20h,L3GD20H_O_CTRL1,pui8Data,1,IMU10CallBack,0);
		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;
		SysCtlDelay(10000000);
	
		
		SysCtlDelay(10000000);
		

/***************************	Magnetometer initialization **************************************/

		LSM303DLHCMagInit(&sLSM303DLHCMag, &g_sI2CInst, LSM303DLHCMag_I2C_ADDRESS, 
								IMU10CallBack, &sLSM303DLHCMag);

		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;
		

	
		LSM303DLHCMagReadModifyWrite(&sLSM303DLHCMag, LSM303DLHC_O_MAG_CRA,0x63,
		LSM303DLHC_MAG_CRA_DO_30HZ, IMU10CallBack,0);
		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;


		LSM303DLHCMagReadModifyWrite(&sLSM303DLHCMag, LSM303DLHC_O_MAG_CRB,0x10,
		LSM303DLHC_MAG_CRB_GAIN_8_1GAUSS, IMU10CallBack,0);
		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;
		
		
		LSM303DLHCMagReadModifyWrite(&sLSM303DLHCMag, LSM303DLHC_O_MAG_MR,0xF8,
		LSM303DLHC_MAG_MR_MODE_CONTINUOUS, IMU10CallBack,0);
		while(!I2CDoneFlag)
		{
		}
		I2CDoneFlag=0;
		SysCtlDelay(10000000);
	
		
	
		return true;
}

void 
AccelRead( float * ReadingsDestination)
{
		LSM303DLHCAccelDataRead(&sLSM303DLHCAccel, IMU10CallBack, 0);
	
		while(!I2CDoneFlag)
		{	
		}
				
		LSM303DLHCAccelDataAccelGetFloat(&sLSM303DLHCAccel, ReadingsDestination, ReadingsDestination + 1, ReadingsDestination + 2);

		//R
		ReadingsDestination[0]=(-ReadingsDestination[0])-AccelOffSetX;
		ReadingsDestination[1]=(-ReadingsDestination[1])-AccelOffSetY;
		ReadingsDestination[2]=(-ReadingsDestination[2])-AccelOffSetZ;
}

void 
MagnetRead( float * ReadingsDestination)
{
		float temp[]={0,0,0};
	LSM303DLHCMagDataRead(&sLSM303DLHCMag,IMU10CallBack, 0);
	
	while(!I2CDoneFlag)
	{	
	}
	
	LSM303DLHCMagDataMagnetoGetFloat(&sLSM303DLHCMag, ReadingsDestination, ReadingsDestination + 1, ReadingsDestination + 2);
	// convert to uT
	ReadingsDestination[0]*= 1e6;	ReadingsDestination[1] *= 1e6;		ReadingsDestination[2] *= 1e6;
	ReadingsDestination[0]-=	68.245926;	ReadingsDestination[1]+=7.388356;	ReadingsDestination[2]+=7.414432;
	temp[0]=ReadingsDestination[0];temp[1]=ReadingsDestination[1];temp[2]=ReadingsDestination[2];
	ReadingsDestination[0]=	(1.208804	*temp[0])	+(	0.036266*temp[1])+	(0.071890*temp[2]);
	ReadingsDestination[1]=	(0.036266	*temp[0])	+(	1.280031*temp[1])+	(-0.032529*temp[2]);
	ReadingsDestination[2]=	(0.071890	*temp[0])	+(-0.032529	*temp[1])+	(1.113341*temp[2]);
}

void 
GyroRead( float * ReadingsDestination)
{

	L3GD20HDataRead(&sl3gd20h, IMU10CallBack, 0);
	
	while(!I2CDoneFlag)
	{	
	}
	
	L3GD20HDataGyroGetFloat(&sl3gd20h, ReadingsDestination, ReadingsDestination + 1, ReadingsDestination + 2);


	//ReadingsDestination[0]+=GyroOffSetX;
	//ReadingsDestination[1]+=GyroOffSetY;
	//ReadingsDestination[2]+=GyroOffSetZ;
	//
	//Try New EngineON OffSet Values
	ReadingsDestination[0]+=0.0373;
	ReadingsDestination[1]+=0.0043;
	ReadingsDestination[2]+=0.1225;
}



void 
QuaternionToEulerAngles(float q0,	float q1,	float q2,	float q3,	float * EulerAngles)
{
		EulerAngles[0]=atan2f(	2*(q0*q1+q2*q3)	,	1-2*(	q1*q1+q2*q2	))	*180/PI;
		EulerAngles[1]=asinf(	2*(q0*q2-q3*q1)	)												*180/PI;
		EulerAngles[2]=atan2f(	2*(q0*q3+q1*q2)	,	1-2*(	q2*q2+q3*q3	))	*180/PI;
}





