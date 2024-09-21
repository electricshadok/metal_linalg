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

    // Set up the node indices
    size_t numEdges = objData.edge.idx.size();
    for (size_t c = 0; c < numEdges; ++c)
    {
        const Edge& edge = objData.edge.idx[c];
        
        // Set node indices
        // TODO: add helper function in ConstraintData<2>
        const size_t i = c * 2;
        const size_t j = i + 1;
        ids[i] = edge[0];
        ids[j] = edge[1];

        // Calculate the norm (rest length) for the edge
        const V3f& xi = objData.nodes.p[ids[i]];
        const V3f& xj = objData.nodes.p[ids[j]];
        rest[c] = (xi - xj).norm();
    }
}

void DistanceConstraint::updateDerivatives(const ObjectData& objData)
{
    // Fill the forces and jacobians
    std::fill(f.begin(), f.end(), V3f::Zero());
    std::fill(dfdx.begin(), dfdx.end(), M33f::Zero());
    std::fill(dfdv.begin(), dfdv.end(), M33f::Zero());
    
    // Set the forces (f)
    for (size_t c = 0; c < numConstraints(); ++c)
    {
        const size_t i = c * 2;
        const size_t j = i + 1;
        const V3f& xi = objData.nodes.p[ids[i]];
        const V3f& xj = objData.nodes.p[ids[j]];
        V3f x_ij = xi - xj;
        const float r = x_ij.norm();
        x_ij /= r;
        f[i] =  x_ij * -k[c] * (r - rest[c]);
        f[j] = f[i] * -1;
    }
    
    // Set the jacobians (dfdx, dfdv)
    // TODO - implement DistanceConstraint::updateDerivatives
}

