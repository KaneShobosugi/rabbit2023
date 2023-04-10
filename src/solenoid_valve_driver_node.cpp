// KaneShobosugi

#include <rclcpp/rclcpp.hpp>

#include "can_plugins2/msg/frame.hpp"
#include "can_utils.hpp"

#include "rabbit2023/solenoid_valve_driver_node.hpp"
#include "rabbit2023/msg/to_solenoid_valve.hpp"

#define MAX_PORT_PCS 10

namespace solenoid_valve_driver_node
{
    class Solenoid_valve_driver_node : public rclcpp::Node
    {
    private:
        std::array<bool, MAX_PORT_PCS> is_on{};

    public:
        rclcpp::Subscription<rabbit2023::msg::ToSolenoidValve>::SharedPtr sub_;
        rclcpp::Publisher<can_plugins2::msg::Frame>::SharedPtr can_pub_;

    public:
        Solenoid_valve_driver_node(const rclcpp::NodeOptions &options) : Node("solenoid_valve_driver_node", options)
        {
            sub_ = this->create_subscription<rabbit2023::msg::ToSolenoidValve>("to_solenoid_valve", 10, std::bind(&Solenoid_valve_driver_node::callback, this,std::placeholders::_1));
            can_pub_ = this->create_publisher<can_plugins2::msg::Frame>("can_tx", 10);
            RCLCPP_INFO(this->get_logger(), "Solenoid_valve_driver_node started.");
        }

    private:
        void callback(const rabbit2023::msg::ToSolenoidValve){

        };
    };
}
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(solenoid_valve_driver_node::Solenoid_valve_driver_node)
