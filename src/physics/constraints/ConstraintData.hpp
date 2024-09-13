#ifndef ConstraintData_hpp
#define ConstraintData_hpp

#include "physics/objects/ObjectData.hpp"
#include <vector>
#include <Eigen/Dense>

// Base class for all ConstraintData
struct ConstraintDataBase
{
    ConstraintDataBase(size_t num_c, size_t num_ids, size_t num_grad, size_t num_jac);
    
    virtual size_t size() const = 0;

    // Setup constraints based on objectData connectivity
    virtual void setupConstraint(const ObjectData& objData, float stiffness) = 0;

    // Compute forces and Jacobians
    virtual void updateDerivatives(const ObjectData& objData) = 0;
    
    // Return the number of constraints
    size_t numConstraints() const;
    
    // Stiffness values for each constraint (size: num_c)
    std::vector<float> k;

    // Node indices associated with each constraint (size: num_c * N)
    std::vector<int> ids;

    // Forces applied to each node under each constraint (size: num_c * N)
    std::vector<Eigen::Vector3f> f;

    // Jacobian matrices with respect to positions (size: num_c * N * N)
    // TODO: constraints are most likely symmetric, we could optimize this code
    std::vector<Eigen::Matrix3f> dfdx;

    // Jacobian matrices with respect to velocities (size: num_c * N * N)
    // TODO: constraints are most likely symmetric, we could optimize this code
    std::vector<Eigen::Matrix3f> dfdv;
};

// Structure to hold data related to constraints in a simulation.
// @tparam N Number of nodes.
// Stiffness values (k) for each constraint (size: C)
// Node indices (ids) associated with each constraint (size: C * N)
// Forces (f) applied to each node under each constraint (size: C * N)
// Jacobian (dfdx) matrices with respect to positions (size: C * N * N)
// Jacobian (dfdv) matrices with respect to velocities (size: C * N * N)
template<size_t N>
struct ConstraintData : public ConstraintDataBase
{
    ConstraintData(size_t numConstraints);
    
    size_t size() const override;
    
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~ConstraintData() = default;
};

#endif /* ConstraintData_hpp */
