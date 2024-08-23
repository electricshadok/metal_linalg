#include "ObjectData.hpp"
#include <unordered_set>

Nodes::Nodes(size_t size) : p(size), vel(size), acc(size), f(size), m(size)
{}

size_t Nodes::numNodes() const
{
    return p.size();
}

void Nodes::append(const Nodes& other) {
    p.insert(p.end(), other.p.begin(), other.p.end());
    vel.insert(vel.end(), other.vel.begin(), other.vel.end());
    acc.insert(acc.end(), other.acc.begin(), other.acc.end());
    f.insert(f.end(), other.f.begin(), other.f.end());
    m.insert(m.end(), other.m.begin(), other.m.end());
}

EdgeConnectivity::EdgeConnectivity(size_t edgeCount) : idx(edgeCount)
{}

void EdgeConnectivity::append(const EdgeConnectivity& other, size_t vertexOffset)
{
    for (const auto& edge : other.idx)
    {
        idx.emplace_back(edge + Edge((int)vertexOffset, (int)vertexOffset));
    }
}

TriangleConnectivity::TriangleConnectivity(size_t triangleCount) : idx(triangleCount)
{}

void TriangleConnectivity::append(const TriangleConnectivity& other, size_t vertexOffset)
{
    for (const auto& tri : other.idx)
    {
        idx.emplace_back(tri + Triangle((int)vertexOffset,
                                        (int)vertexOffset,
                                        (int)vertexOffset));
    }
}

TetConnectivity::TetConnectivity(size_t tetCount) : idx(tetCount)
{
}

void TetConnectivity::append(const TetConnectivity& other, size_t vertexOffset)
{
    for (const auto& tet : other.idx)
    {
        idx.emplace_back(tet + Tet((int)vertexOffset,
                                   (int)vertexOffset,
                                   (int)vertexOffset,
                                   (int)vertexOffset));
    }
}


ObjectData::ObjectData(size_t nodeCount, size_t tetCount, size_t triCount, size_t edgeCount)
    : nodes(nodeCount), tet(tetCount), tri(triCount), edge(edgeCount)
{
}

void ObjectData::append(const ObjectData& other)
{
    size_t vertexOffset = nodes.numNodes();
    nodes.append(other.nodes);
    tet.append(other.tet, vertexOffset);
    tri.append(other.tri, vertexOffset);
    edge.append(other.edge, vertexOffset);
}

void ObjectData::initializeTrianglesFromTets()
{
    // TODO: implement ObjectData::setTrianglesFromTets
}

void ObjectData::initializeEdgesFromTets()
{
    // TODO: implement ObjectData::setEdgesFromTets
}

void ObjectData::initializeEdgesFromTriangles()
{
    // TODO: implement ObjectData::setEdgesFromTriangles
    std::unordered_set<Edge, CustomHash, CustomEqual> edgeMap;
    Edge edge1(1,2);
    Edge edge2(1,2);
    edgeMap.insert(edge1);
    edgeMap.insert(edge2);
}

size_t ObjectData::numNodes() const
{
    return nodes.numNodes();
}
