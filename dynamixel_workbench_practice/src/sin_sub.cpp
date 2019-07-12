#include "dynamixel_workbench_practice/sin_sub.h"

void jointStateCallback(const geometry_msgs::PoseStampedConstPtr& msg)
{
  srv.request.command = "";
  srv.request.id = 1;
  srv.request.addr_name = "Goal_Position";
  srv.request.value = msg->pose.position.x;//msg->dynamixel_state[0].present_position;

  if (client.call(srv))
    {
      ROS_INFO("Set Goal_Position : %d", srv.response.comm_result);
    }
  else
    {
      ROS_ERROR("Failed to call service.");
      return;
    }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dynamixel_workbench_master_slave_demo");

  ros::NodeHandle nh;
  client = nh.serviceClient<dynamixel_workbench_msgs::DynamixelCommand>("/dynamixel_workbench/dynamixel_command");

  srv.request.command = "";
  srv.request.id = 1;
  srv.request.addr_name = "Torque_Enable";
  srv.request.value = 1;

  if (client.call(srv))
    {
      ROS_INFO("Torque_Enable : %d", srv.response.comm_result);
    }
  else
    {
      ROS_ERROR("Failed to call service.");
      return 1;
    }

  ros::spinOnce(); // wait for the service request above

  ros::Subscriber joint_sub = nh.subscribe("/mavros/vision_pose/pose", queue, jointStateCallback);

  // infinite loop w/o rate
  // ros::spin();

  ros::Rate loop_rate(control_cycle);
  while (ros::ok())
    {
      ros::spinOnce();
      loop_rate.sleep();
    }


  return 0;
}
