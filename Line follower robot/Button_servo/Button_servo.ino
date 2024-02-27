#include <ESP32_Servo.h>

Servo myServo;

const int but1 = 23;  // Nút nhấn tăng
const int but2 = 18;  // Nút nhấn giảm
const int but3 = 21;  // Nút nhấn lưu
 
int angle ; 


void setup() {
  Serial.begin(115200);
  myServo.attach(13);  
  pinMode(but1, INPUT); 
  pinMode(but2, INPUT);
  pinMode(but3, INPUT);

}

void loop() {

}
