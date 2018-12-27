# ASR002-High-Speed-Tach
This demonstration uses NVE's ASR002 Smart TMR Angle Sensor to determine the speed and position 
of a 12-volt, 13000 RPM race-car motor. 

The sensor is mounted on one of our TDFN eval boards, and connected to an Arduino Uno via SPI. 
There are two outputs from the Arduino: the absolute angle, generated by a simple R/2R resistor array 
connected to an oscilloscope; and a tachometer PWM output connected to a meter. 

Even at 13000 RPM, the sensor can track not just the speed, but the angular position within two degrees.

A video of the demonstration can be found here: https://youtu.be/Me3p5x8qKME
