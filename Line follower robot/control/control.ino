#define BLYNK_TEMPLATE_ID "TMPL6qOGzea0U"
#define BLYNK_TEMPLATE_NAME "ccc"
#define BLYNK_AUTH_TOKEN "f2rZSWjg24-xkPPypg8zLqezeFxxW3yP"

#include <BlynkSimpleEsp32.h>
#include <WiFi.h>

char auth[] = "f2rZSWjg24-xkPPypg8zLqezeFxxW3yP";  
char ssid[] = "Bi Bo lau 3";   
char pass[] = "20070511";   

int Buzz = 19;
int Speed ;

// Tb6612
#define STBY   4
#define A   15
#define A1  0
#define A2  2
#define B   5
#define B1  16
#define B2  17

bool forward = false;
bool backward = false;
bool left = false;
bool right = false;


void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1);
  }
  Blynk.begin(auth, ssid, pass);

  pinMode(Buzz, OUTPUT);
  digitalWrite(Buzz,HIGH);
  delay(100);
  digitalWrite(Buzz,LOW);
  
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY,HIGH);
  
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A, OUTPUT);

  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B, OUTPUT);
}

BLYNK_WRITE(V1) {
  forward = param.asInt();
}

BLYNK_WRITE(V2) {
  backward = param.asInt();
}

BLYNK_WRITE(V4) {
  right = param.asInt();
}

BLYNK_WRITE(V3) {
  left = param.asInt();
}
BLYNK_WRITE(V0) {
  Speed = param.asInt();
}
//=============================================================================================
void Stop(){
  analogWrite(A,0);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  analogWrite(B,0);
  digitalWrite(B1,LOW);
  digitalWrite(B2,LOW);  
}
//=============================================================================================
void For(){
  analogWrite(A,Speed);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
  analogWrite(B,Speed);
  digitalWrite(B1,HIGH);
  digitalWrite(B2,LOW);
}
//=============================================================================================
void Back(){
  analogWrite(A,Speed);
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);
  analogWrite(B,Speed);
  digitalWrite(B1,LOW);
  digitalWrite(B2,HIGH);
}
void Left(){
  analogWrite(A,Speed);
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);
  analogWrite(B,Speed);
  digitalWrite(B1,HIGH);
  digitalWrite(B2,LOW);
}
void Right(){
  analogWrite(A,Speed);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
  analogWrite(B,Speed);
  digitalWrite(B1,LOW);
  digitalWrite(B2,HIGH);
}
void smartcar() {
  if (forward) {
    For();
  } else if (backward) {
    Back();
  } else if (left) {
    Left();
  } else if (right) {
    Right();
  } else {
    Stop();
  }
}
void loop(){
  smartcar();
  Blynk.run();
  Serial.println(Speed);
}
