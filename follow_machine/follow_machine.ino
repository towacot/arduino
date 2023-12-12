
// const int trigPin_left = 2;
// const int echoPin_left = 3;
// const int trigPin_right = 7;
// const int echoPin_right = 8;
const int timeout =100;//pulesInのタイムアウト時間（マイクロ秒）
//設定
#include "pin_num.h"
int lost=0;//見失ったとき1にする
double space=4;//車間距離cm
int base_duty=50;

double Kp=0;
double Ki=0;
double Kd=0;
double Kp2=0;
//制御定数

double Ldist = 0;
double Rdist= 0;
double dist=0;
double LRdiff = 0;
//制御をかける数

double prediff;
double predist;
//見失った時用の

double adj;
double mag;
//回転数に作用する値 

double dt;
double pretime;
double P,I,D;
double preP = 0;
//制御に関わる数
void setup() {
  Serial.begin(9600);
  pinMode(trigPin_left, OUTPUT);
  pinMode(echoPin_left, INPUT);
  pinMode(trigPin_right, OUTPUT);
  pinMode(echoPin_right, INPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}
void loop() {
  forward_mode();
  following();

}

void following(){

  Ldist=get_dist(trigPin_left,echoPin_left);
  Rdist=get_dist(trigPin_right,echoPin_right);
  LRdiff=Ldist-Rdist;
  dist=(Ldist+Rdist)/2;//左右差と平均距離を導出

  if(lost==1){
    lost_ctrl(prediff,predist);
  }else{
    clearlost();
    regular_ctrl(LRdiff,dist);
  }
  
}
void clearlost(){
  lost=0;
  //lost時に使った数のリセットをする
}

void regular_ctrl(double LRdiff,double dist){//平常時の制御
  adj=PID_calc(LRdiff);
  mag=get_mag(dist,space);
  //制御を行う

  analogWrite(3,mag*(base_duty-adj));//右制御
  analogWrite(9,mag*(base_duty+adj));//左制御
  prediff=LRdiff;
  predist=dist;
}

void lost_ctrl(double diff,double dist){//lost時の制御 I制御を行ってもいいかも

  adj=PID_calc(diff);
  mag=get_mag(dist,space);
  //制御を行う

  //なにか倍率をかける？
  analogWrite(3,mag*(base_duty-adj));//右制御
  analogWrite(9,mag*(base_duty+adj));//左制御
}

double get_mag(double dist,double space){//回転数に作用する倍率を決める もっとうまくやれるかも
  if(space<dist){
    return P_calc(dist,space);
  }else{
    return 0;
  }
}

// double PID_calc(double x){//PID制御の計算部分

//   dt = (micros()-pretime)/1000000;
//   pretime = micros();

//   P = x;
//   I += P*dt;
//   D = (P-preP)/dt;
//   preP = P;
  
//   return Kp*P+Kd*D+Ki*I;
// }
// double P_calc(double x,int double target){//P制御の計算部分

//   P = x-target;
  
//   return Kp2*P;
// }
void forward_mode(){
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  //前進するよ
}

// double get_dist(int trig,int echo){ //距離を返す。タイムアウト時はlostを1にして0を返す。
//   double duration,distance;
//   digitalWrite(trig, LOW);
//   digitalWrite(echo, LOW);
 
//   delayMicroseconds(1);
//   digitalWrite(trig, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trig, LOW);
//   duration = pulseIn(echo, HIGH,timeout);
//   if(duration=0){
//     lost=1;
//     return 0;
//   }else{    
//     distance = duration * 0.000001 * 34000 / 2;

//     return distance;
//   }
// }
