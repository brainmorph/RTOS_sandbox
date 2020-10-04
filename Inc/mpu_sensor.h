/*
 * mpu_sensor.h
 *
 *  Created on: Oct 3, 2020
 *      Author: DC
 */

#ifndef MPU_SENSOR_H_
#define MPU_SENSOR_H_




void InitMPU(void);
void ReadAcceleration(float* floatX, float* floatY, float* floatZ);
void ReadGyro(float* floatX, float* floatY, float* floatZ);



#endif /* MPU_SENSOR_H_ */
