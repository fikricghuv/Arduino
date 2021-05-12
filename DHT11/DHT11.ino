#include <dht11.h>
dht11 DHT11;
#define DHT11PIN A0


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
delay(500);
Serial.println("Sensor Suhu dan Kelembaban Udara Dengan DHT11 \n\n");
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
int chk=DHT11.read(DHT11PIN);
Serial.print("Temperature:         ");
Serial.print((int)DHT11.temperature,2);
Serial.print(" C"); 
Serial.print("   ||   ");

Serial.print("Humidity:         ");
Serial.print((int)DHT11.humidity,2);
Serial.println(" %");
delay(3000);
}
