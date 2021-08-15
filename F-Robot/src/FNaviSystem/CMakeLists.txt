cmake_minimum_required(VERSION 3.0.2)
project(FNaviSystem)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  serial
  std_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES gSerial
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(NaviSystem
    src/FNaviMain.cpp)
target_link_libraries(NaviSystem
    ${catkin_LIBRARIES})

