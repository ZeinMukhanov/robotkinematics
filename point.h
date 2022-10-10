#include <cmath>
#include <iomanip>

using namespace std;

//point class
class point {
  private:
  //declaration of private variables
    double x, y;
  public:
  //default constructor
    point () {
      x = 0;
      y = 0;
    }
  //non-default constructor
    point (double a, double b) {
      x = a;
      y = b;
    }
  //method for setting the value of X
    void setX (double x1) {
      x = x1;
    }
  //method for setting the value of Y
    void setY (double y1) {
      y = y1;
    }
  //getter for X
    double getX () {
      return (x);
    }
  //getter for Y
    double getY () {
      return (y);
    }
};