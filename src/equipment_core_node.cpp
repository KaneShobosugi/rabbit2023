// KaneShobosugi

#include <rclcpp/rclcpp.hpp>

#include "can_plugins2/msg/frame.hpp"
#include "can_utils.hpp"

// #include "rabbit2023/msg/switch_features.hpp"

namespace equipment_core_node
{
    class A{
        A(&pub)
    }
    class Equipment_core_node : public rclcpp::Node
    {
    private:
    public:
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr wheel_lift_front_sub_;
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr wheel_lift_middle_sub_;
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr wheel_lift_rear_sub_;
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr body_lift_sub_;
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr body_expansion_sub_;

        // rclcpp::Subscription;
        rclcpp::Publisher<can_plugins2::msg::Frame>::SharedPtr can_pub_;

    public:
        Equipment_core_node(const rclcpp::NodeOptions &options) : Node("equipment_core_node", options)
        {

            wheel_lift_front_sub_ = this->create_subscription<std_msgs::msg::Bool>("wheel_lift_front",10,std::bind(&Equipment_core_node::callback))

            RCLCPP_INFO(this->get_logger(), "Equipment_core_node has started.");
        }

    private:
        void callback(const msg){

        };
    };
}
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(equipment_core_node::Equipment_core_node)
