//Viral science www.youtube.com/c/viralscience
//FireFighter Truck
// http://projectsiot.xyz/IoTProjects/FireRobot/fireupload.php?a=Y&b=Y
// http://projectsiot.xyz/IoTProjects/FireRobot/firestatus.php

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig
 
 String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9010554823&from=MYDREM&message=";
 String a1 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7995542974&from=MYDREM&message=";

String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/GasBooking/gasupload.php?a=";
String rs = "\0";

String f1 = "\0";
String f = "\0";
String g = "\0";
String m = "\0";

int gas  = 0;

#define fire D6
#define force D7
#define gasPin A0 

#define relay 10
#define buzzer 1


void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}

void setup() {
  Serial.begin(9600);
  Serial.println("power up");
 lcd.begin(16,2);
 
pinMode (buzzer,OUTPUT);
pinMode (relay,OUTPUT);

pinMode (fire,INPUT);
pinMode (force,INPUT);
pinMode (gasPin,INPUT);

 lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" AUTOMATIC GAS  ");
     lcd.setCursor(0,1);
     lcd.print(" BOOKING SYSTEM  ");
     delay(2000);

Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("connecting to ");
     lcd.setCursor(0,1);
     lcd.print(ssid);
     Serial.print(".");
  }
  lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("connected to");
     lcd.setCursor(0,1);
     lcd.print(ssid); 
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


Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/GasBooking/gasupload.php?a==U&b=86&c=L");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/GasBooking/gasupload.php?a=U&b=N");

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

gas = analogRead(gasPin);
Serial.println("gas = "+String(gas));

if(gas > 650)
{
  Serial.println("gas alert.........");
   lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("   GAS ALERT    ");
     lcd.setCursor(0,1);
     lcd.print("PLEASE CHECK......");
      delay(100);
      beep ();
    g = "H";
    msg = a + "GAS%20LEAKAGE%20ALERT%0APLEASE%20CHECK";
    sendsms ();
    msg = a1 + "GAS%20LEAKAGE%20ALERT%0APLEASE%20CHECK";
   // sendsms ();
}
else
{
  g = "L";
}
if(digitalRead(force)==LOW)
{
  Serial.println("CYLINDER IS EMPTY alert.........");
   lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("CYLINDER IS EMPTY");
     lcd.setCursor(0,1);
     lcd.print("PLEASE CHECK......");
      delay(100);
      beep ();
    f1 = "E";
    msg = a + "YOUR%20GAS%20HAS%20BEEN%20BOOKED";
    sendsms ();
    msg = a1 + "CYLINDER%20IS%20EMPTY%0APLEASE%20BOOK%20THE%20GAS";
    sendsms ();
}
else
{
  f1 = "F";
}
if(digitalRead(fire)==HIGH)
{
  Serial.println("fire alert.........");
   lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("FIRE ALERT      ");
     lcd.setCursor(0,1);
     lcd.print("PLEASE CHECK......");
      delay(100);
      beep ();
      digitalWrite(relay,HIGH);
      delay(200);
    f = "Y";
    m = "Y";
       msg = a + "FIRE%20ALERT%0APLEASE%20CHECK";
    sendsms ();
    msg = a1 + "FIRE%20ALERT%0APLEASE%20CHECK";
    //sendsms ();
}
else
{
  f = "N";
  m = "N";
  digitalWrite(relay,LOW);
  delay(100);
}

lcd.clear();
lcd.setCursor(0,0);
     lcd.print("G: "+String(gas));
     lcd.setCursor(0,1);
     lcd.print("F: 0");
     lcd.setCursor(8,1);
     lcd.print("C: 1");
      delay(100);

   rs = r + f1 + "&b=" + g + "&c=" + f + "&d=" + m;
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
 
delay(50);
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
 
delay(50);
}
}
