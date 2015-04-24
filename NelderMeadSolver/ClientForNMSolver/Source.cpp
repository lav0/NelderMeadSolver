
#include <iostream>
#include <Solver.h>

#include <conio.h>
#include <iostream>

int main()
{
  auto obj_fnc = [](double x, double y) {
    
    double sx = x - 11;
    double sy = y - 15;

    return sx * sx + sy * sy + 1;
    
  };

  Solver my_solver(obj_fnc, -1000, 2000, -3000, 2000);
    
  double sol_x1(0), sol_y1(0), value1(0);
  my_solver.solve(true, 0.001, sol_x1, sol_y1, value1);

  std::cout << "Solution is " << sol_x1 << " " << sol_y1 << '\n';
  std::cout << "Value in it " << value1 << '\n';

  _getche();

  return 0;
}