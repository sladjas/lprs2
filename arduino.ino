#include "LedControl.h"

LedControl lc=LedControl(12,13,10,1);
/*PIN 12 je povezan na DIN
PIN 13 je povezan na CLK
PIN 10 je povezan na CS
*/

int number[8];
int numLength = 0; // broj cifara
int i = 0;
int j = 0;
boolean valid = false;
double displayNumber = 0;
String stringNumber;
unsigned long delaytime=2000;

void setup() {
  lc.shutdown(0,false); 
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  Serial.begin(9600);
}

void printDigits() {
  lc.clearDisplay(0);
  for(i=0;i<numLength;i++) {   
    lc.setDigit(0,i,number[numLength-(i+1)],false);  
  }
   for(i=numLength;i<8;i++) {   
    lc.setDigit(0,i,0,false);  
  }
}
void loop() { 
   if(Serial.available()){
    delay(50);
   
    j = 0;
    numLength = 0;
    stringNumber ="";
  }
   while (Serial.available()){
    delay(50);
    int a = Serial.read();
    stringNumber = stringNumber + char(a);
    if(a>47 && a< 58){ //gledamo preko ascii tabele koja je cifra
      a = a - 48;
      number[j] = a;
      numLength=numLength+1;
      if(numLength > 8){
        numLength = 8; //ne prikazujemo vise od moguceg
      }
      j = j +1;
    }
    printDigits();
    valid = true;
    
  }   
    if(valid == true){
    Serial.println(stringNumber); 
    delay(5000);
    lc.clearDisplay(0);
    memset(number, 0, sizeof(number));
    stringNumber ="";
    numLength=0;
    valid = false;
  }
}
