#ifndef MORIIISM_MITOOL_MIMINUITLIB_FITSTAT_H_
#define MORIIISM_MITOOL_MIMINUITLIB_FITSTAT_H_

#include "TMath.h"
#include "TF1.h"
#include "Minuit2/FunctionMinimum.h"

#include "mim_minfcn.h"
#include "mim_fitparam.h"

class FitStat : public MiObject{
public:
    explicit FitStat(string title = "") :
        MiObject("FitStat", title),
        fit_param_(NULL),
        ndata_fit_(0),
        ndf_(0),
        up_minfcn_(0.0),
        valid_(0),
        fcn_min_(0.0),
        edm_(0.0),
        nfcn_(0),
        p_value_(0.0),
        flag_bad_neg_(0),
        aic_(0.0),
        bic_(0.0),
        aic_c_(0.0) {}
    ~FitStat(){
        Null();
    }
  
    // Init
    void Init();

    // Set
    void Set(const MinFcn* const min_fcn, const FitParam* const fit_param,
             ROOT::Minuit2::FunctionMinimum min,
             ROOT::Minuit2::MnUserParameters upar);
    void Set(const MinFcnMulti* const min_fcn_multi, const FitParam* const fit_param,
             ROOT::Minuit2::FunctionMinimum min,
             ROOT::Minuit2::MnUserParameters upar);

    
    void Set(const TF1* const tf1, double chi2 = -1.0);

    // before fit
    void SetByFixPar(const MinFcn* const min_fcn,
                     const FitParam* const fit_param_in);
    void SetByFixPar(const MinFcnMulti* const min_fcn_multi,
                     const FitParam* const fit_param_in);    

    void SetParTerrElm(int ipar, double terr_minus, double terr_plus);
    void SetValidParElm(int ipar, int flag_valid_par);
    void SetValidTerrElm(int ipar, int flag_valid_terr_minus, int flag_valid_terr_plus);

    void Copy(const FitStat* const org);
    FitStat* const Clone() const;

    const FitParam* const GetFitParam() const {return fit_param_;};
    int GetNdataFit() const {return ndata_fit_;};
    int GetNdf() const {return ndf_;};
    double GetUpMinfcn() const {return up_minfcn_;};
    int GetValid() const {return valid_;};
    double GetFcnMin() const {return fcn_min_;};
    double GetEdm() const {return edm_;};
    int GetNfcn() const {return nfcn_;};
    double GetPValue() const {return p_value_;};
    int GetFlagBadNeg() const {return flag_bad_neg_;};
    double GetAic() const {return aic_;};
    double GetBic() const {return bic_;};
    double GetAicC() const {return aic_c_;};

    void Print(FILE* fp) const;

private:
    FitParam* fit_param_;

    int ndata_fit_;    // number of data points used for fit
    int ndf_;          // number of degree of freedom (= ndata_fit_ - fit_param->GetNparFree())

    double up_minfcn_;  // one, when one sigma and one parameter.
    int    valid_;
    // 1: the minimizer did find a minimum without running into troubles
    // 0: a minimum cannot be found.
  
    double fcn_min_;   // function value at the minimum
    // if (minfcn_type == chi2) or (minfcn_type == dnllr)
    // fcn_min_ equals goodness-of-fit statistic (t). 
    // See PDB (particle data book), Section statistic, subsection goodness-of-fit tests.
  
    double edm_;       // expected vertical distance to the minimum
    int    nfcn_;      // total number of function calls during the minimization

    // p_value: The probability to find the goodness-of-fit statistic (t)
    //          in the region of equal or lesser compatibility with H_0 than
    //          the level of compatibility observed with the actual data.
    //          Here, H_0 is the hypothesis in question.
    double p_value_;
    // p_value = -1 for in valid

    int    flag_bad_neg_;  // 1 or 0
    // Even if only a small fraction of the model function become negative value,
    // the likelihood fitting with poisson probability function is not valid, meaning that
    // the parameter region is conceptually unphysical.

    double aic_; // fcn_min_ + 2 * fit_param->GetNparFree()
    double bic_; // fcn_min_ + fit_param->GetNparFree() * ( ln (ndata_Fit_) - ln (2 pi) )
    double aic_c_; // c-aic = aic_ + 2 * k * ( k + 1) / (n - k - 1), where n = ndata_Fit_, k = fit_param->GetNparFree()
    
    void Null();
};

#endif // MORIIISM_MITOOL_MIMINUITLIB_FITSTAT_H_
