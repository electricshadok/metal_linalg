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

    Nodes(size_t size);
    
    size_t numNodes() const {
        return vtx.size();
    }
    
    void append(const Nodes& other);
    
    // Node attributes
    VertexList vtx;
    VelocityList vel;
    AccelerationList acc;
    MassList m;
};

struct TriangleConnectivity
{
    // Type alias for easier usage
    using Triangle = Eigen::Vector3i;
    using TriangleList = std::vector<Triangle, Eigen::aligned_allocator<Triangle>>;

    TriangleConnectivity(size_t triangleCount);
    
    void append(const TriangleConnectivity& other, size_t vertexOffset);
    
    // Triangle attributes
    TriangleList triangles;
};

struct ObjectData
{
    ObjectData(size_t nodeCount, size_t triangleCount);

    size_t numNodes() const {
        return nodes.numNodes();
    }

    void append(const ObjectData& other);
    
    // Object attributes
    Nodes nodes;
    TriangleConnectivity connectivity;
};


#endif /* ObjectData_hpp */
