BME680 => i2p through library
> Temp
> Humidity
> Barometric Pressure
> VOC gas

ICM20498 => i2p
> 9DOF 

SD Reader => SPI
> Duh

Gravity Ozone Sensor => i2p library
> Ozone concentration

GUVA 1918 => Analog pin
> UV detection
> UV Index = V*10

Radiation Sensor => 2 interrupt pins
> Radiation


BLINK CODE MEANING!!!

3 short blink -> bme680_1
3 long blink -> bme680_2
6 long link -> ICM20498
4 even blink -> Gravity (Ozone)
Rapid flashing -> SD Card