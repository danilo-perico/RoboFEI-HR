#include "dynamixel.h"
#include <unistd.h>
#include <stdio.h>


void avoid_swing_left()
{
//-------------------------------------------------------------
// Compensação pelo torque pe esquerdo
int temp;
int posit = -55;
for(int x=0; x<15; x++)
{
	temp = dxl_read_word( 19, 40);
	printf("Torque 19 = %d |\n", temp);
	if(temp<400&&temp>230&&posit<-50)
	{
		inclina_plano(LEG_LEFT, posit++, 45, 0);
		printf("Compensou a direita lento\n");
		usleep(100000);
	}
	if(temp>1080&&temp<1254&&posit>-65)
	{
		inclina_plano(LEG_LEFT, posit--, 45, 0);
		printf("Compensou a esquerda lento\n");
		usleep(100000);
	}
	if(temp<1024&&temp>400&&posit<-48)
	{
		inclina_plano(LEG_LEFT, posit++, 55, 0);
		printf("Compensou a direita rapido\n");
		usleep(10000);
	}
	if(temp>1254&&posit>-65)
	{
		inclina_plano(LEG_LEFT, posit--, 55, 0);
		printf("Compensou a esquerda rapido\n");
		usleep(10000);
	}
	printf("Torque 19 = %d\n", dxl_read_word( 19, 40));
	usleep(10000);
}
//-------------------------------------------------------------
}

//=============================================================
void avoid_swing_right()
{
//-------------------------------------------------------------
// Compensação pelo torque do pé direito
int temp;
int posit = 68;
for(int x=0; x<10; x++)
{
	temp = dxl_read_word( 13, 40);
	printf("Torque 13 = %d |\n", temp);
	if(temp<200&&temp>80&&posit<72)
	{
		inclina_plano(LEG_RIGHT, posit++, 45, 0);
		printf("Compensou a direita lento\n");
		usleep(100000);
	}
	if(temp>1120&&temp<1224&&posit>64)
	{
		inclina_plano(LEG_RIGHT, posit--, 45, 0);
		printf("Compensou a esquerda lento\n");
		usleep(100000);
	}
	if(temp<1024&&temp>200&&posit<72)
	{
		inclina_plano(LEG_RIGHT, posit++, 55, 0);
		printf("Compensou a direita rapido\n");
		usleep(10000);
	}
	if(temp>1224&&posit<64)
	{
		inclina_plano(LEG_RIGHT, posit--, 55, 0);
		printf("Compensou a esquerda rapido\n");
		usleep(10000);
	}
	printf("Torque 13 = %d\n", dxl_read_word( 13, 40));
	usleep(10000);
}
}
//-------------------------------------------------------------

