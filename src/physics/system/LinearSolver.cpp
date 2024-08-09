#include "LinearSolver.hpp"


Eigen::VectorXd LinearSolver::solve(Assembly& assembly)
{
    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.compute(assembly.A());
    if (solver.info() != Eigen::Success) {
        throw std::runtime_error("Matrix decomposition failed");
    }
    return solver.solve(assembly.b());
}

