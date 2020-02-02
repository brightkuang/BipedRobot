/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  Note: This requires CurieBLE library
    from http://librarymanager/all#CurieBLE

  Warning: Bluetooth support is in beta!
 *************************************************************/

#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>
#include <CurieIMU.h>
#include <SimpleTimer.h>
#include <TimeLib.h>
#include <MadgwickAHRS.h>
#include <SCServo.h>

SCSCL sc;

Madgwick filter;          // initialise Madgwick object

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "azAVD4U9m8yTq4RrRkM01hndOfdXEVEN";

BLEPeripheral  blePeripheral;

// A timer instance to avoid flooding the Blynk Server
SimpleTimer timer;

int led_pin    = 13;
int blinkState = 0;

BLYNK_WRITE(V1) {
  int pinData = param.asInt();
  Serial.print("V1:");
  Serial.println(pinData);
  if (pinData == 1) {
    sc.RegWritePos(1, 312, 400);
    sc.RegWritePos(2, 230, 400);
    sc.RegWritePos(3, 168, 400);
    sc.RegWriteAction();  
  }
}

BLYNK_WRITE(V2) {
  int pinData = param.asInt();
  Serial.print("V2:");
  Serial.println(pinData);
  if (pinData == 1) {
    sc.RegWritePos(1, 313, 400);
    sc.RegWritePos(2, 426, 400);
    sc.RegWritePos(3, 321, 400);
    sc.RegWriteAction();  
  }
}

BLYNK_WRITE(V3) {
  int pinData = param.asInt();
  Serial.print("V3:");
  Serial.println(pinData);
  if (pinData == 1) {
    sc.RegWritePos(4, 405, 400);
    sc.RegWritePos(5, 449, 400);
    sc.RegWritePos(6, 290, 400);
    sc.RegWriteAction();  
  }
}

BLYNK_WRITE(V4) {
  int pinData = param.asInt();
  Serial.print("V4:");
  Serial.println(pinData);
  if (pinData == 1) {
    sc.RegWritePos(4, 206, 400);
    sc.RegWritePos(5, 290, 400);
    sc.RegWritePos(6, 310, 400);
    sc.RegWriteAction();  
  }
}

/* we could also do it this way with "Pull"
BLYNK_READ(V5) {
  Blynk.virtualWrite(5, millis() / 1000);
}
*/

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  float a = (aRaw * 2.0) / 32768.0;
  return a;
}

float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767
  
  float g = (gRaw * 250.0) / 32768.0;
  return g;
}

void timerService()
{
  int aix, aiy, aiz;
  int gix, giy, giz;
  float ax, ay, az;
  float gx, gy, gz;
  float roll, pitch, heading;

  // update the IMU data  
  // read raw data from CurieIMU
  CurieIMU.readMotionSensor(aix, aiy, aiz, gix, giy, giz);

  // convert from raw data to gravity and degrees/second units
  ax = convertRawAcceleration(aix);
  ay = convertRawAcceleration(aiy);
  az = convertRawAcceleration(aiz);
  gx = convertRawGyro(gix);
  gy = convertRawGyro(giy);
  gz = convertRawGyro(giz);

  // update the filter, which computes orientation
  filter.updateIMU(gx, gy, gz, ax, ay, az);
    
  // print the heading, pitch and roll
  roll = filter.getRoll();
  pitch = filter.getPitch();
  heading = filter.getYaw();
  
  //We'll use "PUSH" at 1 sec intervals
  Blynk.virtualWrite(5,heading);  // V5
  Blynk.virtualWrite(6,pitch);  // V6
  Blynk.virtualWrite(7,roll);  // V7
  Blynk.virtualWrite(8,gx);  // V8
  Blynk.virtualWrite(9,gy);  // V9
  Blynk.virtualWrite(10,gz); // V10  

// blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(led_pin, blinkState);
}

void setup()
{
  Serial.begin(9600);
  
  Serial1.begin(500000);
  sc.pSerial = &Serial1;
  
  // initialize the output (GPIO) pins
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, 0);    // V0

  // Other Time library functions can be used, like:
  //   timeStatus(), setSyncInterval(interval)...
  // Read more: http://www.pjrc.com/teensy/td_libs_Time.html
  // Update timerService every 1.0 second
  // we do this to avoid flooding the connection 
  // (i.e. the Blynk server) with too much data
  timer.setInterval(500L, timerService);
  
  // start the IMU and filter
  CurieIMU.begin();
  CurieIMU.setGyroRate(2);
  CurieIMU.setAccelerometerRate(2);
  filter.begin(2);

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  // Set the gyroscope range to 250 degrees/second
  CurieIMU.setGyroRange(250);
  
  blePeripheral.setLocalName("hack01");
  blePeripheral.setDeviceName("hack01");
  blePeripheral.setAppearance(384);

  Blynk.begin(blePeripheral, auth);

  blePeripheral.begin();
}

void loop()
{
  // nice and simple...
  Blynk.run();
  blePeripheral.poll();
  timer.run();
}
