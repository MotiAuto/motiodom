#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

#include <chrono>
#include <string>

#include "ekf_utils.hpp"
#include "matrix_utils.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

namespace motiodom
{
    class MotiOdom : public rclcpp::Node
    {
        public:
        explicit MotiOdom(const rclcpp::NodeOptions & node_options);

        private:
        void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg);
        void magnet_callback(const geometry_msgs::msg::Vector3::SharedPtr msg);
        void axis6_callback();
        void axis9_callback();

        rclcpp::Subscription<geometry_msgs::msg::Vector3>::SharedPtr magnetic_field_subscriber_;
        rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber_;
        rclcpp::TimerBase::SharedPtr timer_;
        std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
        bool enable_magnet_, imu_flag_, mag_flag_, enable_position_;
        int delta_time_;
        float delta_float_;
        std::string frame_id_, child_id_;

        std::shared_ptr<AccelAngularEKF<float>> ekf6_;

        sensor_msgs::msg::Imu::SharedPtr get_imu_;
        geometry_msgs::msg::Vector3::SharedPtr get_magnet_;
    };
}

#endif