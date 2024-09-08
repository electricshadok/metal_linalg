#include "DistanceConstraint.hpp"

#include <stdexcept>

AnchorDistanceConstraint::AnchorDistanceConstraint(size_t numConstraints)
    : ConstraintData<1>(numConstraints),
      anchors(numConstraints),
      rest(numConstraints)
{
}

void AnchorDistanceConstraint::setupConstraint(const ObjectData& objData, float stiffness)
{
    // TODO - add AnchorDistanceConstraint::setupConstraint implementation
}

void AnchorDistanceConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - add AnchorDistanceConstraint::updateDerivatives implementation
}

DistanceConstraint::DistanceConstraint(size_t numConstraints)
    : ConstraintData<2>(numConstraints),
      rest(numConstraints)
{
}

void DistanceConstraint::setupConstraint(const ObjectData& objData, float stiffness)
{
    // Raise an error if the number of edges in objData doesn't match the number of constraints
    if (objData.edge.idx.size() != k.size()) {
        throw std::runtime_error("Mismatch between number of edges in ObjectData and the size of the constraint.");
    }

    // Fill the stiffness vector
    std::fill(k.begin(), k.end(), stiffness);

    // Fill the forces and jacobians
    std::fill(f.begin(), f.end(), Eigen::Vector3f::Zero());
    std::fill(dxdf.begin(), dxdf.end(), Eigen::Matrix3f::Zero());
    std::fill(dvdf.begin(), dvdf.end(), Eigen::Matrix3f::Zero());

    // Set up the node indices
    size_t numEdges = objData.edge.idx.size();
    for (size_t i = 0; i < numEdges; ++i)
    {
        const Edge& edge = objData.edge.idx[i];
        
        // Set node indices
        // TODO: add helper function in ConstraintData<2>
        ids[i * 2] = edge[0];
        ids[i * 2 + 1] = edge[1];
        
        // Calculate the norm (rest length) for the edge
        Eigen::Vector3f p1 = objData.nodes.p[edge[0]];
        Eigen::Vector3f p2 = objData.nodes.p[edge[1]];
        rest[i] = (p1 - p2).norm();
    }
}

void DistanceConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - implement DistanceConstraint::updateDerivatives

    // Fill the forces and jacobians
    std::fill(f.begin(), f.end(), Eigen::Vector3f::Zero());
    std::fill(dxdf.begin(), dxdf.end(), Eigen::Matrix3f::Zero());
    std::fill(dvdf.begin(), dvdf.end(), Eigen::Matrix3f::Zero());
    
    // Set the forces (f)
    
    // Set the jacobians (dfdx, dfdv)
}

