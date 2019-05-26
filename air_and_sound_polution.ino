/*
  WiFiEsp example: WebClient

  This sketch connects to google website using an ESP8266 module to
  perform a simple web search.

  For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/

// http://projectsiot.xyz/IoTProjects/AirSoundPollution/asdisplay.php



#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=";
String rs = "\0";
int v = 0;

#define voltage_sensor A0
#define buzzer D6
#define rled D7
#define gled D8

unsigned int previous_status = 0;
unsigned int present_status = 0;
unsigned int vol = 0;
unsigned int alc = 0;
float voltage = 0.0;
float sound = 0.0;

String charging_status = "\0";
char state = 'U';

char state1;

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

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
  lcdstring(0,0," AIR  POLLUTION ");
  lcdstring(0,1,"MONITORING SYSTEM");
  delay(2000);

pinMode(buzzer,OUTPUT);
pinMode(gled,OUTPUT);
pinMode(rled,OUTPUT);
pinMode(voltage_sensor,INPUT);

  digitalWrite(rled, LOW);
  digitalWrite(gled, LOW);
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
   
  http.begin("http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=U&b=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
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



lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"      DONE      ");
  delay(2000);
lcd.clear();    
//Serial.println(F("PLEASE SHOW CARD "));
}

void loop()
{
 vol = analogRead(voltage_sensor);
delay(50);
Serial.print("sensor value = "); Serial.println(vol);

  v =  vol/10;
  
Serial.print("sensor % value = "); Serial.println(v);

if(vol>550)
{
  Serial.println("Air Pollution");
  state='Y';
  lcdstring(0,0,"Air : High    ");
 beep ();
 msg = a + "AIR%20POLLUTION%20DETECTED%20FOR%20TS08EW3500%20CHALLAN%20AMOUNT%20IS:200%20POLLUTION%20IS%20"+String(v);
Serial.println(msg);
sendsms ();
  delay(4000);
}
else
{
  lcdstring(0,0,"Air : Normal    ");
  state='N';
  vol = analogRead(voltage_sensor);
  delay(50);
}
     rs = r + state + "&b=" + String(v);

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
