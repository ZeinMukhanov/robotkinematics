//***********************************************************//
//** Author:Zein Mukhanov                                  **//
//** Date Created: December 01, 2021                       **//
//** Assignment 4: Robot Kinematics                        **//
//** UH-1000 Computer Programming for Engineers, NYUAD     **//
//** Problem:                                              **//
//** Designing the software to simulate the motion of a    **// 
//** multi-degree of freedom kinematic chains that form    **//
//** the structure of a robotic system.                    **//
//***********************************************************//

#include <iostream>

#include "robot.h"
//main function
int main() {
  //test 1
  segment a (point(0,0), 0.5, 50);
  a.printSegmentInfo();
  segment b (a.getEndP(), 0.7, 60);
  b.printSegmentInfo();

  robot d;
  d.newSegment(&a);
  d.newSegment(&b);
  d.drawGraph("g1.png");
 

 //test 2
  segment v (point(0,0), 0.5, 50);
  segment n (v.getEndP(), 0.7, 60);

  robot d1;
  d1.newSegment (&v);
  d1.newSegment(&n);
  d1.deleteSegment();
  d1.drawGraph("g2.png");


//test 3
  segment c (point(0,0), 0.5, 50);
  segment e (c.getEndP(), 0.7, 60);
  robot d2;
  d2.newSegment (&c);
  d2.newSegment(&e);
  double deg[] = {0.3, 0.5};
  d2.applyForwardKinematics(deg, 2);
  d2.drawGraph("g3.png");

  return 0;
} 