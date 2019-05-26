
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>


// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9059966082&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/Drowsy/upload.php?a=";
String rs = "\0";
int v = 0;
int count = 0;
int i = 0;


LiquidCrystal lcd(D0,D1,D2,D3,D4,D5);

const int alc    = A0;

#define ir  D6
#define relay D7
#define buzzer D8


String A = "N";
String D = "N";
int flag1 = 0;
int flag2 = 0;

void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void setup()
{
  
  pinMode(ir, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer,OUTPUT);
pinMode(alc,INPUT);

  
    Serial.begin(9600);
    Serial.println("WELCOME");

        lcd.begin(16, 2);
  

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("REAL TIME DROWSINESS");

          lcd.setCursor(0,1);
          lcd.print("DETECTION");
          delay(1500);

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



  rs=r+"U"+"&b="+D;
  send2server();
lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"      DONE      ");
  delay(2000);
          
          lcd.clear();

          lcd.setCursor(0,0);
          lcd.print("A:");
          lcd.setCursor(8,0);
          lcd.print("D:");
          lcd.setCursor(3,0);
          lcd.print(A);
          lcd.setCursor(11,0);
          lcd.print(D);
}

void loop()
{
  
  int alc_sen = analogRead(A0);
  Serial.print("ALCOHOL:");
  Serial.print("\t");
  Serial.println(alc_sen);
 // lcd.setCursor(3,0);
 // lcd.print(alc_sen);


A = "N";
D = "N";
//EYE BLINK SENSOR FOR DROWSY DETECTION---------------
  if(digitalRead(ir)==1)
  {
  i++;
 delay(1000);
  }
  if(digitalRead(ir)==0)
  {
  if(i>=1)
  {
    i--;
    delay(2000);
    }
  }
  count=i;
  Serial.print("count=");  Serial.println(count);
  
 //---------------6---------DROWSY ALERT-------
  if(count>2) //drowsy detected
  {
    //count = 0;
    Serial.println("dowsy ness detected");
D = "Y";
    count = 3;
    i = count;
digitalWrite(relay,LOW);
delay(300);
   lcd.clear ();
   lcdstring(0,0,"DRIVER DROWSY   ") ;
   lcdstring(0,1,"PLEASE CHECK     ") ;
   beep ();

 if (flag2 == 0)
      {
        flag2 = 1;
        msg = a + "DRIVER%20DROWSY%20ALERT";
        sendsms();
      }
   
     rs=r+A+"&b="+D;
  send2server();
  
   delay (5000);
 }
else if(alc_sen>1000)
  { 
   digitalWrite(relay,0);          
     
   lcd.clear ();
   lcdstring(0,0,"ALCOHOL ALERT     ") ;
   lcdstring(0,1,"PLEASE CHECK     ") ;          
      Serial.println("ALERT! ALCOHOL DETECTED");
      beep ();
A = "Y";

  rs=r+A+"&b="+D;
  send2server();
  
      if (flag1 == 0)
      {
        flag1 = 1;
        msg = a + "DRIVER%20ALCOHOL%20ALERT";
        sendsms();
      }
       delay(5000);
       }
else{
  digitalWrite(relay,1);
  
          lcd.clear();

          lcd.setCursor(0,0);
          lcd.print("A:");
          lcd.setCursor(8,0);
          lcd.print("D:");
          lcd.setCursor(3,0);
          lcd.print(A);
          lcd.setCursor(11,0);
          lcd.print(D);
  flag1=0;
  flag2=0;
  rs=r+A+"&b="+D;
  send2server();
}
}

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
