/* Sketch, used to test the Soladin libary,
This sketch simulate a predefined response of a soladin.
I used this sketch in a breadboard setup to test after the sun went down.
*/


#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
char RxBuf[10] ;
char cmdC1[9] = { 0x00, 0x00, 0x11, 0x00, 0xC1, 0xF3, 0x00, 0x00, 0xC5}; 
char cmd97[9] = { 0x00, 0x00, 0x11, 0x00, 0x97, 0x01, 0x00, 0x00, 0xA9}; 
char cmd9A[9] = { 0x00, 0x00, 0x11, 0x00, 0x9A, 0x54, 0x05, 0x00, 0x04};
char cmdB4[31] = { 0x00, 0x00, 0x11, 0x00, 0xB4, 0xF3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE3, 0x00, 0x04, 0x01, 0x34, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA};
char cmdB9[31] = { 0x00, 0x00, 0x11, 0x00, 0xB9, 0xF3, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x21, 0x00, 0x22, 0x00, 0x00, 0x00, 0xE5, 0x02, 0x7E, 0x48, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E};
char cmdB6[31] = { 0x00, 0x00, 0x11, 0x00, 0xB6, 0xF3, 0x00, 0x00, 0x04, 0x03, 0x35, 0x00, 0x8A, 0x13, 0xF4, 0x00, 0x00, 0x00, 0x24, 0x00, 0x90, 0x0B, 0x00, 0x1F, 0xDB, 0xBC, 0x01, 0x00, 0x00, 0x00, 0xFD};
int Lgth ;
int cnt ;



int freeRam () {  
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
} 




void setup()  
{
  Serial.begin(9600);
  Serial.print("FreeRam= ");
  Serial.println(freeRam());
  mySerial.begin(9600);
  Serial.println("Booting...Done");
}

void loop() { // run over and over
  cnt = 0 ;
  if (mySerial.available() > 0) {
    delay(10);
    while (mySerial.available() > 0 &&  cnt <= 10 ){ 
      RxBuf[cnt] = mySerial.read();
      cnt++ ;
    }  
    Lgth = cnt ;
  }
  if (cnt > 0) {SPrintbuffer();}
  if ( cnt > 0 ) {
    switch (byte(RxBuf[4])) {
    case 0xC1: sndBuf(9,cmdC1); cnt = 0; break;
    case 0xB4: sndBuf(31,cmdB4); cnt = 0; break;
    case 0xB9: sndBuf(31,cmdB9); cnt = 0; break;  
    case 0x97: sndBuf(9,cmd97); cnt = 0; break;  
    case 0x9A: sndBuf(9,cmd9A); cnt = 0; break; 
    case 0xB6: sndBuf(31,cmdB6); cnt = 0 ; break;      
    }
  }
}


void sndBuf(int size, char *OutBuf){
  for (int i=0; i <size ; i++){
    mySerial.write(OutBuf[i]);
  }
}

void SPrintbuffer(){
  Serial.print("0x");
  for (int i=0; i<Lgth ; i++) {
    if (byte(RxBuf[i]) < 0x10) {
      Serial.print("0");
    }
    Serial.print(byte(RxBuf[i]),HEX);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("BufferSize= ");
  Serial.println(Lgth);
}

