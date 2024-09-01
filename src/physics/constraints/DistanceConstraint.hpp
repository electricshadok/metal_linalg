#ifndef DistanceConstraint_hpp
#define DistanceConstraint_hpp

#include "ConstraintData.hpp"

class AnchorDistanceConstraint : public ConstraintData<1>
{
public:
    AnchorDistanceConstraint(size_t numConstraints);

    // Setup constraints based on objectData connectivity
    void setupConstraint(const ObjectData& objData, float stiffness) override;

    // Compute forces and Jacobians
    void computeForces(const ObjectData& objData) override;

private:
    // Fixed anchor points (size: numConstraints)
    std::vector<Eigen::Vector3f> anchors;

    // Rest lengths for each constraint (size: numConstraints)
    std::vector<float> rest;
};

class DistanceConstraint : public ConstraintData<2>
{
public:
    DistanceConstraint(size_t numConstraints);

    // Setup constraints based on objectData connectivity
    void setupConstraint(const ObjectData& objData, float stiffness) override;

    // Compute forces and Jacobians
    void computeForces(const ObjectData& objData) override;

private:
    // Rest lengths for each constraint (size: numConstraints)
    std::vector<float> rest;
};


#endif /* DistanceConstraint_hpp */
