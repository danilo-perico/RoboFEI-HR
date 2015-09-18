#include <dynamixel.h>
#include <unistd.h>


//============================================================================================
//--------------------------------------------------------------------------------------------
void levantar_de_frente()
{
robo_ereto();
espera_mov_levantar();
for(int x=3; x<=8; x++)
    dxl_write_word( x, 34, 1023); // Inicia os braços com alto torque

/*
dxl_write_word(4, MOVING_SPEED, 300);
dxl_write_word(4, P_GOAL_POSITION_L, 715);

dxl_write_word(7, MOVING_SPEED, 300);
dxl_write_word(7, P_GOAL_POSITION_L, 325);
espera_mov_levantar();

dxl_write_word(5, MOVING_SPEED, 300);
dxl_write_word(5, P_GOAL_POSITION_L, 928);

dxl_write_word(8, MOVING_SPEED, 300);
dxl_write_word(8, P_GOAL_POSITION_L, 117);
espera_mov_levantar();

dxl_write_word(4, MOVING_SPEED, 300);
dxl_write_word(4, P_GOAL_POSITION_L, 360);

dxl_write_word(7, MOVING_SPEED, 300);
dxl_write_word(7, P_GOAL_POSITION_L, 651);

dxl_write_word(3, MOVING_SPEED, 300);
dxl_write_word(3, P_GOAL_POSITION_L, 945);

dxl_write_word(6, MOVING_SPEED, 300);
dxl_write_word(6, P_GOAL_POSITION_L, 94);

dxl_write_word(5, MOVING_SPEED, 300);
dxl_write_word(5, P_GOAL_POSITION_L, 606);

dxl_write_word(8, MOVING_SPEED, 300);
dxl_write_word(8, P_GOAL_POSITION_L, 404);
*/

dxl_write_word(5, MOVING_SPEED, 300);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]- 270);

dxl_write_word(8, MOVING_SPEED, 300);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7] + 270);

dxl_write_word(3, MOVING_SPEED, 400);
dxl_write_word(3, P_GOAL_POSITION_L,StandupPos[2]+500);//550

dxl_write_word(6, MOVING_SPEED, 400);
dxl_write_word(6, P_GOAL_POSITION_L,StandupPos[5]-500);//550

//espera_mov_levantar();
/*
dxl_write_word(10, MOVING_SPEED, 300);
dxl_write_word(10, P_GOAL_POSITION_L, 873);//873

dxl_write_word(12, MOVING_SPEED, 300);
dxl_write_word(12, P_GOAL_POSITION_L, 155);//155

dxl_write_word(14, MOVING_SPEED, 300);
dxl_write_word(14, P_GOAL_POSITION_L, 606);//606

dxl_write_word(16, MOVING_SPEED, 300);
dxl_write_word(16, P_GOAL_POSITION_L, 150);//150

dxl_write_word(18, MOVING_SPEED, 300);
dxl_write_word(18, P_GOAL_POSITION_L, 20+48);//68

dxl_write_word(20, MOVING_SPEED, 300);
dxl_write_word(20, P_GOAL_POSITION_L, 401);//401

*/
dxl_write_word(10, MOVING_SPEED, 300);
dxl_write_word(10, P_GOAL_POSITION_L, StandupPos[9] + 341);//873

dxl_write_word(12, MOVING_SPEED, 300);
dxl_write_word(12, P_GOAL_POSITION_L, StandupPos[11] - 426);//155

dxl_write_word(14, MOVING_SPEED, 300);
dxl_write_word(14, P_GOAL_POSITION_L, StandupPos[13] - 200);//606

dxl_write_word(16, MOVING_SPEED, 300);
dxl_write_word(16, P_GOAL_POSITION_L, StandupPos[15] - 337);//150

dxl_write_word(18, MOVING_SPEED, 300);
dxl_write_word(18, P_GOAL_POSITION_L, StandupPos[17] - 424);//68

dxl_write_word(20, MOVING_SPEED, 300);
dxl_write_word(20, P_GOAL_POSITION_L, StandupPos[19] + 182);//401

espera_mov_levantar();

dxl_write_word(5, MOVING_SPEED, 100);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]+ 50);

dxl_write_word(8, MOVING_SPEED, 100);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7] - 50);

espera_mov_levantar();

dxl_write_word(5, MOVING_SPEED, 200);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]+ 160);

dxl_write_word(8, MOVING_SPEED, 200);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7] - 160);

dxl_write_word(3, MOVING_SPEED, 400);
dxl_write_word(3, P_GOAL_POSITION_L,StandupPos[2]+0);

dxl_write_word(6, MOVING_SPEED, 400);
dxl_write_word(6, P_GOAL_POSITION_L,StandupPos[5]-0);

espera_mov_levantar();

dxl_write_word(5, MOVING_SPEED, 400);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]- 60);

dxl_write_word(8, MOVING_SPEED, 400);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7] + 60);

espera_mov_levantar();

inverse_kinematic_right_leg(0, 0, 0, 200);
inverse_kinematic_left_leg(0, 0, 0, 200);
espera_mov_levantar();

for(int x=3; x<=8; x++)
    dxl_write_word( x, 34, 200); // Inicia os braços com baixo torque
/*teste*/
}
