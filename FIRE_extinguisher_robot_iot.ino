//Viral science www.youtube.com/c/viralscience
//FireFighter Truck
// http://projectsiot.xyz/IoTProjects/FireRobot/fireupload.php?a=Y&b=Y
// http://projectsiot.xyz/IoTProjects/FireRobot/firestatus.php

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>

// WiFi parameters to be configured
const char* ssid = "SmartFire"; // Hoofdlettergevoelig
const char* password = "FireRobot"; // Hoofdlettergevoelig
  String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7306667888&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/FireRobot/fireupload.php?a=";
String rs = "\0";
String obs = "\0";
String fir = "\0";
String LAT = "17.420110";
String LNG = "78.656512";
#define fire_sensor D1
#define obstacle_sensor D0 

#define m11 D2
#define m12 D3
#define m21 D4
#define m22 D5

#define relay D6
#define buzzer D7

//#define gled D8
//#define rled 1

unsigned int obstacle = 0;
unsigned int fire = 0;

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
  
pinMode (m11,OUTPUT);
pinMode (m12,OUTPUT);
pinMode (m21,OUTPUT);
pinMode (m22,OUTPUT);
pinMode (fire_sensor,INPUT);
pinMode (obstacle_sensor,INPUT);
pinMode (relay,OUTPUT);
pinMode (buzzer,OUTPUT);

Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  if (WiFi.status() != WL_CONNECTED) {
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
   
  http.begin("http://projectsiot.xyz/IoTProjects/FireRobot/fireupload.php?a=U&b=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

}


void loop()
{
obstacle = digitalRead(obstacle_sensor);
fire = digitalRead(fire_sensor);
Serial.print(F("obstacle = ")); Serial.println(obstacle);
Serial.print(F("fire = ")); Serial.println(fire);

if ((obstacle == 1)&&(fire == 1))
{ 
   Serial.println("both fire and obstacle alert*****");
  stopp ();
  beep ();
   msg = a+"FIRE%20ALERT%0AAT%0ALAT:"+LAT+"%0ALNG:"+LNG;
  send2server (msg);
  rs = r+'Y'+"&b="+'Y';
  send2server (rs);
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
  send2server (rs);
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
   msg = a+"FIRE%20ALERT%0AAT%0ALAT:"+LAT+"%0ALNG:"+LNG;
  send2server (msg);
  rs = r+'Y'+"&b="+'N';
  send2server (rs);
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
  send2server (rs);
  
}
} // LOOP

void send2server (String link)
{
Serial.print("rs = "); Serial.println(link);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(link);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}
