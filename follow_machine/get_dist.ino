double get_dist(int trig,int echo){ //距離を返す。タイムアウト時はlostを1にして0を返す。
  double duration,distance;
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
 
  delayMicroseconds(1);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH,timeout);
  if(duration=0){
    lost=1;
    return 0;
  }else{    
    distance = duration * 0.000001 * 34000 / 2;

    return distance;
  }
}