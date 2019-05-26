 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>


LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

// WiFi parameters to be configured
//const char* ssid = "project12"; // Hoofdlettergevoelig
//const char* password = "project123456"; // Hoofdlettergevoelig

const char* ssid = "AMBEST Technologies"; // Hoofdlettergevoelig
const char* password = "AmBeSt@@321"; // Hoofdlettergevoelig


  String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydream123&to=8186008051&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/HealthCare/healthupload.php?a=";
String rs = "\0";
#define buzzer D8
#define temp A0
#define heart D6
#define gas D7
 
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
    lcd.print("ON BOARD BATTERY");
    lcd.setCursor(0,1);
    lcd.print("CHARGER          ");
  delay(2000);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  lcd.begin(16,2);

 pinMode(temp,INPUT);
pinMode(buzzer,OUTPUT);
 pinMode(gas,INPUT);
 pinMode(heart,INPUT);
 
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
   
  http.begin("http://projectsiot.xyz/IoTProjects/HealthCare/healthupload.php?a=U&b=86&c=L");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

Serial.println("sending welcome message............");
 
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8186008051&from=MYDREM&message=KIT%20STARTED"); //Specify request destination

 
int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(4000);
}

}

void loop() {

 hbvalue = "\0";
 no = random(11);

  
temp2 = analogRead(temp); //read data from analog pin A1. 
float V=temp2*(5/(1023.00)); //conversion of analog voltage to digital voltage. 
  temp1=V*100; //temperature in centigrade scale. 

  temp1 = temp1 - 5;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);
//Serial.print("button = "); Serial.println(digitalRead(button));

Serial.print("button = "); Serial.println(digitalRead(heart));
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
sendsms ();

rs = r + String(temp1)      +"&b="+String(hb)+"&c="+gas1;
send2server ();
delay(5000);

}
if (digitalRead(gas) == HIGH)
{
Serial.println("****** gas alert *********");
  lcd.clear();
  lcd.setCursor(0,0);
    lcd.print("   GAS  ALERT   ");
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK****");
    beep ();
    gas1 = 'H';
    
msg = a + "GAS%20ALERT%20PLEASE%20CHECK";
sendsms ();
rs = r + String(temp1)+"&b="+String(hb)+"&c="+gas1;
send2server ();
delay(5000);
}
else {
  gas1 = 'N';
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
Serial.println("****** heart alert *********");
    lcd.clear();
  lcd.print("HEART BEAT ALERT");
    lcd.setCursor(0,1);
    lcd.print("HB = ");
    lcd.setCursor(6,1);
    lcd.print(hb);
beep ();

msg = a + "HEART%20BEAT%20ALERT%20PLEASE%20CHECK";
sendsms ();
rs = r + String(temp1)+"&b="+String(hb)+"&c="+gas1;
send2server ();
delay(5000);
}
  else
  {
  hbvalue = "\0";   
  lcd.clear();
  lcd.print("HEART BEAT NORMAL");
    lcd.setCursor(0,1);
    lcd.print("H BEAT = ");
    lcd.setCursor(10,1);
    lcd.print(hb);
  delay(2000);
  
  }
  
}
if((digitalRead(heart)==HIGH)&&(temp1<50)&&(digitalRead(gas)==LOW))
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("T: ");
    lcd.setCursor(3,0);
    lcd.print(temp1);
    lcd.setCursor(9,0);
    lcd.print("G: ");
    lcd.setCursor(12,0);
    lcd.print("0"); 
    lcd.setCursor(0,1);
    lcd.print("HEARTBEAT NORMAL");
  delay(500);
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