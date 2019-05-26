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
String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9550858787&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/Agriculture/uploadstatus.php?a=";
String rs = "\0";
String r1 = "http://api.thingspeak.com/update?api_key=A80AKBFWGLN3KT7I";
String rs1 = "\0";

String HUM = "N";
String SOIL = "N";
String MOTOR = "N";

int alc;

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);
#define temp A0
#define humPin D7
#define soilPin D8
#define relay 10


float temp1=0.0;
unsigned temp2 = 0;
unsigned int h = 0;
unsigned int s = 0;
unsigned int m = 0;

int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;

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

void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}
*/

void setup() {
  Serial.begin(9600);
  Serial.println("power up");

  pinMode(temp, INPUT);
  pinMode(soilPin, INPUT);
pinMode(humPin, INPUT);
  pinMode(relay, OUTPUT);

 
lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION         ");
  lcd.setCursor( 0, 1);
  lcd.print("MONITORING S/M      ");
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


Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/Agriculture/uploadstatus.php?a=U&b=86&c=L");


if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/Agriculture/uploadstatus.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(5000);

  lcd.setCursor(0, 0);
  lcd.print("SERVER INT.       ");
  lcd.setCursor( 0, 1);
  lcd.print("     DONE     ");
delay(3000);

}

}


void loop()
{

temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 

  temp1 = temp1 -20;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);

if (temp1 > 55)
{
  Serial.println("high temperature.........");
  lcdstring(0,0,"TEMPERATURE ALERT   ");
  lcdstring(0,1,"T: "+String(temp1));
  delay(20);
 // digitalWrite(relay,LOW);
  delay(500);

  rs = r + String(temp1) + "&b=" + HUM + "&c=" + SOIL + "&d=" + MOTOR ; 
  send2server (rs);
if (flag1 == 0)
{
msg = a + "HIGH%20TEMPERATURE%20ALERT%0AT:"+String(temp1);
sendsms (msg);
flag1 = 1;
} 
  rs1 = r1 + "&field1=" + String(temp1) ; 
  send2server (rs1);
  delay(1800);
}
if (digitalRead(humPin)==HIGH)
{
  Serial.println("humidity alert........");
  lcdstring(0,0,"HUMIDITY ALERT    ");
  lcdstring(0,1,"PLEASE CHECK.......");
  delay(20);
  //digitalWrite(relay,LOW);
  delay(500);
 
  HUM = "Y";
h = 100;
if (flag2 == 0)
{
  flag2 = 1;
msg = a + "HIGH%20HUMIDITY%20ALERT" ;
sendsms (msg);
}  
  rs = r + String(temp1) + "&b=" + HUM + "&c=" + SOIL + "&d=" + MOTOR ; 
  send2server (rs);

 
  rs1 = r1 + "&field2=" + "100" ; 
  send2server (rs1);
  delay(1800);
}

else
{
 flag2 = 0;
  HUM = "N";
}
 if (digitalRead(soilPin)==HIGH)
{
  Serial.println("SOIL alert........");
  lcdstring(0,0,"SOIL WET DETECTED   ");
  lcdstring(0,1,"PLEASE CHECK.......");
  delay(20);
  digitalWrite(relay,LOW);
  delay(500);
  MOTOR = "N";
  SOIL = "Y";
s = 100;
m = 0;

if(flag3==0)
{
flag3 = 1;
msg = a + "WET%20SOIL%20DETECTED%0AMOTOR%20OFF";
sendsms (msg);
} 
flag4 = 0; 
  rs = r + String(temp1) + "&b=" + HUM + "&c=" + SOIL + "&d=" + MOTOR ; 
  send2server (rs);

  rs1 = r1 + "&field3=" + "100" ; 
  send2server (rs1);
}
else
{
 flag3 = 0;
  SOIL = "N";
  if(flag4==0)
{
flag4 = 1;
msg = a + "DRY%20SOIL%20DETECTED%0AMOTOR%20ON";
sendsms (msg);
}  
}
if ((temp1<55)&&(digitalRead(humPin)==LOW)&&(digitalRead(soilPin)==LOW))
{
flag1 = 0;
flag2 = 0;
flag3 = 0;

  lcdstring(0,0,"                       ");
  lcdstring(0,1,"                       ");
  
  lcdstring(0,0,"T: "+String(temp1));
  lcdstring(8,0,"H: 0");
  lcdstring(0,1,"S: DRY ");
  lcdstring(8,1,"M: ON ");
  
  Serial.println("system is normal....");
  digitalWrite(relay,HIGH);
  delay(300);
  MOTOR = "Y";
}
 rs = r + String(temp1) + "&b=" + HUM + "&c=" + SOIL + "&d=" + MOTOR ; 
  send2server (rs);
    rs1 = r1 + "&field1=" + String(temp1) ; 
  send2server (rs1);

} // LOOP

void send2server (String linkk)
{
Serial.print("rs = "); Serial.println(linkk);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(linkk);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}
void sendsms (String link)
{
Serial.print("msg = "); Serial.println(link);
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
void lcdstring (int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
