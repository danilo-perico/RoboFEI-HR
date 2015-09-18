/*--------------------------------------------------------------------

******************************************************************************
* @file virar.cpp
* @author Isaac Jesus da Silva - ROBOFEI-HT - FEI
* @version V0.0.1
* @created 12/07/2014
* @Modified 12/07/2014
* @e-mail isaac25silva@yahoo.com.br
* @brief virar
****************************************************************************
****************************************************************************

Arquivo fonte contendo o algoritmo de virar para direita e esquerda

/--------------------------------------------------------------------*/

#include <dynamixel.h>
#include <unistd.h>
#include <stdio.h>

//============================================================================================
//--------------------------------------------------------------------------------------------
int virar_esquerda(unsigned short int valor)
{
//if(espera_mov()) return 0; // Aguarda termino de alguma atividade
//inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
//inverse_kinematic_left_leg(0, 0.008, 0, 500); //abaixa o corpo
//usleep(100000);

if(valor > 90)
    valor = 90;
if(valor < 35)
    valor = 35;

float altura_pe  = 0.050;
if(espera_mov()) return 0;

dxl_write_word(7, P_GOAL_POSITION_L, StandupPos[6]-20);//512

inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.009, 0, 500); //abaixa o corpo
usleep(100000);


//------------------------------------------------------
inclina_plano(LEG_RIGHT, -50, 45, -10); // inclina para esquerda
inclina_plano(LEG_LEFT, -41, 45, 0);  // inclina para esquerda
inverse_kinematic_right_leg(0, 0.014, -5, 100);
if(espera_mov()) return 0;

inclina_plano(LEG_LEFT, -52, 50, -3);
inclina_plano(LEG_RIGHT, -62, 50, -10);
//inverse_kinematic_left_leg(0, 0.008, 5, 100);

// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_right_leg(0, altura_pe-.01, -4, 400); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(0, altura_pe-.02, -4, 600); //levanta pé direito
usleep(50000);
inclina_plano(LEG_RIGHT, -62, 50, 0);
inverse_kinematic_right_leg(0, altura_pe-.02, -4, 500); //levanta pé direito
//if(espera_mov()) return 0;
usleep(60000);

//inclina_plano(LEG_LEFT, -45, 50, -3);
inverse_kinematic_left_leg(0, 0.009, -1, 100); //ajusta centro de massa
dxl_write_word(15, MOVING_SPEED, 150);
dxl_write_word(15, P_GOAL_POSITION_L, StandupPos[14]+ valor); //vira perna
usleep(100000);

//--------------------------------------------------------
inclina_plano(LEG_LEFT, -50, 80, -8);
inclina_plano(LEG_RIGHT, -70, 100, 25);
inverse_kinematic_right_leg(0, altura_pe-.02, -4, 400); //abaixa pé direito
usleep(100000);
inverse_kinematic_right_leg(0, altura_pe-.035, -4, 200); //abaixa pé direito
usleep(100000);
inclina_plano(LEG_LEFT, -35, 100, -15);
usleep(100000);
inclina_plano(LEG_RIGHT, -70, 400, 20);
inverse_kinematic_right_leg(0, altura_pe-.038, -4, 200); //abaixa pé direito
usleep(100000);
inclina_plano(LEG_RIGHT, -70, 100, 10);
inclina_plano(LEG_LEFT, -30, 100, -5);
usleep(200000);

// -- centraliza o corpo ----------------------------------------------
inclina_plano(LEG_LEFT, 5, 84, -10);
inclina_plano(LEG_RIGHT, -5, 100, -4);
usleep(200000);
inverse_kinematic_right_leg(0, 0.007, 0, 100); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.007, 0, 100); //levanta pé direito
/*
usleep(100000);
inclina_plano(LEG_LEFT, 35, 80, 4);
inclina_plano(LEG_RIGHT, -5, 90, 20);
inverse_kinematic_left_leg(0, 0, 0, 100); //levanta pé direito
usleep(50000);

//--- inclina para direita-----
inverse_kinematic_left_leg(0, 0, 0.008, 200); //levanta pé direito
inverse_kinematic_right_leg(0, 0.005, 0, 100); // abaixa o corpo
inclina_plano(LEG_RIGHT, 20, 45, 0); // inclina para direita
inclina_plano(LEG_LEFT, 40, 45, 15);  // inclina para direita
usleep(100000);


//--- inclina para direita------------------------------------------
//inclina_plano(LEG_RIGHT, 54, 45, 0); // inclina para direita
//inclina_plano(LEG_LEFT, 95, 45, 0);  // inclina para direita
//usleep(100000);
//inverse_kinematic

dxl_write_word(15, MOVING_SPEED, 150);
dxl_write_word(15, P_GOAL_POSITION_L, StandupPos[14]);
usleep(70000);

if(espera_mov_legs()) return 0;
//usleep(65000);
inclina_plano(LEG_RIGHT, 59, 50, 0);
inverse_kinematic_right_leg(0, 0.008, 0, 200);
inverse_kinematic_left_leg(0, 0.013, 0, 200);

if(espera_mov_legs()) return 0;
inclina_plano(LEG_RIGHT, 0, 60, 0);
inclina_plano(LEG_LEFT, 0, 60, 0);
inverse_kinematic_left_leg(0, 0.009, 0, 80);
if(espera_mov_legs()) return 0;
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_right_leg(0, 0.008, 0, 100);
usleep(50000);

//inverse_kinematic_right_leg(0, 0, 0, 300);
//inverse_kinematic_left_leg(0, 0, 0, 300); /* teste*/


//inverse_kinematic_right_leg(0, 0, 0, 300);
//inverse_kinematic_left_leg(0, 0, 0, 300); /* teste*/
dxl_write_word(15, MOVING_SPEED, 150);
dxl_write_word(15, P_GOAL_POSITION_L, StandupPos[14]); //volta a perna
usleep(70000);
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inclina_plano(LEG_LEFT, 0, 100, 0);
inclina_plano(LEG_RIGHT, 0, 100, 0);
usleep(50000);
dxl_write_word(7, P_GOAL_POSITION_L, StandupPos[6]);
if(espera_mov_legs()) return 0;

/*teste*/
return 0;
}

//============================================================================================
//--------------------------------------------------------------------------------------------
int virar_direita(unsigned short int valor)
{
//if(espera_mov()) return 0; // Aguarda termino de alguma atividade
//inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
//inverse_kinematic_left_leg(0, 0.008, 0, 500); //abaixa o corpo
//usleep(100000);

if(valor > 90)
    valor = 90;
if(valor < 35)
    valor = 35;

float altura_pe  = 0.055;
if(espera_mov()) return 0;

inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.009, 0, 500); //abaixa o corpo
usleep(100000);

inclina_plano(LEG_RIGHT, 56, 45, 0); // inclina para direita
inclina_plano(LEG_LEFT, 58, 45, 0);  // inclina para direita
usleep(100000);
inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.010, 0, 600); //abaixa o corpo
usleep(100000);
inverse_kinematic_right_leg(0, 0.008, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.012, 0, 300); //abaixa o corpo
if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, 68, 50, 0); // inclina para direita - 45
inclina_plano(LEG_LEFT, 70, 45, 0); // 40

dxl_write_word(7, P_GOAL_POSITION_L, StandupPos[6]-25); // Abre braço para não enganchar na perna

// Levanta pé curva de aceleração e desaceleração -----
inverse_kinematic_left_leg(0, altura_pe-0.04, 0, 300); // levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(0, altura_pe-0.03, 0, 500); // levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(0, altura_pe-0.03, 0, 300); // levanta pé esquerdo
//if(espera_mov()) return 0;
usleep(65000);
//-------------------------------------------

inverse_kinematic_right_leg(0, 0.008, 0, 200); // ajusta centro de massa
dxl_write_word(9, MOVING_SPEED, 150);
dxl_write_word(9, P_GOAL_POSITION_L, StandupPos[8]- valor);
usleep(100000);

//--------------------------------------------------------
inclina_plano(LEG_LEFT, 70, 80, 0);
inclina_plano(LEG_RIGHT, 65, 800, 0);
inverse_kinematic_left_leg(0, altura_pe-.03, 0, 400); //abaixa pé esquerdo
usleep(100000);
inverse_kinematic_left_leg(0, altura_pe-.038, 0, 200); //abaixa pé direito
usleep(100000);
inclina_plano(LEG_RIGHT, 45, 100, 0);
usleep(100000);
inclina_plano(LEG_LEFT, 70, 800, -25);
inverse_kinematic_left_leg(0, altura_pe-.038, 0, 200); //abaixa pé direito
usleep(100000);


// -- centraliza o corpo ----------------------------------------------
inclina_plano(LEG_RIGHT, -5, 80, 0);
inclina_plano(LEG_LEFT, 5, 90, 0);
inverse_kinematic_right_leg(0, 0.007, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.007, 0, 200); //levanta pé direito
usleep(100000);

dxl_write_word(9, MOVING_SPEED, 150);
dxl_write_word(9, P_GOAL_POSITION_L, StandupPos[8]);
usleep(100000);

inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inclina_plano(LEG_LEFT, 0, 100, 0);
inclina_plano(LEG_RIGHT, 0, 100, 0);
usleep(50000);
dxl_write_word(7, P_GOAL_POSITION_L, StandupPos[6]);
if(espera_mov_legs()) return 0;
/*teste*/

return 0;
}
