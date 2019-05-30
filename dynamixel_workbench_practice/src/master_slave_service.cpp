#include "dynamixel_workbench_practice/master_slave_service.h"

void jointStateCallback(const dynamixel_workbench_msgs::DynamixelStateListConstPtr& msg)
{

  srv.request.command = "";
  srv.request.id = 2;
  srv.request.addr_name = "Goal_Position";
  srv.request.value = msg->dynamixel_state[0].present_position;

  if (client.call(srv))
    {
      // ROS_INFO("True (=1) or False (=0) : %d", srv.response.comm_result);
    }
  else
    {
      ROS_ERROR("Failed to call service.");
      return;
    }

  // loop rate regulation
  // ros::Rate loop_rate(control_cycle);
  // loop_rate.sleep(); // wait for dynamixel_command service.
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

  ros::spinOnce(); // wait for the service request above

  ros::Subscriber joint_sub = nh.subscribe("/dynamixel_workbench/dynamixel_state", queue, jointStateCallback);

  // infinite loop w/o rate
  ros::spin();

  // infinite loop w/ rate
  // ros::Rate loop_rate(control_cycle);
  // while (ros::ok())
  //   {
  //     ros::spinOnce();
  //     loop_rate.sleep();
  //   }

  return 0;
}
