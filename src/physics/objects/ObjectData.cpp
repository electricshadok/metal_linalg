#include "ObjectData.hpp"
#include <unordered_set>

Nodes::Nodes(size_t size) : x(size), v(size), a(size), f(size), m(size)
{}

size_t Nodes::numNodes() const
{
    return x.size();
}

void Nodes::append(const Nodes& other) {
    x.insert(x.end(), other.x.begin(), other.x.end());
    v.insert(v.end(), other.v.begin(), other.v.end());
    a.insert(a.end(), other.a.begin(), other.a.end());
    f.insert(f.end(), other.f.begin(), other.f.end());
    m.insert(m.end(), other.m.begin(), other.m.end());
}

EdgeConnectivity::EdgeConnectivity(size_t edgeCount) : idx(edgeCount)
{}

size_t EdgeConnectivity::numEdges() const
{
    return idx.size();
}

void EdgeConnectivity::append(const EdgeConnectivity& other, size_t vertexOffset)
{
    for (const auto& edge : other.idx)
    {
        idx.emplace_back(edge + Edge((int)vertexOffset, (int)vertexOffset));
    }
}

TriangleConnectivity::TriangleConnectivity(size_t triangleCount) : idx(triangleCount)
{}

size_t TriangleConnectivity::numTriangles() const
{
    return idx.size();
}

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

size_t TetConnectivity::numTets() const
{
    return idx.size();
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
    std::unordered_set<Triangle, CustomHash, CustomEqual> triangleSet;

    for (const auto& tet : tet.idx)
    {
        Triangle t1(tet[0], tet[1], tet[2]);
        Triangle t2(tet[0], tet[1], tet[3]);
        Triangle t3(tet[0], tet[2], tet[3]);
        Triangle t4(tet[1], tet[2], tet[3]);

        triangleSet.insert(t1);
        triangleSet.insert(t2);
        triangleSet.insert(t3);
        triangleSet.insert(t4);
    }

    tri.idx.clear();
    tri.idx.reserve(triangleSet.size());
    tri.idx.insert(tri.idx.end(), triangleSet.begin(), triangleSet.end());
}

void ObjectData::initializeEdgesFromTets()
{
    std::unordered_set<Edge, CustomHash, CustomEqual> edgeSet;

    for (const auto& tet : tet.idx)
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = i + 1; j < 4; ++j)
            {
                Edge edge(tet[i], tet[j]);
                edgeSet.insert(edge);
            }
        }
    }

    edge.idx.clear();
    edge.idx.reserve(edgeSet.size());
    edge.idx.insert(edge.idx.end(), edgeSet.begin(), edgeSet.end());
}

void ObjectData::initializeEdgesFromTriangles()
{
    std::unordered_set<Edge, CustomHash, CustomEqual> edgeSet;
    for (const auto& tri : tri.idx)
    {
        for (int i = 0; i < 3; ++i)
        {
            Edge edge(tri[i], tri[(i + 1) % 3]);
            edgeSet.insert(edge);
        }
    }

    edge.idx.clear();
    edge.idx.reserve(edgeSet.size());
    edge.idx.insert(edge.idx.end(), edgeSet.begin(), edgeSet.end());
}

size_t ObjectData::numNodes() const
{
    return nodes.numNodes();
}

size_t ObjectData::numTets() const
{
    return tet.numTets();
}
size_t ObjectData::numTriangles() const
{
    return tri.numTriangles();
}

size_t ObjectData::numEdges() const
{
    return edge.numEdges();
}
