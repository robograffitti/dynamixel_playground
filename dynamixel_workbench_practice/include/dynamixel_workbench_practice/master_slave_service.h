#ifndef DYNAMIXEL_WORKBENCH_PRACTICE_H
#define DYNAMIXEL_WORKBENCH_PRACTICE_H

#include <ros/ros.h>
#include <dynamixel_workbench_msgs/DynamixelStateList.h>

#include <dynamixel_workbench_msgs/DynamixelCommand.h>
// #include <dynamixel_workbench_msgs/DynamixelCommandRequest.h>
// #include <dynamixel_workbench_msgs/DynamixelCommandResponse.h>

// static int control_cycle = 125;
static int queue = 1;

ros::ServiceClient client;
dynamixel_workbench_msgs::DynamixelCommand srv;

void jointStateCallback(const dynamixel_workbench_msgs::DynamixelStateListConstPtr& msg);

#endif
