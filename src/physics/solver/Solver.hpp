#ifndef Solver_hpp
#define Solver_hpp

#include "physics/solver/SolverData.hpp"
#include "physics/system/Assembly.hpp"


class Solver
{
public:
    
    Solver();
    
    void initialize(const SolverData& data);
    
    void step(const float h, SolverData& data);
    
private:
    
    void assembleGlobalMatrix(const float h, const SolverData& data);
    
    void assembleGlobalVector(const float h, const SolverData& data);
    
    std::vector<Eigen::Vector3f> toVector3f(const Eigen::VectorXf& solution);
    
    Eigen::Vector3f gravity;
    std::shared_ptr<Assembly> system;
};

#endif /* Solver_hpp */
