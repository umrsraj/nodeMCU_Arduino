#include <LiquidCrystal.h>

//#define voltage A0
#define sw1 A0
#define sw2 A1
#define sw3 A2
#define sw4 A3

#define buzzer 11
#define relay1 8
#define relay2 9
#define relay3 10
#define relay4 12

int v = 0;
int solar,wind,piezeo,hand;
float vol = 0;

LiquidCrystal lcdd (2,3,4,5,6,7);
void beep ()
{
  digitalWrite(buzzer,HIGH); delay(700);
  digitalWrite(buzzer,LOW); delay(100);
}
void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
Serial.println("power up");
lcdd.begin (16,2);

pinMode(sw1,INPUT);
pinMode(sw2,INPUT);
pinMode(sw3,INPUT);
pinMode(sw4,INPUT);

pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);
pinMode(relay3,OUTPUT);
pinMode(relay4,OUTPUT);

pinMode(buzzer,OUTPUT);

lcdd.clear ();
lcd(0,0,"  MC BSD POWER  ");
lcd(0,1,"SWITCHING USING ");
delay(2000);

lcdd.clear ();
lcd(0,0,"DIFFERENT SOURCES");
lcd(0,1,"*****************");
delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:

//v = analogRead (voltage);
//delay(50);

solar = analogRead(sw1);
delay(50);
wind = analogRead(sw2);
delay(50);
piezeo = analogRead(sw3);
delay(50);
hand = analogRead(sw4);
delay(50);

 //vol= v * (5.00/1023.00)*5;
//Serial.print("VOLTAGE = "); Serial.println (vol);
Serial.println();
Serial.print("solar = "); Serial.println (solar);
Serial.print("wind = "); Serial.println (wind);
Serial.print("mains = "); Serial.println (piezeo);
Serial.print("dynamo = "); Serial.println (hand);
delay(50);
/*
if (vol < 8)
{
lcdd.clear();
lcd(0,0," LOW BAT ALERT  ");
lcd(4,1,"V: ");
lcd(7,1,String(vol));
  beep ();
  delay(1000);
}

else
*/
if (solar > 550)
{
  lcdd.clear();
lcd(0,0,"SOURCE >> SOLAR");
//lcd(4,1,"V: ");
//lcd(7,1,String(vol));
delay(50);
digitalWrite(relay1,HIGH);
digitalWrite(relay2,LOW);
digitalWrite(relay3,LOW);
delay(400);
}
else if (wind > 550)
{
  lcdd.clear();
lcd(0,0," SOURCE >> WIND ");
//lcd(4,1,"V: ");
//lcd(7,1,String(vol));
delay(50);
digitalWrite(relay2,HIGH);
digitalWrite(relay1,LOW);
digitalWrite(relay3,LOW);
delay(400);
}
else if (piezeo > 550)
{
  lcdd.clear();
lcd(0,0,"SOURCE >> MAINS ");
//lcd(4,1,"V: ");
//lcd(7,1,String(vol));
delay(50);
digitalWrite(relay3,HIGH);
digitalWrite(relay1,LOW);
digitalWrite(relay2,LOW);
delay(400);
}
/*
else if (hand > 550)
{
  lcdd.clear();
lcd(0,0,"SOURCE >> DYNAMO");
lcd(4,1,"V: ");
lcd(7,1,String(vol));
delay(400);
}
*/
else 
{
  lcdd.clear();
lcd(0,0,"   NO  SOURCE   ");
//lcd(4,1,"V: ");
//lcd(7,1,String(vol));
delay(50);
digitalWrite(relay3,LOW);
digitalWrite(relay1,LOW);
digitalWrite(relay2,LOW);
delay(400);
}
}
void lcd(int a, int b, String data)
{
  lcdd.setCursor(a,b);
  lcdd.print(data);
}
/*
void healthcheck ()
{
  for (int x=8;x<13;x++)
  {
    digitalWrite(x,HIGH);
  }
  delay(500);
  for (int x=8;x<13;x++)
  {
    digitalWrite(x,LOW);
  }
  delay(500);
  
  for (int x=8;x<13;x++)
  {
    digitalWrite(x,HIGH);
  }
  delay(500);
  for (int x=8;x<13;x++)
  {
    digitalWrite(x,LOW);
  }
  delay(500);
}
*/
