int QRE1113_Pin = 14; //connected to analog 0

void setup(){
  Serial.begin(9600);
}


void loop(){

  int QRE_Value = analogRead(QRE1113_Pin);
  Serial.println(QRE_Value); 

}
