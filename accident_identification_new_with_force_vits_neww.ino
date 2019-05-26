/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal.h>
#include <ESP8266HTTPClient.h>
#include <String.h>

#define memsPin A0
#define heart D6
#define buzzer 10
#define button D7
#define force D8

int t = 0;
int flag = 0;

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9573761679&from=MYDREM&message=";
String msg = "\0";

String otp[11] = {"62","72","71","75","97","79","92","79","95","83","99"} ;
unsigned int no = 0;
unsigned hb = 0;

void beep()
{
   digitalWrite(buzzer, HIGH); 
   delay(1500);
    digitalWrite(buzzer, LOW); 
    delay(100);
}

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "89a77398b6c44c64bd8d928358c8edd2";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "project12";
char pass[] = "project123456";


float latitude = 0.0;
float longitude = 0.0;


int mems = 0;
WidgetMap myMap(V2);

BLYNK_WRITE(V1) {
// latitude = param[0].asFloat();
// longitude = param[1].asFloat();
GpsParam gps(param);
 Serial.print("Lat: ");
  Serial.println(gps.getLat(), 7);

  Serial.print("Lon: ");
  Serial.println(gps.getLon(), 7);

  // Print 2 decimal places for Alt, Speed
  Serial.print("Altitute: ");
  Serial.println(gps.getAltitude(), 2);

  Serial.print("Speed: ");
  Serial.println(gps.getSpeed(), 2);

  Serial.println();

// Serial.println("lat - "+String(latitude));
 //Serial.println("lon - "+String(longitude));
mems = analogRead(memsPin);
Serial.println("mems = "+String(mems));

Serial.println("forece="+String(digitalRead(force)));

if ((mems <450)||(digitalRead(force)==HIGH))
{
  
  Serial.println("accident occured.......");
 delay(200);

lcd.clear ();
lcdstring(0,0,"ACCIDENT OCCURED   ");
lcdstring(0,1,"AT               ");
delay(500);
//beep ();
delay(1500);
lcd.clear ();
lcdstring(0,0,"LAT:"+String(gps.getLat(),7));
lcdstring(0,1,"LNG:"+String(gps.getLon(),7));
delay(1500);

t = 0;
lcd.clear ();
lcdstring(0,0,"ARE YOU OK?   ");
lcdstring(0,1,"PRESS BUTTON    ");
flag = 0;
while (t < 30)
{
  int bt = digitalRead(button);
  t ++;
  Serial.println("t = "+String(t));
  Serial.println("button = "+String(bt));
  
  digitalWrite(buzzer,HIGH);
  if (bt == 0)
  {
    Serial.println("button pressed");
    flag = 1;
    break;
  }
  delay(500);
}
digitalWrite(buzzer,LOW);
if (flag==0)
{
   Blynk.notify("ACCIDENT OCCURED PLEASE CHECK \nAT\nLAT:"+String(gps.getLat(),7)+"\nLNG:"+String(gps.getLon(),7));
delay(1500);

 int index = 0;
  float lat = param[0].asFloat();
  float lon = param[1].asFloat() ;
  myMap.location(index, lat, lon, "ACCIDENT ALERT");
  delay(200);

lcd.clear ();
lcdstring(0,0,"ACCIDENT OCCURED   ");
lcdstring(0,1,"AT               ");
delay(500);
beep ();
delay(1000);
lcd.clear ();
lcdstring(0,0,"LAT:"+String(gps.getLat(),7));
lcdstring(0,1,"LNG:"+String(gps.getLon(),7));
delay(2500);
delay(2000);
msg = a +"ACCIDENT%20OCCURED%0AAT%0ALAT:%20"+String(gps.getLat(),7)+"%0ALNG:%20"+String(gps.getLon(),7);
sendsms ();
delay(2000);
}
}//mems
else
{
  lcd.clear();
     lcd.setCursor(0,0);
    lcd.print("MEMS:"+String(mems));
      lcd.setCursor(0,1);
    lcd.print("force="+String(digitalRead(force)));
    delay(300);
}
/*
else if (digitalRead(heart)==LOW)
{
  Serial.println("heart beat reading....");
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
 Serial.print("heart beat is = "); Serial.println(hb);

  if ((hb>95)||(hb<70))
  {
Serial.println("****** heart alert *********");

  Blynk.notify("HEART BEAT ALERT");delay(200);
    lcd.clear();
  lcd.print("HEART BEAT ALERT");
    lcd.setCursor(0,1);
    lcd.print("HB = ");
    lcd.setCursor(6,1);
    lcd.print(hb);
beep ();

msg = a + "HEART%20BEAT%20ALERT%20PLEASE%20CHECK%0AAT%0ALAT:%20"+String(gps.getLat(),7)+"%0ALNG:%20"+String(gps.getLon(),7);
 sendsms ();
delay(5000);
}
  else
  {
  lcd.clear();
  lcd.print("HEART BEAT NORMAL");
    lcd.setCursor(0,1);
    lcd.print("H BEAT = ");
    lcd.setCursor(10,1);
    lcd.print(hb);
  delay(2000);
  
  }
}//heart
*/

  
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  lcd.begin(16,2);

pinMode(buzzer,OUTPUT);
pinMode(button,INPUT);
pinMode(heart,INPUT);
pinMode(memsPin,INPUT);
pinMode(force,INPUT);
  lcd.clear ();
  lcdstring (0,0,"CONNECTING TO     ");
  lcdstring (0,1,"BLYNK SERVER      ");
  Blynk.begin(auth, ssid, pass);

  
  lcd.clear ();
  lcdstring (0,0," CONNECTED TO");
  lcdstring (0,1,"   SERVER      ");
  delay(2500);

  Blynk.notify("KIT STARTED");
  delay(200);
Serial.println("power up");

}

void loop()
{
  Blynk.run();
  

}//loop
void lcdstring (int a, int b, String data)
{
  lcd.setCursor (a,b);
  lcd.print(data);
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
