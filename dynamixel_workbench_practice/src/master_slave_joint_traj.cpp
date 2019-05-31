#include "dynamixel_workbench_practice/master_slave_joint_traj.h"

void jointStateCallback(const sensor_msgs::JointStateConstPtr& msg)
{
  double position = 2 * msg->position[0] - msg->position[1];

  traj.header.seq = msg->header.seq;
  traj.header.stamp = ros::Time::now();
  traj.header.frame_id = msg->header.frame_id;

  traj.joint_names.resize(1);
  // traj.joint_names.push_back("tilt");
  traj.joint_names[0] = "tilt";

  trajectory_msgs::JointTrajectoryPoint point;

  point.positions.resize(1);
  // point.positions.push_back(position);
  point.positions[0] = position;
  point.time_from_start = ros::Duration(1.0 / control_cycle);

  traj.points.resize(1);
  traj.points[0] = point;

  ROS_INFO("master : %f, slave : %f", msg->position[0], msg->position[1]);
  ROS_INFO("position : %f", position);

  ros::Rate loop_rate(control_cycle);
  loop_rate.sleep();

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dynamixel_workbench_master_slave_demo");

  ros::NodeHandle nh;
  client = nh.serviceClient<dynamixel_workbench_msgs::DynamixelCommand>("/dynamixel_workbench/dynamixel_command");

  srv.request.command = "";
  srv.request.id = 1;
  srv.request.addr_name = "Torque_Enable";
  srv.request.value = 0;

  if (client.call(srv))
    {
      ROS_INFO("True (=1) or False (=0) : %d", srv.response.comm_result);
    }
  else
    {
      ROS_ERROR("Failed to call service.");
      return 1;
    }

  // ros::spinOnce(); // wait for the service request above
  ros::Publisher joint_traj_pub = nh.advertise<trajectory_msgs::JointTrajectory>("/dynamixel_workbench/joint_trajectory", queue);
  ros::Subscriber joint_sub = nh.subscribe("/dynamixel_workbench/joint_states", queue, jointStateCallback);

  // wait
  // ros::spinOnce();

  // infinite loop w/ rate
  ros::Rate loop_rate(control_cycle);
  while (ros::ok())
    {
      joint_traj_pub.publish(traj);
      ros::spinOnce();
      loop_rate.sleep();
    }

  return 0;
}
