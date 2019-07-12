#ifndef DYNAMIXEL_WORKBENCH_PRACTICE_H
#define DYNAMIXEL_WORKBENCH_PRACTICE_H

#include <ros/ros.h>
#include <dynamixel_workbench_msgs/DynamixelStateList.h>

#include <dynamixel_workbench_msgs/DynamixelCommand.h>
// #include <dynamixel_workbench_msgs/DynamixelCommandRequest.h>
// #include <dynamixel_workbench_msgs/DynamixelCommandResponse.h>

#include <geometry_msgs/PoseStamped.h>

static int control_cycle = 125;
static int queue = 1;

ros::ServiceClient client;
dynamixel_workbench_msgs::DynamixelCommand srv;

void jointStateCallback(const geometry_msgs::PoseStampedConstPtr& msg);

#endif
