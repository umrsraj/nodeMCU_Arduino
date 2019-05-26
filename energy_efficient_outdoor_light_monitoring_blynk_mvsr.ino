/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "82c2dbf81959476084f87be8c9c82fa6";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "project12";
char pass[] = "project123456";

int ldr = 0;
String light = "D";
String S1= "1";
String S2 = "1";
String S3 = "1";

#define ir1 D1
#define ir2 D2
#define ir3 D3
#define rain D0
#define ldrPin A0
#define led1 D4
#define led2 D5
#define led3 D6

WidgetLCD lcd(V0);



void setup()
{
  // Debug console
  Serial.begin(9400);


pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(rain,INPUT);
pinMode(ldr,INPUT);
pinMode(ir1,INPUT);
pinMode(ir2,INPUT);
pinMode(ir3,INPUT);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

Blynk.notify("kit started");
delay(1000);

lcd.clear ();
lcd.print(0,0,"ENERGY EFFICIENT    ");
lcd.print(0,1,"OUTDOOR LIGHT");
delay(2000);
lcd.clear ();
lcd.print(0,0,"MONITORING SYSTEM  ");
lcd.print(0,1,"                       ");
delay(2000);

}

void loop()
{
  Blynk.run();

ldr = analogRead(ldrPin);
delay(10);

if (digitalRead(rain)==LOW)
{
  Serial.println("rain detected");
  Blynk.notify("RAIN DETECTED\nALL LIGHTS ON"); delay(500);
  lcd.clear ();
lcd.print(0,0,"RAIN DETECTED");
lcd.print(0,1,"OUTDOOR LIGHT");
delay(200);

  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);  
}
else
{
  if (ldr > 800)
  {
    light = "N";
    Serial.println("night detected");
    if (digitalRead(ir1)==HIGH)
    {
      S1 = "1";
      Serial.println("ir1 detected");
      digitalWrite(led1,HIGH);
    }
    else
    {
      S1 = "0";
      analogWrite(led1,200);
    }
  if (digitalRead(ir2)==HIGH)
    {
      S2 = "1";
      Serial.println("ir2 detected");
      digitalWrite(led2,HIGH);
    }
    else
    {
      S2 = "0";
      analogWrite(led2,200);
    }
  if (digitalRead(ir3)==HIGH)
    {
      S3 = "1";
      Serial.println("ir3 detected");
      digitalWrite(led3,HIGH);
    }
    else
    {
      S3 = "0";
      analogWrite(led3,200);
    }
  }//if night
  else
  {
    light  = "D";
    Serial.println("day mode detected");
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
  }
  //lcd.clear ();
  lcd.print(0,0,"L:"+light);
  lcd.print(8,0,"IR1:"+S1);
  
  lcd.print(0,1,"IR2:"+S2);
  lcd.print(8,1,"IR3:"+S3);
  delay(100);
  
}// if no rain
}//loop
