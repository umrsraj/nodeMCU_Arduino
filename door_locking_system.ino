
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <LiquidCrystal.h>

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int buttonState,buttonState1;
#define buzzer 1
#define m11 D6
#define m12 D7
#define relay 10
#define vib D8

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";

char auth[] = "bfb95dc909bf471b8a736741ea040978";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "soumya";
char pass[] = "puppy@1715";

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}
WidgetLCD lcd1(V0);
BLYNK_WRITE(V1)
{
   buttonState = param.asInt();
  Serial.print(F("buttonState = ")); Serial.println(buttonState);
}
BLYNK_WRITE(V2)
{
   buttonState1 = param.asInt();
  Serial.print(F("buttonState1 = ")); Serial.println(buttonState1);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  lcd.begin(16,2);
 
pinMode(relay,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(vib,INPUT);

Serial.println("power up");

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
Blynk.notify("kit started");delay(1000);

}

void loop()
{
  Blynk.run();

if(buttonState == 1)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("DOOR OPENING....");
lcd.setCursor(0,1);
lcd.print("");
delay(200);

digitalWrite(m11,HIGH);
digitalWrite(m12,LOW);
delay(2000);
digitalWrite(m11,LOW);
digitalWrite(m12,LOW);
delay(20);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("DOOR CLOSING....");
lcd.setCursor(0,1);
lcd.print("");
delay(20);

digitalWrite(m11,LOW);
digitalWrite(m12,HIGH);
delay(2000);
digitalWrite(m11,LOW);
digitalWrite(m12,LOW);
delay(20);
delay(200);
}
else if (buttonState1 == 1)
{
 lcd.clear();
lcd.setCursor(0,0);
lcd.print("FENCING ON");
lcd.setCursor(0,1);
lcd.print("");
delay(20); 
digitalWrite(relay,HIGH);
delay(500);
Serial.print("vib=");
Serial.print(digitalRead(vib));
if(digitalRead(vib)==LOW)
{
   lcd.clear();
lcd.setCursor(0,0);
lcd.print("INTRUDER ALERT");
lcd.setCursor(0,1);
lcd.print("PLEASE CHECK");
delay(200);
Blynk.notify("INTURDER ALERT\nPLEASE CHECK");
beep ();
delay(2000); 
}
}
else if(buttonState1 == 0)
{
  
 lcd.clear();
lcd.setCursor(0,0);
lcd.print("FENCING OFF");
lcd.setCursor(0,1);
lcd.print("");
delay(20); 
digitalWrite(relay,LOW);
delay(500);
}
else
{
    
 lcd.clear();
lcd.setCursor(0,0);
lcd.print("DOOR CLOSED");
lcd.setCursor(0,1);
lcd.print("FENCING ON");
delay(20); 
digitalWrite(relay,HIGH);
delay(200);
}
}
