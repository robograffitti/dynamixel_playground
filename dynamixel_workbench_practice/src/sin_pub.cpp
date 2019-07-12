#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "offb_node_mavros1");
  ros::NodeHandle nh;

  ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
    ("mavros/vision_pose/pose", 1);

  //the setpoint publishing rate MUST be faster than 2Hz
  ros::Rate rate(50);

  geometry_msgs::PoseStamped pose;
  pose.header.stamp = ros::Time::now();
  pose.pose.position.x = 2048;
  pose.pose.position.y = 0;
  pose.pose.position.z = 1.00;
  pose.pose.orientation.x = 0;
  pose.pose.orientation.y = 0;
  pose.pose.orientation.z = 0;
  pose.pose.orientation.w = 1.00;

  int i = 0;

  while(ros::ok()){
    pose.header.stamp = ros::Time::now();
    pose.pose.position.x = 2048 + 2048*sin(0.01*i);
    local_pos_pub.publish(pose);
    i++;

    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}
