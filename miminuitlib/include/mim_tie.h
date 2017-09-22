#ifndef MORIIISM_MITOOL_MIMINUITLIB_TIE_H_
#define MORIIISM_MITOOL_MIMINUITLIB_TIE_H_

#include "mi_iolib.h"

class MimTie : public MiObject{
public:
    explicit MimTie(string title = "") :
        MiObject("MimTie", title),
        ntie_(0),
        id_data_lhs_arr_(NULL),
        id_func_lhs_arr_(NULL),
        id_data_rhs_arr_(NULL),
        id_func_rhs_arr_(NULL)
        {}
    ~MimTie(){
        Null();
    }

    void Init(int ntie);
    void SetIdDataLhsElm(int itie, int id_data);
    void SetIdFuncLhsElm(int itie, int id_func);
    void SetIdDataRhsElm(int itie, int id_data);
    void SetIdFuncRhsElm(int itie, int id_func);

    void Load(string file);
    void Print(FILE* fp) const;

    MimTie* const Clone() const {abort();};
    
    //
    // const functions
    //
    int GetNtie() const {return ntie_;};
    int* const GetIdDataLhsArr() const {return id_data_lhs_arr_;};
    int* const GetIdFuncLhsArr() const {return id_func_lhs_arr_;};
    int* const GetIdDataRhsArr() const {return id_data_rhs_arr_;};
    int* const GetIdFuncRhsArr() const {return id_func_rhs_arr_;};

    int GetIdDataLhsElm(int itie) const {return id_data_lhs_arr_[itie];};
    int GetIdFuncLhsElm(int itie) const {return id_func_lhs_arr_[itie];};
    int GetIdDataRhsElm(int itie) const {return id_data_rhs_arr_[itie];};
    int GetIdFuncRhsElm(int itie) const {return id_func_rhs_arr_[itie];};

    static MimTie* const GenSel(const MimTie* const mim_tie,
                                 const int* const nfunc_id_arr,
                                 const int* const* const func_id_arr);
    
private:
    // lhs: left hand side
    // rhs: right hand side
    
    int ntie_;
    int* id_data_lhs_arr_;
    int* id_func_lhs_arr_;
    int* id_data_rhs_arr_;
    int* id_func_rhs_arr_;
    
    void Null();
};

#endif // MORIIISM_MITOOL_MIMINUITLIB_TIE_H_

