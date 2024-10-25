#ifndef _Waveshare_AS7341_H_
#define _Waveshare_AS7341_H_

#include "DEV_Config.h"

#define true 1
#define false 0
#define INPUT 0
#define OUTPUT 1
#define AS7341_ADDRESS       (0X39)

#define AS7341_ASTATUS     (0X60) //ASTATUS Register (Address 0x60 or 0x94)

#define AS7341_CONFIG      (0X70)
#define AS7341_STAT        (0X71)
#define AS7341_EDGE        (0X72)
#define AS7341_CPIO        (0X73)
#define AS7341_LED         (0X74)

#define AS7341_ENABLE      (0X80)
#define AS7341_ATIME       (0X81)
#define AS7341_WTIME       (0X83)

#define AS7341_SP_TH_L_LSB (0X84)
#define AS7341_SP_TH_L_MSB (0X85)
#define AS7341_SP_TH_H_LSB (0X86)
#define AS7341_SP_TH_H_MSB (0X87)
#define AS7341_AUXID       (0X90)
#define AS7341_REVID       (0X91)

#define AS7341_ID          (0X92)
#define AS7341_STATUS_1    (0X93)
//#define AS7341_ASTATUS     (0X94)


#define AS7341_CH0_DATA_L  (0X95)
#define AS7341_CH0_DATA_H  (0X96)
#define AS7341_CH1_DATA_L  (0X97)
#define AS7341_CH1_DATA_H  (0X98)
#define AS7341_CH2_DATA_L  (0X99)
#define AS7341_CH2_DATA_H  (0X9A)
#define AS7341_CH3_DATA_L  (0X9B)
#define AS7341_CH3_DATA_H  (0X9C)
#define AS7341_CH4_DATA_L  (0X9D)
#define AS7341_CH4_DATA_H  (0X9E)
#define AS7341_CH5_DATA_L  (0X9F)
#define AS7341_CH5_DATA_H  (0XA0)

#define AS7341_STATUS_2    (0XA3)
#define AS7341_STATUS_3    (0XA4)
#define AS7341_STATUS_5    (0XA6)
#define AS7341_STATUS_6    (0XA7)
#define AS7341_CFG_0       (0XA9)
#define AS7341_CFG_1       (0XAA)
#define AS7341_CFG_3       (0XAC)
#define AS7341_CFG_6       (0XAF)
#define AS7341_CFG_8       (0XB1)
#define AS7341_CFG_9       (0XB2)
#define AS7341_CFG_10      (0XB3)
#define AS7341_CFG_12      (0XB5)


#define AS7341_PERS          (0XBD)
#define AS7341_GPIO_2        (0XBE)
#define AS7341_ASTEP_L       (0XCA)
#define AS7341_ASTEP_H       (0XCB)
#define AS7341_AGC_GAIN_MAX  (0XCF)
#define AS7341_AZ_CONFIG     (0XD6)
#define AS7341_FD_TIME_1     (0XD8)
#define AS7341_TIME_2        (0XDA)
#define AS7341_CFG0          (0XD7)
#define AS7341_STATUS        (0XDB)
#define AS7341_INTENAB       (0XF9)
#define AS7341_CONTROL       (0XFA)
#define AS7341_FIFO_MAP      (0XFC)
#define AS7341_FIFO_LVL      (0XFD)
#define AS7341_FDATA_L       (0XFE)
#define AS7341_FDATA_H       (0XFF)


#define AS7341_GPIO               4


  /**
    The measurement mode of spectrum snesor 
  */
  typedef enum {
    eSpm = 0,/**<SPM>*/
    eSyns = 1,/**<SYNS*/
    eSynd = 3,/**<SYND>*/
    
  }eMode_t;
  
   /**
    The modes of channel mapping 
  */
  typedef enum{
    eF1F4ClearNIR,/**<Map the values of the registers of 6 channels to F1,F2,F3,F4,clear,NIR>*/
    eF5F8ClearNIR,/**<Map the values of the registers of 6 channels to F5,F6,F7,F8,clear,NIR>*/
  }eChChoose_t;
  
    /**
    Represent 10 different photodiode measurement channels 
  */
  typedef enum{
    eCH_F1,
    eCH_F2,
    eCH_F3,
    eCH_F4,
    eCH_F5,
    eCH_F6,
    eCH_F7,
    eCH_F8,
    eCH_CLEAR,
    eCH_NIR,
  }eChannel_t;
  
   /**
    The values of the registers of 6 channels under eF1F4ClearNIR
  */
  typedef struct{
    UWORD channel1;/**<channel1 diode data>*/
    UWORD channel2;/**<channel2 diode data>*/
    UWORD channel3;/**<channel3 diode data>*/
    UWORD channel4;/**<channel4 diode data>*/
    UWORD CLEAR;/**<clear diode data>*/
    UWORD NIR;/**<NIR diode data>*/
  }sModeOneData_t;

    /**
    The values of the registers of 6 channels under eF5F8ClearNIR
  */
  typedef struct{
    UWORD channel5;/**<channel5 diode data>*/
    UWORD channel6;/**<channel6 diode data>*/
    UWORD channel7;/**<channel7 diode data>*/
    UWORD channel8;/**<channel8 diode data>*/
    UWORD CLEAR;/**<clear diode data>*/
    UWORD NIR;/**<NIR diode data>*/
  }sModeTwoData_t;
  
UBYTE AS7341_Init(eMode_t mode);
void AS7341_Enable(int flag);
void AS7341_EnableSpectralMeasure(int flag);
void AS7341_EnableSMUX(int flag);
void AS7341_EnableFlickerDetection(int flag);
void F1F4_Clear_NIR(void);
void F5F8_Clear_NIR(void);
void FDConfig(void);
void AS7341_startMeasure(eChChoose_t mode);
UBYTE AS7341_ReadFlickerData(void);
UWORD AS7341_GetChannelData(UBYTE channel);
sModeOneData_t AS7341_ReadSpectralDataOne(void);
sModeTwoData_t AS7341_ReadSpectralDataTwo(void);
void AS7341_Config(eMode_t mode);
int AS7341_MeasureComplete(void);
void AS7341_SetGpioMode(UBYTE mode);
void AS7341_SetBank(UBYTE addr);
void AS7341_EnableLED(int flag);
void AS7341_ControlLed(UBYTE LED,UBYTE current);
void AS7341_INTerrupt(void);
void AS7341_ClearInterrupt(void);
void AS7341_EnableSpectralInterrupt(int flag);
void AS7341_SetThreshold(UWORD lowThre,UWORD highThre);
UWORD AS7341_GetLowThreshold(void);
UWORD AS7341_GetHighThreshold(void);
void AS7341_ATIME_config(UBYTE value);
void AS7341_ASTEP_config(UWORD value);
void AS7341_AGAIN_config(UBYTE value);
void AS7341_SetInterruptPersistence(UBYTE value);
void AS7341_SetSpectralThresholdChannel(UBYTE value);
void AS7341_SynsINT_sel(void);
void AS7341_disableALL(void);
#endif
