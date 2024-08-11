#include "LinearSolvers.hpp"


Eigen::VectorXf LUSolver::solve(Assembly& assembly)
{
    Eigen::SparseLU<Eigen::SparseMatrix<float>> solver;
    solver.compute(assembly.A());
    if (solver.info() != Eigen::Success) {
        throw std::runtime_error("Matrix decomposition failed");
    }
    return solver.solve(assembly.b());
}

CGSolver::CGSolver(bool usePreconditioner)
    : usePreconditioner(usePreconditioner) {}

Eigen::VectorXf CGSolver::solve(Assembly& assembly)
{
    if (usePreconditioner) {
        Eigen::ConjugateGradient<Eigen::SparseMatrix<float>, Eigen::Lower | Eigen::Upper, Eigen::DiagonalPreconditioner<float>> solver;
        solver.compute(assembly.A());
        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("CG decomposition failed with preconditioner");
        }
        return solver.solve(assembly.b());
    } else {
        Eigen::ConjugateGradient<Eigen::SparseMatrix<float>, Eigen::Lower | Eigen::Upper> solver;
        solver.compute(assembly.A());
        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("CG decomposition failed");
        }
        return solver.solve(assembly.b());
    }
}
