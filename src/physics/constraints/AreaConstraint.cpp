#include "AreaConstraint.hpp"

AreaConstraint::AreaConstraint(size_t numConstraints)
    : ConstraintData<3>(numConstraints),
      rest(numConstraints)
{
}

void AreaConstraint::setupConstraint(const ObjectData& objData, float stiffness)
{
    // Raise an error if the number of edges in objData doesn't match the number of constraints
    if (objData.tri.idx.size() != k.size()) {
        throw std::runtime_error("Mismatch between number of triangles in ObjectData and the size of the constraint.");
    }

    // Fill the stiffness vector
    std::fill(k.begin(), k.end(), stiffness);

    // Fill the forces and jacobians
    std::fill(f.begin(), f.end(), Eigen::Vector3f::Zero());
    std::fill(dxdf.begin(), dxdf.end(), Eigen::Matrix3f::Zero());
    std::fill(dvdf.begin(), dvdf.end(), Eigen::Matrix3f::Zero());

    // Set up the node indices
    size_t numTriangles = objData.tri.idx.size();
    for (size_t i = 0; i < numTriangles; ++i)
    {
        const Triangle& tri = objData.tri.idx[i];
        
        // Set node indices
        // TODO: add helper function in ConstraintData<3>
        ids[i * 3] = tri[0];
        ids[i * 3 + 1] = tri[1];
        ids[i * 3 + 2] = tri[2];
        
        // TODO - Calculate the triangle area (add in geometry lib)
        float area = 1.0f;
        rest[i] = area;
    }
}

void AreaConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - implement AreaConstraint::updateDerivatives

    // Set the forces (f)
    
    // Set the jacobians (dfdx, dfdv)
}
