#include "VolumeConstraint.hpp"

#include "geometry/Geometry.hpp"

VolumeConstraint::VolumeConstraint(size_t numConstraints)
    : ConstraintData<4>(numConstraints),
      rest(numConstraints)
{
}

void VolumeConstraint::setupConstraint(const ObjectData& objData, float stiffness)
{
    // Raise an error if the number of edges in objData doesn't match the number of constraints
    if (objData.tet.idx.size() != k.size()) {
        throw std::runtime_error("Mismatch between number of tetrahedra in ObjectData and the size of the constraint.");
    }

    // Fill the stiffness vector
    std::fill(k.begin(), k.end(), stiffness);

    // Fill the forces and jacobians
    std::fill(f.begin(), f.end(), Eigen::Vector3f::Zero());
    std::fill(dfdx.begin(), dfdx.end(), Eigen::Matrix3f::Zero());
    std::fill(dfdv.begin(), dfdv.end(), Eigen::Matrix3f::Zero());

    // Set up the node indices
    size_t numTets = objData.tet.idx.size();
    for (size_t i = 0; i < numTets; ++i)
    {
        const Tet& tet = objData.tet.idx[i];

        // Set node indices
        // TODO: add helper function in ConstraintData<4>
        ids[i * 4] = tet[0];
        ids[i * 4 + 1] = tet[1];
        ids[i * 4 + 2] = tet[2];
        ids[i * 4 + 3] = tet[3];

        const Eigen::Vector3f& x0 = objData.nodes.p[tet[0]];
        const Eigen::Vector3f& x1 = objData.nodes.p[tet[1]];
        const Eigen::Vector3f& x2 = objData.nodes.p[tet[2]];
        const Eigen::Vector3f& x3 = objData.nodes.p[tet[3]];

        const float volume = Geometry::volume(x0,x1,x2,x3);
        rest[i] = volume;
    }
}

void VolumeConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - implement VolumeConstraint::updateDerivatives

    // Set the forces (f)
    
    // Set the jacobians (dfdx, dfdv)
}
