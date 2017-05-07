/**
 * 9-DOF Adalogger - Revision 1.6 - Last Update: 2017-05-06 - http://jimmynewland.com
 * 
 * This sketch uses a 9 degrees-of-freedom (LSM9DS1 9-DOF) Adafruit sensor 
 * on board am Adafruit Feather 32u4 Adalogger board. The data is saved to an onboard
 * 4GB MicroSD Card as plain, tabbed delimited text. The 9-DOF sensor has 3-axis 
 * sensors for acceleration, magnetic field, and gyroscopic motion.
 * 
 * 2 sketches were used from Adafruit Industries. 
 * One for the 9-DOF called lsm9ds1.ino.
 * And one for the Adalogger called Datalogger.ino
 */

 //START 9-DOF init
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5
// You can also use software SPI
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS, LSM9DS1_MCS);
// Or hardware SPI! In this case, only CS pins are passed in
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_XGCS, LSM9DS1_MCS);

//END 9-DOF init

//START Adalogger init
/*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.
 */
//#include <SPI.h> // repeated include
#include <SD.h>
const int chipSelect = 4;
long int count = 0; // this counter keeps up with the number of sensor reads

//END Adalogger init

// Used to setup the 9-DOF sensor package.
void setupSensor()
{
  // 1.) Set the accelerometer range
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}

void setup() 
{
  count = 1; // start the counter
  //START 9-DOF setup
  Serial.begin(115200);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");

  // helper to just set the default scaling we want, see above!
  setupSensor();
  //END 9-DOF setup

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  //END Adalogger setup
}

void loop() 
{
  //START 9-DOF loop
  lsm.read();  /* ask it to read in the data */ 

  /* Get a new sensor event */ 
  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 

  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2");
  Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
  Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");

  Serial.print("Mag X: "); Serial.print(m.magnetic.x);   Serial.print(" gauss");
  Serial.print("\tY: "); Serial.print(m.magnetic.y);     Serial.print(" gauss");
  Serial.print("\tZ: "); Serial.print(m.magnetic.z);     Serial.println(" gauss");

  Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" dps");
  Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" dps");
  Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" dps");

  Serial.println();
  delay(200);
  //END 9-DOF loop

  //START Adalogger loop
    // make a string for assembling the data to log:
  String dataString = "";

  //
  dataString = dataString + count + "," + dataString; 
  dataString = dataString + a.acceleration.x + "," 
                          + a.acceleration.y + "," 
                          + a.acceleration.z + ",";

  dataString = dataString + m.magnetic.x + "," 
                          + m.magnetic.y + ","
                          + m.magnetic.z + ",";

  dataString = dataString + g.gyro.x + ","
                          + g.gyro.y + ","
                          + g.gyro.z;
  
  //

  // read three sensors and append to the string:
  //for (int analogPin = 0; analogPin < 3; analogPin++) {
  //  int sensor = analogRead(analogPin);
  //  dataString += String(sensor);
  //  if (analogPin < 2) {
  //    dataString += ",";
  //  }
  //}

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  count++; // this counter keeps up with each read of the sensor every 200ms
  //END Adalogger loop
}
