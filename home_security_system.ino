
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>
#include <stdio.h>


#define pir D6
#define ir D7
#define relay D8
#define buzzer 1
#define gled 3
#define rled 10

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8179605909&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/HomeSecurity/secupload.php?";
String rs = "\0";
char read_msg[200] ;
int v = 0;
int count = 0;
char msg1[200] = "" ;
char msg2[200] = "" ;

void lcdstring (unsigned int a, unsigned int b, String data);


LiquidCrystal lcd (D5,D4,D3,D2,D1,D0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

pinMode(pir,INPUT);
pinMode(ir,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(relay,OUTPUT);
//pinMode(gled,OUTPUT);
//pinMode(rled,OUTPUT);


  
  lcd.begin(16, 2);
  
  lcd.clear();
  lcdstring(0,0," HOME SECURITY  ");
  lcdstring(0,1,"     SYSTEM     ");
  delay(2000);

  Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     lcd.clear();
  lcdstring(0,0,"CONNECTING WI-FI");
  delay(200);
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
     lcd.clear();
  lcdstring(0,0,"WI-FI CONNECTED");
  delay(2000);

lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  delay(2000);
  Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=U&b=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/HomeSecurity/secupload.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
     String  payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}


lcd.clear();
  lcdstring(0,0,"SERVER INT. DONE");
  delay(2000);
lcd.clear();    

Serial.println(F("PLEASE SHOW CARD "));



}

void loop() {
  // put your main code here, to run repeatedly:

if ((digitalRead(D6)==HIGH)&&(digitalRead(ir)==HIGH))
{
  Serial.println("INTRUDER AT VAULT");
   digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
  lcd.clear();
  lcdstring(0,0,"INTRUDER AT VAULT");
  lcdstring(0,1," SHCKING S/M ON ");
  delay(100);
  digitalWrite(relay,HIGH);
  delay(500);
  beep ();
   rs = r+"a="+'Y'+"&b="+'Y';
  send2server ();
  delay(100);
   msg = a+"INTRUDER%20IS%20AT%20VAULT%0ASHOCKING%20SYSTEM%20IS%20ON%0APLEASE%20CHECK";
  sendmsg (); 
  delay(2000);
}

else if (digitalRead(pir)==HIGH)
{
  Serial.println("intruder alert");
   digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
  lcd.clear();
  lcdstring(0,0,"INTRUDER ALERT");
  lcdstring(0,1,"PLEASE CHECK....");
  delay(100);
  digitalWrite(relay,LOW);
  delay(500);
  beep ();
   rs = r+"a="+'N'+"&b="+'Y';
  send2server ();
  delay(100);
   msg = a+"INTRUDER%20ALERT%20PLEASE%20CHECK";
  sendmsg (); 
  delay(2000);
}
else if (digitalRead(ir)==HIGH)
{
  Serial.println("THEFT ALERT AT VAULT");
   digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
    lcd.clear();
  lcdstring(0,0,"VAULT THEFT ALERT");
  lcdstring(0,1,"PLEASE CHECK....");
  delay(100);
  digitalWrite(relay,HIGH);
  delay(500);
  beep ();
   rs = r+"a="+'Y'+"&b="+'N';
  send2server ();
  delay(100);
   msg = a+"VAULT%20THEFT%20ALERT%0ASHOCKING%20SYSTEM%20IS%20ON%0APLEASE%20CHECK";
  sendmsg (); 
  delay(2000);
}
else
{
  lcd.clear();
  lcdstring(0,0,"SYSTEM IS NORMAL");
  lcdstring(0,1,"..................");
  delay(200);
    rs = r+"a="+'N'+"&b="+'N';
  send2server ();
  digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
  delay(100);
}

}// loop

void lcdstring (unsigned int a, unsigned int b, String data)
{
  // lcd.clear();
  lcd.setCursor(a, b);
  lcd.print(data);
}

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

void sendmsg ()
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

void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}
