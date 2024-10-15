#ifndef AreaContraint_hpp
#define AreaContraint_hpp

#include "ConstraintData.hpp"

class AreaConstraint : public ConstraintData<3>
{
public:
    AreaConstraint(size_t numConstraints);

    // Setup constraints based on objectData connectivity
    void setupConstraint(const ObjectData& objData, float stiffness, float damping);

    // Compute forces and Jacobians
    void updateDerivatives(const ObjectData& objData) override;

private:
    // Rest lengths for each constraint (size: numConstraints)
    std::vector<float> rest;
};

#endif /* AreaContraint_hpp */
