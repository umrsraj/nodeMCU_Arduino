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

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7981002667&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/TollBooth/tollbooth.php?a=";
String rs = "\0";
#define m11 D6
#define m12 D7
#define buzzer D8
 
int count1 = 0;                                          // count = 0
char input[12];

int amount = 200;
int amount1 = 200;
void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void forward ()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  delay(50);
}
void backward ()
{
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  delay(50);
}

void stop_motor ()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  delay(50);
}

void sendsms (void);
void send2server (void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" RFID BSD TOLL ");
  lcd.setCursor( 0, 1);
  lcd.print(" BOOTH MNGR S/M ");
  delay(2500);

  pinMode(buzzer, OUTPUT);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);

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
   
  http.begin("http://projectsiot.xyz/IoTProjects/TollBooth/tollbooth.php?a=U&b=5&c=6&d=3");

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
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7981002667&from=MYDREM&message=KIT%20STARTED"); //Specify request destination

 
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

R:
  lcd.setCursor(0, 0);
  lcd.print("Please show card          ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");

  if (Serial.available())
  {
    count1 = 0;
    while (Serial.available() && count1 < 12)         // Read 12 characters and store them in input array
    {
      input[count1] = Serial.read();
      count1++;
      delay(5);
    }//WHILE
    //

    Serial.println(input);                           // Print RFID tag number
    Serial.print(F("input[10] is ")); Serial.println(input[10]);
  if (input[10] == '6')
    {

      input[10] = '0';

      if (amount < 5)
      {
         lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("UR BALENCE IS 0");
        lcd.setCursor(0, 1);
        lcd.print(" PLZ RECHARGE  ");
        delay(2000);

msg = a + "CARD1MATCHED%20NO%20BALANCE";
sendsms ();
rs = r + 'A' + "&b=" + '0' + "&c=" + String(amount) + "&d=" + 'N';
send2server ();

goto R;
}

      else if (amount > 49)
      {

        amount = amount - 50 ;
        Serial.print(F("remaining bal == ")); Serial.println(amount);

        if (amount < 51)
        {

          lcd.setCursor(4, 1);
          lcd.print("LOW BALENCE");

        }
       msg = a + "CARD-1MATCHED%20REMAINING%20BALANCE="+String(amount);
sendsms ();
rs = r + 'A' + "&b=" + "50" + "&c=" + String(amount) + "&d=" + 'Y';
send2server ();

lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  CARD1 MATCHED   ");
        lcd.setCursor(0, 1);
        lcd.print("RE BAL:");
        lcd.setCursor(8, 1);
        lcd.print(amount);
        delay(500);
        forward ();
        delay(2000);
        stop_motor ();
        delay(1000);
        backward ();
        delay(2000);
        stop_motor();
        delay(1500);
      }
    } // 1st card
    else  if (input[10] == '9')
    {

      input[10] = '0';

      if (amount1 < 5)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("UR BALENCE IS 0");
        lcd.setCursor(0, 1);
        lcd.print(" PLZ RECHARGE  ");
        delay(2000);

msg = a + "CARDM-2%20MATCHED%20NO%20BALANCE";
sendsms ();
rs = r + 'B' + "&b=" + '0' + "&c=" + String(amount1) + "&d=" + 'N';
send2server ();

goto R;
}

      else if (amount1 > 49)
      {

        amount1 = amount1 - 50 ;
        Serial.print(F("remaining bal == ")); Serial.println(amount1);

        if (amount1 < 51)
        {

          lcd.setCursor(4, 1);
          lcd.print("LOW BALENCE");

        }
       msg = a + "CARD-2%20MATCHED%20REMAINING%20BALANCE="+String(amount1);
sendsms ();
rs = r + 'B' + "&b=" + "50" + "&c=" + String(amount1) + "&d=" + 'Y';
send2server ();

lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  CARD2 MATCHED   ");
        lcd.setCursor(0, 1);
        lcd.print("RE BAL:");
        lcd.setCursor(8, 1);
        lcd.print(amount1);
        delay(500);
        forward ();
        delay(2000);
        stop_motor ();
        delay(1000);
        backward ();
        delay(2000);
        stop_motor();
        delay(1500);
      }
    } // 2nd card

       else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  INVALID CARD  ");
      delay(1600);
      lcd.setCursor(0, 1);
      lcd.print("***PLZ CHECK***");
      beep  ();
      delay(1700);
      
rs = r + 'H' + "&b=" + '0' + "&c=" + '0' + "&d=" + 'N';
send2server ();
}

    }
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
//   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7981002667&from=MYDREM&message="); 
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
