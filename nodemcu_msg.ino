// d3 -  msg trig pin


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <LiquidCrystal.h>
#include <String.h>

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig
String a1 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9573116584&from=MYDREM&message=";
String a2 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8179999394&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/DrunkDrive/uploadstatus.php?a=";
String rs = "\0";
String obs = "\0";
String fir = "\0";
int alc;

//#define fire_sensor D1
//#define obstacle_sensor D0 

//#define m11 D2
//#define m12 D3
//#define m21 D4
//#define m22 D5

#define buzzer D2
#define pin D3

unsigned int obstacle = 0;
unsigned int fire = 0;
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
*/
void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}

void setup() {
  Serial.begin(9600);
  Serial.println("power up");
 
pinMode(pin,INPUT);
pinMode (buzzer,OUTPUT);

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


Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/HealthCare/healthupload.php?a=U&b=86&c=L");


if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/DrunkDrive/uploadstatus.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(5000);
}

}


void loop()
{

if (digitalRead(pin)==LOW)
{
  Serial.println("sms sending");

  msg = a1+"ACCIDENT%20OCCURRED%0AAT%0ALAT:17.307119%0ALNG:78.455241";rs = msg;
send2server();
  msg = a2+"ACCIDENT%20OCCURRED%0AAT%0ALAT:17.307119%0ALNG:78.455241";
rs = msg;
send2server();
  rs= "\0";
}
else if (digitalRead(D2)==HIGH)
{
  beep ();
}

} // LOOP

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
