/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <LiquidCrystal.h>


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "402a3d9301ae4affb9e7166d55c9bc5e";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "project12";
char pass[] = "project123456";
int rr = 0;
int rrr = 0;

WidgetLCD lcd1(V0);

BLYNK_WRITE(V1) {
 int buttonState = param.asInt ();

analogWrite(D8,buttonState);
delay(100);
if (buttonState > 20)
{
  rr = 1;
}
 else {
  rr = 0;
 }
}
/*
BLYNK_WRITE(V2) {
 int buttonState = param.asInt ();

Serial.println("looppppp");
analogWrite(D7,buttonState);
delay(100);
if (buttonState > 0)
{
  rrr = 1;
}
 else {
  rrr = 0;
 }
}
*/
LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

void setup()
{
  // Debug console
  Serial.begin(9600);
lcd.begin(16,2);

lcdstring(0,0,"HOME  APPLIANCES   ");
lcdstring(0,1,"  CONTROL SYSTEM   ");
delay(2500);

  
  Blynk.begin(auth, ssid, pass);

Blynk.notify("kit started");
delay(1000);

  lcd1.clear(); //Use it to clear the LCD Widget
  lcd1.print(0, 0, "HOME APPLIANCES"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd1.print(0, 1, "    CONTROL    ");
  delay(2000);

   lcd1.clear();
  
lcdstring(0,0,"                    ");
lcdstring(0,1,"                    ");
}

void loop()
{
  Blynk.run();
lcd1.print(0,0,"D1: "+String(digitalRead(D6)));
lcd1.print(8,0,"D2: "+String(digitalRead(D7)));
lcd1.print(0,1,"D3: "+String(rr));
delay(20);

lcdstring(0,0,"D1: "+String(digitalRead(D6)));
lcdstring(8,0,"D2: "+String(digitalRead(D7)));
lcdstring(0,1,"D3: "+String(rr));
delay(200);
}
void lcdstring(int a, int b, String dataa)
{
lcd.setCursor(a,b);
lcd.print(dataa);
}
