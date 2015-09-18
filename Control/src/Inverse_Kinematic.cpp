#include <dynamixel.h>
#include <math.h>
#include <cmath>
#include <unistd.h>

#define STANDUP 0.18599999 //0.18599999
#define L1 0.093           //0.093
#define L2 0.093
#define Ry 3.1416/2
//#define VEL 200

//----------------------------------------------------------------------------------
//==================================================================================

void inverse_kinematic_right_leg(float x, float y_e, int inclin, int VEL)
{

//float x=0;
float y=STANDUP-y_e;

float h, fi, A, theta1, B, theta2, C, theta3, max_angle, t1, t2, t3;

//h=sqrt(x*x + z*z);

//fi = atan(x/z) + 3.1416/2;

theta2 = acos((x*x + y*y - L1*L1 - L2*L2)/(2*L1*L2));

if(x>=0)
theta1 = atan(y/x) - acos((x*x + y*y + L1*L1 - L2*L2)/(2*L1*sqrt(x*x+y*y)))-3.1416/2;
else
theta1 = atan(y/x) - acos((x*x + y*y + L1*L1 - L2*L2)/(2*L1*sqrt(x*x+y*y)))+3.1416/2;

theta3 = Ry - theta1 - theta2-3.1416/2 - inclin*3.1416/180;

//--- verifica qual maior theta --
t1 = std::abs(dxl_read_word( 10, P_PRESENT_POSITION_L) - std::abs(StandupPos[9]-theta1/0.0051133));
t2 = std::abs(dxl_read_word( 12, P_PRESENT_POSITION_L) - std::abs(StandupPos[11]-theta2/0.0051133));
t3 = std::abs(dxl_read_word( 14, P_PRESENT_POSITION_L) - std::abs(StandupPos[13]+theta3/0.0051133));

max_angle=t1;

if(t2>t1)
max_angle = t2;

if(t3>max_angle)
max_angle=t3;
//-------------------------------

//printf("\nt1 =  %f | t2 = %f | t3 = %f | max_angle = %f\n", t1, t2, t3, max_angle);
//printf("\nRight Leg \ntheta1 = %f | theta2 = %f | theta3 = %f | t = %f\n",theta1*180/3.1416,
                    //theta2*180/3.1416, theta3*180/3.1416, max_angle/(VEL*2.27328));
float zc, xc;
xc = L1*cos(theta1) + L2*cos(theta1+theta2);
zc = L1*sin(theta1) + L2*sin(theta1+theta2);
fi = theta1 + theta2 + theta3;

if(theta2<180)
{
//printf("Y = %f | X = %f | Fi = %f\n", zc, xc, fi*180/3.1416);

dxl_write_word(10, MOVING_SPEED, VEL*(t1/max_angle));
dxl_write_word(12, MOVING_SPEED, VEL*(t2/max_angle));
dxl_write_word(14, MOVING_SPEED, VEL*(t3/max_angle));

dxl_write_word(10, P_GOAL_POSITION_L, StandupPos[9]-theta1/0.0051133);//512
dxl_write_word(12, P_GOAL_POSITION_L, StandupPos[11]-theta2/0.0051133);//510
dxl_write_word(14, P_GOAL_POSITION_L, StandupPos[13]+theta3/0.0051133);//562
}
else
printf("Posição fora do alcance do robo\n");
}
//=======================================================================================
//---------------------------------------------------------------------------------------

void inverse_kinematic_left_leg(float x, float y_e, int inclin, int VEL)
{

//float x=0;
float y=STANDUP-y_e;

float h, fi, A, theta1, B, theta2, C, theta3, max_angle, t1, t2, t3;

theta2 = acos((x*x + y*y - L1*L1 - L2*L2)/(2*L1*L2));

if(x>=0)
theta1 = atan(y/x) - acos((x*x + y*y + L1*L1 - L2*L2)/(2*L1*sqrt(x*x+y*y)))-3.1416/2;
else
theta1 = atan(y/x) - acos((x*x + y*y + L1*L1 - L2*L2)/(2*L1*sqrt(x*x+y*y)))+3.1416/2;

theta3 = Ry - theta1 - theta2-3.1416/2 - inclin*3.1416/180;

//--- verifica qual maior theta --
t1 = std::abs(dxl_read_word( 16, P_PRESENT_POSITION_L) - std::abs(StandupPos[15]+theta1/0.0051133));
t2 = std::abs(dxl_read_word( 18, P_PRESENT_POSITION_L) - std::abs(StandupPos[17]-theta2/0.0051133));
t3 = std::abs(dxl_read_word( 20, P_PRESENT_POSITION_L) - std::abs(StandupPos[19]-theta3/0.0051133));

max_angle=t1;

if(t2>t1)
max_angle = t2;

if(t3>max_angle)
max_angle=t3;
//-------------------------------

//printf("\nLeft Leg\ntheta1 = %f | theta2 = %f | theta3 = %f | t = %f\n",theta1*180/3.1416,
 //                       theta2*180/3.1416, theta3*180/3.1416, max_angle/(VEL*2.27328));
float zc, xc;
xc = L1*cos(theta1) + L2*cos(theta1+theta2);
zc = L1*sin(theta1) + L2*sin(theta1+theta2);
fi = theta1 + theta2 + theta3;

if(theta2<180)
{
//printf("Y = %f | X = %f | Fi = %f\n", zc, xc, fi*180/3.1416);

dxl_write_word(16, MOVING_SPEED, VEL*t1/max_angle);
dxl_write_word(18, MOVING_SPEED, VEL*t2/max_angle);
dxl_write_word(20, MOVING_SPEED, VEL*t3/max_angle);

dxl_write_word(16, P_GOAL_POSITION_L, StandupPos[15]+theta1/0.0051133);//512
dxl_write_word(18, P_GOAL_POSITION_L, StandupPos[17]-theta2/0.0051133);//510
dxl_write_word(20, P_GOAL_POSITION_L, StandupPos[19]-theta3/0.0051133);//467
}
else
printf("Posição fora do alcance do robo\n");
}

//===================================================================================

void inclina_plano(int select_leg, int angle, int vel, int offset_pe)
{
    if(select_leg==0) // selecionou perna direita
    {
        dxl_write_word(11, MOVING_SPEED, vel);
        dxl_write_word(13, MOVING_SPEED, vel);
        dxl_write_word(11, P_GOAL_POSITION_L, StandupPos[10]-angle);//510
        dxl_write_word(13, P_GOAL_POSITION_L, StandupPos[12]-angle-offset_pe);//467
    }
    if(select_leg==1) // selecionou perna esquerda
    {
        dxl_write_word(17, MOVING_SPEED, vel);
        dxl_write_word(19, MOVING_SPEED, vel);
        dxl_write_word(17, P_GOAL_POSITION_L, StandupPos[16]-angle);//510
        dxl_write_word(19, P_GOAL_POSITION_L, StandupPos[18]-angle-offset_pe);//467
    }


}

