#include <ros/ros.h>
#include "telemetry.h"
#include "std_msgs/UInt8MultiArray.h"

Telemetry* tele = nullptr;
void G_Listenser_CallBack(const std_msgs::UInt8MultiArray::ConstPtr& msg);


void G_timerCallback(const ros::TimerEvent&)
{
  // ROS_INFO_STREAM(" Listening Message !! ");
  tele->Get_Waypoint();

}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "FGuideMain");
  ros::NodeHandle nh;
  ros::Subscriber G_Listener = nh.subscribe("/Control2Guidance",11,G_Listenser_CallBack);
  ros::Publisher  G_talker   = nh.advertise<std_msgs::UInt8MultiArray>("/Guidance2Control",11);



  tele = new Telemetry(" Telemetry Serial Init");

  ros::Timer timerG = nh.createTimer(ros::Duration(0.01),G_timerCallback);
  ROS_INFO("GUIDE SYSTEM START");
  ros::spin();
}

void G_Listenser_CallBack(const std_msgs::UInt8MultiArray::ConstPtr& msg)
{

}
