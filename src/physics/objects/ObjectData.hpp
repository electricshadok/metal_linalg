#ifndef ObjectData_hpp
#define ObjectData_hpp

#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <vector>
#include "common.h"

struct Nodes
{
    Nodes(size_t size);
    
    size_t numNodes() const {
        return p.size();
    }
    
    void append(const Nodes& other);
    
    // Node attributes
    PositionList p;
    VelocityList vel;
    AccelerationList acc;
    ForceList f;
    MassList m;
};

struct TriangleConnectivity
{
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
