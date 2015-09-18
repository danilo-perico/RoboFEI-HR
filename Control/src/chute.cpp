/*--------------------------------------------------------------------

******************************************************************************
* @file chute.cpp
* @author Isaac Jesus da Silva - ROBOFEI-HT - FEI
* @version V0.0.7
* @created 20/01/2014
* @Modified 17/07/2014
* @e-mail isaac25silva@yahoo.com.br
* @brief chute
****************************************************************************
****************************************************************************

Arquivo fonte contendo o algoritmo de chute com pé direito e pé esquerdo

/--------------------------------------------------------------------*/

#include <dynamixel.h>
#include <unistd.h>
#include <stdio.h>

//============================================================================================
//--------------------------------------------------------------------------------------------
int chute_direito()
{

float altura_pe  = 0.055;
if(espera_mov()) return 0; // Aguarda termino de alguma atividade

inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.009, 0, 500); //abaixa o corpo
usleep(100000);


//------------------------------------------------------
inclina_plano(LEG_RIGHT, -50, 45, -10); // inclina para esquerda
inclina_plano(LEG_LEFT, -41, 45, 0);  // inclina para esquerda
inverse_kinematic_right_leg(0, 0.014, -5, 100);
if(espera_mov_legs()) return 0;

inclina_plano(LEG_LEFT, -56, 40, 0); //52
inclina_plano(LEG_RIGHT, -62, 40, -10);
//inverse_kinematic_left_leg(0, 0.008, 5, 100);

// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_right_leg(0, altura_pe-.01, 0, 400); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(0, altura_pe-.02, -7, 600); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(0, altura_pe-.02, -9, 500); //levanta pé direito
//if(espera_mov_legs()) return 0;
usleep(60000);
//--------------------------------------------------------

//-------------------------------------------------------------
// Compensação pelo torque pe esquerdo
avoid_swing_left();
//-------------------------------------------------------------

inclina_plano(LEG_RIGHT, -75, 30, 0);
// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_right_leg(0.05, altura_pe-.02, -5, 400); //avança pé direito
usleep(50000);
inverse_kinematic_right_leg(0.05, altura_pe-.01, 0, 700); //avança pé direito
usleep(40000);
inverse_kinematic_right_leg(0.08, altura_pe, 0, 400); //avança pé direito
//if(espera_mov_legs()) return 0;
usleep(70000);
inclina_plano(LEG_RIGHT, -62, 30, 0);
//--------------------------------------------------------
inverse_kinematic_left_leg(0, 0.008, 2, 100); // volta com o corpo um pouco pra frente
//---- avança pé direito --------------------------------
inverse_kinematic_right_leg(0, altura_pe-0.01, 0, 400); // volta o pé direito
usleep(35000);
inverse_kinematic_right_leg(0, altura_pe-0.02, -7, 500); // volta o pé direito
usleep(65000);
inverse_kinematic_right_leg(0, altura_pe-0.02, -9, 300); // volta o pé direito
//if(espera_mov_legs()) return 0;
usleep(70000);

//---------------------------------------------------
//if(espera_mov_legs()) return 0;
inverse_kinematic_right_leg(0, 0.018, -7, 100);
inverse_kinematic_left_leg(0, 0.008, 2, 100);
if(espera_mov_legs()) return 0;
inclina_plano(LEG_RIGHT, 0, 65, 0);
inclina_plano(LEG_LEFT, 0, 65, 0);
inverse_kinematic_right_leg(0, 0.010, -2, 100);
if(espera_mov_legs()) return 0;
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_left_leg(0, 0.008, 0, 100); /* teste*/
if(espera_mov_legs()) return 0;

return 0;
}



//=============================================================================================
//---------------------------------------------------------------------------------------------
int chute_esquerdo()
{
float altura_pe  = 0.055;
if(espera_mov()) return 0; // Aguarda termino de alguma atividade

inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.009, 0, 500); //abaixa o corpo
usleep(100000);

inclina_plano(LEG_RIGHT, 54, 45, 0); // inclina para direita
inclina_plano(LEG_LEFT, 56, 45, 0);  // inclina para direita
usleep(100000);
inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.010, 0, 600); //abaixa o corpo
usleep(100000);
inverse_kinematic_right_leg(0, 0.008, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.012, 0, 300); //abaixa o corpo
if(espera_mov_legs()) return 0;
inclina_plano(LEG_RIGHT, 68, 50, 0); // inclina para direita - 45
inclina_plano(LEG_LEFT, 64, 45, 0); // 40
// Levanta pé curva de aceleração e desaceleração -----
inverse_kinematic_left_leg(0, altura_pe-0.04, 0, 300); // levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(0, altura_pe-0.03, 0, 500); // levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(0.02, altura_pe-0.03, 0, 300); // levanta pé esquerdo 0.3
//if(espera_mov_legs()) return 0;
usleep(65000);

//-------------------------------------------------------------
// Compensação pelo torque do pé direito
avoid_swing_right();
//-------------------------------------------------------------

dxl_write_word(7, P_GOAL_POSITION_L, StandupPos[6]-20); // Abre braço para não enganchar na perna
// avança o pé esquerdo -------------------------------
inclina_plano(LEG_LEFT, 80, 30, 0);
inverse_kinematic_left_leg(0.08, altura_pe-0.02, 0, 400); // avança pé esquerdo
usleep(35000);
inverse_kinematic_left_leg(0.08, altura_pe-0.01, 7, 700); // avança pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(0.09, altura_pe, 7, 600); // avança pé esquerdo
//if(espera_mov_legs()) return 0;
usleep(65000);
//volta pe esquerdo---------------------------------------
inclina_plano(LEG_LEFT, 80, 30, 0);
inverse_kinematic_left_leg(0, altura_pe, 7, 400); // volta pé esquerdo
usleep(35000);
inverse_kinematic_left_leg(0, altura_pe-0.015, 7, 600); // volta pé esquerdo
usleep(55000);
inverse_kinematic_left_leg(0, altura_pe-0.03, 0, 300); // volta pé esquerdo
//if(espera_mov_legs()) return 0;
usleep(80000);
//--------------------------------------------------------
//if(espera_mov_legs()) return 0;
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_left_leg(0, 0.015, 0, 100);
if(espera_mov_legs()) return 0;
inclina_plano(LEG_RIGHT, 0, 65, 0);
inclina_plano(LEG_LEFT, 0, 65, 0);
inverse_kinematic_left_leg(0, 0.009, 0, 100);
if(espera_mov_legs()) return 0;
inverse_kinematic_left_leg(0, 0.008, 0, 100);
usleep(50000);

inverse_kinematic_right_leg(0, 0.008, 0, 300);
inverse_kinematic_left_leg(0, 0.008, 0, 300); /* teste*/
dxl_write_word(7, P_GOAL_POSITION_L, StandupPos[6]); // Volta braço
if(espera_mov_legs()) return 0;

return 0;
}
