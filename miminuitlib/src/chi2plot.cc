#include "mim_chi2plot.h"

//
// Chi2PlotPar
//

void Chi2PlotPar::Null()
{
    if(NULL != index_)  {delete [] index_; index_ = NULL;}
    if(NULL != nstep_)  {delete [] nstep_; nstep_ = NULL;}
    if(NULL != lo_str_) {delete [] lo_str_; lo_str_ = NULL;}
    if(NULL != up_str_) {delete [] up_str_; up_str_ = NULL;}
    if(NULL != sigma_str_) {delete [] sigma_str_; sigma_str_ = NULL;}
    if(NULL != index1_str_) {delete [] index1_str_; index1_str_ = NULL;}
    if(NULL != num_index1_) {delete [] num_index1_; num_index1_ = NULL;}
    if(NULL != index1_arr_) {
        for(int ipar = 0; ipar < npar_; ipar ++){
            delete [] index1_arr_[ipar]; index1_arr_[ipar] = NULL;
        }
        delete [] index1_arr_; index1_arr_ = NULL;
    }
    npar_ = 0;
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void Chi2PlotPar::Init(int npar)
{
    Null();
    
    npar_ = npar;
    index_      = new int [npar_];
    nstep_      = new int [npar_];
    lo_str_     = new string [npar_];
    up_str_     = new string [npar_];
    sigma_str_  = new string [npar_];
    index1_str_ = new string [npar_];
    num_index1_ = new int [npar_];
    index1_arr_ = new int* [npar_];
    for(int ipar = 0; ipar < npar_; ipar ++){
        index_[ipar]      = 0;
        nstep_[ipar]      = 0;
        lo_str_[ipar]     = "";
        up_str_[ipar]     = "";
        sigma_str_[ipar]  = "";
        index1_str_[ipar] = "";
        num_index1_[ipar] = 0;
        index1_arr_[ipar] = NULL;
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void Chi2PlotPar::SetDataElm(int ipar, int index, int nstep, string lo_str, string up_str,
                             string sigma_str, string index1_str)
{
    // check lo_str, up_str, & sigma_str
    IsValidLoUpSigmaStr(lo_str, up_str, sigma_str);
    // then, only the following two cases are valid.
    // lo_str_ == "none", up_str_ == "none", sigma_str_ != "none"
    // lo_str_ != "none", up_str_ != "none", sigma_str_ == "none"
    
    index_[ipar]      = index;
    nstep_[ipar]      = nstep;
    lo_str_[ipar]     = lo_str;
    up_str_[ipar]     = up_str;
    sigma_str_[ipar]  = sigma_str;
    index1_str_[ipar] = index1_str;

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void Chi2PlotPar::Load(string file)
{
    Null();
    
    string* line_arr = NULL;
    long npar_long = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &npar_long);
    int npar = (int) npar_long;
    Init(npar);
    for(int ipar = 0; ipar < npar; ipar ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[ipar]);
        if(6 != ncolumn){
            MPrintWarnClass("ncolumn != 6");
        }
        istringstream iss(line_arr[ipar]);
        int index_tmp, nstep_tmp;        
        string lo_str_tmp, up_str_tmp, sigma_str_tmp, index1_str_tmp;
        iss >> index_tmp >> nstep_tmp >> lo_str_tmp >> up_str_tmp >> sigma_str_tmp >> index1_str_tmp;
        SetDataElm(ipar, index_tmp, nstep_tmp, lo_str_tmp, up_str_tmp, sigma_str_tmp, index1_str_tmp);
    }
    MiIolib::DelReadFile(line_arr);

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void Chi2PlotPar::SetLoUpSigmaByFitStat(const FitStat* const fit_stat)
{
    const FitParam* const fit_param = fit_stat->GetFitParam();
    
    for(int ipar = 0; ipar < GetNpar(); ipar++){
        if("none" == GetLoStrElm(ipar) &&
           "none" == GetUpStrElm(ipar) &&
           "none" != GetSigmaStrElm(ipar) ){

            int index    = GetIndexElm(ipar);
            double sigma = atof(GetSigmaStrElm(ipar).c_str());

            string lo_str = "";
            string up_str = "";
            string sigma_str = "";
            GetLoUpSigmaStrByFitParam(fit_param, index, sigma,
                                      &lo_str, &up_str, &sigma_str);
            lo_str_[ipar] = lo_str;
            up_str_[ipar] = up_str;
            sigma_str_[ipar] = sigma_str;
        }
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void Chi2PlotPar::SetIndex1Arr(const FitParam* const fit_param)
{
    printf("debug: GetNpar() = %d\n", GetNpar());
    
    for(int ipar = 0; ipar < GetNpar(); ipar ++){

        printf("debug: index1_str_[ipar] = %s\n", index1_str_[ipar].c_str());
        
        if("none" == index1_str_[ipar]){
            num_index1_[ipar] = 0;
        } else if ("all" == index1_str_[ipar]){
            int num_index1 = fit_param->GetNpar();
            num_index1_[ipar] = num_index1;
            index1_arr_[ipar] = new int [num_index1];
            for(int inum = 0; inum < num_index1; inum ++){
                index1_arr_[ipar][inum] = inum;
            }
        } else if ("others" == index1_str_[ipar]){
            int num_index1 = fit_param->GetNpar() - 1;
            num_index1_[ipar] = num_index1;
            index1_arr_[ipar] = new int [num_index1];

            int inum = 0;
            int npar_fit_param = fit_param->GetNpar();
            for(int ipar_fit_param = 0; ipar_fit_param < npar_fit_param; ipar_fit_param ++){
                if(index_[ipar] != ipar_fit_param){
                    index1_arr_[ipar][inum] = ipar_fit_param;
                    inum ++;
                }
            }
        } else if ("all_free" == index1_str_[ipar]){
            int num_index1 = fit_param->GetNparFree();
            num_index1_[ipar] = num_index1;
            index1_arr_[ipar] = new int [num_index1];

            int inum = 0;
            int npar_fit_param = fit_param->GetNpar();
            for(int ipar_fit_param = 0; ipar_fit_param < npar_fit_param; ipar_fit_param ++){
                if(fit_param->GetParSerrInitElm(ipar_fit_param) >= 0){
                    index1_arr_[ipar][inum] = ipar_fit_param;
                    inum ++;
                }
            }
        } else if ("others_free" == index1_str_[ipar]){
            int inum = 0;
            int npar_fit_param = fit_param->GetNpar();

            printf("debug: others_free npar_fit_param = %d\n", npar_fit_param);

            
            for(int ipar_fit_param = 0; ipar_fit_param < npar_fit_param; ipar_fit_param ++){
                if(fit_param->GetParSerrInitElm(ipar_fit_param) >= 0 &&
                   index_[ipar] != ipar_fit_param){
                    inum ++;
                }
            }
            int num_index1 = inum;
            num_index1_[ipar] = num_index1;
            index1_arr_[ipar] = new int [num_index1];

            inum = 0;
            for(int ipar_fit_param = 0; ipar_fit_param < npar_fit_param; ipar_fit_param ++){
                if(fit_param->GetParSerrInitElm(ipar_fit_param) >= 0 &&
                   index_[ipar] != ipar_fit_param){
                    index1_arr_[ipar][inum] = ipar_fit_param;
                    inum ++;
                }
            }
        } else {
            // split index1_str
            int nsplit = 0;
            string* split_arr = NULL;
            MiStr::GenSplit(index1_str_[ipar], &nsplit, &split_arr, ",");
            if(nsplit < 1){
                MPrintErrClass("bad.");
                abort();
            }
            num_index1_[ipar] = nsplit;
            index1_arr_[ipar] = new int [nsplit];
            for(int isplit = 0; isplit < nsplit; isplit ++){
                index1_arr_[ipar][isplit] = atoi(split_arr[isplit].c_str());
            }
            delete [] split_arr; split_arr = NULL;
        }
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void Chi2PlotPar::Copy(const Chi2PlotPar* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}

    CopyTitle(org);
    
    Null();
    npar_   = org->npar_;
    index_  = new int [npar_];
    nstep_  = new int [npar_];
    lo_str_ = new string [npar_];
    up_str_ = new string [npar_];
    sigma_str_  = new string [npar_];
    index1_str_ = new string [npar_];
    num_index1_ = new int [npar_];
    index1_arr_ = new int* [npar_];
    
    for(int ipar = 0; ipar < npar_; ipar ++){
        index_[ipar]  = org->index_[ipar];
        nstep_[ipar]  = org->nstep_[ipar];
        lo_str_[ipar] = org->lo_str_[ipar];
        up_str_[ipar] = org->up_str_[ipar];
        sigma_str_[ipar] = org->sigma_str_[ipar];
        
        index1_str_[ipar] = org->index1_str_[ipar];
        num_index1_[ipar] = org->num_index1_[ipar];

        if(1 > num_index1_[ipar]){
            index1_arr_[ipar] = NULL;
        } else {
            index1_arr_[ipar] = new int [ num_index1_[ipar] ];
            for(int inum = 0; inum < num_index1_[ipar]; inum ++){
                index1_arr_[ipar][inum] = org->index1_arr_[ipar][inum];
            }
        }
    }
    
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

Chi2PlotPar* const Chi2PlotPar::Clone() const
{
    Chi2PlotPar* obj_new = new Chi2PlotPar;
    obj_new->Copy(this);
    return obj_new;
}

void Chi2PlotPar::Print(FILE* fp) const
{
    char prompt[kLineSize];
    sprintf(prompt, "%s::%s: %s",
            GetClassName().c_str(), __func__, GetTitle().c_str());
    fprintf(fp, "%s: npar_ : %d\n", prompt, npar_);
    fprintf(fp, "%s: ipar: index   nstep  low   up  sigma  index1 \n",
            prompt);
    for(int ipar = 0; ipar < npar_; ipar++){
        fprintf(fp, "%s: %d:  %d  %d  %s  %s  %s  ! %s\n",
                prompt,
                ipar, index_[ipar], nstep_[ipar],
                lo_str_[ipar].c_str(), up_str_[ipar].c_str(), sigma_str_[ipar].c_str(),
                index1_str_[ipar].c_str());
    }
}

double Chi2PlotPar::GetStepElm(int ipar) const
{
    if("none" == lo_str_[ipar] ||
       "none" == up_str_[ipar]  ){
        MPrintErrClass("bad.");
        abort();
    }
    double lo = atof(lo_str_[ipar].c_str());
    double up = atof(up_str_[ipar].c_str());
    double step = (up - lo) / nstep_[ipar];
    return step;
}


double Chi2PlotPar::GetParVal(int ipar, int istep) const
{
    if("none" == lo_str_[ipar] ||
       "none" == up_str_[ipar]  ){
        MPrintErrClass("bad.");
        abort();
    }
    double lo = atof(lo_str_[ipar].c_str());
    double step = GetStepElm(ipar);
    double val = lo + (istep + 0.5) * step;
    return val;
}


int Chi2PlotPar::IsValidLoUpSigmaStr(string lo_str, string up_str, string sigma_str)
{
    int retval = 1;
    
    if("none" == lo_str &&
       "none" == up_str   ) {
        if("none" == sigma_str){
            MPrintErr("bad.");
            abort();
        }
    } else if ("none" != lo_str &&
               "none" != up_str   ) {
        if("none" != sigma_str){
            MPrintErr("bad.");
            abort();
        }
    } else {
        MPrintErr("bad.");
        abort();
    }
    return retval;
}


void Chi2PlotPar::GetLoUpSigmaStrByFitParam(const FitParam* const fit_param, int index, double sigma,
                                            string* lo_str_ptr, string* up_str_ptr, string* sigma_str_ptr)
{
    if( sigma < DBL_EPSILON ){
        MPrintErr("bad.");
        abort();
    }
    
    double par     = fit_param->GetParElm( index );
    double par_err = fit_param->GetParSerrElm( index );
    if(par_err < DBL_EPSILON){
        MPrintErr("bad.");
        abort();
    }
    double lo = par - par_err * sigma;
    double up = par + par_err * sigma;
    if("none" != fit_param->GetParLoStrElm( index ) &&
       "none" != fit_param->GetParUpStrElm( index )   ){
        double lo_limit = atof(fit_param->GetParLoStrElm( index ).c_str());
        double up_limit = atof(fit_param->GetParUpStrElm( index ).c_str());
        if( lo < lo_limit){
            lo = lo_limit;
        }
        if( up > up_limit){
            up = up_limit;
        }
    }
    char lo_char[kLineSize];
    char up_char[kLineSize];
    sprintf(lo_char, "%e", lo);
    sprintf(up_char, "%e", up);

    string lo_str = lo_char;
    string up_str = up_char;
    string sigma_str = "none";

    *lo_str_ptr = lo_str;
    *up_str_ptr = up_str;
    *sigma_str_ptr = sigma_str;
}



//
// Chi2PlotContPar
//

void Chi2PlotContPar::Null()
{
    if(NULL != index0_)     {delete [] index0_;     index0_     = NULL;}
    if(NULL != nstep0_)     {delete [] nstep0_;     nstep0_     = NULL;}
    if(NULL != lo0_str_)    {delete [] lo0_str_;    lo0_str_    = NULL;}
    if(NULL != up0_str_)    {delete [] up0_str_;    up0_str_    = NULL;}
    if(NULL != sigma0_str_) {delete [] sigma0_str_; sigma0_str_ = NULL;}

    if(NULL != index1_)     {delete [] index1_;     index1_     = NULL;}
    if(NULL != nstep1_)     {delete [] nstep1_;     nstep1_     = NULL;}
    if(NULL != lo1_str_)    {delete [] lo1_str_;    lo1_str_    = NULL;}
    if(NULL != up1_str_)    {delete [] up1_str_;    up1_str_    = NULL;}
    if(NULL != sigma1_str_) {delete [] sigma1_str_; sigma1_str_ = NULL;}
    
    if(NULL != index2_str_) {delete [] index2_str_; index2_str_ = NULL;}
    if(NULL != num_index2_) {delete [] num_index2_; num_index2_ = NULL;}
    if(NULL != index2_arr_) {
        for(int icont = 0; icont < ncont_; icont ++){
            delete [] index2_arr_[icont]; index2_arr_[icont] = NULL;
        }
        delete [] index2_arr_; index2_arr_ = NULL;
    }
    ncont_ = 0;    
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void Chi2PlotContPar::Init(int ncont)
{
    Null();
    
    ncont_ = ncont;
    index0_     = new int [ncont_];
    nstep0_     = new int [ncont_];
    lo0_str_    = new string [ncont_];
    up0_str_    = new string [ncont_];
    sigma0_str_ = new string [ncont_];

    index1_     = new int [ncont_];
    nstep1_     = new int [ncont_];
    lo1_str_    = new string [ncont_];
    up1_str_    = new string [ncont_];
    sigma1_str_ = new string [ncont_];

    index2_str_ = new string [ncont_];
    num_index2_ = new int [ncont_];
    index2_arr_ = new int* [ncont_];

    for(int icont = 0; icont < ncont_; icont ++){
        index0_[icont]     = 0;
        nstep0_[icont]     = 0;
        lo0_str_[icont]    = "";
        up0_str_[icont]    = "";
        sigma0_str_[icont] = "";

        index1_[icont]     = 0;
        nstep1_[icont]     = 0;
        lo1_str_[icont]    = "";
        up1_str_[icont]    = "";
        sigma1_str_[icont] = "";

        index2_str_[icont] = "";
        num_index2_[icont] = 0;
        index2_arr_[icont] = NULL;
    }
    
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Chi2PlotContPar::SetDataElm(int icont,
                                 int index0, int nstep0, string lo0_str, string up0_str, string sigma0_str,
                                 int index1, int nstep1, string lo1_str, string up1_str, string sigma1_str,
                                 string index2_str)
{

    // check lo_str, up_str, & sigma_str
    Chi2PlotPar::IsValidLoUpSigmaStr(lo0_str, up0_str, sigma0_str);
    Chi2PlotPar::IsValidLoUpSigmaStr(lo1_str, up1_str, sigma1_str);
    // then, only the following two cases are valid.
    // lo_str_ == "none", up_str_ == "none", sigma_str_ != "none"
    // lo_str_ != "none", up_str_ != "none", sigma_str_ == "none"

    index0_[icont]     = index0;
    nstep0_[icont]     = nstep0;
    lo0_str_[icont]    = lo0_str;
    up0_str_[icont]    = up0_str;
    sigma0_str_[icont] = sigma0_str;

    index1_[icont]     = index1;
    nstep1_[icont]     = nstep1;
    lo1_str_[icont]    = lo1_str;  
    up1_str_[icont]    = up1_str;
    sigma1_str_[icont] = sigma1_str;
    index2_str_[icont] = index2_str;

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Chi2PlotContPar::Load(string file)
{
    Null();
    
    string* line_arr = NULL;
    long ncont_long = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ncont_long);
    int ncont = (int) ncont_long;
    Init(ncont);
    for(int icont = 0; icont < ncont; icont ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[icont]);
        if(11 != ncolumn){
            MPrintWarnClass("ncolumn != 11");
        }
        istringstream iss(line_arr[icont]);
        int index0_tmp, nstep0_tmp;
        string lo0_str_tmp, up0_str_tmp, sigma0_str_tmp;
        int index1_tmp, nstep1_tmp;
        string lo1_str_tmp, up1_str_tmp, sigma1_str_tmp;
        string index2_str_tmp;
        iss >> index0_tmp >> nstep0_tmp >> lo0_str_tmp >> up0_str_tmp >> sigma0_str_tmp
            >> index1_tmp >> nstep1_tmp >> lo1_str_tmp >> up1_str_tmp >> sigma1_str_tmp
            >> index2_str_tmp;
        SetDataElm(icont,
                   index0_tmp, nstep0_tmp, lo0_str_tmp, up0_str_tmp, sigma0_str_tmp,
                   index1_tmp, nstep1_tmp, lo1_str_tmp, up1_str_tmp, sigma1_str_tmp,
                   index2_str_tmp);
    }
    MiIolib::DelReadFile(line_arr);

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Chi2PlotContPar::SetLoUpSigmaByFitStat(const FitStat* const fit_stat)
{
    const FitParam* const fit_param = fit_stat->GetFitParam();

    for(int icont = 0; icont < ncont_; icont++){
        if("none" == GetLo0StrElm(icont) &&
           "none" == GetUp0StrElm(icont) &&
           "none" != GetSigma0StrElm(icont) ){

            int index0    = GetIndex0Elm(icont);
            double sigma0 = atof(GetSigma0StrElm(icont).c_str());
            
            string lo0_str = "";
            string up0_str = "";
            string sigma0_str = "";
            Chi2PlotPar::GetLoUpSigmaStrByFitParam(fit_param, index0, sigma0,
                                                   &lo0_str, &up0_str, &sigma0_str);
            lo0_str_[icont]    = lo0_str;
            up0_str_[icont]    = up0_str;
            sigma0_str_[icont] = sigma0_str;
        }

        if("none" == GetLo1StrElm(icont) &&
           "none" == GetUp1StrElm(icont) &&
           "none" != GetSigma1StrElm(icont) ){

            int index1    = GetIndex1Elm(icont);
            double sigma1 = atof(GetSigma1StrElm(icont).c_str());
            
            string lo1_str = "";
            string up1_str = "";
            string sigma1_str = "";
            Chi2PlotPar::GetLoUpSigmaStrByFitParam(fit_param, index1, sigma1,
                                                   &lo1_str, &up1_str, &sigma1_str);
            lo1_str_[icont]    = lo1_str;
            up1_str_[icont]    = up1_str;
            sigma1_str_[icont] = sigma1_str;
        }
    }
}

void Chi2PlotContPar::SetIndex2Arr(const FitParam* const fit_param)
{
    for(int icont = 0; icont < GetNcont(); icont ++){
    
        if("none" == index2_str_[icont]){
            num_index2_[icont] = 0;
        } else if ("all" == index2_str_[icont]){
            int num_index2 = fit_param->GetNpar();
            num_index2_[icont] = num_index2;
            index2_arr_[icont] = new int [num_index2];
            for(int inum = 0; inum < num_index2; inum ++){
                index2_arr_[icont][inum] = inum;
            }
        } else if ("others" == index2_str_[icont]){
            int num_index2 = fit_param->GetNpar() - 1;
            num_index2_[icont] = num_index2;
            index2_arr_[icont] = new int [num_index2];

            int inum = 0;
            int npar_fit_param = fit_param->GetNpar();
            for(int ipar_fit_param = 0; ipar_fit_param < npar_fit_param; ipar_fit_param ++){
                if(index0_[icont] != ipar_fit_param &&
                   index1_[icont] != ipar_fit_param   ){
                    index2_arr_[icont][inum] = ipar_fit_param;
                    inum ++;
                }
            }
        } else if ("all_free" == index2_str_[icont]){
            int num_index2 = fit_param->GetNparFree();
            num_index2_[icont] = num_index2;
            index2_arr_[icont] = new int [num_index2];

            int inum = 0;
            int npar_fit_param = fit_param->GetNpar();
            for(int ipar_fit_param = 0; ipar_fit_param < npar_fit_param; ipar_fit_param ++){
                if(fit_param->GetParSerrInitElm(ipar_fit_param) >= 0){
                    index2_arr_[icont][inum] = ipar_fit_param;
                    inum ++;
                }
            }
        } else if ("others_free" == index2_str_[icont]){
            int inum = 0;
            int npar_fit_param = fit_param->GetNpar();
            for(int ipar_fit_param = 0; ipar_fit_param < npar_fit_param; ipar_fit_param ++){
                if(fit_param->GetParSerrInitElm(ipar_fit_param) >= 0 &&
                   index0_[icont] != ipar_fit_param &&
                   index1_[icont] != ipar_fit_param   ){
                    inum ++;
                }
            }
            int num_index2 = inum;
            num_index2_[icont] = num_index2;
            index2_arr_[icont] = new int [num_index2];

            inum = 0;
            for(int ipar_fit_param = 0; ipar_fit_param < npar_fit_param; ipar_fit_param ++){
                if(fit_param->GetParSerrInitElm(ipar_fit_param) >= 0 &&
                   index0_[icont] != ipar_fit_param &&
                   index1_[icont] != ipar_fit_param   ){
                    index2_arr_[icont][inum] = ipar_fit_param;
                    inum ++;
                }
            }
        } else {
            // split index2_str
            int nsplit = 0;
            string* split_arr = NULL;
            MiStr::GenSplit(index2_str_[icont], &nsplit, &split_arr, ",");
            if(nsplit < 1){
                MPrintErrClass("bad.");
                abort();
            }
            num_index2_[icont] = nsplit;
            index2_arr_[icont] = new int [nsplit];
            for(int isplit = 0; isplit < nsplit; isplit ++){
                index2_arr_[icont][isplit] = atoi(split_arr[isplit].c_str());
            }
            delete [] split_arr; split_arr = NULL;
        }
    }
    
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void Chi2PlotContPar::Copy(const Chi2PlotContPar* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}

    CopyTitle(org);

    Null();
    ncont_   = org->ncont_;
    index0_     = new int [ncont_];
    nstep0_     = new int [ncont_];
    lo0_str_    = new string [ncont_];
    up0_str_    = new string [ncont_];
    sigma0_str_ = new string [ncont_];

    index1_     = new int [ncont_];
    nstep1_     = new int [ncont_];
    lo1_str_    = new string [ncont_];
    up1_str_    = new string [ncont_];
    sigma1_str_ = new string [ncont_];

    index2_str_ = new string [ncont_];
    num_index2_ = new int [ncont_];
    index2_arr_ = new int* [ncont_];

    for(int icont = 0; icont < ncont_; icont ++){
        index0_[icont]     = org->index0_[icont];
        nstep0_[icont]     = org->nstep0_[icont];
        lo0_str_[icont]    = org->lo0_str_[icont];
        up0_str_[icont]    = org->up0_str_[icont];
        sigma0_str_[icont] = org->sigma0_str_[icont];

        index1_[icont]     = org->index1_[icont];
        nstep1_[icont]     = org->nstep1_[icont];
        lo1_str_[icont]    = org->lo1_str_[icont];
        up1_str_[icont]    = org->up1_str_[icont];
        sigma1_str_[icont] = org->sigma1_str_[icont];        

        index2_str_[icont] = org->index2_str_[icont];
        num_index2_[icont] = org->num_index2_[icont];
        
        if(1 > num_index2_[icont]){
            index2_arr_[icont] = NULL;
        } else {
            index2_arr_[icont] = new int [ num_index2_[icont] ];
            for(int inum = 0; inum < num_index2_[icont]; inum ++){
                index2_arr_[icont][inum] = org->index2_arr_[icont][inum];
            }
        }
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

Chi2PlotContPar* const Chi2PlotContPar::Clone() const
{
    Chi2PlotContPar* obj_new = new Chi2PlotContPar;
    obj_new->Copy(this);
    return obj_new;
}


void Chi2PlotContPar::Print(FILE* fp) const
{
    char prompt[kLineSize];
    sprintf(prompt, "%s::%s: %s",
            GetClassName().c_str(), __func__, GetTitle().c_str());
    fprintf(fp, "%s: ncont_ : %d\n", prompt, ncont_);
    fprintf(fp, "%s: icont: index0   nstep0  low0   up0  sigma0       "
            "index1   nstep1  low1   up1  sigma1      index2\n",
            prompt);
    for(int icont = 0; icont < ncont_; icont++){
        fprintf(fp, "%s: %d:  %d  %d   %s %s %s      %d  %d   %s %s %s    %s\n",
                prompt, icont,
                index0_[icont], nstep0_[icont],
                lo0_str_[icont].c_str(), up0_str_[icont].c_str(), sigma0_str_[icont].c_str(),
                index1_[icont], nstep1_[icont],
                lo1_str_[icont].c_str(), up1_str_[icont].c_str(), sigma1_str_[icont].c_str(),
                index2_str_[icont].c_str());
    }
}


double Chi2PlotContPar::GetStep0Elm(int icont) const
{
    if("none" == lo0_str_[icont] ||
       "none" == up0_str_[icont]  ){
        MPrintErrClass("bad.");
        abort();
    }
    double lo = atof(lo0_str_[icont].c_str());
    double up = atof(up0_str_[icont].c_str());
    double step = (up - lo) / nstep0_[icont];
    return step;
}

double Chi2PlotContPar::GetStep1Elm(int icont) const
{
    if("none" == lo1_str_[icont] ||
       "none" == up1_str_[icont]  ){
        MPrintErrClass("bad.");
        abort();
    }
    double lo = atof(lo1_str_[icont].c_str());
    double up = atof(up1_str_[icont].c_str());
    double step = (up - lo) / nstep1_[icont];
    return step;

}

double Chi2PlotContPar::GetPar0Val(int icont, int istep) const
{
    if("none" == lo0_str_[icont] ||
       "none" == up0_str_[icont]  ){
        MPrintErrClass("bad.");
        abort();
    }
    double lo = atof(lo0_str_[icont].c_str());
    double step = GetStep0Elm(icont);
    double val = lo + (istep + 0.5) * step;
    return val;
}

double Chi2PlotContPar::GetPar1Val(int icont, int istep) const
{
    if("none" == lo1_str_[icont] ||
       "none" == up1_str_[icont]  ){
        MPrintErrClass("bad.");
        abort();
    }
    double lo = atof(lo1_str_[icont].c_str());
    double step = GetStep1Elm(icont);
    double val = lo + (istep + 0.5) * step;
    return val;
}
