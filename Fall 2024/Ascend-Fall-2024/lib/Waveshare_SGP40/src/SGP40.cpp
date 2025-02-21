#include "SGP40.h"

UBYTE  CRC_TABLE[] = {
	0, 49, 98, 83, 196, 245, 166, 151, 185, 136, 219, 234, 125, 76, 31, 46,
	67, 114, 33, 16, 135, 182, 229, 212, 250, 203, 152, 169, 62, 15, 92, 109,
	134, 183, 228, 213, 66, 115, 32, 17, 63, 14, 93, 108, 251, 202, 153, 168,
	197, 244, 167, 150, 1, 48, 99, 82, 124, 77, 30, 47, 184, 137, 218, 235,
	61, 12, 95, 110, 249, 200, 155, 170, 132, 181, 230, 215, 64, 113, 34, 19,
	126, 79, 28, 45, 186, 139, 216, 233, 199, 246, 165, 148, 3, 50, 97, 80,
	187, 138, 217, 232, 127, 78, 29, 44, 2, 51, 96, 81, 198, 247, 164, 149,
	248, 201, 154, 171, 60, 13, 94, 111, 65, 112, 35, 18, 133, 180, 231, 214,
	122, 75, 24, 41, 190, 143, 220, 237, 195, 242, 161, 144, 7, 54, 101, 84,
	57, 8, 91, 106, 253, 204, 159, 174, 128, 177, 226, 211, 68, 117, 38, 23,
	252, 205, 158, 175, 56, 9, 90, 107, 69, 116, 39, 22, 129, 176, 227, 210,
	191, 142, 221, 236, 123, 74, 25, 40, 6, 55, 100, 85, 194, 243, 160, 145,
	71, 118, 37, 20, 131, 178, 225, 208, 254, 207, 156, 173, 58, 11, 88, 105,
	4, 53, 102, 87, 192, 241, 162, 147, 189, 140, 223, 238, 121, 72, 27, 42,
	193, 240, 163, 146, 5, 52, 103, 86, 120, 73, 26, 43, 188, 141, 222, 239,
	130, 179, 224, 209, 70, 119, 36, 21, 59, 10, 89, 104, 255, 206, 157, 172
};

//Without_humidity_compensation
//sgp40_measure_raw + 2*humi + CRC + 2*temp + CRC
UBYTE  WITHOUT_HUM_COMP[8] = {0X26, 0X0F, 0X80, 0X00, 0XA2, 0X66, 0X66, 0X93}; // default Temperature=25 Humidity=50
UBYTE WITH_HUM_COMP[8] = {0x26, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //Manual input

/******************************************************************************
  function:	Send one byte of data to  I2C dev
  parameter:
            Addr: Register address
            Value: Write to the value of the register
  Info:
******************************************************************************/
static void SGP40_Write(UBYTE *Value, UBYTE num)
{
	I2C_Write_Nbyte(Value, num);
}

/******************************************************************************
  function:	 read one byte of data to  I2C dev
  parameter:
            Addr: Register address
  Info:
******************************************************************************/
static UWORD SGP40_Read()
{
	//(address, 0, 3)#last byte is CRC8
	UWORD rdata;
	rdata = I2C_Read_Nbyte(0, 3);

	return rdata;
}

static UBYTE CRC8_MAXIM(UBYTE msb,UBYTE lsb)
{
	UBYTE crc = 0xff;
	crc ^= msb;
	crc = CRC_TABLE[crc];
	crc ^= lsb;
	crc = CRC_TABLE[crc];
	// Serial.print("CRC = 0X");
	// Serial.print(crc, HEX);
	return crc;
}

/******************************************************************************
  function:	TSL2591 Initialization
  parameter:
  Info:
******************************************************************************/
UBYTE SGP40_Init(void)
{
	DEV_ModuleInit();
	DEV_I2C_Init(SGP40_ADDR);

	Serial.print("SGP40 VOC Sensor Init\r\n");

	//feature set 0x3220
	UBYTE wbuf[2];
	wbuf[0] = 0x20;
	wbuf[1] = 0x2f;
	SGP40_Write(wbuf, 2);
	DEV_Delay_ms(500);
	UWORD Rdata = SGP40_Read();
	if(Rdata != 0x3220) { // 0x3220
		Serial.print("feature set should = 0x3220, but val = 0X");
		Serial.println(Rdata, HEX);
		return 1;
	}

	// Self Test 0x4B00 is failed, 0xD400 pass
	wbuf[0] = 0X28;
	wbuf[1] = 0X0E;
	SGP40_Write(wbuf, 2); //feature set 0xD400
	DEV_Delay_ms(500); // must
	Rdata = SGP40_Read();
	if(Rdata != 0xD400) {
		Serial.print("Self Test should = 0xD400, but val = 0X");
		Serial.println(Rdata, HEX);
		return 1;
	}

	// reset
	DEV_Delay_ms(500);
	wbuf[0] = 0X00;
	wbuf[1] = 0X06;
	SGP40_Write(wbuf, 2); //feature set 0xD400

	return 0;
}

UBYTE SGP40_MeasureRaw(float temp, float humi)
{
	//Serial.print("measureRaw\r\n");

	// 2*humi + CRC
	uint16_t paramh;
	paramh = (UWORD)((humi * 65535) / 100 + 0.5); // for DATASHEET page13
	WITH_HUM_COMP[2] = paramh >> 8;
	WITH_HUM_COMP[3] = paramh & 0xFF;
	WITH_HUM_COMP[4] = CRC8_MAXIM(WITH_HUM_COMP[2], WITH_HUM_COMP[3]);
	// 2*temp + CRC
	uint16_t paramt;
	paramt = (uint16_t)(((temp + 45) * 65535) / 175);
	WITH_HUM_COMP[5] = paramt >> 8;
	WITH_HUM_COMP[6] = paramt & 0xFF;
	WITH_HUM_COMP[7] = CRC8_MAXIM(WITH_HUM_COMP[5], WITH_HUM_COMP[6]);

	SGP40_Write(WITH_HUM_COMP, 8);

	DEV_Delay_ms(500);
	UWORD Rdata = SGP40_Read();
	// Serial.println(Rdata);
	return Rdata;
}

UBYTE SGP40_MeasureVOC(float temp, float humi)
{
	VocAlgorithmParams voc_algorithm_params;
	VocAlgorithm_init(&voc_algorithm_params);
	
	//Serial.print("voc index\r\n");

	int32_t voc_index;
	uint16_t sraw = SGP40_MeasureRaw(temp, humi);

	VocAlgorithm_process(&voc_algorithm_params, sraw, &voc_index);
	//Serial.println(voc_index);
	return voc_index;
}


