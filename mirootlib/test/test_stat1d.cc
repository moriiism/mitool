#include "mi_iolib.h"
#include "mir_stat1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Set(long ndata, double min, double max,
//             double sum, double sum_err, double amean, double variance, double stddev,
//             double unbiased_variance, double sqrt_of_unbiased_variance,
//             double rms, double median, double wmean, double wmean_err, long num_bad_wmean, 
//             double amean_of_err,
//             int ndf, double chi2, double chi2_red, double prob_chi2);
//    void Copy(const Stat1dim* const org);
//    Stat1dim* const Clone() const;
    {
        printf("--- test Set\n");

        long ndata = 10;
        double min = 1.0;
        double max = 2.0;
        double sum = 3.0;
        double sum_err = 4.0;
        double amean = 5.0;
        double variance = 6.0;
        double stddev = 7.0;
        double unbiased_variance = 8.0;
        double sqrt_of_unbiased_variance = 9.0;
        double rms = 10.0;
        double median = 11.0;
        double wmean = 12.0;
        double wmean_err = 13.0;
        long num_bad_wmean = 14; 
        double amean_of_err = 15.0;
        int ndf = 16;
        double chi2 = 17.0;
        double chi2_red = 18.0;
        double prob_chi2 = 19.0;
        
        Stat1dim* stat1d = new Stat1dim;
        stat1d->Set(ndata, min, max,
                    sum, sum_err, amean, variance, stddev,
                    unbiased_variance, sqrt_of_unbiased_variance,
                    rms, median, wmean, wmean_err, num_bad_wmean, 
                    amean_of_err,
                    ndf, chi2, chi2_red, prob_chi2);

        printf("--- \n");
        //    long GetNdata() const {return ndata_;};
        printf("GetNdata() = %ld\n", stat1d->GetNdata());
        assert(stat1d->GetNdata() == ndata);

        //    double GetMin() const {return min_;};
        printf("GetMin() = %e\n", stat1d->GetMin());
        assert(stat1d->GetMin() == min);
        
        //    double GetMax() const {return max_;};
        printf("GetMax() = %e\n", stat1d->GetMax());
        assert(stat1d->GetMax() == max);
        
        //    double GetSum() const {return sum_;};
        printf("GetSum() = %e\n", stat1d->GetSum());
        assert(stat1d->GetSum() == sum);
        
        //    double GetSumErr() const {return sum_err_;};
        printf("GetSumErr() = %e\n", stat1d->GetSumErr());
        assert(stat1d->GetSumErr() == sum_err);
        
        //    double GetAmean() const {return amean_;};
        printf("GetAmean() = %e\n", stat1d->GetAmean());
        assert(stat1d->GetAmean() == amean);

        //    double GetVariance() const {return variance_;};
        printf("GetVariance() = %e\n", stat1d->GetVariance());
        assert(stat1d->GetVariance() == variance);
        
        //    double GetStddev() const {return stddev_;};
        printf("GetStddev() = %e\n", stat1d->GetStddev());
        assert(stat1d->GetStddev() == stddev);
        
        //    double GetUnbiasedVariance() const {return unbiased_variance_;};
        printf("GetUnbiasedVariance() = %e\n", stat1d->GetUnbiasedVariance());
        assert(stat1d->GetUnbiasedVariance() == unbiased_variance);
        
        //    double GetSqrtOfUnbiasedVariance() const {return sqrt_of_unbiased_variance_;};
        printf("GetSqrtOfUnbiasedVariance() = %e\n", stat1d->GetSqrtOfUnbiasedVariance());
        assert(stat1d->GetSqrtOfUnbiasedVariance() == sqrt_of_unbiased_variance);
        
        //    double GetRms() const {return rms_;};
        printf("GetRms() = %e\n", stat1d->GetRms());
        assert(stat1d->GetRms() == rms);
        
        //    double GetMedian() const {return median_;};
        printf("GetMedian() = %e\n", stat1d->GetMedian());
        assert(stat1d->GetMedian() == median);
        
        //    double GetWmean() const {return wmean_;};
        printf("GetWmean() = %e\n", stat1d->GetWmean());
        assert(stat1d->GetWmean() == wmean);
        
        //    double GetWmeanErr() const {return wmean_err_;};
        printf("GetWmeanErr() = %e\n", stat1d->GetWmeanErr());
        assert(stat1d->GetWmeanErr() == wmean_err);
        
        //    long GetNumBadWmean() const {return num_bad_wmean_;};
        printf("GetNumBadWmean() = %ld\n", stat1d->GetNumBadWmean());
        assert(stat1d->GetNumBadWmean() == num_bad_wmean);
        
        //    double GetAmeanOfErr() const {return amean_of_err_;};
        printf("GetAmeanOfErr() = %e\n", stat1d->GetAmeanOfErr());
        assert(stat1d->GetAmeanOfErr() == amean_of_err);
        
        //    int GetNdf() const {return ndf_;};
        printf("GetNdf() = %d\n", stat1d->GetNdf());
        assert(stat1d->GetNdf() == ndf);
        
        //    double GetChi2() const {return chi2_;};
        printf("GetChi2() = %e\n", stat1d->GetChi2());
        assert(stat1d->GetChi2() == chi2);
        
        //    double GetChi2Red() const {return chi2_red_;};
        printf("GetChi2Red() = %e\n", stat1d->GetChi2Red());
        assert(stat1d->GetChi2Red() == chi2_red);
        
        //    double GetProbChi2() const {return prob_chi2_;};
        printf("GetProbChi2() = %e\n", stat1d->GetProbChi2());
        assert(stat1d->GetProbChi2() == prob_chi2);
        
        stat1d->Print(stdout);
        
        printf("--- test Copy\n");
        Stat1dim* stat1d_new = new Stat1dim;
        stat1d_new->Copy(stat1d);
        stat1d_new->Print(stdout);

        printf("--- test Clone\n");
        Stat1dim* stat1d_clone = stat1d->Clone();
        stat1d_clone->Print(stdout);


        printf("--- \n");
        //    void Print(FILE* fp) const;
        stat1d->Print(stdout);
        
        delete stat1d;
        delete stat1d_new;
        delete stat1d_clone;
        
        printf("=== \n");
    }

    printf("=== end === \n");

    return status_prog;
}
