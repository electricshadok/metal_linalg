#include "AreaConstraint.hpp"

#include "geometry/Geometry.hpp"

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
    std::fill(dfdx.begin(), dfdx.end(), Eigen::Matrix3f::Zero());
    std::fill(dfdv.begin(), dfdv.end(), Eigen::Matrix3f::Zero());

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

        const Eigen::Vector3f& x0 = objData.nodes.p[tri[0]];
        const Eigen::Vector3f& x1 = objData.nodes.p[tri[1]];
        const Eigen::Vector3f& x2 = objData.nodes.p[tri[2]];

        const float area = Geometry::area(x0, x1, x2);
        rest[i] = area;
    }
}

void AreaConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - implement AreaConstraint::updateDerivatives

    // Set the forces (f)
    
    // Set the jacobians (dfdx, dfdv)
}
