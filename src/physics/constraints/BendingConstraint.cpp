#include "BendingConstraint.hpp"

BendingConstraint::BendingConstraint(size_t numConstraints)
    : ConstraintData<4>(numConstraints),
      rest(numConstraints)
{
}

void BendingConstraint::setupConstraint(const ObjectData& objData, float stiffness, float damping)
{
    // TODO: implement function to get edges with 2 adjacent triangles
    // Raise an error if the number of edges in objData doesn't match the number of constraints
    // if (objData.edge.idx.size() != k.size()) {
    //    throw std::runtime_error("Mismatch between number of edges in ObjectData and the size of the constraint.");
    //}

    // Fill the stiffness vector
    setProperties(stiffness, damping);

    // TODO: Set up the node indices
}

void BendingConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - implement VolumeConstraint::updateDerivatives

    // Reset the forces and jacobians
    resetDerivatives();
    
    // Set the forces (f)
    
    // Set the jacobians (dfdx, dfdv)
}
