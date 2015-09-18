/*--------------------------------------------------------------------

******************************************************************************
  * @file       decision.cpp
  * @author     Isaac Jesus da Silva - ROBOFEI-HT - FEI
  * @version    V0.0.3
  * @created    11/07/2014
  * @Modified   14/07/2014
  * @e-mail     isaac25silva@yahoo.com.br
  * @brief      Decision
  ****************************************************************************
/--------------------------------------------------------------------*/

#include <iostream>
#include <blackboard.h>
#include<unistd.h>

#define DEBUG

int main(void)
{
int pos_servo1 = 803;
int pos_servo2 = 512;

float dist_ball;

using_shared_memory();


std::cout<<"Decision"<<std::endl;

while(1)
{
//DECISION_ACTION_VISION=0;
//sleep(10);
DECISION_ACTION_VISION=1;
//sleep(10);

	dist_ball = VISION_DIST_BALL;
	//head_motor_angle = VISION_MOTOR_ANGLE;
	if (VISION_SEARCH_BALL == 1)
	{
		DECISION_ACTION_A = 0;
		if (VISION_LOST_BALL == 1)
			DECISION_ACTION_A = 3; //virar a direita
	}
	else
	{
	     if (VISION_LOST_BALL == 1)
		DECISION_ACTION_A = 3; //virar a direita
	     else
	     {
		if (VISION_MOTOR1_ANGLE > (pos_servo1 - 268)) //535 // Bola esta longe----------------
        	{
			//Bola longe do pé porem entre 430 a 610 (em uma posição quase enfrente ao robo)
            		if(VISION_MOTOR2_ANGLE >= (pos_servo2 - 82) && VISION_MOTOR2_ANGLE <= (pos_servo2 + 90)) // 430 a 610
			{
				if(VISION_MOTOR1_ANGLE < (pos_servo1 - 228))//575
               				DECISION_ACTION_A = 8;  //andar lento
				else
					DECISION_ACTION_A = 1;  //andar
			}

           		if(VISION_MOTOR2_ANGLE > (pos_servo2 + 90)) //610 // Bola a esquerda do robo------------
			{
				DECISION_ACTION_A = 2;  //virar a esquerda
			}
           		if(VISION_MOTOR2_ANGLE < (pos_servo2 - 82)) //430 // Bola a direita do robô-------------
			{
                		DECISION_ACTION_A = 3;  //virar a direita
			}
        	}
       		else  // Bola esta perto--------------------------------------------------------------
		{
           		if(dist_ball < 0.33) 
			{
				if(VISION_MOTOR2_ANGLE <= (pos_servo2 - 32) && VISION_MOTOR2_ANGLE >= (pos_servo2 - 113)) //480 a 400
              				DECISION_ACTION_A = 4; //chutar com pe direito
				if(VISION_MOTOR2_ANGLE < (pos_servo2 - 113)) //400
					DECISION_ACTION_A = 7; //andar de lado direita

				if(VISION_MOTOR2_ANGLE >= (pos_servo2 + 58) && VISION_MOTOR2_ANGLE <= (pos_servo2 + 140)) // 570 a 652
              				DECISION_ACTION_A = 5; //chutar com pe esquerdo
				if(VISION_MOTOR2_ANGLE > (pos_servo2 + 140)) //652
					DECISION_ACTION_A = 6; //andar de lado esquerda

				if(VISION_MOTOR2_ANGLE < (pos_servo2 + 58)  && VISION_MOTOR2_ANGLE >(pos_servo2 + 8)) //570 a 520
              				DECISION_ACTION_A = 5; //chutar com pe esquerdo
              				//DECISION_ACTION_A = 6; //andar de lado esquerda
				if(VISION_MOTOR2_ANGLE <= (pos_servo2 + 8)  && VISION_MOTOR2_ANGLE >(pos_servo2 - 32)) // 520 a 480
              				DECISION_ACTION_A = 4; //chutar com pe direito
              				//DECISION_ACTION_A = 7; //andar de lado direita

			}
			else
			{
				if(VISION_MOTOR2_ANGLE >= (pos_servo2 + 8))//520
					DECISION_ACTION_A = 2; //virar a esquerda;
				else
					DECISION_ACTION_A = 3;  //virar a direita
			}
		}
	     }
	}
	usleep(500000);
	std::cout<< "Action " << DECISION_ACTION_A;
	if(DECISION_ACTION_A == 0)
		std::cout<<" | Nada a fazer"<<std::endl;
	if(DECISION_ACTION_A == 1)
		std::cout<<" | Andar"<<std::endl;
	if(DECISION_ACTION_A == 2)
		std::cout<<" | Virar a esquerda"<<std::endl;
	if(DECISION_ACTION_A == 3)
		std::cout<<" | Virar a direita"<<std::endl;
	if(DECISION_ACTION_A == 4)
		std::cout<<"| Chutar com pe direito"<<std::endl;
	if(DECISION_ACTION_A == 5)
		std::cout<<" | Chutar com pe esquerdo"<<std::endl;
	if(DECISION_ACTION_A == 6)
		std::cout<<" | Andar de Lado esquerda"<<std::endl;
	if(DECISION_ACTION_A == 7)
		std::cout<<" | Andar de Lado direita"<<std::endl;
	if(DECISION_ACTION_A == 8)
		std::cout<<" | Andar Lento"<<std::endl;
	std::cout<< "Lost Ball " << VISION_LOST_BALL << std::endl;
	std::cout<< "Search ball " << VISION_SEARCH_BALL <<std::endl;

/*
a = COM_ACTION_ROBOT1;
b = COM_ACTION_ROBOT2;
c = COM_ACTION_ROBOT3;
d=COM_STATE_ROBOT1;
e=COM_STATE_ROBOT2;
f=COM_STATE_ROBOT3;
g=COM_POS_ROBOT1;
h=COM_POS_ROBOT2;
i=COM_POS_ROBOT3;
j=COM_POS_BALL_ROBOT1;
k=COM_POS_BALL_ROBOT2;
l=COM_POS_BALL_ROBOT3;
m=COM_POS_OPP_A_ROBOT1;
n=COM_POS_OPP_A_ROBOT2;
o=COM_POS_OPP_A_ROBOT3;
p=COM_POS_OPP_A_ROBOT4;
q=COM_POS_OPP_B_ROBOT1;
r=COM_POS_OPP_B_ROBOT2;
s=COM_POS_OPP_B_ROBOT3;
t=COM_POS_OPP_B_ROBOT4;
u=COM_POS_OPP_C_ROBOT1;
v=COM_POS_OPP_C_ROBOT2;
x=COM_POS_OPP_C_ROBOT3;
z=COM_POS_OPP_C_ROBOT4;
aa = COM_REFEREE;
ab = LOCALIZATION_THETA;
ac = LOCALIZATION_X;
ad = LOCALIZATION_Y;
ae = VISION_DIST_BALL;
af = VISION_DIST_GOAL;
ag = VISION_DIST_OPP1;
ah = VISION_DIST_OPP2;
ai = VISION_DIST_OPP3;
aj = CONTROL_ACTION;

usleep(50);
//SENT VARIABLES
DECISION_ACTION_A = 15; //PLANNING
DECISION_ACTION_B = 16+inc; //PLANNING
DECISION_STATE = 1+inc; //COMMUNICATION
DECISION_POSITION_A = 10+inc; //COMMUNICATION
DECISION_POSITION_B = 11+inc; //COMMUNICATION
DECISION_POSITION_C = 12+inc; //COMMUNICATION
DECISION_BALL_POS = 20+inc; //COMMUNICATION
DECISION_OPP1_POS = 30+inc; //COMMUNICATION
DECISION_OPP2_POS = 31+inc; //COMMUNICATION
DECISION_OPP3_POS = 32+inc; //COMMUNICATION
}

inc++;

#ifdef DEBUG
cout << "decision received " << a <<" "<< b <<" "<< c <<" "<< d <<" "<< e <<" "<< f <<" "<< g <<" "<< h <<" "<< i <<" "<< j <<" "<< k <<" "<< l <<" "<< m <<" "<< n <<" "<< o <<" "<< p <<" "<< q <<" "<< r <<" "<< s <<" "<< t <<" "<< u <<" "<< v <<" "<< x <<" "<< z << " " << ab << " " << ac <<" " << ad << " "<< ae << " " << af <<" "<< ag << " " << ah << " " << ai << endl;
#endif
*/
}
}
