#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_solve.h"
#include "mifc_std.h"
#include "mir_qdp_tool.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    double GetRootNewton(const MirFunc* const func, const double* const par_func,
//                         const MirFunc* const func_prime, const double* const par_func_prime,
//                         double root_init, double epsilon);
    {
        printf("--- test GetRootNewton\n");

        // func = a*(x - b)^2 + c
        // func_prime = 2*a*(x - b) = 2*a*x - 2*a*b

        double par_a = 2.0;
        double par_b = 3.0;
        double par_c = -10.0;
        
        MirFunc* func = new ParabolaFunc;
        double par_func[3];
        par_func[0] = par_a;
        par_func[1] = par_b;
        par_func[2] = par_c;

        MirFunc* func_prime = new LinFunc;
        double par_func_prime[2];
        par_func_prime[0] = -2 * par_a * par_b;
        par_func_prime[1] = 2 * par_a;

        double root_init = 5.0;
        double epsilon = 1.e-10;
        double ans = MirSolve::GetRootNewton(func, par_func,
                                             func_prime, par_func_prime,
                                             root_init, epsilon);
        MirQdpTool::MkQdp(func, par_func,
                          1000, -5.0, 10.0,
                          "/home/morii/temp/newton.qdp");
        double ans_true = par_b + sqrt(-1 * par_c / par_a);
        printf("ans      = %e\n", ans);
        printf("ans_true = %e\n", ans_true);
        assert( fabs(ans - ans_true) < epsilon );
        
        printf("=== \n");
    }
    
//    // solve equation: f(x) = 0
//    double GetRootSecant(const MirFunc* const func, const double* const par_func,
//                         double root_init0, double root_init1, double epsilon);
    {
        printf("--- test GetRootSecant\n");
        // func = a*(x - b)^2 + c
        double par_a = 2.0;
        double par_b = 3.0;
        double par_c = -10.0;
        
        MirFunc* func = new ParabolaFunc;
        double par_func[3];
        par_func[0] = par_a;
        par_func[1] = par_b;
        par_func[2] = par_c;

        double root_init0 = 5.0;
        double root_init1 = 10.0;
        double epsilon = 1.e-10;
        double ans = MirSolve::GetRootSecant(func, par_func,
                                             root_init0, root_init1, epsilon);
        MirQdpTool::MkQdp(func, par_func,
                          1000, -5.0, 10.0,
                          "/home/morii/temp/secant.qdp");
        double ans_true = par_b + sqrt(-1 * par_c / par_a);
        printf("ans      = %e\n", ans);
        printf("ans_true = %e\n", ans_true);
        assert( fabs(ans - ans_true) < epsilon );
        printf("=== \n");
    }
   
//    // solve equation: f(x) = constant
//    double GetRootSecantEqC(const MirFunc* const func, const double* const par_func,
//                            double root_init0, double root_init1, double constant, double epsilon);
    {
        printf("--- test GetRootSecantEqC\n");
        printf("=== \n");
    }

//    // solve equation: f(x) = 0
//    double GetRootBisection(const MirFunc* const func, const double* const par_func,
//                            double root_init0, double root_init1,
//                            double epsilon);
    {
        printf("--- test GetRootBisection\n");
        // func = a*(x - b)^2 + c
        double par_a = 2.0;
        double par_b = 3.0;
        double par_c = -10.0;
        
        MirFunc* func = new ParabolaFunc;
        double par_func[3];
        par_func[0] = par_a;
        par_func[1] = par_b;
        par_func[2] = par_c;

        double root_init0 = 5.0;
        double root_init1 = 10.0;
        double epsilon = 1.e-10;
        double ans = MirSolve::GetRootBisection(func, par_func,
                                                root_init0, root_init1, epsilon);
        MirQdpTool::MkQdp(func, par_func,
                          1000, -5.0, 10.0,
                          "/home/morii/temp/bisect.qdp");
        double ans_true = par_b + sqrt(-1 * par_c / par_a);
        printf("ans      = %e\n", ans);
        printf("ans_true = %e\n", ans_true);
        assert( fabs(ans - ans_true) < epsilon );
        
        printf("=== \n");
    }
   
//    // solve equation: f(x) = constant
//    double GetRootBisectionEqC(const MirFunc* const func, const double* const par_func,
//                               double root_init0, double root_init1,
//                               double constant, double epsilon);
    {
        printf("--- test GetRootBisectionEqC\n");
        printf("=== \n");
    }
    
    return status_prog;
}
