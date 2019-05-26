//Viral science www.youtube.com/c/viralscience
//FireFighter Truck
// http://projectsiot.xyz/IoTProjects/FireRobot/fireupload.php?a=Y&b=Y
// http://projectsiot.xyz/IoTProjects/FireRobot/firestatus.php

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <LiquidCrystal.h>
#include <String.h>

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig
String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9014449822&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/DrunkDrive/uploadstatus.php?a=";
String rs = "\0";
String obs = "\0";
String fir = "\0";
int alc;

LiquidCrystal lcd (D0,D3,D4,D5,D6,D7);
//#define fire_sensor D1
//#define obstacle_sensor D0 

//#define m11 D2
//#define m12 D3
//#define m21 D4
//#define m22 D5

#define relay D1
#define buzzer D2

//#define gled D8
//#define rled 1

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
 
//pinMode (rled,OUTPUT);
//pinMode (gled,OUTPUT);
  
//pinMode (m11,OUTPUT);
//pinMode (m12,OUTPUT);
//pinMode (m21,OUTPUT);
//pinMode (m22,OUTPUT);
//pinMode (fire_sensor,INPUT);
//pinMode (obstacle_sensor,INPUT);
pinMode (relay,OUTPUT);
pinMode (buzzer,OUTPUT);
lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("***IOT BSD ***");
  lcd.setCursor( 0, 1);
  lcd.print("Drunk &DriveS/M ");
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
   
  http.begin("http://projectsiot.xyz/IoTProjects/DrunkDrive/uploadstatus.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(5000);
}

}


void loop()
{

//obstacle = digitalRead(obstacle_sensor);
//fire = digitalRead(fire_sensor);
alc=analogRead(A0);
Serial.print(F("alc = ")); Serial.println(alc);
//delay(2000);
//Serial.print(F("fire = ")); Serial.println(fire);
if(alc<900)
{
  rs = r+'N';
  send2server ();
  lcd.setCursor(0, 0);
  lcd.print("SYTEM  OK        ");
  lcd.setCursor( 0, 1);
  lcd.print("                    ");
  delay(1500);
  digitalWrite(relay,HIGH);
  delay(500);
  

}
else
{
   rs = r+'Y';
  send2server ();
   lcd.setCursor(0, 0);
  lcd.print("SYTEM NOT OK        ");
  lcd.setCursor( 0, 1);
  lcd.print("                    ");
  delay(1500);
  digitalWrite(relay,LOW);
  delay(500);
  beep();
  beep();
}

/*

if ((obstacle == 1)&&(fire == 1))
{ 
   Serial.println("both fire and obstacle alert*****");
  stopp ();
  beep ();
  rs = r+'Y'+"&b="+'Y';
  send2server ();
delay(100);
  digitalWrite(relay,HIGH);
  delay(2000);
  digitalWrite(relay,LOW);
  delay(2000);
   left ();
  delay(700);
  forward ();
  delay(200);
  
}
else if ((obstacle == 1)&&(fire == 0))
{
  Serial.println("obstacle present");
  stopp ();
  beep ();
  rs = r+'N'+"&b="+'Y';
  send2server ();
 delay(200);
  left ();
  delay(700);
  forward ();
  delay(200);
}

else if ((fire == 1)&&(obstacle == 0))
{
  Serial.println("FIRE ALERT");
  stopp ();
  beep ();
  rs = r+'Y'+"&b="+'N';
  send2server ();
  fir = 'Y';
  digitalWrite(relay,HIGH);
  delay(2000);
  digitalWrite(relay,LOW);
  delay(2000);
  forward ();
  delay(200);
}
else
{
  forward ();
   rs = r+'N'+"&b="+'N';
  send2server ();
}*/
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
