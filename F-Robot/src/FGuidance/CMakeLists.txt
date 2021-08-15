cmake_minimum_required(VERSION 3.0.2)
project(FGuidance)


add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  serial
  std_msgs
  uSerial
  rospy
)

#catkin_install_python(PROGRAMS scripts/talker.py
#  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)

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

add_executable(${PROJECT_NAME}
    src/telemetry.cpp
    src/FGuideMain.cpp)
target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES})
