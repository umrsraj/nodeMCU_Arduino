#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
 

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);
 
// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig
 
const char* http_site = "http://sms.scubedigi.com/";
const int http_port = 80;


#define m11 D6
#define m12 D7
#define buzzer D8

unsigned int flag = 0;
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
        lcd.print("   WELCOME TO   ");
        lcd.setCursor( 0,1);
         lcd.print("EMPLOYEE MONITORING");
         delay(2000);

lcd.clear();
lcd.setCursor(0,0);
        lcd.print("   USING RFID   ");
        lcd.setCursor( 2,1);
         //lcd.print("----ON RFID-----");
         delay(1500);
  
Serial.println("state-------------2");



Serial.println("state-------------3");

 Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=U&b=Y");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=U&b=Y");

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
if (flag == 0)
{
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("EMPLOYEE1 MATCHED"); 
  
// digitalWrite(rled,LOW);
// digitalWrite(gled,HIGH);

  input[10]='\0';
  
Serial.print("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=A&b=Y");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
  
   http.begin("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=A&b=Y");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

Serial.println("sending message---management-----");

 //Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient

  http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=EMPLOYEE1%20ENTRY");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

Serial.println("sending message--- parent-1 -----");

 //Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient

  http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9642008668&from=MYDREM&message=EMPLOYEE1%20ENTRY");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("EMPLOYEE1 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("**** ENTRY *****");
      delay(500);

      forward ();
      delay(1500);
      stop_motor ();
      delay(2000);
      backward ();
      delay(1500);
      stop_motor();

      // digitalWrite(rled,LOW);
      // digitalWrite(gled,LOW);
flag = 1;
}//IF FLAG == 0    

else if (flag == 1)
{

lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("EMPLOYEE1 MATCHED"); 
  
// digitalWrite(rled,LOW);
// digitalWrite(gled,HIGH);

  input[10]='\0';
  
Serial.print("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=A&b=Y");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

   http.begin("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=A&b=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
Serial.println("sending message---management-----");

 //Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient

  http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=EMPLOYEE1%20LEAVING");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

Serial.println("sending message--- parent-1 -----");

 //Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient

  http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9642008668&from=MYDREM&message=EMPLOYEE1%20LEAVING");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("EMPLOYEE1 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("**** EXIT *****");
      delay(500);

      forward ();
      delay(1500);
      stop_motor ();
      delay(2000);
      backward ();
      delay(1500);
      stop_motor();

      // digitalWrite(rled,LOW);
      // digitalWrite(gled,LOW);
flag = 0;
}//IF FLAG == 1

} // 1st card
else if (input[10]=='A')
{
if (flag1 == 0)
{
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("EMPLOYEE2 MATCHED"); 
  
// digitalWrite(rled,LOW);
// digitalWrite(gled,HIGH);

  input[10]='\0';
  
Serial.print("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=A&b=Y");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

   http.begin("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=B&b=Y");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
Serial.println("sending message---management-----");

 //Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient

  http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=EMPLOYEE2%20ENTRY");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

Serial.println("sending message--- parent-1 -----");

 //Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient

  http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8886845033&from=MYDREM&message=EMPLOYEE2%20ENTRY");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("EMPLOYEE2 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("**** ENTRY *****");
      delay(500);

      forward ();
      delay(1500);
      stop_motor ();
      delay(2000);
      backward ();
      delay(1500);
      stop_motor();

      // digitalWrite(rled,LOW);
      // digitalWrite(gled,LOW);
flag1 = 1;
}//IF FLAG == 0    

else if (flag1 == 1)
{

lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("EMPLOYEE2 MATCHED"); 
  
// digitalWrite(rled,LOW);
// digitalWrite(gled,HIGH);

  input[10]='\0';
  
Serial.print("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=A&b=Y");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

   http.begin("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=B&b=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
Serial.println("sending message---management-----");

 //Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient

  http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=EMPLOYEE2%20LEAVING");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

Serial.println("sending message--- parent-2 -----");

 //Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient

  http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8886845033&from=MYDREM&message=EMPLOYEE2%20LEAVING");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("EMPLOYEE2 MATCHED");  
    lcd.setCursor(0,1);
    lcd.print("**** EXIT *****");
      delay(500);

      forward ();
      delay(1500);
      stop_motor ();
      delay(2000);
      backward ();
      delay(1500);
      stop_motor();

      // digitalWrite(rled,LOW);
      // digitalWrite(gled,LOW);
flag1 = 0;
}//IF FLAG1 == 1

} // 2nd card

else
{
  // digitalWrite(gled,LOW);
//// digitalWrite(rled,HIGH);
   lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  INVALID CARD  ");
    delay(1600);
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK***");
    beep  ();
    delay(700);
    
 Serial.println("http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=H&b=0&c=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

   http.begin("http://projectsiot.xyz/IoTProjects/SchoolChildSecurity/childupdate.php?a=H&b=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
    

}
   } 

  /*
Serial.println("loop Started");
String raj = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF";
//raj = raj + String(r) ;
  Serial.println(raj);
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9063779181&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

   http.begin(raj);
    
    int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
  } else {
    Serial.println("Error in WiFi connection");   
  }
  delay(3000); //Send a request every 30 seconds

r = r + 10;
  Serial.print("r = "); Serial.println(r);
raj = "\n";
*/
}
