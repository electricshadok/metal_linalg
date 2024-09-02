#include "VolumeConstraint.hpp"

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
    std::fill(dxdf.begin(), dxdf.end(), Eigen::Matrix3f::Zero());
    std::fill(dvdf.begin(), dvdf.end(), Eigen::Matrix3f::Zero());

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
        
        // TODO - Calculate the tetrahedron volume (add in geometry lib)
        float volume = 1.0f;
        rest[i] = volume;
    }
}

void VolumeConstraint::updateDerivatives(const ObjectData& objData)
{
    // TODO - implement VolumeConstraint::updateDerivatives

    // Set the forces (f)
    
    // Set the jacobians (dfdx, dfdv)
}
