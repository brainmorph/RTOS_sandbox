/*
 * mpu9250.h
 *
 *  Created on: Oct 3, 2020
 *      Author: DC
 */

#ifndef MPU9250_H_
#define MPU9250_H_

#include <stdint.h>

void ReadAcceleration9250(float* floatX, float* floatY, float* floatZ);
void ReadGyro9250(float* floatX, float* floatY, float* floatZ);

void InitMPU9250(void);

#endif /* mpu9250.h */
