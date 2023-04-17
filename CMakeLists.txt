cmake_minimum_required(VERSION 3.8)
project(rabbit2023)

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(can_plugins2 REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/ToSolenoidValve.msg"
  "msg/SwitchFeatures.msg"
  DEPENDENCIES std_msgs
)



include_directories(
  include
  ${can_plugins2_INCLUDE_DIRS}
)

# check if ROS_DISTRO is foxy or humble
if($ENV{ROS_DISTRO} STREQUAL "humble")
  ament_export_dependencies(rosidl_default_runtime)
  rosidl_get_typesupport_target(cpp_typesupport_target
    ${PROJECT_NAME} "rosidl_typesupport_cpp"
  )
endif()

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_library(solenoid_valve_driver_node SHARED
  solenoid_valve_driver_node.cpp
)
add_library(equipment_teleop_node SHARED
  equipment_teleop_node.cpp
)
add_library(equipment_core_node SHARED
  equipment_core_node.cpp
)




 # check if ROS_DISTRO is foxy or humbles
# if($ENV{ROS_DISTRO} STREQUAL "humble")
target_link_libraries(solenoid_valve_driver_node  "${cpp_typesupport_target}")
target_link_libraries(equipment_teleop_node "${cpp_typesupport_target}")
target_link_libraries(equipment_core_node "${cpp_typesupport_target}")
  
# elseif($ENV{ROS_DISTRO} STREQUAL "foxy")
#   rosidl_target_interfaces(
#     solenoid_valve_driver_node
#     equipment_teleop_node

#   ${PROJECT_NAME} "rosidl_typesupport_cpp")
# endif()


ament_target_dependencies(solenoid_valve_driver_node
  rclcpp
  rclcpp_components
  std_msgs
  sensor_msgs
  can_plugins2
)
ament_target_dependencies(equipment_teleop_node
  rclcpp
  rclcpp_components
  std_msgs
  sensor_msgs
  can_plugins2
)
ament_target_dependencies(equipment_core_node
  rclcpp
  rclcpp_components
  std_msgs
  sensor_msgs
  can_plugins2
)

rclcpp_components_register_nodes(
  solenoid_valve_driver_node "solenoid_valve_driver_node::Solenoid_valve_driver_node"
)
rclcpp_components_register_nodes(
  equipment_teleop_node "equipment_teleop_node::Equipment_teleop_node"
)
rclcpp_components_register_nodes(
  equipment_core_node "equipment_core_node::Equipment_core_node"
)


install(TARGETS solenoid_valve_driver_node equipment_teleop_node equipment_core_node 
  DESTINATION lib
)
# install(TARGETS  equipment_teleop_node
#   DESTINATION lib
# )


# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   # the following line skips the linter which checks for copyrights
#   # comment the line when a copyright and license is added to all source files
#   set(ament_cmake_copyright_FOUND TRUE)
#   # the following line skips cpplint (only works in a git repo)
#   # comment the line when this package is in a git repo and when
#   # a copyright and license is added to all source files
#   set(ament_cmake_cpplint_FOUND TRUE)
#   ament_lint_auto_find_test_dependencies()
# endif()

ament_package()
