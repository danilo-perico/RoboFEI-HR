#! /usr/bin/env python
#coding: utf-8
#  ----------------------------------------------------------------------------
#  ****************************************************************************
#  * @file decision.py
#   *@project: ROBOFEI-HT - FEI 😛
#  * @author Isaac Jesus da Silva
#  * @version V0.0.1
#  * @created 06/10/2015
#  * @e-mail isaac25silva@yahoo.com.br
#  * @brief Decision
#   *@modified by: Danilo H. Perico
#   *@modified: 14 Oct 2015
#  ****************************************************************************
#  Program to execute the Decision process
#  ****************************************************************************

#import parser for arguments    
import argparse

try:
    from configparser import ConfigParser
except ImportError:
    from ConfigParser import ConfigParser  # ver. < 3.0

#looking for the library SharedMemory
from SharedMemory import SharedMemory 

import time

print
print '################### Decision #########################'
print 

##create arguments for each behavior
#parser = argparse.ArgumentParser(description='Robot behavior', epilog= 'Se nenhuma ação for selecionada um comportamento comum será adotado! / If there is not a selected argument an ordinary behavior will be adopted!')
#parser.add_argument('--golie', '-g', action="store_true", help = 'Seleciona comportamento de goleiro / selects golie behavior')
#parser.add_argument('--quarterback', '-q', action="store_true", help = 'Seleciona comportamento de zagueiro / selects quarterback behavior')
#parser.add_argument('--attacker', '-a', action="store_true", help = 'Seleciona comportamento de atacante / selects attacker behavior')

#args = parser.parse_args()

#Golie decision:
#if args.golie == True:
#    robot = Golie()
#
##Quarterback decicion:    
#elif args.quarterback == True:
#    robot = Quarterback()
#    
##Attacker decision:    
#elif args.attacker == True:
#    robot = Attacker()
#    
##Ordinary decision:
#else:
#    robot = Ordinary()

class TreatingRawData(object):

     #Instantiate the BlackBoard's class:
    bkb = SharedMemory()
    
    # instantiate:
    config = ConfigParser()

    # looking for the file config.ini:
    config.read('../../Control/Data/config.ini')
    
    def __init__(self):
        print
        print 'Raw data - read (get) and write (set) methods'
        print
        
    def get_referee_usage(self):
        return self.config.get('Decision', 'use_vision') # lê na section Decision a variavel use_vision

    def get_motor_tilt(self):
        return self.bkb.read_int('VISION_MOTOR1_ANGLE')
        
    def get_motor_pan(self):
        return self.bkb.read_int('VISION_MOTOR2_ANGLE')
        
    def get_head_pan_initial(self):
        return self.config.getint('Offset', 'ID_19')

    def get_head_tilt_initial(self):
        return self.config.getint('Offset', 'ID_20')
        
    def get_search_ball_status(self):
        return self.bkb.read_int('VISION_SEARCH_BALL')
        
    def get_lost_ball_status(self):
        return self.bkb.read_int('VISION_LOST_BALL')

    def set_stand_still(self):
        print 'stand still'
        return self.bkb.write_int('DECISION_ACTION_A', 0)

    def set_walk_forward(self):
        print 'walk forward',
        return self.bkb.write_int('DECISION_ACTION_A', 1)
        
    def set_angle_turn(self,vel):
        return self.bkb.write_int('DECISION_ACTION_B', vel)
        
    def set_turn_left(self):
        print 'turn left'
        return self.bkb.write_int('DECISION_ACTION_A', 2)
        
    def set_turn_right(self):
        print 'turn right'
        return self.bkb.write_int('DECISION_ACTION_A', 3)
        
    def set_kick_right(self):
        print 'kick right'
        return self.bkb.write_int('DECISION_ACTION_A', 4)
        
    def set_kick_left(self):
        print 'kick left'
        return self.bkb.write_int('DECISION_ACTION_A', 5)
        
    def set_sidle_left(self):
        print 'sidle left'
        return self.bkb.write_int('DECISION_ACTION_A', 6)
        
    def set_sidle_right(self):
        print 'sidle right'
        return self.bkb.write_int('DECISION_ACTION_A', 7)
        
    def set_walk_forward_slow(self):
        print 'walk forward slow'
        self.set_walk_speed(5)
        return self.bkb.write_int('DECISION_ACTION_A', 8)
        
    def set_revolve_around_ball(self):
        print 'revolve around ball'
        return self.bkb.write_int('DECISION_ACTION_A', 9)
        
    def set_walk_backward(self):
        print 'walk backward'
        return self.bkb.write_int('DECISION_ACTION_A', 10)
        
    def set_gait(self):
        print 'gait'
        return self.bkb.write_int('DECISION_ACTION_A', 11)
        
    def set_pass_left(self):
        print 'pass left'
        return self.bkb.write_int('DECISION_ACTION_A', 12)
        
    def set_pass_right(self):
        print 'pass right'
        return self.bkb.write_int('DECISION_ACTION_A', 13)
        
    def set_jump_left(self):
        return self.bkb.write_int('DECISION_ACTION_A', 14)

    def set_jump_right(self):
        return self.bkb.write_int('DECISION_ACTION_A', 15)
        
    def set_vision_line(self):
        return self.bkb.write_int('DECISION_ACTION_VISION', 1)
        
        
    def delta_position_pan(self):
        '''right > 0 / left < 0'''
        return self.get_head_pan_initial() - self.get_motor_pan()

    def delta_position_tilt(self):
        '''up > 0 / down < 0 / middle is looking for the horizon'''
        return self.get_head_tilt_initial() - self.get_motor_tilt()

        
##############################################################################

class Ordinary(TreatingRawData):
    " " " Ordinary class " " "
    
    def __init__(self):
        print
        print 'Ordinary behavior called' 
        print
                
    def decision(self):
            self.set_vision_line() #set vision to find ball

            self.set_walk_forward()
            if self.delta_position_pan() >= 4 or self.delta_position_pan() <= -4:
				self.set_angle_turn(self.delta_position_pan()*0.15)
				print "   Turn ", self.delta_position_pan()*0.15

robot = Ordinary()

while True:
    robot.decision()

    time.sleep(0.2)

#            if self.get_search_ball_status() == 1: #1 - searching ball
#                self.set_stand_still()
#                while self.get_lost_ball_status() == 1: #1 - lost ball
#                   self.set_turn_right()
#                self.set_stand_still()
#            else:
#                if self.get_lost_ball_status() == 1:
#                    self.set_stand_still() #stop robot because the ball
#                    #can be already found
#                else:
#                    #pan in the middle:
#                    if self.delta_position_pan() <= 70 and self.delta_position_pan() >= -70:
#                        if self.delta_position_tilt() >= -84:
#                            self.set_walk_forward()
#                        elif self.delta_position_tilt() < -84 and self.delta_position_tilt() >= -210:
#                            self.set_walk_forward_slow()
#                        else:
#                            if self.delta_position_pan() >= 0:
#                                if self.get_orientation_usage() == 'yes':
#                                    self.set_vision_orientation()
#                                    time.sleep(2)
#                                    if self.get_orientation() == 1:
#                                        self.set_kick_right()
#                                    else:
#                                        self.set_revolve_around_ball()
#                                        time.sleep(7)
#                                        self.set_vision_ball()
#                                else:
#                                    self.set_kick_right()
#                            else:
#                                if self.get_orientation_usage() == 'yes':
#                                    self.set_vision_orientation()
#                                    time.sleep(2)
#                                    if self.get_orientation() == 1:
#                                        self.set_kick_left()
#                                    else:
#                                        self.set_revolve_around_ball()
#                                        time.sleep(7)
#                                        self.set_vision_ball()
#                                else:
#                                    self.set_kick_left()

#                    #pan in the right:
#                    if self.delta_position_pan() > 70:
#                        if self.delta_position_tilt() >= -210:
#                            self.set_turn_right()
#                        elif self.delta_position_tilt() < -210 and self.delta_position_pan() > 115:
#                            self.set_sidle_right()
#                        else:
#                            if self.get_orientation_usage() == 'yes':
#                                self.set_vision_orientation()
#                                time.sleep(2)
#                                if self.get_orientation() == 1:
#                                    self.set_kick_right()
#                                else:
#                                    self.set_revolve_around_ball()
#                                    time.sleep(7)
#                                    self.set_vision_ball()
#                            else:
#                                self.set_kick_right()

#                    #pan in the left:
#                    if self.delta_position_pan() < -70:
#                        if self.delta_position_tilt() >= -210:
#                            self.set_turn_left()
#                        elif self.delta_position_tilt() < -210 and self.delta_position_pan() < -95:
#                            self.set_sidle_left()
#                        else:
#                            if self.get_orientation_usage() == 'yes':
#                                self.set_vision_orientation()
#                                time.sleep(2)
#                                if self.get_orientation() == 1:
#                                    self.set_kick_right()
#                                else:
#                                    self.set_revolve_around_ball()
#                                    time.sleep(7)
#                                    self.set_vision_ball()
#                            else:
#                                self.set_kick_right()
#        else:
#            print 'Invalid argument received from referee!'
    
    
    
