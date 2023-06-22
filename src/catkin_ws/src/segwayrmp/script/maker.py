import rospy
from visualization_msgs.msg import Marker

def marker_publisher():
    # Initialize the node
    rospy.init_node('marker_publisher_node')

    # Create a publisher
    pub = rospy.Publisher('visualization_marker', Marker, queue_size=10)

    # Create the markers
    marker1 = Marker()
    marker1.header.frame_id = "map"  # or another frame your system uses
    marker1.type = marker1.SPHERE
    marker1.action = marker1.ADD
    marker1.id = 0  # Assign a unique ID to this marker

    # Set the marker parameters
    marker1.pose.position.x = 4.128625570630382
    marker1.pose.position.y = 4.6077443804611375
    marker1.pose.position.z = 0
    marker1.pose.orientation.x = 0.0
    marker1.pose.orientation.y = 0.0
    marker1.pose.orientation.z = 0.0
    marker1.pose.orientation.w = 1.0
    marker1.scale.x = 1.0
    marker1.scale.y = 1.0
    marker1.scale.z = 1.0
    marker1.color.a = 1.0
    marker1.color.r = 0.0
    marker1.color.g = 1.0
    marker1.color.b = 0.0

    marker2 = Marker()
    marker2.header.frame_id = "map"
    marker2.type = marker2.SPHERE
    marker2.action = marker2.ADD
    marker2.id = 1  # Assign a unique ID to this marker

    # Set the marker parameters
    marker2.pose.position.x = -3.363145699387306
    marker2.pose.position.y = 1.882509867731477
    marker2.pose.position.z = 0
    marker2.pose.orientation.x = 0.0
    marker2.pose.orientation.y = 0.0
    marker2.pose.orientation.z = 0.0
    marker2.pose.orientation.w = 1.0
    marker2.scale.x = 1.0
    marker2.scale.y = 1.0
    marker2.scale.z = 1.0
    marker2.color.a = 1.0
    marker2.color.r = 0.0
    marker2.color.g = 1.0
    marker2.color.b = 0.0

    rate = rospy.Rate(10)  # 10 Hz

    while not rospy.is_shutdown():
        # print("pubishing")
        pub.publish(marker1)
        pub.publish(marker2)
        rate.sleep()

if __name__ == '__main__':
    try:
        marker_publisher()
    except rospy.ROSInterruptException:
        pass