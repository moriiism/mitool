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
    SetVal(org->GetNdata(), org->GetVal());
    SetFlagValSorted(org->GetFlagValSorted());
}

double DataArray1d::GetValElm(long idata) const
{
    IsValidRange(idata);
    return val_[idata];
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
    fprintf(fp, "# ndata_           = %ld\n", ndata_);
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
// protected
//

void DataArray1d::NullDataArray1d()
{
    ndata_ = 0;
    if(NULL != val_) {delete [] val_; val_ = NULL;}
    flag_val_sorted_ = 0;
}

void DataArray1d::InitDataArray1d(long ndata)
{
    NullDataArray1d();
    ndata_ = ndata;
    val_ = new double [ndata_];
    for(long idata = 0; idata < ndata_; idata++){
        val_[idata] = 0.0;
    }
    flag_val_sorted_ = 0;
}

void DataArray1d::IsValNotNull() const
{
    if(NULL == GetVal()){
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
