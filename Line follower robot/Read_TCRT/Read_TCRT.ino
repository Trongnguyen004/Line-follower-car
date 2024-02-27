const int S1 = 25;
const int S2 = 33;
const int S3 = 32;
const int S4 = 35;
const int S5 = 34;
void setup(){
  Serial.begin(115200);
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);  
}
void loop(){
  int S1_value = digitalRead(S1);
  int S2_value = digitalRead(S2);
  int S3_value = digitalRead(S3);
  int S4_value = digitalRead(S4);
  int S5_value = digitalRead(S5);
  Serial.print(S1_value); Serial.print("   ");
  Serial.print(S2_value); Serial.print("   ");
  Serial.print(S3_value); Serial.print("   ");
  Serial.print(S4_value); Serial.print("   ");
  Serial.print(S5_value); Serial.println("   ");
 delay(10);
}
