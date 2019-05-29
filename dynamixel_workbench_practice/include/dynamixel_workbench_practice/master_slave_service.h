#ifndef DYNAMIXEL_WORKBENCH_PRACTICE_H
#define DYNAMIXEL_WORKBENCH_PRACTICE_H

#include <ros/ros.h>
// #include <dynamixel_workbench_msgs/DynamixelState.h>
#include <dynamixel_workbench_msgs/DynamixelStateList.h>

#include <dynamixel_workbench_msgs/DynamixelCommand.h>
// #include <dynamixel_workbench_msgs/DynamixelCommandRequest.h>
// #include <dynamixel_workbench_msgs/DynamixelCommandResponse.h>

static int control_cycle = 250;
static int queue = 1;
int count = 0;

dynamixel_workbench_msgs::DynamixelCommand srv;

// ros::NodeHandle nh;
ros::ServiceClient client;
// ros::Rate loop_rate;

void jointStateCallback(const dynamixel_workbench_msgs::DynamixelStateListConstPtr& msg);
void commandClient();

#endif
