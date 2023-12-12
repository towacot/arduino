double PID_calc(double x){//PID制御の計算部分

  dt = (micros()-pretime)/1000000;
  pretime = micros();

  P = x;
  I += P*dt;
  D = (P-preP)/dt;
  preP = P;
  
  return Kp*P+Kd*D+Ki*I;
}
double P_calc(double x,double target){//P制御の計算部分

  P = x-target;
  
  return Kp2*P;
}