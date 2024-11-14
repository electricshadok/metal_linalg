#ifndef ConstraintData_hpp
#define ConstraintData_hpp

#include "physics/objects/ObjectData.hpp"
#include <vector>
#include "physics/Common.hpp"

// Base class for all ConstraintData
struct ConstraintDataBase
{
    ConstraintDataBase(size_t num_c, size_t size);
    
    size_t size() const {return _size;}
    
    float k(size_t idx) {return _k[idx];}
    float kd(size_t idx) {return _kd[idx];}
    int* ids(size_t idx) {return &_ids[idx * _size];}
    V3f* f(size_t idx) {return &_f[idx * _size];}
    M33f* dfdx(size_t idx) {return &_dfdx[idx * _size * _size];}
    M33f* dfdv(size_t idx) {return &_dfdv[idx * _size * _size];}
    
    // Compute forces and Jacobians
    virtual void updateDerivatives(const ObjectData& objData) = 0;
    
    // Return the number of constraints
    size_t numConstraints() const;
    
    // Set properties
    void setProperties(float stiffness, float damping);
    
    // Reset derivatives
    void resetDerivatives();
    
    // Stiffness values for each constraint (size: num_c)
    std::vector<float> _k;
    
    // Stiffness values for each constraint (size: num_c)
    std::vector<float> _kd;

    // Node indices associated with each constraint (size: num_c * N)
    std::vector<int> _ids;

    // Forces applied to each node under each constraint (size: num_c * N)
    std::vector<V3f> _f;
    
    // Constraint size
    size_t _size;

    // Jacobian matrices with respect to positions (size: num_c * N * N)
    // TODO: constraints are most likely symmetric, we could optimize this code
    std::vector<M33f> _dfdx;

    // Jacobian matrices with respect to velocities (size: num_c * N * N)
    // TODO: constraints are most likely symmetric, we could optimize this code
    std::vector<M33f> _dfdv;
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
    
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~ConstraintData() = default;
};

#endif /* ConstraintData_hpp */
