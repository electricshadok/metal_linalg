#ifndef LinearSolver_hpp
#define LinearSolver_hpp

#include <Eigen/Dense>
#include "physics/system/Assembly.hpp"

/*
Linear solver to experiment with.

# Direct Solver #
- LU Solver
- QR Solver
 
# Iterative Solver #
- Conjugate Gradient (CG)

The following improvements and variations are commonly used with the Conjugate Gradient method:

1. Preconditioned Conjugate Gradient (PCG):
   - Preconditioners: Jacobi (Diagonal)
   - Incomplete LU (ILU)
   - Symmetric Successive Over-Relaxation (SSOR)

2. Solvers for Non-Symmetric Systems:
   - Conjugate Gradient Squared (CGS)
   - BiCGSTAB (Biconjugate Gradient Stabilized)
   - GMRES (Generalized Minimal Residual Method)

3. Stabilization and Truncation Techniques:
   - Truncated Conjugate Gradient (TCG)
*/

class LinearSolverBase
{
public:
    virtual ~LinearSolverBase() = default;
    virtual Eigen::VectorXf solve(Assembly& assembly) = 0;
};

class LUSolver : public LinearSolverBase
{
public:
    Eigen::VectorXf solve(Assembly& assembly) override;
};

enum class PreconditionerType {
    None,
    Diagonal,
    IncompleteLU,
    SSOR // Not implemented yet
};

class CGSolver : public LinearSolverBase
{
public:
    CGSolver(PreconditionerType preconditioner = PreconditionerType::None);

    Eigen::VectorXf solve(Assembly& assembly) override;

private:
    PreconditionerType preconditioner;
};


#endif /* LinearSolver_hpp */
