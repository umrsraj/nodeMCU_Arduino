/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define m11 D1
#define m12 D2
#define m21 D3
#define m22 D4
#define ir  D5

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "e029b774158a4cd890688b527fd0afc7";

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

  pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  pinMode(m21,OUTPUT);
  pinMode(m22,OUTPUT);

  pinMode(ir,INPUT);
  
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
if (digitalRead(ir)==HIGH)
{
   left ();
}

}
