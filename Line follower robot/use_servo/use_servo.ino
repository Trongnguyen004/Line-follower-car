#include <ESP32Servo.h>

Servo servoMotor; // Khai báo một đối tượng servo

int servoPin = 13; // Chọn chân nối servo

void setup() {
  servoMotor.attach(servoPin); // Gắn servo vào chân
}

void loop() {
  // Điều chỉnh servo đến góc 0 độ
  servoMotor.write(0);
  delay(1000); // Chờ 1 giây

  // Điều chỉnh servo đến góc 90 độ
  servoMotor.write(90);
  delay(1000); // Chờ 1 giây

  // Điều chỉnh servo đến góc 180 độ
  servoMotor.write(180);
  delay(1000); // Chờ 1 giây
}
