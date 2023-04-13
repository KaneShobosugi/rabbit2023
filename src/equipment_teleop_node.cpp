// KaneShobosugi

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>

#include "can_plugins2/msg/frame.hpp"
#include "can_utils.hpp"

#include "rabbit2023/msg/switch_features.hpp"

#include "key_map.hpp"
#include "switch_feature.hpp"

#define BUTTON_PCS 10

namespace equipment_teleop_node
{
    // struct
    // {
    //     std::array<bool, 3> is_on{};

    // } wheel_lift;
    // class Button_input_reaction
    // {
    // private:
    //     const uint8_t valve_no;
    //     const uint8_t button_id;
    //     const std::string topic_name;

    // public:
    //     void
    //     button_input_reaction(uint8_t &valve_no, uint8_t &button_id, std::string &topic_name)
    //         : valve_no(valve_no){

    //           };
    //     void update(auto &msg, auto &button_input_pre)
    //     {
    //         if (button_input_pre[] != msg->axes[button_map::Y];)
    //         {
    //             button_input_pre[button_map::Y] = msg->axes[button_map::Y];
    //             wheel_lift.is_on[0] = !wheel_lift.is_on[0];

    //         }
    //     }

    // private:
    // }

    class Equipment_teleop_node : public rclcpp::Node
    {
    private:
    public:
        rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
        rclcpp::Publisher<rabbit2023::msg::SwitchFeatures>::SharedPtr sf_pub_;

    public:
        Equipment_teleop_node(const rclcpp::NodeOptions &options) : Node("equipment_teleop_node", options)
        {
            joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
                "joy", 10, std::bind(&Equipment_teleop_node::callback, this, std::placeholders::_1));

            sf_pub_ = this->create_publisher<rabbit2023::msg::SwitchFeatures>("switch_features", 10);

            // Button_input_reaction button_input_reaction();

            RCLCPP_INFO(this->get_logger(), "Equipment_teleop_node has started.");
        }

    private:
        // std::array<bool, BUTTON_PCS> button_input_cur{};
        bool button_input_check(auto &msg, auto &button_input_pre, const auto &button_id)
        {
            if (button_input_pre[button_id] != msg->axes[button_id])
            {
                button_input_pre[button_id] = msg->axes[button_id];
                return true;
            }
            return false;
        };
        void command_proc(auto const &sw_no, auto &command)
        {
            feature_state[sw_no] = !feature_state[sw_no];
            command.feature_no = sw_no;
            command.is_on = feature_state[sw_no];
        };
        std::array<bool, BUTTON_PCS> button_input_pre{};

        std::array<bool, 5> feature_state{};

        void callback(const sensor_msgs::msg::Joy::ConstSharedPtr msg)
        {
            rabbit2023::msg::SwitchFeatures command;
            if (button_input_check(msg, button_input_pre, button_map::Y))
            {
                command_proc(switch_feature::wheel_lift_front, command);
                sf_pub_->publish(command);
            }
            if (button_input_check(msg, button_input_pre, button_map::B))
            {
                command_proc(switch_feature::wheel_lift_middle, command);
                sf_pub_->publish(command);
            }
            if (button_input_check(msg, button_input_pre, button_map::X))
            {
                command_proc(switch_feature::wheel_lift_rear, command);
                sf_pub_->publish(command);
            }
            if (button_input_check(msg, button_input_pre, button_map::Y))
            {
                command_proc(switch_feature::body_lift, command);
                sf_pub_->publish(command);
            }
        };
    };
}
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(equipment_teleop_node::Equipment_teleop_node)
