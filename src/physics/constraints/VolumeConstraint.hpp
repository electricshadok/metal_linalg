#ifndef VolumeConstraint_hpp
#define VolumeConstraint_hpp

#include "ConstraintData.hpp"

class VolumeConstraint : public ConstraintData<4>
{
public:
    VolumeConstraint(size_t numConstraints);

    // Setup constraints based on objectData connectivity
    void setupConstraint(const ObjectData& objData, float stiffness) override;

    // Compute forces and Jacobians
    void updateDerivatives(const ObjectData& objData) override;

private:
    // Rest lengths for each constraint (size: numConstraints)
    std::vector<float> rest;
};

#endif /* VolumeConstraint_hpp */
