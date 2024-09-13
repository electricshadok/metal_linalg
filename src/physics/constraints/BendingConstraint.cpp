#include "BendingConstraint.hpp"

BendingConstraint::BendingConstraint(size_t numConstraints)
    : ConstraintData<4>(numConstraints),
      rest(numConstraints)
{
}

void BendingConstraint::setupConstraint(const ObjectData& objData, float stiffness)
{
    // TODO: implement function to get edges with 2 adjacent triangles
    // Raise an error if the number of edges in objData doesn't match the number of constraints
    // if (objData.edge.idx.size() != k.size()) {
    //    throw std::runtime_error("Mismatch between number of edges in ObjectData and the size of the constraint.");
    //}

    // Fill the stiffness vector
    std::fill(k.begin(), k.end(), stiffness);

    // Fill the forces and jacobians
    std::fill(f.begin(), f.end(), Eigen::Vector3f::Zero());
    std::fill(dfdx.begin(), dfdx.end(), Eigen::Matrix3f::Zero());
    std::fill(dfdv.begin(), dfdv.end(), Eigen::Matrix3f::Zero());

    // TODO: Set up the node indices
}

void BendingConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - implement VolumeConstraint::updateDerivatives

    // Set the forces (f)
    
    // Set the jacobians (dfdx, dfdv)
}
