#include "AreaConstraint.hpp"

#include "geometry/Geometry.hpp"

AreaConstraint::AreaConstraint(size_t numConstraints)
    : ConstraintData<3>(numConstraints),
      rest(numConstraints)
{
}

void AreaConstraint::setupConstraint(const ObjectData& objData, float stiffness, float damping)
{
    // Raise an error if the number of edges in objData doesn't match the number of constraints
    if (objData.tri.idx.size() != numConstraints()) {
        throw std::runtime_error("Mismatch between number of triangles in ObjectData and the size of the constraint.");
    }

    // Fill the stiffness vector
    setProperties(stiffness, damping);

    // Set up the node indices
    size_t numTriangles = objData.tri.idx.size();
    for (size_t i = 0; i < numTriangles; ++i)
    {
        const Triangle& tri = objData.tri.idx[i];

        // Set node indices
        int* triIds = ids(i);
        triIds[0] = tri[0];
        triIds[1] = tri[1];
        triIds[2] = tri[2];

        const V3f& x0 = objData.nodes.x[tri[0]];
        const V3f& x1 = objData.nodes.x[tri[1]];
        const V3f& x2 = objData.nodes.x[tri[2]];

        const float area = Geometry::area(x0, x1, x2);
        rest[i] = area;
    }
}

void AreaConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - implement AreaConstraint::updateDerivatives

    // Reset the forces and jacobians
    resetDerivatives();
    
    // Set the forces (f)
    
    // Set the jacobians (dfdx, dfdv)
}
