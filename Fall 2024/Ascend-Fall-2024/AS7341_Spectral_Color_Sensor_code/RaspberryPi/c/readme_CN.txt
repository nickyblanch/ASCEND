/*****************************************************************************7341
* | File      	:   Readme_CN.txt
* | Author      :   Waveshare team
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-12-23
* | Info        :   在这里提供一个中文版本的使用文档，以便你的快速使用
******************************************************************************/
这个文件是帮助您使用本例程。
在这里简略的描述本工程的使用：

1.基本信息：
本例程均在Raspberry Pi 3B+ 上进行了验证;
本例程使用AS7341 Spectral Color Sensor模块进行了验证，你可以在工程的examples\中查看对应的测试例程;

2.代码简介：
examples中包含了所有测试c文件
lib中是所有库文件

注：在SYNS模式下，需要给传感器的GPIO引脚一个下降沿信号触发测量，芯片上电后GPIO引脚默认为低电平
因此你需要先将GPIO口先拉高再拉低来产生一个下降沿信号，一个下降沿信号触发一次测量。测量完成后，
芯片会进入IDLE模式，进入低功耗状态。



3.安装库：
Raspberry Pi
    安装BCM2835
        1.	wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.60.tar.gz
        2.	tar zxvf bcm2835-1.60.tar.gz 
        3.	cd bcm2835-1.60/
        4.	sudo ./configure
        5.	sudo make
        6.	sudo make check
        7.	sudo make install
        8.	# 更多的可以参考官网：http://www.airspayce.com/mikem/bcm2835/
    安装wiringPi
        1.	sudo apt-get install wiringpi
        2.	#对于树莓派4B可能需要进行升级：
        3.	cd /tmp
        4.	wget https://project-downloads.drogon.net/wiringpi-latest.deb
        5.	sudo dpkg -i wiringpi-latest.deb
        6.	gpio -v
        7.	# 运行gpio -v会出现2.52版本，如果没有出现说明安装出错
        

在Makefile文件中有
    # USELIB = USE_BCM2835_LIB
    # USELIB = USE_WIRINGPI_LIB
    USELIB = USE_DEV_LIB
Raspberry Pi 支持BCM2835、WIRINGPI和DEV_LIB


4.基本使用：
测试程序在examples\目录中查看
Run:
    make clean 
    make
    sudo ./main data
这里的data可以是flicker、syns、int、pinint、clear
每个测试文件的开头都对其有详细的功能描述



