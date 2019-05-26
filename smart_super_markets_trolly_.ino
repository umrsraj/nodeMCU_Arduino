/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AMBEST Technologies";
char pass[] = "AmBeSt@@321";

// Attach virtual serial terminal to Virtual Pin V1
WidgetTerminal terminal(V1);

BLYNK_WRITE(V1)
{

  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("hi") == param.asStr()) {
    terminal.println("You said: 'hi'") ;
    terminal.println("I said: 'hello'") ;
  } else {

    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}


#include <String.h>
#include <LiquidCrystal.h>


#define button D6
#define buzzer D7

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=";
String msg = "\0";

String items = "\0";

int count1 = 0; 
// count = 0
char input[12];

int  q = 0;

const int meat = 200;
const int oil = 100;
const int pen = 20;
const int soap = 50;
const int toy = 250;

int no = 0;
int no1 = 0;

int amount = 1000;
int cost = 0;

LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);


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
Serial.println("smart trolly for megamalls");

pinMode(buzzer,OUTPUT);
pinMode(button,INPUT);

lcd.begin(16,2);

lcd.clear();
lcdstring(0,0," SMART SHOPPING  ");
lcdstring(0,1,"      CART       ");
delay(2000);

     lcd.clear();
  lcdstring(0,0," CONNECTING  TO ");
  lcdstring(0,1,"    SERVER     ");
delay(1000);
  
  Blynk.begin(auth, ssid, pass);
  
     lcd.clear();
  lcdstring(0,0,"WI-FI CONNECTED   ");
  lcdstring(0,1,"SERVER CONNECTED   ");
  delay(2000);

 terminal.println(F("KIT STARTED "));
  terminal.println(F("-------------"));
  terminal.flush();
  Blynk.notify("kit started"); delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  
lcd.setCursor(0, 0);
  lcd.print("Please show card          ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");


if (digitalRead(button) == HIGH)
{

Serial.println("BUTTON -- PRESSED ");

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

 if (input[10]=='C')
    {
      Serial.print(F("items = ")); Serial.println(items);
    no1 = items.length();
    Serial.print(F("items. length = ")); Serial.println(no1);
    no = items.indexOf('m');
for (q = 0; q <7; q++)
{
  items[no+q] = '$';
 
}   
Serial.print(F("items = ")); Serial.println(items);
    no = items.length();
    Serial.print(F("items. length = ")); Serial.println(no);
     
      cost = cost - meat;
   Serial.println(F("you REMOVED -- MEAT = 500 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   MEAT : 200   "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='E')
    {
    
      Serial.print(F("items = ")); Serial.println(items);
    no1 = items.length();
    Serial.print(F("items. length = ")); Serial.println(no1);
    no = items.indexOf('o');
for (q = 0; q <6; q++)
{
  items[no+q] = '$';
 
}     
Serial.print(F("items = ")); Serial.println(items);
    no = items.length();
    Serial.print(F("items. length = ")); Serial.println(no);  
   
    cost = cost - oil;
    
   Serial.println(F("you REMOVED -- OIL = 100 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   OIL : 100    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='8')
    {

      Serial.print(F("items = ")); Serial.println(items);
    no1 = items.length();
    Serial.print(F("items. length = ")); Serial.println(no1);
    no = items.indexOf('p');
for (q = 0; q <6; q++)
{
  items[no+q] = '$';
 
}     
Serial.print(F("items = ")); Serial.println(items);
    no = items.length();
    Serial.print(F("items. length = ")); Serial.println(no);  
      
    cost = cost - pen;
    
   Serial.println(F("you REMOVED --  PEN = 20 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   PEN : 20    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='F')
    {

      Serial.print(F("items = ")); Serial.println(items);
    no1 = items.length();
    Serial.print(F("items. length = ")); Serial.println(no1);
    no = items.indexOf('t');
for (q = 0; q <6; q++)
{
  items[no+q] = '$';
 
}      
Serial.print(F("items = ")); Serial.println(items);
    no = items.length();
    Serial.print(F("items. length = ")); Serial.println(no);  
      
    cost = cost - toy;
    
   Serial.println(F("you REMOVED --  TOY = 250 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   TOY : 250    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}

else if (input[10]=='7')
    {

      Serial.print(F("items = ")); Serial.println(items);
    no1 = items.length();
    Serial.print(F("items. length = ")); Serial.println(no1);
    no = items.indexOf('s');
for (q = 0; q <7; q++)
{
  items[no+q] = '$';
 
}       
Serial.print(F("items = ")); Serial.println(items);
    no = items.length();
    Serial.print(F("items. length = ")); Serial.println(no);  
      
    cost = cost - soap;
    
   Serial.println(F("you REMOVED --  SOAP = 50 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   SOAP : 50    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
for (q = 0; q <60; q++)
{
 if( items[no] == '$')
 {
  Serial.println("$ found-removing null");
  items.remove(no, 1);
 }
}//for loop  
}// serial available for button

}//if button
    
else if (Serial.available())
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

 if (input[10]=='C')
    {
      
      items += "meat%2C";
      Serial.print(F("items = ")); Serial.println(items);
      cost = cost + meat;
   Serial.println(F("you enterred -- MEAT = 500 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  

   
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   MEAT : 500   "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='E')
    {
      
    items += "oil%2C";
      Serial.print(F("items = ")); Serial.println(items);
    cost = cost + oil;
    
   Serial.println(F("you enterred -- OIL = 100 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   OIL : 100    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='8')
    {
      
       items += "pen%2C";
      Serial.print(F("items = ")); Serial.println(items);
      
    cost = cost + pen;
    
   Serial.println(F("you enterred --  PEN = 20 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   PEN : 20    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='F')
    {
      
    items += "toy%2C";
      Serial.print(F("items = ")); Serial.println(items);
      
    cost = cost + toy;
    
   Serial.println(F("you enterred --  TOY = 250 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   TOY : 250    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}

else if (input[10]=='7')
    {
      
    items += "soap%2C";
      Serial.print(F("items = ")); Serial.println(items);
      
    cost = cost + soap;
    
   Serial.println(F("you enterred --  SOAP = 50 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   SOAP : 50    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}

else if (input[10]=='4')
{

lcd.clear();
lcdstring(0,0,"CARD  AUTHERIZED");
lcdstring(0,1,"****************");
delay(2000);

lcd.clear();
lcdstring(0,0,"FINAL BILL: ");
lcdstring(12,0,String(cost));
delay(2000);


 if ((amount < cost)|| (amount <= 0))
{
  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("insufficient bal");
       lcd.setCursor(0,1);
    lcd.print(" PLZ RECHARGE  ");
    delay(2000);
    
}
else if (amount >= cost)
{

lcd.clear();

if (amount <101)
{
    lcd.setCursor(0,1);
    lcd.print("    LOW BALENCE  ");      
}  
  Serial.print(F("amount = ")); Serial.println(amount);
  amount = amount - cost;
  Serial.print(F("cost = ")); Serial.println(cost);
  Serial.print(F("amount****** = ")); Serial.println(amount);

lcdstring(0,0,"RE CARD BAL=");
lcdstring(12,0,String(amount));
delay(2000);




}
  
}

else
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("INVALID CARD  ");
  lcd.setCursor(0,0);
  lcd.print("PLEASE CHECK....");
  delay(30);
  beep ();
}

  } // Serial.available ()


 
} // loop
void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
