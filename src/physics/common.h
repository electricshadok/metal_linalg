#ifndef common_h
#define common_h

// Nodes
using Position = Eigen::Vector3f;
using Velocity = Eigen::Vector3f;
using Acceleration = Eigen::Vector3f;
using Force = Eigen::Vector3f;
using Mass = float;

using PositionList = std::vector<Position, Eigen::aligned_allocator<Position>>;
using VelocityList = std::vector<Velocity, Eigen::aligned_allocator<Velocity>>;
using AccelerationList = std::vector<Acceleration, Eigen::aligned_allocator<Acceleration>>;
using ForceList = std::vector<Force, Eigen::aligned_allocator<Force>>;
using MassList = std::vector<Mass>;

// Connectivities
using Triangle = Eigen::Vector3i;
using TriangleList = std::vector<Triangle, Eigen::aligned_allocator<Triangle>>;

#endif /* common_h */
