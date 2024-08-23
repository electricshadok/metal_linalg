#include "CubeMesh.hpp"
#include "physics/Common.hpp"

CubeMesh::CubeMesh() : ObjectData(8,0,12,0)
{
    // TODO: delete CubeMesh to be replaced with LatticeMesh(1,1,1)
    initializeNodes();
    initializeTriangles();
    initializeEdgesFromTriangles();
}

void CubeMesh::initializeNodes()
{
    static const Position verticesData[] = {
        // Front
        {-1,  1,  1},
        { 1,  1,  1},
        {-1, -1,  1},
        { 1, -1,  1},
        // Back
        {-1,  1, -1},
        { 1,  1, -1},
        {-1, -1, -1},
        { 1, -1, -1},
    };

    for (size_t i = 0; i < 8; ++i) {
        nodes.p[i] = verticesData[i];
        nodes.vel[i].setZero();
        nodes.acc[i].setZero();
        nodes.f[i].setZero();
        nodes.m[i] = 0.1f; // TODO: set mass on object level
    }
}

void CubeMesh::initializeTriangles()
{
    static const uint16_t indices[] = {
        // Front
        0, 1, 2, 2, 1, 3,
        // Back
        4, 5, 6, 6, 5, 7,
        // Left
        0, 2, 4, 4, 2, 6,
        // Right
        1, 3, 5, 5, 3, 7,
        // Top
        0, 1, 4, 4, 1, 5,
        // Bottom
        2, 3, 6, 6, 3, 7,
    };

    for (size_t i = 0; i < 12; ++i) {
        tri.idx[i] = Triangle(indices[i * 3], indices[i * 3 + 1], indices[i * 3 + 2]);
    }
}
