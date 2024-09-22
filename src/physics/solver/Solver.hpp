#ifndef Solver_hpp
#define Solver_hpp

#include "physics/solver/SolverData.hpp"
#include "physics/system/Assembly.hpp"
#include "physics/Common.hpp"

class Solver
{
public:
    
    Solver();

    void initialize(const SolverData& data);
    
    void step(const float h, SolverData& data);
    
private:
    
    void assembleGlobalMatrix(const float h, const SolverData& data);
    
    void assembleGlobalVector(const float h, const SolverData& data);
    
    std::vector<V3f> toV3f(const Eigen::VectorXf& solution);
    
    V3f gravity;
    std::shared_ptr<Assembly> system;
};

#endif /* Solver_hpp */
