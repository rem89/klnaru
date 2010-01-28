/*
 * MainController.cpp
 *
 *  Created on: Jan 28, 2010
 *      Author: joseph
 */

#include <ros/ros.h>
#include <std_msgs/String.h>
void chatterCallback(const std_msgs::StringConstPtr& msg)
{
  ROS_INFO("Received [%s]", msg->data.c_str());
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "MainController");
  ros::NodeHandle n;
  ros::Subscriber chatter_sub = n.subscribe("chatter", 100, chatterCallback);
  ros::spin();
}

