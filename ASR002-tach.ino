/****************************************************************************** 
Tachometer using NVE ASR002 Smart Angle Sensor
Arduino Uno connections: pin 10=SS; pin 11=MOSI; pin 12=MISO; pin 13=SCLK
Port D = Output angle (256=360 degrees) 
pin 9 = PWM tach output (5V = 20000 RPM)
NVE Corporation (email: sensor-apps@nve.com)                     rev. 12/23/18 
******************************************************************************/
#include <SPI.h>
int angle; 
int oldAngle; 
unsigned long currentTime; //Timer of most recent zero-crossing
unsigned long oldTime; //Timer of previous zero-crossing
unsigned long period; //Time between revolutions
int RPM; //Scaled RPM for analog output;

void setup() {
pinMode(10, OUTPUT); //Pin 10 = Sensor SS
DDRD = 0xFF; //Set Port D as outputs (for angle)
SPI.begin ();
SPI.beginTransaction(SPISettings(2500000, MSBFIRST, SPI_MODE0));
digitalWrite(10, LOW); //Enable sensor
}

void loop() {  
angle = (SPI.transfer (0))<<8; //Send 0 for address angle; receive angle MSB
delayMicroseconds (3); //Allow time between address bytes
angle |= SPI.transfer (0); //2nd address byte (0 for read); receive angle LSB
if (abs(angle-oldAngle)>1800) { //Check for discontinuity (360-0 transition)
currentTime = micros();
period = currentTime-oldTime;
oldTime = currentTime;
RPM=60000000L/period*256L/20000L; //RPM=60E6/period; 256=PWM FS; 20000 RPM=meter FS
if (RPM<25 || RPM>255) RPM=0; //Prevent overflow
analogWrite(9, RPM); //Analog RPM output
}
PORTD = long(angle)*256L/3600; //Output scaled angle to R/2R array on Port D
oldAngle=angle;
delayMicroseconds (10); //Allow time for next data
}
