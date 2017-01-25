#ifndef MORIIISM_MITOOL_MIROOTLIB_STAT1D_H_
#define MORIIISM_MITOOL_MIROOTLIB_STAT1D_H_

#include "mir_math.h"

// "Average" and "mean" are ambiguous, then we do not use these names.
// Instead, we use the followings:
//   Arithmetic mean --> AMean
//   Weighted mean   --> WMean

class Stat1dim : public MiObject{
public:
    explicit Stat1dim(string title = "") :
        MiObject("Stat1dim", title),
        ndata_(0),
        min_(0.0),
        max_(0.0),
        sum_(0.0),
        sum_err_(0.0),
        amean_(0.0),
        variance_(0.0),
        stddev_(0.0),
        unbiased_variance_(0.0),
        sqrt_of_unbiased_variance_(0.0),
        rms_(0.0),
        median_(0.0),
        wmean_(0.0),
        wmean_err_(0.0),
        num_bad_wmean_(0),
        amean_of_err_(0.0),
        ndf_(0),
        chi2_(0.0),
        chi2_red_(0.0),
        prob_chi2_(0.0) {}
    ~Stat1dim(){
        Null();
    }

    void Set(long ndata, double min, double max,
             double sum, double sum_err, double amean, double variance, double stddev,
             double unbiased_variance, double sqrt_of_unbiased_variance,
             double rms, double median, double wmean, double wmean_err, long num_bad_wmean, 
             double amean_of_err,
             int ndf, double chi2, double chi2_red, double prob_chi2);
    void Copy(const Stat1dim* const org);
    Stat1dim* const Clone() const;

    long GetNdata() const {return ndata_;};
    double GetMin() const {return min_;};
    double GetMax() const {return max_;};
    double GetSum() const {return sum_;};
    double GetSumErr() const {return sum_err_;};
    double GetAmean() const {return amean_;};
    double GetVariance() const {return variance_;};
    double GetStddev() const {return stddev_;};
    double GetUnbiasedVariance() const {return unbiased_variance_;};
    double GetSqrtOfUnbiasedVariance() const {return sqrt_of_unbiased_variance_;};
    double GetRms() const {return rms_;};
    double GetMedian() const {return median_;};
    double GetWmean() const {return wmean_;};
    double GetWmeanErr() const {return wmean_err_;};
    long GetNumBadWmean() const {return num_bad_wmean_;};
    double GetAmeanOfErr() const {return amean_of_err_;};
    int GetNdf() const {return ndf_;};
    double GetChi2() const {return chi2_;};
    double GetChi2Red() const {return chi2_red_;};
    double GetProbChi2() const {return prob_chi2_;};

    void Print(FILE* fp) const;

private:
    long ndata_;   // number of data
    double min_;
    double max_;
  
    double sum_;
    double sum_err_;
    double amean_;   // arithmetic mean
    double variance_;
    double stddev_;

    double unbiased_variance_;
    double sqrt_of_unbiased_variance_;    
    
    double rms_;
    double median_;

    double wmean_;
    double wmean_err_;
    long num_bad_wmean_;

    double amean_of_err_;

    int ndf_;  // number of degree of freedom
    double chi2_;
    double chi2_red_;
    double prob_chi2_;

    void Null();
};

#endif // MORIIISM_MITOOL_MIROOTLIB_STAT1D_H_
