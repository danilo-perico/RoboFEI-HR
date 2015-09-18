#include <iostream>
#include <stdio.h>
#include <dynamixel.h>
#include <unistd.h>
#include <blackboard.h>
#include <ctime>

inline void mySleep(clock_t msec) // clock_t is a like typedef unsigned int clock_t. Use clock_t instead of integer in this context
{
clock_t start_time = clock();
clock_t end_time = msec + start_time;
while(clock() != end_time);
} 

inline void readGyroStop(float imuz)
{
	//std::cout<<"IMU X = "<<IMU_GYRO_X<<std::endl;
	//std::cout<<"IMU Y = "<<IMU_GYRO_Y<<std::endl;
	//std::cout<<"IMU Z = "<<IMU_GYRO_Z<<std::endl;

	float ImuZ = IMU_GYRO_Z;
	if(ImuZ<-imuz)
	{
		usleep(500000);
		std::cout<<"IMU Z = "<<ImuZ<<std::endl;
	}
}

int andar()
{
robo_ereto();
if(espera_mov()) return 0;

inclina_plano(LEG_RIGHT, 50, 40, 0); // inclina para direita
inclina_plano(LEG_LEFT, 50, 40, 0);  // inclina para direita
if(espera_mov()) return 0;
inclina_plano(LEG_LEFT, 56, 40, 0);
inverse_kinematic_left_leg(0, 0.02, 0, 300); // levanta pé esquerdo
if(espera_mov()) return 0;
for(int x=0; x<3; x++)
{
inverse_kinematic_left_leg(0.02, 0.02, 0, 100); // avança pé esquerdo
if(espera_mov()) return 0;
inverse_kinematic_right_leg(-0.01, 0.005, 0, 200); // movimenta o corpo pra frente
inverse_kinematic_left_leg(0.01, 0.006, 0, 200); //abaixa pé esquerdo
inclina_plano(LEG_RIGHT, 40, 60, 0);
inclina_plano(LEG_LEFT, 40, 60, 0);
if(espera_mov()) return 0;
inverse_kinematic_left_leg(0.01, 0.005, 0, 300);
inclina_plano(LEG_RIGHT, 0, 40, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 40, 0);  // volta da inclinação ficando reto
if(espera_mov()) return 0;
sleep(1);
inclina_plano(LEG_RIGHT, -45, 40, 0); // inclina para esquerda
inclina_plano(LEG_LEFT, -48, 40, 0);  // inclina para esquerda
if(espera_mov()) return 0;
inclina_plano(LEG_LEFT, -55, 40, 0);
inclina_plano(LEG_RIGHT, -58, 40, 0);
inverse_kinematic_left_leg(0, 0.005, 0, 100); // volta com o corpo um pouco pra frente
inverse_kinematic_right_leg(-0.01, 0.03, -10, 300); //levanta pé direito
if(espera_mov()) return 0;
inverse_kinematic_right_leg(0.02, 0.03, -10, 100); // avança o pé direito
if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, -40, 60, 0);
inclina_plano(LEG_LEFT, -40, 60, 0);
inverse_kinematic_right_leg(0.01, 0.01, -5, 100); // abaixa pé sem chutar o chão
inverse_kinematic_left_leg(-0.01, 0.005, 0, 100);//movimenta um pouco com o corpo pra frente
if(espera_mov()) return 0;
inverse_kinematic_right_leg(0.01, 0.005, 0, 100);//abaixa pé direito
inclina_plano(LEG_RIGHT, 0, 40, 0);
inclina_plano(LEG_LEFT, 0, 40, 0);
if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, 50, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 50, 40, 0);  //inclina para direita
if(espera_mov()) return 0;
inclina_plano(LEG_LEFT, 56, 40, 0);
inverse_kinematic_left_leg(-0.01, 0.02, 0, 300); //levanta pé esquerdo
if(espera_mov()) return 0;
}

inverse_kinematic_left_leg(0, 0.02, 0, 300);
if(espera_mov()) return 0;
inverse_kinematic_right_leg(0, 0.005, 0, 100);
inverse_kinematic_left_leg(0, 0.006, 0, 100);
if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, 0, 40, 0);
inclina_plano(LEG_LEFT, 0, 40, 0);
if(espera_mov()) return 0;
inverse_kinematic_right_leg(0, 0, 0, 300);
inverse_kinematic_left_leg(0, 0, 0, 300);

return 0;
}
//===================================================================================
//-----------------------------------------------------------------------------------
int andar_rapido(int passo)
{

#define ALTURA_PE 0.03
#define LARGURA_PASSO 0.042 // Largura do passo
#define MEIO_PASSO 0.021    // MEIO_PASSO = LARGURA_PASSO/2
#define PASSO_3DE4 0.0315    // PASSO_3DE4 = LARGURA_PASSO*(3/4)
#define PASSO_1DE4 0.0105    // PASSO_1DE4 = LARGURA_PASSO*(1/4)

//dxl_write_word(3, MOVING_SPEED, 270);
//dxl_write_word(3, P_GOAL_POSITION_L, 838);

//dxl_write_word(6, MOVING_SPEED, 270);
//dxl_write_word(6, P_GOAL_POSITION_L, 178);

if(espera_mov()) return 0; // Aguarda termino de alguma atividade

inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.009, 0, 500); //abaixa o corpo
usleep(100000);

inclina_plano(LEG_RIGHT, 54, 45, 0); // inclina para direita
inclina_plano(LEG_LEFT, 56, 45, 0);  // inclina para direita
usleep(100000);
inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.010, 0, 600); //abaixa o corpo
usleep(80000);
inverse_kinematic_right_leg(0, 0.008, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.012, 0, 300); //abaixa o corpo
usleep(70000);
//if(espera_mov_legs()) return 0;
inclina_plano(LEG_RIGHT, 70, 50, 0); // inclina para direita - 45
inclina_plano(LEG_LEFT, 64, 45, 0); // 40

// Levanta pé curva de aceleração e desaceleração -----
inverse_kinematic_left_leg(0, ALTURA_PE-0.02, 0, 300); // levanta pé esquerdo
usleep(54000);
inverse_kinematic_left_leg(0, ALTURA_PE-0.01, 0, 700); // levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(PASSO_1DE4, ALTURA_PE, 0, 400); // levanta pé esquerdo
usleep(65000);
//-------------------------------------------

//-------------------------------------------------------------
// Compensação pelo torque do pé direito
avoid_swing_right();
//-------------------------------------------------------------


//for(int x=0; x<2; x++)
while(DECISION_ACTION_A == 1)
{

// avança o pé esquerdo -------------------------------
//inclina_plano(LEG_LEFT, 60, 30, 0);
inclina_plano(LEG_LEFT, 96, 600, -15);
inverse_kinematic_left_leg(PASSO_3DE4, ALTURA_PE, 0, 400); // avança pé esquerdo
usleep(35000);
inverse_kinematic_left_leg(LARGURA_PASSO, ALTURA_PE+.01, -6, 700); // avança pé esquerdo
usleep(55000);
inverse_kinematic_left_leg(LARGURA_PASSO, ALTURA_PE, -4, 300); // avança pé esquerdo
//if(espera_mov()) return 0;
usleep(70000);
inclina_plano(LEG_LEFT, 96, 65, -20);

//-----------------------------------------------------
//if(espera_mov()) return 0;
//---- abaixa pé --------------------------------------
inclina_plano(LEG_RIGHT, 55, 45, 5);
inverse_kinematic_right_leg(0, 0.008, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 350); //abaixa pé esquerdo
usleep(30000);
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 600); //abaixa pé esquerdo
usleep(50000);
inverse_kinematic_right_leg(0, 0.007, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.02, 2, 200); //abaixa pé esquerdo
//if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, 50, 45, 5);
inclina_plano(LEG_LEFT, 80, 60, -20);
usleep(60000);
//-----------------------------------------------------
inclina_plano(LEG_RIGHT, 45, 100, 0);
inclina_plano(LEG_LEFT, 65, 60, 0);
inverse_kinematic_left_leg(MEIO_PASSO, 0.014, 0, 200);
inverse_kinematic_right_leg(-MEIO_PASSO, 0.008, -1, 100);

//---- volta da inclinação -----------------------------
inclina_plano(LEG_RIGHT, 0, 70, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, -20, 70, 0);  // volta da inclinação ficando reto
usleep(10000);
inclina_plano(LEG_RIGHT, 0, 100, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, -10, 100, 0);  // volta da inclinação ficando reto
usleep(35000);
inverse_kinematic_left_leg(MEIO_PASSO, 0.010, 0, 100);
inclina_plano(LEG_RIGHT, 0, 50, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 50, 0);  // volta da inclinação ficando reto
if(espera_mov_legs()) return 0;
//------------------------------------------------------
//usleep(100000);

inclina_plano(LEG_RIGHT, -65, 55*1.2, 0); // inclina para esquerda // **editar aqui para mexer a inclinacao do andar**
inclina_plano(LEG_LEFT, -45, 38*1.2, 0);  // inclina para esquerda
inverse_kinematic_left_leg(PASSO_1DE4, 0.008, 3, 100*0.4);
inverse_kinematic_right_leg(-PASSO_3DE4, 0.0095, 2, 120*0.4);
if(espera_mov_legs()) return 0;
//usleep(100000);

inclina_plano(LEG_LEFT, -51, 40, -5);
inclina_plano(LEG_RIGHT, -62, 40, 0);
inverse_kinematic_left_leg(0, 0.01, 2, 100);

// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_right_leg(-LARGURA_PASSO, ALTURA_PE, 0, 300); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(-LARGURA_PASSO, ALTURA_PE, 0, 600); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(-LARGURA_PASSO+.02, ALTURA_PE, 0, 400); //levanta pé direito
//if(espera_mov_legs()) return 0;
usleep(95000);

//--------------------------------------------------------
inverse_kinematic_left_leg(0, 0.008, 2, 100); // volta com o corpo um pouco pra frente
inclina_plano(LEG_RIGHT, -90, 30, 20);//incluido posteriormente para nao raspar a perna direita----------------------=========<<
//---- avança pé direito --------------------------------
inverse_kinematic_right_leg(LARGURA_PASSO, ALTURA_PE+.005, 0, 400); // avança o pé direito
usleep(35000);
inverse_kinematic_right_leg(LARGURA_PASSO, ALTURA_PE+.005, 0, 700); // avança o pé direito
usleep(35000);
inclina_plano(LEG_RIGHT, -80, 40, 20);
inverse_kinematic_right_leg(LARGURA_PASSO, ALTURA_PE-0.005, 0, 500); // avança o pé direito
//if(espera_mov()) return 0;
usleep(70000);
//-------------------------------------------------------

inclina_plano(LEG_RIGHT, -45, 60, -10);
inclina_plano(LEG_LEFT, -38, 60, 0);

//----- abaixa pé no chão -------------------------
inverse_kinematic_left_leg(0, 0.008, 4, 80);//movimenta um pouco com o corpo pra frente
inverse_kinematic_right_leg(LARGURA_PASSO, 0.016, -5, 150); // abaixa pé sem chutar o chão
usleep(30000);
inverse_kinematic_right_leg(LARGURA_PASSO, 0.016, -5, 300); // abaixa pé sem chutar o chão
usleep(40000);
inverse_kinematic_right_leg(LARGURA_PASSO, 0.016, -5, 80); // abaixa pé sem chutar o chão
if(espera_mov_legs()) return 0;
//-------------------------------------------------

usleep(60000);
inverse_kinematic_right_leg(MEIO_PASSO, 0.012, 0, 80);
inverse_kinematic_left_leg(-MEIO_PASSO, 0.008, 0, 80);
//inclina_plano(LEG_LEFT, -36, 60, 0);

// volta da inclinação -------------------------------
inclina_plano(LEG_RIGHT, 0, 70, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 60, 0); //volta da inclinação ficando reto
usleep(10000);
inclina_plano(LEG_RIGHT, 0, 200, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 170, 0); //volta da inclinação ficando reto
usleep(32000);
inclina_plano(LEG_RIGHT, 0, 50, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 43, 0); //volta da inclinação ficando reto
if(espera_mov_legs()) return 0;
//----------------------------------------------------

inclina_plano(LEG_RIGHT, 45, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 60, 40, 0);  //inclina para direita
inverse_kinematic_right_leg(PASSO_1DE4, 0.008, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(-PASSO_3DE4, 0.009, 0, 200); //abaixa o corpo
if(espera_mov_legs()) return 0;

inclina_plano(LEG_RIGHT, 65, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 64, 40, 10);
inverse_kinematic_left_leg(-PASSO_3DE4, 0.013, 2, 100);
// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_left_leg(-LARGURA_PASSO, ALTURA_PE-0.01, 0, 300); //levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(-LARGURA_PASSO, ALTURA_PE-0.01, 0, 500); //levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(-LARGURA_PASSO+.02, ALTURA_PE-0.01, 0, 400); //levanta pé esquerdo
//if(espera_mov()) return 0;
usleep(65000);
//--------------------------------------------------------------------------------------------------------------------
// avança o pé esquerdo -------------------------------
//inclina_plano(LEG_LEFT, 60, 30, 0);
inclina_plano(LEG_RIGHT, 70, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 64, 40, 10);
inverse_kinematic_right_leg(PASSO_1DE4, 0.008, 2, 200);
usleep(65000);
}

inclina_plano(LEG_RIGHT, 60, 40, 0);
inverse_kinematic_right_leg(PASSO_1DE4, 0.008, 2, 200);
inverse_kinematic_left_leg(0, ALTURA_PE-0.005, 0, 300);
if(espera_mov_legs()) return 0;
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_left_leg(0, 0.015, 0, 100);
if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, 0, 65, 0);
inclina_plano(LEG_LEFT, 0, 65, 0);
inverse_kinematic_left_leg(0, 0.009, 0, 100);
if(espera_mov()) return 0;
inverse_kinematic_left_leg(0, 0.008, 0, 100);
usleep(50000);

inverse_kinematic_right_leg(0, 0.008, 0, 300);
inverse_kinematic_left_leg(0, 0.008, 0, 300); /* teste*/

return 0;
}

//===================================================================================
//-----------------------------------------------------------------------------------
int andar_veloz2(int passo)
{

#define ALTURA_PE 0.03
#define LARGURA_PASSO 0.044 // Largura do passo
#define MEIO_PASSO 0.022    // MEIO_PASSO = LARGURA_PASSO/2
#define PASSO_3DE4 0.033    // PASSO_3DE4 = LARGURA_PASSO*(3/4)
#define PASSO_1DE4 0.011    // PASSO_1DE4 = LARGURA_PASSO*(1/4)

//dxl_write_word(3, MOVING_SPEED, 270);
//dxl_write_word(3, P_GOAL_POSITION_L, 838);

//dxl_write_word(6, MOVING_SPEED, 270);
//dxl_write_word(6, P_GOAL_POSITION_L, 178);

if(espera_mov()) return 0; // Aguarda termino de alguma atividade
readGyroStop(0.3);

inverse_kinematic_right_leg(0, 0.008, 0, 550); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.009, 0, 550); //abaixa o corpo
usleep(100000);

inclina_plano(LEG_RIGHT, 54, 45, 0); // inclina para direita
inclina_plano(LEG_LEFT, 56, 45, 0);  // inclina para direita
usleep(100000);
inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.010, 0, 600); //abaixa o corpo
usleep(80000);
inverse_kinematic_right_leg(0, 0.008, 0, 200*1.1); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.012, 0, 300*1.1); //abaixa o corpo
usleep(70000);
readGyroStop(0.4);

//if(espera_mov_legs()) return 0;
inclina_plano(LEG_RIGHT, 70, 50, 0); // inclina para direita - 45
inclina_plano(LEG_LEFT, 64, 45, 0); // 40

// Levanta pé curva de aceleração e desaceleração -----
inverse_kinematic_left_leg(0, ALTURA_PE-0.02, 0, 300); // levanta pé esquerdo
usleep(54000);
inverse_kinematic_left_leg(0, ALTURA_PE-0.01, 0, 700); // levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(PASSO_1DE4, ALTURA_PE, 0, 400); // levanta pé esquerdo
inverse_kinematic_right_leg(0, 0.008, 3, 200); // tomba o corpo pra frente
usleep(65000);
//-------------------------------------------

//-------------------------------------------------------------
// Compensação pelo torque do pé direito
//avoid_swing_right();
//-------------------------------------------------------------


for(int x=0; x<20; x++)
//while(DECISION_ACTION_A == 1)
{
readGyroStop(0.3);

// avança o pé esquerdo -------------------------------
//inclina_plano(LEG_LEFT, 60, 30, 0);
inclina_plano(LEG_LEFT, 96, 600, -20);
inverse_kinematic_right_leg(0, 0.008, 5, 200); // tomba o corpo pra frente
inverse_kinematic_left_leg(PASSO_3DE4, ALTURA_PE, 0, 400); // avança pé esquerdo
usleep(35000);
inverse_kinematic_left_leg(LARGURA_PASSO, ALTURA_PE+.01, -4, 600); // avança pé esquerdo
usleep(55000);
inverse_kinematic_left_leg(LARGURA_PASSO, ALTURA_PE, 0, 400); // avança pé esquerdo
//if(espera_mov()) return 0;
usleep(70000);
inclina_plano(LEG_LEFT, 96, 65, -20);

//-----------------------------------------------------
//if(espera_mov()) return 0;
//---- abaixa pé --------------------------------------
inclina_plano(LEG_RIGHT, 55, 45, 5);
inverse_kinematic_right_leg(0, 0.008, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 400); //abaixa pé esquerdo
usleep(30000);
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 600); //abaixa pé esquerdo
usleep(50000);
inverse_kinematic_right_leg(0, 0.007, 2, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.02, 2, 200); //abaixa pé esquerdo
//if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, 50, 45, 5);
inclina_plano(LEG_LEFT, 80, 60, -20);
usleep(60000);
//-----------------------------------------------------
inclina_plano(LEG_RIGHT, 45, 100, 0);
inclina_plano(LEG_LEFT, 65, 60, 0);
inverse_kinematic_left_leg(MEIO_PASSO, 0.014, 0, 200);
inverse_kinematic_right_leg(-MEIO_PASSO, 0.008, 1, 100);

readGyroStop(0.3);

//---- volta da inclinação -----------------------------
inclina_plano(LEG_RIGHT, 0, 70, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, -20, 70, 0);  // volta da inclinação ficando reto
usleep(10000);
inclina_plano(LEG_RIGHT, 0, 100, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, -10, 100, 0);  // volta da inclinação ficando reto
usleep(35000);
inverse_kinematic_left_leg(MEIO_PASSO, 0.010, 0, 100);
inclina_plano(LEG_RIGHT, 0, 50, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 50, 0);  // volta da inclinação ficando reto
usleep(170000);

//if(espera_mov_legs()) return 0;

readGyroStop(0.3);

//------------------------------------------------------
//usleep(100000);

inclina_plano(LEG_RIGHT, -68, 55*0.7, 0); // inclina para esquerda // **editar aqui para mexer a inclinacao do andar**
inclina_plano(LEG_LEFT, -44, 38*1.2, 0);  // inclina para esquerda
usleep(35000);
inverse_kinematic_left_leg(PASSO_1DE4, 0.008, 3, 100*0.6);
inverse_kinematic_right_leg(-PASSO_3DE4, 0.011, 2, 120*1.3);
if(espera_mov_legs()) return 0;
//usleep(100000);

readGyroStop(0.3);

inclina_plano(LEG_LEFT, -51, 40, -5);
inclina_plano(LEG_RIGHT, -62, 40, 0);
inverse_kinematic_left_leg(0, 0.01, 2, 100);

// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_right_leg(-LARGURA_PASSO, ALTURA_PE, 0, 300); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(-LARGURA_PASSO, ALTURA_PE, 0, 700); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(-LARGURA_PASSO+.02, ALTURA_PE, 0, 500); //levanta pé direito
//if(espera_mov_legs()) return 0;
usleep(95000);

//--------------------------------------------------------
inverse_kinematic_left_leg(0, 0.008, 2, 100); // volta com o corpo um pouco pra frente
inclina_plano(LEG_RIGHT, -90, 30, 20);//incluido posteriormente para nao raspar a perna direita----------------------=========<<
//---- avança pé direito --------------------------------
inverse_kinematic_right_leg(LARGURA_PASSO, ALTURA_PE+.005, 0, 500); // avança o pé direito
usleep(35000);
inverse_kinematic_right_leg(LARGURA_PASSO, ALTURA_PE+.005, 0, 700); // avança o pé direito
usleep(35000);
inclina_plano(LEG_RIGHT, -80, 40, 20);
inverse_kinematic_right_leg(LARGURA_PASSO, ALTURA_PE-0.005, 0, 500); // avança o pé direito
//if(espera_mov()) return 0;
usleep(70000);
//-------------------------------------------------------

inclina_plano(LEG_RIGHT, -45, 60, -10);
inclina_plano(LEG_LEFT, -38, 60, 0);

//----- abaixa pé no chão -------------------------
inverse_kinematic_left_leg(0, 0.008, 4, 80);//movimenta um pouco com o corpo pra frente
inverse_kinematic_right_leg(LARGURA_PASSO, 0.016, -5, 150); // abaixa pé sem chutar o chão
usleep(30000);
inverse_kinematic_right_leg(LARGURA_PASSO, 0.016, -3, 300); // abaixa pé sem chutar o chão
usleep(40000);
inverse_kinematic_right_leg(LARGURA_PASSO, 0.016, 0, 80); // abaixa pé sem chutar o chão
if(espera_mov_legs()) return 0;
//-------------------------------------------------

readGyroStop(0.3);

usleep(60000);
inverse_kinematic_right_leg(MEIO_PASSO, 0.012, 0, 80);
inverse_kinematic_left_leg(-MEIO_PASSO, 0.008, 0, 80);
//inclina_plano(LEG_LEFT, -36, 60, 0);

// volta da inclinação -------------------------------
inclina_plano(LEG_RIGHT, 0, 70, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 60, 0); //volta da inclinação ficando reto
usleep(10000);
inclina_plano(LEG_RIGHT, 0, 200, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 170, 0); //volta da inclinação ficando reto
usleep(32000);
inclina_plano(LEG_RIGHT, 0, 50, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 43, 0); //volta da inclinação ficando reto
usleep(170000);
//if(espera_mov_legs()) return 0;
//----------------------------------------------------

readGyroStop(0.3);

inclina_plano(LEG_RIGHT, 45, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 60, 40, 0);  //inclina para direita
inverse_kinematic_right_leg(PASSO_1DE4, 0.008, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(-PASSO_3DE4, 0.009, 0, 200); //abaixa o corpo
if(espera_mov_legs()) return 0;
readGyroStop(0.3);

inclina_plano(LEG_RIGHT, 65, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 64, 40, 10);
inverse_kinematic_left_leg(-PASSO_3DE4, 0.013, 2, 100);
// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_left_leg(-LARGURA_PASSO, ALTURA_PE-0.01, 0, 300); //levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(-LARGURA_PASSO, ALTURA_PE-0.01, 0, 700); //levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(-LARGURA_PASSO+.02, ALTURA_PE-0.01, 0, 400); //levanta pé esquerdo
inverse_kinematic_right_leg(0, 0.008, 3, 200); // tomba o corpo pra frente
//if(espera_mov()) return 0;
usleep(65000);
//--------------------------------------------------------------------------------------------------------------------
// avança o pé esquerdo -------------------------------
//inclina_plano(LEG_LEFT, 60, 30, 0);
inclina_plano(LEG_RIGHT, 70, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 64, 40, 10);
inverse_kinematic_right_leg(PASSO_1DE4, 0.008, 3, 200);
usleep(65000);
}

inclina_plano(LEG_RIGHT, 60, 40, 0);
inverse_kinematic_right_leg(PASSO_1DE4, 0.008, 2, 200);
inverse_kinematic_left_leg(0, ALTURA_PE-0.005, 0, 300);
if(espera_mov_legs()) return 0;
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_left_leg(0, 0.015, 0, 100);
if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, 0, 65, 0);
inclina_plano(LEG_LEFT, 0, 65, 0);
inverse_kinematic_left_leg(0, 0.009, 0, 100);
if(espera_mov()) return 0;
inverse_kinematic_left_leg(0, 0.008, 0, 100);
usleep(50000);

inverse_kinematic_right_leg(0, 0.008, 0, 300);
inverse_kinematic_left_leg(0, 0.008, 0, 300); /* teste*/

return 0;
}

//======================================================================================
//--------------------------------------------------------------------------------------
int andar_veloz(int passo)
{

#
#define ALTURA_PE 0.03
#define LARGURA_PASSO 0.044 // Largura do passo
#define MEIO_PASSO 0.022    // MEIO_PASSO = LARGURA_PASSO/2
#define PASSO_3DE4 0.033    // PASSO_3DE4 = LARGURA_PASSO*(3/4)
#define PASSO_1DE4 0.011    // PASSO_1DE4 = LARGURA_PASSO*(1/4)

//dxl_write_word(3, MOVING_SPEED, 270);
//dxl_write_word(3, P_GOAL_POSITION_L, 838);

//dxl_write_word(6, MOVING_SPEED, 270);
//dxl_write_word(6, P_GOAL_POSITION_L, 178);

if(espera_mov()) return 0; // Aguarda termino de alguma atividade

inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.009, 0, 500); //abaixa o corpo
usleep(100000);

inclina_plano(LEG_RIGHT, 54, 45, 0); // inclina para direita
inclina_plano(LEG_LEFT, 56, 45, 0);  // inclina para direita
usleep(100000);
inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.010, 0, 600); //abaixa o corpo
usleep(80000);
inverse_kinematic_right_leg(0, 0.008, 0, 200*1.1); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.012, 0, 300*1.1); //abaixa o corpo
usleep(70000);
//if(espera_mov_legs()) return 0;
inclina_plano(LEG_RIGHT, 70, 50, 0); // inclina para direita - 45
inclina_plano(LEG_LEFT, 64, 45, 0); // 40

// Levanta pé curva de aceleração e desaceleração -----
inverse_kinematic_left_leg(0, ALTURA_PE-0.02, 0, 300); // levanta pé esquerdo
usleep(54000);
inverse_kinematic_left_leg(0, ALTURA_PE-0.01, 0, 700); // levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(PASSO_1DE4, ALTURA_PE, 0, 400); // levanta pé esquerdo
usleep(65000);
//-------------------------------------------

//-------------------------------------------------------------
// Compensação pelo torque do pé direito
//avoid_swing_right();
//-------------------------------------------------------------


//for(int x=0; x<2; x++)
while(DECISION_ACTION_A == 1)
{

// avança o pé esquerdo -------------------------------
//inclina_plano(LEG_LEFT, 60, 30, 0);
inclina_plano(LEG_LEFT, 96, 600, -15);
inverse_kinematic_left_leg(PASSO_3DE4, ALTURA_PE, 0, 400); // avança pé esquerdo
usleep(35000);
inverse_kinematic_left_leg(LARGURA_PASSO, ALTURA_PE+.01, -6, 700); // avança pé esquerdo
usleep(55000);
inverse_kinematic_left_leg(LARGURA_PASSO, ALTURA_PE, -4, 400); // avança pé esquerdo
//if(espera_mov()) return 0;
usleep(70000);
inclina_plano(LEG_LEFT, 96, 65, -20);

//-----------------------------------------------------
//if(espera_mov()) return 0;
//---- abaixa pé --------------------------------------
inclina_plano(LEG_RIGHT, 55, 45, 5);
inverse_kinematic_right_leg(0, 0.008, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 400); //abaixa pé esquerdo
usleep(30000);
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 600); //abaixa pé esquerdo
usleep(50000);
inverse_kinematic_right_leg(0, 0.007, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.02, 2, 200); //abaixa pé esquerdo
//if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, 50, 45, 5);
inclina_plano(LEG_LEFT, 80, 60, -20);
usleep(60000);
//-----------------------------------------------------
inclina_plano(LEG_RIGHT, 45, 100, 0);
inclina_plano(LEG_LEFT, 65, 60, 0);
inverse_kinematic_left_leg(MEIO_PASSO, 0.014, 0, 200);
inverse_kinematic_right_leg(-MEIO_PASSO, 0.008, -1, 100);

//---- volta da inclinação -----------------------------
inclina_plano(LEG_RIGHT, 0, 70, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, -20, 70, 0);  // volta da inclinação ficando reto
usleep(10000);
inclina_plano(LEG_RIGHT, 0, 100, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, -10, 100, 0);  // volta da inclinação ficando reto
usleep(35000);
inverse_kinematic_left_leg(MEIO_PASSO, 0.010, 0, 100);
inclina_plano(LEG_RIGHT, 0, 50, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 50, 0);  // volta da inclinação ficando reto
//usleep(150000);
if(espera_mov_legs()) return 0;

//------------------------------------------------------
//usleep(100000);

inclina_plano(LEG_RIGHT, -65, 55*1.2, 0); // inclina para esquerda // **editar aqui para mexer a inclinacao do andar**
inclina_plano(LEG_LEFT, -45, 38*1.2, 0);  // inclina para esquerda
inverse_kinematic_left_leg(PASSO_1DE4, 0.008, 3, 100*0.4);
inverse_kinematic_right_leg(-PASSO_3DE4, 0.0095, 2, 120*0.4);
if(espera_mov_legs()) return 0;
//usleep(100000);

inclina_plano(LEG_LEFT, -51, 40, -5);
inclina_plano(LEG_RIGHT, -62, 40, 0);
inverse_kinematic_left_leg(0, 0.01, 2, 100);

// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_right_leg(-LARGURA_PASSO, ALTURA_PE, 0, 300); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(-LARGURA_PASSO, ALTURA_PE, 0, 700); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(-LARGURA_PASSO+.02, ALTURA_PE, 0, 500); //levanta pé direito
//if(espera_mov_legs()) return 0;
usleep(95000);

//--------------------------------------------------------
inverse_kinematic_left_leg(0, 0.008, 2, 100); // volta com o corpo um pouco pra frente
inclina_plano(LEG_RIGHT, -90, 30, 20);//incluido posteriormente para nao raspar a perna direita----------------------=========<<
//---- avança pé direito --------------------------------
inverse_kinematic_right_leg(LARGURA_PASSO, ALTURA_PE+.005, 0, 500); // avança o pé direito
usleep(35000);
inverse_kinematic_right_leg(LARGURA_PASSO, ALTURA_PE+.005, 0, 700); // avança o pé direito
usleep(35000);
inclina_plano(LEG_RIGHT, -80, 40, 20);
inverse_kinematic_right_leg(LARGURA_PASSO, ALTURA_PE-0.005, 0, 500); // avança o pé direito
//if(espera_mov()) return 0;
usleep(70000);
//-------------------------------------------------------

inclina_plano(LEG_RIGHT, -45, 60, -10);
inclina_plano(LEG_LEFT, -38, 60, 0);

//----- abaixa pé no chão -------------------------
inverse_kinematic_left_leg(0, 0.008, 4, 80);//movimenta um pouco com o corpo pra frente
inverse_kinematic_right_leg(LARGURA_PASSO, 0.016, -5, 150); // abaixa pé sem chutar o chão
usleep(30000);
inverse_kinematic_right_leg(LARGURA_PASSO, 0.016, -5, 300); // abaixa pé sem chutar o chão
usleep(40000);
inverse_kinematic_right_leg(LARGURA_PASSO, 0.016, -5, 80); // abaixa pé sem chutar o chão
if(espera_mov_legs()) return 0;
//-------------------------------------------------

usleep(60000);
inverse_kinematic_right_leg(MEIO_PASSO, 0.012, 0, 80);
inverse_kinematic_left_leg(-MEIO_PASSO, 0.008, 0, 80);
//inclina_plano(LEG_LEFT, -36, 60, 0);

// volta da inclinação -------------------------------
inclina_plano(LEG_RIGHT, 0, 70, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 60, 0); //volta da inclinação ficando reto
usleep(10000);
inclina_plano(LEG_RIGHT, 0, 200, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 170, 0); //volta da inclinação ficando reto
usleep(32000);
inclina_plano(LEG_RIGHT, 0, 50, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 43, 0); //volta da inclinação ficando reto
if(espera_mov_legs()) return 0;
//----------------------------------------------------

inclina_plano(LEG_RIGHT, 45, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 60, 40, 0);  //inclina para direita
inverse_kinematic_right_leg(PASSO_1DE4, 0.008, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(-PASSO_3DE4, 0.009, 0, 200); //abaixa o corpo
if(espera_mov_legs()) return 0;

inclina_plano(LEG_RIGHT, 65, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 64, 40, 10);
inverse_kinematic_left_leg(-PASSO_3DE4, 0.013, 2, 100);
// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_left_leg(-LARGURA_PASSO, ALTURA_PE-0.01, 0, 300); //levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(-LARGURA_PASSO, ALTURA_PE-0.01, 0, 700); //levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(-LARGURA_PASSO+.02, ALTURA_PE-0.01, 0, 400); //levanta pé esquerdo
//if(espera_mov()) return 0;
usleep(65000);
//--------------------------------------------------------------------------------------------------------------------
// avança o pé esquerdo -------------------------------
//inclina_plano(LEG_LEFT, 60, 30, 0);
inclina_plano(LEG_RIGHT, 70, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 64, 40, 10);
inverse_kinematic_right_leg(PASSO_1DE4, 0.008, 2, 200);
usleep(65000);
}

inclina_plano(LEG_RIGHT, 60, 40, 0);
inverse_kinematic_right_leg(PASSO_1DE4, 0.008, 2, 200);
inverse_kinematic_left_leg(0, ALTURA_PE-0.005, 0, 300);
if(espera_mov_legs()) return 0;
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_left_leg(0, 0.015, 0, 100);
if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, 0, 65, 0);
inclina_plano(LEG_LEFT, 0, 65, 0);
inverse_kinematic_left_leg(0, 0.009, 0, 100);
if(espera_mov()) return 0;
inverse_kinematic_left_leg(0, 0.008, 0, 100);
usleep(50000);

inverse_kinematic_right_leg(0, 0.008, 0, 300);
inverse_kinematic_left_leg(0, 0.008, 0, 300); /* teste*/

return 0;
}


//===================================================================================
//-----------------------------------------------------------------------------------
int andar_lento()
{

#define ALTURA_PE 0.03
#define LARGURA_PASSO 0.042 // Largura do passo

if(espera_mov()) return 0; // Aguarda termino de alguma atividade

inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.009, 0, 500); //abaixa o corpo
usleep(100000);

inclina_plano(LEG_RIGHT, 54, 45, 0); // inclina para direita
inclina_plano(LEG_LEFT, 56, 45, 0);  // inclina para direita
usleep(100000);
inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.010, 0, 600); //abaixa o corpo
usleep(80000);
inverse_kinematic_right_leg(0, 0.008, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.012, 0, 300); //abaixa o corpo
usleep(70000);
inclina_plano(LEG_RIGHT, 70, 50, 0); // inclina para direita - 45
inclina_plano(LEG_LEFT, 64, 45, 0); // 40

// Levanta pé curva de aceleração e desaceleração -----
inverse_kinematic_left_leg(0, ALTURA_PE-0.02, 0, 300); // levanta pé esquerdo
usleep(54000);
inverse_kinematic_left_leg(0, ALTURA_PE-0.01, 0, 700); // levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(PASSO_1DE4, ALTURA_PE, 0, 400); // levanta pé esquerdo
usleep(65000);
//-------------------------------------------

//-------------------------------------------------------------
// Compensação pelo torque do pé direito
//avoid_swing_right();
//-------------------------------------------------------------


//for(int x=0; x<2; x++)
//while(DECISION_ACTION_A == 1)
//{

// avança o pé esquerdo -------------------------------
//inclina_plano(LEG_LEFT, 60, 30, 0);
inclina_plano(LEG_LEFT, 96, 600, -15);
inverse_kinematic_left_leg(PASSO_3DE4, ALTURA_PE, 0, 400); // avança pé esquerdo
usleep(35000);
inverse_kinematic_left_leg(LARGURA_PASSO, ALTURA_PE+.01, -6, 700); // avança pé esquerdo
usleep(55000);
inverse_kinematic_left_leg(LARGURA_PASSO, ALTURA_PE, -4, 400); // avança pé esquerdo
//if(espera_mov()) return 0;
usleep(70000);
inclina_plano(LEG_LEFT, 96, 65, -20);

//-----------------------------------------------------
//if(espera_mov()) return 0;
//---- abaixa pé --------------------------------------
inclina_plano(LEG_RIGHT, 55, 45, 5);
inverse_kinematic_right_leg(0, 0.008, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 400); //abaixa pé esquerdo
usleep(30000);
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 600); //abaixa pé esquerdo
usleep(50000);
inverse_kinematic_right_leg(0, 0.007, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.02, 2, 200); //abaixa pé esquerdo
//if(espera_mov()) return 0;
inclina_plano(LEG_RIGHT, 50, 45, 5);
inclina_plano(LEG_LEFT, 80, 60, -20);
usleep(60000);

//-----------------------------------------------------
inclina_plano(LEG_RIGHT, 45, 100, 0);
inclina_plano(LEG_LEFT, 65, 60, 0);
inverse_kinematic_left_leg(MEIO_PASSO, 0.014, 0, 200);
inverse_kinematic_right_leg(-MEIO_PASSO, 0.008, -1, 100);

//---- volta da inclinação -----------------------------
inclina_plano(LEG_RIGHT, 0, 70, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, -20, 70, 0);  // volta da inclinação ficando reto
usleep(10000);
inclina_plano(LEG_RIGHT, 0, 100, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, -10, 100, 0);  // volta da inclinação ficando reto
usleep(35000);
inverse_kinematic_left_leg(0, 0.010, 0, 100);
inclina_plano(LEG_RIGHT, 0, 50, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 50, 0);  // volta da inclinação ficando reto
if(espera_mov_legs()) return 0;

//------------------------------------------------------
//usleep(100000);

inclina_plano(LEG_RIGHT, -65, 55*1.5, 0); // inclina para esquerda // **editar aqui para mexer a inclinacao do andar**
inclina_plano(LEG_LEFT, -45, 38*1.5, 0);  // inclina para esquerda
inverse_kinematic_left_leg(PASSO_1DE4, 0.008, 3, 100*0.5);
inverse_kinematic_right_leg(-PASSO_3DE4, 0.0095, 2, 120*0.5);
if(espera_mov_legs()) return 0;
//usleep(100000);

inclina_plano(LEG_LEFT, -51, 50, -5);
inclina_plano(LEG_RIGHT, -62, 50, 0);
inverse_kinematic_left_leg(0, 0.01, 2, 120);

// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_right_leg(-LARGURA_PASSO, ALTURA_PE, 0, 300); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(-LARGURA_PASSO-0.02, ALTURA_PE, 0, 700); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(0, ALTURA_PE, 0, 300); //levanta pé direito
//if(espera_mov_legs()) return 0;
usleep(100000);

inverse_kinematic_right_leg(0, 0.012, 0, 120);
inverse_kinematic_left_leg(0, 0.008, 0, 120);
usleep(70000);

// volta da inclinação -------------------------------
inclina_plano(LEG_RIGHT, 0, 70*1.2, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 60*1.2, 0); //volta da inclinação ficando reto
usleep(10000);
inclina_plano(LEG_RIGHT, 0, 200, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 170, 0); //volta da inclinação ficando reto
usleep(32000);
inclina_plano(LEG_RIGHT, 0, 50, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 43, 0); //volta da inclinação ficando reto
if(espera_mov_legs()) return 0;

inverse_kinematic_right_leg(0, 0.008, 0, 300);
inverse_kinematic_left_leg(0, 0.008, 0, 300); /* teste*/

return 0;
}
