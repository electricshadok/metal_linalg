#include "DistanceConstraint.hpp"

AnchorDistanceConstraint::AnchorDistanceConstraint(size_t numConstraints)
    : ConstraintData<1>(numConstraints),
      anchors(numConstraints),
      rest(numConstraints)
{
    for (size_t i = 0; i < numConstraints; ++i) 
    {
        anchors[i] = Eigen::Vector3f::Zero();
        rest[i] = 1.0f;
    }
}

void AnchorDistanceConstraint::setupConstraint(const ObjectData& objData, float stiffness)
{
    // TODO - add AnchorDistanceConstraint::setupConstraint implementation
}

void AnchorDistanceConstraint::computeForces(const ObjectData& objData)
{
    // TODO - add AnchorDistanceConstraint::computeForces implementation
}

DistanceConstraint::DistanceConstraint(size_t numConstraints)
    : ConstraintData<2>(numConstraints),
      rest(numConstraints)
{
    for (size_t i = 0; i < numConstraints; ++i) 
    {
        rest[i] = 1.0f;
    }
}

void DistanceConstraint::setupConstraint(const ObjectData& objData, float stiffness)
{
    // TODO - add DistanceConstraint::setupConstraint
    size_t numEdges = objData.edge.idx.size();

    numEdges = numEdges;
}

void DistanceConstraint::computeForces(const ObjectData& objData)
{
    // TODO - add DistanceConstraint::computeForces
}

