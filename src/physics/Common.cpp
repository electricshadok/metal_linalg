#include "Common.hpp"
#include <set>

std::size_t CustomHash::operator()(const Edge& edge) const
{
    // Ensure the hash is the same for Edge(0, 1) and Edge(1, 0)
    int v1 = std::min(edge[0], edge[1]);
    int v2 = std::max(edge[0], edge[1]);
    return std::hash<int>()(v1) ^ (std::hash<int>()(v2) << 1);
}

std::size_t CustomHash::operator()(const Triangle& tri) const
{
    // Sort the vertices to ensure the hash is order-independent
    std::array<int, 3> idx = {tri[0], tri[1], tri[2]};
    std::sort(idx.begin(), idx.end());

    // Combine the hashes of the sorted vertices
    std::size_t v1 = std::hash<int>()(idx[0]);
    std::size_t v2 = std::hash<int>()(idx[1]);
    std::size_t v3 = std::hash<int>()(idx[2]);
    return v1 ^ (v2 << 1) ^ (v3 << 2);
}

std::size_t CustomHash::operator()(const Tet& tet) const
{
    // Sort the vertices to ensure the hash is order-independent
    std::array<int, 4> idx = {tet[0], tet[1], tet[2], tet[3]};
    std::sort(idx.begin(), idx.end());

    // Combine the hashes of the sorted vertices
    std::size_t v1 = std::hash<int>()(idx[0]);
    std::size_t v2 = std::hash<int>()(idx[1]);
    std::size_t v3 = std::hash<int>()(idx[2]);
    std::size_t v4 = std::hash<int>()(idx[3]);
    return v1 ^ (v2 << 1) ^ (v3 << 2) ^ (v4 << 3);
}

bool CustomEqual::operator()(const Edge& lhs, const Edge& rhs) const
{
    return (lhs[0] == rhs[0] && lhs[1] == rhs[1]) ||
           (lhs[0] == rhs[1] && lhs[1] == rhs[0]);}

bool CustomEqual::operator()(const Triangle& lhs, const Triangle& rhs) const
{
    return std::set<int>({lhs[0], lhs[1], lhs[2]}) == std::set<int>({rhs[0], rhs[1], rhs[2]});
}

bool CustomEqual::operator()(const Tet& lhs, const Tet& rhs) const
{
    return std::set<int>({lhs[0], lhs[1], lhs[2], lhs[3]}) == std::set<int>({rhs[0], rhs[1], rhs[2], rhs[3]});
}
