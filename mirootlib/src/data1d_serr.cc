#include "mir_data1d_serr.h"

//
// public
//

void DataArraySerr1d::Init(long ndata)
{
    InitDataArray1d(ndata);
    InitDataArraySerr1d(ndata);
}

void DataArraySerr1d::SetValSerr(long ndata,
                                 const double* const val_serr)
{
    if(GetNdata() != ndata){
        MPrintErrClass("GetNdata() != ndata");
        abort();
    }
    IsValSerrNotNull();
    for(long idata = 0; idata < ndata; idata++){
        IsValSerrPlus(val_serr[idata]);
        val_serr_[idata] = val_serr[idata];
    }
}


void DataArraySerr1d::SetValSerr(vector<double> val_serr)
{
    if(GetNdata() != (long) val_serr.size()){
        MPrintErrClass("GetNdata() != val_serr.size()");
        abort();
    }
    IsValSerrNotNull();
    for(long idata = 0; idata < (long) val_serr.size(); idata++){
        IsValSerrPlus(val_serr[idata]);
        val_serr_[idata] = val_serr[idata];
    }
}

void DataArraySerr1d::SetValSerrElm(long idata, double val_serr)
{
    IsValSerrNotNull();
    IsValidRange(idata);
    val_serr_[idata] = val_serr;
}


void DataArraySerr1d::Fill(long idata)
{
    double val_pre = GetValElm(idata);
    double val_new = val_pre + 1.0;
    SetValElm(idata, val_new);
    SetValSerrElm(idata, sqrt(val_new));
    // poisson error    
}

void DataArraySerr1d::Fill(long idata, double weight)
{
    double val_pre = GetValElm(idata);
    double val_new = val_pre + weight;
    SetValElm(idata, val_new);
    SetValSerrElm(idata, sqrt(val_new));
    // poisson error
}

void DataArraySerr1d::FillByMax(long idata,
                                double val,
                                double val_serr)
{
    double val_pre = GetValElm(idata);
    if(val_pre < val){
        SetValElm(idata, val);
        SetValSerrElm(idata, val_serr);
    }
}


void DataArraySerr1d::FillByMin(long idata,
                                double val,
                                double val_serr)
{
    double val_pre = GetValElm(idata);
    if(val_pre > val){
        SetValElm(idata, val);
        SetValSerrElm(idata, val_serr);
    }
}

void DataArraySerr1d::SetConst(double constant)
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, constant);
        SetValSerrElm(idata, sqrt(constant));
    }
}

void DataArraySerr1d::SetValErrByPoissonErr()
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        double val = GetValElm(idata);
        SetValSerrElm(idata, sqrt(val));
    }
}

DataArraySerr1d* const DataArraySerr1d::Clone() const
{
    DataArraySerr1d* obj_new = new DataArraySerr1d;
    obj_new->Copy(this);
    return obj_new;
}


void DataArraySerr1d::Load(string file)
{
    NullDataArray1d();
    NullDataArraySerr1d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
        if(2 != ncolumn){
            MPrintWarnClass("ncolumn != 2");
        }
        istringstream iss(line_arr[idata]);
        double val_tmp;
        double val_serr_tmp;
        iss >> val_tmp >> val_serr_tmp;
        SetValElm(idata, val_tmp);
        SetValSerrElm(idata, val_serr_tmp);
    }
    MiIolib::DelReadFile(line_arr);

    int flag_val_sorted = 0;
    ReadInfo(file, &flag_val_sorted);
    SetFlagValSorted(flag_val_sorted);
}

double DataArraySerr1d::GetValSerrElm(long idata) const
{
    IsValidRange(idata);
    return val_serr_[idata];
}

// output

void DataArraySerr1d::PrintData(FILE* fp, int mode,
                                double offset_val) const
{
    long ndata = GetNdata();
    if(0 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.10e  %.10e\n",
                    GetValElm(idata) - offset_val,
                    GetValSerrElm(idata));
        }
    } else if (1 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%ld   %.10e  %.10e\n",
                    idata,
                    GetValElm(idata) - offset_val,
                    GetValSerrElm(idata));
        }
    } else if (2 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.10e  %.10e  1.0\n",
                    GetValElm(idata) - offset_val,
                    GetValSerrElm(idata));
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad mode (=%d).", mode);
        MPrintErrClass(msg);
        abort();
    }
}

double DataArraySerr1d::GetOffsetValFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetValAndErrMin();
    } else if ("ed" == offset_tag){
        offset = GetValAndErrMax();
    } else if ("md" == offset_tag){
        offset = ( GetValAndErrMin() + GetValAndErrMax() ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

//
// private
//


void DataArraySerr1d::NullDataArraySerr1d()
{
    if(NULL != val_serr_) {delete [] val_serr_; val_serr_ = NULL;}
}


void DataArraySerr1d::InitDataArraySerr1d(long ndata)
{
    NullDataArraySerr1d();
    if(GetNdata() != ndata){
        MPrintErrClass("GetNdata() != ndata");
        abort();
    }
    val_serr_ = new double [ndata];
    for(long idata = 0; idata < ndata; idata++){
        val_serr_[idata] = 0.0;
    }
}

void DataArraySerr1d::IsValSerrNotNull() const
{
    if(NULL == GetValSerr()){
        MPrintErrClass("bad GetValSerr() (=NULL)");
        abort();
    }
}

void DataArraySerr1d::IsValSerrPlus(double val_serr) const
{
    if(val_serr < 0.0){
        char msg[kLineSize];
        sprintf(msg, "val_serr(=%e) < 0.0", val_serr);
        MPrintErr(msg);
        abort();
    }
}
