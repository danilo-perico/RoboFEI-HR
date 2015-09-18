#include <dynamixel.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
 #include <cstdlib>


using namespace std;

void keyboard(int key)
{
        switch(key){
            case 97: //a
            cout << "Levantar quando as costas estão para cima" << endl;
            levantar_de_costas();
            main(0,0);
            break;

            case 98: //b
            cout << "Levantar quando o peito está para cima" << endl;
            levantar_de_frente();
            main(0,0);
            break;

             case 99: //c
            cout << "Chutar" << endl;
            chute_direito();
            main(0,0);
            break;

             case 102: //f
            cout << "Andar para frente" << endl;
            //andar_veloz(1);
            andar_rapido(1);
            main(0,0);
            break;

            case 100: //d
            cout << "Vira para direita" << endl;
            andar_lateral_direita();
            main(0,0);
            break;

             case 101: //e
            cout << "Vira para esquerda" << endl;
            //virar_esq(1);
            main(0,0);
            break;

             case 107: //k
            cout << "Andar curto para frente" << endl;
            //andar_curto(1);
            main(0,0);
            break;

             case 118: //v
            cout << "Marchando" << endl;
            andar_marchando();
            main(0,0);
            break;

             case 115: //s
            cout << "Stop" << endl;
            robo_ereto();
            main(0,0);
            break;

            case 104: //h
            cout << "Greetings" << endl;
            calling();
            main(0,0);
            break;

              case 27: //ESC (stop)
            cout << "Stop and shutdown code" << endl;
            robo_ereto();
            exit(0);
            break;

        }
}
