#ifndef SolverData_hpp
#define SolverData_hpp

#include "physics/objects/ObjectData.hpp"
#include "physics/constraints/ConstraintData.hpp"

#include <memory>
#include <vector>

struct SolverData
{
    SolverData();
    
    std::shared_ptr<ObjectData> obj;
    std::vector<std::shared_ptr<ConstraintDataBase>> ctns;
};


#endif /* SolverData_hpp */
