#include <stdio.h>
#include <dynamixel.h>
#include <unistd.h>
#include "blackboard.h"

int espera_mov()
{

    if(IMU_STATE==1)
    {
	call_standup();
	return 1;
    }

    for(unsigned short int i=3;i<21;i++)
    {
        while(dxl_read_byte( i, P_MOVING ) != 0)
            usleep(2000); //Espera 2 milisegundos evitando uso excessivo do processador
	//printf("Torque 19 = %d\n", dxl_read_word( 19, 40));
    }
    return 0;
}

void espera_mov_ID(int id)
{
    while(dxl_read_byte( id, P_MOVING ) != 0)
        usleep(2000); //Espera 2 milisegundos evitando uso excessivo do processador
}


int espera_mov_legs()
{
    if(IMU_STATE==1)
    {
	call_standup();
	return 1;
    }
    for(unsigned short int i=9;i<21;i++) // Apenas para as pernas do Darwin 9 até 20
    {
        while(dxl_read_byte( i, P_MOVING ) != 0)
            usleep(2000); //Espera 2 milisegundos evitando uso excessivo do processador
    }

    //int key = kbhit();

    //if (key != 0)
        //keyboard(key);
    return 0;
}

void espera_mov_levantar()
{
    for(unsigned short int i=3;i<21;i++)
    {
        while(dxl_read_byte( i, P_MOVING ) != 0)
            usleep(2000); //Espera 2 milisegundos evitando uso excessivo do processador
    }
}

int call_standup()
{
	printf("\nCaiu\n");
	usleep(300000);
	if(IMU_ACCEL_X > 0)
		levantar_de_frente();
	else
		levantar_de_costas();
	usleep(300000);
	printf("\nLevantou\n");	
}
