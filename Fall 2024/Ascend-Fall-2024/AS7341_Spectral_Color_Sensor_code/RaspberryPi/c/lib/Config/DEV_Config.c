/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2019-07-08
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"
#include <unistd.h>
#include <fcntl.h>

#if USE_LGPIO_LIB
int GPIO_Handle;
int I2C_Handle;
#endif

uint32_t fd;
int INT_PIN;
/******************************************************************************
function:	Equipment Testing
parameter:
Info:   Only supports Jetson Nano and Raspberry Pi
******************************************************************************/
static int DEV_Equipment_Testing(void)
{
	int i;
	int fd;
	char value_str[20];
	fd = open("/etc/issue", O_RDONLY);
    printf("Current environment: ");
	while(1) {
		if (fd < 0) {
			return -1;
		}
		for(i=0;; i++) {
			if (read(fd, &value_str[i], 1) < 0) {
				return -1;
			}
			if(value_str[i] ==32) {
				printf("\r\n");
				break;
			}
			printf("%c",value_str[i]);
		}
		break;
	}

	if(i<5) {
		printf("Unrecognizable\r\n");
        return -1;
	} else {
		char RPI_System[10]   = {"Raspbian"};
		for(i=0; i<6; i++) {
			if(RPI_System[i] != value_str[i]) {
                #if USE_DEV_LIB    
                    return 'J';
                #endif
                return -1;
			}
		}
        return 'R';
	}
	return -1;
}


/******************************************************************************
function:	GPIO Function initialization and transfer
parameter:
Info:
******************************************************************************/
void DEV_GPIO_Mode(UWORD Pin, UWORD Mode)
{
    /*
        0:  INPT   
        1:  OUTP
    */
#ifdef USE_BCM2835_LIB  
    if(Mode == 0 || Mode == BCM2835_GPIO_FSEL_INPT){
        bcm2835_gpio_fsel(Pin, BCM2835_GPIO_FSEL_INPT);
    }else {
        bcm2835_gpio_fsel(Pin, BCM2835_GPIO_FSEL_OUTP);
    }
#elif USE_WIRINGPI_LIB
    if(Mode == 0 || Mode == INPUT){
        pinMode(Pin, INPUT);
        pullUpDnControl(Pin, PUD_UP);
    }else{ 
        pinMode(Pin, OUTPUT);
    }
#elif  USE_LGPIO_LIB  
    if(Mode == 0 || Mode == LG_SET_INPUT){
        lgGpioClaimInput(GPIO_Handle,LFLAGS,Pin);
        // printf("IN Pin = %d\r\n",Pin);
    }else{
        lgGpioClaimOutput(GPIO_Handle, LFLAGS, Pin, LG_LOW);
        // printf("OUT Pin = %d\r\n",Pin);
    }
#elif USE_GPIOD_LIB
	if(Mode == 0 || Mode == GPIOD_IN) {
		GPIOD_Direction(Pin, GPIOD_IN);
		// Debug("IN Pin = %d\r\n",Pin);
	} else {
		GPIOD_Direction(Pin, GPIOD_OUT);
		// Debug("OUT Pin = %d\r\n",Pin);
	}
#endif   
}

void DEV_Digital_Write(UWORD Pin, UBYTE Value)
{
#ifdef USE_BCM2835_LIB
    bcm2835_gpio_write(Pin, Value);
    
#elif USE_WIRINGPI_LIB
    digitalWrite(Pin, Value);
    
#elif  USE_LGPIO_LIB  
    lgGpioWrite(GPIO_Handle, Pin, Value);
#elif USE_GPIOD_LIB
	GPIOD_Write(Pin, Value);
    
#endif
}

UBYTE DEV_Digital_Read(UWORD Pin)
{
    UBYTE Read_value = 0;
#ifdef USE_BCM2835_LIB
    Read_value = bcm2835_gpio_lev(Pin);
    
#elif USE_WIRINGPI_LIB
    Read_value = digitalRead(Pin);
#elif  USE_LGPIO_LIB  
    Read_value = lgGpioRead(GPIO_Handle,Pin);
#elif USE_GPIOD_LIB
	Read_value = GPIOD_Read(Pin);
#endif
    return Read_value;
}


/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms)
{
#ifdef USE_BCM2835_LIB
    bcm2835_delay(xms);
#elif USE_WIRINGPI_LIB
    delay(xms);
#elif  USE_LGPIO_LIB 
    lguSleep(xms/1000.0);
#elif USE_GPIOD_LIB
	UDOUBLE i;
	for(i=0; i < xms; i++) {
		usleep(1000);
	}
#endif
}


void GPIO_Config(void)
{
    int Equipment = DEV_Equipment_Testing();
    if(Equipment=='R'){
        INT_PIN = 4;
    }else if(Equipment=='J'){
        #if USE_DEV_LIB
        INT_PIN = GPIO4;
        #endif
    }else{
        printf("Device read failed or unrecognized!!!\r\n");
        while(1);
    }
    
    DEV_GPIO_Mode(INT_PIN, 0);
}

/******************************************************************************
function:	I2C Function initialization and transfer
parameter:
Info:
******************************************************************************/
void DEV_I2C_Init(uint8_t Add)
{
#if DEV_I2C
    #ifdef USE_BCM2835_LIB
        printf("BCM2835 I2C Device\r\n");  
        bcm2835_i2c_begin();
        bcm2835_i2c_setSlaveAddress(Add);
        
    #elif USE_WIRINGPI_LIB
        printf("WIRINGPI I2C Device\r\n");       
        fd = wiringPiI2CSetup(Add);
    #elif  USE_LGPIO_LIB 
        printf("LGPIO I2C Device\r\n");   
        I2C_Handle = lgI2cOpen(1, Add, 0);

    #elif USE_DEV_LIB
        printf("DEV I2C Device\r\n"); 
        DEV_HARDWARE_I2C_begin("/dev/i2c-1");
        DEV_HARDWARE_I2C_setSlaveAddress(Add);
    #endif
#endif
}

void I2C_Write_Byte(uint8_t Cmd, uint8_t value)
{
	int ref;
#if DEV_I2C
    #ifdef USE_BCM2835_LIB
        char wbuf[2]={Cmd, value};
        bcm2835_i2c_write(wbuf, 2);
    #elif USE_WIRINGPI_LIB
        //wiringPiI2CWrite(fd,Cmd);
        ref = wiringPiI2CWriteReg8(fd, (int)Cmd, (int)value);
        while(ref != 0) {
            ref = wiringPiI2CWriteReg8 (fd, (int)Cmd, (int)value);
            if(ref == 0)
                break;
        }
    #elif  USE_LGPIO_LIB   
        lgI2cWriteByteData(I2C_Handle, Cmd, value);
    #elif USE_DEV_LIB
        char wbuf[2]={Cmd, value};
        DEV_HARDWARE_I2C_write(wbuf, 2);

    #endif
#endif
}

int I2C_Read_Byte(uint8_t Cmd)
{
	int ref;
#if DEV_I2C
    #ifdef USE_BCM2835_LIB
        char rbuf[2]={0};
        bcm2835_i2c_read_register_rs(&Cmd, rbuf, 1);
        ref = rbuf[0];
        
    #elif USE_WIRINGPI_LIB
        ref = wiringPiI2CReadReg8 (fd, (int)Cmd);
    
    #elif  USE_LGPIO_LIB 
        ref = lgI2cReadByteData(I2C_Handle, Cmd);

    #elif USE_DEV_LIB
        char rbuf[2]={0};
        DEV_HARDWARE_I2C_read(Cmd, rbuf, 1);
        ref = rbuf[0];
    #endif
#endif
    return ref;
}

int I2C_Read_Word(uint8_t Cmd)
{
	int ref;
#if DEV_I2C
    #ifdef USE_BCM2835_LIB
        char rbuf[2] = {0};
        bcm2835_i2c_read_register_rs(&Cmd, rbuf, 2);
        ref = rbuf[1]<<8 | rbuf[0];
        
    #elif USE_WIRINGPI_LIB
        ref = wiringPiI2CReadReg16 (fd, (int)Cmd);
    
    #elif  USE_LGPIO_LIB 
        ref = lgI2cReadByteData(I2C_Handle, Cmd);

    #elif USE_DEV_LIB
        char rbuf[2] = {0};
        DEV_HARDWARE_I2C_read(Cmd, rbuf, 2);
        ref = rbuf[1]<<8 | rbuf[0];
    #endif
#endif
    return ref;
}

/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_ModuleInit(void)
{
 #ifdef USE_BCM2835_LIB
    if(!bcm2835_init()) {
        printf("bcm2835 init failed  !!! \r\n");
        return 1;
    } else {
        printf("bcm2835 init success !!! \r\n");
    }

#elif USE_WIRINGPI_LIB  
    //if(wiringPiSetup() < 0)//use wiringpi Pin number table  
    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        printf("set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        printf("set wiringPi lib success  !!! \r\n");
    }

#elif  USE_LGPIO_LIB
    char buffer[NUM_MAXBUF];
    FILE *fp;
    fp = popen("cat /proc/cpuinfo | grep 'Raspberry Pi 5'", "r");
    if (fp == NULL) {
        printf("It is not possible to determine the model of the Raspberry PI\n");
        return -1;
    }

    if(fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        GPIO_Handle = lgGpiochipOpen(4);
        if (GPIO_Handle < 0)
        {
            printf( "gpiochip4 Export Failed\n");
            return -1;
        }
    }
    else
    {
        GPIO_Handle = lgGpiochipOpen(0);
        if (GPIO_Handle < 0)
        {
            printf( "gpiochip0 Export Failed\n");
            return -1;
        }
    }
#elif USE_DEV_LIB
    printf("USE_DEV_LIB \r\n");
#endif
    GPIO_Config();
    DEV_I2C_Init(0x29);
    
    return 0;
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_ModuleExit(void)
{
#ifdef USE_BCM2835_LIB
    bcm2835_i2c_end();
    bcm2835_close();
    
#elif USE_WIRINGPI_LIB

#elif  USE_LGPIO_LIB 
    lgI2cClose(I2C_Handle);

#elif USE_DEV_LIB
    DEV_HARDWARE_I2C_end();
#endif
}

