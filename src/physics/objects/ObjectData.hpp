#ifndef ObjectData_hpp
#define ObjectData_hpp

#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <vector>
#include "Common.h"

struct Nodes
{
    Nodes(size_t size);
    
    size_t numNodes() const;
    
    void append(const Nodes& other);
    
    PositionList p;
    VelocityList vel;
    AccelerationList acc;
    ForceList f;
    MassList m;
};

struct EdgeConnectivity
{
    EdgeConnectivity(size_t edgeCount);
    
    void append(const EdgeConnectivity& other, size_t vertexOffset);
    
    EdgeList idx;
};

struct TriangleConnectivity
{
    TriangleConnectivity(size_t triangleCount);
    
    void append(const TriangleConnectivity& other, size_t vertexOffset);
    
    TriangleList idx;
};

struct TetConnectivity
{
    TetConnectivity(size_t tetCount);
    
    void append(const TetConnectivity& other, size_t vertexOffset);
    
    TetList idx;
};

struct ObjectData
{
    ObjectData(size_t nodeCount, size_t tetCount, size_t triCount, size_t edgeCount);

    size_t numNodes() const;

    void append(const ObjectData& other);
    
    Nodes nodes;
    TetConnectivity tet;
    TriangleConnectivity tri;
    EdgeConnectivity edge;
};


#endif /* ObjectData_hpp */
