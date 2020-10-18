/*
 * spiLOG.c
 *
 *  Created on: Oct 18, 2020
 *      Author: DC
 */


#include <spi.h>
//#include "spiLOG.h"




//1. Chip Select function
void SPI1_CS_function(int state)
{
	if(state) HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
}

//6. Write multipl bytes register
void SPI1_write_bytes(uint8_t reg, const uint8_t* buf, uint8_t len)
{
	uint8_t spiBuf[3];
	//Put CSN low
	SPI1_CS_function(0);
	//Transmit register address and data
	spiBuf[0] = reg|0x20;
	HAL_SPI_Transmit(&hspi1, spiBuf, 1, 100);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)buf, len, 100);
	//Bring CSN high
	SPI1_CS_function(1);
}



////3. Read single byte from a register
//uint8_t NRF24_read_register(uint8_t reg)
//{
//	uint8_t spiBuf[3];
//	uint8_t retData;
//	//Put CSN low
//	NRF24_csn(0);
//	//Transmit register address
//	spiBuf[0] = reg&0x1F;
//	HAL_SPI_Transmit(&nrf24_hspi, spiBuf, 1, 100);
//	//Receive data
//	HAL_SPI_Receive(&nrf24_hspi, &spiBuf[1], 1, 100);
//	retData = spiBuf[1];
//	//Bring CSN high
//	NRF24_csn(1);
//	return retData;
//}
