int white=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int left = analogRead(A0);
  int right= analogRead(A1);
  // if ((analogRead(A2)<200)){
  //   //前方センサが白を検知
  //     white=white+1;
  //     //backを1に
  //   //}
  // }
  Serial.print("left  ");
  Serial.print(left);
  Serial.print("right  ");
  Serial.println(right);
  // Serial.print("front");
  // Serial.print(front);
  // Serial.print("backL");
  // Serial.print(backl);
  // Serial.print("backR");
  // Serial.println(backr);
}
