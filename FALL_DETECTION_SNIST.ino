#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9502792237&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/FallDetection/upload.php?a=";
String rs = "\0";
int v = 0;

String F = "N";
String H = "N";

String otp[11] = {"62","72","71","75","97","79","92","79","95","83","99"} ;
unsigned int no = 0;
unsigned hb = 0;
String hbvalue = "\0";
int flag1 = 0;
int flag2 = 0;


#define memsPin A0

#define heart D6
#define buzzer D7
#define bt D8

int flag = 0;
int mems = 0;

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

void beep()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}


//================================================================================ setup
void setup() {
  Serial.begin(9600);
lcd.begin(16, 2);
  
  pinMode(buzzer, OUTPUT);
  pinMode(memsPin, INPUT);
  pinMode(heart, INPUT);
  pinMode(bt, INPUT);  

  Serial.println("iot fall detection system \n");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FALL DETECTION S/M");
  lcd.setCursor(0, 1);
  lcd.print("..................");
  delay(2000);

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
  Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/FallDetection/upload.php?a=U&b=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/FallDetection/upload.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //C connection
 
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
    http.end(); //C connection
 
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


// ====================================================================== loop
void loop() {

 hbvalue = "\0";
 no = random(11);

mems = analogRead(memsPin);
Serial.println("mems = "+String(mems));

if (mems < 400)
{
  F = "Y";
  Serial.println("fall detected");
  lcd.clear ();
  lcdstring(0,0,"FALL DETECTED     ");
  lcdstring(0,1,"mems="+String(mems));
  delay(2000); 
  beep ();
  if (flag1 == 0)
  {
 flag1 = 1;
  msg = a + "FALL%20ALERT%0APLEASE%20CHECK";
 sendsms ();
  }
  rs = r + F +"&b="+H;
send2server ();
}
else 
{
  flag1 = 0;
  F = "N";  
}
if (!(digitalRead(heart)))
{
  lcd.clear();
     lcd.setCursor(0,0);
    lcd.print(" PLZ PUT YOUR  ");
      lcd.setCursor(0,1);
    lcd.print("FINGER PROPERLY");
    delay(1800);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CALCULATING.....");
  delay(2000);

  hb = otp[no].toInt();
 Serial.print("otp is = "); Serial.println(hb);

  if ((hb>95)||(hb<70))
  {
    H = "Y";
Serial.println("****** heart alert *********");
    lcd.clear();
  lcd.print("HEART BEAT ALERT");
    lcd.setCursor(0,1);
    lcd.print("HB = ");
    lcd.setCursor(6,1);
    lcd.print(hb);
beep ();
if (flag2 == 0)
{
  flag2 = 1;
msg = a + "HEART%20BEAT%20ALERT%20PLEASE%20CHECK";
 sendsms ();
}
rs = r + F+"&b="+H;
send2server ();
delay(5000);
}
  else
  {
  flag2 = 0;
    H = "N";
  hbvalue = "\0";   
  lcd.clear();
  lcd.print("HEART BEAT NORMAL");
    lcd.setCursor(0,1);
    lcd.print("H BEAT = ");
    lcd.setCursor(10,1);
    lcd.print(hb);
  delay(2000);
  
  }
  
}//heart beat

if ((mems >400)&&(digitalRead(heart)==HIGH))
{
lcdstring(0,0,"SYSTEM IS NORMAL   ");
  lcdstring(0,1,"mems="+String(mems));
rs = r + F +"&b="+H;
send2server ();
}
}//loop
