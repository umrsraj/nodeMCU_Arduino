
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/VisitorCounter/upload.php?a=";
String rs = "\0";

int inir = 0;
int L1 = 0;
int L2 = 0;
int L3 = 0;

int in=0,out=0,tot=0;

#define inir1 A0
#define outir D6
#define relay1 D7
#define relay2 D8
#define relay3 10
#define buzzer 03

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);


void lcdstring (unsigned int a, unsigned int b, String data);


void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}


void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();
  lcdstring(0,0,"*** IOT BASED *** ");
  lcdstring(0,1,"VISITOR COUNTER    ");
  delay(2000);

pinMode(buzzer,OUTPUT);
pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);
pinMode(relay3,OUTPUT);
pinMode(inir1,INPUT);
pinMode(outir,INPUT);


Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     lcd.clear();
  lcdstring(0,0," CONNECTING  TO ");
  lcdstring(0,1,ssid);
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
  lcdstring(0,0,"  CONNECTED TO  ");
  lcdstring(0,1,ssid);
  delay(2000);

lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"  PLEASE WAIT  ");
  delay(2000);
  Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=U&b=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/VisitorCounter/upload.php?a=U&b=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
/*
Serial.print(F("sending init message............"));
Serial.print("msg = "); Serial.println("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=KIT%20STARTED");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
 http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=KIT%20STARTED");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
*/


lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"      DONE      ");
  delay(2000);
//lcd.clear();    
//Serial.println(F("PLEASE SHOW CARD "));

lcd.clear ();

  lcdstring(0,0,"I:");
  lcdstring(5,0,"O:");
  lcdstring(10,0,"T:");
  lcdstring(0,1,"L1:");
  lcdstring(6,1,"L2:");
  lcdstring(12,1,"L3:");
delay(200);

}

void loop()
{

 
inir = analogRead(inir1);
delay(5);
Serial.print("inir value = "); Serial.println(inir);

if(tot > 10)
{
  L1 = 1;
  L2 = 1;
  L3 = 1;
  delay(100);
  digitalWrite(relay1,HIGH);
  delay(100);
  digitalWrite(relay2,HIGH);
  delay(100);
  digitalWrite(relay3,HIGH);
  delay(100);
}
else if(tot > 4)
{
  L1 = 1;
  L2 = 1;
  L3 = 0;
  delay(100);
  digitalWrite(relay1,HIGH);
  delay(100);
  digitalWrite(relay2,HIGH);
  delay(100);
  digitalWrite(relay3,LOW);
  delay(100);
}
else if(tot > 0)
{
  L1 = 1;
  L2 = 0;
  L3 = 0;
  delay(100);
  digitalWrite(relay1,HIGH);
  delay(100);
  digitalWrite(relay2,LOW);
  delay(100);
  digitalWrite(relay3,LOW);
  delay(100);
}
else
{
  L1 = 0;
  L2 = 0;
  L3 = 0;
  delay(100);
  digitalWrite(relay1,LOW);
  delay(100);
  digitalWrite(relay2,LOW);
  delay(100);
  digitalWrite(relay3,LOW);
  delay(100);
}

if(inir > 550)

//if (digitalRead(inir1)==HIGH)
{
  Serial.println("in count = "+String(in));
    in++;
    tot = in - out ;

     lcdstring(0,0,"I:"+String(in));
  lcdstring(5,0,"O:"+String(out));
  lcdstring(10,0,"T:"+String(tot));
  lcdstring(0,1,"L1:"+String(L1));
  lcdstring(6,1,"L2:"+String(L2));
  lcdstring(12,1,"L3:"+String(L3));
  
      if (tot> 30)
    {
      beep ();
    }
  
    while(analogRead(inir1)>550);
}
else if(digitalRead(outir)==HIGH)
{

  Serial.println("out count = "+String(in));
    out++;
    
    tot = in - out ;

if (tot < 0 )
{
  tot = 0;
}
    
     lcdstring(0,0,"I:"+String(in));
  lcdstring(5,0,"O:"+String(out));
  lcdstring(10,0,"T:"+String(tot));
  lcdstring(0,1,"L1:"+String(L1));
  lcdstring(6,1,"L2:"+String(L2));
  lcdstring(12,1,"L3:"+String(L3));
  
    while(digitalRead(outir)==HIGH);

}

rs = r + String(in) + "&b=" + String(out) + "&c=" + String(tot) + "&d=" + String(L1)+ "&e=" + String(L2)+ "&f=" + String(L3);

        Serial.println(rs);
        send2server ();

}// loop
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

void lcdstring (unsigned int a, unsigned int b, String data)
{
  // lcd.clear();
  lcd.setCursor(a, b);
  lcd.print(data);
}
