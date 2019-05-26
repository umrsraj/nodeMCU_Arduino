
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>
#include <stdio.h>


// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/RoboticCar/storedata.php?a=";
String rs = "\0";
//char read_msg[200] ;
String read_msg = "\0";
int v = 0;
int count = 0;
char msg1[200] = "" ;
char msg2[200] = "" ;

void lcdstring (unsigned int a, unsigned int b, String data);


LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  
  
  Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
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
   
  http.begin("http://projectsiot.xyz/IoTProjects/RoboticCar/storedata.php?a=U");

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

if (Serial.available() !=0)
{
  count = 0;
  
 while(Serial.available()!=0)
   {
  //  read_msg[count] = char(Serial.read());
    read_msg = Serial.readString();
    count ++;
    delay(5);
   }
  Serial.print("read_msg is = "); Serial.println(read_msg);
}
}//loop
