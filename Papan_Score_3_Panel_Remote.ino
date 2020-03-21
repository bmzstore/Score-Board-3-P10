#include "DMD3.h"
#include "bmzSegment16.h"
#include "bmz6x7.h"
#include "bmz4x6.h"
#include "bmz5x7.h"
#include "bmz9.h"
#include "BIG7SEGMENT.h"
DMD3 display (3,1);

#include <IRremote.h>
#define buzzer 3
int RECV_PIN = 14;

//RealPlayer
// ON/OFF = 1FE48B7
// REPEAT = 1FE58A7
// MUTE = 1FE7887
// PHOTO = 1FE807F
// MUSIC = 1FE40BF
// MOVIE =1FEC03F
// STOP = 1FE20DF
// UP = 1FEA05F
// PAUSE = 1FE609F
// LEFT = 1FEE01F
// ENTER = 1FE10EF
// RIGHT = 1FE906F
// DOWN = 1FED827
// V+ = 1FE30CF
// V- = 1FE00FF
// BACK = 1FEB04F
// NEXT = 1FEF00F
// PREV = 1FE708F
// FOR = 1FE9867


//CarMP3
//0 = FF6897
//1 = FF30CF
//2 = FF18E7
//3 = FF7A85
//4 = FF10EF
//5 = FF38CF
//6 = FF5AA5
//7 = FF42BD
//8 = FF4AB5
//9 = FF52AD
//CH- = FFA25D
//CH+ = FFE21D
//CH  = FF629D
// PREV = FF22DD
// NEXT = FF02FD
// PLAY = FFC23D
// - = FFE01F
// + = FFA857
// EQ = FF906F

int Kanan, Kiri;
int satuanKiri, satuanKanan, puluhanKiri, puluhanKanan;
int foulKiri, foulKanan;
int periode;
int nilaiKiri=00;
int nilaiKanan=00;
boolean st=0;
int kecerahan=50;

IRrecv irrecv(RECV_PIN);

decode_results results;

//Score
char dmdBuff1[10];
char dmdBuff2[10];
char dmdBuff3[10];
char dmdBuff4[10];
//Foul
char dmdBuff5[10];
char dmdBuff6[10];
//Periode
char dmdBuff7[10];
//Timer
char dmdBuff8[10];
char dmdBuff9[10];
void scan()
{
    display.refresh();
}

 
void setup() {
    Timer1.initialize(2000);
    Timer1.attachInterrupt(scan);
    Timer1.pwm(9,55);
    irrecv.enableIRIn();
    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
    pinMode(A4, INPUT_PULLUP);
     pinMode(buzzer,OUTPUT);
   
    digitalWrite(buzzer,HIGH);
}

double prev=0,prev1=0;
long prev3=0,prev4=0;
int menit=0,detik=0,milidetik=0;
int setmenit=1;
long m,s,ms;
boolean p=0,flag=0;

void loop() {
  int mn,dt;
  Kiri=nilaiKiri;
  Kanan=nilaiKanan;

  satuanKiri=Kiri%10;
  puluhanKiri=Kiri/10;

  satuanKanan=Kanan%10;
  puluhanKanan=Kanan/10;
  
    if (irrecv.decode(&results)) {
      //Score
    if(results.value==0x1FEB04F){ nilaiKiri++;delay(0);}// Tambah Score Kiri
    if(results.value==0x1FEF00F){ nilaiKiri--;delay(0);}// Kurang Score Kiri
    if(results.value==0x1FE708F){ nilaiKanan++;delay(0);}// Tambah Score Kanan
    if(results.value==0x1FE9867){ nilaiKanan--;delay(0);}//Kurang Score Kiri 

     //Foul
     if(results.value==0x1FE807F){foulKiri++;delay(0);}
     if(results.value==0x1FE20DF){foulKiri--;delay(0);}
     if(results.value==0x1FEC03F){foulKanan++;delay(0);}
     if(results.value==0x1FE609F){foulKanan--;delay(0);}

     //Periode
     if(results.value==0x1FE30CF){periode++;delay(0);}
     if(results.value==0x1FE00FF){periode--;delay(0);}

     //Timer
     if(results.value==0x1FEA05F){setmenit++;delay(0);}
     if(results.value==0x1FED827){setmenit--;delay(0);}
     
     //Kecerahan
     if(results.value==0x1FEE01F){kecerahan++;delay(0);}
     if(results.value==0x1FE906F){kecerahan--;delay(0);}

     //Reset
     if(results.value==0x1FE48B7){
      setmenit = 00;
      nilaiKiri = 00;
      nilaiKanan = 00;
      foulKiri = 0;
      foulKanan = 0;
      periode = 0;
      st=0; 
      //delay(10);
      }
     
     //Start
     if(results.value==0x1FE10EF){
    if(st==0){ 
    }
    st=1;p=0;
      }
    if(results.value==0xFFB04F){ p=1;}// pause
    if(results.value==0xFF9867){ st=0;p=0;}// reset
    irrecv.resume(); // Receive the next value
    }

    
  if(setmenit>99)setmenit=0;
  if(setmenit<0)setmenit=99;

  //Score
     if (nilaiKiri > 99) {
      nilaiKiri = 00;
    }

     if (nilaiKiri < 00) {
      nilaiKiri = 99;
    }
    
    if (nilaiKanan > 99) {
      nilaiKanan = 00;
    }

     if (nilaiKanan < 00) {
      nilaiKanan = 99;
    }

  //Foul
    if (foulKiri > 9) {
      foulKiri = 0;
    }

     if (foulKiri < 0) {
      foulKiri = 9;
    }
    
    if (foulKanan > 9) {
      foulKanan = 0;
    }

     if (foulKanan < 0) {
      foulKanan = 9;
    }

    //Periode
    if (periode > 9) {
      periode = 0;
    }

     if (periode < 0) {
      periode = 9;
    }

    //Timer
    if (menit > 99) {
      menit = 00;
    }

     if (menit < 00) {
      menit = 99;
    }

    //Kecerahan
    if (kecerahan > 255) {
     kecerahan = 0;
    }

     if (kecerahan < 0) {
      kecerahan = 255;
    }
    
    
    
 
    sprintf(dmdBuff1, "%.1d", puluhanKiri);
    sprintf(dmdBuff2, "%.1d", satuanKiri);
    sprintf(dmdBuff3, "%.1d", puluhanKanan);
    sprintf(dmdBuff4, "%.1d", satuanKanan);
  

    //Score
    display.setFont(BIG7SEGMENT);
    display.drawText(5, 0, dmdBuff1);
    display.drawText(17, 0, dmdBuff2);
    //display.drawText(25, 0, "0");
    //display.drawText(33, 0, "0");
    display.drawText(69, 0, dmdBuff3);
    display.drawText(81, 0, dmdBuff4);

      display.setFont(bmz5x7);
       display.drawText(40, 0, "TIM");
       
        display.setFont(bmz6x7);
       display.drawText(33, 8, "A<->B");

        display.drawLine(0,16,0,0);
        display.drawLine(1,16,1,0);
        
        display.drawLine(30,16,30,0);
        display.drawLine(31,16,31,0);
        
        display.drawLine(65,16,65,0);
        display.drawLine(64,16,64,0);
        
        display.drawLine(94,16,94,0);
         display.drawLine(95,16,95,0);
/*
    //Time
    sprintf(dmdBuff8, "%.2d", menit);
    sprintf(dmdBuff9, "%.2d", detik);
    display.setFont(bmz5x7);
    display.drawText(19, 0, dmdBuff8);
    display.drawText(30, 0, ":");
    display.drawText(34, 0, dmdBuff9);

    //Priode
    sprintf(dmdBuff7, "%.1d", periode);
    display.setFont(bmz6x7);
    display.drawText(29, 7, dmdBuff7);

    //Foul
    sprintf(dmdBuff5, "%.1d", foulKiri);
    sprintf(dmdBuff6, "%.1d", foulKanan);
    display.setFont(bmz4x6);
    display.drawText(22, 9, dmdBuff5);
    display.drawText(38, 9, dmdBuff6);

    
    display.drawLine(16,12,19,9);
    display.drawLine(16,12,19,15);
    display.drawLine(19,9,19,15);
    display.drawLine(18,10,18,14);
    display.drawCircle(17,12,0);

    display.drawLine(44,9,47,12);
    display.drawLine(44,15,47,12);
    display.drawLine(44,9,44,15);
    display.drawLine(45,10,45,14);
    display.drawCircle(46,12,0);
    */
    if(st==0){
  prev=millis();
  menit=setmenit; 
  detik=0;
  milidetik=0; 
}
else{
  prev=millis();
  if (prev - prev1 >= 0) {
    if(p==0){
    milidetik--;
    if(milidetik<0){
      detik--;
      milidetik=99;
      if(menit==0&&detik<=10)flag=1;
      }
    if(detik<0){
      detik=59;
      if(menit>0)menit--;
      
      }  
    prev1 = prev;
    if(flag==1){
      if(milidetik>50)digitalWrite( buzzer, 1 );
      else {digitalWrite( buzzer, 0 );flag=0;}
      
    }
    }
  }
}
if(menit==0&&detik==0&&milidetik==0&&st==1) {
   
    digitalWrite(buzzer,LOW);
    waktuHabis();
    
    digitalWrite(buzzer,HIGH);
      //setmenit = 00;
      //nilaiKiri = 00;
      //nilaiKanan = 00;
      //foulKiri = 0;
      //foulKanan = 0;
      //periode = 0;
      st=0;
   
}
}

void waktuHabis(){
    display.clear();
    display.setFont(bmz9);
    display.drawText(12,-1, "WAKTU");
    display.drawText(16,8, "HABIS");
    delay(1000);
    display.clear();
    delay(1000);
    display.drawText(12,-1, "WAKTU");
    display.drawText(16,8, "HABIS");
    delay(1000);
    display.clear();
    delay(1000);
    display.drawText(12,-1, "WAKTU");
    display.drawText(16,8, "HABIS");
    delay(1000);
    display.clear();
}

