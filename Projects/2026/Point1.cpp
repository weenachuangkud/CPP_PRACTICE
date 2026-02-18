#include <iostream>
#include <memory>

class Point
{
public:
  int x,y;

  Point(const int& newX, const int& newY) : x(newX), y(newY) {};
  ~Point()
  {
    std::cout<< "Deleted Point" << std::endl;
  }
  
  void Display() 
  {
    std::cout<< x << "," << y << std::endl;
  }
};

int main()
{ 
  Point p1(0, 0);
  p1.Display();
  return 0;
}
