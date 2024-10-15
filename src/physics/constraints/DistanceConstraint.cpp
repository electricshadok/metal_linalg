#include "DistanceConstraint.hpp"

#include <stdexcept>

AnchorDistanceConstraint::AnchorDistanceConstraint(size_t numConstraints)
    : ConstraintData<1>(numConstraints),
      anchors(numConstraints),
      nodeIds(numConstraints),
      rest(numConstraints)
{
}

void AnchorDistanceConstraint::setupZeroAnchor(size_t anchorId, const ObjectData& objData, size_t nodeId)
{
    // Set the anchor position and node ids
    const V3f& nodePos = objData.nodes.x[nodeId];
    anchors[anchorId] = nodePos;
    nodeIds[anchorId] = nodeId;
    rest[anchorId] = 0;
}

void AnchorDistanceConstraint::setupAnchor(size_t anchorId, const V3f& anchorPos, const ObjectData& objData, size_t nodeId)
{
    // Set the anchor position and node ids
    anchors[anchorId] = anchorPos;
    nodeIds[anchorId] = nodeId;
    
    // Get node id
    const V3f& nodePos = objData.nodes.x[nodeId];
    rest[anchorId] = (anchorPos - nodePos).norm();
}

V3f& AnchorDistanceConstraint::anchor(size_t anchorId)
{
    return anchors[anchorId];
}

void AnchorDistanceConstraint::setupConstraint(const ObjectData& objData, float stiffness, float damping)
{
    // TODO - add AnchorDistanceConstraint::setupConstraint implementation
}

void AnchorDistanceConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - add AnchorDistanceConstraint::updateDerivatives implementation
    
    // Fill the forces and jacobians
    std::fill(f.begin(), f.end(), V3f::Zero());
    std::fill(dfdx.begin(), dfdx.end(), M33f::Zero());
    std::fill(dfdv.begin(), dfdv.end(), M33f::Zero());
    
}

DistanceConstraint::DistanceConstraint(size_t numConstraints)
    : ConstraintData<2>(numConstraints),
      rest(numConstraints)
{
}

void DistanceConstraint::setupConstraint(const ObjectData& objData, float stiffness, float damping)
{
    // Raise an error if the number of edges in objData doesn't match the number of constraints
    if (objData.edge.idx.size() != k.size()) {
        throw std::runtime_error("Mismatch between number of edges in ObjectData and the size of the constraint.");
    }

    // Fill the stiffness and damping vector
    std::fill(k.begin(), k.end(), stiffness);
    std::fill(kd.begin(), kd.end(), damping);

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
        const V3f& xi = objData.nodes.x[ids[i]];
        const V3f& xj = objData.nodes.x[ids[j]];
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
        const V3f& xi = objData.nodes.x[ids[i]];
        const V3f& xj = objData.nodes.x[ids[j]];
        V3f x_ij = xi - xj;
        const float norm_x_ij = x_ij.norm();
        x_ij /= norm_x_ij;

        f[i] =  x_ij * -k[c] * (norm_x_ij - rest[c]);
        f[j] = -f[i];
        
        // TODO: implement damping force for DistanceConstraint
    }
    
    // Set the jacobians (dfdx, dfdv)
    for (size_t c = 0; c < numConstraints(); ++c)
    {
        const size_t i = c * 2;
        const size_t j = i + 1;
        const V3f& xi = objData.nodes.x[ids[i]];
        const V3f& xj = objData.nodes.x[ids[j]];
        V3f x_ij = xi - xj;
        const float norm_x_ij = x_ij.norm();
        x_ij /= norm_x_ij;

        // -k . [(1 - rest / |x_ij|)(I - x_ij * x_ij^T) + (x_ij * x_ij^T)]
        M33f I = M33f::Identity();
        M33f outer = x_ij * x_ij.transpose();
        M33f dfdx_c = (I - outer) * (1.0 - rest[c] / norm_x_ij) + outer;
        dfdx_c = -k[c] * dfdx_c;
        dfdx[i * 2 + 0] = dfdx_c;
        dfdx[i * 2 + 1] = -dfdx_c;
        dfdx[j * 2 + 0] = -dfdx_c;
        dfdx[j * 2 + 1] = dfdx_c;

        // TODO: implement damping jacobian for DistanceConstraint
    }

}

