#ifndef MORIIISM_MITOOL_MIMINUITLIB_SEARCH_PAR_H_
#define MORIIISM_MITOOL_MIMINUITLIB_SEARCH_PAR_H_

#include "TF1.h"
#include "TAxis.h"
#include "TPad.h"

#include "mi_iolib.h"
#include "mir_hist_info.h"

class MimSearchPar : public MiObject{
public:
    explicit MimSearchPar(string title = "") :
        MiObject("MimSearchPar", title),
        npar_(0), par_info_(NULL) {}
    ~MimSearchPar() {
        Null();
    }

    void Init(long npar);
    void Load(string file);
    void Copy(const MimSearchPar* const org);
    MimSearchPar* const Clone() const;
    
    void Print(FILE* fp) const;
  
    // const func
    int GetNpar() const {return npar_;};
    HistInfo1d* const* const GetParInfo() const {return par_info_;};
    long GetNbinElm(int ipar) const {return par_info_[ipar]->GetNbin();}
    double GetLoElm(int ipar) const {return par_info_[ipar]->GetLo();};
    double GetUpElm(int ipar) const {return par_info_[ipar]->GetUp();};

private:
    long npar_;
    HistInfo1d** par_info_;
    void Null();
};

#endif // MORIIISM_MITOOL_MIMINUITLIB_SEARCH_PAR_H_

