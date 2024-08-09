#ifndef LinearSolver_hpp
#define LinearSolver_hpp

#include <Eigen/Dense>
#include "physics/system/Assembly.hpp"

class LinearSolver
{
public:
    
    Eigen::VectorXd solve(Assembly& assembly);
    
};

#endif /* LinearSolver_hpp */
