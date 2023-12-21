const int timeout =2000;//pulesInのタイムアウト時間（マイクロ秒）
//設定
#include "pin_num.h"
#include <NewPing.h>
int lost=0;//見失ったとき1にする
double space=5;//車間距離cm
int base_duty=30;

double Kp=4.5;
//4.5 yosi
double Kd=0.1;
double Kp2=0;
//制御定数

double Ldist = 0;
double Rdist= 0;
double dist=15;
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
double P,D;
double preP = 0;
//制御に関わる数
int MAX_DISTANCE =15;
NewPing Lsonar(Pin_left,Pin_left, MAX_DISTANCE);
NewPing Rsonar(Pin_right,Pin_right, MAX_DISTANCE);
void setup() {
 Serial.begin(9600);
  // pinMode(trigPin_left, OUTPUT);
  // pinMode(echoPin_left, INPUT);
  // pinMode(trigPin_right, OUTPUT);
  // pinMode(echoPin_right, INPUT);

  pinMode(motorV1_right, OUTPUT);
  pinMode(motorP_right, OUTPUT);
  pinMode(motorV2_right, OUTPUT);
  pinMode(motorV1_left, OUTPUT);
  pinMode(motorV2_left, OUTPUT);
  pinMode(motorP_left, OUTPUT);
}
void loop() {
  forward_mode();
  // if(reboot==0){
  //   forward_mode();
  // }else if(reboot==1){
  //   stop();
  // }
  following();

}

void following(){
  Ldist=Lsonar.ping()* 0.000001 * 34000 / 2;
  Rdist=Rsonar.ping()* 0.000001 * 34000 / 2;
  LRdiff=Ldist-Rdist;
  dist=(Ldist+Rdist)/2;//左右差と平均距離を導出
  if((Ldist<space)||(Rdist<space)){
    dist=5;
  }
  Serial.println(Ldist);
  if((Ldist==0)||(Rdist==0)){
    lost_ctrl(prediff,predist);
  }else{
    regular_ctrl(LRdiff,dist);
  }
  
}

void regular_ctrl(double LRdiff,double dist){//平常時の制御
  adj=PID_calc(LRdiff);
  mag=get_mag(dist,space);
  //制御を行う
  if(mag*base_duty-adj<=0){
    analogWrite(3,0);//右制御
    analogWrite(9,mag*base_duty+adj);//左制御
  }else if(mag*base_duty+adj<=0){
    analogWrite(3,mag*base_duty-adj);//右制御
    analogWrite(9,0);//左制御
  }else{
    analogWrite(3,mag*base_duty-adj);//右制御
    analogWrite(9,mag*base_duty+adj);//左制御
  }
  prediff=LRdiff;
  predist=dist;
}

void lost_ctrl(double diff,double dist){//lost時の制御 I制御を行ってもいいかも

  adj=PID_calc(diff);
  
  mag=get_mag(dist,space);
  //制御を行う
  if(mag*base_duty-adj<=0){
      analogWrite(3,0);//右制御
      analogWrite(9,mag*base_duty+adj);//左制御
    }else if(mag*base_duty+adj<=0){
      analogWrite(3,mag*base_duty-adj);//右制御
      analogWrite(9,0);//左制御
    }else{
      analogWrite(3,mag*base_duty-adj);//右制御
      analogWrite(9,mag*base_duty+adj);//左制御
    }
}

double get_mag(double dist,double space){//回転数に作用する倍率を決める もっとうまくやれるかも
  if(space<dist){
    return dist/space;
    // return P_calc(dist,space);
  }else if(dist<=space){
    return 0;
  }
}

void forward_mode(){
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  //前進するよ
}
void stop(){
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
}

