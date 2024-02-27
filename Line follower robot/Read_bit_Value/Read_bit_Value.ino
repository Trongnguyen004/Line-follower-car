const int switchPin1 = 36; // Cổng số của công tắc 1
const int switchPin2 = 22; // Cổng số của công tắc 2
const int switchPin3 = 39; // Cổng số của công tắc 3

void setup() {
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin3, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // Đọc trạng thái bit từ 3 công tắc
  int bit1 = digitalRead(switchPin1);
  int bit2 = digitalRead(switchPin2);
  int bit3 = digitalRead(switchPin3);
  
  // Ghép các bit lại thành một số nguyên duy nhất
  int switchState = (bit3 << 2) | (bit2 << 1) | bit1;
  
  // Sử dụng câu lệnh switch để thực hiện các chức năng khác nhau tùy thuộc vào trạng thái bit
  switch (switchState) {
    case 0:
      // Thực hiện chức năng khi tất cả các công tắc đều tắt
      Serial.println("All switches are off");
      break;
    case 1:
      // Thực hiện chức năng khi chỉ có công tắc 1 được bật
      Serial.println("Switch 1 is on");
      break;
    case 2:
      // Thực hiện chức năng khi chỉ có công tắc 2 được bật
      Serial.println("Switch 2 is on");
      break;
    case 3:
      // Thực hiện chức năng khi có công tắc 1 và 2 được bật
      Serial.println("Switch 1 and 2 are on");
      break;
    case 4:
      // Thực hiện chức năng khi chỉ có công tắc 3 được bật
      Serial.println("Switch 3 is on");
      break;
    case 5:
      // Thực hiện chức năng khi có công tắc 1 và 3 được bật
      Serial.println("Switch 1 and 3 are on");
      break;
    case 6:
      // Thực hiện chức năng khi có công tắc 2 và 3 được bật
      Serial.println("Switch 2 and 3 are on");
      break;
    case 7:
      // Thực hiện chức năng khi tất cả các công tắc đều được bật
      Serial.println("All switches are on");
      break;
    default:
      Serial.println("Invalid switch state");
      break;
  }
  
  delay(500); // Đợi 0.5 giây trước khi đọc lại trạng thái của các công tắc
}
