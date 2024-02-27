#define BLYNK_TEMPLATE_ID "TMPL6qOGzea0U"
#define BLYNK_TEMPLATE_NAME "ccc"
#define BLYNK_AUTH_TOKEN "f2rZSWjg24-xkPPypg8zLqezeFxxW3yP"

#include <BlynkSimpleEsp32.h>
#include <WiFi.h>

char auth[] = "f2rZSWjg24-xkPPypg8zLqezeFxxW3yP";  
char ssid[] = "Bi Bo lau 3";   
char pass[] = "20070511"; 

// CB
const int S1 = 34;
const int S2 = 35;
const int S3 = 32;
const int S4 = 33;
const int S5 = 25;
const int S6 = 26;
const int S7 = 27;
const int S8 = 14;
const int IR = 12;

int s1, s2, s3, s4, s5, s6, s7, s8;
int Alpha = 2000;

float error;
float past_error;
int Left, Right;
int Speed = 110;
float Kp = 30;
float PID_value;

int Speed_modecontrol;

//Bit
const int bit0 = 36;
const int bit1 = 22;
const int bit2 = 39;
int bit0_value, bit1_value, bit2_value;

// Button
int But1 = 23;
int But2 = 18;
int But3 = 21;
int But3_value, lastBut3_value;

int ttp223 = 13;
int ttp_value, lastttp_value;
int Buzz = 19;

// Tb6612
#define STBY   4
#define A   15
#define A1  0
#define A2  2
#define B   5
#define B1  16
#define B2  17

bool but_forward = false;
bool but_backward = false;
bool but_left = false;
bool but_right = false;

//=============================================================================================
void setup(){
  Serial.begin(115200);
  
  WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
  { 
    delay(10); 
  }
  Blynk.begin(auth, ssid, pass);
  
  pinMode(Buzz, OUTPUT);
  digitalWrite(Buzz,HIGH);
  delay(100);
  digitalWrite(Buzz,LOW);
  
  pinMode(STBY, OUTPUT);
//  digitalWrite(STBY,HIGH);
  
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A, OUTPUT);

  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B, OUTPUT);

  pinMode(But1, INPUT);
  pinMode(But2, INPUT);
  pinMode(But3, INPUT);
  
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);  
  pinMode(S6,INPUT);
  pinMode(S7,INPUT);
  pinMode(S8,INPUT);
  pinMode(IR,OUTPUT);
//  digitalWrite(IR,HIGH);    
  pinMode(bit0,INPUT);
  pinMode(bit1,INPUT);
  pinMode(bit2,INPUT);
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
void Auto(){
  analogWrite(A,Left);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
  analogWrite(B,Right);
  digitalWrite(B1,HIGH);
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
void forward(){
  analogWrite(A,Speed_modecontrol);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
  analogWrite(B,Speed_modecontrol);
  digitalWrite(B1,HIGH);
  digitalWrite(B2,LOW);
}
//=============================================================================================
void back(){
  analogWrite(A,Speed_modecontrol);
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);
  analogWrite(B,Speed_modecontrol);
  digitalWrite(B1,LOW);
  digitalWrite(B2,HIGH);
}
void left(){
  analogWrite(A,Speed_modecontrol);
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);
  analogWrite(B,Speed_modecontrol);
  digitalWrite(B1,HIGH);
  digitalWrite(B2,LOW);
}
void right(){
  analogWrite(A,Speed_modecontrol);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
  analogWrite(B,Speed_modecontrol);
  digitalWrite(B1,LOW);
  digitalWrite(B2,HIGH);
}
//=============================================================================================
void Run(){
  But3_value = digitalRead(But3);
  ttp_value = digitalRead(ttp223);
  if (But3_value != lastBut3_value && But3_value == LOW) {
    if (But3_value == LOW) {
      digitalWrite(STBY, !digitalRead(STBY));
    }
  }else if(ttp_value != lastttp_value && ttp_value == LOW) {
    if (ttp_value == LOW) {
      digitalWrite(STBY, !digitalRead(STBY));
    }
  }
  lastBut3_value = But3_value;
  lastttp_value = ttp_value;
}
//=============================================================================================
void Read_tcrt(){ // S5 S4 S3 S2 S1
  
  int S1_value = digitalRead(S1);
  int S2_value = digitalRead(S2);
  int S3_value = digitalRead(S3);
  int S4_value = digitalRead(S4);
  int S5_value = digitalRead(S5);

  if      ((S5_value == 1)&& (S4_value == 1)&& (S3_value == 0)&& (S2_value == 1)&& (S1_value == 1)){
    error = 0;     //11011
  }else if((S5_value == 1)&& (S4_value == 1)&& (S3_value == 0)&& (S2_value == 0)&& (S1_value == 1)){
    error = 0.5;   //
  }else if((S5_value == 1)&& (S4_value == 1)&& (S3_value == 1)&& (S2_value == 0)&& (S1_value == 1)){
    error = 1;     //
  }else if((S5_value == 1)&& (S4_value == 1)&& (S3_value == 1)&& (S2_value == 0)&& (S1_value == 0)){
    error = 1.5;   // 
  }else if((S5_value == 1)&& (S4_value == 1)&& (S3_value == 1)&& (S2_value == 1)&& (S1_value == 0)){
    error = 2;     // 
  }else if((S5_value == 0)&& (S4_value == 1)&& (S3_value == 1)&& (S2_value == 1)&& (S1_value == 1)){
    error = -2;    //
  }else if((S5_value == 0)&& (S4_value == 0)&& (S3_value == 1)&& (S2_value == 1)&& (S1_value == 1)){
    error = -1.5;  //
  }else if((S5_value == 1)&& (S4_value == 0)&& (S3_value == 1)&& (S2_value == 1)&& (S1_value == 1)){
    error = -1;    //
  }else if((S5_value == 1)&& (S4_value == 0)&& (S3_value == 0)&& (S2_value == 1)&& (S1_value == 1)){
    error = -0.5;  //
  }else if((S5_value == 1)&& (S4_value == 1)&& (S3_value == 1)&& (S2_value == 1)&& (S1_value == 1)){
    error = 4;     //
  }else if((S5_value == 0)&& (S4_value == 0)&& (S3_value == 0)&& (S2_value == 0)&& (S1_value == 0)){
    error = 5;     //
  }  
}
//=============================================================================================
void modetcrt(){
  PID_value = error*Kp;
  
  Left = Speed + PID_value ;
  Right = Speed - PID_value ;
  Left= constrain(Left, 0, 255);
  Right = constrain(Right, 0, 255);

  if(error == 2){
    Left = 200 ;
    Right = 0 ;
    Auto();
  }else if (error == -2){
    Left = 0 ;
    Right = 200 ;
    Auto();
  }else if (error == 5){
    Stop();
  }else if (error == 4){
    PID_value = past_error*Kp;
    Left = Speed + PID_value ;
    Right = Speed - PID_value ;
    Left= constrain(Left, 0, 255);
    Right = constrain(Right, 0, 255);
  }else {
    Auto();
  }

  past_error = error;
}
//=============================================================================================
void modecontrol(){
  digitalWrite(STBY,HIGH);
  if (but_forward) {
    forward();
  } else if (but_backward) {
    back();
  } else if (but_left) {
    left();
  } else if (but_right) {
    right();
  } else {
    Stop();
  }
}
BLYNK_WRITE(V1) {
  but_forward = param.asInt();
}

BLYNK_WRITE(V2) {
  but_backward = param.asInt();
}
BLYNK_WRITE(V4) {
  but_right = param.asInt();
}
BLYNK_WRITE(V3) {
  but_left = param.asInt();
}
BLYNK_WRITE(V0) {
  Speed_modecontrol = param.asInt();
}
//=============================================================================================
void modeqtr_diy(){
  s1 = analogRead(S1);
  s2 = analogRead(S2);
  s3 = analogRead(S3);
  s4 = analogRead(S4);
  s5 = analogRead(S5);
  s6 = analogRead(S6);
  s7 = analogRead(S7);
  s8 = analogRead(S8);
  float S[8]= {s8, s7, s6, s5, s4, s3, s2, s1};
  for (int i=0; i<8; i++){
    if(S[i] >= Alpha){
       S[i]=1;
    }else{
       S[i]=0;
    }
  }
  
  if      ((S[0]==0) && (S[1]==0) && (S[2]==0) && (S[3]==1) && (S[4]==1) && (S[5]==0) && (S[6]==0) && (S[7]==0) ){
    error = 0;        //00011000
  }else if((S[0]==0) && (S[1]==0) && (S[2]==0) && (S[3]==0) && (S[4]==1) && (S[5]==0) && (S[6]==0) && (S[7]==0) ){
    error = 0.5;      //00001000
  }else if((S[0]==0) && (S[1]==0) && (S[2]==0) && (S[3]==0) && (S[4]==1) && (S[5]==1) && (S[6]==0) && (S[7]==0) ){
    error = 1;        //00001100
  }else if((S[0]==0) && (S[1]==0) && (S[2]==0) && (S[3]==0) && (S[4]==0) && (S[5]==1) && (S[6]==0) && (S[7]==0) ){
    error = 1.5;      //00000100
  }else if((S[0]==0) && (S[1]==0) && (S[2]==0) && (S[3]==0) && (S[4]==0) && (S[5]==1) && (S[6]==1) && (S[7]==0) ){
    error = 2;        //00000110
  }else if((S[0]==0) && (S[1]==0) && (S[2]==0) && (S[3]==0) && (S[4]==0) && (S[5]==0) && (S[6]==1) && (S[7]==0) ){
    error = 2.5;      //00000010
  }else if((S[0]==0) && (S[1]==0) && (S[2]==0) && (S[3]==0) && (S[4]==0) && (S[5]==0) && (S[6]==1) && (S[7]==1) ){
    error = 3;        //00000011
  }else if((S[0]==0) && (S[1]==0) && (S[2]==0) && (S[3]==0) && (S[4]==0) && (S[5]==0) && (S[6]==0) && (S[7]==1) ){
    error = 4;        //00000001
  }else if((S[0]==1) && (S[1]==0) && (S[2]==0) && (S[3]==0) && (S[4]==0) && (S[5]==0) && (S[6]==0) && (S[7]==0) ){
    error = -4;       //10000000
  }else if((S[0]==1) && (S[1]==1) && (S[2]==0) && (S[3]==0) && (S[4]==0) && (S[5]==0) && (S[6]==0) && (S[7]==0) ){
    error = -3;       //11000000
  }else if((S[0]==0) && (S[1]==1) && (S[2]==0) && (S[3]==0) && (S[4]==0) && (S[5]==0) && (S[6]==0) && (S[7]==0) ){
    error = -2.5;     //01000000
  }else if((S[0]==0) && (S[1]==1) && (S[2]==1) && (S[3]==0) && (S[4]==0) && (S[5]==0) && (S[6]==0) && (S[7]==0) ){
    error = -2;       //01100000
  }else if((S[0]==0) && (S[1]==0) && (S[2]==1) && (S[3]==0) && (S[4]==0) && (S[5]==0) && (S[6]==0) && (S[7]==0) ){
    error = -1.5;     //00100000
  }else if((S[0]==0) && (S[1]==0) && (S[2]==1) && (S[3]==1) && (S[4]==0) && (S[5]==0) && (S[6]==0) && (S[7]==0) ){
    error = -1;       //00110000
  }else if((S[0]==0) && (S[1]==0) && (S[2]==0) && (S[3]==1) && (S[4]==0) && (S[5]==0) && (S[6]==0) && (S[7]==0) ){
    error = -0.5;     //00010000
  }else if((S[0]==0) && (S[1]==0) && (S[2]==0) && (S[3]==0) && (S[4]==0) && (S[5]==0) && (S[6]==0) && (S[7]==0) ){
    error = 5;        //00000000  mSt line
  }else if((S[0]==1) && (S[1]==1) && (S[2]==1) && (S[3]==1) && (S[4]==1) && (S[5]==1) && (S[6]==1) && (S[7]==1) ){
    error = 6;        //11111111  full den
  }
}

void modeqtr_module(){
  
}
//=============================================================================================
void Read_bit(){
  bit0_value = digitalRead(bit0);
  bit1_value = digitalRead(bit1);
  bit2_value = digitalRead(bit2);

  int bitState = (bit2_value << 2) | (bit1_value << 1) | bit0_value;
  
  switch (bitState) {
    case 0:
        Read_tcrt();
        Run();
        modetcrt();
      break;
    case 1:
        modeqtr_module();
      break;
    case 2:
        modeqtr_diy();
      break;
    case 3:

      break;
    case 4:

      break;
    case 5:

      break;
    case 6:

      break;
    case 7:
        modecontrol();
        Blynk.run();
      break;
    default:

      break;
  }
  delay(10);

}
//=============================================================================================
void loop(){
  Read_bit();
  Serial.print(error);
  Serial.print("    ");
  Serial.print(error);
  Serial.print("    ");
}
