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
String r = "http://projectsiot.xyz/IoTProjects/DamGate/damupload.php?a=";
String rs = "\0";
int v = 0;


#define LEV1 D6
#define LEV2 D7
#define LEV3 1

#define MTP D8
#define MTN 10
#define buzzer 3

unsigned int  lev1, lev2, lev3;
String lev,gate;
int flag = 0;

void beep()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}


//================================================================================ setup
void setup() {
  Serial.begin(9600);
lcd.begin(16, 2);
  
  pinMode(buzzer, OUTPUT);
  pinMode(MTP, OUTPUT);
  pinMode(MTN, OUTPUT);
  pinMode(LEV1, INPUT);
  pinMode(LEV2, INPUT);
  pinMode(LEV3, INPUT);
  

  Serial.println("IOT BASED DAM GATE CONTROL SYSTEM \n");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IOT BSD DAM-GATE");
  lcd.setCursor(0, 1);
  lcd.print(" CONTROL SYSTEM ");
  delay(2000);

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

lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"  PLEASE WAIT  ");
  delay(2000);
  Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=U&b=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/DamGate/damupload.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //C connection
 
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
    http.end(); //C connection
 
delay(500);
}
*/


lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"      DONE      ");
  delay(2000);
lcd.clear();    
Serial.println(F("PLEASE SHOW CARD "));

 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("L1= ");
  lcd.setCursor(5, 0);
  lcd.print("0");
  lcd.setCursor(9, 0);
  lcd.print("L2= ");
  lcd.setCursor(13, 0);
  lcd.print("0");

  lcd.setCursor(0, 1);
  lcd.print("L3= ");
  lcd.setCursor(5, 1);
  lcd.print("0");
  lcd.setCursor(9, 1);
  lcd.print("GA= ");
  lcd.setCursor(13, 1);
  lcd.print("0");
  delay(200);

}


// ====================================================================== loop
void loop() {


  lev1 = digitalRead(LEV1);
  Serial.println(lev1);

  lev2 = digitalRead(LEV2);
  Serial.println(lev2);

  lev3 = digitalRead(LEV3);
  Serial.println(lev3);



  //IF ALL LEVEL FULL--------DAM FULL-----
  if ((lev1 == LOW) && (lev2 == LOW) && (lev3 == LOW))
  { 
   
    lev = '3';
    gate = 'O';

    lcd.setCursor(5, 0);
    lcd.print("1");
    lcd.setCursor(13, 0);
    lcd.print("1");
    lcd.setCursor(5, 1);
    lcd.print("1");

    beep();
    
    if (flag == 1)
    {
      //lcd.setCursor(13, 1);
     // lcd.print("1");
      flag = 0;
      digitalWrite(MTP, HIGH);
      digitalWrite(MTN, LOW);
      delay(4000);
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, LOW);
      delay(100);
      lcd.setCursor(13, 1);
      lcd.print(gate);
    }

  }  //DAM GATE FULL


  //if DAM GATE IS EMPTY
  if ((lev1 == HIGH) && (lev2 == HIGH) && (lev3 == HIGH))
  { 
    lev = '0';
    gate = 'C';
    lcd.setCursor(5, 0);
    lcd.print("0");
    lcd.setCursor(13, 0);
    lcd.print("0");
    lcd.setCursor(5, 1);
    lcd.print("0");

   
    if (flag == 0)
    {
      beep();
   //   lcd.setCursor(13, 1);
     // lcd.print("1");
      flag = 1;
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, HIGH);
      delay(4000);
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, LOW);
      delay(100);
      lcd.setCursor(13, 1);
      lcd.print(gate);
    }


  }  //DAM GATE EMPTY



  //1ST LEVEL DETECT
  if ((lev1 == LOW) && (lev2 == HIGH) && (lev3 == HIGH))
  {
    lev = '1';
    gate = 'C';
    lcd.setCursor(5, 0);
    lcd.print("1");
    lcd.setCursor(13, 0);
    lcd.print("0");
    lcd.setCursor(5, 1);
    lcd.print("0");
    lcd.setCursor(13, 1);
    lcd.print(gate);
    if (flag == 0)
    {
      beep();
   //   lcd.setCursor(13, 1);
     // lcd.print("1");
      flag = 1;
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, HIGH);
      delay(4000);
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, LOW);
      delay(100);
      lcd.setCursor(13, 1);
      lcd.print(gate);
    }


  }  //DAM GATE AT LEVEL-1


  //2ND LEVEL DETECT
  if ((lev1 == LOW) && (lev2 == LOW) && (lev3 == HIGH))
  {
    lev = '2';
    gate = 'C';
    lcd.setCursor(5, 0);
    lcd.print("1");
    lcd.setCursor(13, 0);
    lcd.print("1");
    lcd.setCursor(5, 1);
    lcd.print("0");
    lcd.setCursor(13, 1);
    lcd.print(gate);
    if (flag == 0)
    {
      beep();
   //   lcd.setCursor(13, 1);
     // lcd.print("1");
      flag = 1;
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, HIGH);
      delay(4000);
      digitalWrite(MTP, LOW);
      digitalWrite(MTN, LOW);
      delay(100);
      lcd.setCursor(13, 1);
      lcd.print(gate);
    }


  }  //DAM GATE AT LEVEL-1

   rs = r+lev+"&b="+String(gate);

        Serial.println(rs);
       send2server ();

}//loop
  void send2server ()
{
Serial.print("rs = "); Serial.println(rs);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(rs);b 2

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
