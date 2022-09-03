#include <ros.h>
#include <std_msgs/Float32.h>
#include <CytronMotorDriver.h>

ros::NodeHandle nh;
std_msgs::Float32 max_vel_L, max_vel_R;

CytronMD L_motor(PWM_DIR, 9, 8);     // PWM 1 = Pin 9, DIR 1 = Pin 8.
CytronMD R_motor(PWM_DIR, 11, 10);   // PWM 2 = Pin 11, DIR 2 = Pin 10.

float req_pwm_L, req_pwm_R;
float percent_L, percent_R;

void lwheel_callback(const std_msgs::Float32& inp){
//  Serial.println("Lcll"/);
  percent_L = inp.data/max_vel_L.data;  
  req_pwm_L = (int)(255*percent_L);
  L_motor.setSpeed(req_pwm_L);  
}

void rwheel_callback(const std_msgs::Float32& inp){
  percent_R = inp.data/max_vel_R.data;
  req_pwm_R = (int)(255*percent_R);
  R_motor.setSpeed(req_pwm_R);
}

ros::Subscriber<std_msgs::Float32> lwheel_vtarget("/lwheel_vtarget", lwheel_callback);
ros::Subscriber<std_msgs::Float32> rwheel_vtarget("/rwheel_vtarget", rwheel_callback);

void setup()
{
  nh.initNode();
  
  max_vel_L.data = 0.5;
  max_vel_R.data = 0.5;
  
//  nh.getParam("~max_vel_Fl", &max_vel_L.data);
//  nh.getParam("~max_vel_Fr", &max_vel_R.data);

  nh.subscribe(lwheel_vtarget);
  nh.subscribe(rwheel_vtarget);

  Serial.begin(57600);
}

void loop()
{
  nh.spinOnce();
}
