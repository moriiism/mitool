#include "mir_solve.h"

double MirSolve::GetRootNewton(const MirFunc* const func, const double* const par_func,
                               const MirFunc* const func_prime, const double* const par_func_prime,
                               double root_init)
{
    string func_name = "MirSolve::GetRootNewton()";
    int iterate = 0;
    double root = root_init;
    while(fabs(func->Eval1d(root, par_func)) > DBL_EPSILON){
        root = root - func->Eval1d(root, par_func) / func_prime->Eval1d(root, par_func_prime);
        iterate ++;
    }
    return root;
}



double MirSolve::GetRootSecant(const MirFunc* const func, const double* const par_func,
                               double root_init0, double root_init1)
{
    string func_name = "MirSolve::GetRootSecant()";
    int iterate = 0;
    double root = root_init0;
    double root_0 = root_init0;
    double root_1 = root_init1;
    while(fabs(func->Eval1d(root, par_func)) > DBL_EPSILON){
        double yval_0 = fabs(func->Eval1d(root_0, par_func));
        double yval_1 = fabs(func->Eval1d(root_1, par_func));
        root = (root_0 * yval_1 - root_1 * yval_0) / (yval_1 - yval_0);
        root_0 = root_1;
        root_1 = root;
        printf("%s: %d: root = %e\n", func_name.c_str(), iterate, root);
        iterate ++;
    }
    return root;
}


double MirSolve::GetRootSecantEqC(const MirFunc* const func, const double* const par_func,
                                  double root_init0, double root_init1, double constant)
{
    string func_name = "MirSolve::GetRootSecantEqC()";
    int iterate = 0;
    double root = root_init0;
    double root_0 = root_init0;
    double root_1 = root_init1;
    while(fabs(func->Eval1d(root, par_func) - constant) > DBL_EPSILON){
        double yval_0 = fabs(func->Eval1d(root_0, par_func) - constant);
        double yval_1 = fabs(func->Eval1d(root_1, par_func) - constant);
        root = (root_0 * yval_1 - root_1 * yval_0) / (yval_1 - yval_0);
        root_0 = root_1;
        root_1 = root;
        printf("%s: %d: root = %e\n", func_name.c_str(), iterate, root);
        iterate ++;
    }
    return root;
}


double MirSolve::GetRootSecantEqCEpsilon(const MirFunc* const func, const double* const par_func,
                                         double root_init0, double root_init1, double constant,
                                         double epsilon)
{
    string func_name = "MirSolve::GetRootSecantEqCEpsilon()";
    int iterate = 0;
    double root = root_init0;
    double root_0 = root_init0;
    double root_1 = root_init1;
    while(fabs(func->Eval1d(root, par_func) - constant) > epsilon){
        double yval_0 = fabs(func->Eval1d(root_0, par_func) - constant);
        double yval_1 = fabs(func->Eval1d(root_1, par_func) - constant);
        root = (root_0 * yval_1 - root_1 * yval_0) / (yval_1 - yval_0);
        root_0 = root_1;
        root_1 = root;
        iterate ++;
    }
    return root;
}

// bisection

double MirSolve::GetRootBisection(const MirFunc* const func, const double* const par_func,
                                  double root_init0, double root_init1,
                                  double epsilon)
{
    string func_name = "MirSolve::GetRootBisection()";
    int iterate = 0;

    double root_0 = root_init0;
    double root_1 = root_init1;
    double yval_0 = func->Eval1d(root_init0, par_func);
    double yval_1 = func->Eval1d(root_init1, par_func);
    if(yval_0 * yval_1 >= 0){
        printf("bad blacket\n");
        exit(1);
    }
    double root = (root_0 + root_1)/2.;
    double yval = func->Eval1d(root, par_func);
    while(fabs(yval) > epsilon){
        if(yval * yval_0 > 0){
            root_0 = (root_0 + root_1)/2.;
        } else {
            root_1 = (root_0 + root_1)/2.;
        }
        root = (root_0 + root_1)/2.;
        yval = func->Eval1d(root, par_func);
        iterate ++;
    }
    printf("%s: %d: root = %e\n", func_name.c_str(), iterate, root);
    return root;
}


double MirSolve::GetRootBisectionEqC(const MirFunc* const func, const double* const par_func,
                                     double root_init0, double root_init1,
                                     double constant, double epsilon)
{
    string func_name = "MirSolve::GetRootBisectionEqC()";
    int iterate = 0;

    double root_0 = root_init0;
    double root_1 = root_init1;
    double yval_0 = func->Eval1d(root_init0, par_func) - constant;
    double yval_1 = func->Eval1d(root_init1, par_func) - constant;
    if(yval_0 * yval_1 >= 0){
        printf("bad blacket\n");
        exit(1);
    }
    double root = (root_0 + root_1)/2.;
    double yval = func->Eval1d(root, par_func) - constant;
    while(fabs(yval) > epsilon){
        if(yval * yval_0 > 0){
            root_0 = (root_0 + root_1)/2.;
        } else {
            root_1 = (root_0 + root_1)/2.;
        }
        root = (root_0 + root_1)/2.;
        yval = func->Eval1d(root, par_func) - constant;
        iterate ++;
    }
    return root;
}
