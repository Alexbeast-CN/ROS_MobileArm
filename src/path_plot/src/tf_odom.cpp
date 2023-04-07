#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "nav_msgs/msg/odometry.hpp"
#include <tf2/convert.h>
#include <tf2/LinearMath/Quaternion.h>
#include <geometry_msgs/msg/quaternion.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

using namespace std::chrono_literals;

  double wheel_separation = 0.18;
  double x = 0.0;
  double y = 0.0;
  double left_wheel_est_vel = 0.0;
  double right_wheel_est_vel = 0.0;
  double vth = 0.0;

// void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg)
// {
//   vx = msg->linear.x;
//   vy = msg->linear.y;
//   vth = msg->angular.z;
// }

void jointVelCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
{
    left_wheel_est_vel = msg->velocity[0];
    right_wheel_est_vel = msg->velocity[2];
}

int main(int argc, char** argv){
  rclcpp::init(argc, argv);

  auto node = std::make_shared<rclcpp::Node>("odometry_publisher");
  auto odom_pub = node->create_publisher<nav_msgs::msg::Odometry>("odom", 50);
  tf2_ros::TransformBroadcaster odom_broadcaster(node);

  // auto cmd_vel_sub = node->create_subscription<geometry_msgs::msg::Twist>(
  //   "/mobile_base_controller/cmd_vel_unstamped", 10, cmdVelCallback);

    auto joint_vel_sub = node->create_subscription<sensor_msgs::msg::JointState>(
    "/joint_states", 10, jointVelCallback);

  double x = 0.0;
  double y = 0.0;
  double th = 0.0;

  auto current_time = node->now();
  auto last_time = node->now();

  rclcpp::Rate r(30.0);
  while(rclcpp::ok()){

    rclcpp::spin_some(node);               // check for incoming messages
    current_time = node->now();

    //compute odometry in a typical way given the velocities of the robot
    double dt = (current_time - last_time).seconds();
    double linear = (right_wheel_est_vel + left_wheel_est_vel) / 2;
    double angular = (right_wheel_est_vel - left_wheel_est_vel) / wheel_separation;

    double delta_x = linear * cos(th)  * dt;
    double delta_y = linear * sin(th)  * dt;
    double delta_th = angular * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::msg::Quaternion odom_quat;
    tf2::Quaternion quat;
    quat.setRPY(0, 0, th);
    odom_quat = tf2::toMsg(quat);

    //first, we'll publish the transform over tf
    geometry_msgs::msg::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::msg::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = linear;
    odom.twist.twist.linear.y = 0;
    odom.twist.twist.angular.z = vth;

    // odom.child_frame_id = "base_link";
    // odom.twist.twist.linear.x = vx;
    // odom.twist.twist.linear.y = vy;
    // odom.twist.twist.angular.z = vth;

    //publish the message
    odom_pub->publish(odom);

    last_time = current_time;
    r.sleep();
  }
  rclcpp::shutdown();
  return 0;
}