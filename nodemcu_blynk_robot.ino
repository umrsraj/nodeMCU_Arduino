/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "d6e46b1b40904183b2f9ac51d42032e1";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "project";
char pass[] = "project12345";



#define m1a D1
#define m1b D2
#define m2a D3
#define m2b D4

void forward(void)
{
  Serial.println("moving forward ....");
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
   delay(100);
}

void backward(void)
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
   delay(100);
     Serial.println("moving BACKWARD ....");
}

void left(void)
{
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
  delay(100);
    Serial.println("moving LEFT ....");
}

void right(void)
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
  delay(100);
    Serial.println("moving RIGHT ....");
}

void stop_motor(void)
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
  delay(100);
    Serial.println("moving STOP ....");
}


BLYNK_WRITE(V1)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
forward ();
}
}
BLYNK_WRITE(V2)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
backward ();
}
}
BLYNK_WRITE(V3)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
left ();
}
}
BLYNK_WRITE(V4)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
right ();
}
}
BLYNK_WRITE(V5)
{
  int pin = param.asInt(); // assigning incoming value from pin V1 to a variable
if (pin == 1)
{
stop_motor();
}
}


void setup()
{
  // Debug console
  Serial.begin(9600);


pinMode(m1a,OUTPUT);
pinMode(m1b,OUTPUT);
pinMode(m2a,OUTPUT);
pinMode(m2b,OUTPUT);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
