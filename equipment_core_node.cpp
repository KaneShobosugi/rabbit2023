// KaneShobosugi

#include <rclcpp/rclcpp.hpp>

#include "can_plugins2/msg/frame.hpp"
#include "can_utils.hpp"

#include "rabbit2023/msg/switch_features.hpp"
#include "rabbit2023/msg/to_solenoid_valve.hpp"
#include "include/switch_feature.hpp"

namespace equipment_core_node
{

    class Equipment_core_node : public rclcpp::Node
    {
    private:
    public:
        rclcpp::Subscription<rabbit2023::msg::SwitchFeatures>::SharedPtr sf_sub_;
        // rclcpp::Subscription;
        rclcpp::Publisher<can_plugins2::msg::Frame>::SharedPtr can_pub_;
        rclcpp::Publisher<rabbit2023::msg::ToSolenoidValve>::SharedPtr sv_pub_;

    public:
        Equipment_core_node(const rclcpp::NodeOptions &options) : Node("equipment_core_node", options)
        {

            sf_sub_ = this->create_subscription<rabbit2023::msg::SwitchFeatures>("switch_features", 10, std::bind(&Equipment_core_node::callback, this, std::placeholders::_1));
            can_pub_ = this->create_publisher<can_plugins2::msg::Frame>("can_tx", 10);
            sv_pub_ = this->create_publisher<rabbit2023::msg::ToSolenoidValve>("to_solenoid_valve", 10);

            RCLCPP_INFO(this->get_logger(), "Equipment_core_node has started.");
        }

    private:
        void callback(const rabbit2023::msg::SwitchFeatures &msg)
        {
            uint8_t feature_no{msg.feature_no};
            bool is_on{msg.is_on};

            rabbit2023::msg::ToSolenoidValve frame;

            if (feature_no == switch_feature::wheel_lift_front)
            {
                frame.port_no = feature_no;
                frame.is_on = is_on;
                sv_pub_->publish(frame);
            }
            if (feature_no == switch_feature::wheel_lift_middle)
            {
                frame.port_no = feature_no;
                frame.is_on = is_on;
                sv_pub_->publish(frame);
            }
            if (feature_no == switch_feature::wheel_lift_rear)
            {
                frame.port_no = feature_no;
                frame.is_on = is_on;
                sv_pub_->publish(frame);
            }
            if (feature_no == switch_feature::body_lift)
            {
                frame.port_no = feature_no;
                frame.is_on = is_on;
                sv_pub_->publish(frame);
            }
            if (feature_no == switch_feature::body_expansion)
            {
                frame.port_no = feature_no;
                frame.is_on = is_on;
                sv_pub_->publish(frame);
                // assistance by wheels
            }
        };
    };
}
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(equipment_core_node::Equipment_core_node)
