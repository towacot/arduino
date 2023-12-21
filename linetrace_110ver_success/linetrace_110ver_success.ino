int base_duty =110;
//これが基本のスピードになるよ
float Kp=0.076;
float Ki=0;
float Kd=0.0000000000007;
// float Kp=0.057;100
// float Ki=0;
// float Kd=0.0000000000007;
// float Kp=0.06;95 
// float Ki=0;
// float Kd=0.0000000000007;
// float Kp=0.057; 90
// float Ki=0;
// float Kd=0.0000000000007;
// float Kp=0.07;85
// float Ki=0;
// float Kd=0.0000000000007;
//PID制御の定数 これを調整してほしい
/*調整の方針
  １．まずKpを調節(でかすぎると曲がりすぎるから 曲がりすぎないくらいに下げてから
  ギリギリまで上げる)
  ２．kpがいい感じになった（kpだけで動く）らKiの調整
      理屈的には kiのおかげで、ギザギザしなくなるはず
  3.kdの調整
    kdなしで動いている班もあるのでじかんかかりそうなら速さ上げてもいい
    ki,kpよりだいぶ小さくなるはず
  4.うまく走るセッティングが見つかったら、記録して、スピードを上げる

  この繰り返し
*/

int LRdiff;
float adj;
float dt;
float pretime;
float P,I,D;
float preP = 0;
//PID制御で使うやつ

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  forward_mode();

  //前方センサー
  PID_control();
  //PID制御をおこなうよ！
  
}

float PID_calc(int x){
  //PID制御の計算部分
  dt = (micros()-pretime)/1000000;
  pretime = micros();
  P = x;
  I += P*dt;
  
  D = (P-preP)/dt;
  
  preP = P;
  
  return Kp*P+Kd*D+Ki*I;
}
void PID_control(){
  //PID制御の入出力部分

  LRdiff = analogRead(A1)-analogRead(A0);
  //右が黒の時正　左が黒の時負になるよ！ 0~1023
  adj = PID_calc(LRdiff);
  //LRdiffを0に近づけたい！

  analogWrite(3,base_duty-adj);//右制御
  analogWrite(9,base_duty+adj );//左制御
}
void forward_mode(){
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  //前進するよ
}
