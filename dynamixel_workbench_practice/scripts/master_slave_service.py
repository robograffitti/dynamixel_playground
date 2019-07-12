#!/usr/bin/env python
import rospy
# from dynamixel_workbench_msgs.msg import DynamixelState
from dynamixel_workbench_msgs.msg import DynamixelStateList
from dynamixel_workbench_msgs.srv import DynamixelCommand
from dynamixel_workbench_msgs.srv import DynamixelCommandResponse

control_cycle = 125 # use if willing to regulate control cycle.
queue = 1
id_1 = 7 # 1
id_2 = 8 # 2

# subscribe joint states and call dynamixel command service.
def joint_states_callback(msg):

    # print "current master angle: %s" % msg.dynamixel_state[0].present_position

    # service clinent implementation
    rospy.wait_for_service('dynamixel_workbench/dynamixel_command')
    try:
        service = rospy.ServiceProxy('dynamixel_workbench/dynamixel_command', DynamixelCommand)
        response = service('', id_2, 'Goal_Position', msg.dynamixel_state[0].present_position)
    except rospy.ServiceException, e:
        print "Service call failed: %s" % e
        return DynamixelCommandResponse

    # loop w/ rate
    # rate = rospy.Rate(control_cycle)
    # rate.sleep()

def command_client():

    # initialize node
    rospy.init_node('dynamixel_command_client')

    # turn off torque of master (id=1)
    rospy.wait_for_service('dynamixel_workbench/dynamixel_command')

    try:
        service = rospy.ServiceProxy('dynamixel_workbench/dynamixel_command', DynamixelCommand)
        response = service('', id_1, 'Torque_Enable', 0)
        print response.comm_result
    except rospy.ServiceException, e:
        print "Service call failed: %s" % e
        return DynamixelCommandResponse

    # subscriber
    joint_states_sub = rospy.Subscriber('/dynamixel_workbench/dynamixel_state', DynamixelStateList,
                                        joint_states_callback, queue_size=queue)

    # ROS loop w/o rate
    rospy.spin()

    # ROS loop w/ rate
    # rate = rospy.Rate(control_cycle)
    # while not rospy.is_shutdown():
    #     rate.sleep()

if __name__ == "__main__":
    command_client()
