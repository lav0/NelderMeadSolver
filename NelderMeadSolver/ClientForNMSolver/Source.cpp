
#include <iostream>
#include <Solver.h>

#include <conio.h>
#include <memory>

int main()
{
  auto obj_fnc = [](const VariableSetPtr& vars) {
    
    auto point = dynamic_cast<Point*>(vars.get());
    auto x = point->X;
    auto y = point->Y;

    double sx = x - 11;
    double sy = y - 15;

    return sx * sx + sy * sy + 1;
    
  };

  Solver my_solver(obj_fnc, -1000, 2000, -3000, 2000);
    
  double value1(0);
  auto var = Point(0.0, 0.0);
  my_solver.solve(true, 0.001, var, value1);

  std::cout << "Solution is " << var.X << " " << var.Y << '\n';
  std::cout << "Value in it " << value1 << '\n';

  _getche();

  return 0;
}