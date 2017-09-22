#ifndef MORIIISM_MITOOL_MIROOTLIB_FUNC_OPE_H_
#define MORIIISM_MITOOL_MIROOTLIB_FUNC_OPE_H_

#include "TRandom3.h"
#include "TF1.h"
#include "TF2.h"
#include "mir_root_tool.h"
#include "mir_func_par.h"
#include "mir_func.h"

namespace MirFuncOpe{
    TF1* const GenTF1(const MirFunc* const func,
                      double x_low, double x_up);
    TF2* const GenTF2(const MirFunc* const func,
                      double x_low, double x_up,
                      double y_low, double y_up);
    void DrawFunc(const MirFunc* const func,
                  const MirFuncPar* const func_par,
                  MirRootTool* const root_tool,
                  double x_low, double x_up,
                  string outfig);
    void DrawFunc(const MirFunc* const func,
                  const MirFuncPar* const func_par,
                  MirRootTool* const root_tool,
                  double x_low, double x_up,
                  double y_low, double y_up,
                  string outfig);
    double GetRandom(const MirFunc* const func,
                     const MirFuncPar* const func_par,
                     double x_low, double x_up,
                     int rand_seed);
    double GetRandom(const MirFunc* const func,
                     const MirFuncPar* const func_par,
                     double x_low, double x_up,
                     double y_low, double y_up,
                     int rand_seed);
    // If rand_seed is 0, the seed is automatically
    // computed via a TUUID object.
    // In this case the seed is guaranteed
    // to be unique in space and time.
}

#endif // MORIIISM_MITOOL_MIROOTLIB_FUNC_OPE_H_
