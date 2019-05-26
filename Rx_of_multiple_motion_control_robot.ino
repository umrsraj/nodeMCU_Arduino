#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <TinyGPS++.h>
#include <String.h>
#include <stdlib.h>

LiquidCrystal lcd (4,16,17,5,18,19);

TinyGPSPlus gps;

#define ss Serial

#define trigPin 15
#define echoPin 2
#define m1a 13
#define m1b 12
#define m2a 14
#define m2b 27
#define buzzer 21

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

long duration, distance,duration1,distance1;
String payload;


void forward ()
{
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  delay(50);
}
void backward ()
{
  digitalWrite(m1b,HIGH);
  digitalWrite(m1a,LOW);
  digitalWrite(m2b,HIGH);
  digitalWrite(m2a,LOW);
  delay(50);
}

void left ()
{
   digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  digitalWrite(m2b,LOW);
  digitalWrite(m2a,HIGH);
  delay(1000);
  stop_motor ();
}
void right ()
{

  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2b,HIGH);
  digitalWrite(m2a,LOW);
  delay(1000);
  stop_motor ();
}
void stop_motor ()
{
  digitalWrite(m1b,LOW);
  digitalWrite(m1a,LOW);
  digitalWrite(m2b,LOW);
  digitalWrite(m2a,LOW);
  delay(50);
}
void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  Serial.println("power up");


  pinMode(buzzer, OUTPUT);
  pinMode(m1a, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2b, OUTPUT);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);

stop_motor ();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MULTIPLE MOTION ");
  lcd.setCursor( 0, 1);
  lcd.print(" CONTROL SYSTEM ");
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" OF ROBOTIC CAR ");
  lcd.setCursor( 0, 1);
  lcd.print("   BSD ON IOT   ");
  delay(2000);

 Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("connecting to");
    lcd.setCursor( 2, 1);
    lcd.print(ssid);
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("connected to ");
  lcd.setCursor( 2, 1);
  lcd.print(ssid);
  // IP adres.
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Signaalsterkte.
  long rssi = WiFi.RSSI();
  Serial.print("Signaal sterkte (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");

}

void loop ()
{

 while (ss.available() > 0)
    if (gps.encode(ss.read()))
     // displayInfo();
     
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    //while(true);
  }


digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

 if(distance>220)
 {
  distance=220;
 }
 
Serial.print("distance--- "); Serial.println(distance);

if (distance < 30)
{
  
stop_motor ();
lcd.clear ();
lcd.setCursor (0,0);
lcd.println("OBSTACLE ALERT ");
lcd.setCursor (0,1);
lcd.println("Dsit:"+String(distance));
delay(2000);
    lcd.clear ();
    lcd.setCursor(0,0);
    lcd.print("LAT:"+String(gps.location.lat(),6));
    lcd.setCursor(0,1);
    lcd.print("LNG:"+String(gps.location.lng(),6));
    
//delay(500);
beep ();


delay(2000);
}
else
{
//====================================================
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
 
    HTTPClient http; //Declare an object of class HTTPClient
   http.begin("http://projectsiot.xyz/IoTProjects/RoboticCar/updatevalues.php"); //Specify request destination

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
     payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection

if((payload.indexOf("stop")!=(-1))||(payload.indexOf("5")!=(-1)))
 {
Serial.println("stop");
stop_motor ();  
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ROBOT>> STOP          ");
payload=="\0";
 }
 
else if((payload.indexOf("backward")!=(-1))||(payload.indexOf("back")!=(-1))||(payload.indexOf("2")!=(-1)))
 {
Serial.println("backward");
backward (); 
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ROBOT>> BACKWARD          ");
payload=="\0";
 }
else if((payload.indexOf("left")!=(-1))||(payload.indexOf("3")!=(-1)))
 {
Serial.println("left");
left (); 
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ROBOT>> LEFT          ");
payload=="\0";
 }
else if((payload.indexOf("right")!=(-1))||(payload.indexOf("4")!=(-1)))
 {
Serial.println("right");
right ();  
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ROBOT>> RIGHT          ");
payload=="\0";
 }
else if((payload.indexOf("forward")!=(-1))||(payload.indexOf("front")!=(-1))||(payload.indexOf("1")!=(-1)))
 {
Serial.println("forward");
forward ();
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ROBOT>> FORWARD          ");
payload=="\0";
 }

 }//if wifi connected
}//else of loop
//====================================================
}//loop
void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);

  //  delay(100);
  }
  else
  {
    Serial.print(F("INVALID"));
     lcd.clear ();
    lcd.setCursor(0,0);
    lcd.print("INVALID LOCATION");
    lcd.setCursor(0,0);
    lcd.print("");
    //delay(100);
  }

 
  Serial.println();
}
