#include "CubeMesh.hpp"
#include "physics/Common.hpp"

CubeMesh::CubeMesh() : ObjectData(8,6,12,0)
{
    initializeNodes();
    initializeTriangles();
    initializeTets();
    initializeEdgesFromTets();
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
        0, 1, 2, 2, 1, 3, // Front
        4, 5, 6, 6, 5, 7, // Back
        0, 2, 4, 4, 2, 6, // Left
        1, 3, 5, 5, 3, 7, // Right
        0, 1, 4, 4, 1, 5, // Top
        2, 3, 6, 6, 3, 7, // Bottom
    };

    for (size_t i = 0; i < 12; ++i) {
        tri.idx[i] = Triangle(indices[i * 3], indices[i * 3 + 1], indices[i * 3 + 2]);
    }
}

void CubeMesh::initializeTets()
{
    // TODO: try to visualize those Tets
    static const uint16_t indices[] = {
        0, 1, 2, 4, // front-bottom-left to back-top-right
        1, 3, 2, 4, // front-bottom-right to back-top-left)
        4, 5, 6, 0, // back-bottom-left to front-top-right
        5, 7, 6, 0, // back-bottom-right to front-top-left
        0, 1, 4, 5, // center front-face to opposite corner
        2, 3, 6, 7 // center back-face to opposite corner
    };

    for (size_t i = 0; i < 6; ++i) {
        tet.idx[i] = Tet(indices[i * 4], indices[i * 4 + 1], indices[i * 4 + 2], indices[i * 4 + 3]);
    }
}
