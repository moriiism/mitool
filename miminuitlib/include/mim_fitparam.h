#ifndef MORIIISM_MITOOL_MIMINUITLIB_FITPARAM_H_
#define MORIIISM_MITOOL_MIMINUITLIB_FITPARAM_H_

#include "TF1.h"
#include "mi_base.h"
#include "mi_iolib.h"
#include "mir_func.h"
#include "mir_func_par.h"

class FitParam : public MiObject{
public:
    explicit FitParam(string title = "") :
        MiObject("FitParam", title),
        npar_(0),
        par_name_(NULL),
        par_init_(NULL),
        par_serr_init_(NULL),
        par_lo_str_(NULL),
        par_up_str_(NULL),
        flag_calc_terr_(NULL),
        index_comp_(NULL),
        par_(NULL),
        par_serr_(NULL),
        par_terr_minus_(NULL),
        par_terr_plus_(NULL),
        valid_par_(NULL),
        valid_terr_minus_(NULL),
        valid_terr_plus_(NULL) {} 
    ~FitParam() {
        Null();
    }

    void Init(int npar);
    
    // To set initial parameters for fits
    // Set par_serr < 0, to fix parameter.
    void SetIn(int npar, const string* const par_name,
               const double* const par_init, const double* const par_serr_init,
               const string* const par_lo_str, const string* const par_up_str,
               const int* const flag_calc_terr, const int* const index_comp);
    void SetInElm(int ipar, string par_name,
                  double par_init, double par_serr_init,
                  string par_lo_str, string par_up_str,
                  int flag_calc_terr, int index_comp);
    void LoadIn(string file);
    void FixPar(int ipar, double par_init);
    void SetParInit(int npar, const double* const par_init);
    void SetFlagCalcTerrElm(int ipar, int flag_calc_terr);

    // set results
    void SetPar(int npar, const double* const par);
    void SetParSerr(int npar, const double* const par_serr);    
    void SetParElm(int ipar, double par);
    void SetParSerrElm(int ipar, double par_serr);
    void SetParTerrElm(int ipar, double terr_minus, double terr_plus);
    void SetValidParElm(int ipar, int valid_par);
    void SetValidTerrElm(int ipar, int valid_terr_minus, int valid_terr_plus);

    void SetOut(const FitParam* const fitparam_in,
                int npar, const double* const par, const double* const par_serr);
    
    void Copy(const FitParam* const org);
    FitParam* const Clone() const;

    
    void Print(FILE* fp) const;

    int GetNpar() const {return npar_;};
    const string* const GetParName() const {return par_name_;};
    const double* const GetParInit() const {return par_init_;};
    const double* const GetParSerrInit() const {return par_serr_init_;};
    const string* const GetParLoStr() const {return par_lo_str_;};
    const string* const GetParUpStr() const {return par_up_str_;};
    const int* const GetFlagCalcTerr() const { return flag_calc_terr_;};
    const int* const GetIndexComp() const {return index_comp_;};
    const double* const GetPar() const {return par_;};
    const double* const GetParSerr() const  {return par_serr_;};
    const double* const GetParTerrMinus() const  {return par_terr_minus_;};
    const double* const GetParTerrPlus() const  {return par_terr_plus_;};
    const int* const GetValidPar() const  {return valid_par_;};    
    const int* const GetValidTerrMinus() const  {return valid_terr_minus_;};
    const int* const GetValidTerrPlus() const  {return valid_terr_plus_;};    
    
    string GetParNameElm(int ipar) const {return par_name_[ipar];};
    double GetParInitElm(int ipar) const {return par_init_[ipar];};
    double GetParSerrInitElm(int ipar) const {return par_serr_init_[ipar];};
    string GetParLoStrElm(int ipar) const {return par_lo_str_[ipar];};
    string GetParUpStrElm(int ipar) const {return par_up_str_[ipar];};
    int    GetFlagCalcTerrElm(int ipar) const {return flag_calc_terr_[ipar];};
    int    GetIndexCompElm(int ipar) const {return index_comp_[ipar];};
    double GetParElm(int ipar) const {return par_[ipar];};
    double GetParSerrElm(int ipar) const {return par_serr_[ipar];};    
    double GetParTerrMinusElm(int ipar) const {return par_terr_minus_[ipar];};
    double GetParTerrPlusElm(int ipar) const {return par_terr_plus_[ipar];};
    int GetValidParElm(int ipar) const  {return valid_par_[ipar];};
    int GetValidTerrMinusElm(int ipar) const  {return valid_terr_minus_[ipar];};
    int GetValidTerrPlusElm(int ipar) const  {return valid_terr_plus_[ipar];};

    int GetNparFree() const;

    // If you calculate asymmetrical error for at least one parameter,
    // This function returns 1. If not, it returns 0.
    int IsCalcTerr() const;
    
    static void CopyPar(const FitParam* const fitparam, TF1* const tf1);

    MirFuncPar* const GenFuncPar() const;
    MirFuncPar* const GenFuncParInit() const;

    int GetIndexByName(string name) const;
    
private:
    int npar_;
    string* par_name_;
    double* par_init_;
    double* par_serr_init_; // if < 0, this par will be fixed.
    string* par_lo_str_;
    string* par_up_str_;
    // whether you calculate asymmetrical error or not
    int* flag_calc_terr_;
    int* index_comp_;

    // results
    double* par_;
    double* par_serr_;
    double* par_terr_minus_;
    double* par_terr_plus_;
    int*    valid_par_;
    int*    valid_terr_minus_;
    int*    valid_terr_plus_;

    void Null();
};

#endif // MORIIISM_MITOOL_MIMINUITLIB_FITPARAM_H_
