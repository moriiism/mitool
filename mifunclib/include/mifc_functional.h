#ifndef MORIIISM_MITOOL_MIFUNCLIB_FUNCTIONAL_H_
#define MORIIISM_MITOOL_MIFUNCLIB_FUNCTIONAL_H_

#include "mir_math.h"
#include "mir_func.h"

//
// oval = func_org(xval - par_shift, par_org) + par_shift_oval
// (par) = [(par_org), (par_shift), par_shift_oval]
//
class ParallelShiftFunc : public MirFunc{
public:
    explicit ParallelShiftFunc(string title = "") :
        MirFunc("ParallelShiftFunc", title),
        func_obj_(NULL)
        {
            SetNpar(0);
            SetNdim(0);
        }
    ~ParallelShiftFunc()
        {
            Null();
        }
    void InitSet(const MirFunc* const func_obj);
    void Copy(const ParallelShiftFunc* const org);
    ParallelShiftFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    MirFunc* const GetFuncObj() const {return func_obj_;};
    
private:
    MirFunc* func_obj_;
    void Null();    
};


//
// oval = func_org( rot(xval, theta), par_org)
// (par) = [(par_org), theta]
//
class RotationFunc : public MirFunc{
public:
    explicit RotationFunc(string title = "") :
        MirFunc("RotationFunc", title),
        func_obj_(NULL)
        {
            SetNpar(0);
            SetNdim(0);            
        }
    ~RotationFunc()
        {
            Null();
        }
    void InitSet(const MirFunc* const func_obj);
    void Copy(const RotationFunc* const org);
    RotationFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    MirFunc* const GetFuncObj() const {return func_obj_;};
    
private:
    MirFunc* func_obj_;
    void Null();
};


//
// oval = func1(xval, par1) + func2(xval, par2)
// (par) = [par1, par2]
//

class AddFunc : public MirFunc{
public:
    explicit AddFunc(string title = "") :
        MirFunc("AddFunc", title),
        func_obj1_(NULL),
        func_obj2_(NULL)
        {
            SetNpar(0);
            SetNdim(0);            
        }
    ~AddFunc()
        {
            Null();
        }
    void InitSet(const MirFunc* const func_obj1,
                 const MirFunc* const func_obj2);
    void Copy(const AddFunc* const org);
    AddFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    MirFunc* const GetFuncObj1() const {return func_obj1_;};
    MirFunc* const GetFuncObj2() const {return func_obj2_;};
    
private:
    MirFunc* func_obj1_;
    MirFunc* func_obj2_;
    void Null();    
};


//
// oval = sum_{i = 0}^{N - 1} func_i(xval, par_i)
// (par) = [par_0, par_1, ..., par_N-1]
//

class AddNFunc : public MirFunc{
public:
    explicit AddNFunc(string title = "") :
        MirFunc("AddNFunc", title),
        nfunc_(0),
        func_obj_arr_(NULL)
        {
            SetNpar(0);
            SetNdim(0);            
        }
    ~AddNFunc()
        {
            Null();
        }
    void InitSet(int nfunc,
                 const MirFunc* const* const func_obj_arr);
    void Copy(const AddNFunc* const org);
    AddNFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    int GetNfunc() const {return nfunc_;};
    MirFunc** const GetFuncObjArr() const {return func_obj_arr_;};
    MirFunc* const GetFuncObjArrElm(int ifunc) const {return func_obj_arr_[ifunc];};

private:
    int nfunc_;
    MirFunc** func_obj_arr_;
    void Null();    
};

//
// oval = sum_{i = 0}^{N - 1} norm_i * func_i(xval, par_i)
// (par) = [par_0, par_1, ..., par_N-1, norm_0, ..., norm_N-1]
//
// Linear Combination
//

class LinCombFunc : public MirFunc{
public:
    explicit LinCombFunc(string title = "") :
        MirFunc("LinCombFunc", title),
        nfunc_(0),
        func_obj_arr_(NULL)
        {
            SetNpar(0);
            SetNdim(0);
        }
    ~LinCombFunc()
        {
            Null();
        }
    void InitSet(int nfunc,
                 const MirFunc* const* const func_obj_arr);
    void Copy(const LinCombFunc* const org);
    LinCombFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    int GetNfunc() const {return nfunc_;};
    MirFunc** const GetFuncObjArr() const {return func_obj_arr_;};
    MirFunc* const GetFuncObjArrElm(int ifunc) const {return func_obj_arr_[ifunc];};

    static int GetNparTotalLincomb(int nfunc, const MirFunc* const* const func_arr);

private:
    int nfunc_;
    MirFunc** func_obj_arr_;
    void Null();    
};

#endif // MORIIISM_MITOOL_MIFUNCLIB_FUNCTIONAL_H_
