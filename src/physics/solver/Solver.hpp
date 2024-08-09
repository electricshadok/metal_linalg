#ifndef Solver_hpp
#define Solver_hpp

#include "physics/Scene.hpp"
#include "physics/system/Assembly.hpp"

class Solver
{
public:
    
    void initialize(const Scene& scene);
    
    void step(const float dt, const Scene& scene);
    
private:
    std::shared_ptr<Assembly> system;
};

#endif /* Solver_hpp */
