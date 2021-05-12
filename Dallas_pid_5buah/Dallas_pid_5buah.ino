#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#define suhu_kaki 7

OneWire sh(suhu_kaki);
DallasTemperature sensors(&sh);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float suhu1;
float suhu2;
float suhu3;
float suhu4;
float suhu5;

int btup = A4;
int btdown = A3;
int btenter = A2;
int btmonitor = A1;
int waktu;

int btupx = 0;
int btdownx = 0;
int btenterx = 0;
int btmonitorx = 0;

int levlow = 9;
int levhigh = 8;
int buzzer = A5;

int levlowx = 0;
int levhighx = 0;
int cacah = 1;

float kp = 1.15;
float ki = 0.67;
float kd = 0.15;

float p,i,d,suhu,pid;
float error,errorx,sumerr;
float sp;

int detik = 60;
int menit;
int jam;

void setup()
{

  pinMode(btup,INPUT);
  pinMode(btdown,INPUT);
  pinMode(btenter,INPUT);
 
  pinMode(levlow,INPUT);
  pinMode(levhigh,INPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,HIGH);

  Serial.begin (9600);
  lcd.begin(20,4);

sensors.begin();
lcd.clear();
ceklevel();
menu();
}


void loop()
{
  ambilsuhu();
 
  analogWrite(10,pid);
 
  error = sp - suhu1;
  p = error * kp;
  sumerr = error + errorx;
  i = ki * sumerr;
  d = kd * (error - errorx) ;
  pid = p + i + d;
  //pid = sp - pid;
  //pid = 255.0 - pid;

  if(pid < 1){
  pid = 0;
  }
 
  if(pid > 255){
  pid = 255;
  }

lcd.setCursor(0,0);
lcd.print("SP:");
lcd.print(sp);
lcd.print(" P:");
lcd.print(pid);
lcd.print("       ");
 
lcd.setCursor(0,1);
lcd.print("T:");
lcd.print(suhu1);
lcd.print(" W:");
lcd.print(jam);
lcd.print(":");
lcd.print(menit);
lcd.print(":");
lcd.print(detik);
lcd.print("  ");
       

 btmonitorx = digitalRead(btmonitor);

if(btmonitorx == 1){
  monitorx();
  }

 
if(btmonitorx == 0){
    lcd.setCursor(0,2);
    lcd.print("                    ");
    lcd.setCursor(0,3);
    lcd.print("                    ");
   
  }


if(menit == 0){
 lcd.clear();
 delay(1000);
 selesai();
}
 
errorx = error;


detik--;

if(detik < 0){
detik = 60;
menit--;
}

delay(1000); 
}



void selesai(){
 
digitalWrite(buzzer,LOW); 
lcd.setCursor(0,0);
lcd.print("PROSES SELESAI");

analogWrite(10,0);
       
selesai(); 
}

void monitorx(){
 
    lcd.setCursor(0,2);
    lcd.print("T1:");
    lcd.setCursor(4,2);
    lcd.print(suhu2);
    lcd.setCursor(0,3);
    lcd.print("T2:");
    lcd.setCursor(4,3);
    lcd.print(suhu3);
    lcd.setCursor(11,2);
    lcd.print("T3:");
    lcd.setCursor(15,2);
    lcd.print(suhu4);
    lcd.setCursor(11,3);
    lcd.print("T4:");
    lcd.setCursor(15,3);
    lcd.print(suhu5); 
 
}


void ambilsuhu(){

  sensors.requestTemperatures();

  suhu1 = sensors.getTempCByIndex(0);
  suhu2 = sensors.getTempCByIndex(1);
  suhu3 = sensors.getTempCByIndex(2);
  suhu4 = sensors.getTempCByIndex(3);
  suhu5 = sensors.getTempCByIndex(4);
    
}


void ceklevel(){
 
levlowx = digitalRead(levlow);
levhighx = digitalRead(levhigh);

if(levlowx == 0){
  digitalWrite(buzzer,LOW);
}

if(levlowx == 1){
  digitalWrite(buzzer,HIGH);
}

if(levhighx == 1){
  lcd.clear();
  delay(1000);
  return;
}
    
lcd.setCursor(0,0);
lcd.print("SENSOR1 = ");
lcd.print(levlowx);
 
lcd.setCursor(0,1);
lcd.print("SENSOR2 = ");
lcd.print(levhighx);

ceklevel();  
}


void menu(){

btupx = digitalRead(btup);
btdownx = digitalRead(btdown);
btenterx = digitalRead(btenter);
 
lcd.setCursor(0,0);
lcd.print("PILIH MENU ");

if(btupx == 1){
  delay(200);
  cacah++;
}

if(btdownx == 1){
  delay(200);
  cacah--;
}

if(cacah > 6){
cacah = 1; 
}


if(btenterx == 1){
lcd.clear();
delay(3000); 
return; 
}

if(cacah == 1){ 
lcd.setCursor(0,1);
lcd.print("Suhu = 37 C");
lcd.setCursor(0,2);
lcd.print("Waktu = 10 Menit");
sp = 37;
menit = 10;
} 

if(cacah == 2){ 
lcd.setCursor(0,1);
lcd.print("Suhu = 40 C");
lcd.setCursor(0,2);
lcd.print("Waktu = 15 Menit");
sp = 40;
menit = 15;
}

if(cacah == 3){ 
lcd.setCursor(0,1);
lcd.print("Suhu = 45 C");
lcd.setCursor(0,2);
lcd.print("Waktu = 10 Menit");
sp = 45;
menit = 10;
}

if(cacah == 4){ 
lcd.setCursor(0,1);
lcd.print("Suhu = 50 C");
lcd.setCursor(0,2);
lcd.print("Waktu = 10 Menit");
sp = 50;
menit = 10;
}

if(cacah == 5){
lcd.setCursor(0,1);
lcd.print("Suhu = 55 C");
lcd.setCursor(0,2);
lcd.print("Waktu = 10 Menit");
sp = 55;
menit = 10;
}

if(cacah == 6){
lcd.setCursor(0,1);
lcd.print("Suhu = 60 C");
lcd.setCursor(0,2);
lcd.print("Waktu = 10 Menit");
sp = 60;
menit = 10;
}
  
menu(); 
}
