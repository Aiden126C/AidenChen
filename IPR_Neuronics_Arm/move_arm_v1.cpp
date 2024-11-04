// File:          move_arm_v1.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include "IPR.hpp"


#include <webots/Robot.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>



// All the webots classes are defined in the "webots" namespace
using namespace webots;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
double gGrabPosition[] = {3.00660, -1.35619, 1.19083, -3.24647, -2.94524, 0.727475, -0.727475};
double gDropPosition[] = {5.09282, 0.0, 3.08698, -1.34990, -2.82252, 0.727475, -0.727475};

// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  //Robot *robot = new Robot();
  IPR *ipr = new IPR();


  //ipr->moveToPosition(gDropPosition,true);
  /*ipr->openGripper();
  ipr->closeGripper();
  ipr->dropCube(gDropPosition);
  ipr->moveToInitPosition();
  ipr->grabCube(gGrabPosition);*/
  
  ipr->grabCube(gGrabPosition);
  ipr->dropCube(gDropPosition);
  ipr->moveToInitPosition();
  
  // get the time step of the current world.
  int timeStep = (int)ipr->getBasicTimeStep();

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  /*Motor *base = robot->getMotor("base");
  Motor *upperarm = robot->getMotor("upperarm");
  Motor *forearm = robot->getMotor("forearm");
  Motor *wrist = robot->getMotor("wrist");
  Motor *rot_wrist = robot->getMotor("rotational_wrist");*/
  
  
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
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
  };

  // Enter here exit cleanup code.

  delete ipr;
  return 0;
}
