/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define ir D0
#define relay D1

#define temp A0

#define m11 D2
#define m12 D3
#define m21 D4
#define m22 D5

#define pir D7
#define buzzer D8

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
delay(100);
}

void beep1 ()
{
  digitalWrite(buzzer,HIGH);
  delay(400);
  digitalWrite(buzzer,LOW);
delay(60);
  digitalWrite(buzzer,HIGH);
  delay(400);
  digitalWrite(buzzer,LOW);
delay(60);
}


float temp1=0.0;
unsigned temp2 = 0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f0c79de74672437094933f67fda836b8";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "project12";
char pass[] = "project123456";

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V1)
{
  int pinvalue = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pinvalue == 1)
{
  if (digitalRead(ir)==LOW)
  {
  forward ();
}
}
}
BLYNK_WRITE(V2)
{
  int pinvalue = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pinvalue == 1)
{
  if (digitalRead(ir)==LOW)
  {
  backward ();
}
}
}
BLYNK_WRITE(V3)
{
  int pinvalue = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pinvalue == 1)
{
  if (digitalRead(ir)==LOW)
  {
  left ();
}
}
}
BLYNK_WRITE(V4)
{
  int pinvalue = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pinvalue == 1)
{
  if (digitalRead(ir)==LOW)
  {
  right ();
}
}
}
BLYNK_WRITE(V5)
{
  int pinvalue = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pinvalue == 1)
{

  stopp ();

}
}
void forward ()
{
Serial.println("FORWARD ");
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
  delay(50);
}
void backward ()
{
Serial.println("BACKWARD ");
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  digitalWrite(m21,LOW);
  digitalWrite(m22,HIGH);
  delay(50);
}
void left ()
{
Serial.println("LEFT ");
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,HIGH);
  delay(50);
}
void right ()
{
Serial.println("RIGHT ");
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
  delay(50);
}
void stopp ()
{
Serial.println("STOP ");
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
  delay(50);
}


void setup()
{
  // Debug console
  Serial.begin(9600);
  Serial.println("power up");

 pinMode(temp,INPUT);
  pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  pinMode(m21,OUTPUT);
  pinMode(m22,OUTPUT);
  pinMode(relay,OUTPUT);
  pinMode(buzzer,OUTPUT);

  pinMode(ir,INPUT);
  pinMode(pir,INPUT);
  
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 

  temp1 = temp1 - 25;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);

if (temp1 > 50)
{
Serial.println("temperature alert");
beep ();
delay(100);
digitalWrite(relay,HIGH);
delay(300);
}
else
{
  delay(100);
digitalWrite(relay,LOW);
delay(100);
}
if (digitalRead(ir)==HIGH)
{
  beep ();
 Serial.println("obstacle alert...");
 left ();
 delay(1500);
 stopp ();
}

else if (digitalRead(pir)==HIGH)
{
 Serial.println("pir detected");
  beep1 ();
}


}
