
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>


#define m11 D0
#define m12 D1
#define m21 D2
#define m22 D3
#define m31 D4
#define m32 D5
#define m41 D6
#define m42 D7

#define ir A0
#define buzzer D8

unsigned int obstacle = 0;
char ch;

  String obs = "\0";  //obstacle detection alert
String mov = "\0";  //Robot Movement Alert-----
   

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String m1 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9848645851&from=MYDREM&message=";
String m2 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8074303938&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/FruitPickRobot/upload.php?a=";
String rs = "\0";

String box1 = "N";
String box2 = "N";

int flag1 = 0;
int flag2 = 0;
int ldr1 = 0;
int ldr2 = 0;



void lcdstring (unsigned int a, unsigned int b, String data);

void forward ()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  delay(10);
}

void backward ()
{
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m22, HIGH);
  digitalWrite(m21, LOW);
  delay(10);
}
void left ()
{
  digitalWrite(m12, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
  delay(10);
}

void right ()
{

  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  delay(10);
}
void stopp ()
{
  digitalWrite(m12, LOW);
  digitalWrite(m11, LOW);
  digitalWrite(m22, LOW);
  digitalWrite(m21, LOW);
  delay(10);
}

//-------------------hand control-----
void up(void)
{
  digitalWrite(m31, HIGH); 
  digitalWrite(m32, LOW);   
 // digitalWrite(m2a, HIGH); 
 // digitalWrite(m2b, LOW); 
  delay(1000);               
}

void down(void)
{
  digitalWrite(m31, LOW); 
  digitalWrite(m32, HIGH);   
//  digitalWrite(m2a, LOW); 
 // digitalWrite(m2b, HIGH); 
  delay(1000);               
}

void openm(void)
{
 // digitalWrite(m1a, HIGH); 
  //digitalWrite(m1b, LOW);   
  digitalWrite(m41, LOW); 
  digitalWrite(m42, HIGH); 
 delay(1000);               
}

void closem(void)
{
  //digitalWrite(m1a, LOW); 
  //digitalWrite(m1b, HIGH);   
  digitalWrite(m41, HIGH); 
  digitalWrite(m42, LOW); 
  delay(1000);               
}

void stop_motor(void)
{
  digitalWrite(m31, LOW); 
  digitalWrite(m32, LOW);   
  digitalWrite(m41, LOW); 
  digitalWrite(m42, LOW); 
  delay(1000);               
}
//------------------------------------

void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);

pinMode (m11,OUTPUT);
pinMode (m12,OUTPUT);
pinMode (m21,OUTPUT);
pinMode (m22,OUTPUT);

pinMode (m31,OUTPUT);
pinMode (m32,OUTPUT);
pinMode (m41,OUTPUT);
pinMode (m42,OUTPUT);

pinMode (ir,INPUT);
pinMode (buzzer,OUTPUT);


Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
beep ();
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

rs = r + "U&b=N";
send2server ();


}

void loop()
{


}// loop
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
 
delay(50);
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


