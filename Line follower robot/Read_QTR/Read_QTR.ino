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

// Tb6612
#define STBY   4
#define A   15
#define A1  0
#define A2  2
#define B   5
#define B1  16
#define B2  17

int But3 = 21;
int But3_value, lastBut3_value;
int ttp223 = 13;
int ttp_value, lastttp_value;

void setup(){
  Serial.begin(115200);
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);
  pinMode(S6,INPUT);
  pinMode(S7,INPUT);
  pinMode(S8,INPUT);
  pinMode(IR,OUTPUT);
  
   pinMode(STBY, OUTPUT);
//  digitalWrite(STBY,HIGH);
  
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B, OUTPUT);
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
void pid(){
  PID_value = error*Kp;
  
  Left = Speed + PID_value ;
  Right = Speed - PID_value ;
  Left= constrain(Left, 0, 255);
  Right = constrain(Right, 0, 255);
}
void loop(){
  Run();
//  digitalWrite(IR,HIGH);
  s1 = analogRead(S1);
  s2 = analogRead(S2);
  s3 = analogRead(S3);
  s4 = analogRead(S4);
  s5 = analogRead(S5);
  s6 = analogRead(S6);
  s7 = analogRead(S7);
  s8 = analogRead(S8);
  float A[8]= {s8, s7, s6, s5, s4, s3, s2, s1};
  for (int i=0; i<8; i++){
    if(A[i] >= Alpha){
       A[i]=1;
    }else{
       A[i]=0;
    }
    Serial.print(A[i]);
    Serial.print("    ");
  }
  
  if      ((A[0]==0) && (A[1]==0) && (A[2]==0) && (A[3]==1) && (A[4]==1) && (A[5]==0) && (A[6]==0) && (A[7]==0) ){
    error = 0;        //00011000
  }else if((A[0]==0) && (A[1]==0) && (A[2]==0) && (A[3]==0) && (A[4]==1) && (A[5]==0) && (A[6]==0) && (A[7]==0) ){
    error = 0.5;      //00001000
  }else if((A[0]==0) && (A[1]==0) && (A[2]==0) && (A[3]==0) && (A[4]==1) && (A[5]==1) && (A[6]==0) && (A[7]==0) ){
    error = 1;        //00001100
  }else if((A[0]==0) && (A[1]==0) && (A[2]==0) && (A[3]==0) && (A[4]==0) && (A[5]==1) && (A[6]==0) && (A[7]==0) ){
    error = 1.5;      //00000100
  }else if((A[0]==0) && (A[1]==0) && (A[2]==0) && (A[3]==0) && (A[4]==0) && (A[5]==1) && (A[6]==1) && (A[7]==0) ){
    error = 2;        //00000110
  }else if((A[0]==0) && (A[1]==0) && (A[2]==0) && (A[3]==0) && (A[4]==0) && (A[5]==0) && (A[6]==1) && (A[7]==0) ){
    error = 2.5;      //00000010
  }else if((A[0]==0) && (A[1]==0) && (A[2]==0) && (A[3]==0) && (A[4]==0) && (A[5]==0) && (A[6]==1) && (A[7]==1) ){
    error = 3;        //00000011
  }else if((A[0]==0) && (A[1]==0) && (A[2]==0) && (A[3]==0) && (A[4]==0) && (A[5]==0) && (A[6]==0) && (A[7]==1) ){
    error = 4;        //00000001
  }else if((A[0]==1) && (A[1]==0) && (A[2]==0) && (A[3]==0) && (A[4]==0) && (A[5]==0) && (A[6]==0) && (A[7]==0) ){
    error = -4;       //10000000
  }else if((A[0]==1) && (A[1]==1) && (A[2]==0) && (A[3]==0) && (A[4]==0) && (A[5]==0) && (A[6]==0) && (A[7]==0) ){
    error = -3;       //11000000
  }else if((A[0]==0) && (A[1]==1) && (A[2]==0) && (A[3]==0) && (A[4]==0) && (A[5]==0) && (A[6]==0) && (A[7]==0) ){
    error = -2.5;     //01000000
  }else if((A[0]==0) && (A[1]==1) && (A[2]==1) && (A[3]==0) && (A[4]==0) && (A[5]==0) && (A[6]==0) && (A[7]==0) ){
    error = -2;       //01100000
  }else if((A[0]==0) && (A[1]==0) && (A[2]==1) && (A[3]==0) && (A[4]==0) && (A[5]==0) && (A[6]==0) && (A[7]==0) ){
    error = -1.5;     //00100000
  }else if((A[0]==0) && (A[1]==0) && (A[2]==1) && (A[3]==1) && (A[4]==0) && (A[5]==0) && (A[6]==0) && (A[7]==0) ){
    error = -1;       //00110000
  }else if((A[0]==0) && (A[1]==0) && (A[2]==0) && (A[3]==1) && (A[4]==0) && (A[5]==0) && (A[6]==0) && (A[7]==0) ){
    error = -0.5;     //00010000
  }else if((A[0]==0) && (A[1]==0) && (A[2]==0) && (A[3]==0) && (A[4]==0) && (A[5]==0) && (A[6]==0) && (A[7]==0) ){
    error = 5;        //00000000  mat line
  }else if((A[0]==1) && (A[1]==1) && (A[2]==1) && (A[3]==1) && (A[4]==1) && (A[5]==1) && (A[6]==1) && (A[7]==1) ){
    error = 6;        //11111111  full den
  }
  
  Serial.println(error);
}
