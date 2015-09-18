#include <dynamixel.h>
#include <math.h>
#include <cmath>
#include <unistd.h>

#define VEL 200 // Define a velocidade
#define VEL_ANDAR 400 //define velocidade para andar
#define VEL_ANDAR2 80

void calling()
{
    for(int x=3; x<=8; x++)
       dxl_write_word( x, 34, 1023); // Seta o torque dos braços no máximo

    dxl_write_word(8, MOVING_SPEED, 300);
    dxl_write_word(8, P_GOAL_POSITION_L, 91);//478
    dxl_write_word(5, MOVING_SPEED, 300);
    dxl_write_word(5, P_GOAL_POSITION_L, 974);
    espera_mov();
   for(int i=1;i<4;i++)
    {
    dxl_write_word(7, MOVING_SPEED, 300);
    dxl_write_word(7, P_GOAL_POSITION_L, 554);
    dxl_write_word(4, MOVING_SPEED, 300);
    dxl_write_word(4, P_GOAL_POSITION_L, 456);

    espera_mov();
    dxl_write_word(4, MOVING_SPEED, 300);
    dxl_write_word(4, P_GOAL_POSITION_L, 400);
    dxl_write_word(7, MOVING_SPEED, 300);
    dxl_write_word(7, P_GOAL_POSITION_L, 600);
    espera_mov();

    }

    for(int x=3; x<=8; x++)
       dxl_write_word( x, 34, 200); // Seta os braços com baixo torque
}


void greetings()
{
    for(int x=3; x<=8; x++)
       dxl_write_word( x, 34, 1023); // Seta o torque dos braços no máximo

    dxl_write_word(3, MOVING_SPEED, 200);
    dxl_write_word(3, P_GOAL_POSITION_L, 456);
    dxl_write_word(4, MOVING_SPEED, 200);
    dxl_write_word(4, P_GOAL_POSITION_L, 417);
    dxl_write_word(5, MOVING_SPEED, 400);
    dxl_write_word(5, P_GOAL_POSITION_L, 900);

    dxl_write_word(6, MOVING_SPEED, 200);
    dxl_write_word(6, P_GOAL_POSITION_L, 546-22);
    dxl_write_word(7, MOVING_SPEED, 200);
    dxl_write_word(7, P_GOAL_POSITION_L, 600+34);
    dxl_write_word(8, MOVING_SPEED, 400);
    dxl_write_word(8, P_GOAL_POSITION_L, 682-550);

espera_mov();


    for(int i=1;i<4;i++)
    {
    dxl_write_word(3, MOVING_SPEED, 200);
   dxl_write_word(3, P_GOAL_POSITION_L, 456);
    dxl_write_word(6, MOVING_SPEED, 200);
    dxl_write_word(6, P_GOAL_POSITION_L, 546-22);
    espera_mov();
    dxl_write_word(3, MOVING_SPEED, 200);
    dxl_write_word(3, P_GOAL_POSITION_L, 556);
     dxl_write_word(6, MOVING_SPEED, 200);
    dxl_write_word(6, P_GOAL_POSITION_L, 456-22);
    espera_mov();
    }	
    robo_ereto();
    for(int x=3; x<=8; x++)
       dxl_write_word( x, 34, 200); // Seta os braços com baixo torque
}


//int braco = 300;
