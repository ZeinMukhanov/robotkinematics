#include "point.h"

class segment {
  private:
  //declaring the private variables
    point startP;
    //method for calculating the coordinates of the end effector
    point endPoint() {
       double x2 = startP.getX () + (getL()*cos(getA()));
       double y2 = startP.getY () + (getL()*sin(getA()));
       cout << getA() << endl;
       cout << x2 << " & " << y2 << " & " << getL() << endl;
       return point (x2, y2);
    }
    point endP;
    double angle;
    double length;
    segment *childS;
  //declaring the public members
  public:
    segment (point startPoint, double angle1, double length1) {
      length = length1;
      startP = startPoint;
      angle = angle1;  
      childS = NULL;
      endP = endPoint();
    }

    segment* getChildS () {
      return childS;
    }
//setter childSegment
    void setChildS (segment* childSegment) {
       childS = childSegment;
    }
//getter for angle
    double getA () {
      return angle;
    }
//setter for angle
    void setA (double angle1) {
      angle = angle1;
      endP = endPoint();
    }
//getter for length
    double getL () {
      return length;
    }

//setter for length
    void setL (double length1) {
      length = length1;
      endP = endPoint();
    }
//getter for the starting X coordinate
    double getStartPx () {
      return startP.getX();
    }
//getter for the starting Y coordinate
    double getStartPy () {
      return startP.getY();
    }
//getter for the end X coordinate
    double getEndPx() {
      return endP.getX();
    }
//getter for the end Y coordinate
    double getEndPy() {
      return endP.getY();
    }
//getter for start point
    point getStartP () {
      return startP;
    }
//getter for end point
    point getEndP () {
      return endP;
    }

//setter for start point
    void setStartP(point point1) {
        startP = point1;
        endP = endPoint();
    }
    
     
//method for outputing the segmentation information on the screen
    void printSegmentInfo () {
      cout.setf(ios::left);
      cout << "------------------------------------------------" << endl;
      cout << setw(10) << "The coordinates of the start point are " << "(" << getStartPx() << "," << getStartPy () << ")" << endl;
      cout << setw (10) << "The angle is " << setw(20) << getA()  << endl;
      cout << setw(10) << "The length is " << setw(20) << getL() << endl;
      cout << setw(10) << "The coordinates of the end point are " << "("  << getEndPx () << "," << getEndPy () << ")" << endl;
      cout << "------------------------------------------------" << endl;
    }
    
};