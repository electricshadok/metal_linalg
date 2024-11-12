#include "VolumeConstraint.hpp"

#include "geometry/Geometry.hpp"

VolumeConstraint::VolumeConstraint(size_t numConstraints)
    : ConstraintData<4>(numConstraints),
      rest(numConstraints)
{
}

void VolumeConstraint::setupConstraint(const ObjectData& objData, float stiffness, float damping)
{
    // Raise an error if the number of edges in objData doesn't match the number of constraints
    if (objData.tet.idx.size() != k.size()) {
        throw std::runtime_error("Mismatch between number of tetrahedra in ObjectData and the size of the constraint.");
    }

    // Fill the stiffness vector
    std::fill(k.begin(), k.end(), stiffness);
    std::fill(kd.begin(), kd.end(), damping);

    // Set up the node indices
    size_t numTets = objData.tet.idx.size();
    for (size_t i = 0; i < numTets; ++i)
    {
        const Tet& tet = objData.tet.idx[i];

        // Set node indices
        int* tetIds = ids(i);
        tetIds[0] = tet[0];
        tetIds[1] = tet[1];
        tetIds[2] = tet[2];
        tetIds[3] = tet[3];

        const V3f& x0 = objData.nodes.x[tet[0]];
        const V3f& x1 = objData.nodes.x[tet[1]];
        const V3f& x2 = objData.nodes.x[tet[2]];
        const V3f& x3 = objData.nodes.x[tet[3]];

        const float volume = Geometry::volume(x0,x1,x2,x3);
        rest[i] = volume;
    }
}

void VolumeConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - implement VolumeConstraint::updateDerivatives

    // Reset the forces and jacobians
    std::fill(_f.begin(), _f.end(), V3f::Zero());
    std::fill(_dfdx.begin(), _dfdx.end(), M33f::Zero());
    std::fill(_dfdv.begin(), _dfdv.end(), M33f::Zero());
    
    // Set the forces (f)
    
    // Set the jacobians (dfdx, dfdv)
}
