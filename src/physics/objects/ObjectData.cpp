#include "ObjectData.hpp"

ObjectData::ObjectData(size_t nodeCount, size_t triangleCount)
    : nodes(nodeCount), connectivity(triangleCount)
{
}

