#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial1.begin(500000);
  sc.pSerial = &Serial1;

  delay(5000);

}

void loop()
{
  sc.RegWritePos(1, 312, 400);
  sc.RegWritePos(2, 230, 400);
  sc.RegWritePos(3, 168, 400);
  sc.RegWriteAction();   
  delay(400);

  sc.RegWritePos(1, 313, 1600);
  sc.RegWritePos(2, 426, 1600);
  sc.RegWritePos(3, 321, 1600);
  sc.RegWritePos(4, 226, 400);
  sc.RegWritePos(5, 196, 400);
  sc.RegWritePos(6, 277, 400);
  sc.RegWriteAction();   
  delay(400);
  
  sc.RegWritePos(4, 475, 800);
  sc.RegWritePos(5, 357, 800);
  sc.RegWritePos(6, 264, 800);
  sc.RegWriteAction();   
  delay(800);

  sc.RegWritePos(4, 405, 400);
  sc.RegWritePos(5, 449, 400);
  sc.RegWritePos(6, 290, 400);
  sc.RegWriteAction();   
  delay(400);
  
  sc.RegWritePos(1, 354, 400);
  sc.RegWritePos(2, 319, 400);
  sc.RegWritePos(3, 373, 400);
  sc.RegWritePos(4, 206, 1600);
  sc.RegWritePos(5, 290, 1600);
  sc.RegWritePos(6, 310, 1600);
  sc.RegWriteAction();   
  delay(400);

  sc.RegWritePos(1, 354, 800);
  sc.RegWritePos(2, 159, 800);
  sc.RegWritePos(3, 228, 800);
  sc.RegWriteAction();   
  delay(800);
}
