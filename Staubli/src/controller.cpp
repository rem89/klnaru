/*
 * controller.cpp
 *
 *  Created on: Jan 29, 2010
 *      Author: joseph
 */

#include "TX60L.h"
#include <iostream>
#include <algorithm>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>
#include "staubli/command.h"		//command service of staubli
#include "controller.h"


void print(double e){
	std::cout << " " << e;
}

int GetPosition(staubli::command::Response *res){

	TX60L robot;
	robot.Login(STAUBLI_IP, "default", "");
	robot.Power(true);
	ROS_INFO("Staubli is connected !!.");

	std::vector<double> position;
	position.resize(6);

	if(robot.GetRobotCartesianPosition(position)){
		for_each(position.begin(), position.end(), print);
		std::cout <<"\n";
		res->x = position[0];
		res->y = position[1];
		res->z = position[2];
		res->theta_x  = position[3];
		res->theta_y  = position[4];
		res->theta_z  = position[5];
	}else
		std::cout <<"wrong\n";

	robot.Logoff();
	return 0;
}

int GetJoints(staubli::command::Response *res){

	TX60L robot;
	robot.Login(STAUBLI_IP, "default", "");
	robot.Power(true);
	ROS_INFO("Staubli is connected !!.");

	std::vector<double> joints;
	joints.resize(6);

	if(robot.GetRobotJoints(joints)){
		for_each(joints.begin(), joints.end(), print);
		std::cout <<"\n";
		res->joint1 = joints[0];
		res->joint2 = joints[1];
		res->joint3 = joints[2];
		res->joint4  = joints[3];
		res->joint5  = joints[4];
		res->joint6  = joints[5];
	}else
		std::cout <<"wrong\n";

	robot.Logoff();
	return 0;
}

int MoveJoints(staubli::command::Request  *req,
			   staubli::command::Response *res)
{
	TX60L robot;
	robot.Login(STAUBLI_IP, "default", "");
	robot.Power(true);
	ROS_INFO("Staubli is connected !!.");

	//Move joints
	std::vector<double> target_joints;
	target_joints.push_back(req->joint1);
	target_joints.push_back(req->joint2);
	target_joints.push_back(req->joint3);
	target_joints.push_back(req->joint4);
	target_joints.push_back(req->joint5);
	target_joints.push_back(req->joint6);
	robot.ResetMotion();
	robot.MoveJoints(target_joints);

	//Get Current joints
//	for_each(target_joints.begin(), target_joints.end(), print);
//	std::cout <<"\n";
	res->joint1 = target_joints[0];
	res->joint2 = target_joints[1];
	res->joint3 = target_joints[2];
	res->joint4  = target_joints[3];
	res->joint5  = target_joints[4];
	res->joint6  = target_joints[5];

	//Log off staubli
	robot.Logoff();
}

// handler for command service
// See command.srv
bool commandhandler(staubli::command::Request  &req,
					staubli::command::Response &res ){

	ROS_INFO("Command #%d.",req.command_number);
	switch(req.command_number){
		case 1 : GetPosition(&res); break;
		case 2 : GetJoints(&res);break;
		case 3 : MoveJoints(&req,&res);break;
		default: break;
	}
	return true;

}

int main(int argc, char** argv){

	ros::init(argc, argv, "staubli_server");
	ros::NodeHandle n;
	ros::ServiceServer service = n.advertiseService("command", commandhandler);
	ROS_INFO("Ready to access staubli.");
	ros::spin();

	return 0;
}
