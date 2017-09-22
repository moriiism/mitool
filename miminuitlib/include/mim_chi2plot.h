#ifndef MORIIISM_MITOOL_MIMINUITLIB_CHI2PLOT_H_
#define MORIIISM_MITOOL_MIMINUITLIB_CHI2PLOT_H_

#include "mi_iolib.h"
#include "mim_fitstat.h"

class Chi2PlotPar : public MiObject{
public:
    explicit Chi2PlotPar(string title = "") :
        MiObject("Chi2PlotPar", title),
        npar_(0),
        index_(NULL), nstep_(NULL),
        lo_str_(NULL), up_str_(NULL),
        sigma_str_(NULL),
        index1_str_(NULL),
        num_index1_(NULL),
        index1_arr_(NULL) {}
    ~Chi2PlotPar() {
        Null();
    }

    // Init
    void Init(int npar);

    // Set
    void SetDataElm(int ipar, int index, int nstep, string lo_str, string up_str,
                    string sigma_str, string index1_str);
   
    void Load(string file);
    void SetLoUpSigmaByFitStat(const FitStat* const fit_stat);
    // sigma --> Low and Up

    void SetIndex1Arr(const FitParam* const fit_param);
    // index1_str --> num_index1_ & index1_arr_
    
    void Copy(const Chi2PlotPar* const org);
    Chi2PlotPar* const Clone() const;
    void Print(FILE* fp) const;
  
    int GetNpar() const {return npar_;};
    const int* const GetIndex() const {return index_;};
    const int* const GetNstep() const {return nstep_;};
    const string* const GetLoStr() const {return lo_str_;};
    const string* const GetUpStr() const {return up_str_;};
    const string* const GetSigmaStr() const {return sigma_str_;};
    const string* const GetIndex1Str() const {return index1_str_;};
    const int* const GetNumIndex1() const {return num_index1_;};
    const int* const* const GetIndex1Arr() const {return index1_arr_;};

    int GetIndexElm(int ipar) const {return index_[ipar];};
    int GetNstepElm(int ipar) const {return nstep_[ipar];};
    string GetLoStrElm(int ipar) const {return lo_str_[ipar];};
    string GetUpStrElm(int ipar) const {return up_str_[ipar];};
    string GetSigmaStrElm(int ipar) const {return sigma_str_[ipar];};
    string GetIndex1StrElm(int ipar) const {return index1_str_[ipar];};
    int GetNumIndex1Elm(int ipar) const {return num_index1_[ipar];};
    int GetIndex1ArrElm(int ipar, int inum) const {return index1_arr_[ipar][inum];};

    double GetStepElm(int ipar) const;
    double GetParVal(int ipar, int istep) const;

    static int IsValidLoUpSigmaStr(string lo_str, string up_str, string sigma_str);
    static void GetLoUpSigmaStrByFitParam(const FitParam* const fit_param, int index, double sigma,
                                          string* lo_str_ptr, string* up_str_ptr, string* sigma_str_ptr);

private:
    int npar_;
    int* index_;
    int* nstep_;
    string* lo_str_;
    string* up_str_;
    string* sigma_str_;

    string* index1_str_;
    int*  num_index1_;
    int** index1_arr_;


    void Null();
};


class Chi2PlotContPar : public MiObject{
public:
    explicit Chi2PlotContPar(string title = "") :
        MiObject("Chi2PlotContPar", title),
        ncont_(0),
        index0_(NULL), nstep0_(NULL), lo0_str_(NULL), up0_str_(NULL), sigma0_str_(NULL),
        index1_(NULL), nstep1_(NULL), lo1_str_(NULL), up1_str_(NULL), sigma1_str_(NULL),
        index2_str_(NULL), num_index2_(NULL), index2_arr_(NULL) {}
    ~Chi2PlotContPar() {
        Null();
    }

    // Init
    void Init(int ncont);

    // Set
    void SetDataElm(int icont,
                    int index0, int nstep0, string lo0_str, string up0_str, string sigma0_str,
                    int index1, int nstep1, string lo1_str, string up1_str, string sigma1_str,
                    string index2_str);

    void Load(string file);
    void SetLoUpSigmaByFitStat(const FitStat* const fit_stat);
    // sigma --> Low and Up
    
    void SetIndex2Arr(const FitParam* const fit_param);
    // index2_str --> num_index2_ & index2_arr_

    void Copy(const Chi2PlotContPar* const org);
    Chi2PlotContPar* const Clone() const;
    void Print(FILE* fp) const;
  
    int GetNcont() const {return ncont_;};
    const int* const GetIndex0() const {return index0_;};
    const int* const GetNstep0() const {return nstep0_;};
    const string* const GetLo0Str() const {return lo0_str_;};
    const string* const GetUp0Str() const {return up0_str_;};
    const string* const GetSigma0Str() const {return sigma0_str_;};

    const int* const GetIndex1() const {return index1_;};
    const int* const GetNstep1() const {return nstep1_;};
    const string* const GetLo1Str() const {return lo1_str_;};
    const string* const GetUp1Str() const {return up1_str_;};
    const string* const GetSigma1Str() const {return sigma1_str_;};

    const string* const GetIndex2Str() const {return index2_str_;};
    const int* const GetNumIndex2() const {return num_index2_;};
    const int* const* const GetIndex2Arr() const {return index2_arr_;};

    int GetIndex0Elm(int icont) const {return index0_[icont];};
    int GetNstep0Elm(int icont) const {return nstep0_[icont];};
    string GetLo0StrElm(int icont) const {return lo0_str_[icont];};
    string GetUp0StrElm(int icont) const {return up0_str_[icont];};
    string GetSigma0StrElm(int icont) const {return sigma0_str_[icont];};

    int GetIndex1Elm(int icont) const {return index1_[icont];};
    int GetNstep1Elm(int icont) const {return nstep1_[icont];};
    string GetLo1StrElm(int icont) const {return lo1_str_[icont];};
    string GetUp1StrElm(int icont) const {return up1_str_[icont];};
    string GetSigma1StrElm(int icont) const {return sigma1_str_[icont];};

    string GetIndex2StrElm(int icont) const {return index2_str_[icont];};
    int GetNumIndex2Elm(int icont) const {return num_index2_[icont];};
    int GetIndex2ArrElm(int icont, int inum) const {return index2_arr_[icont][inum];};
    
    double GetStep0Elm(int icont) const;
    double GetStep1Elm(int icont) const;
    double GetPar0Val(int icont, int istep) const;
    double GetPar1Val(int icont, int istep) const;
    
private:
    int ncont_;
    int* index0_;
    int* nstep0_;
    string* lo0_str_;
    string* up0_str_;
    string* sigma0_str_;

    int* index1_;
    int* nstep1_;
    string* lo1_str_;
    string* up1_str_;
    string* sigma1_str_;

    string* index2_str_;
    int* num_index2_;
    int** index2_arr_;

    void Null();
};

#endif // MORIIISM_MITOOL_MIMINUITLIB_CHI2PLOT_H_
