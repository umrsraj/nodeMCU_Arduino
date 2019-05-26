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
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

  String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/BloodStore/upload.php?a=";
String rs = "\0";

char b1 = 'N';
char b2 = 'N';

#define buzzer D8
#define temp A0
#define blood1 D6
#define blood2 D7
 
String hbvalue = "\0";

float temp1=0.0;
String gas1 = "\0";

String otp[11] = {"62","72","71","75","97","79","92","79","95","83","99"} ;
unsigned int no = 0;
unsigned hb = 0;
unsigned temp2 = 0;

void beep()
{
   digitalWrite(buzzer, HIGH); 
   delay(1500);
    digitalWrite(buzzer, LOW); 
    delay(100);
}
void showprojectname ()
{
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BLOOD BANK       ");
    lcd.setCursor(0,1);
    lcd.print("MONITORING SYSTEM");
  delay(2000);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  lcd.begin(16,2);

 pinMode(temp,INPUT);
pinMode(buzzer,OUTPUT);
 pinMode(blood1,INPUT);
 pinMode(blood2,INPUT);
 
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

Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/HealthCare/healthupload.php?a=U&b=86&c=L");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/BloodStore/upload.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

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

 hbvalue = "\0";
 no = random(11);

if (digitalRead(blood1)==HIGH)
{
  b1 = 'N';
}
else
{
  b1 = 'Y';
}

if (digitalRead(blood2)==HIGH)
{
  b2 = 'N';
}
else
{
  b2 = 'Y';
}

  
temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 

  temp1 = temp1 - 30;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);
//Serial.print("button = "); Serial.println(digitalRead(button));

if(temp1>50)
{
Serial.println("****** temperature alert *********");
lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURE ALERT");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
    beep ();
msg = a + "TEMPERATURE%20ALERT%20PLEASE%20CHECK";
// sendsms ();
send2server ();
delay(5000);

}
else if ((b1=='N')&&(b2=='N'))
{
Serial.println("****** blood 1 not available *********");
  lcd.clear();
  lcd.setCursor(0,0);
    lcd.print("BLOOD BANK      ");
    lcd.setCursor(0,1);
    lcd.print("OUT OF STACK     ");
    beep ();
 msg = a + "BLOOD%20OUT%20OF%20STACK%0APLEASE%20CHECK";
// sendsms ();   
    
    
msg = a + "GAS%20ALERT%20PLEASE%20CHECK";
// sendsms ();
send2server ();
delay(5000);
}
else {
  lcd.clear ();
  lcdstring(0,0,"T: "+String(temp1));
  lcdstring(0,1,"B1: "+String(b1));
  lcdstring(8,1,"B2: "+String(b2));
  
  send2server ();
  delay(300);
}

rs = r + String(temp1)+"&b="+String(hb)+"&c="+gas1;
send2server ();
}// loop

void send2server ()
{
Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=U&b=Y");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  //http.begin("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=U&b=Y");
http.begin(
rs = r + String(temp1)+"&b="+b1+"&c="+b2);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(100);
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
void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
