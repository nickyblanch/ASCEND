/*****************************************************************************
* | File      	:   Readme_CN.txt
* | Author      :   Waveshare team
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-01-15
* | Info        :   在这里提供一个中文版本的使用文档，以便你的快速使用
******************************************************************************/
这个文件是帮助您使用本例程。
在这里简略的描述本工程的使用：

1.基本信息：
本例程在Raspberry Pi 3B+ 进行了验证;
本例程使用AS7341 Spectral Color Sensor模块进行了验证，你可以在工程的examples\中查看对应的测试例程;

2.管脚连接：
AS7341    =>    RPI(BCM)
VCC         ->    3.3V/5V
GND         ->    GND
SDA         ->    SDA
SCL         ->    SCL
INT         ->    4
GPIO    ->    -

注：在SYNS模式下，需要给传感器的GPIO引脚一个下降沿信号触发测量，芯片上电后GPIO引脚默认为低电平
因此你需要先将GPIO口先拉高再拉低来产生一个下降沿信号，一个下降沿信号触发一次测量。测量完成后，
芯片会进入IDLE模式，进入低功耗状态。

3.安装库：
    sudo apt-get update
    sudo apt-get install python-pip
    sudo apt-get install python-pil
    sudo apt install python-gpiozero
    sudo pip install smbus
或

    sudo apt-get update
    sudo apt-get install python3-pip
    sudo apt-get install python3-pil
    sudo apt install python3-gpiozero
    sudo pip3 install smbus
    
4.基本使用：
测试程序在examples\目录中查看

python2
    sudo python data.py

python3
    sudo python3 data.py