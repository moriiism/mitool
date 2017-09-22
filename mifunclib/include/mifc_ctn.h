#ifndef MORIIISM_MITOOL_MIFUNCLIB_CONT_H_
#define MORIIISM_MITOOL_MIFUNCLIB_CONT_H_

#include "mir_func.h"
#include "mir_func_par.h"
#include "mifc_functional.h"

//
// container of function
//

class MifcCtn : public MiObject{
public:
    explicit MifcCtn(string title = "") :
        MiObject("MifcCtn", title),
        id_(0),
        name_(""),
        func_(NULL),
        func_par_(NULL) {}
    ~MifcCtn(){
        Null();
    }
    void InitSet(int id,
                 string name,
                 const MirFunc* const func,
                 const MirFuncPar* const func_par);

    void Copy(const MifcCtn* const org);
    MifcCtn* const Clone() const;

    //
    // const functions
    //
    void Print(FILE* fp) const;

    int GetId() const {return id_;};
    string GetName() const {return name_;};
    MirFunc* GetFunc() const {return func_;};
    MirFuncPar* GetFuncPar() const {return func_par_;};

private:
    int id_;
    string name_;
    MirFunc* func_;
    MirFuncPar* func_par_;
    
    void Null();
};

//
// container of function array and their linear combination
//

class MifcLincombCtn : public MiObject{
public:
    explicit MifcLincombCtn(string title = "") :
        MiObject("MifcLincombCtn", title),
        nfunc_(0),
        id_arr_(NULL),
        name_arr_(NULL),
        func_arr_(NULL),
        func_par_arr_(NULL),
        coeff_arr_(NULL) {}
    ~MifcLincombCtn(){
        Null();
    }
    void InitSet(int nfunc,
                 const int* const id_arr,
                 const string* const name_arr,
                 const MirFunc* const* const func_arr,
                 const MirFuncPar* const* const func_par_arr,
                 const double* const coeff_arr);

    void SetCoeffArrElm(int ifunc, double coeff);

   
    void Copy(const MifcLincombCtn* const org);
    MifcLincombCtn* const Clone() const;

    //
    // const functions
    //
    void Print(FILE* fp) const;

    int GetNfunc() const {return nfunc_;};
    int* const GetIdArr() const {return id_arr_;};
    string* const GetNameArr() const {return name_arr_;};
    MirFunc** const GetFuncArr() const {return func_arr_;};
    MirFuncPar** const GetFuncParArr() const {return func_par_arr_;};
    double* const GetCoeffArr() const {return coeff_arr_;};
    
    int GetIdArrElm(int ifunc) const {return id_arr_[ifunc];};
    string GetNameArrElm(int ifunc) const {return name_arr_[ifunc];};
    MirFunc* GetFuncArrElm(int ifunc) const {return func_arr_[ifunc];};
    MirFuncPar* GetFuncParArrElm(int ifunc) const {return func_par_arr_[ifunc];};
    double GetCoeffArrElm(int ifunc) const {return coeff_arr_[ifunc];};

    LinCombFunc* const GenFuncLincomb() const;
    MirFuncPar* const GenFuncLincombPar() const;
    
private:
    int nfunc_;
    int* id_arr_;
    string* name_arr_;
    MirFunc** func_arr_;
    MirFuncPar** func_par_arr_;
    double* coeff_arr_;

    void Null();
};


#endif // MORIIISM_MITOOL_MIFUNCLIB_CONT_H_
