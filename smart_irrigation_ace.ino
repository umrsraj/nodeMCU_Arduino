/*
 * heart patient monitoring system
 *  * hotspot name : project12
 * hotspot possword : project123456
 */
 
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
#include <stdlib.h>
#include <String.h>

#define button1 18
#define button2 19
#define button3 22
#define button4 23

int p = 0;

#define soilPin 34
#define pir 35
#define buzzer 14
#define relay 12

LiquidCrystal lcd (15,2,4,16,17,5);

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

 String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8008633011&from=MYDREM&message=";
String msg = "\0";

int flags = 0;
char pass[5] = "\0";
char pass1[5] = "1234";
char pass2[5] = "4321";
 
int i = 0;

String hbvalue = "\0";
String S = "N";
String M = "N";
float temp1=0.0;
String gas1 = "\0";


int soil = 0;
int flag = 0;

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
    lcd.print("SMART IRRIGATION S/M");
    lcd.setCursor(0,1);
    lcd.print("....................");
  delay(2500);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  lcd.begin(16,2);

 pinMode(soilPin,INPUT);
pinMode(pir,INPUT);
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

soil = analogRead(soilPin);
Serial.println("soil="+String(soil));
Serial.print("pir = "); Serial.println(digitalRead(pir));
  
  lcd.clear ();
  lcdstring (0,0,"PLEASE ENTR PSWD");
  lcdstring (0,1,"****************");
  delay(2500);
 
  lcd.clear ();
  lcdstring (0,0,"    PASSWORD    ");

Serial.println("in password while loop");

while(i<4)
{
  soil = analogRead(soilPin);
Serial.println("soil="+String(soil));
Serial.print("pir = "); Serial.println(digitalRead(pir));

 if (digitalRead(button1) == HIGH)
  {
      Serial.println("BUTTON --1");
    pass[i]='1';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(100);
    while(digitalRead(button1)==HIGH);
  }
  else if (digitalRead(button2) == HIGH)
  {
      Serial.println("BUTTON --2");
    pass[i]='2';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(100);
    while(digitalRead(button2)==HIGH);
  }
   else if (digitalRead(button3) == HIGH)
  {
      Serial.println("BUTTON --3");
    pass[i]='3';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(100);
    while(digitalRead(button3)==HIGH);
  }
  else if (digitalRead(button4) == HIGH)
  {
      Serial.println("BUTTON --4");
    pass[i]='4';
    lcd.setCursor(i,1);
    lcd.print('4');
    i++;
    delay(100);
    while(digitalRead(button4)==HIGH);
  } 

 if(soil<550)
{
  M = "N";
  S = "Y";
Serial.println("******soil alert *********");
  lcd.clear();
  lcd.setCursor(0,0);
    lcd.print("SOIL  WET      ");
    lcd.setCursor(0,1);
    lcd.print("MOTOR - OFF");
    digitalWrite(relay,LOW);
delay(300);
    beep ();
    gas1 = 'H';
    
    if (flags == 1)
    {
      flags = 0;
    msg = a + "SOIL%20WET%0AMOTOR%20OFF";
send2server ();
    }
//rs = r + String(temp1)+"&b="+S+"&c="+M;
//send2server ();
delay(2000);

}
else
{
   lcd.clear();
  lcd.setCursor(0,0);
    lcd.print("SOIL  DRY      ");
    lcd.setCursor(0,1);
    lcd.print("MOTOR - ON  ");
    delay(200);
    digitalWrite(relay,HIGH);
    if (flags == 0)
    {
      flags = 1;
    msg = a + "SOIL%20DRY%0AMOTOR%20ON";
send2server ();
    }
delay(300);
}

p = analogRead(pir);
Serial.println("pir = "+String(p));

 if ((p > 1500)&&(flag==1))
{
  M = "N";
  S = "Y";
Serial.println("****** pir alert *********");
  lcd.clear();
  lcd.setCursor(0,0);
    lcd.print("PIR DETECTED     ");
    lcd.setCursor(0,1);
    lcd.print("SENDING SMS          ");
delay(300);
    beep ();
    gas1 = 'H';
    
msg = a + "PIR%20DETECTED%20PLEASE%20CHECK";
send2server ();
//rs = r + String(temp1)+"&b="+S+"&c="+M;
//send2server ();
delay(2000);
}
}
pass[4] = '\0';
Serial.print(F("enterred password = ")); Serial.println(pass);
i = 0;

  if(strcmp(pass,pass1)==0)  
  {    
    Serial.println("pasworddd  matched.....");
  lcdstring (0,0,"PASSWORD MATCHED     ");
  lcdstring (0,1,"                       ");
  delay(2000);
  flag = 1;
  lcdstring (0,0,"PIR ACTIVATED");
  lcdstring (0,1,"                   ");
  delay(2000);
   
  }
  else    if(strcmp(pass,pass2)==0)  
  {    
    Serial.println("pasworddd  matched222.....");
  lcdstring (0,0,"PASSWORD MATCHED     ");
  lcdstring (0,1,"                         ");
  delay(2000);
 flag = 0;
  lcdstring (0,0,"PIR DE-ACTIVATED");
  lcdstring (0,1,"                      ");
  delay(2000);

  }
  else
  {
    Serial.println("wrong pasworddd");
    beep ();
 
  
  lcdstring (0,0,"WRONG PASSWORD      ");
  lcdstring (0,1,"TRY AGAIN             ");
  delay(2000);    
}

 
}// loop

void send2server ()
{
Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  //http.begin("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=U&b=Y");
http.begin(msg);

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
