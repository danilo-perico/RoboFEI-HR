# @author Isaac Jesus da Silva - ROBOFEI-HT - FEI
# @version V0.0.1
# @created 04/07/2014
# @Modified 02/07/2014 
#
# 
# Para Help acesse http://www.cmake.org/cmake/help/v2.8.0/cmake.html#command:link_directories

include_directories(
  include
  ${RoboFEI-HT_SOURCE_DIR}/Blackboard/include
  ${RoboFEI-HT_SOURCE_DIR}/Dynamixel/include
)

include_directories(include)
add_library(libcontrol SHARED src/andar.cpp src/andar_de_lado.cpp src/andar_marchando.cpp src/chute.cpp src/swing.cpp src/desligar_servos.cpp src/espera_mov.cpp src/greetings.cpp  src/Inverse_Kinematic.cpp src/levantar_de_costas.cpp src/levantar_de_frente.cpp src/roboereto.cpp src/virar.cpp)
install(TARGETS libcontrol DESTINATION ${RoboFEI-HT_BINARY_DIR}/lib)

#link_directories(
#  ${RoboFEI-HT_BINARY_DIR}/Blackboard}
#  ${RoboFEI-HT_BINARY_DIR}/Dynamixel}
#)

#MESSAGE(STATUS "CMAKE_SOURCE_DIR:         " ${RoboFEI-HT_SOURCE_DIR})
#MESSAGE(STATUS "CMAKE_BINARY_DIR:         " ${RoboFEI-HT_BINARY_DIR})


#cria executável
add_executable(control src/control.cpp)

#adiciona as dependências
add_dependencies(control libcontrol dynamixel  dxl_hal blackboard)

target_link_libraries(control libcontrol dynamixel dxl_hal blackboard)

install(TARGETS control DESTINATION ${RoboFEI-HT_BINARY_DIR}/bin)
#install(TARGETS control DESTINATION /usr/local/bin)


