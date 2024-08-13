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

CGSolver::CGSolver(PreconditionerType preconditioner)
    : preconditioner(preconditioner)
{}

Eigen::VectorXf CGSolver::solve(Assembly& assembly)
{
    switch (preconditioner)
    {
        case PreconditionerType::Diagonal:
        {
            Eigen::ConjugateGradient<Eigen::SparseMatrix<float>, Eigen::Lower | Eigen::Upper, Eigen::DiagonalPreconditioner<float>> solver;
            solver.compute(assembly.A());
            if (solver.info() != Eigen::Success) {
                throw std::runtime_error("CG failed with diagonal preconditioner");
            }
            return solver.solve(assembly.b());
        }
        case PreconditionerType::IncompleteLU: 
        {
            Eigen::ConjugateGradient<Eigen::SparseMatrix<float>, Eigen::Lower | Eigen::Upper, Eigen::IncompleteLUT<float>> solver;
            solver.compute(assembly.A());
            if (solver.info() != Eigen::Success) {
                throw std::runtime_error("CG failed with ILU preconditioner");
            }
            return solver.solve(assembly.b());
        }
        case PreconditionerType::SSOR:
        {
            throw std::runtime_error("SSOR preconditioner is not supported yet.");
        }
        case PreconditionerType::None:
        default: 
        {
            Eigen::ConjugateGradient<Eigen::SparseMatrix<float>, Eigen::Lower | Eigen::Upper> solver;
            solver.compute(assembly.A());
            if (solver.info() != Eigen::Success) {
                throw std::runtime_error("CG failed");
            }
            return solver.solve(assembly.b());
        }
    }
}
