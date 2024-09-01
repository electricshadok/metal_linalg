#ifndef ConstraintData_hpp
#define ConstraintData_hpp

#include "physics/objects/ObjectData.hpp"
#include <vector>
#include <Eigen/Dense>

// Base class for all ConstraintData
struct ConstraintDataBase
{
    virtual ~ConstraintDataBase() = default;

    // Setup constraints based on objectData connectivity
    virtual void setupConstraint(const ObjectData& objData, float stiffness) = 0;

    // Compute forces and Jacobians
    virtual void computeForces(const ObjectData& objData) = 0;
};

// Structure to hold data related to constraints in a simulation.
// @tparam N Number of nodes.
template<size_t N>
struct ConstraintData : public ConstraintDataBase
{
    ConstraintData(size_t numConstraints);
    
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~ConstraintData() = default;
    
    // Setup constraints based on objectData connectivity
    virtual void setupConstraint(const ObjectData& objData, float stiffness) = 0;

    // Compute forces and Jacobians
    virtual void computeForces(const ObjectData& objData) = 0;
    
    // Stiffness values for each constraint (size: C)
    std::vector<float> k;

    // Node indices associated with each constraint (size: C * N)
    std::vector<int> ids;

    // Forces applied to each node under each constraint (size: C * N)
    std::vector<Eigen::Vector3f> f;

    // Jacobian matrices with respect to positions (size: C * N * N)
    // TODO: constraints are most likely symmetric, we could optimize this code
    std::vector<Eigen::Matrix3f> dxdf;

    // Jacobian matrices with respect to velocities (size: C * N * N)
    // TODO: constraints are most likely symmetric, we could optimize this code
    std::vector<Eigen::Matrix3f> dvdf;
};

#endif /* ConstraintData_hpp */
