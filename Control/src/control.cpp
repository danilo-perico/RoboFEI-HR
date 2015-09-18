/*--------------------------------------------------------------------

******************************************************************************
* @file control.cpp
* @author Isaac Jesus da Silva - ROBOFEI-HT - FEI
* @version V0.0.7
* @created 20/01/2014
* @Modified 16/07/2014
* @e-mail isaac25silva@yahoo.com.br
* @brief control
****************************************************************************
****************************************************************************

Arquivo fonte contendo o programa que controla os servos do corpo do robô

/--------------------------------------------------------------------*/
#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <dynamixel.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include "blackboard.h"

#include <time.h>
#include <assert.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <iostream>
#include <math.h>

//void PrintCommStatus(int CommStatus);
//void PrintErrorCode(void);

//////global variables////////////////////////////////////////////////
int inclina = 55;
unsigned int StandupPos[22] = {803, 512, //01 , 02, (cabeça)
                382, 417+20, 353+20, //03, 04, 05, (braço direito)
                472+170, 600-20, 689-20, //06, 07, 08, (braço esquerdo) 472
                512, 512+20+5, 512-5, 591-10-5, 512, 801+5+8+20-23+5, //09, 10, 11, 12, 13, 14 (perna direita)
               512, 512-25-5, 512+20, 492-5, 512, 224-5-8+23+10}; //15, 16, 17, 18, 19, 20 (perna esquerda)

/*
unsigned int StandupPos[22] = {803, 512, //01 , 02, (cabeça)
                382, 417, 353+20, //03, 04, 05, (braço direito)
                472+170, 600, 689-20, //06, 07, 08, (braço esquerdo) 472
                512, 512+20, 512-5, 591-10, 512, 801+5, //09, 10, 11, 12, 13, 14 (perna direita)
               512, 512-25, 512+20, 492, 512, 224-5}; //15, 16, 17, 18, 19, 20 (perna esquerda)

/*
unsigned int StandupPos[22] = {803, 512, //01 , 02, (cabeça)
                545, 417, 335, //03, 04, 05, (braço direito)
                472, 600, 682, //06, 07, 08, (braço esquerdo)
                512, 512, 512, 591, 512, 791+5+5, //09, 10, 11, 12, 13, 14 (perna direita)
               512, 512, 535-10, 492, 512, 203+5+11+5}; //15, 16, 17, 18, 19, 20 (perna esquerda)
*/

void monitora_tensao();

void obedecer_decisao();

int main(int argc, char* argv[])
{
    printf( "Darwin Robot running...\n\n" );

    int * baudnum = new int; //alocado dinâmicamente
    *baudnum = DEFAULT_BAUDNUM;  //velocidade de transmissao da serial em 1Mbps
    int * deviceIndex = new int; //alocado dinâmicamente
    *deviceIndex = 0; 		//endereça USB
    //unsigned int tensaomedia = 0;

    using_shared_memory();

    char string[50]; //String usada para definir prioridade do programa

    system("echo 123456| sudo -S chmod 777 /dev/ttyUSB*");//libera acesso a USB

    sprintf(string,"echo fei 123456| sudo -S renice -20 -p %d", getpid()); // prioridade maxima do codigo
    system(string);//prioridade

   

// ---- Open USBDynamixel -----------------------------------------------{
bool servoComunica = false;
bool servoConectado = false;
	while(*deviceIndex<3)// laço que percorre o servo 0, 1 e 2.
	{
		if( dxl_initialize(*deviceIndex, *baudnum) == 0 )
		{
			printf( "Failed to open servo%d!\n", *deviceIndex );
			if(*deviceIndex==2)  // Não encontrou nenhum
			{
				if(servoComunica)
				    printf("Conectou-se a uma placa mas não conseguiu se comunicar com o servo\n");
				else
				    printf("Não encontrou nenhuma placa do servo conectada a porta USB\n");
			        return 0;
			}
			*deviceIndex = *deviceIndex + 1;      // Não conecta na placa do servo e tenta a proxima porta.
		}
		else
		{
			servoComunica = true;
			printf( "Succeed to open Servo%d!\n", *deviceIndex );
			servoConectado = dxl_read_byte( 20, 3 ) == 20;
			usleep(1000);
			servoConectado = dxl_read_byte( 20, 3 ) == 20;//Tenta novamente caso falhe a comunicação
			usleep(1000);
			servoConectado = dxl_read_byte( 20, 3 ) == 20;//Tenta novamente caso falhe a comunicação
    			if(servoConectado)
			{
       			 	printf("Servo%d okay - Connected and communicated!\n", *deviceIndex);
			 	break;
			}
    			else
    			{
				printf("Servo wrong or not communicated!\n");
				if(*deviceIndex==2)
				{
				    printf("Conectou-se a uma placa mas não conseguiu se comunicar com o servo\n");
				    return 0;
				}
				*deviceIndex = *deviceIndex + 1;
			}
		}
	}
	delete deviceIndex; delete baudnum; //desalocando da memória
//-----------------------------------------------------------------------------}



for(int x=3; x<=8; x++)
    dxl_write_word( x, 34, 200); // Inicia os braços com baixo torque

	dxl_write_byte(5, 25, 0); //Apaga Led
	dxl_write_byte(8, 25, 0); //Apaga Led
	dxl_write_byte(9, 25, 0); //Apaga Led
	dxl_write_byte(15, 25, 0); //Apaga Led
	dxl_write_byte(12, 24, 1);  //Turn on Torque
        dxl_write_byte(18, 24, 1); //Turn on Torque	

robo_ereto();

	printf( "Press Enter key to continue!(press ESC and Enter to quit)\n" );
		if(getchar() == 0x1b)
			return 0;

	while(1)
	{
	//greetings();

	//sleep(1);

	//sistema responsável por evitar que a bateria descarrega abaixo do limite minimo de tensão.
	monitora_tensao(); 

	//andar_veloz2(1);
	//virar_direita(60);
	//virar_esquerda(80);

	printf( "Press Enter key to continue!(press ESC and Enter to quit)\n" );
		if(getchar() == 0x1b)
			break;

	robo_ereto();

	printf( "Press Enter key to continue!(press ESC and Enter to quit)\n" );
		if(getchar() == 0x1b)
			break;

	//obedecer_decisao();

//andar_veloz(2);
//andar_lento();
//for(int p=0; p<5;p++)
//levantar_de_frente();
//virar_esquerda(30); //diferença servo2 = 42
//virar_esquerda(40); //diferença servo2 = 57
//virar_esquerda(60); //diferença servo2 = 65
//virar_esquerda(80); //diferença servo2 = 87
//virar_esquerda(100);
//virar_direita(30);
//virar_direita(40);
//virar_direita(60);
//virar_direita(80);
//levantar_de_costas();
//desligar_servos();
//robo_ereto();
//espera_mov();
//andar_lateral_direita();
//andar_lateral_direita();
//sleep(2);
//andar_lateral_esquerda();
//andar_lateral_esquerda();
//chute_direito();
//andar_rapido(2);
//chute_esquerdo();
//andar_marchando();
//sleep(4);


//andar_veloz(2);
//sleep(2);

/*
//printf("Tensão = %d\n",dxl_read_byte( 20, 42));
for(int x=1; x<23;++x)
printf("Torque %d = %d\n", x, dxl_read_word( x, 40));
printf("-------------------------------------------------\n");
usleep(500000);
*/


//inverse_kinematic_right_leg(0.001, 0.07, 0, 200);
//inverse_kinematic_left_leg(0.001, 0.07, 0, 200);


//sleep(2);
//inverse_kinematic_right_leg(0, 0,0,200);
//inverse_kinematic_left_leg(0, 0,0,200);
//sleep(2);
/*
// Teste Robot ----------------------------------------
sleep(2);
inclina_plano(LEG_RIGHT, 48, 40, 0);
inclina_plano(LEG_LEFT, 48, 40, 0);
inverse_kinematic_left_leg(0, 0.002, 0, 50);
espera_mov();
inclina_plano(LEG_LEFT, 61, 40, 0);
inverse_kinematic_left_leg(0, 0.04, 0, 300);
espera_mov();
inverse_kinematic_left_leg(0.12, 0.1, 0, 40);
espera_mov();
inverse_kinematic_left_leg(0, 0.04, 0, 40);
espera_mov();
sleep(1);
inverse_kinematic_left_leg(0, 0, 0, 200);
inclina_plano(LEG_RIGHT, 0, 40, 0);
inclina_plano(LEG_LEFT, 0, 40, 0);
espera_mov();
sleep(1);
inclina_plano(LEG_RIGHT, -43, 40, 0);
inclina_plano(LEG_LEFT, -43, 40, 0);
inverse_kinematic_right_leg(0, 0.003, 0, 50);
espera_mov();
inverse_kinematic_right_leg(0, 0.04, 0, 300);
inclina_plano(LEG_RIGHT, -55, 30, 0);
espera_mov();
inverse_kinematic_right_leg(0.1, 0.11, 0, 40);
espera_mov();
inverse_kinematic_right_leg(0, 0.04, 0, 40);
espera_mov();
sleep(1);
inverse_kinematic_right_leg(0, 0, 0, 200);
inclina_plano(LEG_RIGHT, 0, 40, 0);
inclina_plano(LEG_LEFT, 0, 40, 0);
//-----------------------------------------------------
*/
/*

//Teste de inverse kinematic -------------------------
robo_ereto();
sleep(2);
inverse_kinematic_right_leg(0.001, 0.07, 0, 200);
inverse_kinematic_left_leg(0.001, 0.07, 0, 200);
sleep(2);
inverse_kinematic_right_leg(0.09, 0.07, 0, 200);
inverse_kinematic_left_leg(0.09, 0.07, 0, 200);
sleep(2);
inverse_kinematic_right_leg(-0.04, 0.07, 0, 200);
inverse_kinematic_left_leg(-0.04, 0.07, 0, 200);
sleep(2);
inverse_kinematic_right_leg(0.06, 0.11, 0, 200);
inverse_kinematic_left_leg(0.06, 0.11, 0, 200);
sleep(2);
inverse_kinematic_right_leg(0.001, 0.07, 0, 200);
inverse_kinematic_left_leg(0.001, 0.07, 0, 200);
sleep(2);
inverse_kinematic_right_leg(0, 0, 0, 200);
inverse_kinematic_left_leg(0, 0, 0, 200);
//-----------------------------------------------------
*/
/*
//Teste de agachamento----------------
sleep(2);
inverse_kinematic_right_leg(0, 0.05, 0, 250);
inverse_kinematic_left_leg(0, 0.05, 0, 250);
sleep(2);
inverse_kinematic_right_leg(0, 0, 0, 250);
inverse_kinematic_left_leg(0, 0, 0, 250);
*/
//andar_rapido(3);
//andar_lateral_direita(1);
//andar_lateral_esquerda(1);
//virar(5);
//andar(2);
//andar_curto(3);

/*
retorno_visao = visao();// Entra no programa da visão e recebe retorno se achou a bola
//robo_ereto();
//sleep(2);




if (retorno_visao == 1) // Se retornou 1, então o robo encontrou a bola e está com a câmera centralizada nela
{
printf("distancia: %2.2f |", distancia_bola());
printf("  virou %d",StandupPos[1]-dxl_read_word( 2, P_PRESENT_POSITION_L));
printf("  Servo1: %d - Servo2: %d\n",dxl_read_word( 1, P_PRESENT_POSITION_L), dxl_read_word( 2, P_PRESENT_POSITION_L));

   float dist_bola = -distancia_bola(); // Calcula a distância que o robo está da bola
        if (dist_bola > 0.05 && ((StandupPos[1]-dxl_read_word( 2, P_PRESENT_POSITION_L))/100) < 1)
        {
            //virar((594-dxl_read_word( 2, P_PRESENT_POSITION_L))/100);//100

            if(dist_bola > 0.20)
                andar_rapido(dist_bola/0.095);//0.95

            if(dist_bola <= 0.20)
                andar_rapido(dist_bola/0.04);
            //robo_ereto_corrigido();

        }
        else
           if(dist_bola > 0.05)
           {
               //virar((594-dxl_read_word( 2, P_PRESENT_POSITION_L))/100);
           }


        //posição exata de chute servo 1: 537 / servo 2: 627
        if ((dxl_read_word( 1, P_PRESENT_POSITION_L) >= StandupPos[0]-343 && dxl_read_word( 1, P_PRESENT_POSITION_L) <= StandupPos[0]-295)
             && (dxl_read_word( 2, P_PRESENT_POSITION_L) >= StandupPos[1]-96 && (dxl_read_word( 2, P_PRESENT_POSITION_L) <= StandupPos[1]-14)))
        {
            chute_direito();
        }

        if ((dxl_read_word( 1, P_PRESENT_POSITION_L) >= StandupPos[0]-343 && dxl_read_word( 1, P_PRESENT_POSITION_L) <= StandupPos[0]-295)
             && (dxl_read_word( 2, P_PRESENT_POSITION_L) < StandupPos[1]-96)) // verifica se necessita andar lateral
        {
            andar_lateral_direita();
        }

        if ((dxl_read_word( 1, P_PRESENT_POSITION_L) >= StandupPos[0]-343 && dxl_read_word( 1, P_PRESENT_POSITION_L) <= StandupPos[0]-295)
             && (dxl_read_word( 2, P_PRESENT_POSITION_L) > StandupPos[1]-14)) // verifica se necessita andar lateral
        {
            andar_lateral_esquerda();
        }

        if ((dxl_read_word( 2, P_PRESENT_POSITION_L) >= StandupPos[1]-96 && (dxl_read_word( 2, P_PRESENT_POSITION_L) <= StandupPos[1]-14))
            && dist_bola<=0.05 && (dxl_read_word( 1, P_PRESENT_POSITION_L) < StandupPos[0]-295))
        {
            andar_rapido(1);
        }


}

if (retorno_visao == 2)
{
    printf("Não achou bola\n");
    dxl_write_word(2, P_GOAL_POSITION_L, StandupPos[1]);
    dxl_write_word(1, P_GOAL_POSITION_L, StandupPos[0]);
    //for (int i = 0; i<3 ; i++)
    //virar(3);
}

/**/
    }
	// Close device
	dxl_terminate();
	printf( "Press Enter key to terminate...\n" );
	getchar();
	return 0;
}


/* Compensação pelo torque
int temp;
int posit = 64;
for(int x=0; x<1000; x++)
{
	temp = dxl_read_word( 13, 40);
	printf("Torque 13 = %d\n", temp);
	if(temp<200&&temp>96)
	{
		inclina_plano(LEG_RIGHT, posit++, 45, 0);
		printf("Foi 68\n");
		usleep(100000);
	}
	if(temp>1180&&temp<1200)
	{
		inclina_plano(LEG_RIGHT, posit--, 45, 0);
		printf("Foi 68\n");
		usleep(100000);
	}
	if(temp<1024&&temp>200)
	{
		inclina_plano(LEG_RIGHT, posit++, 45, 0);
		printf("Foi 68\n");
		usleep(20000);
	}
	if(temp>1200)
	{
		inclina_plano(LEG_RIGHT, posit--, 45, 0);
		printf("Foi 68\n");
		usleep(20000);
	}
	printf("Torque 13 = %d\n", dxl_read_word( 13, 40));
	usleep(10000);
}
*/
//=================================================================================================================
void monitora_tensao()
{
	unsigned int tensaomedia = 0;
	for(int x=3,tensao=0; x<21; x++)
	{
	    //printf("Tensao %d = %d\n", x, dxl_read_byte( x, 42));
	    if((tensao = dxl_read_byte( x, 42)) == 0)
		tensao = 185;
	    tensaomedia = tensaomedia + tensao;
	}
	printf("Tensao media = %d\n", tensaomedia = tensaomedia/18);
	
	if(tensaomedia < 165)
	{	
	    inverse_kinematic_right_leg(0, 0.1, 0, 200);
	    inverse_kinematic_left_leg(0, 0.1, 0, 200);
	    dxl_write_byte(5, 25, 1);  //Turn on Led
	    dxl_write_byte(8, 25, 1);  //Turn on Led
	    dxl_write_byte(9, 25, 1);  //Turn on Led
	    dxl_write_byte(15, 25, 1); //Turn on Led
	    espera_mov_legs();
	    dxl_write_byte(12, 24, 0);  //Turn off Torque
	    dxl_write_byte(18, 24, 0); //Turn off Torque	    
	    while(1)
		sleep(1);	    
	}

}
//=================================================================================================================

void obedecer_decisao()
{
//-------------Decision---------------------------------------------------
	//usleep(500000);
	std::cout<< "Action " << DECISION_ACTION_A;
	if(DECISION_ACTION_A == 0)
	{
		std::cout<<" | Nada a fazer"<<std::endl;
		robo_ereto();
	}
	if(DECISION_ACTION_A == 1)
	{
		std::cout<<" | Andar"<<std::endl;
		andar_veloz(1);
		usleep(500000);
	}
	if(DECISION_ACTION_A == 2)
	{
		std::cout<<" | Virar a esquerda"<<std::endl;
		virar_esquerda(80);
		usleep(500000);
	}
	if(DECISION_ACTION_A == 3)
	{
		std::cout<<" | Virar a direita"<<std::endl;
		virar_direita(60);
		usleep(500000);
	}
	if(DECISION_ACTION_A == 4)
	{
		std::cout<<"| Chutar com pe direito"<<std::endl;
		chute_direito();
		usleep(500000);
	}
	if(DECISION_ACTION_A == 5)
	{
		std::cout<<" | Chutar com pe esquerdo"<<std::endl;
		chute_esquerdo();
		usleep(500000);
	}
	if(DECISION_ACTION_A == 6)
	{
		std::cout<<" | Andar de Lado esquerda"<<std::endl;
		andar_lateral_esquerda();
		usleep(500000);
	}
	if(DECISION_ACTION_A == 7)
	{
		std::cout<<" | Andar de Lado direita"<<std::endl;
		andar_lateral_direita();
		usleep(500000);
	}
	if(DECISION_ACTION_A == 8)
	{
		std::cout<<" | Andar lento"<<std::endl;
		andar_lento();
		usleep(500000);
	}
//------------------------------------------------------------------------
}
//=================================================================================================================


