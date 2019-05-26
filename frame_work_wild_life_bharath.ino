#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);



// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydm123&to=9652490222&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/WildLife/upload.php?a=";
String rs = "\0";
int v = 0;

char F = 'N';
char H = 'N';
char R = 'N';



String otp[11] = {"62","72","71","75","97","79","92","79","95","83","99"} ;
unsigned int no = 0;
unsigned hb = 0;
String hbvalue = "\0";



#define temp A0
#define rain D6
#define fire D7
#define hum D8

int flag = 0;
float temp1=0.0;
unsigned temp2 = 0;


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



//================================================================================ setup
void setup() {
  Serial.begin(9600);
lcd.begin(16, 2);
  
  pinMode(hum, INPUT);
  pinMode(fire, INPUT);
  pinMode(rain, INPUT);  
pinMode(temp,INPUT);

  Serial.println("iot fall detection system \n");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WILD FIRE TRACKING   ");
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
  Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=U&b=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/WildLife/upload.php?a=U");

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


temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 

  temp1 = temp1 - 30;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);
//Serial.print("button = "); Serial.println(digitalRead(button));

if(temp1>50)
{
 Serial.println("high temperatuere detected");
  lcd.clear ();
  lcdstring(0,0,"TEMPERATURE ALERT    ");
  lcdstring(0,1,"PLEASE CHECK     ");
  delay(2000); 
  msg = a + "FALL%20ALERT%0APLEASE%20CHECK";
// sendsms ();
}
if (digitalRead(rain)==LOW)
{
  R = 'Y';
  Serial.println("high temperatuere detected");
  lcd.clear ();
  lcdstring(0,0,"RAIN DETECTED    ");
  lcdstring(0,1,"PLEASE CHECK     ");
  delay(2000); 
  msg = a + "FALL%20ALERT%0APLEASE%20CHECK"; 
  // sendsms ();
}
else 
{
  R = 'N';
}
if (digitalRead(fire)==HIGH)
{
   F = 'Y';
  Serial.println("high temperatuere detected");
  lcd.clear ();
  lcdstring(0,0,"FIRE DETECTED    ");
  lcdstring(0,1,"PLEASE CHECK     ");
  delay(2000); 
  msg = a + "FALL%20ALERT%0APLEASE%20CHECK"; 
  // sendsms (); 
}
else
{
  F = 'N';
}
if (digitalRead(hum)==HIGH)
{
   H = 'Y';
  Serial.println("high temperatuere detected");
  lcd.clear ();
  lcdstring(0,0,"HUMIDITY ALERT      ");
  lcdstring(0,1,"PLEASE CHECK     ");
  delay(2000); 
  msg = a + "FALL%20ALERT%0APLEASE%20CHECK"; 
  // sendsms (); 
}
else
{
  H = 'N';
}
if ((H=='N')&&(F=='N')&&(R=='N')&&(temp1 < 50))
{
lcd.clear ();
  lcdstring(0,0,"T:"+String(temp1));
  lcdstring(8,0,"R: 0");
  lcdstring(0,1,"F: 0");
  lcdstring(8,1,"H: 0");
  delay(200); 
}
rs = r + String(temp1) +"&b="+ R + "&c=" + F + "&d=" + H;
send2server ();
}//loop
