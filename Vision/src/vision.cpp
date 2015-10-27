/*--------------------------------------------------------------------

******************************************************************************
  * @file       vision.cpp
  * @author     Claudio Vilao - ROBOFEI-HT - FEI
  * @version    V1.0.1
  * @created    24/04/2014
  * @Modified   27/10/2015
  * @Modified by Isaac Jesus da Silva
  * @e-mail
  * @brief      Vision of racing
  ****************************************************************************
/--------------------------------------------------------------------*/

#include <iostream>
#include "blackboard.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cvaux.h>
#include <highgui.h>
#include <cxcore.h>
#include <math.h>
#include <dynamixel.h>
#include <unistd.h>
#include <boost/program_options.hpp> //tratamento de argumentos linha de comando

#include <signal.h>

#include "minIni.h"


#define HEAD_TILT 20
#define HEAD_PAN 19

#define INI_FILE_PATH       "Control/Data/config.ini"

#define P_GOAL_POSITION_L	30
#define P_GOAL_POSITION_H	31
#define P_PRESENT_POSITION_L	36
#define P_PRESENT_POSITION_H	37
#define P_MOVING		46
#define DEFAULT_BAUDNUM		1 // 1Mbps

//#define DEBUG
#define XC .038 //distancia da camera em relação ao servo
#define YC .05 //Altura da camera em relação ao servo

using namespace cv;
using namespace std;

// Tamanho Padrão de captura WebCam Robo- 640x480
//#define RESOLUCAO_X 1280 //1280   1920
//#define RESOLUCAO_Y 720  //720   1080

#define RESOLUCAO_X 320 //1280   1920 640
#define RESOLUCAO_Y 240  //720   1080 480

#define CENTERBALL 0.03 // Porcentagem de quanto centraliza a bola no quadro
#define AJUSTE 0.285 // para resolução de 640x480
//#define AJUSTE 0.285*0.49 // para resolução de 1280x720
#define AJUSTEDIST 1 // para resolução de 640x480
//#define AJUSTEDIST 0.5 //para resolução de 1280x720

int HeadFollow(float posx, float posy, bool *head_move1, bool *head_move2);
void GoalSearch(bool inicio);

//803, 512,
int pos_servo1 = 803; //803
int pos_servo2 = 512;
int cont_BallSearch;

CvCapture* captura;
CvMemStorage* memoria;

void siginthandler(int param)
{
  printf("User pressed Ctrl+C\n");
  exit(1);
} 

int main(int argc, char **argv)
{ 
//cout << "teste" << endl;
signal(SIGINT, siginthandler);
    CvSeq* lines = 0;
    int cont = 0;
    bool head_move2 = false;
    bool head_move1 = false;
    int i;
    int baudnum = DEFAULT_BAUDNUM; //velocidade de transmissao
    int index = 0;
    int deviceIndex = 0; //endereça a USB
    int Moving, PresentPos;
    unsigned int lost_ball = 0; // Conta quantos frames a bola está perdida
    int saida = 0;
    int CommStatus;

    using_shared_memory();

	minIni* ini;
	ini = new minIni(INI_FILE_PATH);

	if((pos_servo2=ini->getd("Offset","ID_19",-1024))==-1024){
		cout<<"Erro na leitura do conf.ini";
		return(0);
	}

	if((pos_servo1=ini->getd("Offset","ID_20",-1024))==-1024){
		cout<<"Erro na leitura do conf.ini";
		return(0);
	}


	//*********************************************************
	//-------------para entrada de argumentos-----------------------------------
 	namespace po=boost::program_options;
  	po::options_description desc("options");
  	desc.add_options()
    ("help", "produce help message")
    ("vg", "apresenta o video do gol na tela")
    ("dev0", "Abre Camera 0")
    ("dev1", "Abre Camera 1")
	;
  
	po::variables_map variables;
	po::store(po::parse_command_line(argc, argv, desc), variables);
	po::notify(variables); 
	//------------------------------

	if (variables.count("help")) 
	{
		cout << desc << "\n";
		return 1;
	}

	if (variables.count("vg"))	cout<<"Chamou o video do gol\n";

	//--------------------------------------------------------------------------
	//**************************************************************************
	// ---- Open USBDynamixel -----------------------------------------------{
	bool servoComunica = false;

	while(deviceIndex<3)// laço que percorre o servo 0, 1 e 2.
	{
		if( dxl_initialize(deviceIndex, baudnum) == 0 )
		{
			printf( "Failed to open servo%d!\n", deviceIndex );
			if(deviceIndex==2)  // Não encontrou nenhum
			{
				if(servoComunica)
				    printf("Conectou-se a uma placa mas não conseguiu se comunicar com o servo\n");
				else
				    printf("Não encontrou nenhuma placa do servo conectada a porta USB\n");
			    return 0;
			}
			deviceIndex++;      // Não conecta na placa do servo e tenta a proxima porta.
		}
		else
		{
			servoComunica = true;
			printf( "Succeed to open Servo%d!\n", deviceIndex );
    		if(dxl_read_byte( 19, 3 ) == 19)
			{
       			printf("Servo%d okay - Connected and communicated!\n", deviceIndex);
			 	break;
			}
    		else
    		{
				printf("Servo wrong or not communicated!\n");
				if(deviceIndex==2)
				{
					printf("Conectou-se a uma placa mas não conseguiu se comunicar com o servo\n");
					return 0;
				}
				deviceIndex++;
			}
		}
	}
	//-----------------------------------------------------------------------------}

    CvFont font;
    double hScale=1.0;
    double vScale=1.0;
    int    lineWidth=1;
    int posX = 1;
    int posY = 1;
    bool inicio=1;

    cont_BallSearch = 0;

    dxl_write_word(HEAD_TILT, 34, 512); // Usando apenas 50% do torque
	dxl_write_word(2, 34, 512); // Usando apenas 50% do torque

	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);

    	// Abre o dispositivo de captura "0" que é /dev/video0
	int dev=0;
	if (variables.count("dev0")) dev = 0;
	if (variables.count("dev1")) dev = 1; else dev = 0;

 	captura = cvCaptureFromCAM( dev );
 	//captura = cvCaptureFromCAM( 0 );

	if( !captura )
	{
	    fprintf( stderr, "ERRO Não há captura na Camera %i/n",dev  );
	    //fprintf( stderr, "ERRO Não há captura na Camera %i/n",0  );
	    getchar();
	    return -1;
    }

	cvSetCaptureProperty( captura, CV_CAP_PROP_FRAME_WIDTH, RESOLUCAO_X);
	cvSetCaptureProperty( captura, CV_CAP_PROP_FRAME_HEIGHT, RESOLUCAO_Y );

	CvSize tamanho = cvSize(cvGetCaptureProperty(captura, CV_CAP_PROP_FRAME_WIDTH),cvGetCaptureProperty(captura, CV_CAP_PROP_FRAME_HEIGHT));

	// Cria uma janela onde as imagens capturadas serão apresentadas
	if (variables.count("vg")) cvNamedWindow( "Imagem", CV_WINDOW_AUTOSIZE );

    usleep(1000000);

	//*****************************************************************************

	IplImage*  Quadro_hsv  = cvCreateImage(tamanho, IPL_DEPTH_8U, 3);
	IplImage*  segmentada  = cvCreateImage(tamanho, IPL_DEPTH_8U, 1);

	//Posiciona a cabeca na posicao correta de achar a linha
	dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, pos_servo2);
	dxl_write_word(HEAD_TILT, P_GOAL_POSITION_L, pos_servo1+190);

	DECISION_ACTION_VISION=1;
    while( 1 )
 	{

		//******************************************************************************************************
		if(DECISION_ACTION_VISION==1) // Vendo o Gol------------------------------------
		{       	
			//Minimo e maximo para segmentar a cor preta em HSV 
		   	CvScalar minG = cvScalar(92, 0 , 30 , 0);//24 160 //160
		    CvScalar maxG = cvScalar(255, 141, 128, 10);//47 //250

		    IplImage* GoalFrame = cvQueryFrame( captura );

		    if( !GoalFrame )
		    {
		        fprintf( stderr, "ERRO Quadro Gol Vazio...\n" );
		        getchar();
		        break;
		    }
		    
			//*****************************************************************
		    IplImage* Gray  = cvCreateImage(tamanho, IPL_DEPTH_8U, 1);
		    cvCvtColor(GoalFrame, Gray, CV_BGR2GRAY);
		    double brightness = cvMean(Gray);

		    if (brightness < 20)
		    {
			    cout << "Esta escuro!! "<<endl;
		    }
		    else
		    {
		        cout << "Esta Claro!! "<<endl;
		    }
			//*****************************************************************
		    CvSize tamanhoG = cvSize(cvGetCaptureProperty(captura, CV_CAP_PROP_FRAME_WIDTH),cvGetCaptureProperty(captura, CV_CAP_PROP_FRAME_HEIGHT));

		    //IplImage* CannyG        = cvCreateImage(tamanhoG, IPL_DEPTH_8U, 1 );
		    IplImage* QuadroHsvG    = cvCreateImage(tamanhoG, IPL_DEPTH_8U, 3);
		    IplImage* segmentadaG   = cvCreateImage(tamanhoG, IPL_DEPTH_8U, 1);

		    cvCvtColor(GoalFrame, QuadroHsvG, CV_BGR2HSV);
		    cvInRangeS(QuadroHsvG, minG, maxG, segmentadaG);
		    //cvCanny( segmentadaG, CannyG, 50, 125, 3 );
		     // Memoria para as linhas de Hough
		    //CvMemStorage* memoriaG = cvCreateMemStorage(0);


		    Mat img (segmentadaG);
		    cv::Point Coord;
		    cv::Moments mm = cv::moments(img,false);
		    double moment10 = mm.m10;
		    double moment01 = mm.m01;
		    double moment00 = mm.m00;
		    Coord.x = int(moment10 / moment00);
		    Coord.y = int(moment01 / moment00);

			if (Coord.x<0)
				Coord.x = 0;
			if (Coord.y<0)
				Coord.y = 0;
	
		    if ((Coord.x != 0) && (Coord.y != 0))
		    {
		        VISION_DIST_GOAL = 1;
		    }
		    else
		    {
		        VISION_DIST_GOAL = 0;
		    }

			cvCircle(GoalFrame , Coord, 10, CV_RGB(0,255,0), -1, 8, 0 );

		    if(VISION_DIST_GOAL == 0) //
		    {

		        GoalSearch(inicio);//Procura pelo campo
		        saida = 0;
		        inicio = 0;
		    }
		    else
		    {
		        //VISION_DIST_GOAL = 1;
		        if (inicio==0)// Faz o robô parar a cabeça no instante que achou a bola que estava perdida
		        {            // Sem esse comando o código não funciona porque ele não para a cabeça
		            dxl_write_word(HEAD_TILT, P_GOAL_POSITION_L, dxl_read_word( HEAD_TILT, P_PRESENT_POSITION_L));
		            dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, dxl_read_word( HEAD_PAN, P_PRESENT_POSITION_L));
		        }

		        inicio =1;

		        if (HeadFollow(Coord.x, Coord.y, &head_move1, &head_move2) == 1)
			    {// Move a cabeça para seguir a bola
		           saida++;
		        }

			    VISION_MOTOR2_ANGLE = dxl_read_word( HEAD_PAN, P_PRESENT_POSITION_L);
			    std::cout <<"Servo2 Gol = "<< VISION_MOTOR2_ANGLE << std::endl;

			    VISION_MOTOR1_ANGLE = dxl_read_word( HEAD_TILT, P_PRESENT_POSITION_L);
			    std::cout <<"Servo1 Gol = "<<VISION_MOTOR1_ANGLE << std::endl;
		    }

		    if( (cvWaitKey(10) & 255) == 27)
		    {
		    	//cvReleaseMemStorage(&memoriaG);
		        //cvReleaseImage(&CannyG);
		        cvReleaseImage(&QuadroHsvG);
		        cvReleaseImage(&segmentadaG);
				break;
			}
			//cvShowImage( "Linhas Detectadas", CannyG);
			//cvShowImage( "Saida Cinza", segmentada);
			//pthread_mutex_lock( &mutex3 );

		    if (variables.count("vg"))
			{
				cvShowImage( "Imagem", GoalFrame );
				//cvShowImage( "Linhas Detectadas", CannyG);
			//cvShowImage( "Saida Cinza", segmentada);
			}

		//-----------------------------------------------------------------------------------
		}// endif DECISION_ACTION_VISION==1
		//******************************************************************************************************
	} //while(1)

return 0;
}


//=======================================================================================================================
//------------- Função que faz a cabeça centralizar a bola no vídeo------------------------------------------------------
int HeadFollow(float posx, float posy, bool *head_move1, bool *head_move2)
{
    int pan = 0;
    int tilt = 0;
	int LookDown = 180;
	int LeftLimit = pos_servo2 - 50;
	int RightLimit = pos_servo2 + 50;

    dxl_write_word(HEAD_TILT, MOVING_SPEED, 300);//300
    dxl_write_word(HEAD_PAN, MOVING_SPEED, 500);//300

    bool nolimitleft = dxl_read_word( HEAD_PAN, P_PRESENT_POSITION_L) > LeftLimit;
    bool nolimitright = dxl_read_word( HEAD_PAN, P_PRESENT_POSITION_L) < RightLimit;
    bool nolimit_total = nolimitleft && nolimitright;


	//------ Realiza o movimento do Pan -----------------------------------------------------------
    //------ Segue a bola para a esquerda do video -----------------------------------------
    if(posx<(RESOLUCAO_X/2)*(1-CENTERBALL) && *head_move2==false && nolimitright)
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, dxl_read_word( HEAD_PAN, P_PRESENT_POSITION_L)+( ((RESOLUCAO_X/2)-posx) * AJUSTE));

    //------ Segue a bola para a direita do video -----------------------------------------
    if(posx>(RESOLUCAO_X/2)*(CENTERBALL+1) && *head_move2==false && nolimitleft)
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, dxl_read_word( HEAD_PAN, P_PRESENT_POSITION_L)-( (posx-(RESOLUCAO_X/2)) * AJUSTE));

    // Para a cabeça se chegou na posição desejada ----------------------------------------
    if(posx>=(RESOLUCAO_X/2)*(1-CENTERBALL) && posx<=(RESOLUCAO_X/2)*(CENTERBALL+1) && nolimit_total)
	{
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, dxl_read_word( HEAD_PAN, P_PRESENT_POSITION_L));
        pan = 1;
    }

    if(dxl_read_byte( HEAD_PAN, P_MOVING ))
        *head_move2 = true;  // verifica se a cabeça está em movimento
    else
        *head_move2 = false; // verifica se a cabeça está em movimento
	//---------------------------------------------------------------------------------------------

	if (pan == 1)
		return 1;
	else
		return 0;
}
//=======================================================================================================================


void GoalSearch(bool inicio)
{
    // Posição inicial da cabeça {304, 594} //01 , 02, cabeça
	static unsigned int varredura=0;

    dxl_write_word(HEAD_PAN, MOVING_SPEED, 150);//Seta as velocidades da cabeça
    dxl_write_word(HEAD_TILT, MOVING_SPEED, 400);

    if(inicio)
        varredura--; // continua a varredura de onde parou

    if(varredura>9||varredura<1)
        varredura=0;

    if(dxl_read_byte( HEAD_PAN, P_MOVING )==0)
    	varredura++;

	int LookDown = 180;
	int LeftLimit = 50;
	int RightLimit = 50;

    if(dxl_read_byte( HEAD_PAN, P_MOVING )==0 && varredura==8)
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, pos_servo2+LeftLimit);

    if(dxl_read_byte( HEAD_PAN, P_MOVING )==0 && varredura==7)
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, pos_servo2-RightLimit);
	

    if(dxl_read_byte( HEAD_PAN, P_MOVING )==0 && varredura==6)
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, pos_servo2-RightLimit);


    if(dxl_read_byte( HEAD_PAN, P_MOVING )==0 && varredura==5)
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, pos_servo2+LeftLimit);


    if(dxl_read_byte( HEAD_PAN, P_MOVING )==0 && varredura==4)
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, pos_servo2+LeftLimit);


    if(dxl_read_byte( HEAD_PAN, P_MOVING )==0 && varredura==3)
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, pos_servo2-RightLimit);

    if(dxl_read_byte( HEAD_TILT, P_MOVING )==0 && varredura==2)
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, pos_servo2-RightLimit);

    if(dxl_read_byte( HEAD_TILT, P_MOVING )==0 && varredura==1)
    {
        dxl_write_word(HEAD_PAN, MOVING_SPEED, 700);
        dxl_write_word(HEAD_PAN, P_GOAL_POSITION_L, pos_servo2-RightLimit);    
    }
}


#ifdef DEBUG
cout << "vision received" << A <<" "<< B <<" "<< C << endl;
#endif



