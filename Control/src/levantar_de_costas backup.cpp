#include <dynamixel.h>
#include <unistd.h>


//============================================================================================
//--------------------------------------------------------------------------------------------
void levantar_de_costas()
{

for(int x=3; x<=8; x++)
    dxl_write_word( x, 34, 1023); // Inicia os braços com alto torque
/*
robo_ereto();
espera_mov();

inverse_kinematic_right_leg(0, 0.07, -100, 200);
inverse_kinematic_left_leg(0, 0.07, -100, 200);
espera_mov();

inverse_kinematic_right_leg(-0.05, 0.07, -100, 200);
inverse_kinematic_left_leg(-0.05, 0.07, -100, 200);
espera_mov();

dxl_write_word(5, MOVING_SPEED, 300);
dxl_write_word(5, P_GOAL_POSITION_L, StandupPos[4]- 290);

dxl_write_word(8, MOVING_SPEED, 300);
dxl_write_word(8, P_GOAL_POSITION_L, StandupPos[7] + 290);

dxl_write_word(3, MOVING_SPEED, 700);
dxl_write_word(3, P_GOAL_POSITION_L,StandupPos[2]+300);

dxl_write_word(6, MOVING_SPEED, 700);
dxl_write_word(6, P_GOAL_POSITION_L,StandupPos[5]-300);

espera_mov();

dxl_write_word(3, MOVING_SPEED, 600);
dxl_write_word(3, P_GOAL_POSITION_L,StandupPos[2]+150);

dxl_write_word(6, MOVING_SPEED, 600);
dxl_write_word(6, P_GOAL_POSITION_L,StandupPos[5]-150);



/*teste*/


//dxl_write_word(i, MOVING_SPEED, 100);
//dxl_write_word(i, P_GOAL_POSITION_L, StandupPos[i]+0);

dxl_write_word(12, MOVING_SPEED, 100);
dxl_write_word(12, P_GOAL_POSITION_L, 310);

dxl_write_word(18, MOVING_SPEED, 100);
dxl_write_word(18, P_GOAL_POSITION_L, 180+48);
//espera_mov();


dxl_write_word(3, MOVING_SPEED, 100);
dxl_write_byte(3, TORQUE_ENABLE, 0);

dxl_write_word(6, MOVING_SPEED, 100);
dxl_write_byte(6, TORQUE_ENABLE, 0);
//espera_mov();

dxl_write_word(5, MOVING_SPEED, 100);
dxl_write_word(5, P_GOAL_POSITION_L,10);

dxl_write_word(8, MOVING_SPEED, 100);
dxl_write_word(8, P_GOAL_POSITION_L,1010);

dxl_write_word(10, MOVING_SPEED, 100);
dxl_write_word(10, P_GOAL_POSITION_L, 700);

dxl_write_word(16, MOVING_SPEED, 100);
dxl_write_word(16, P_GOAL_POSITION_L, 324);


dxl_write_word(20, MOVING_SPEED, 100);
dxl_write_word(20, P_GOAL_POSITION_L, 60);

dxl_write_word(14, MOVING_SPEED, 100);
dxl_write_word(14, P_GOAL_POSITION_L, 947);
espera_mov();

dxl_write_word(20, MOVING_SPEED, 100);
dxl_write_byte(20, TORQUE_ENABLE, 0);

dxl_write_word(14, MOVING_SPEED, 100);
dxl_write_byte(14, TORQUE_ENABLE, 0);
espera_mov();

dxl_write_word(3, MOVING_SPEED, 480);
dxl_write_word(6, MOVING_SPEED, 480);
//dxl_write_byte(3, TORQUE_ENABLE, 1);
//dxl_write_byte(6, TORQUE_ENABLE, 1);

dxl_write_word(3, P_GOAL_POSITION_L, 509-50);
dxl_write_word(6, P_GOAL_POSITION_L, 550+50);


dxl_write_word(10, MOVING_SPEED, 200);
dxl_write_word(10, P_GOAL_POSITION_L, 437);

dxl_write_word(16, MOVING_SPEED, 200);
dxl_write_word(16, P_GOAL_POSITION_L, 592);
espera_mov();
//-----------------------------------------------------

dxl_write_word(5, MOVING_SPEED, 700);
dxl_write_word(5, P_GOAL_POSITION_L,2);

dxl_write_word(8, MOVING_SPEED, 700);
dxl_write_word(8, P_GOAL_POSITION_L,1020);

dxl_write_word(3, MOVING_SPEED, 480);
dxl_write_word(6, MOVING_SPEED, 480);
dxl_write_word(3, P_GOAL_POSITION_L, 509-80);
dxl_write_word(6, P_GOAL_POSITION_L, 550+80);

dxl_write_word(12, MOVING_SPEED, 200);
dxl_write_word(12, P_GOAL_POSITION_L, 310-40);

dxl_write_word(18, MOVING_SPEED, 200);
dxl_write_word(18, P_GOAL_POSITION_L, 228-40);

espera_mov();

dxl_write_word(5, MOVING_SPEED, 700);
dxl_write_word(5, P_GOAL_POSITION_L,62+30);
dxl_write_word(8, MOVING_SPEED, 700);
dxl_write_word(8, P_GOAL_POSITION_L,960-30);
dxl_write_word(3, MOVING_SPEED, 480);
dxl_write_word(6, MOVING_SPEED, 480);
dxl_write_word(3, P_GOAL_POSITION_L, 509-90);
dxl_write_word(6, P_GOAL_POSITION_L, 550+90);


//dxl_write_byte(14, TORQUE_ENABLE, 1);
//dxl_write_byte(20, TORQUE_ENABLE, 1);
printf("Servo 14 = %d", dxl_read_word( 14, P_PRESENT_POSITION_L)); //leitura 620
printf("Servo 20 = %d", dxl_read_word( 20, P_PRESENT_POSITION_L)); //leitura 382

dxl_write_word(10, MOVING_SPEED, 200);
dxl_write_word(10, P_GOAL_POSITION_L, 437-80); //532

dxl_write_word(16, MOVING_SPEED, 200);
dxl_write_word(16, P_GOAL_POSITION_L, 592+80);//487

espera_mov();

//dxl_write_word(12, MOVING_SPEED, 200);
//dxl_write_word(12, P_GOAL_POSITION_L, 310-90);

//dxl_write_word(18, MOVING_SPEED, 200);
//dxl_write_word(18, P_GOAL_POSITION_L, 228-90);

/*
dxl_write_word(12, MOVING_SPEED, 100);
dxl_write_word(12, P_GOAL_POSITION_L, 310);

dxl_write_word(18, MOVING_SPEED, 100);
dxl_write_word(18, P_GOAL_POSITION_L, 180+48);
//espera_mov();


dxl_write_word(3, MOVING_SPEED, 100);
dxl_write_byte(3, TORQUE_ENABLE, 0);

dxl_write_word(6, MOVING_SPEED, 100);
dxl_write_byte(6, TORQUE_ENABLE, 0);
//espera_mov();

dxl_write_word(5, MOVING_SPEED, 100);
dxl_write_word(5, P_GOAL_POSITION_L,10);

dxl_write_word(8, MOVING_SPEED, 100);
dxl_write_word(8, P_GOAL_POSITION_L,1010);

dxl_write_word(10, MOVING_SPEED, 100);
dxl_write_word(10, P_GOAL_POSITION_L, 700);

dxl_write_word(16, MOVING_SPEED, 100);
dxl_write_word(16, P_GOAL_POSITION_L, 324);


dxl_write_word(20, MOVING_SPEED, 100);
dxl_write_word(20, P_GOAL_POSITION_L, 60);

dxl_write_word(14, MOVING_SPEED, 100);
dxl_write_word(14, P_GOAL_POSITION_L, 947);
espera_mov();

dxl_write_word(20, MOVING_SPEED, 100);
dxl_write_byte(20, TORQUE_ENABLE, 0);

dxl_write_word(14, MOVING_SPEED, 100);
dxl_write_byte(14, TORQUE_ENABLE, 0);
espera_mov();

dxl_write_word(3, MOVING_SPEED, 480);
dxl_write_word(6, MOVING_SPEED, 480);
//dxl_write_byte(3, TORQUE_ENABLE, 1);
//dxl_write_byte(6, TORQUE_ENABLE, 1);

dxl_write_word(3, P_GOAL_POSITION_L, 509-50);
dxl_write_word(6, P_GOAL_POSITION_L, 550+50);


dxl_write_word(10, MOVING_SPEED, 200);
dxl_write_word(10, P_GOAL_POSITION_L, 437);

dxl_write_word(16, MOVING_SPEED, 200);
dxl_write_word(16, P_GOAL_POSITION_L, 592);
espera_mov();
//-----------------------------------------------------

dxl_write_word(5, MOVING_SPEED, 700);
dxl_write_word(5, P_GOAL_POSITION_L,2);

dxl_write_word(8, MOVING_SPEED, 700);
dxl_write_word(8, P_GOAL_POSITION_L,1020);

dxl_write_word(3, MOVING_SPEED, 480);
dxl_write_word(6, MOVING_SPEED, 480);
dxl_write_word(3, P_GOAL_POSITION_L, 509-80);
dxl_write_word(6, P_GOAL_POSITION_L, 550+80);

dxl_write_word(12, MOVING_SPEED, 200);
dxl_write_word(12, P_GOAL_POSITION_L, 310-80);

dxl_write_word(18, MOVING_SPEED, 200);
dxl_write_word(18, P_GOAL_POSITION_L, 228-80);

espera_mov();

dxl_write_word(5, MOVING_SPEED, 700);
dxl_write_word(5, P_GOAL_POSITION_L,62+30);
dxl_write_word(8, MOVING_SPEED, 700);
dxl_write_word(8, P_GOAL_POSITION_L,960-30);
dxl_write_word(3, MOVING_SPEED, 480);
dxl_write_word(6, MOVING_SPEED, 480);
dxl_write_word(3, P_GOAL_POSITION_L, 509-90);
dxl_write_word(6, P_GOAL_POSITION_L, 550+90);


//dxl_write_byte(14, TORQUE_ENABLE, 1);
//dxl_write_byte(20, TORQUE_ENABLE, 1);
printf("Servo 14 = %d", dxl_read_word( 14, P_PRESENT_POSITION_L)); //leitura 620
printf("Servo 20 = %d", dxl_read_word( 20, P_PRESENT_POSITION_L)); //leitura 382

dxl_write_word(10, MOVING_SPEED, 200);
dxl_write_word(10, P_GOAL_POSITION_L, 437-50); //532

dxl_write_word(16, MOVING_SPEED, 200);
dxl_write_word(16, P_GOAL_POSITION_L, 592+50);//487

espera_mov();

dxl_write_word(12, MOVING_SPEED, 200);
dxl_write_word(12, P_GOAL_POSITION_L, 310-90);

dxl_write_word(18, MOVING_SPEED, 200);
dxl_write_word(18, P_GOAL_POSITION_L, 228-90);
/*teste*/

for(int x=3; x<=8; x++)
    dxl_write_word( x, 34, 200); // Inicia os braços com baixo torque

}
