/*
 * spiLOG.h
 *
 *  Created on: Oct 18, 2020
 *      Author: DC
 */

#ifndef SPILOG_H_
#define SPILOG_H_

//1. Chip Select function
void SPI1_CS_function(int state);

//6. Write multiple bytes to a register
void SPI1_write_bytes(uint8_t reg, const uint8_t* buf, uint8_t len);

#endif /* SPILOG_H_ */
