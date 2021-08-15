#ifndef SLIDINGMODE_H
#define SLIDINGMODE_H

#include <math.h>
class SlidingMode
{
public:
  SlidingMode();
  void InitParamater();
  void InitPlanning();
  void Global_Control();
  void Local_Control();
  void Main_Control();
  float sign(float x);
private:
  float x_d=0;
  float y_d=0;
  float theta_d=0;
  float omega_d=0;
  float v_d =0;
  float pre_x_d=0;
  float pre_y_d=0;
  float pre_theta_d=0;
  float pre_omega_d=0;
  float pre_v_d=0;

  float x_r=0;
  float y_r=0;
  float theta_r=-10;
  float v_r=0; // m/s
  float omega_r=0;

  float pre_x_r=0;
  float pre_y_r=0;
  float pre_theta_r=theta_r;
  float v_r_dot=0;


  float W=0.6;
  float M= 3;
  float L=0.8;
  float I=1/12*(W*W+L*L);
  float F_flag=0;
  float F_right =0;
  float F_left =0;

  float theta_e=0;
  float y_e = 0;
  float x_e = 0;
  float x_e_dot=0;
  float y_e_dot =0;
  float theta_e_dot=0;




  float omega_c=0;
  float pre_omega_c=0;
  float v_d_dot=0;
  float v_c_dot=0;
  float omega_d_dot=0;
  float omega_c_dot=0;


  float k1=1;
  float k2=1;
  float k3=3000;
  float Q1=1.0;
  float P1=0.1;
  float Q2=10.25;
  float P2=0.1;
  float s1=0;
  float s2=0;
  float Ts = 0.1;
  float x_plan[1000]={0};
  float y_plan[1000]={0};
  float x_gps=0;
  float y_gps=0;
  int count_point=0;

};

#endif // SLIDINGMODE_H
