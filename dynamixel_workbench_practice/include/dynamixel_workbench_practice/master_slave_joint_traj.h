#ifndef DYNAMIXEL_WORKBENCH_PRACTICE_H
#define DYNAMIXEL_WORKBENCH_PRACTICE_H

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <trajectory_msgs/JointTrajectoryPoint.h>

#include <dynamixel_workbench_msgs/DynamixelCommand.h>
// #include <dynamixel_workbench_msgs/DynamixelCommandRequest.h>
// #include <dynamixel_workbench_msgs/DynamixelCommandResponse.h>

static int control_cycle = 100;
static int queue = 1;

ros::ServiceClient client;
dynamixel_workbench_msgs::DynamixelCommand srv;

trajectory_msgs::JointTrajectory traj;

// ros::Publisher joint_traj_pub;

void jointStateCallback(const sensor_msgs::JointStateConstPtr& msg);

#endif
