#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_
/***********************************************************************************************************************
			------------------------------------------------------------------------
			|\\\																///|
			|\\\					Hardware interface							///|
			------------------------------------------------------------------------
***********************************************************************************************************************/
#include "Arduino.h"
//#include <avr/pgmspace.h>
#include "Wire.h"

#include "Debug.h"


#define DEV_SPI 0
#define DEV_I2C 1

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define INT_PIN 8


/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) digitalWrite(_pin, _value == 0? LOW:HIGH)
#define DEV_Digital_Read(_pin) digitalRead(_pin)

/*------------------------------------------------------------------------------------------------------*/
UBYTE DEV_ModuleInit(void);
void  DEV_ModuleExit(void);

void DEV_I2C_Init(uint8_t Add);

void I2C_Write_Byte(UBYTE Cmd, UBYTE value);
int I2C_Read_Byte(UBYTE Cmd);

int I2C_Read_Word(UBYTE Cmd);

void I2C_Write_Nbyte(UBYTE *data, UBYTE num);
UWORD I2C_Read_Nbyte(UBYTE Cmd, UBYTE num);
void DEV_GPIO_Mode(UWORD Pin, UWORD mode);
//void DEV_Digital_Write(UWORD Pin, UBYTE Value);
//UBYTE DEV_Digital_Read(UWORD Pin);

void DEV_Delay_ms(UDOUBLE xms);

// void DEV_SPI_WriteByte(UBYTE Value);
// void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len);

#endif
