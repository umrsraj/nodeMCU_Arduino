
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/MovableRailway/pfupload.php?a=";
String rs = "\0";

int inir = 0;
int L1 = 0;
int L2 = 0;
int L3 = 0;

int in=0,out=0,tot=0;

unsigned int previous_status = 0;
unsigned int present_status = 0;
unsigned int ir1 = 0;
unsigned int flag = 0;

#define ir1sensor A0
#define ir2 D6
#define m11 D7 
#define m12 10
#define buzzer 1

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);


void lcdstring (unsigned int a, unsigned int b, String data);


void forward ()
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(50);
}
void backward ()
{
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  delay(50);
}
void stop_motor ()
{
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  delay(50); 
}

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
  Serial.println("power up");
  
lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("   WELCOME TO   ");
lcd.setCursor (0,1);
lcd.print ("AUTOMATIC MOVABLE");
delay (1500);

lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("RAILWAY PLATFORM");
lcd.setCursor (0,1);
lcd.print ("    WITH IoT    ");
delay(2000);

pinMode(ir1sensor,INPUT);
pinMode(ir2,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);


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
   
  http.begin("http://projectsiot.xyz/IoTProjects/MovableRailway/pfupload.php?a=U&b=0");

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

delay(200);

}

void loop()
{

 
ir1 = analogRead(ir1sensor);
delay(5);
Serial.print("ir1 value = "); Serial.println(ir1);

if ((ir1 > 600)&&(flag == 0))
{
  flag = 1;

 lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("PLATFOR  OPENING");
lcd.setCursor (0,1);
lcd.print ("*****************");
beep ();

  rs = r + 'Y' ;
 Serial.println(rs);
        send2server ();

forward ();
delay(2000);
stop_motor ();
delay(600);

 lcd.clear ();
lcd.setCursor (0,0);
lcd.print (" PLATFOR OPENED ");
lcd.setCursor (0,1);
lcd.print ("*****************");
delay (500);
}
else if ((digitalRead(ir2)==HIGH)&&(flag==1))
{
flag = 0;

 lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("PLATFOR  CLOSING ");
lcd.setCursor (0,1);
lcd.print ("*****************");
beep ();
  rs = r + 'N' ;
 Serial.println(rs);
        send2server ();

backward ();
delay(2000);
stop_motor ();
delay(600);

 lcd.clear ();
lcd.setCursor (0,0);
lcd.print (" PLATFOR CLOSED ");
lcd.setCursor (0,1);
lcd.print ("*****************");
delay (500);
  
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
