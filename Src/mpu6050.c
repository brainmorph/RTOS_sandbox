/*
 * mpu6050.c
 *
 *  Created on: Jun 16, 2020
 *      Author: DC
 */

#include "mpu6050.h"
#include "i2c.h"
#include "logging.h"
#include "assert.h"

/* Static Function Declarations */
static uint8_t readMPUreg(uint8_t reg);
static void readMPUregs(uint8_t reg, uint16_t size, uint8_t* data);
static void writeMPUreg(uint8_t reg, uint8_t value);
//static void configMPUFilter();



#ifdef MPU6050
#define WHO_AM_I 0x75
#define WHO_AM_I_RETURN_VAL 0x68
#define PWR_MGMT_1 0x6B
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#endif

#define MPU9250
#ifdef MPU9250
#define WHO_AM_I 0x75
#define WHO_AM_I_RETURN_VAL 0x71
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#endif

void InitMPU(void)
{
	volatile uint8_t value = 0;

	//read a register over I2C
	value = readMPUreg(WHO_AM_I);
	assert(value == WHO_AM_I_RETURN_VAL); // suspend operation if not true; there's a major issue and there's no point continuing

	value = readMPUreg(0x6B);
	writeMPUreg(PWR_MGMT_1, 0x00); // wake the IMU
	readMPUreg(PWR_MGMT_1);

	value = readMPUreg(PWR_MGMT_2);
	writeMPUreg(PWR_MGMT_2, 0x00); // enable all sensors
	readMPUreg(PWR_MGMT_2);

	readMPUreg(ACCEL_CONFIG); // read accel config register
	writeMPUreg(ACCEL_CONFIG, 0x10); // configure fullscale for +-8 g
	value = readMPUreg(ACCEL_CONFIG); // confirm

	readMPUreg(GYRO_CONFIG); // read gyro config register
	writeMPUreg(GYRO_CONFIG, 0x08); // configure fullscale for +- 500 degress/s
	value = readMPUreg(GYRO_CONFIG); // confirm

	value = value;

//	configMPUFilter(); // apply filtering to IMU readings
}

/*
 * Read specified register from MPU6050 module.
 *
 * Input: register address
 *
 * Output: return 8bit register value
 */
static uint8_t readMPUreg(uint8_t reg)
{
	uint16_t deviceAddress = 0x68;
	uint16_t shiftedAddress = deviceAddress << 1;
	uint8_t pData[100];
	pData[0] = reg; //register in question
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c3, shiftedAddress, pData, 1, 1000); //select MPU register
	if(status != HAL_OK)
	{
		// TODO: log error
		log_incrementErrorCount();
	}

	uint8_t value = 0;
	status = HAL_I2C_Master_Receive(&hi2c3, shiftedAddress, &value, 1, 1000); //read from MPU register
	return value;
}

/*
 * Read multiple registers from MPU6050 module.
 *
 * Input: register address
 *
 * Output: fill data buffer with register values
 */
static void readMPUregs(uint8_t reg, uint16_t size, uint8_t* data)
{
	uint16_t deviceAddress = 0x68;
	uint16_t shiftedAddress = deviceAddress << 1;
	uint8_t pData[100];
	pData[0] = reg; //register in question
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c3, shiftedAddress, pData, 1, 1000); //select register
	if(status != HAL_OK)
	{
		// TODO: log error
		log_incrementErrorCount();
	}

	status = HAL_I2C_Master_Receive(&hi2c3, shiftedAddress, data, size, 1000); //read from register
	if(status != HAL_OK)
	{
		// TODO: log error
		log_incrementErrorCount();
	}
}

/*
 * Write value to specified register
 *
 * Input: register address, value to write
 */
static void writeMPUreg(uint8_t reg, uint8_t value) // TODO: move to separate module
{
	uint16_t deviceAddress = 0x68;
	uint16_t shiftedAddress = deviceAddress << 1;
	uint8_t pData[100];
	pData[0] = reg; //register in question
	pData[1] = value; //value to write
	uint16_t Size = 2; //we need to send 2 bytes of data (check out mpu datasheet... write register operation is defined this way)
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c3, shiftedAddress, pData, Size, 1000); //select register and write to it all in one
	if(status != HAL_OK)
	{
		// TODO: log error
	}
}

//static void configMPUFilter()
//{
//	// Read register
//	volatile int16_t config = 0;
//	config = readMPUreg(0x1A);
//
//	config &= 0xF8;
//	config |= 0x0; // this is the value that goes into register
//
//	writeMPUreg(0x1A, config);
//	volatile uint8_t test = readMPUreg(0x1A);
//	test = test;
//}

void ReadAcceleration(float* floatX, float* floatY, float* floatZ)
{
	volatile uint8_t test1 = readMPUreg(0x1C);
	test1 = test1;

	// Read x,y,z all acceleration in one go to guarantee they're from same sample
	uint8_t data[10] = {0};
	readMPUregs(0x3B, 8, data); // read consecutive bytes

	volatile int16_t aX = (data[0] << 8) | data[1];
	volatile int16_t aY = (data[2] << 8) | data[3];
	volatile int16_t aZ = (data[4] << 8) | data[5];

	volatile int16_t temp = (data[6] << 8) | data[7];

	volatile float temperature = ((float)temp / 340.0) + 36.53; // straight from MPU6050 datasheet. No explanation given why these numbers
	temperature = temperature;


	volatile uint8_t temp1 = readMPUreg(0x41);
	volatile uint8_t temp2 = readMPUreg(0x42);
	volatile int16_t temp3 = (temp1 << 8) | temp2;


	/* Temperature calculation for 9250 taken from
	 * https://github.com/bolderflight/MPU9250/blob/master/src/MPU9250.cpp
	 */
    const float _tempScale = 333.87f;
    const float _tempOffset = 21.0f;
	temperature2 = (((float)temp3 - _tempOffset) / _tempScale) + _tempOffset;


	*floatX = (float)aX * (8.0/32767.0); // FS=+-8g
	*floatY = (float)aY * (8.0/32767.0);
	*floatZ = (float)aZ * (8.0/32767.0);

	//convert from g to m/s^2
	*floatX *= 9.807;
	*floatY *= 9.807;
	*floatZ *= 9.807;
}



void ReadGyro(float* floatX, float* floatY, float* floatZ)
{
	// Read x,y,z all gyro in one go to guarantee they're from same sample
	uint8_t data[10] = {0};
	readMPUregs(0x43, 8, data); // read consecutive bytes

	volatile int16_t gX = (data[0] << 8) | data[1];
	volatile int16_t gY = (data[2] << 8) | data[3];
	volatile int16_t gZ = (data[4] << 8) | data[5];


	*floatX = (float)gX * (500.0/32767.0); // FS=+-500 deg/s
	*floatY = (float)gY * (500.0/32767.0);
	*floatZ = (float)gZ * (500.0/32767.0);

}
