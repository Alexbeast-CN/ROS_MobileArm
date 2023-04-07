#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/msg/point.hpp"
#include "visualization_msgs/msg/marker.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("showpath");
  auto marker_pub = node->create_publisher<visualization_msgs::msg::Marker>("visualization_marker", 10);
  rclcpp::Rate r(10);

  rclcpp::Clock::SharedPtr clock = std::make_shared<rclcpp::Clock>(RCL_ROS_TIME);
  tf2_ros::Buffer tf_buffer(clock, tf2::Duration(tf2::BUFFER_CORE_DEFAULT_CACHE_TIME));


  // tf2_ros::Buffer tf_buffer;
  tf2_ros::TransformListener tf_listener(tf_buffer);

  visualization_msgs::msg::Marker points, line_strip;
  points.header.frame_id = line_strip.header.frame_id = "odom";
  points.ns = line_strip.ns = "showpath";
  points.action = line_strip.action = visualization_msgs::msg::Marker::ADD;
  points.pose.orientation.w = line_strip.pose.orientation.w = 1.0;

  points.id = 0;
  line_strip.id = 1;

  points.type = visualization_msgs::msg::Marker::POINTS;
  line_strip.type = visualization_msgs::msg::Marker::LINE_STRIP;

  line_strip.scale.x = 0.05;

  line_strip.color.b = 1.0;
  line_strip.color.a = 1.0;

  float x(0), y(0);
  int cnt(0);

  while (rclcpp::ok())
  {
    geometry_msgs::msg::TransformStamped transform;
    try{
      transform = tf_buffer.lookupTransform("odom", "base_link", tf2::TimePointZero);
    }
    catch (tf2::TransformException &ex){
      RCLCPP_ERROR(node->get_logger(), "%s", ex.what());
      rclcpp::sleep_for(1s);
      continue;
    }
    x = transform.transform.translation.x;
    y = transform.transform.translation.y;

    geometry_msgs::msg::Point p;
    p.x = x;
    p.y = y;
    p.z = 0.1;

    if (cnt > 1) {line_strip.points.push_back(p);}
    else {cnt++;}

    marker_pub->publish(line_strip);

    r.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
