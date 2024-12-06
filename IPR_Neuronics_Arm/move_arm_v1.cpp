// File:          move_arm_v1.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include "IPR.hpp"
#include <iostream>
#include <string>


#include <webots/Robot.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Keyboard.hpp>



// All the webots classes are defined in the "webots" namespace
using namespace webots;

double* mapKeyboard(int let, const IPR* ipr, const Keyboard* kbd) {
  static double move[2];
  double res = 0.05;
  //std::cout << let << std::endl;
  if(let=='E') {
    move[0] = 0;
    move[1] = ipr->motorPosition(0) + res;
  }
  else if(let=='S') {
    move[0] = 0;
    move[1] = ipr->motorPosition(0) - res;
  }
  else if(let=='R') {
    move[0] = 1;
    move[1] = ipr->motorPosition(1) + res;
  }
  else if(let=='D') {
    move[0] = 1;
    move[1] = ipr->motorPosition(1) - res;
  }
  else if(let=='T') {
    move[0] = 2;
    move[1] = ipr->motorPosition(2) + res;
  }
  else if(let=='F') {
    move[0] = 2;
    move[1] = ipr->motorPosition(2) - res;
  }
  else if(let=='Y') {
    move[0] = 3;
    move[1] = ipr->motorPosition(3) + res;
  }
  else if(let=='G') {
    move[0] = 3;
    move[1] = ipr->motorPosition(3) - res;
  }
  else if(let=='U') {
    move[0] = 4;
    move[1] = ipr->motorPosition(4) + res;
  }
  else if(let=='H') {
    move[0] = 4;
    move[1] = ipr->motorPosition(4) - res;
  }
  else if(let=='I') {
    move[0] = 5;
    move[1] = ipr->motorPosition(5) + res;
  }
  else if(let=='J') {
    move[0] = 5;
    move[1] = ipr->motorPosition(5) - res;
  }
  return move;
}

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
double gGrabPosition[] = {3.00660, -1.35619, 1.19083, -3.24647, -2.94524, 0.727475, -0.727475};
double gDropPosition[] = {5.09282, 0.0, 3.08698, -1.34990, -2.82252, 0.727475, -0.727475};
double zeroPosition[] = {3,-2.39,0.41,0,-3,0};
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  //Robot *robot = new Robot();
  IPR *ipr = new IPR();
  Keyboard *kbd = new Keyboard();
  kbd->enable(200);

  //ipr->moveToPosition(gDropPosition,true);
  /*ipr->openGripper();
  ipr->closeGripper();
  ipr->dropCube(gDropPosition);
  ipr->moveToInitPosition();
  ipr->grabCube(gGrabPosition);*/
  
  //ipr->grabCube(gGrabPosition);
  //ipr->dropCube(gDropPosition);
  ipr->moveToInitPosition();
  ipr->moveToPosition(zeroPosition,false);
  
  
  // get the time step of the current world.
  int timeStep = (int)ipr->getBasicTimeStep();

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  /*Motor *base = robot->getMotor("base");
  Motor *upperarm = robot->getMotor("upperarm");
  Motor *forearm = robot->getMotor("forearm");
  Motor *wrist = robot->getMotor("wrist");
  Motor *rot_wrist = robot->getMotor("rotational_wrist");*/
  
  std::cout << "BASE_MOTOR = 0,\n"
    "UPPER_ARM_MOTOR = 1,\n"
    "FOREARM_MOTOR = 2,\n"
    "WRIST_MOTOR = 3,\n"
    "ROTATIONAL_WRIST_MOTOR = 4,\n"
    "GRIPPER_MOTOR = 5,\n"
    "MOTOR_NUMBER = 6" << std::endl;
    
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
  int count = 0;
  double adjusted[] = {0,0,0,0,0,0};
  double next_move[] = {0,0};
  // - perform simulation steps until Webots is stopping the controller
  while (ipr->step(timeStep) != -1) {
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    //  double val = ds->getValue();

    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    /*base->setPosition(2);
    wait(10);
    upperarm->setPosition(-2);
    forearm->setPosition(2);
    wrist->setPosition(2);
    rot_wrist->setPosition(2);*/
    if(count++ % 100 == 0) {
      for(int i = 0; i < 6; i++) {
        std::cout << ipr->motorPosition(i) << ", ";
      }
      std::cout << std::endl;
    }
    
    //ipr->moveToInitPosition();
    
    int key = kbd->getKey();
    if(key != -1) {
      //double *next_move2 = mapKeyboard(key, ipr, kbd);
      //ipr->setMotorPosition(next_move2[0], next_move2[1]);
      if(key == kbd->UP) {
        for(int i = 1; i < 4; i++) {
          adjusted[i] = ipr->motorPosition(i);
        }
        if(adjusted[2] < 0.8) {
          adjusted[1] = adjusted[1] + 0.05;
          adjusted[2] = adjusted[2] + 0.1;
          adjusted[3] = adjusted[3] - 0.19;
        }
        else {
          adjusted[1] = adjusted[1] - 0.05;
          adjusted[2] = adjusted[2] + 0.1;
          adjusted[3] = adjusted[3] - 0.05;
        }
        //ipr->moveToPosition(adjusted, false);
        ipr->setMotorPosition(1, adjusted[1]);
        ipr->setMotorPosition(2, adjusted[2]);
        ipr->setMotorPosition(3, adjusted[3]);
      }
      else if(key == kbd->DOWN) {
        for(int i = 1; i < 4; i++) {
          adjusted[i] = ipr->motorPosition(i);
        }
        if(adjusted[2] < 0.7) {
          adjusted[1] = adjusted[1] - 0.05;
          adjusted[2] = adjusted[2] - 0.1;
          adjusted[3] = adjusted[3] + 0.15;
        }
        else {
          adjusted[1] = adjusted[1] + 0.05;
          adjusted[2] = adjusted[2] - 0.1;
          adjusted[3] = adjusted[3] + 0.05;
        }
        //ipr->moveToPosition(adjusted, false);
        ipr->setMotorPosition(1, adjusted[1]);
        ipr->setMotorPosition(2, adjusted[2]);
        ipr->setMotorPosition(3, adjusted[3]);
      }
      else if(key == kbd -> LEFT) {
        next_move[0] = 0;
        next_move[1] = ipr->motorPosition(0) - 0.1;
        ipr->setMotorPosition(next_move[0], next_move[1]);
      }
      else if(key == kbd -> RIGHT) {
        next_move[0] = 0;
        next_move[1] = ipr->motorPosition(0) + 0.1;
        ipr->setMotorPosition(next_move[0], next_move[1]);
      }
      else if(key == 'Z') {
        next_move[0] = 5;
        next_move[1] = ipr->motorPosition(5) - 0.1;
        ipr->setMotorPosition(next_move[0], next_move[1]);
      }
      else if(key == 'X') {
        next_move[0] = 5;
        next_move[1] = ipr->motorPosition(5) + 0.1;
        ipr->setMotorPosition(next_move[0], next_move[1]);
      }
    }
    
    
    //ipr->moveToPosition(zeroPosition,false);
    
  };

  // Enter here exit cleanup code.

  delete ipr;
  delete kbd;
  return 0;
}
