#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
 

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);
 
// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

  String a1 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7794035247&from=MYDREM&message=";
  String a2 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9493007482&from=MYDREM&message=";
String msg = "\0";

String rs = "\0";
String r = "http://projectsiot.xyz/IoTProjects/ExamLeakage/upload.php?a=";
 
const char* http_site = "http://sms.scubedigi.com/";
const int http_port = 80;

char paper1 = 'A';
char paper2 = 'A';

#define m11 D6
#define m12 D7
#define buzzer D8

unsigned int flag2 = 0;
unsigned int flag1 = 0;

int count1 = 0;                                          // count = 0
char input[12];

void forward ()
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(50);  
}
void backward ()
{
  digitalWrite(m12,HIGH);
  digitalWrite(m11,LOW);
  delay(50);  
}
void stop_motor ()
{
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  delay(50);  
}

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}
 

 
void setup(void) { 
  Serial.begin(9600);
  lcd.begin(16,2);

pinMode(buzzer,OUTPUT);
 pinMode(m11,OUTPUT);
 pinMode(m12,OUTPUT); 
 //pinMode(gled,OUTPUT);
 //pinMode(rled,OUTPUT);
 
  
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
lcd.setCursor(0,0);
        lcd.print("PAPER LEAKAGE");
        lcd.setCursor( 0,1);
         lcd.print("PROTECTION S/M");
         delay(2000);

  
 Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=U&b=Y");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin("http://projectsiot.xyz/IoTProjects/ExamLeakage/upload.php?a=U&b=Y");

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
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=KIT%20STARTED"); //Specify request destination

  //http.begin("http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=U&b=0&c=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
*/
}
 
void loop() {


//Serial.println("state----------loop");

lcd.setCursor(0,0);
    lcd.print("plz show card         ");
lcd.setCursor(0,1);
    lcd.print("                      ");

if(Serial.available())
   {
      count1 = 0;
      while(Serial.available() && count1 < 12)          // Read 12 characters and store them in input array
      {
         input[count1] = Serial.read();
         count1++;
         delay(5);
      }//WHILE
//

 Serial.println(input);                           // Print RFID tag number 
   Serial.print("input[10] is "); Serial.println(input[10]);
//////////////////////////////
if (input[10]=='C')
{
  input[10]='\0';

if (flag1 == 0)
{
  flag1 ++;
  paper1 = 'A';
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("PAPER-1 AT          ");
    lcd.setCursor(0,1);
    lcd.print("LOCATION - 1       "); 
  delay(2000);
}//IF FLAG == 0 
else if (flag1 == 1)
{
  flag1 ++;
  paper1 = 'B';
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("PAPER-1 AT          ");
    lcd.setCursor(0,1);
    lcd.print("LOCATION - 2       "); 
  delay(2000);
}//FLAG == 1 
else if (flag1 == 2)
{
  flag1 ++;
  paper1 = 'C';
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("PAPER-1 AT          ");
    lcd.setCursor(0,1);
    lcd.print("LOCATION - 3       "); 
  delay(1500);

     rs = a1+ "PAPER-1%20REACHED%20TO%20LOCATION-3";
     send2server ();
     rs = a2+ "PAPER-1%20REACHED%20TO%20LOCATION-3";
     send2server ();

forward ();
delay(4000);
stop_motor ();
delay(3000);
backward ();
delay(4000);
stop_motor();
  
}//FLAG == 2 
/*
else if (flag1 == 3)
{
  flag1 ++;
  flag1 = 0;
  paper1 = 'D';
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("PAPER-1 AT          ");
    lcd.setCursor(0,1);
    lcd.print("EXAM CENTER       "); 
  delay(2000);
}//FLAG == 3
*/
}//CARD-1
else if (input[10]=='6')
{
  input[10]='\0';

if (flag2 == 0)
{
  flag2 ++;
  paper2 = 'A';
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("PAPER-2 AT          ");
    lcd.setCursor(0,1);
    lcd.print("LOCATION - 1       "); 
  delay(2000);
}//IF FLAG == 0 
else if (flag2 == 1)
{
  flag2 ++;
  paper2 = 'B';
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("PAPER-2 AT          ");
    lcd.setCursor(0,1);
    lcd.print("LOCATION - 2       "); 
  delay(2000);
}//FLAG == 1 
else if (flag2 == 2)
{
  flag2 ++;
  paper2 = 'C';
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("PAPER-2 AT          ");
    lcd.setCursor(0,1);
    lcd.print("LOCATION - 3       "); 
  delay(1500);

     rs = a1+ "PAPER-2%20REACHED%20TO%20LOCATION-3";
     send2server ();
     rs = a2+ "PAPER-2%20REACHED%20TO%20LOCATION-3";
     send2server ();
  
  forward ();
delay(4000);
stop_motor ();
delay(3000);
backward ();
delay(4000);
stop_motor();


}//FLAG == 2 
/*
else if (flag2 == 3)
{
  flag2 ++;
  flag2 = 0;
  paper2 = 'D';
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("PAPER-2 AT          ");
    lcd.setCursor(0,1);
    lcd.print("EXAM CENTER       "); 
  delay(2000);
}//FLAG == 3
*/
}//CARD-2
else
{
  // digitalWrite(gled,LOW);
//// digitalWrite(rled,HIGH);
   lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  INVALID CARD  ");
   
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK***");
    beep  ();
     delay(1600);

     rs = a1+ "UNAUTHORIZED%20ACCESS%0APLEASE%20CHECK";
     send2server ();
     rs = a2+ "UNAUTHORIZED%20ACCESS%0APLEASE%20CHECK";
     send2server ();
     
     
    
    

}
   } 
rs = r + paper1 + "&b=" + paper2;
send2server ();

}//loop
void send2server ()
{
   Serial.print("rs= ");
   Serial.println(rs);
   
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
