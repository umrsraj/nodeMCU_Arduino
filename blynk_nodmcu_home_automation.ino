/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

volatile int buttonState = 0;
volatile int buttonState1 = 0;
volatile int buttonState2 = 0;

int r1 = 0;
int r2 = 0;
int r3 = 0;

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

BLYNK_WRITE(V3)
{
   buttonState2 = param.asInt();
  Serial.print(F("buttonState2 = ")); Serial.println(buttonState2);
}
LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "31a4c852f9dd4245910df7173fa98d5f";
//char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";(my own)

 char auth[] = "14bb158d02394e6cac65f529e06dcb8f";


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "project12";
char pass[] = "project123456";

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1

void setup()
{
  // Debug console
  Serial.begin(9600);

  Serial.println("power up");
lcd.begin(16,2);

pinMode(D7,OUTPUT);
pinMode(D8,OUTPUT);
pinMode(10,OUTPUT);

attachInterrupt (D6,pinisr,RISING);

lcd.clear();
lcdstring(0,0,"  WELL COME TO  ");
lcdstring(0,1,"HOME AUTOMATION ");
delay(2000);

lcd.clear();
lcdstring(0,0,"  USING GOOGLE  ");
lcdstring(0,1,"   ASSISTANCE   ");
delay(2000);

lcd.clear();
lcdstring(0,0,"  CONNECTING TO ");
lcdstring(0,1,"     NETWORK    ");
delay(200);



  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);


  Blynk.notify("KIT STARTED");
  delay(100);

lcd1.clear();
lcd1.print(0,0,"  WELL COME TO  ");
lcd1.print(0,1,"HOME AUTOMATION ");
delay(2000);

lcd1.clear();
lcd1.print(0,0,"  USING GOOGLE  ");
lcd1.print(0,1,"   ASSISTANCE   ");
delay(2000);

  
lcd.clear();
lcd1.clear();
}

void loop()
{
  Blynk.run();

if (buttonState == 1)
{
  r1=1;
  delay(200);
  digitalWrite(D7,HIGH);
  delay(1000);
}
else if (buttonState == 0)
{
  r1=0;
  delay(200);
  digitalWrite(D7,LOW);
  delay(1000);
}

if (buttonState1 == 1)
{
  r2=1;
  delay(200);
  digitalWrite(D8,HIGH);
  delay(1000);
}
else if (buttonState1 == 0)
{
  r2=0;
  delay(200);
  digitalWrite(D8,LOW);
  delay(1000);
}
/*
if (buttonState2 == 1)
{
  r3=1;
  delay(200);
  digitalWrite(10,HIGH);
  delay(1000);
}
else if (buttonState2 == 0)
{
  r3=0;
  delay(200);
  digitalWrite(10,LOW);
  delay(1000);
}
*/

lcdstring(0,0,"L1: ");
lcdstring(4,0,String(r1));
lcdstring(8,0,"L2: ");
lcdstring(12,0,String(r2));
//lcdstring(0,1,"L3: ");
//lcdstring(4,1,String(r3));
delay(200);
lcd1.print(0,0,"L1: ");
lcd1.print(4,0,String(r1));
lcd1.print(8,0,"L2: ");
lcd1.print(12,0,String(r2));
//lcd1.print(0,1,"L3: "+String(r3));
/*
lcdstring(0,1,"L3: ");
lcdstring(4,1,String(digitalRead(D9)));
lcdstring(8,1,"L4: ");
lcdstring(12,1,String(digitalRead(D10)));
*/
delay(200);

}
void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
void pinisr ()
{
  Serial.println("pir alert*****");
  Blynk.notify("INTRUDER ALERT PLZ CHECK!!!");
  delayMicroseconds(400);
}
