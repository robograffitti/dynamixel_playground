#!/usr/bin/env python
import rospy
# from dynamixel_workbench_msgs.msg import DynamixelState
from dynamixel_workbench_msgs.msg import DynamixelStateList
from dynamixel_workbench_msgs.srv import DynamixelCommand
from dynamixel_workbench_msgs.srv import DynamixelCommandResponse

# subscribe joint states and call dynamixel command service.
def joint_states_callback(msg):

    print "current master angle: %s" % msg.dynamixel_state[0].present_position

    # service clinent implementation
    rospy.wait_for_service('dynamixel_workbench/dynamixel_command')
    try:
        service = rospy.ServiceProxy('dynamixel_workbench/dynamixel_command', DynamixelCommand)
        response = service('', 2, 'Goal_Position', msg.dynamixel_state[0].present_position)
    except rospy.ServiceException, e:
        print "Service call failed: %s" % e
        return DynamixelCommandResponse

    rate = rospy.Rate(125)
    rate.sleep()

def command_client():


if __name__ == "__main__":

    rospy.init_node('dynamixel_command_client')

    # subscriber
    joint_states_sub = rospy.Subscriber('/dynamixel_workbench/dynamixel_state',
                                        DynamixelStateList, joint_states_callback, queue_size=1)

    # Spin
    rospy.spin()

    # ROS loop
    # rate = rospy.Rate(125)
    # while not rospy.is_shutdown():
    #     rate.sleep()
