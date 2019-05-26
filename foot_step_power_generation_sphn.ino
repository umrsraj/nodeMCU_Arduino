
/*
 * heart patient monitoring system
 *  * hotspot name : project12
 * hotspot possword : project123456
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>


LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

// WiFi parameters to be configured
//const char* ssid = "project12"; // Hoofdlettergevoelig
//const char* password = "project123456"; // Hoofdlettergevoelig

const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig


  String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8186008051&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/FootStepPower/footstep.php?a=";
String rs = "\0";

#define solPin A0
#define relay D6

int sol = 0;

float s = 0.0;

String sta = "\0";

void showprojectname ()
{
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FOOT STEP POWER");
    lcd.setCursor(0,1);
    lcd.print("GENERATION S/M");
  delay(2000);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  lcd.begin(16,2);

 pinMode(A0,INPUT);
 pinMode(relay,OUTPUT);
 
 
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

Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/FootStepPower/footstep.php?a=U&b=86&c=L");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/FootStepPower/footstep.php?a=U&b=86&c=L");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

}

void loop() {

sol = analogRead (solPin);
delay (50);
Serial.println("sol = " +String(sol));

 s = sol * (5.00/1023.00)*5;


lcd.clear();
lcd.setCursor(0,0);
lcd.print("V: "+String(s));
delay(300);

if (s > 6)
{
  Serial.println("charging status --  on");
  sta ="A";
  digitalWrite(relay,HIGH);
lcd.setCursor(0,1);
lcd.print("CHARGING - ON");
  delay(200);
}
else 
{
    Serial.println("charging status -- off");
  sta ="B";
  digitalWrite(relay,LOW);
lcd.setCursor(0,1);
lcd.print("CHARGING - OFF");
  delay(200);
}

rs = r + sta +"&b="+String(s);
send2server ();

}// loop

void send2server ()
{
Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=U&b=Y");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  //http.begin("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=U&b=Y");
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
Serial.println("sending welcome message............");
 
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
//   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8186008051&from=MYDREM&message="); 
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
