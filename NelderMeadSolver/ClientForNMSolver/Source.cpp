
#include <iostream>
#include <Solver.h>
#include <SimplexFactory.h>

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

  auto bounds = Bounds(-1000, 2000, -3000, 2000);
  
  auto simplex1 = SimplexFactory::simplexTriple(obj_fnc, bounds, eArea::SW);
  auto simplex2 = SimplexFactory::simplexTriple(obj_fnc, bounds, eArea::SE);
  auto simplex3 = SimplexFactory::simplexTriple(obj_fnc, bounds, eArea::NW);
  auto simplex4 = SimplexFactory::simplexTriple(obj_fnc, bounds, eArea::NE);

  Solver my_solver(obj_fnc);
  my_solver.addSimplex(simplex1.get());
  my_solver.addSimplex(simplex2.get());
  my_solver.addSimplex(simplex3.get());
  my_solver.addSimplex(simplex4.get());
    
  double value1(0);
  auto var = VariableSetPtr();
  my_solver.solve(true, 0.001, var, value1);
  
  std::cout << "Solution is " << var->getVar(0) << " " << var->getVar(1) << '\n';
  std::cout << "Value in it " << value1 << '\n';

  _getche();

  return 0;
}