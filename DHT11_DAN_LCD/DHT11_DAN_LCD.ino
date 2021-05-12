#include <dht11.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
dht11 DHT11;
#define DHT11PIN A0

const int relay1 = 9;

void setup() {
  // put your setup code here, to run once:
lcd.init();
lcd.init();
lcd.backlight();
Serial.begin(9600);
pinMode(relay1, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int chk=DHT11.read(DHT11PIN);

Serial.print((float)DHT11.humidity,2);
Serial.print("%");
Serial.print(" ");
Serial.print((float)DHT11.temperature,2);
Serial.println("*C");

lcd.setCursor(0, 0);
lcd.print("KELEMBAPAN: ");
lcd.print((float)DHT11.humidity,2);
lcd.print("%");

lcd.setCursor(0, 1);
lcd.print("SUHU: ");
lcd.print((float)DHT11.temperature,2);
lcd.print((char)223);
lcd.print("C ");
delay(1000);
if(DHT11.temperature,2 <= 28)
{ digitalWrite(relay1, HIGH);
}
else { (DHT11.temperature,2 >= 29);
 
  digitalWrite(relay1, LOW);
}
}
