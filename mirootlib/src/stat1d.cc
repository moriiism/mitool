#include "mir_stat1d.h"

// public

void Stat1dim::Set(long ndata, double min, double max,
                   double sum, double sum_err, double amean, double variance, double stddev,
                   double unbiased_variance, double sqrt_of_unbiased_variance,
                   double rms, double median, double wmean, double wmean_err, long num_bad_wmean, 
                   double amean_of_err,
                   int ndf, double chi2, double chi2_red, double prob_chi2)
{
    ndata_         = ndata;
    min_           = min;
    max_           = max;
    sum_           = sum;
    sum_err_       = sum_err;
    amean_         = amean;
    variance_      = variance;
    stddev_        = stddev;
    unbiased_variance_         = unbiased_variance;
    sqrt_of_unbiased_variance_ = sqrt_of_unbiased_variance;
    rms_           = rms;
    median_        = median;
    wmean_         = wmean;
    wmean_err_     = wmean_err;
    num_bad_wmean_ = num_bad_wmean; 
    amean_of_err_  = amean_of_err;
    ndf_           = ndf;
    chi2_          = chi2;
    chi2_red_      = chi2_red;
    prob_chi2_     = prob_chi2;
}

void Stat1dim::Copy(const Stat1dim* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}

    Null();
    
    ndata_          = org->ndata_;
    min_            = org->min_;
    max_            = org->max_;
    sum_            = org->sum_;
    sum_err_        = org->sum_err_;
    amean_          = org->amean_;
    variance_       = org->variance_;
    stddev_         = org->stddev_;
    unbiased_variance_         = org->unbiased_variance_;
    sqrt_of_unbiased_variance_ = org->sqrt_of_unbiased_variance_;
    rms_            = org->rms_;
    median_         = org->median_;
    wmean_          = org->wmean_;
    wmean_err_      = org->wmean_err_;
    num_bad_wmean_  = org->num_bad_wmean_; 
    amean_of_err_   = org->amean_of_err_;
    ndf_            = org->ndf_;
    chi2_           = org->chi2_;
    chi2_red_       = org->chi2_red_;
    prob_chi2_      = org->prob_chi2_;
}

Stat1dim* const Stat1dim::Clone() const
{
    Stat1dim* obj_new = new Stat1dim;
    obj_new->Copy(this);
    return obj_new;
}

void Stat1dim::Print(FILE* fp) const
{
    fprintf(fp, "ndata_                      = %ld\n", ndata_);
    fprintf(fp, "min_                        = %e\n", min_);
    fprintf(fp, "max_                        = %e\n", max_);
    fprintf(fp, "sum_                        = %e\n", sum_);
    fprintf(fp, "sum_err_                    = %e\n", sum_err_);
    fprintf(fp, "amean_                      = %e\n", amean_);
    fprintf(fp, "variance_                   = %e\n", variance_);
    fprintf(fp, "stddev_                     = %e\n", stddev_);
    fprintf(fp, "unbiased_variance_          = %e\n", unbiased_variance_);
    fprintf(fp, "sqrt_of_unbiased_variance_  = %e\n", sqrt_of_unbiased_variance_);
    fprintf(fp, "rms_                        = %e\n", rms_);
    fprintf(fp, "median_                     = %e\n", median_);
    fprintf(fp, "wmean_                      = %e\n", wmean_);
    fprintf(fp, "wmean_err_                  = %e\n", wmean_err_);
    fprintf(fp, "num_bad_wmean_              = %ld\n", num_bad_wmean_);
    fprintf(fp, "amean_of_err_               = %e\n", amean_of_err_);
    fprintf(fp, "fit by constant: ndf_       = %d\n", ndf_);
    fprintf(fp, "fit by constant: chi2_      = %e\n", chi2_);
    fprintf(fp, "fit by constant: chi2_red_  = %e\n", chi2_red_);
    fprintf(fp, "fit by constant: prob_chi2_ = %e\n", prob_chi2_);
}

// private

void Stat1dim::Null()
{
    ndata_ = 0;
    min_ = 0.0;
    max_ = 0.0;
    sum_ = 0.0;
    sum_err_ = 0.0;
    amean_ = 0.0;
    variance_= 0.0;
    stddev_= 0.0;
    unbiased_variance_= 0.0;
    sqrt_of_unbiased_variance_= 0.0;
    rms_= 0.0;
    median_= 0.0;
    wmean_= 0.0;
    wmean_err_= 0.0;
    num_bad_wmean_ = 0;
    amean_of_err_ = 0.0;
    ndf_ = 0;
    chi2_ = 0.0;
    chi2_red_ = 0.0;
    prob_chi2_ = 0.0;
}
