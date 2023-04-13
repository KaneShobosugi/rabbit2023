// KaneShobosugi
// compatible with joypads on X-Mode.

#include <rclcpp/rclcpp.hpp>

namespace button_map
{
    enum : uint8_t
    {
        A,
        B,
        X,
        Y,
        LB,
        RB,
        BACK,
        START,
        CENTER,
        LEFT_STICK,
        RIGHT_STICK,
    };
}
namespace axis_map
{
    enum : uint8_t
    {
        LEFT_STICK_H,
        LEFT_STICK_V,
        LEFT_TRIGGER,
        RIGHT_STICK_H,
        RIGHT_STICK_V,
        RIGHT_TRIGGER,
        CROSS_H,
        CROSS_V,
    };
}