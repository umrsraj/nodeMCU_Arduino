
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
String r = "http://projectsiot.xyz/IoTProjects/NoticeBoard/uploadnotice.php?a=";
String rs = "\0";
char read_msg[100] ;
int v = 0;
int count = 0;
char msg1[100] = "" ;
char msg2[100] = "" ;

void lcdstring (unsigned int a, unsigned int b, String data);


LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  lcd.begin(16, 1);
  
  lcd.clear();
  lcdstring(0,0," E-NOTICE BOARD ");
  
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
/*
lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  delay(2000);
  Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=U&b=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/NoticeBoard/uploadnotice.php?a=U");

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
  lcdstring(0,0,"SERVER INT. DONE");
  delay(2000);
lcd.clear();    

Serial.println(F("PLEASE SHOW CARD "));



}

void loop() {
  // put your main code here, to run repeatedly:

if (Serial.available() !=0)
{
  count = 0;
 // strcpy(msg1,NULL);
 while(Serial.available()!=0)
   {
    read_msg[count] = char(Serial.read());
    count ++;
    delay(5);
    
   }
   //read_msg[count]='\n';
  Serial.print("read_msg is = "); Serial.println(read_msg);
  Serial.print("read_msg length = "); Serial.println(strlen(read_msg));
//msg1 = "                                                                                                               ";
strcpy(msg1,"                                ");
  strcpy(msg1,read_msg);
for(int i = 0; i <= strlen(read_msg); i++)
    {
      if(read_msg[i] == ' ')  
    {
        read_msg[i] = '$';
    }
  }
  strcpy(msg2,read_msg); 
  Serial.print("msg2 = "); Serial.println(msg2);
  Serial.print("msg1 = "); Serial.println(msg1);

  Serial.print("A = "); Serial.println(r+msg2);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin(r+msg2);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500); 
}
strcpy(msg2,"                                ");
}  // if serial available

lcd.clear ();
lcd.setCursor(0,0);
lcd.print(msg1);
for (int positionCounter = 2; positionCounter < 16; positionCounter++) 
{
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(400);   
  }
  
}// loop

void lcdstring (unsigned int a, unsigned int b, String data)
{
  // lcd.clear();
  lcd.setCursor(a, b);
  lcd.print(data);
}
