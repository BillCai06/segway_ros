cmake_minimum_required(VERSION 2.8.3)
project(segwayrmp)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -funroll-loops -fpic -Wall -Wno-sign-compare -Werror=return-type -g")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -fpic")

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  rospy
  std_msgs
  tf
  nav_msgs
  sensor_msgs
  segway_msgs
)

catkin_package(
  CATKIN_DEPENDS
  message_runtime
)


include_directories(
  include ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS}

)



 add_executable(ChassisResponseTest
         tools/ChassisResponseTest.cpp
         )
 target_link_libraries(ChassisResponseTest
         ${catkin_LIBRARIES})


add_executable(drive_segway_sample
         tools/drive_segway_sample.cpp
         )
 target_link_libraries(drive_segway_sample
         ${catkin_LIBRARIES})


add_executable(SmartCar
  src/SmartCar.cpp
  src/robot.cpp
  src/Ge_encoder_odometry.cpp

)
add_executable(vel_router
 src/vel_router.cpp)
target_link_libraries(vel_router ${catkin_LIBRARIES})

add_executable(odom_base_link_tf_node src/odom_base_link_tf_node.cpp)
target_link_libraries(odom_base_link_tf_node ${catkin_LIBRARIES})


message( "project source dir " ${PROJECT_SOURCE_DIR} )
add_dependencies(SmartCar ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
  set(LIBRARY_NAME "${PROJECT_SOURCE_DIR}/lib/libctrl_arm64-v8a.so")
else()
  set(LIBRARY_NAME "${PROJECT_SOURCE_DIR}/lib/libctrl_x86_64.so")
endif()


target_link_libraries(SmartCar
  ${catkin_LIBRARIES} 
  #"~/catkin_ws/src/RosCode/segwayrmp/lib/libgxctrl_arm64-v8a.so"
  ${PROJECT_SOURCE_DIR} ${LIBRARY_NAME}
  #${PROJECT_SOURCE_DIR}/lib/libctrl_x86_64.so
)

