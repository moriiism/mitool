#ifndef MORIIISM_MITOOL_MIFUNCLIB_GEN_H_
#define MORIIISM_MITOOL_MIFUNCLIB_GEN_H_

#include "mifc_std.h"
#include "mifc_spec.h"

namespace MifcGen
{
    MirFunc* const GenFunc(string func_name);
    MirFunc* const GenFuncStd(string func_name);
    FuncSpec* const GenFuncSpec(string func_name);

} // namespace MifcGen


#endif // MORIIISM_MITOOL_MIFUNCLIB_GEN_H_
