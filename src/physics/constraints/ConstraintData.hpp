#ifndef ConstraintData_hpp
#define ConstraintData_hpp

#include <vector>
#include <Eigen/Dense>

// Structure to hold data related to constraints in a simulation.
// @tparam N Number of nodes.
// @tparam C Number of constraints.
template<size_t N>
struct ConstraintData
{
    ConstraintData(size_t c);
    
    // Stiffness values for each constraint (size: C)
    std::vector<float> k;

    // Node indices associated with each constraint (size: C * N)
    std::vector<int> ids;

    // Forces applied to each node under each constraint (size: C * N)
    std::vector<Eigen::Vector3f> f;

    // Jacobian matrices with respect to positions (size: C * N * N)
    std::vector<Eigen::Matrix3f> dxdf;

    // Jacobian matrices with respect to velocities (size: C * N * N)
    std::vector<Eigen::Matrix3f> dvdf;
};

#endif /* ConstraintData_hpp */
