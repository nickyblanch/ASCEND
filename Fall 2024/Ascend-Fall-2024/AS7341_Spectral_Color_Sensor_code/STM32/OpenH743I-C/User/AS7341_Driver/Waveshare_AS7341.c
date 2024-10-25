/*****************************************************************************
* | File      	:   AS7341.c
* | Author      :   Waveshare team
* | Function    :   AS7341 driver
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-1-13
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"
#include "Waveshare_AS7341.h"

 eMode_t measureMode;
/******************************************************************************
function:	Read one byte of data to AS7341 via I2C
parameter:  
            Addr: Register address
Info:
******************************************************************************/
static UBYTE AS7341_Read_Byte(UBYTE Addr)
{
    return I2C_Read_Byte(Addr);
}

/******************************************************************************
function:	Read one word of data to AS7341 via I2C
parameter:
            Addr: Register address
Info:
******************************************************************************/
/*
static UWORD AS7341_Read_Word(UBYTE Addr)
{
    return I2C_Read_Word(Addr);
}
*/
/******************************************************************************
function:	Send one byte of data to AS7341 via I2C
parameter:
            Addr: Register address
           Value: Write to the value of the register
Info:
******************************************************************************/
static void AS7341_Write_Byte(UBYTE Addr, UBYTE Value)
{
    I2C_Write_Byte(Addr, Value);
}


/******************************************************************************
function:	AS7341 Initialization
parameter:
Info:
******************************************************************************/
UBYTE AS7341_Init(eMode_t mode)
{
	DEV_I2C_Init(AS7341_ADDRESS<<1);//8-bit address
    //printf("ID = 0x%x\r\n",AS7341_Read_Byte(AS7341_ID));//get AS7341 id	
	AS7341_Enable(true);
	measureMode=mode;
	return 0;
}

/******************************************************************************
function： enable PON
info：	power on
******************************************************************************/
void AS7341_Enable(int flag)
{
	UBYTE data,data1;
	data=AS7341_Read_Byte(AS7341_ENABLE);
    if(flag == true){
    data = data | (1<<0);
    } else {
    data = data & (~1);
    }
	AS7341_Write_Byte(AS7341_ENABLE,data);
    DEV_Delay_ms(500);
    data1=AS7341_Read_Byte(AS7341_ENABLE);
    if(data1 == data)
        printf("Initialization is complete !\r\n");
    else
    {
        printf("initialization is failure !\r\n");
        printf("Please check whether the IIC pin is connected correctly and whether the IIC function is normal \r\n");
        printf("Please press the reset button or run the program again after checking \r\n");
        while(1);
    }
    AS7341_Write_Byte(0x00, 0x30);
}

/******************************************************************************
function： enable Spectral measure
info：	
******************************************************************************/
void AS7341_EnableSpectralMeasure(int flag)//Enable spectral measurement
{
    UBYTE data;
    data=AS7341_Read_Byte(AS7341_ENABLE);
    if(flag == true){
      data = data | (1<<1);
    } else {
      data = data & (~(1<<1));
    }
    AS7341_Write_Byte(AS7341_ENABLE,data);
}

/******************************************************************************
function： enable SMUX
info：	
******************************************************************************/
void AS7341_EnableSMUX(int flag)//Enable multiplexer
/*The other available channels can be accessed by amultiplexer (SMUX) connecting them to one of the internal ADCs.*/
{
  UBYTE data;
    data=AS7341_Read_Byte(AS7341_ENABLE);
  if(flag == true){
    data = data | (1<<4);
  } else {
    data = data & (~(1<<4));
  }
    AS7341_Write_Byte(AS7341_ENABLE,data);
}

/******************************************************************************
function:	enable flicker detection
info：	
******************************************************************************/
void AS7341_EnableFlickerDetection(int flag)
{

  UBYTE data;
  data=AS7341_Read_Byte(AS7341_ENABLE);
  if(flag == true){
    data = data | (1<<6);
  } else {
    data = data & (~(1<<6));
  }
  AS7341_Write_Byte(AS7341_ENABLE,data);
}

/******************************************************************************
function:	choose model for spectral measurement
info：	
******************************************************************************/
void AS7341_Config(eMode_t mode)
{
  UBYTE data;
  AS7341_SetBank(1);
  data=AS7341_Read_Byte(AS7341_CONFIG);
  switch(mode){
    case eSpm : {
      data = (data & (~3)) | eSpm;
    };
	break;
    case eSyns : {
      data = (data & (~3)) | eSyns;
    };
	break;
    case eSynd : {
      data = (data & (~3)) | eSynd;
    };
	break;
    default : break;
  }
  AS7341_Write_Byte(AS7341_CONFIG,data);
  AS7341_SetBank(0);
}

/******************************************************************************
function:	Configure SMUX for sensors F1-4, Clear and NIR
info：	
******************************************************************************/
void F1F4_Clear_NIR() 
{
  AS7341_Write_Byte(0x00, 0x30); 
  AS7341_Write_Byte(0x01, 0x01); 
  AS7341_Write_Byte(0x02, 0x00); 
  AS7341_Write_Byte(0x03, 0x00); 
  AS7341_Write_Byte(0x04, 0x00); 
  AS7341_Write_Byte(0x05, 0x42); 
  AS7341_Write_Byte(0x06, 0x00); 
  AS7341_Write_Byte(0x07, 0x00); 
  AS7341_Write_Byte(0x08, 0x50); 
  AS7341_Write_Byte(0x09, 0x00); 
  AS7341_Write_Byte(0x0A, 0x00); 
  AS7341_Write_Byte(0x0B, 0x00); 
  AS7341_Write_Byte(0x0C, 0x20); 
  AS7341_Write_Byte(0x0D, 0x04); 
  AS7341_Write_Byte(0x0E, 0x00); 
  AS7341_Write_Byte(0x0F, 0x30); 
  AS7341_Write_Byte(0x10, 0x01); 
  AS7341_Write_Byte(0x11, 0x50); 
  AS7341_Write_Byte(0x12, 0x00); 
  AS7341_Write_Byte(0x13, 0x06); 
}
/******************************************************************************
function:	Configure SMUX for sensors F5-8, Clear and NIR
info：	
******************************************************************************/
void F5F8_Clear_NIR() 
{
  AS7341_Write_Byte(0x00, 0x00); 
  AS7341_Write_Byte(0x01, 0x00); 
  AS7341_Write_Byte(0x02, 0x00); 
  AS7341_Write_Byte(0x03, 0x40); 
  AS7341_Write_Byte(0x04, 0x02); 
  AS7341_Write_Byte(0x05, 0x00); 
  AS7341_Write_Byte(0x06, 0x10); 
  AS7341_Write_Byte(0x07, 0x03); 
  AS7341_Write_Byte(0x08, 0x50); 
  AS7341_Write_Byte(0x09, 0x10); 
  AS7341_Write_Byte(0x0A, 0x03); 
  AS7341_Write_Byte(0x0B, 0x00); 
  AS7341_Write_Byte(0x0C, 0x00); 
  AS7341_Write_Byte(0x0D, 0x00); 
  AS7341_Write_Byte(0x0E, 0x24); 
  AS7341_Write_Byte(0x0F, 0x00); 
  AS7341_Write_Byte(0x10, 0x00); 
  AS7341_Write_Byte(0x11, 0x50); 
  AS7341_Write_Byte(0x12, 0x00); 
  AS7341_Write_Byte(0x13, 0x06); 
}
/******************************************************************************
function:	Configure SMUX for flicker detection
info：	
******************************************************************************/
void FDConfig() 
{

  AS7341_Write_Byte(0x00, 0x00); 
  AS7341_Write_Byte(0x01, 0x00); 
  AS7341_Write_Byte(0x02, 0x00); 
  AS7341_Write_Byte(0x03, 0x00); 
  AS7341_Write_Byte(0x04, 0x00); 
  AS7341_Write_Byte(0x05, 0x00); 
  AS7341_Write_Byte(0x06, 0x00); 
  AS7341_Write_Byte(0x07, 0x00); 
  AS7341_Write_Byte(0x08, 0x00); 
  AS7341_Write_Byte(0x09, 0x00); 
  AS7341_Write_Byte(0x0A, 0x00); 
  AS7341_Write_Byte(0x0B, 0x00); 
  AS7341_Write_Byte(0x0C, 0x00); 
  AS7341_Write_Byte(0x0D, 0x00); 
  AS7341_Write_Byte(0x0E, 0x00); 
  AS7341_Write_Byte(0x0F, 0x00); 
  AS7341_Write_Byte(0x10, 0x00); 
  AS7341_Write_Byte(0x11, 0x00); 
  AS7341_Write_Byte(0x12, 0x00); 
  AS7341_Write_Byte(0x13, 0x60);
}

/******************************************************************************
function:	Start the measurement
info：		This function only handles SPM and SYNS modes.
******************************************************************************/
void AS7341_startMeasure(eChChoose_t mode)
{
	  UBYTE data=0;
	  data = AS7341_Read_Byte(AS7341_CFG_0);  
	  data = data & (~(1<<4));

	  AS7341_Write_Byte(AS7341_CFG_0,data);
	  
	  AS7341_EnableSpectralMeasure(false);
	  AS7341_Write_Byte(0xAF,0x10);//SMUX Command config
	  
	  if(mode  == eF1F4ClearNIR)
      F1F4_Clear_NIR();
	  else if(mode  == eF5F8ClearNIR)
	  F5F8_Clear_NIR();
	  AS7341_EnableSMUX(true);
	  if(measureMode == eSyns){
	  AS7341_SetGpioMode(INPUT);
      AS7341_Config(eSyns);
      }
	  else if(measureMode == eSpm){
      AS7341_Config(eSpm);
	  }
	  AS7341_EnableSpectralMeasure(true);
      if(measureMode == eSpm){
        while(!AS7341_MeasureComplete()){
        DEV_Delay_ms(1);
        }
      }
}
/******************************************************************************
function:  read flicker data
info：		
******************************************************************************/
UBYTE AS7341_ReadFlickerData()
{
	  UBYTE flicker;
	  UBYTE data=0;
	  data = AS7341_Read_Byte(AS7341_CFG_0);
	  data = data & (~(1<<4));
	  AS7341_Write_Byte(AS7341_CFG_0,data);
	  AS7341_EnableSpectralMeasure(false);
	  AS7341_Write_Byte(0xAF,0x10);
	  FDConfig();
	  AS7341_EnableSMUX(true);
	  AS7341_EnableSpectralMeasure(true);
	  UBYTE retry = 100;

	  if(retry == 0) printf(" data access error");
	  AS7341_EnableFlickerDetection(true);
	  DEV_Delay_ms(600);
	  flicker = AS7341_Read_Byte(AS7341_STATUS);
	  printf("flicker: %d \r\n",flicker);
	  AS7341_EnableFlickerDetection(false);
	  switch(flicker){
		case 37:
		  flicker = 100;
		  break;
		case 40:
		  flicker = 0;
		  break;
		case 42:
		  flicker = 120;
		  break;		  
		case 44:
		  flicker = 1;
		  break;		  
		case 45:
		  flicker = 2;
		  break;		  
		default:
		  flicker = 2;
	  }
	  return flicker;
}

/******************************************************************************
function:  Determine whether the measurement is complete
info：		
******************************************************************************/

int AS7341_MeasureComplete(){
	UBYTE status;
	status = AS7341_Read_Byte(AS7341_STATUS_2); 
	if((status & (1<<6))){
		return true;
	}
	else{
		return false;
	}
}

/******************************************************************************
function:  Gets data for all channels
info：		
******************************************************************************/
UWORD AS7341_GetChannelData(UBYTE channel)
{
  UWORD data[2];
  UWORD channelData = 0x0000;
  data[0] = AS7341_Read_Byte(AS7341_CH0_DATA_L + channel*2); 
  data[1] = AS7341_Read_Byte(AS7341_CH0_DATA_H + channel*2); 
  channelData = data[1];
  channelData = (channelData<<8) | data[0];
  DEV_Delay_ms(50);
  return channelData;
}

/******************************************************************************
function:  Use SMUX to read data from the low channel
info：		
******************************************************************************/

sModeOneData_t AS7341_ReadSpectralDataOne()
{
  sModeOneData_t data;
  data.channel1 = AS7341_GetChannelData(0);
  data.channel2 = AS7341_GetChannelData(1);
  data.channel3 = AS7341_GetChannelData(2);
  data.channel4 = AS7341_GetChannelData(3);
  data.CLEAR = AS7341_GetChannelData(4);
  data.NIR = AS7341_GetChannelData(5);
  return data;
}

/******************************************************************************
function:  Use SMUX to read data from the high channel
info：		
******************************************************************************/

sModeTwoData_t AS7341_ReadSpectralDataTwo()
{
  sModeTwoData_t data;
  data.channel5 = AS7341_GetChannelData(0);
  data.channel6 = AS7341_GetChannelData(1);
  data.channel7 = AS7341_GetChannelData(2);
  data.channel8 = AS7341_GetChannelData(3);
  data.CLEAR = AS7341_GetChannelData(4);
  data.NIR = AS7341_GetChannelData(5);
  return data;
}

/******************************************************************************
function:	Set GPIO to input or output mode
info：
******************************************************************************/
void AS7341_SetGpioMode(UBYTE mode)
{
  UBYTE data;

  data = AS7341_Read_Byte(AS7341_GPIO_2);  
  if(mode == INPUT){
     data = data | (1<<2);
  }
  
  if(mode == OUTPUT){
     data = data & (~(1<<2));
  }
  AS7341_Write_Byte(AS7341_GPIO_2,data);
}

/******************************************************************************
function:	Configure the ATIME register
info：
******************************************************************************/
void AS7341_ATIME_config(UBYTE value)
{
  AS7341_Write_Byte(AS7341_ATIME,value);
}

/******************************************************************************
function:	Configure the ASTEP register
info：
******************************************************************************/
void AS7341_ASTEP_config(UWORD value)
{
  UBYTE highValue,lowValue;
  lowValue = value & 0x00ff;
  highValue = value >> 8 ;
  AS7341_Write_Byte(AS7341_ASTEP_L,lowValue);
  AS7341_Write_Byte(AS7341_ASTEP_H,highValue);
}

/******************************************************************************
function:	Configure the AGAIN register
value:    0    1    2    3    4    5      6     7     8     9      10
gain:   X0.5 | X1 | X2 | X4 | X8 | X16 | X32 | X64 | X128 | X256 | X512
******************************************************************************/
void AS7341_AGAIN_config(UBYTE value)
{
  if(value > 10) value = 10;
  AS7341_Write_Byte(AS7341_CFG_1,value);
}

/******************************************************************************
function:	enable led
info：true		: Enable
			false		: Anergy
******************************************************************************/
void AS7341_EnableLED(int flag)
{
  UBYTE data=0;
  UBYTE data1=0;
  AS7341_SetBank(1);
  data = AS7341_Read_Byte(AS7341_CONFIG);
  data1 = AS7341_Read_Byte(AS7341_LED);
  if(flag== true)
	{
    data = data | 0x08;
	} 
	else 
	{
    data = data & 0xf7;
    data1 = data1 & 0x7f;
		AS7341_Write_Byte(AS7341_LED,data1);
  }
  AS7341_Write_Byte(AS7341_CONFIG,data);
  AS7341_SetBank(0);
}
/******************************************************************************
function:	set REG_BANK
info：	0: Register access to register 0x80 and above
		1: Register access to register 0x60 to 0x74
******************************************************************************/
void AS7341_SetBank(UBYTE addr)
{
  UBYTE data=0;
  data = AS7341_Read_Byte(AS7341_CFG_0);
  if(addr == 1){
  
    data = data | (1<<4);
  }
  
  if(addr == 0){
  
    data = data & (~(1<<4));
  }
  AS7341_Write_Byte(AS7341_CFG_0,data);
}
/******************************************************************************
function:	Control the brightness of the LED
info：   LED 			 :   true  : LED ON
											 false : LED OFF
         current   :  intensity control
******************************************************************************/
void AS7341_ControlLed(UBYTE LED,UBYTE current)
{
  UBYTE data=0;
  if(current < 1) current = 1;
    current--;
  if(current > 19) current = 19;
  AS7341_SetBank(1); 
	if(LED == true)	
		data = 0x80 | current;
	else	
		data = current;
  AS7341_Write_Byte(AS7341_LED,data);
  DEV_Delay_ms(100);
  AS7341_SetBank(0);
}

/******************************************************************************
function:	Determine whether the threshold setting is exceeded
info：Spectral interruptions occur when the set threshold is exceeded
******************************************************************************/
void AS7341_INTerrupt()
{
  UBYTE data = AS7341_Read_Byte(AS7341_STATUS_1);
  if(data & 0x80){
     printf("Spectral interrupt generation ！\r\n");
  } else {
    return ;
  }
}

/******************************************************************************
function:	clear interrupt
info：		This register is self-clearing, meaning that writing a "1" to any bit in the
	register clears that status bit. 
******************************************************************************/
void AS7341_ClearInterrupt()
{
	
  AS7341_Write_Byte(AS7341_STATUS_1,0xff);

}
/******************************************************************************
function:	enable spectral interrupt
info：
******************************************************************************/
void AS7341_EnableSpectralInterrupt(int flag)
{
  UBYTE data;
  data = AS7341_Read_Byte(AS7341_INTENAB);
  if(flag == true)
  {
    data = data | (1<<3);
    AS7341_Write_Byte(AS7341_INTENAB,data);
  }
  else{
    data = data & (~(1<<3));
    AS7341_Write_Byte(AS7341_INTENAB,data);
  }
  
}
/******************************************************************************
function:Spectral Interrupt Persistence
	value:      CHANNEL:
	0			Every spectral cycle generates aninterrupt
	1			1
	2			2
	3			3
	4			5
	5			10
	...			5*(value-3)
	14			55
	15			60
******************************************************************************/
void AS7341_SetInterruptPersistence(UBYTE value)
{
	UBYTE data;
	data= value;
	AS7341_Write_Byte(AS7341_PERS,data);
	data = AS7341_Read_Byte(AS7341_PERS);
}
/******************************************************************************
function:	Set the interrupt threshold up and 
info：
******************************************************************************/
void AS7341_SetThreshold(UWORD lowThre,UWORD highThre)
{
  if(lowThre >= highThre)return ;
  else
  
  AS7341_Write_Byte(AS7341_SP_TH_L_LSB,lowThre);
  AS7341_Write_Byte(AS7341_SP_TH_L_MSB,lowThre>>8);
  
  AS7341_Write_Byte(AS7341_SP_TH_H_LSB,highThre);
  AS7341_Write_Byte(AS7341_SP_TH_H_MSB,highThre>>8); 
  
  DEV_Delay_ms(20);
}
/******************************************************************************
function:	Set the Spectral Threshold Channel
		VALUE 			CHANNEL
		0 				CH0
		1 				CH1
		2 				CH2
		3 				CH3
		4 				CH4
******************************************************************************/
void AS7341_SetSpectralThresholdChannel(UBYTE value)
{
	AS7341_Write_Byte(AS7341_CFG_12,value);
}


/******************************************************************************
function:	get low threshold
info：
******************************************************************************/

UWORD AS7341_GetLowThreshold()
{
  uint16_t data; 
  data = AS7341_Read_Byte(AS7341_SP_TH_L_LSB);  
  data = (AS7341_Read_Byte(AS7341_SP_TH_L_MSB)<<8) | data; 
  return data ;
}

/******************************************************************************
function:	get high threshold
info：
******************************************************************************/
UWORD AS7341_GetHighThreshold()
{
  uint16_t data;
  data = AS7341_Read_Byte(AS7341_SP_TH_H_LSB);
  data = (AS7341_Read_Byte(AS7341_SP_TH_H_MSB)<<8) | data;
  return data ;
}

/******************************************************************************
function:	syns interrupt set
info：
******************************************************************************/
void AS7341_SynsINT_sel()
{
	AS7341_Write_Byte(AS7341_CONFIG,0x05);
}


/******************************************************************************
function:	disable power,spectral reading, flicker detection  
info：
******************************************************************************/
void AS7341_disableALL()
{
	AS7341_Write_Byte(AS7341_ENABLE ,0x02);
}
