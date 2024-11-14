#include "DistanceConstraint.hpp"

#include <stdexcept>

const float EPSILON = 1e-6f;

AnchorDistanceConstraint::AnchorDistanceConstraint(size_t numConstraints)
    : ConstraintData<1>(numConstraints),
      anchors(numConstraints),
      rest(numConstraints)
{
}

void AnchorDistanceConstraint::setupZeroAnchor(size_t anchorId, const ObjectData& objData, int nodeId)
{
    // Set the anchor position and node ids
    const V3f& nodePos = objData.nodes.x[nodeId];
    anchors[anchorId] = nodePos;
    ids(anchorId)[0] = nodeId;
    rest[anchorId] = 0;
}

void AnchorDistanceConstraint::setupAnchor(size_t anchorId, const V3f& anchorPos, const ObjectData& objData, int nodeId)
{
    // Set the anchor position and node ids
    anchors[anchorId] = anchorPos;
    ids(anchorId)[0] = nodeId;
    
    // Get node id
    const V3f& nodePos = objData.nodes.x[nodeId];
    rest[anchorId] = (anchorPos - nodePos).norm();
}

V3f& AnchorDistanceConstraint::anchor(size_t anchorId)
{
    return anchors[anchorId];
}

void AnchorDistanceConstraint::setupConstraint(float stiffness, float damping)
{
    setProperties(stiffness, damping);
}

void AnchorDistanceConstraint::updateDerivatives(const ObjectData& objData)
{
    // Fill the forces and jacobians
    resetDerivatives();
    
    // Set the forces (f)
    for (size_t c = 0; c < numConstraints(); ++c)
    {
        int* ids_c = ids(c);
        V3f* f_c = f(c);
        
        const V3f& xi = objData.nodes.x[ids_c[0]];
        const V3f& xj = anchors[c];
        
        V3f x_ij = xi - xj;
        const float norm_x_ij = x_ij.norm();
        
        if (norm_x_ij < EPSILON)
        {
            continue;
        }
        
        x_ij /= norm_x_ij;

        f_c[0] =  x_ij * -k(c) * (norm_x_ij - rest[c]);
        
        // TODO: implement damping force for DistanceConstraint
    }
    
    // Set the jacobians (dfdx, dfdv)
    for (size_t c = 0; c < numConstraints(); ++c)
    {
        int* ids_c = ids(c);
        M33f* dfdx_c = dfdx(c);
        
        const V3f& xi = objData.nodes.x[ids_c[0]];
        const V3f& xj = anchors[c];
        
        V3f x_ij = xi - xj;
        const float norm_x_ij = x_ij.norm();
        
        if (norm_x_ij < EPSILON)
        {
            continue;
        }

        x_ij /= norm_x_ij;
        
        // -k . [(1 - rest / |x_ij|)(I - x_ij * x_ij^T) + (x_ij * x_ij^T)]
        M33f I = M33f::Identity();
        M33f outer = x_ij * x_ij.transpose();
        M33f dfdx_v = (I - outer) * (1.0 - rest[c] / norm_x_ij) + outer;
        dfdx_c[0] = -k(c) * dfdx_v;
        
        // TODO: implement damping force for DistanceConstraint
    }
    
}

DistanceConstraint::DistanceConstraint(size_t numConstraints)
    : ConstraintData<2>(numConstraints),
      rest(numConstraints)
{
}

void DistanceConstraint::setupConstraint(const ObjectData& objData, float stiffness, float damping)
{
    // Raise an error if the number of edges in objData doesn't match the number of constraints
    if (objData.edge.idx.size() != numConstraints()) {
        throw std::runtime_error("Mismatch between number of edges in ObjectData and the size of the constraint.");
    }

    // Fill the stiffness and damping vector
    setProperties(stiffness, damping);

    // Set up the node indices
    size_t numEdges = objData.edge.idx.size();
    for (size_t c = 0; c < numEdges; ++c)
    {
        const Edge& edge = objData.edge.idx[c];
        
        // Set node indices
        int* edgeIds = ids(c);
        edgeIds[0] = edge[0];
        edgeIds[1] = edge[1];

        // Calculate the norm (rest length) for the edge
        const V3f& xi = objData.nodes.x[edgeIds[0]];
        const V3f& xj = objData.nodes.x[edgeIds[1]];
        rest[c] = (xi - xj).norm();
    }
}

void DistanceConstraint::updateDerivatives(const ObjectData& objData)
{
    // Fill the forces and jacobians
    resetDerivatives();
    
    // Set the forces (f)
    for (size_t c = 0; c < numConstraints(); ++c)
    {
        int* ids_c = ids(c);
        V3f* f_c = f(c);
        
        const V3f& xi = objData.nodes.x[ids_c[0]];
        const V3f& xj = objData.nodes.x[ids_c[1]];
        V3f x_ij = xi - xj;
        const float norm_x_ij = x_ij.norm();
        x_ij /= norm_x_ij;

        f_c[0] =  x_ij * -k(c) * (norm_x_ij - rest[c]);
        f_c[1] = -f_c[0];
        
        // TODO: implement damping force for DistanceConstraint
    }
    
    // Set the jacobians (dfdx, dfdv)
    for (size_t c = 0; c < numConstraints(); ++c)
    {
        int* ids_c = ids(c);
        M33f* dfdx_c = dfdx(c);
        
        const V3f& xi = objData.nodes.x[ids_c[0]];
        const V3f& xj = objData.nodes.x[ids_c[1]];
        V3f x_ij = xi - xj;
        const float norm_x_ij = x_ij.norm();
        x_ij /= norm_x_ij;

        // -k . [(1 - rest / |x_ij|)(I - x_ij * x_ij^T) + (x_ij * x_ij^T)]
        M33f I = M33f::Identity();
        M33f outer = x_ij * x_ij.transpose();
        M33f dfdx_v = (I - outer) * (1.0 - rest[c] / norm_x_ij) + outer;
        dfdx_v =  dfdx_v * -k(c);
        
        dfdx_c[0] = dfdx_v;
        dfdx_c[1] = -dfdx_v;
        dfdx_c[2] = -dfdx_v;
        dfdx_c[3] = dfdx_v;

        // TODO: implement damping jacobian for DistanceConstraint
    }

}

