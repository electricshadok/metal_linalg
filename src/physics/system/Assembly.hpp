#ifndef Assembly_hpp
#define Assembly_hpp

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <vector>

class Assembly
{
public:
    Assembly(size_t numNodes);

    // Methods to add contributions to A and b
    void addToMatrix(const Eigen::Matrix3d& subMatrix, size_t row, size_t col);
    void addToVector(const Eigen::Vector3d& subVector, size_t row);

    // Getter methods for accessing A and b
    const Eigen::SparseMatrix<double>& A() const {return _A;}
    const Eigen::VectorXd& b() const {return _b;}
    
private:
    size_t size; // size = numNodes*3
    Eigen::SparseMatrix<double> _A;
    Eigen::VectorXd _b;
};


#endif /* Assembly_hpp */
