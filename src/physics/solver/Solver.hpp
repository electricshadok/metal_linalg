#ifndef Solver_hpp
#define Solver_hpp

#include "physics/objects/ObjectData.hpp"
#include "physics/system/Assembly.hpp"

class Solver
{
public:
    
    Solver();
    
    void initialize(const ObjectData& obj);
    
    void step(const float h, ObjectData& obj);
    
private:
    Eigen::Vector3f gravity;
    std::shared_ptr<Assembly> system;
};

#endif /* Solver_hpp */
