cmake_minimum_required (VERSION 2.6)
project (RoboFEI-HT)

add_subdirectory(Dynamixel)
add_subdirectory(Blackboard)
#add_subdirectory(Communication)
#add_subdirectory(Communication/Server)
#add_subdirectory(Communication/Client)
add_subdirectory(Control)
#add_subdirectory(Decision)
#add_subdirectory(Planning)
add_subdirectory(Vision)
#add_subdirectory(Localization)
#add_subdirectory(Management)
add_subdirectory(IMU)

