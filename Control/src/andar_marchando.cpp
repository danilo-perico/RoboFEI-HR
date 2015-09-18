#include <dynamixel.h>
#include <unistd.h>


//============================================================================================
//--------------------------------------------------------------------------------------------
void andar_marchando()
{
robo_ereto();


//desligar_servos();
/*
dxl_write_word(3, MOVING_SPEED, 300);
dxl_write_word(3, P_GOAL_POSITION_L, 821);

dxl_write_word(4, MOVING_SPEED, 300);
dxl_write_word(4, P_GOAL_POSITION_L, 452);

dxl_write_word(5, MOVING_SPEED, 300);
dxl_write_word(5, P_GOAL_POSITION_L, 256);

dxl_write_word(6, MOVING_SPEED, 300);
dxl_write_word(6, P_GOAL_POSITION_L, 194);

dxl_write_word(7, MOVING_SPEED, 300);
dxl_write_word(7, P_GOAL_POSITION_L, 555);

dxl_write_word(8, MOVING_SPEED, 300);
dxl_write_word(8, P_GOAL_POSITION_L, 776);
*/


for(int i=0;i<5;i++)
{
    //Inclina para direta e sobre pe esquerdo//
    inverse_kinematic_right_leg(0,0.03,0,400);
    inverse_kinematic_left_leg(0,0.03,0,400);
    usleep(200000);

    inverse_kinematic_right_leg(0,0.01,0,400);
    inverse_kinematic_left_leg(0,0.01,0,400);
    usleep(200000);
}

inverse_kinematic_right_leg(0,0,0,200);
inverse_kinematic_left_leg(0,0,0,200);
usleep(200000);
}
