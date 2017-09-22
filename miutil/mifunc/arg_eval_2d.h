#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_EVAL_2D_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_EVAL_2D_H_

#include "mi_base.h"

class ArgValEval2d : public MiArgBase{
public:
    ArgValEval2d() :
        MiArgBase(),
        progname_(""),
        func_name_(""),
        par_file_(""),
        xval_(0.0), yval_(0.0) {}
    ~ArgValEval2d(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFuncName() const {return func_name_;};
    string GetParFile() const {return par_file_;};
    double GetXval() const {return xval_;};
    double GetYval() const {return yval_;};

private:
    string progname_;
    string func_name_;
    string par_file_;
    double xval_;
    double yval_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);    
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_EVAL_2D_H_
