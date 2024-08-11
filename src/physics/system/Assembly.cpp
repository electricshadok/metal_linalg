#include "Assembly.hpp"

Assembly::Assembly(size_t numNodes) :
    size(numNodes*3),
    _A(numNodes*3, numNodes*3),
    _b(numNodes*3)
{
    _b.setZero();
}

void Assembly::addToMatrix(const Eigen::Matrix3f& subMatrix, size_t row, size_t col)
{
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (row + i < size && col + j < size) {
                _A.coeffRef(row + i, col + j) += subMatrix(i, j);
            }
        }
    }
}

void Assembly::addToVector(const Eigen::Vector3f& subVector, size_t row)
{
    for (size_t i = 0; i < 3; ++i) {
        if (row + i < size) {
            _b(row + i) += subVector(i);
        }
    }
}

void Assembly::setZero()
{
    _A.setZero();
    _b.setZero();
}
