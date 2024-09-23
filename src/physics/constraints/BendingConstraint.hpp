#ifndef BendingConstraint_hpp
#define BendingConstraint_hpp

#include "ConstraintData.hpp"

class BendingConstraint : public ConstraintData<4>
{
public:
    BendingConstraint(size_t numConstraints);

    // Setup constraints based on objectData connectivity
    void setupConstraint(const ObjectData& objData, float stiffness, float damping) override;

    // Compute forces and Jacobians
    void updateDerivatives(const ObjectData& objData) override;

private:
    // Rest lengths for each constraint (size: numConstraints)
    std::vector<float> rest;
};

#endif /* BendingConstraint_hpp */
