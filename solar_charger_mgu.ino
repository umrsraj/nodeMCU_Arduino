/*
 *  * hotspot name : project12
 * hotspot possword : project123456
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
#include <stdlib.h>
#include <String.h>

#define volPin A0
#define relay D6
#define buzzer D7

int flag = 0;

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

 String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7013624803&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/Voltage/upload.php?a=";
String rs = "\0";

 
int i = 0;

String hbvalue = "\0";
String S = "N";
String M = "N";
float temp1=0.0;
String gas1 = "\0";

unsigned int v ;
float vol;

int soil = 0;

String otp[11] = {"62","72","71","75","97","79","92","79","95","83","99"} ;
unsigned int no = 0;
unsigned hb = 0;
unsigned temp2 = 0;

void beep()
{
   digitalWrite(buzzer, HIGH); 
   delay(500);
    digitalWrite(buzzer, LOW); 
    delay(50);
}
void showprojectname ()
{
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MOBILE CHARGER USING   ");
    lcd.setCursor(0,1);
    lcd.print("SOLAR                  ");
  delay(2500);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  lcd.begin(16,2);

 pinMode(volPin,INPUT);
pinMode(relay,OUTPUT);
pinMode(buzzer,OUTPUT);
showprojectname ();

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
/*
Serial.println("sending welcome message............");
 
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 //  http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=KIT%20STARTED"); //Specify request destination

 
int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(4000);
}
*/



}

void loop() {

v = analogRead(volPin);
delay(5);
 vol= v * (5.00/1023.00)*5;
vol = vol-1;
Serial.print(F("voltage = ")); Serial.println(vol); 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Vol: "+String(vol));

if (vol < 7)
{
    lcd.setCursor(0,1);
    lcd.print("CHARGING - OFF     ");
  Serial.println("low voltage");
  delay(200);
  digitalWrite(relay,LOW);
  delay(200);
 beep ();
if (flag == 0)
{
  flag = 1;
  msg = a + "Vol:"+String(vol)+"%0ACHARGING-OFF";
  send2server (msg);
}
  
}
 else
 {
    lcd.setCursor(0,1);
    lcd.print("CHARGING - ON     ");
  delay(100);
   digitalWrite(relay,HIGH);
  delay(200);
  if (flag == 1)
{
  flag = 0;
  msg = a + "Vol:"+String(vol)+"%0ACHARGING-ON";
  send2server (msg);
}
 }
rs = r + String(vol);
 send2server (rs);
}// loop

void send2server (String link)
{
Serial.print("link = "); Serial.println(link);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  //http.begin("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=U&b=Y");
http.begin(link);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(50);
}

  
}
/*
void sendsms ()
{
Serial.println("sending welcome message............");
 
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
//   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message="); 
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
*/

void lcdstring(int a,int b, String data1)
{
  lcd.setCursor(a,b);
  lcd.print(data1);
}
