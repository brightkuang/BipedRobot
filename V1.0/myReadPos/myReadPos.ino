#include <SCServo.h>

SCSCL sc;
int LEDpin = 13;

void setup()
{
	pinMode(LEDpin,OUTPUT);
	digitalWrite(LEDpin, HIGH);
	Serial1.begin(500000);
  Serial.begin(115200);
  sc.pSerial = &Serial1;
}

void loop()
{
	s16 pos1 = sc.ReadPos(1);
  Serial.print(pos1);
  s16 pos2 = sc.ReadPos(2);
  Serial.print(":");
  Serial.print(pos2);
  s16 pos3 = sc.ReadPos(3);
  Serial.print(":");
  Serial.print(pos3);
  s16 pos4 = sc.ReadPos(4);
  Serial.print(":");
  Serial.print(pos4);
  s16 pos5 = sc.ReadPos(5);
  Serial.print(":");
  Serial.print(pos5);
  s16 pos6 = sc.ReadPos(6);
  Serial.print(":");
  Serial.println(pos6);
  delay(2000);
	
}
