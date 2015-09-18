#include <dynamixel.h>
#include <unistd.h>
#include <blackboard.h>

void andar()
{
robo_ereto();
espera_mov();

inclina_plano(LEG_RIGHT, 50, 40, 0); // inclina para direita
inclina_plano(LEG_LEFT, 50, 40, 0);  // inclina para direita
espera_mov();
inclina_plano(LEG_LEFT, 56, 40, 0);
inverse_kinematic_left_leg(0, 0.02, 0, 300); // levanta pé esquerdo
espera_mov();
for(int x=0; x<3; x++)
{
inverse_kinematic_left_leg(0.02, 0.02, 0, 100); // avança pé esquerdo
espera_mov();
inverse_kinematic_right_leg(-0.01, 0.005, 0, 200); // moviemnta corpo pra frente
inverse_kinematic_left_leg(0.01, 0.006, 0, 200); //abaixa pé esquerdo
inclina_plano(LEG_RIGHT, 40, 60, 0);
inclina_plano(LEG_LEFT, 40, 60, 0);
espera_mov();
inverse_kinematic_left_leg(0.01, 0.005, 0, 300);
inclina_plano(LEG_RIGHT, 0, 40, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 40, 0);  // volta da inclinação ficando reto
espera_mov();
sleep(1);
inclina_plano(LEG_RIGHT, -45, 40, 0); // inclina para esquerda
inclina_plano(LEG_LEFT, -48, 40, 0);  // inclina para esquerda
espera_mov();
inclina_plano(LEG_LEFT, -55, 40, 0);
inclina_plano(LEG_RIGHT, -58, 40, 0);
inverse_kinematic_left_leg(0, 0.005, 0, 100); // volta com o corpo um pouco pra frente
inverse_kinematic_right_leg(-0.01, 0.03, -10, 300); //levanta pé direito
espera_mov();
inverse_kinematic_right_leg(0.02, 0.03, -10, 100); // avança o pé direito
espera_mov();
inclina_plano(LEG_RIGHT, -40, 60, 0);
inclina_plano(LEG_LEFT, -40, 60, 0);
inverse_kinematic_right_leg(0.01, 0.01, -5, 100); // abaixa pé sem chutar o chão
inverse_kinematic_left_leg(-0.01, 0.005, 0, 100);//movimenta um pouco com o corpo pra frente
espera_mov();
inverse_kinematic_right_leg(0.01, 0.005, 0, 100);//abaixa pé direito
inclina_plano(LEG_RIGHT, 0, 40, 0);
inclina_plano(LEG_LEFT, 0, 40, 0);
espera_mov();
inclina_plano(LEG_RIGHT, 50, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 50, 40, 0);  //inclina para direita
espera_mov();
inclina_plano(LEG_LEFT, 56, 40, 0);
inverse_kinematic_left_leg(-0.01, 0.02, 0, 300); //levanta pé esquerdo
espera_mov();
}

inverse_kinematic_left_leg(0, 0.02, 0, 300);
espera_mov();
inverse_kinematic_right_leg(0, 0.005, 0, 100);
inverse_kinematic_left_leg(0, 0.006, 0, 100);
espera_mov();
inclina_plano(LEG_RIGHT, 0, 40, 0);
inclina_plano(LEG_LEFT, 0, 40, 0);
espera_mov();
inverse_kinematic_right_leg(0, 0, 0, 300);
inverse_kinematic_left_leg(0, 0, 0, 300);

}
//===================================================================================
//-----------------------------------------------------------------------------------
void andar_rapido(int passo)
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

espera_mov(); // Aguarda termino de alguma atividade

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
//espera_mov_legs();
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
//espera_mov();
usleep(70000);
inclina_plano(LEG_LEFT, 96, 65, -20);

//-----------------------------------------------------
//espera_mov();
//---- abaixa pé --------------------------------------
inclina_plano(LEG_RIGHT, 55, 45, 5);
inverse_kinematic_right_leg(0, 0.008, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 350); //abaixa pé esquerdo
usleep(30000);
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 600); //abaixa pé esquerdo
usleep(50000);
inverse_kinematic_right_leg(0, 0.007, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.02, 2, 200); //abaixa pé esquerdo
//espera_mov();
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
espera_mov_legs();
//------------------------------------------------------
//usleep(100000);

inclina_plano(LEG_RIGHT, -65, 55*1.2, 0); // inclina para esquerda // **editar aqui para mexer a inclinacao do andar**
inclina_plano(LEG_LEFT, -45, 38*1.2, 0);  // inclina para esquerda
inverse_kinematic_left_leg(PASSO_1DE4, 0.008, 3, 100*0.4);
inverse_kinematic_right_leg(-PASSO_3DE4, 0.0095, 2, 120*0.4);
espera_mov_legs();
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
//espera_mov_legs();
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
//espera_mov();
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
espera_mov_legs();
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
espera_mov_legs();
//----------------------------------------------------

inclina_plano(LEG_RIGHT, 45, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 60, 40, 0);  //inclina para direita
inverse_kinematic_right_leg(PASSO_1DE4, 0.008, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(-PASSO_3DE4, 0.009, 0, 200); //abaixa o corpo
espera_mov_legs();

inclina_plano(LEG_RIGHT, 65, 40, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 64, 40, 10);
inverse_kinematic_left_leg(-PASSO_3DE4, 0.013, 2, 100);
// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_left_leg(-LARGURA_PASSO, ALTURA_PE-0.01, 0, 300); //levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(-LARGURA_PASSO, ALTURA_PE-0.01, 0, 500); //levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(-LARGURA_PASSO+.02, ALTURA_PE-0.01, 0, 400); //levanta pé esquerdo
//espera_mov();
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
espera_mov_legs();
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_left_leg(0, 0.015, 0, 100);
espera_mov();
inclina_plano(LEG_RIGHT, 0, 65, 0);
inclina_plano(LEG_LEFT, 0, 65, 0);
inverse_kinematic_left_leg(0, 0.009, 0, 100);
espera_mov();
inverse_kinematic_left_leg(0, 0.008, 0, 100);
usleep(50000);

inverse_kinematic_right_leg(0, 0.008, 0, 300);
inverse_kinematic_left_leg(0, 0.008, 0, 300); /* teste*/


}

//===================================================================================
//-----------------------------------------------------------------------------------
void andar_veloz(int passo)
{

#define ALTURA_PE_v 0.035
#define LARGURA_PASSO_v 0.07   // Largura do passo
#define MEIO_PASSO_v 0.035     // MEIO_PASSO_v = LARGURA_PASSO/2
#define PASSO_3DE4_v 0.0525    // PASSO_3DE4_v = LARGURA_PASSO*(3/4)
#define PASSO_1DE4_v 0.0175    // PASSO_1DE4_v = LARGURA_PASSO*(1/4)

espera_mov(); // Aguarda termino de alguma atividade

inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.009, 0, 500); //abaixa o corpo
usleep(100000);

inclina_plano(LEG_RIGHT, 60, 45, 0); // inclina para direita
inclina_plano(LEG_LEFT, 64, 45, 0);  // inclina para direita
usleep(100000);
inverse_kinematic_right_leg(0, 0.008, 0, 500); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.010, 0, 600); //abaixa o corpo
usleep(100000);
inverse_kinematic_right_leg(0, 0.008, 0, 200); // abaixa o corpo
inverse_kinematic_left_leg(0, 0.012, 0, 300); //abaixa o corpo
espera_mov_legs();
inclina_plano(LEG_RIGHT, 68, 50, 0); // inclina para direita - 45
inclina_plano(LEG_LEFT, 64, 45, 0); // 40

// Levanta pé curva de aceleração e desaceleração -----
inverse_kinematic_left_leg(0, ALTURA_PE_v-0.01, 0, 300); // levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(0, ALTURA_PE_v-0.005, 0, 600); // levanta pé esquerdo
usleep(40000);
inverse_kinematic_left_leg(PASSO_1DE4_v, ALTURA_PE_v-0.005, 0, 600); // levanta pé esquerdo
inclina_plano(LEG_RIGHT, 67, 40, 0); // inclina para direita
//espera_mov();
usleep(55000);
//-------------------------------------------


for(int x=0; x<2; x++)
{
// avança o pé esquerdo -------------------------------
inclina_plano(LEG_LEFT, 54, 30, 2);
inverse_kinematic_left_leg(PASSO_3DE4_v, ALTURA_PE_v, 0, 600); // avança pé esquerdo
usleep(35000);
inverse_kinematic_left_leg(LARGURA_PASSO_v, ALTURA_PE_v+.01, 7, 900); // avança pé esquerdo
usleep(35000);
inverse_kinematic_left_leg(LARGURA_PASSO_v, ALTURA_PE_v, 7, 500); // avança pé esquerdo
//espera_mov();
usleep(40000);

//-----------------------------------------------------
//espera_mov();
//---- abaixa pé --------------------------------------
inclina_plano(LEG_RIGHT, 50, 45, 5);
inclina_plano(LEG_LEFT, 52, 40, 5);
inverse_kinematic_right_leg(0, 0.008, 0, 80); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO_v, 0.025, 5, 500); //abaixa pé esquerdo
usleep(30000);
inverse_kinematic_left_leg(LARGURA_PASSO_v, 0.02, -5, 800); //abaixa pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(LARGURA_PASSO_v, 0.015, -5, 300); //abaixa pé esquerdo
//espera_mov();
usleep(40000);

//-----------------------------------------------------
inclina_plano(LEG_RIGHT, 45, 60, 0);
inclina_plano(LEG_LEFT, 50, 60, -10);
espera_mov();

//usleep(70000);
inverse_kinematic_left_leg(MEIO_PASSO_v, 0.01, 0, 100);
inverse_kinematic_right_leg(-MEIO_PASSO_v, 0.008, 2, 100);

//---- volta da inclinação -----------------------------
inclina_plano(LEG_RIGHT, 0, 60, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 65, 0);  // volta da inclinação ficando reto
usleep(10000);
inclina_plano(LEG_RIGHT, 0, 150, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 170, 0);  // volta da inclinação ficando reto
usleep(45000);
inclina_plano(LEG_RIGHT, 0, 50, 0); // volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 55, 0);  // volta da inclinação ficando reto
espera_mov();
//------------------------------------------------------
//usleep(100000);

inclina_plano(LEG_RIGHT, -50, 45, -10); // inclina para esquerda
inclina_plano(LEG_LEFT, -41, 45, 0);  // inclina para esquerda
inverse_kinematic_left_leg(PASSO_1DE4_v, 0.008, 5, 100); //==============================Ponto sensivel a queda =========
inverse_kinematic_right_leg(-PASSO_3DE4_v, 0.013, 0, 200); //==============================Ponto sensivel a queda =========
espera_mov_legs();

inclina_plano(LEG_LEFT, -50, 40, 0);
inclina_plano(LEG_RIGHT, -58, 40, -10);
inverse_kinematic_left_leg(0, 0.01, 4, 100);

// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_right_leg(-LARGURA_PASSO_v, ALTURA_PE_v, -5, 300); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(-LARGURA_PASSO_v, ALTURA_PE_v, -7, 600); //levanta pé direito
usleep(50000);
inverse_kinematic_right_leg(-LARGURA_PASSO_v+.02, ALTURA_PE_v+.005, -7, 500); //levanta pé direito
//espera_mov();
usleep(60000);
//--------------------------------------------------------
inverse_kinematic_left_leg(0, 0.008, 2, 100); // volta com o corpo um pouco pra frente

//---- avança pé direito --------------------------------
inverse_kinematic_right_leg(LARGURA_PASSO_v, ALTURA_PE_v+.005, -5, 500); // avança o pé direito
usleep(35000);
inverse_kinematic_right_leg(LARGURA_PASSO_v, ALTURA_PE_v+.005, -5, 700); // avança o pé direito
usleep(65000);
inverse_kinematic_right_leg(LARGURA_PASSO_v, ALTURA_PE_v-0.005, 0, 500); // avança o pé direito
//espera_mov();
usleep(70000);
//-------------------------------------------------------

inclina_plano(LEG_RIGHT, -40, 60, -10);
inclina_plano(LEG_LEFT, -40, 60, 0);

//----- abaixa pé no chão -------------------------
inverse_kinematic_left_leg(0, 0.008, 4, 80);//movimenta um pouco com o corpo pra frente
inverse_kinematic_right_leg(LARGURA_PASSO_v, 0.02, -5, 150); // abaixa pé sem chutar o chão
usleep(30000);
inverse_kinematic_right_leg(LARGURA_PASSO_v, 0.02, -5, 300); // abaixa pé sem chutar o chão
usleep(50000);
inverse_kinematic_right_leg(LARGURA_PASSO_v, 0.019, -2, 80); // abaixa pé sem chutar o chão
espera_mov();

//-------------------------------------------------
//usleep(65000);
inverse_kinematic_right_leg(MEIO_PASSO_v, 0.01, 0, 80);
inverse_kinematic_left_leg(-MEIO_PASSO_v, 0.008, 0, 80);

// volta da inclinação -------------------------------
inclina_plano(LEG_RIGHT, 0, 65, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 65, 0); //volta da inclinação ficando reto
usleep(10000);
inclina_plano(LEG_RIGHT, 0, 200, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 200, 0); //volta da inclinação ficando reto
usleep(32000);
inclina_plano(LEG_RIGHT, 0, 50, 0);//volta da inclinação ficando reto
inclina_plano(LEG_LEFT, 0, 50, 0); //volta da inclinação ficando reto
espera_mov();

//----------------------------------------------------
inclina_plano(LEG_RIGHT, 50, 50, 0); //inclina para a direita
inclina_plano(LEG_LEFT, 46, 50, 0);  //inclina para direita
inverse_kinematic_right_leg(PASSO_1DE4_v, 0.008, 2, 100); // abaixa o corpo//==============================Ponto sensivel a queda =
inverse_kinematic_left_leg(-PASSO_3DE4_v, 0.013, 2, 200); //abaixa o corpo//==============================Ponto sensivel a queda ==
espera_mov_legs();

inclina_plano(LEG_LEFT, 50, 45, 10);
inverse_kinematic_right_leg(0, 0.008, 0, 100);


// curva de aceleração e desaceleração levantar pé--------
inverse_kinematic_left_leg(-LARGURA_PASSO_v, ALTURA_PE_v, 0, 300); //levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(-LARGURA_PASSO_v, ALTURA_PE_v, 0, 500); //levanta pé esquerdo
usleep(50000);
inverse_kinematic_left_leg(-LARGURA_PASSO_v+.02, ALTURA_PE_v, 0, 400); //levanta pé esquerdo
//espera_mov();
usleep(65000);


//--------------------------------------------------------
}

inverse_kinematic_left_leg(PASSO_3DE4, ALTURA_PE, 0, 400); //extra
usleep(35000);
//espera_mov();
inverse_kinematic_left_leg(0, ALTURA_PE_v-0.01, 0, 300);
espera_mov();
inverse_kinematic_right_leg(0, 0.008, 0, 100);
inverse_kinematic_left_leg(0, 0.012, 0, 100);
espera_mov();
inclina_plano(LEG_RIGHT, 0, 65, 0);
inclina_plano(LEG_LEFT, 0, 65, 0);
espera_mov();
inverse_kinematic_right_leg(0, 0, 0, 300);
inverse_kinematic_left_leg(0, 0, 0, 300); /* teste*/

}

//===================================================================================
//-----------------------------------------------------------------------------------
void andar_lento()
{

#define ALTURA_PE 0.03
#define LARGURA_PASSO 0.042 // Largura do passo

espera_mov(); // Aguarda termino de alguma atividade

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
//espera_mov();
usleep(70000);
inclina_plano(LEG_LEFT, 96, 65, -20);

//-----------------------------------------------------
//espera_mov();
//---- abaixa pé --------------------------------------
inclina_plano(LEG_RIGHT, 55, 45, 5);
inverse_kinematic_right_leg(0, 0.008, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 400); //abaixa pé esquerdo
usleep(30000);
inverse_kinematic_left_leg(LARGURA_PASSO, 0.025, 2, 600); //abaixa pé esquerdo
usleep(50000);
inverse_kinematic_right_leg(0, 0.007, 1, 300); // movimenta corpo pra frente
inverse_kinematic_left_leg(LARGURA_PASSO, 0.02, 2, 200); //abaixa pé esquerdo
//espera_mov();
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
espera_mov_legs();

//------------------------------------------------------
//usleep(100000);

inclina_plano(LEG_RIGHT, -65, 55*1.5, 0); // inclina para esquerda // **editar aqui para mexer a inclinacao do andar**
inclina_plano(LEG_LEFT, -45, 38*1.5, 0);  // inclina para esquerda
inverse_kinematic_left_leg(PASSO_1DE4, 0.008, 3, 100*0.5);
inverse_kinematic_right_leg(-PASSO_3DE4, 0.0095, 2, 120*0.5);
espera_mov_legs();
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
//espera_mov_legs();
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
espera_mov_legs();

inverse_kinematic_right_leg(0, 0.008, 0, 300);
inverse_kinematic_left_leg(0, 0.008, 0, 300); /* teste*/

}
