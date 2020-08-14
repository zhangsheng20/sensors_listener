#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

/**
 * This tutorial demonstrates simple receipt of IMU sensor data over the ROS system.
 */

/**
 * Callback function executes when new topic data comes.
 * Task of the callback function is to print data to screen.
 */


void stampCompare(ros::Time Time_in,bool IsUgv)
{
  static ros::Time ScanTime;
  static ros::Time UgvOdomTime;
  if(IsUgv==1)
  {
    UgvOdomTime=Time_in;
  }  
  else
  {
    ScanTime=Time_in;
  }
  ros::Duration TimeGap=UgvOdomTime-ScanTime;
 
  ROS_INFO("TimeGap Seq: [%f]",  TimeGap.toSec());

}

void imu_chatterCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
  //ROS_INFO("Imu Seq: [%d]", msg->header.seq);
}


void scan_chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  //ROS_INFO("Scan Seq: [%d]", msg->header.seq);
  stampCompare(msg->header.stamp,0);
}


void Odom_chatterCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  //ROS_INFO("UgvOdom Seq: [%d]", msg->header.seq);
  stampCompare(msg->header.stamp,1);
}

int main(int argc, char **argv)
{
 
 
  ros::init(argc, argv, "imu_listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/mavros/imu/data", 1000, imu_chatterCallback);
  ros::Subscriber sub2 = n.subscribe("/scan", 1000, scan_chatterCallback);
  ros::Subscriber sub3 = n.subscribe("/UgvOdomTopic", 1000, Odom_chatterCallback);

  ros::spin();

  return 0;
}
