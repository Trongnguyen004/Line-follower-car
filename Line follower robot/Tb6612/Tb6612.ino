int But1 = 23;
int But2 = 18;
int But3 = 21;
int Speed = 100;
int SpeedA = 100;
int SpeedB = 100;
int Buzz = 19;
int But3_value, lastBut3_value;
#define STBY   4
#define A   15
#define A1  0
#define A2  2
#define B   5
#define B1  16
#define B2  17

void setup(){
  Serial.begin(115200);
  pinMode(Buzz, OUTPUT);
  digitalWrite(Buzz,HIGH);
  delay(10);
  digitalWrite(Buzz,LOW);
  
  pinMode(STBY, OUTPUT);
//  digitalWrite(STBY,LOW);
  
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A, OUTPUT);

  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B, OUTPUT);

  pinMode(But1, INPUT);
  pinMode(But2, INPUT);
  pinMode(But3, INPUT);
}
void For(){
  analogWrite(A,SpeedA);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
  analogWrite(B,SpeedB);
  digitalWrite(B1,HIGH);
  digitalWrite(B2,LOW);
}
void Back(){
  analogWrite(A,Speed);
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);
  analogWrite(B,Speed);
  digitalWrite(B1,LOW);
  digitalWrite(B2,HIGH);
}
void Stop(){
  analogWrite(A,0);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  analogWrite(B,0);
  digitalWrite(B1,LOW);
  digitalWrite(B2,LOW);
}
void  loop(){
  Run();
  Serial.println(STBY);
  
}
void Run(){
  But3_value = digitalRead(But3);
  if (But3_value != lastBut3_value && But3_value == LOW) {
    if (But3_value == LOW) {
      digitalWrite(STBY, !digitalRead(STBY));
        For();
        delay(5000);
        Stop();
        delay(2000);
//        Back();
//        delay(1000);
//        Stop();
//        delay(2000);
    }
  }
  lastBut3_value = But3_value;
}
