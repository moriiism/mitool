#ifndef MORIIISM_MITOOL_MIMINUITLIB_FUNC_PAR_INDEX_H_
#define MORIIISM_MITOOL_MIMINUITLIB_FUNC_PAR_INDEX_H_

#include "mi_iolib.h"
#include "mifc_functional.h"
#include "mim_tie.h"
#include "mim_link.h"

class MimFuncLincombParIndex : public MiObject{
public:
    explicit MimFuncLincombParIndex(string title = "") :
        MiObject("MimFuncLincombParIndex", title),
        nfile_(0),
        nfunc_arr_(NULL),
        npar_base_arr_(NULL),
        index_base_arr_(NULL),
        npar_coeff_arr_(NULL),
        index_coeff_arr_(NULL),
        npar_total_(0){}
    ~MimFuncLincombParIndex() {
        Null();
    }
    void InitSet(int nfile,
                 const LinCombFunc* const* const func_lincomb_arr,
                 const MimTie* const mim_tie);

    // const func
    int GetNfile() const {return nfile_;};
    int* const GetNfuncArr() const {return nfunc_arr_;};
    int** const GetNparBaseArr() const {return npar_base_arr_;};
    MimLink**** const GetIndexBaseArr() const {return index_base_arr_;};
    int* const GetNparCoeffArr() const {return npar_coeff_arr_;};
    MimLink*** const GetIndexCoeffArr() const {return index_coeff_arr_;};

    int GetNfuncArrElm(int ifile) const {return nfunc_arr_[ifile];};
    int GetNparBaseArrElm(int ifile, int ifunc) const
        {return npar_base_arr_[ifile][ifunc];};
    MimLink* const GetIndexBaseArrElm(int ifile, int ifunc, int ipar) const
        {return index_base_arr_[ifile][ifunc][ipar];};
    int GetNparCoeffArrElm(int ifile) const {return npar_coeff_arr_[ifile];};
    MimLink* const GetIndexCoeffArrElm(int ifile, int ifunc) const
        {return index_coeff_arr_[ifile][ifunc];};

    int GetNparTotal() const {return npar_total_;};
    
    void Print(FILE* fp) const;

private:
    int nfile_;
    int* nfunc_arr_;
    int** npar_base_arr_;
    MimLink**** index_base_arr_;
    int* npar_coeff_arr_;
    MimLink*** index_coeff_arr_;

    int npar_total_;

    void Null();
};

#endif // MORIIISM_MITOOL_MIMINUITLIB_FUNC_PAR_INDEX_H_
