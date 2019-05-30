#!/usr/bin/env python
import rospy

from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint
from dynamixel_workbench_msgs.srv import DynamixelCommand
from dynamixel_workbench_msgs.srv import DynamixelCommandResponse

# constant
control_cycle = 100

# shared msg data
traj = JointTrajectory()

# subscribe joint states and call dynamixel command service.
def joint_states_callback(msg):

    position = 2 * msg.position[0] - msg.position[1]
    # print "%s" % position
    # print "pan: %s" % msg.position[0]
    # print "tilt: %s" % msg.position[1]

    traj.header.seq = msg.header.seq
    traj.header.stamp = rospy.Time.now()
    traj.header.frame_id = msg.header.frame_id

    traj.joint_names = range(1)
    traj.joint_names = ['tilt']

    point = JointTrajectoryPoint()
    point.positions = range(1)
    point.positions = [position]
    # point.time_from_start = rospy.Duration.from_sec(0.008)
    point.time_from_start = rospy.Duration.from_sec(0.010)

    traj.points = range(1)
    traj.points = [point]

def joint_traj_handler():
    # initialize node
    rospy.init_node('dynamixel_command_client')

    # turn off torque of master (id=1)
    rospy.wait_for_service('dynamixel_workbench/dynamixel_command')
    try:
        service = rospy.ServiceProxy('/dynamixel_workbench/dynamixel_command', DynamixelCommand)
        response = service('', 1, 'Torque_Enable', 0)
        print response.comm_result
    except rospy.ServiceException, e:
        print "Service call failed: %s" % e
        return DynamixelCommandResponse

    # subscriber
    joint_states_sub = rospy.Subscriber('/dynamixel_workbench/joint_states', JointState, joint_states_callback, queue_size=1)

    # publisher
    joint_traj_pub = rospy.Publisher('/dynamixel_workbench/joint_trajectory', JointTrajectory, queue_size=1)

    # ROS loop w/ rate
    rate = rospy.Rate(control_cycle)
    while not rospy.is_shutdown():
        # print "loop"
        joint_traj_pub.publish(traj)
        rate.sleep()

if __name__ == "__main__":
    try:
        joint_traj_handler()
    except rospy.ROSInterruptException: pass
