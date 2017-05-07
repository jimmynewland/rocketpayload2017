# rocketpayload2017
9-DOF Adalogger - Revision 1.6 - Last Update: 2017-05-07 - http://jimmynewland.com

9-DOF Sensor package meant to ride along with the Texas A&amp;M Rocketry team summer launch.

This code is based on code written by Adafruit authors for the 9-DOF sensor and the Feather Adalogger. Some minor changes were added
and the code was combined into one functioning chunk of code. Since the payload must be stand-alone, all code requiring user intervention
was removed.

This sketch uses a 9 degrees-of-freedom (LSM9DS1 9-DOF) Adafruit sensor on board am Adafruit Feather 32u4 Adalogger board. 
The data is saved to an onboard 4GB MicroSD Card as plain, tabbed delimited text. The 9-DOF sensor has 3-axis sensors 
for acceleration, magnetic field, and gyroscopic motion. 

2 sketches were used from Adafruit Industries. 
One for the 9-DOF called lsm9ds1.ino. https://github.com/adafruit/Adafruit_LSM9DS1
And one for the Adalogger called Datalogger.ino https://github.com/adafruit/SD/blob/master/examples/Datalogger/Datalogger.ino
