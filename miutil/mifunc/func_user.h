#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_FUNC_USER_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_FUNC_USER_H_

#include "mifc_gen.h"

namespace FuncUser
{
    MirFunc* const GenFunc(string func_name);
    MirFunc* const GenFuncUser(string func_name);
}

class TestFunc : public MirFunc{
public:
    TestFunc(string title = "") :
        MirFunc("TestFunc", title)
        {
            SetNpar(1);
            SetNdim(1);            
        }
    ~TestFunc() {}
    void Copy(const TestFunc* const org);
    TestFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_FUNC_USER_H_
