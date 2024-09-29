#ifndef DistanceConstraint_hpp
#define DistanceConstraint_hpp

#include "ConstraintData.hpp"
#include "physics/Common.hpp"

class AnchorDistanceConstraint : public ConstraintData<1>
{
public:
    AnchorDistanceConstraint(size_t numConstraints);
    
    // Get anchor
    V3f& anchor(size_t anchor_idx);

    // Setup constraints based on objectData connectivity
    void setupConstraint(const ObjectData& objData, float stiffness, float damping) override;

    // Compute forces and Jacobians
    void updateDerivatives(const ObjectData& objData) override;

private:
    // Fixed anchor points (size: numConstraints)
    std::vector<V3f> anchors;

    // Rest lengths for each constraint (size: numConstraints)
    std::vector<float> rest;
};

class DistanceConstraint : public ConstraintData<2>
{
public:
    DistanceConstraint(size_t numConstraints);

    // Setup constraints based on objectData connectivity
    void setupConstraint(const ObjectData& objData, float stiffness, float damping) override;

    // Compute forces and Jacobians
    void updateDerivatives(const ObjectData& objData) override;

private:
    // Rest lengths for each constraint (size: numConstraints)
    std::vector<float> rest;
};


#endif /* DistanceConstraint_hpp */
