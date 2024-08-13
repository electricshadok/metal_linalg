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
using Edge = Eigen::Vector2i;
using EdgeList = std::vector<Edge, Eigen::aligned_allocator<Edge>>;
using Triangle = Eigen::Vector3i;
using TriangleList = std::vector<Triangle, Eigen::aligned_allocator<Triangle>>;
using Tet = Eigen::Vector4i;
using TetList = std::vector<Tet, Eigen::aligned_allocator<Tet>>;

#endif /* common_h */
