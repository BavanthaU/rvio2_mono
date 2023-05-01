#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>

class OdometryPublisher
{
public:
  OdometryPublisher()
  {
    // Subscribe to trajectory topic
    trajectory_sub_ = nh_.subscribe("/rvio2/trajectory", 1, &OdometryPublisher::trajectoryCallback, this);

    // Publish odometry on separate topic
    odometry_pub_ = nh_.advertise<nav_msgs::Odometry>("/camera_color_optical_frame/odom", 1);
  }

  void trajectoryCallback(const nav_msgs::Path::ConstPtr& msg)
  {
    // Get the most recent pose from the trajectory
    const auto& pose = msg->poses.back();

    // Create odometry message
    nav_msgs::Odometry odom;
    odom.header.stamp = pose.header.stamp;
    odom.header.frame_id = "world";
    odom.child_frame_id = "camera_color_optical_frame";
    odom.pose.pose = pose.pose;

    // Publish odometry message
    odometry_pub_.publish(odom);
  }

private:
  ros::NodeHandle nh_;
  ros::Subscriber trajectory_sub_;
  ros::Publisher odometry_pub_;
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "odometry_publisher");

  OdometryPublisher publisher;

  ros::spin();

  return 0;
}

