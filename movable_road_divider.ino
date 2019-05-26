#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>


LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/MovableDivider/upload.php?a=";
String rs = "\0";
int v = 0;

#define m11 1
#define m12 3
#define irl D6
#define irm D7
#define irh D8
#define buzzer 10

unsigned int previous_status = 0;
unsigned int present_status = 0;
unsigned int vol = 0;
unsigned int alc = 0;
float voltage = 0.0;
float sound = 0.0;

String charging_status = "\0";
int state = 0;

int state1;

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
  delay(400);
  digitalWrite(buzzer,HIGH);
  delay(400);
  digitalWrite(buzzer,LOW);
  delay(100);
}

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);
  Serial.println("power up");

  lcd.begin(16, 2);
  lcd.clear();
  lcdstring(0,0,"    MOVABLE     ");
  lcdstring(0,1,"  ROAD DIVIDER  ");
  delay(2000);

pinMode(irl,INPUT);
pinMode(irm,INPUT);
pinMode(irh,INPUT);
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(buzzer,OUTPUT);

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

lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"  PLEASE WAIT  ");
  delay(2000);
  Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=U&b=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/MovableDivider/upload.php?a=U");

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
lcd.clear();    
Serial.println(F("PLEASE SHOW CARD "));
}

void loop()
{

if ((digitalRead(irl) == HIGH) && (digitalRead(irm) == HIGH) && (digitalRead(irh) == HIGH))
{
Serial.println(F("traffic high"));
lcd.clear();
  lcdstring(0,0,"T. LEVEL: HIGH");
  lcdstring(0,1," ");
  delay(200);
 beep ();
  if(state == 0)
  {
    state = 1;
digitalWrite(m11,HIGH);
digitalWrite(m12,LOW);
   delay(2000);
 digitalWrite(m11,LOW);
 digitalWrite(m12,LOW);
 delay(200);
  }
 rs = r + "H";
 send2server ();
 
}
else if ((digitalRead(irl) == HIGH) && (digitalRead(irm) == HIGH) && (digitalRead(irh) == LOW))
{
Serial.println(F("traffic mediUM"));
lcd.clear();
  lcdstring(0,0,"T. LEVEL: MEDIUM");
  lcdstring(0,1," ");
  delay(200);
 beep ();
  if(state == 1)
  {
   state = 0;
digitalWrite(m12,HIGH);
digitalWrite(m11,LOW);
   delay(2000);
 digitalWrite(m11,LOW);
 digitalWrite(m12,LOW);
 delay(200);
  }
 rs = r + "M";
 send2server ();
 
}

else if ((digitalRead(irl) == HIGH) && (digitalRead(irm) == LOW) && (digitalRead(irh) == LOW))
{
Serial.println(F("traffic LOW"));
lcd.clear();
  lcdstring(0,0,"T. LEVEL: LOW");
  lcdstring(0,1," ");
  beep1 (); 
  if(state == 1)
  {
 
   state = 0;
digitalWrite(m12,HIGH);
digitalWrite(m11,LOW);
   delay(2000);
 digitalWrite(m11,LOW);
 digitalWrite(m12,LOW);
 delay(200);
  }
 
 rs = r + "L";
 send2server ();
 
}
else 
{
  Serial.println(F("no traffic"));
lcd.clear();
  lcdstring(0,0,"NO TRAFFIC");
  lcdstring(0,1," ");
  delay(200);
  
  if(state == 1)
  {
   state = 0;
digitalWrite(m12,HIGH);
digitalWrite(m11,LOW);
   delay(2000);
 digitalWrite(m11,LOW);
 digitalWrite(m12,LOW);
 delay(200);
  }
  rs = r + "N";
 send2server ();
}
 

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
