
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>
#include <stdio.h>

#define m11 D0
#define m12 D1
#define m21 D2
#define m22 D3

#define m31 D4
#define m32 D5
#define m41 D6
#define m42 D7

#define ir D8
#define buzzer 10


unsigned int obstacle = 0;
char ch;

String obs = "\0";  //obstacle detection alert
String mov = "\0";  //Robot Movement Alert-----

void forward ()
{
  Serial.println("moving --- forward ");
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  delay(10);
}

void backward ()
{
  Serial.println("moving --- backward ");
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m22, HIGH);
  digitalWrite(m21, LOW);
  delay(10);
}
void left ()
{
  Serial.println("moving --- left ");
  digitalWrite(m12, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
  delay(1500);
  stopp ();
}

void right ()
{

  Serial.println("moving --- right ");
  
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  delay(1500);
  stopp ();
}
void stopp ()
{
  Serial.println("moving --- stopp ");
  digitalWrite(m12, LOW);
  digitalWrite(m11, LOW);
  digitalWrite(m22, LOW);
  digitalWrite(m21, LOW);
  delay(10);
}

//-------------------hand control-----
void up(void)
{
  Serial.println("moving --- up ");
  digitalWrite(m31, HIGH); 
  digitalWrite(m32, LOW);   
 // digitalWrite(m2a, HIGH); 
 // digitalWrite(m2b, LOW); 
  delay(1500); 
    digitalWrite(m31, LOW); 
  digitalWrite(m32, LOW);   
  digitalWrite(m41, LOW); 
  digitalWrite(m42, LOW);              
}

void down(void)
{
  Serial.println("moving --- down ");
  digitalWrite(m31, LOW); 
  digitalWrite(m32, HIGH);   
//  digitalWrite(m2a, LOW); 
 // digitalWrite(m2b, HIGH); 
  delay(1500); 
    digitalWrite(m31, LOW); 
  digitalWrite(m32, LOW);   
  digitalWrite(m41, LOW); 
  digitalWrite(m42, LOW);              
}

void openm(void)
{
  Serial.println("moving --- open ");
 // digitalWrite(m1a, HIGH); 
  //digitalWrite(m1b, LOW);   
  digitalWrite(m41, LOW); 
  digitalWrite(m42, HIGH); 
 delay(1500);   
 digitalWrite(m31, LOW); 
  digitalWrite(m32, LOW);   
  digitalWrite(m41, LOW); 
  digitalWrite(m42, LOW);            
}

void closem(void)
{
  Serial.println("moving --- close ");
  //digitalWrite(m1a, LOW); 
  //digitalWrite(m1b, HIGH);   
  digitalWrite(m41, HIGH); 
  digitalWrite(m42, LOW); 
  delay(1500);  
    digitalWrite(m31, LOW); 
  digitalWrite(m32, LOW);   
  digitalWrite(m41, LOW); 
  digitalWrite(m42, LOW);             
}

void stop_motor(void)
{
  Serial.println("moving --- stop_motor ");
  digitalWrite(m31, LOW); 
  digitalWrite(m32, LOW);   
  digitalWrite(m41, LOW); 
  digitalWrite(m42, LOW); 
  delay(1000);               
}
//------------------------------------

void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}
 




// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/FruitPickRobot/upload.php?a=";
String rs = "\0";
//char read_msg[200] ;
String read_msg = "\0";
int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi


  
pinMode (m11,OUTPUT);
pinMode (m12,OUTPUT);
pinMode (m21,OUTPUT);
pinMode (m22,OUTPUT);

pinMode (m31,OUTPUT);
pinMode (m32,OUTPUT);
pinMode (m41,OUTPUT);
pinMode (m42,OUTPUT);

pinMode (ir,INPUT);
pinMode (buzzer,OUTPUT);


 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }

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

  Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=U&b=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/FruitPickRobot/upload.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
     String  payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

   

Serial.println(F("PLEASE SHOW CARD "));



}

void loop() {
  // put your main code here, to run repeatedly:


obstacle = digitalRead(ir);
//Serial.print(F("obstacle = ")); Serial.println(obstacle);



if (obstacle == 1)
{ 
  obs= "Y";
   Serial.println("OBSTACLE ALERT *****");
  stopp ();delay(200);  beep ();
  left (); 
  delay(1000);
  stopp ();
  rs = r+"Y"+"&b="+"S";
  send2server (rs);
  delay(200);
   //msg = a+"FIRE%20ALERT%0AAT%0ALAT:"+LAT+"%0ALNG:"+LNG;
  //send2server (msg);
  delay(2000);  
}

if (obstacle == 0)
{ 
  obs= "N";
}



if (Serial.available() !=0)
{ 
 while(Serial.available()!=0)
   {
  //  read_msg[count] = char(Serial.read());
    read_msg = Serial.readString();
    count ++;
    delay(5);
   }
  Serial.print("read_msg is = "); Serial.println(read_msg);

if ((read_msg.indexOf("forward")!=(-1))||(read_msg.indexOf("front")!=(-1))||(read_msg.indexOf("f")!=(-1))||(read_msg.indexOf("1")!=(-1)))
{
forward ();
mov = "F";

read_msg = "\0";
}
else if ((read_msg.indexOf("backward")!=(-1))||(read_msg.indexOf("back")!=(-1))||(read_msg.indexOf("b")!=(-1))||(read_msg.indexOf("2")!=(-1)))
{
backward ();
mov = "B";
read_msg = "\0";
}
else if ((read_msg.indexOf("left")!=(-1))||(read_msg.indexOf("l")!=(-1))||(read_msg.indexOf("3")!=(-1)))
{
left ();
mov = "L";
read_msg = "\0";
}
else if ((read_msg.indexOf("right")!=(-1))||(read_msg.indexOf("r")!=(-1))||(read_msg.indexOf("4")!=(-1)))
{
right ();
mov = "R";
read_msg = "\0";
}
else if ((read_msg.indexOf("stop")!=(-1))||(read_msg.indexOf("s")!=(-1))||(read_msg.indexOf("5")!=(-1)))
{
stopp ();
mov = "S";
read_msg = "\0";
}
else if ((read_msg.indexOf("up")!=(-1))||(read_msg.indexOf("u")!=(-1))||(read_msg.indexOf("6")!=(-1)))
{
up ();
mov = "U";
read_msg = "\0";
}
else if ((read_msg.indexOf("down")!=(-1))||(read_msg.indexOf("d")!=(-1))||(read_msg.indexOf("7")!=(-1)))
{
down ();
mov = "D";
read_msg = "\0";
}
else if ((read_msg.indexOf("open")!=(-1))||(read_msg.indexOf("o")!=(-1))||(read_msg.indexOf("8")!=(-1)))
{
openm ();
mov = "O";
read_msg = "\0";
}
else if ((read_msg.indexOf("close")!=(-1))||(read_msg.indexOf("c")!=(-1))||(read_msg.indexOf("9")!=(-1)))
{
closem ();
mov = "C";
read_msg = "\0";
}

  rs = r+obs+"&b="+mov;
  send2server (rs);
}//serial ava
}//loop
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
