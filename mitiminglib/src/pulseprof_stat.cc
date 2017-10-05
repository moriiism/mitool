#include "mit_pulseprof_stat.h"

double PulseProfStat::GetChi2(const HistDataSerr1d* const h1d_pulse)
{
    double wmean = 0.0;
    double wmean_err = 0.0;
    long nsel = 0;
    int* mask_sel_arr = NULL;
    double chi2 = 0.0;
    long dof = 0;
    double chi2_red = 0.0;
    double prob = 0.0;
    MirMath::GenChi2byConst(h1d_pulse->GetNbinX(),
                            h1d_pulse->GetOvalArr()->GetVal(),
                            h1d_pulse->GetOvalArr()->GetValSerr(),
                            &wmean, &wmean_err,
                            &nsel, &mask_sel_arr,
                            &chi2, &dof, &chi2_red, &prob);
    return chi2;

}


/**********************

void PulseProf::GetPlsFrac(string method, double *pf_ptr, double *pf_err_ptr) const
{
    // method:
    // p2p: peak to peak: (rate_max - rate_min) / (rate_max + rate_min)
    // int: (integrated pulsed flux) / (integrated flux)
    // rms: PF = sqrt{ 1/(N - 1) * \int (R_i - R_mean)**2 } / R_mean

    string func_name = "PulseProf::GetPlsFrac()";
  
    double pf = 0.0;
    double pf_err = 0.0;
    if(method == "p2p"){
        int index_at_min = TMath::LocMin(nbin_1p_, rate_);
        int index_at_max = TMath::LocMax(nbin_1p_, rate_);
        double rate_min = rate_[index_at_min];
        double rate_max = rate_[index_at_max];
        double rate_min_err = rate_err_[index_at_min];
        double rate_max_err = rate_err_[index_at_max];

        pf = (rate_max - rate_min) / (rate_max + rate_min);
        pf_err = 2./ pow(rate_max + rate_min, 2) 
            * sqrt(pow(rate_min * rate_max_err, 2) + pow(rate_max * rate_min_err, 2));

    }else if(method == "int"){
        // PF = (integrated pulsed flux) / (integrated flux)
        //    = \int{ R_i - R_min } / \int{ R_i }
        //    = (\int{R_i} - N R_min ) / \int{ R_i }
        //    = ( \int_(i!=min){R_i} + (1 - N) R_min ) / ( \int_(i!=min){R_i} + R_min )

        int index_at_min = TMath::LocMin(nbin_1p_, rate_);
        double rate_min     = rate_[index_at_min];
        double rate_min_err = rate_err_[index_at_min];

        double sum = 0.0;
        double sum_nomin = 0.0;
        double sum_nomin_err2 = 0.0;
        for(int ibin = 0; ibin < nbin_1p_; ibin ++){
            sum += rate_[ibin];
            if (ibin != index_at_min){
                sum_nomin += rate_[ibin];
                sum_nomin_err2 += pow(rate_err_[ibin], 2);
            }
        }
   
        pf = (sum - nbin_1p_ * rate_min) / sum;
        pf_err = nbin_1p_ / pow(sum, 2)
            * sqrt( rate_min * rate_min * sum_nomin_err2
                    + pow(sum_nomin * rate_min_err, 2) );
    }else if(method == "rms"){
        // PF = sqrt{ 1/(N - 1) * \int (R_i - R_mean)**2 } / R_mean

        double sum_r1 = 0.0;
        double sum_r2 = 0.0;
        double sum_r2e2 = 0.0;
        double sum_r1e2 = 0.0;
        double sum_r0e2 = 0.0;
        for(int ibin = 0; ibin < nbin_1p_; ibin ++){
            sum_r1   += rate_[ibin];
            sum_r2   += pow(rate_[ibin], 2);
            sum_r2e2 += pow(rate_[ibin] * rate_err_[ibin], 2);
            sum_r1e2 += rate_[ibin] * pow(rate_err_[ibin], 2);
            sum_r0e2 += pow(rate_err_[ibin], 2);
        }

        pf = sqrt(sum_r2 - pow(sum_r1, 2) / nbin_1p_)/ sum_r1
            * nbin_1p_ / sqrt(nbin_1p_ - 1);

        pf_err = sqrt( sum_r1 * sum_r1 * sum_r2e2 - 2 * sum_r1 * sum_r2 * sum_r1e2
                       + sum_r2 * sum_r2 * sum_r0e2 )
            / ( sum_r1 * sum_r1 * sqrt(sum_r2 - sum_r1 * sum_r1 / nbin_1p_) )
            * nbin_1p_ / sqrt(nbin_1p_ - 1);
    }else {
        printf("%s: error: bad method (=%s)\n", func_name.c_str(), method.c_str());
        exit(1);
    }
  
    *pf_ptr = pf;
    *pf_err_ptr = pf_err;
}


//
//void PulseProf::GetPlsFrac(string method, const Interval* const gti_min_phase,
//                           double* const pf_ptr, double* const pf_err_ptr) const
//{
//  // method:
//  // int_min: (integrated pulsed flux) / (integrated flux)
//  //          use bins within the gti_min_phase as the minimum
//
//  string func_name = "PulseProf::GetPlsFrac(method, gti_min_phase, pf_ptr, pf_err_ptr)";
//  
//  double pf = 0.0;
//  double pf_err = 0.0;

if(method == "int_min"){
    // PF = (integrated pulsed flux) / (integrated flux)
    //    = \int{ R_i - R_min } / \int{ R_i }
    //    = (\int{R_i} - N R_min ) / \int{ R_i }
    //    = ( \int_(i!=min){R_i} + (1 - N) R_min ) / ( \int_(i!=min){R_i} + R_min )


    vector<double> rate_for_min;
    vector<double> rate_err_for_min;
    double *index_for_min = new double [nbin_1p_];
    for(int ibin = 0; ibin < nbin_1p_; ibin ++){
        index_for_min[ibin] = 0;
        for(int iterm = 0; iterm < gti_min_phase->GetNterm(); iterm ++){
            if(gti_min_phase->GetTstart()[iterm] <= tbin_[ibin] - tbin_err_[ibin] &&
               tbin_[ibin] + tbin_err_[ibin] <= gti_min_phase->GetTstop()[iterm]){
                rate_for_min.push_back(rate_[ibin]);
                rate_err_for_min.push_back(rate_err_[ibin]);
                index_for_min[ibin] = 1;
                break;
            }
        }
    }

    printf("size of rate_for_min = %d\n", (int) rate_for_min.size());
    printf("size of rate_err_for_min = %d\n", (int) rate_err_for_min.size());
    int nbin_min = rate_for_min.size();
    
    // weighted mean
    double wmean = 0.0;
    double wmean_err = 0.0;
    double num = 0.0;
    double den = 0.0;
    for(int ibin = 0; ibin < nbin_min; ibin ++){
        num += rate_for_min[ibin] / pow(rate_err_for_min[ibin], 2);
        den += 1./ pow(rate_err_for_min[ibin], 2);
    }
    wmean = num/den;
    wmean_err = sqrt(1./den);
    
    double rate_min     = wmean;
    double rate_min_err = wmean_err;
    printf("%s: rate_min = %f +- %f\n", func_name.c_str(), rate_min, rate_min_err);

    double sum = 0.0;
    double sum_nomin = 0.0;
    double sum_nomin_err2 = 0.0;
    for(int ibin = 0; ibin < nbin_1p_; ibin ++){
        sum += rate_[ibin];
        if(index_for_min[ibin] != 1){
            sum_nomin += rate_[ibin];
            sum_nomin_err2 += pow(rate_err_[ibin], 2);
        }
    }
    pf = (sum_nomin + (nbin_min - nbin_1p_) * rate_min)
        / (sum_nomin + nbin_min * rate_min);
    pf_err = nbin_1p_ / pow(sum_nomin + nbin_min * rate_min, 2)
        * sqrt( rate_min * rate_min * sum_nomin_err2
                + pow(sum_nomin * rate_min_err, 2) );
} else {
    printf("%s: error: bad method (=%s)\n", func_name.c_str(), method.c_str());
    exit(1);
}
  
*pf_ptr = pf;
*pf_err_ptr = pf_err;
}




void PulseProf::GetPlsDiff(const PulseProf* const pulseprof,
                           const PulseProf* const pulseprof_template,
                           double *chi2_ptr, double *chi2_red_ptr,
                           double *prob_ptr, int *dof_ptr) const
{
    string func_name = "PulseProf::GetChi2PlsDiff()";
    if(CheckFormatSame(pulseprof, pulseprof_template) != 1){
        printf("%s: error: format of pulseprof and pulseprof_template are different.\n",
               func_name.c_str());
        exit(1);
    }
  
    if(pulseprof->GetRateType() != 2){
        printf("%s: error: bad rate_type (=%d).\n", func_name.c_str(), pulseprof->GetRateType());
        exit(1);
    }

    int nbin_1p = pulseprof->GetNbin1p();

    double chi2 = 0.0;
    for(int ibin = 0; ibin < nbin_1p; ibin ++){
        chi2 += pow(pulseprof->GetRate()[ibin] - pulseprof_template->GetRate()[ibin], 2)/
            ( pow(pulseprof->GetRateErr()[ibin], 2) + pow(pulseprof_template->GetRateErr()[ibin], 2) );
    }
    int dof = nbin_1p;
    double chi2_red = chi2 / dof;
    double prob = TMath::Prob(chi2, dof);

    *chi2_ptr = chi2;
    *chi2_red_ptr = chi2_red;
    *prob_ptr = prob;
    *dof_ptr = dof;
}


void PulseProf::GetPlsDiffByChi2min(const PulseProf* const pulseprof,
                                    const PulseProf* const pulseprof_template,
                                    double *chi2_ptr, double *chi2_red_ptr,
                                    double *prob_ptr, int *dof_ptr,
                                    double *coeff_a_ptr, double *coeff_b_ptr,
                                    double *coeff_a_err_ptr, double *coeff_b_err_ptr,
                                    string method, int *tbin_shift_ptr) const
{
    string func_name = "PulseProf::GetChi2PlsDiff()";
    if(CheckFormatSame(pulseprof, pulseprof_template) != 1){
        printf("%s: error: format of pulseprof and pulseprof_template are different.\n",
               func_name.c_str());
        exit(1);
    }
  
    if(pulseprof->GetRateType() != 2){
        printf("%s: error: bad rate_type (=%d).\n", func_name.c_str(), pulseprof->GetRateType());
        exit(1);
    }

    int nbin = pulseprof->GetNbin1p();
    double *data = new double [nbin];
    double *data_err = new double [nbin];  
    double *temp = new double [nbin];
    for(int ibin = 0; ibin < nbin; ibin ++){
        data[ibin] = pulseprof->GetRate()[ibin];
        data_err[ibin] = pulseprof->GetRateErr()[ibin];    
        temp[ibin] = pulseprof_template->GetRate()[ibin];
    }


    double chi2, chi2_red, prob;
    int dof;
    double coeff_a, coeff_b;
    double coeff_a_err, coeff_b_err;
    int tbin_shift;

    if(method == "phase-fix"){
        LeastSquareDataTemplate(nbin, data, data_err, temp, 
                                &chi2, &chi2_red, &prob, &dof,
                                &coeff_a, &coeff_b,
                                &coeff_a_err, &coeff_b_err);
        tbin_shift = 0;
    } else if (method == "phase-shift"){
        LeastSquareDataTemplate(nbin, data, data_err, temp, 
                                &chi2, &chi2_red, &prob, &dof,
                                &coeff_a, &coeff_b,
                                &coeff_a_err, &coeff_b_err);

        double mergin = 100;
        double chi2_min = chi2 + mergin;
        double chi2_red_min;
        double prob_min;
        double coeff_a_min;
        double coeff_b_min;
        double coeff_a_err_min;
        double coeff_b_err_min;
        int    tbin_shift_min;
        // printf("debug:first: chi2: %f\n", chi2);

        double *temp_shift = new double [nbin];
        for(int ibin_shift = 0; ibin_shift < nbin; ibin_shift ++){
            double chi2_shift, chi2_red_shift, prob_shift;
            double coeff_a_shift, coeff_b_shift;
            double coeff_a_err_shift, coeff_b_err_shift;
            for(int ibin = 0; ibin < nbin; ibin ++){
                temp_shift[ibin] = temp[(ibin + ibin_shift) % nbin];
            }
            LeastSquareDataTemplate(nbin, data, data_err, temp_shift, 
                                    &chi2_shift, &chi2_red_shift, &prob_shift, &dof,
                                    &coeff_a_shift, &coeff_b_shift,
                                    &coeff_a_err_shift, &coeff_b_err_shift);
            if(chi2_shift < chi2_min){
                tbin_shift_min = nbin - ibin_shift;
                chi2_min       = chi2_shift;
                chi2_red_min   = chi2_red_shift;
                prob_min       = prob_shift;
                coeff_a_min    = coeff_a_shift;
                coeff_b_min    = coeff_b_shift;
                coeff_a_err_min = coeff_a_err_shift;
                coeff_b_err_min = coeff_b_err_shift;
            }
            //printf("debug: chi2_shift: %f\n", chi2_shift);
            //printf("debug: chi2_red_min: %f\n", chi2_red_min);
      
        }

        tbin_shift = tbin_shift_min;
        chi2      = chi2_min;
        chi2_red  = chi2_red_min;
        prob      = prob_min;
        coeff_a   = coeff_a_min;
        coeff_b   = coeff_b_min;
        coeff_a_err = coeff_a_err_min;
        coeff_b_err = coeff_b_err_min;

    } else {
        printf("%s: error: bad method (= %s)\n", func_name.c_str(), method.c_str());
        exit(1);
    }
  
    *chi2_ptr = chi2;
    *chi2_red_ptr = chi2_red;
    *prob_ptr = prob;
    *dof_ptr = dof;
    *coeff_a_ptr = coeff_a;
    *coeff_b_ptr = coeff_b;
    *coeff_a_err_ptr = coeff_a_err;
    *coeff_b_err_ptr = coeff_b_err;
    *tbin_shift_ptr = tbin_shift;
}

void PulseProf::LeastSquareDataTemplate(int nbin,
                                        const double* const data,
                                        const double* const data_err,
                                        const double* const temp,
                                        double *chi2_ptr, double *chi2_red_ptr,
                                        double *prob_ptr, int *dof_ptr,
                                        double *coeff_a_ptr, double *coeff_b_ptr,
                                        double *coeff_a_err_ptr, double *coeff_b_err_ptr) const
{
    // this calculation assumes that the error of template is negligible.

    string func_name = "PulseProf::LeastSquareDataTemplate()";
  
    double coeff_a = 0.0; // scale
    double coeff_b = 0.0; // offset
    double coeff_a_err = 0.0;
    double coeff_b_err = 0.0;
  
    double sum_0   = 0.0;
    double sum_t1  = 0.0;
    double sum_t2  = 0.0;
    double sum_d   = 0.0;
    double sum_td  = 0.0;
  
    for(int ibin = 0; ibin < nbin; ibin ++){
        sum_0   += 1./ pow(data_err[ibin], 2);
        sum_t1  += temp[ibin]/ pow(data_err[ibin], 2);
        sum_t2  += pow(temp[ibin], 2)/ pow(data_err[ibin], 2);
        sum_d   += data[ibin]/ pow(data_err[ibin], 2);
        sum_td  += (data[ibin] * temp[ibin])/ pow(data_err[ibin], 2);
    }
    double det = sum_t2 * sum_0 - sum_t1 * sum_t1;

    coeff_a = (sum_0  * sum_td - sum_t1 * sum_d ) / det;
    coeff_b = (sum_t2 * sum_d  - sum_t1 * sum_td) / det;
    coeff_a_err = sqrt(sum_0  / det);
    coeff_b_err = sqrt(sum_t2 / det);


    //printf("debug: %s: coeff_a = %f\n", func_name.c_str(), coeff_a);
    //  printf("debug: %s: coeff_b = %f\n", func_name.c_str(), coeff_b);
//  printf("debug: %s: coeff_a_err = %f\n", func_name.c_str(), coeff_a_err);
    //printf("debug: %s: coeff_b_err = %f\n", func_name.c_str(), coeff_b_err);
  
    double chi2 = 0.0;
    for(int ibin = 0; ibin < nbin; ibin ++){
        chi2 += pow(data[ibin] - (coeff_a * temp[ibin] + coeff_b), 2) / pow(data_err[ibin], 2);
    }
    int dof = nbin - 2;
    double chi2_red = chi2 / dof;
    double prob = TMath::Prob(chi2, dof);
  
    // printf("debug: %s: chi2_red = %f\n", func_name.c_str(), chi2_red);
    
    *chi2_ptr = chi2;
    *chi2_red_ptr = chi2_red;
    *prob_ptr = prob;
    *dof_ptr = dof;
    *coeff_a_ptr = coeff_a;
    *coeff_b_ptr = coeff_b;
    *coeff_a_err_ptr = coeff_a_err;
    *coeff_b_err_ptr = coeff_b_err;
}



*****************/
