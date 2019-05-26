//Viral science www.youtube.com/c/viralscience
//FireFighter Truck
// http://projectsiot.xyz/IoTProjects/FireRobot/fireupload.php?a=Y&b=Y
// http://projectsiot.xyz/IoTProjects/FireRobot/firestatus.php

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <TinyGPS++.h>

#include <LiquidCrystal.h>
#include <String.h>
TinyGPSPlus gps;
#define ss Serial

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig
String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7680833470&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/GarbageMonitoring/upload.php?a=";
String rs = "\0";
String BIN1 = "\0";
String BIN2 = "\0";
int alc;

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);
#define trigPin D6
#define echoPin D7
#define trigPin1 D8
#define echoPin1 10


#define buzzer 1//RX

long duration, distance,duration1,distance1;

unsigned int obstacle = 0;
unsigned int fire = 0;
/*
void forward ()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  delay(10);
}

void backward ()
{
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m22, HIGH);
  digitalWrite(m21, LOW);
  delay(10);
}
void left ()
{
  digitalWrite(m12, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
  delay(10);
}

void right ()
{

  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  delay(10);
}
void stopp ()
{
  digitalWrite(m12, LOW);
  digitalWrite(m11, LOW);
  digitalWrite(m22, LOW);
  digitalWrite(m21, LOW);
  delay(10);
}
*/
void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}

void setup() {
  Serial.begin(9600);
  Serial.println("power up");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

 
//pinMode (rled,OUTPUT);
//pinMode (gled,OUTPUT);
  
//pinMode (m11,OUTPUT);
//pinMode (m12,OUTPUT);
//pinMode (m21,OUTPUT);
//pinMode (m22,OUTPUT);
//pinMode (fire_sensor,INPUT);
//pinMode (obstacle_sensor,INPUT);
//pinMode (relay,OUTPUT);
pinMode (buzzer,OUTPUT);
lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("*IOT BSD GARBAGE ***");
  lcd.setCursor( 0, 1);
  lcd.print("MONITORING SYSTEM ");
  delay(2500);
  
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("CONNECTING--TO");
        lcd.setCursor( 2,1);
         lcd.print(ssid);
         delay(100);

Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  
  // Verbonden.
  Serial.println("OK!");
  
  // Access Point (SSID).
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // IP adres.
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
Serial.println("state---------------1"); 
  // Signaalsterkte.
  long rssi = WiFi.RSSI();
  Serial.print("Signaal sterkte (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");


Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/HealthCare/healthupload.php?a=U&b=86&c=L");


if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/GarbageMonitoring/upload.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection

  lcd.clear();
 
  lcd.setCursor(0, 0);
  lcd.print("  GPS DETECTED       ");
  lcd.setCursor( 0, 1);
  lcd.print("                  ");

   delay(1500);
 
delay(5000);

  lcd.setCursor(0, 0);
  lcd.print("DUSTBIN 1:");
  lcd.setCursor( 0, 1);
  lcd.print("DUSTBIN 2:");
}

}


void loop()
{
  if (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

   if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
   // while(true);

  }
  lcd.setCursor(0, 0);
  lcd.print("DUSTBIN 1:");
  lcd.setCursor( 0, 1);
  lcd.print("DUSTBIN 2:");

//obstacle = digitalRead(obstacle_sensor);
//fire = digitalRead(fire_sensor);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
delay(50);
Serial.print(F("distance = ")); Serial.println(distance);
//Serial.print(F("obstacle = ")); Serial.println(obstacle);
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
distance1= duration1*0.034/2;
Serial.print("Distance: ");
Serial.println(distance1);
delay(50);
Serial.print(F("distance1 = ")); Serial.println(distance1);

if(distance>100)
{
  
  lcd.setCursor(10, 0);
  lcd.print("EMT     ");
  BIN1="EMPTY";
}
else if(distance<100&&distance>20)
{
  
  lcd.setCursor(10, 0);
  lcd.print("MID    ");
  BIN1="MIDIUM";
}
else if(distance<20)
{
  
  lcd.setCursor(10, 0);
  lcd.print("FUL    ");
  BIN1="FULL";
  beep();
  beep();
  msg = a+"BIN1--FULL%20AT%0ALAT:17.486962%0ALAN:78.656826";
  sendsms ();
}

if(distance1>100)
{
  
  lcd.setCursor(10, 1);
  lcd.print("EMT     ");
  BIN2="EMPTY";
}
else if(distance1<100&&distance1>20)
{
  
  lcd.setCursor(10, 1);
  lcd.print("MID       ");
  BIN2="MEDIUM";
}
else if(distance1<20)
{
  
  lcd.setCursor(10, 1);
  lcd.print("FUL     ");
  BIN2="FULL";
  beep();
  beep();

  msg = a+"BIN2--FULL%20AT%0A%0ALAT:17.486962%0ALAN:78.656826";
  sendsms ();

}

rs = r+BIN1+"&b="+BIN2;
  send2server ();

} // LOOP

void send2server ()
{
Serial.print("rs = "); Serial.println(rs);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(rs);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}
void sendsms ()
{
Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}



void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    delay(700);
  }
  else
  {
    Serial.print(F("INVALID"));
    delay(2000);
  }

  Serial.println();
}
