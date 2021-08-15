#include "slidingmode.h"

SlidingMode::SlidingMode()
{

}
void SlidingMode::InitParamater()
{
    pre_x_r = x_gps;
    pre_y_r = y_gps;
}
void SlidingMode::InitPlanning()
{
    // Get Home POint
    pre_x_d = x_plan[0];
    pre_y_d = y_plan[0];


}
float SlidingMode::sign(float x)
{
  if (x > 0.0)
  {
      return 1.0;
  }
  else if (x< 0.0)
  {
      return -1.0;
  }
  else
  {
      return 0;
  }
}
void SlidingMode::Local_Control()  // T sample = 0.1s TImer
{
    x_e=  cos(theta_d)*(x_r - x_d)+sin(theta_d)*(y_r-y_d);
    y_e= -sin(theta_d)*(x_r - x_d)+cos(theta_d)*(y_r-y_d);
    theta_e = theta_r-theta_d; //rad   theta_r(rad) theta_d(rad)

    x_e_dot = -v_d +v_r*cos(theta_e) + omega_d*y_e;
    y_e_dot =  v_r*sin(theta_e)- omega_d*x_e;
    theta_e_dot = omega_r-omega_d;    //rad/s

    //Sliding Surface
    s1 = x_e_dot+ k1*x_e;
    s2 = y_e_dot+ k2*y_e+k3*sign(y_e)*theta_e;    // theta_e(rad)

    v_d_dot = v_d/Ts;
    omega_d_dot = omega_d/Ts; //rad /s2

    v_c_dot = ( -Q1*s1 - P1*sign(s1) - k1*x_e_dot + v_d_dot + v_r*sin(theta_e)*theta_e_dot - y_e_dot*omega_d - omega_d_dot*y_e )/cos(theta_e);
    omega_c = omega_d + ( -Q2*s2 - P2*sign(s2) - k2*y_e_dot - v_r_dot*sin(theta_e) + omega_d*x_e_dot + omega_d_dot*x_e )/( v_r*cos(theta_e) + k3*sign(y_e) );

    omega_c_dot = omega_c/Ts;

    F_right = 1/2*( ( M*v_c_dot + F_flag )+( 2*I*omega_c_dot/W + F_flag ) );
    F_left  = 1/2*( ( M*v_c_dot + F_flag )-( 2*I*omega_c_dot/W + F_flag ) );

}
void SlidingMode::Global_Control()
{
    x_d=x_plan[count_point];
    y_d=y_plan[count_point];
    theta_d=atan(( y_d-pre_y_d )/( x_d-pre_x_d ));   //rad
    omega_d=0.01;
    v_d = 4/3;  // F=20N


}
void SlidingMode::Main_Control()
{
    Global_Control();
    if ( (x_d  - x_r ) <= 0.05  && ( y_d - y_r) <= 0.05 )
    {
        Local_Control();
    }
}






















