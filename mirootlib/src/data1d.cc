#include "mir_data1d.h"

//
// public
//

void DataArray1d::SetVal(long ndata, const double* const val)
{
    if(GetNdata() != ndata){
        MPrintErrClass("GetNdata() != ndata");
        abort();
    }
    IsValNotNull();
    for(long idata = 0; idata < GetNdata(); idata++){
        val_[idata] = val[idata];
    }
}


void DataArray1d::SetVal(vector<double> val)
{
    if(GetNdata() != (long) val.size()){
        MPrintErrClass("GetNdata() != val.size()");
        abort();
    }
    IsValNotNull();    
    for(long idata = 0; idata < GetNdata(); idata++){
        val_[idata] = val[idata];
    }
}

void DataArray1d::SetValElm(long idata, double val)
{
    IsValNotNull();
    IsValidRange(idata);
    val_[idata] = val;
}

void DataArray1d::Copy(const DataArray1d* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}

    CopyTitle(org);
    Init(org->GetNdata());
    SetFlagValSorted(org->GetFlagValSorted());
    if("DataArrayNerr1d" == GetClassName()){
      //SetVal(org->GetNdata(), org->GetVal());
        SetVal(org->GetVal());
    } else if("DataArraySerr1d" == GetClassName()){
        if("DataArrayNerr1d" == org->GetClassName()){
	  //SetVal(org->GetNdata(), org->GetVal());
            SetVal(org->GetVal());
            SetValErrByPoissonErr();
        } else if("DataArraySerr1d" == org->GetClassName()){
	  //SetVal(org->GetNdata(), org->GetVal());
            SetVal(org->GetVal());
            SetValSerr(org->GetNdata(), org->GetValSerr());
        } else if("DataArrayTerr1d" == org->GetClassName()){
	  //SetVal(org->GetNdata(), org->GetVal());
            SetVal(org->GetVal());
            double* val_serr = org->GenValSerr();
            SetValSerr(org->GetNdata(), val_serr);
            delete [] val_serr;
        }
    } else if("DataArrayTerr1d" == GetClassName()){
        if("DataArrayNerr1d" == org->GetClassName()){
	  //SetVal(org->GetNdata(), org->GetVal());
            SetVal(org->GetVal());
            SetValErrByPoissonErr();
        } else if("DataArraySerr1d" == org->GetClassName()){
	  //SetVal(org->GetNdata(), org->GetVal());
            SetVal(org->GetVal());
            SetValTerr(org->GetNdata(), org->GetValSerr());
        } else if("DataArrayTerr1d" == org->GetClassName()){
	  //SetVal(org->GetNdata(), org->GetVal());
            SetVal( org->GetVal());
            SetValTerr(org->GetNdata(),
                       org->GetValTerrPlus(),
                       org->GetValTerrMinus());
        }
    }
}

double DataArray1d::GetValElm(long idata) const
{
    IsValidRange(idata);
    return val_[idata];
}


// statistic

double DataArray1d::GetValMin() const
{
    // double ans = MirMath::GetMin(GetNdata(), GetVal());
    double ans = MirMath::GetMin(GetVal());
    return ans;
}

double DataArray1d::GetValMax() const
{
    //double ans = MirMath::GetMax(GetNdata(), GetVal());
    double ans = MirMath::GetMax(GetVal());
    return ans;
}

long DataArray1d::GetLocValMin() const
{
  //long ans = MirMath::GetLocMin(GetNdata(), GetVal());
    long ans = MirMath::GetLocMin(GetVal());
    return ans;
}

long DataArray1d::GetLocValMax() const
{
  //long ans = MirMath::GetLocMax(GetNdata(), GetVal());
    long ans = MirMath::GetLocMax(GetVal());
    return ans;
}

void DataArray1d::Save(string outfile, int mode, double offset_val) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintInfo(fp);
    PrintData(fp, mode, offset_val);
    fclose(fp);
}

void DataArray1d::SaveData(string outfile, int mode, double offset_val) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintData(fp, mode, offset_val);
    fclose(fp);
}

void DataArray1d::PrintInfo(FILE* fp) const
{
    fprintf(fp, "#\n");
    //    fprintf(fp, "# ndata_           = %ld\n", ndata_);
    fprintf(fp, "# val_.size()      = %ld\n", val_.size());
    fprintf(fp, "# flag_val_sorted_ = %d\n", flag_val_sorted_);
    fprintf(fp, "#\n");
    fprintf(fp, "\n");
}

int DataArray1d::IsAllOne() const
{
    int all_one = 1;
    for(long idata = 0; idata < GetNdata(); idata++){
        if(1 != GetValElm(idata)){
            all_one = 0;
            break;
        }
    }
    return all_one;
}

// offset_tag = "st", "md", "ed", "no", value
double DataArray1d::GetOffsetIndexFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = 0.0;
    } else if ("ed" == offset_tag){
        offset = GetNdata();
    } else if ("md" == offset_tag){
        offset = GetNdata()/2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

//
// static
//

void DataArray1d::ReadInfo(string file, int* flag_val_sorted_ptr)
{
    int flag_val_sorted = 0;
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileComment(file, &line_arr, &ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(line_arr[idata], &ncolumn, &split_arr);
        if(4 != ncolumn){
            continue;
        }
        if("flag_val_sorted_" == split_arr[1]){
            flag_val_sorted = atoi(split_arr[3].c_str());
        }
        delete [] split_arr;
    }
    MiIolib::DelReadFile(line_arr);

    *flag_val_sorted_ptr = flag_val_sorted;
}

//
// protected
//

void DataArray1d::NullDataArray1d()
{
    //ndata_ = 0;
    // if(NULL != val_) {delete [] val_; val_ = NULL;}
    val_.clear();
    val_.shrink_to_fit();
    flag_val_sorted_ = 0;
}

void DataArray1d::InitDataArray1d(long ndata)
{
    NullDataArray1d();
    //ndata_ = ndata;
    //val_ = new double [ndata_];
    val_.resize(ndata);
    for(long idata = 0; idata < ndata; idata++){
        val_[idata] = 0.0;
    }
    flag_val_sorted_ = 0;
}

void DataArray1d::IsValNotNull() const
{
  //    if(NULL == GetVal()){
    if(0 == GetVal().size()){
        char msg[kLineSize];
        sprintf(msg, "GetVal() = NULL");
        MPrintErr(msg);
        abort();
    }
}

void DataArray1d::IsValidRange(long idata) const
{
    if(idata < 0 || GetNdata() <= idata){
        char msg[kLineSize];
        sprintf(msg, "idata (=%ld)", idata);
        MPrintErr(msg);
        abort();
    }
}


void DataArray1d::IsValSerrPlus(double val_serr) const
{
    if(val_serr < 0.0){
        char msg[kLineSize];
        sprintf(msg, "val_serr(=%e) < 0.0", val_serr);
        MPrintErr(msg);
        abort();
    }
}
