#include "ObjectData.hpp"


Nodes::Nodes(size_t size) : vtx(size), vel(size), acc(size), m(size)
{}

void Nodes::append(const Nodes& other) {
    vtx.insert(vtx.end(), other.vtx.begin(), other.vtx.end());
    vel.insert(vel.end(), other.vel.begin(), other.vel.end());
    acc.insert(acc.end(), other.acc.begin(), other.acc.end());
    m.insert(m.end(), other.m.begin(), other.m.end());
}

TriangleConnectivity::TriangleConnectivity(size_t triangleCount) : triangles(triangleCount) 
{}

void TriangleConnectivity::append(const TriangleConnectivity& other, size_t vertexOffset) {
    for (const auto& tri : other.triangles) {
        triangles.emplace_back(tri + Triangle((int)vertexOffset,
                                              (int)vertexOffset,
                                              (int)vertexOffset));
    }
}

ObjectData::ObjectData(size_t nodeCount, size_t triangleCount)
    : nodes(nodeCount), connectivity(triangleCount)
{
}

void ObjectData::append(const ObjectData& other) {
    size_t vertexOffset = nodes.numNodes();
    nodes.append(other.nodes);
    connectivity.append(other.connectivity, vertexOffset);
}

