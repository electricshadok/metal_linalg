#ifndef ObjectData_hpp
#define ObjectData_hpp

#include <vector>
#include "physics/Common.hpp"

struct Nodes
{
    Nodes(size_t size);
    
    size_t numNodes() const;
    
    void append(const Nodes& other);
    
    PositionList p; // TODO: rename to x
    VelocityList vel; // TODO: rename to v
    AccelerationList acc; // TODO: rename to a
    ForceList f;
    MassList m;
};

struct EdgeConnectivity
{
    EdgeConnectivity(size_t edgeCount);
    
    size_t numEdges() const;
    
    void append(const EdgeConnectivity& other, size_t vertexOffset);
    
    EdgeList idx;
};

struct TriangleConnectivity
{
    TriangleConnectivity(size_t triangleCount);
    
    size_t numTriangles() const;
    
    void append(const TriangleConnectivity& other, size_t vertexOffset);
    
    TriangleList idx;
};

struct TetConnectivity
{
    TetConnectivity(size_t tetCount);
    
    size_t numTets() const;
    
    void append(const TetConnectivity& other, size_t vertexOffset);
    
    TetList idx;
};

struct ObjectData
{
    ObjectData(size_t nodeCount, size_t tetCount, size_t triCount, size_t edgeCount);

    size_t numNodes() const;
    size_t numTets() const;
    size_t numTriangles() const;
    size_t numEdges() const;

    void append(const ObjectData& other);
    
    void initializeTrianglesFromTets();
    void initializeEdgesFromTets();
    void initializeEdgesFromTriangles();

    Nodes nodes;
    TetConnectivity tet;
    TriangleConnectivity tri;
    EdgeConnectivity edge;
};


#endif /* ObjectData_hpp */
