#include <dynamixel.h>
#include <unistd.h>


//============================================================================================
//--------------------------------------------------------------------------------------------
void levantar_de_costas()
{

for(int x=3; x<=8; x++)
    dxl_write_word( x, 34, 1023); // Inicia os braços com alto torque


dxl_write_word(12, MOVING_SPEED, 150);
dxl_write_word(12, P_GOAL_POSITION_L, StandupPos[11]-271);//310

dxl_write_word(18, MOVING_SPEED, 150);
dxl_write_word(18, P_GOAL_POSITION_L, StandupPos[17]-264);//228

//dxl_write_word(3, MOVING_SPEED, 150);
dxl_write_byte(3, TORQUE_ENABLE, 0);

//dxl_write_word(6, MOVING_SPEED, 150);
dxl_write_byte(6, TORQUE_ENABLE, 0);

dxl_write_word(5, MOVING_SPEED, 150);
dxl_write_word(5, P_GOAL_POSITION_L,StandupPos[4]-360);//10

dxl_write_word(8, MOVING_SPEED, 150);
dxl_write_word(8, P_GOAL_POSITION_L,StandupPos[7]+340);//1010

dxl_write_word(10, MOVING_SPEED, 150);
dxl_write_word(10, P_GOAL_POSITION_L, StandupPos[9]+168);//700

dxl_write_word(16, MOVING_SPEED, 150);
dxl_write_word(16, P_GOAL_POSITION_L, StandupPos[15]-163);//324

dxl_write_word(20, MOVING_SPEED, 150);
dxl_write_word(20, P_GOAL_POSITION_L, StandupPos[19]-159);//60

dxl_write_word(14, MOVING_SPEED, 150);
dxl_write_word(14, P_GOAL_POSITION_L, StandupPos[13]+141);//947
espera_mov_levantar();

//dxl_write_word(20, MOVING_SPEED, 100);
dxl_write_byte(20, TORQUE_ENABLE, 0);

//dxl_write_word(14, MOVING_SPEED, 100);
dxl_write_byte(14, TORQUE_ENABLE, 0);
espera_mov_levantar();

dxl_write_word(3, MOVING_SPEED, 480);
dxl_write_word(6, MOVING_SPEED, 480);

dxl_write_word(3, P_GOAL_POSITION_L, StandupPos[2]+77);//459
dxl_write_word(6, P_GOAL_POSITION_L, StandupPos[5]-42);//600

dxl_write_word(10, MOVING_SPEED, 200);
dxl_write_word(10, P_GOAL_POSITION_L, StandupPos[9]-95);//437

dxl_write_word(16, MOVING_SPEED, 200);
dxl_write_word(16, P_GOAL_POSITION_L, StandupPos[15]+105);//592
espera_mov_levantar();

dxl_write_word(5, MOVING_SPEED, 700);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]-350);//-----------------------xxx --0002

dxl_write_word(8, MOVING_SPEED, 700);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7]+350);//--------------------xxx --1020

dxl_write_word(3, MOVING_SPEED, 480);
dxl_write_word(6, MOVING_SPEED, 480);
dxl_write_word(3, P_GOAL_POSITION_L, StandupPos[2]+47);//429
dxl_write_word(6, P_GOAL_POSITION_L, StandupPos[5]-12);//630

dxl_write_word(12, MOVING_SPEED, 200);
dxl_write_word(12, P_GOAL_POSITION_L, StandupPos[11]-311);//270

dxl_write_word(18, MOVING_SPEED, 200);
dxl_write_word(18, P_GOAL_POSITION_L, StandupPos[17]-304);//188

espera_mov_levantar();
//-----------------------------------------------------------------


// ---- Abre as pernas -------------------------
dxl_write_word(5, MOVING_SPEED, 100);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]-276);//97

dxl_write_word(8, MOVING_SPEED, 100);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7]+248);//917

dxl_write_word(11, MOVING_SPEED, 95);
dxl_write_word(11, P_GOAL_POSITION_L, StandupPos[10]+286);//793

dxl_write_word(17, MOVING_SPEED, 92);
dxl_write_word(17, P_GOAL_POSITION_L, StandupPos[16]-289);//243

dxl_write_word(10, MOVING_SPEED, 100);
dxl_write_word(10, P_GOAL_POSITION_L, StandupPos[9]+139);//671

dxl_write_word(16, MOVING_SPEED, 100);
dxl_write_word(16, P_GOAL_POSITION_L, StandupPos[15]-113);//374
espera_mov_levantar();

//---- Empurra o corpo para ficar sentado -----------------
dxl_write_word(5, MOVING_SPEED, 100);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]-159); //214

dxl_write_word(8, MOVING_SPEED, 100);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7]+159); //778+50

dxl_write_word(14, MOVING_SPEED, 100);
dxl_write_word(14, P_GOAL_POSITION_L, StandupPos[13]-118); //688

dxl_write_word(20, MOVING_SPEED, 100);
dxl_write_word(20, P_GOAL_POSITION_L, StandupPos[19]+108); //327

espera_mov_levantar();


//----- Puxa os braços para traz -------------------------

dxl_write_word(13, MOVING_SPEED, 150);
dxl_write_word(13, P_GOAL_POSITION_L, StandupPos[12]+392); //904

dxl_write_word(19, MOVING_SPEED, 150);
dxl_write_word(19, P_GOAL_POSITION_L, StandupPos[18]- 188); //324

dxl_write_word(5, MOVING_SPEED, 200);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]-350); //------------------------xx 0002

dxl_write_word(8, MOVING_SPEED, 200);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7]+350); //------------------------xx 1020

usleep(100000);

dxl_write_word(3, MOVING_SPEED, 400);
dxl_write_word(3, P_GOAL_POSITION_L,StandupPos[2]+480);

dxl_write_word(6, MOVING_SPEED, 400);
dxl_write_word(6, P_GOAL_POSITION_L,StandupPos[5]-480);
espera_mov_levantar();

//---- Traz os braço para frente---------------------------
dxl_write_word(5, MOVING_SPEED, 700);
dxl_write_word(5, P_GOAL_POSITION_L,StandupPos[4] + 100);

dxl_write_word(8, MOVING_SPEED, 700);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7] - 100);

usleep(80000);
//espera_mov_levantar();

//---- Gira as pernas -------------------------------------
dxl_write_word(9, MOVING_SPEED, 200);
dxl_write_word(9, P_GOAL_POSITION_L,StandupPos[8] + 75);

dxl_write_word(15, MOVING_SPEED, 200);
dxl_write_word(15, P_GOAL_POSITION_L, StandupPos[14] - 75);
espera_mov_levantar();

dxl_write_word(16, MOVING_SPEED, 200);
dxl_write_word(16, P_GOAL_POSITION_L,StandupPos[15]);

dxl_write_word(10, MOVING_SPEED, 200);
dxl_write_word(10, P_GOAL_POSITION_L, StandupPos[9]);
espera_mov_levantar();

/*

dxl_write_word(9, MOVING_SPEED, 10);
dxl_write_word(9, P_GOAL_POSITION_L,StandupPos[8]);

dxl_write_word(15, MOVING_SPEED, 10);
dxl_write_word(15, P_GOAL_POSITION_L, StandupPos[14]);

dxl_write_word(11, MOVING_SPEED, 100);
dxl_write_word(11, P_GOAL_POSITION_L, StandupPos[10]);

dxl_write_word(17, MOVING_SPEED, 100);
dxl_write_word(17, P_GOAL_POSITION_L, StandupPos[16]);

dxl_write_word(13, MOVING_SPEED, 20);
dxl_write_word(13, P_GOAL_POSITION_L, StandupPos[12]);

dxl_write_word(19, MOVING_SPEED, 20);
dxl_write_word(19, P_GOAL_POSITION_L, StandupPos[18]);
*/

inverse_kinematic_right_leg(0, 0, 0, 250);
inverse_kinematic_left_leg(0, 0, 0, 250);
//espera_mov_levantar();
inclina_plano(LEG_RIGHT, 0, 150, 0);
inclina_plano(LEG_LEFT, 0, 150, 0);
espera_mov_levantar();
dxl_write_word(9, MOVING_SPEED, 100);
dxl_write_word(9, P_GOAL_POSITION_L,StandupPos[8]);

dxl_write_word(15, MOVING_SPEED, 100);
dxl_write_word(15, P_GOAL_POSITION_L, StandupPos[14]);
espera_mov_levantar();

//---------------levantar de frente------------------------
/*
dxl_write_word(5, MOVING_SPEED, 300);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]- 270);

dxl_write_word(8, MOVING_SPEED, 300);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7] + 270);

dxl_write_word(3, MOVING_SPEED, 400);
dxl_write_word(3, P_GOAL_POSITION_L,StandupPos[2]+550);

dxl_write_word(6, MOVING_SPEED, 400);
dxl_write_word(6, P_GOAL_POSITION_L,StandupPos[5]-550);
*/
dxl_write_word(10, MOVING_SPEED, 500);
dxl_write_word(10, P_GOAL_POSITION_L, StandupPos[9] + 341);

dxl_write_word(12, MOVING_SPEED, 500);
dxl_write_word(12, P_GOAL_POSITION_L, StandupPos[11] - 426);

dxl_write_word(14, MOVING_SPEED, 500);
dxl_write_word(14, P_GOAL_POSITION_L, StandupPos[13] - 200);

dxl_write_word(16, MOVING_SPEED, 500);
dxl_write_word(16, P_GOAL_POSITION_L, StandupPos[15] - 337);

dxl_write_word(18, MOVING_SPEED, 500);
dxl_write_word(18, P_GOAL_POSITION_L, StandupPos[17] - 424);

dxl_write_word(20, MOVING_SPEED, 500);
dxl_write_word(20, P_GOAL_POSITION_L, StandupPos[19] + 182);

espera_mov_levantar();

dxl_write_word(5, MOVING_SPEED, 200);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]+ 50);

dxl_write_word(8, MOVING_SPEED, 200);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7] - 50);

espera_mov_levantar();

dxl_write_word(5, MOVING_SPEED, 200);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]+ 160);

dxl_write_word(8, MOVING_SPEED, 200);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7] - 160);

dxl_write_word(3, MOVING_SPEED, 420);
dxl_write_word(3, P_GOAL_POSITION_L,StandupPos[2]+0);

dxl_write_word(6, MOVING_SPEED, 420);
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

/*teste*/

for(int x=3; x<=8; x++)
    dxl_write_word( x, 34, 200); // Inicia os braços com baixo torque

}
