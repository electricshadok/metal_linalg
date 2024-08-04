#ifndef ObjectData_hpp
#define ObjectData_hpp

#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <vector>

struct Nodes
{
    // Type alias for easier usage
    using Vertex = Eigen::Vector3f;
    using Velocity = Eigen::Vector3f;
    using Acceleration = Eigen::Vector3f;
    using Mass = float;
    using VertexList = std::vector<Vertex, Eigen::aligned_allocator<Vertex>>;
    using VelocityList = std::vector<Velocity, Eigen::aligned_allocator<Velocity>>;
    using AccelerationList = std::vector<Acceleration, Eigen::aligned_allocator<Acceleration>>;
    using MassList = std::vector<Mass>;

    // Node attributes
    VertexList vtx;
    VelocityList vel;
    AccelerationList acc;
    MassList m;

    // Constructor to initialize the mesh
    Nodes(size_t size) : vtx(size), vel(size), acc(size), m(size ){}
};

struct TriangleConnectivity
{
    // Type alias for easier usage
    using Triangle = Eigen::Vector3i;
    using TriangleList = std::vector<Triangle, Eigen::aligned_allocator<Triangle>>;

    TriangleList triangles;

    // Constructor to initialize the connectivites
    TriangleConnectivity(size_t triangleCount) : triangles(triangleCount) {}
};

class ObjectData
{
public:
    ObjectData(size_t nodeCount, size_t triangleCount);

    Nodes nodes;
    TriangleConnectivity connectivity;
};


#endif /* ObjectData_hpp */
