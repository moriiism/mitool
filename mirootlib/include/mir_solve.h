#ifndef MORIIISM_MITOOL_MIROOTLIB_SOLVE_H_
#define MORIIISM_MITOOL_MIROOTLIB_SOLVE_H_

#include "mir_func.h"

namespace MirSolve
{
    
    double GetRootNewton(const MirFunc* const func, const double* const par_func,
                         const MirFunc* const func_prime, const double* const par_func_prime,
                         double root_init, double epsilon);

    // solve equation: f(x) = 0
    double GetRootSecant(const MirFunc* const func, const double* const par_func,
                         double root_init0, double root_init1, double epsilon);

    // solve equation: f(x) = constant
    double GetRootSecantEqC(const MirFunc* const func, const double* const par_func,
                            double root_init0, double root_init1, double constant, double epsilon);

    // solve equation: f(x) = 0
    double GetRootBisection(const MirFunc* const func, const double* const par_func,
                            double root_init0, double root_init1,
                            double epsilon);

    // solve equation: f(x) = constant
    double GetRootBisectionEqC(const MirFunc* const func, const double* const par_func,
                               double root_init0, double root_init1,
                               double constant, double epsilon);
    
} // namespace MirSolve


#endif // MORIIISM_MITOOL_MIROOTLIB_SOLVE_H_


