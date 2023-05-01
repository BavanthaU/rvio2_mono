
#ifndef ODOMETRY_PUBLISHER_H
#define ODOMETRY_PUBLISHER_H

#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>

class OdometryPublisher
{
public:
  OdometryPublisher();
  void trajectoryCallback(const nav_msgs::Path::ConstPtr& msg);

private:
  ros::NodeHandle nh_;
  ros::Subscriber trajectory_sub_;
  ros::Publisher odometry_pub_;
};

#endif // ODOMETRY_PUBLISHER_H
