/*
 * mpu_sensor.c
 *
 *  Created on: Oct 3, 2020
 *      Author: DC
 */

#include "mpu_sensor.h"

/* !!! --- Select the appropriate MPU --- !!! */
//#define MPU6050
#define MPU9250


#ifdef MPU6050
#include "mpu6050.h"
#endif

#ifdef MPU9250
#include "mpu9250.h"
#endif


typedef struct
{
	void (*InitMPU)(void);

	void (*ReadAcceleration)(float* floatX, float* floatY, float* floatZ);
	void (*ReadGyro)(float* floatX, float* floatY, float* floatZ);

} MPUSensor;

static MPUSensor mpuSensor;


/* Private Functions */
static void SetupIMUSensor()
{
#ifdef MPU6050
	mpuSensor.InitMPU = InitMPU6050;
	mpuSensor.ReadAcceleration = ReadAcceleration6050;
	mpuSensor.ReadGyro = ReadGyro6050;
#endif

#ifdef MPU9250
	mpuSensor.InitMPU = InitMPU9250;
	mpuSensor.ReadAcceleration = ReadAcceleration9250;
	mpuSensor.ReadGyro = ReadGyro9250;
#endif
}


/* Public Functions */

void InitMPU(void)
{
	SetupIMUSensor();

	mpuSensor.InitMPU();
}

void ReadAcceleration(float* floatX, float* floatY, float* floatZ)
{
	mpuSensor.ReadAcceleration(floatX, floatY, floatZ);
}

void ReadGyro(float* floatX, float* floatY, float* floatZ)
{
	mpuSensor.ReadGyro(floatX, floatY, floatZ);
}
