#ifndef Assembly_hpp
#define Assembly_hpp

#include "physics/Common.hpp"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <vector>

class Assembly
{
public:
    Assembly(size_t numNodes);

    // Methods to add contributions to A and b
    void addToMatrix(const M33f& subMatrix, size_t row, size_t col);
    void addToVector(const V3f& subVector, size_t row);
    
    // Getter methods for accessing A and b
    const Eigen::SparseMatrix<float>& A() const {return _A;}
    const Eigen::VectorXf& b() const {return _b;}

    void setZero();
    
    // TODO: export system into a txt file for debugging

private:
    size_t size; // size = numNodes*3
    Eigen::SparseMatrix<float> _A;
    Eigen::VectorXf _b;
};


#endif /* Assembly_hpp */
