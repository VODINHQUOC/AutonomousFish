#include <ros/ros.h>
#include "usb2can.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/Float32MultiArray.h"
#include <stdint.h>

uint16_t lenX=0,lenY=0;
float y_posPlan[1000]={0};
float x_posPlan[1000]={0};
void C_Listener_CallBack(const std_msgs::UInt8MultiArray::ConstPtr& msg);
void C_ListenPositionPlan_Callback(const std_msgs::Float32MultiArray::ConstPtr& msg);
void C_ListenPositionPlanX_Callback(const std_msgs::Float32MultiArray::ConstPtr& msg);

void C_timerCallback(const ros::TimerEvent&)
{
  // ROS_INFO_STREAM("Check Timer 1s ");
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "FControlMain");
  ros::NodeHandle nh;
  ros::Subscriber C_Listener = nh.subscribe("/Guidance2Control",11,C_Listener_CallBack);
  ros::Subscriber C_ListenPositionPlan=nh.subscribe("positionY",500,C_ListenPositionPlan_Callback);
  ros::Subscriber C_ListenPositionPlanX=nh.subscribe("positionX",500,C_ListenPositionPlanX_Callback);
  ros::Publisher  C_talker   = nh.advertise<std_msgs::UInt8MultiArray>("/Control2Guidance",11);

  Usb2Can* u2cPtr=nullptr;
  u2cPtr = new Usb2Can("USB2CAN Serial Init");

  ros::Timer timer = nh.createTimer(ros::Duration(0.1),C_timerCallback);
  ROS_INFO("Control System Start");

  ros::spin();


}
void C_ListenPositionPlanX_Callback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
  lenX=(uint16_t)(msg->data[0]);
  for(uint16_t i=0;i<lenX;i++)
  {
    x_posPlan[i]=msg->data[i+1];
  }
  ROS_INFO_STREAM("Check Data C++ :"<<x_posPlan[5]);
}
void C_ListenPositionPlan_Callback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
  lenY = (uint16_t)(msg->data[0]);
  for(uint16_t i=0;i<lenY;i++)
  {
    y_posPlan[i]=msg->data[i+1];
  }
  ROS_INFO_STREAM("Check Data C++ :"<<y_posPlan[5]);
  // ROS_INFO("Check Data C++ : [%.8f]",x);

}
void C_Listener_CallBack(const std_msgs::UInt8MultiArray::ConstPtr& msg)
{

}
