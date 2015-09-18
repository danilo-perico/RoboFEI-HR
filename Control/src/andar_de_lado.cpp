/*--------------------------------------------------------------------

******************************************************************************
* @file andar_de_lado.cpp
* @author Isaac Jesus da Silva - ROBOFEI-HT - FEI
* @version V0.0.3
* @created 20/01/2014
* @Modified 03/07/2014
* @e-mail isaac25silva@yahoo.com.br
* @brief andar_de_lado
****************************************************************************
****************************************************************************

Arquivo fonte contendo o algoritmo do andar de lado para a esquerda e para a direita

/--------------------------------------------------------------------*/

#include "dynamixel.h"
#include <unistd.h>
#include <stdio.h>

int andar_lateral_direita()
{

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
inverse_kinematic_right_leg(0, altura_pe-.01, 0, 400); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(0, altura_pe-.02, -7, 600); //levanta pé direito
usleep(50000);
inclina_plano(LEG_RIGHT, -62, 50, 10);
inverse_kinematic_right_leg(0, altura_pe-.02, -9, 500); //levanta pé direito
//if(espera_mov()) return 0;
usleep(60000);

//--------------------------------------------------------
inclina_plano(LEG_LEFT, -50, 80, -15);
inclina_plano(LEG_RIGHT, -120, 100, 25);
inverse_kinematic_right_leg(0, altura_pe-.02, -2, 400); //abaixa pé direito
usleep(100000);
inverse_kinematic_right_leg(0, altura_pe-.035, 0, 200); //abaixa pé direito
usleep(100000);
inclina_plano(LEG_LEFT, -35, 100, -15);
usleep(100000);
inclina_plano(LEG_RIGHT, -120, 400, 20);
inverse_kinematic_right_leg(0, altura_pe-.045, 0, 200); //abaixa pé direito
usleep(100000);
inclina_plano(LEG_RIGHT, -80, 100, 10);
inclina_plano(LEG_LEFT, -30, 100, -5);
usleep(200000);
// -- centraliza o corpo ----------------------------------------------
inclina_plano(LEG_LEFT, 25, 84, -10);
inclina_plano(LEG_RIGHT, -15, 100, -4);
usleep(200000);
inverse_kinematic_right_leg(0, 0.007, 0, 100); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.007, 0, 100); //levanta pé direito

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
inclina_plano(LEG_RIGHT, 54, 45, 0); // inclina para direita
inclina_plano(LEG_LEFT, 95, 45, 0);  // inclina para direita
usleep(100000);
//inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
//inverse_kinematic_left_leg(0, 0.012, 0, 500); //abaixa o corpo
//usleep(100000);
//inverse_kinematic_right_leg(0, 0.008, 0, 200); // abaixa o corpo
//inverse_kinematic_left_leg(0, 0.012, 0, 200); //abaixa o corpo
if(espera_mov()) return 0;
inclina_plano(LEG_LEFT, 62, 40, 0);
inclina_plano(LEG_RIGHT, 60, 40, 0);

// Levanta pé curva de aceleração e desaceleração -----
inverse_kinematic_left_leg(0, altura_pe-0.03, 0, 300); // levanta pé esquerdo

usleep(50000);
inclina_plano(LEG_LEFT, 65, 40, 0);
inverse_kinematic_left_leg(0, altura_pe-0.020, 0, 500); // levanta pé esquerdo
//inclina_plano(LEG_RIGHT, 66, 45, 0); // inclina para direita
usleep(70000);
inverse_kinematic_left_leg(0, altura_pe-0.03, 0, 300); // levanta pé esquerdo
//if(espera_mov()) return 0;
usleep(65000);

//-------------------------------------------

//-------------------------------------------------------------
// Compensação pelo torque do pé direito
avoid_swing_right();
//-------------------------------------------------------------


//if(espera_mov()) return 0;
//inverse_kinematic_right_leg(0, 0.008, 0, 100);
//inverse_kinematic_left_leg(0, 0.012, 0, 100);
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
dxl_write_word(7, P_GOAL_POSITION_L, StandupPos[6]);
if(espera_mov_legs()) return 0;

return 0;
}
//=======================================================================================
//---------------------------------------------------------------------------------------
int andar_lateral_esquerda()
{

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
inclina_plano(LEG_LEFT, 64, 45, 0); // 40

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

//--------------------------------------------------------
inclina_plano(LEG_LEFT, 120, 80, 0);
inclina_plano(LEG_RIGHT, 65, 800, 0);
inverse_kinematic_left_leg(0, altura_pe-.03, 0, 400); //abaixa pé esquerdo
usleep(100000);
inverse_kinematic_left_leg(0, altura_pe-.045, 0, 200); //abaixa pé direito
usleep(100000);
inclina_plano(LEG_RIGHT, 45, 100, 0);
usleep(100000);
inclina_plano(LEG_LEFT, 120, 800, -25);
inverse_kinematic_left_leg(0, altura_pe-.045, 0, 200); //abaixa pé direito
usleep(100000);

// -- centraliza o corpo ----------------------------------------------
inclina_plano(LEG_RIGHT, -15, 80, 0);
inclina_plano(LEG_LEFT, 10, 90, 0);
inverse_kinematic_right_leg(0, 0.007, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.007, 0, 200); //levanta pé direito
usleep(100000);

inverse_kinematic_right_leg(0, 0, 0, 100); //levanta pé direito
inclina_plano(LEG_RIGHT, -15, 80, -20); //arruma calcanhar
usleep(50000);

//--- inclina para direita-----
inverse_kinematic_right_leg(0, 0, 0.008, 300); //levanta pé direito
inverse_kinematic_left_leg(0, 0.005, 0, 100); // abaixa o corpo
inclina_plano(LEG_RIGHT, -40, 45, 0); // inclina para esquerda
inclina_plano(LEG_LEFT, -20, 45, 15);  // inclina para esquerda
usleep(100000);

//--- inclina para direita------------------------------------------
inclina_plano(LEG_RIGHT, -120, 52, 10); // inclina para direita
inclina_plano(LEG_LEFT, -50, 45, 0);  // inclina para direita
usleep(100000);
//inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.008, 3, 500); //abaixa o corpo
if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, -55, 40, 0);

// Levanta pé curva de aceleração e desaceleração -----
inverse_kinematic_right_leg(0, altura_pe-0.03, 0, 300); // levanta pé direito
usleep(50000);
inclina_plano(LEG_RIGHT, -64, 40, 0);
inverse_kinematic_right_leg(0, altura_pe-0.020, 0, 500); // levanta pé direito
//inclina_plano(LEG_RIGHT, 66, 45, 0); // inclina para esquerda
usleep(70000);
inverse_kinematic_right_leg(0, altura_pe-0.03, 0, 300); // levanta pé direito
//if(espera_mov()) return 0;
usleep(65000);
//-------------------------------------------

//-------------------------------------------------------------
// Compensação pelo torque pe esquerdo
avoid_swing_left();
//-------------------------------------------------------------

//inclina_plano(LEG_LEFT, 59, 40, 0);
//if(espera_mov()) return 0;
//inverse_kinematic_right_leg(0, 0.008, 0, 100);
//inverse_kinematic_left_leg(0, 0.012, 0, 100);
if(espera_mov_legs()) return 0;
inclina_plano(LEG_LEFT, -55, 50, 5);
inclina_plano(LEG_RIGHT, -64, 40, 5);
inverse_kinematic_left_leg(0, 0.008, 2, 100);
inverse_kinematic_right_leg(0, 0.017, 0, 100);
if(espera_mov_legs()) return 0;
inclina_plano(LEG_RIGHT, 0, -60, 0);
inclina_plano(LEG_LEFT, 0, -60, 0);
inverse_kinematic_right_leg(0, 0.009, 0, 100);
if(espera_mov_legs()) return 0;
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_right_leg(0, 0.008, 0, 100);
usleep(50000);

//inverse_kinematic_right_leg(0, 0, 0, 300);
//inverse_kinematic_left_leg(0, 0, 0, 300); /* teste*/

/* teste*/
dxl_write_word(7, P_GOAL_POSITION_L, StandupPos[6]);
if(espera_mov_legs()) return 0;
/*teste*/
return 0;
}
