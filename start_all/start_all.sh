#!/bin/bash
#!/RoboFEI-HT/build/bin

sudo echo "starting all processes"
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/RoboFEI-HT/build/lib
# export PATH=$PATH:~/RoboFEI-HT/build/bin
# source #HOME/.bashrc

while true
do
#    if [ ! "$(pidof imu)" ] 
#    then
#       mate-terminal -x sh -c './start_imu.sh' &
#   fi

   if [ ! "$(pidof vision)" ] 
   then
        mate-terminal -x sh -c './start_vision.sh' &
   fi

    if [ ! "$(pidof -x start_decision.sh)" ]  
    then
        mate-terminal -x sh -c './start_decision.sh' &
    fi

    if [ ! "$(pidof control)" ] 
    then
       sleep 2
       mate-terminal -x sh -c 'echo 123456 | sudo -S ./start_control.sh' &
    fi

    sleep 10
done
