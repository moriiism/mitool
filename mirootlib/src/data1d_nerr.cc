#include "mir_data1d_nerr.h"

//
// public
//

void DataArrayNerr1d::Init(long ndata)
{
    InitDataArray1d(ndata);
}

void DataArrayNerr1d::Fill(long idata)
{
    double val_pre = GetValElm(idata);
    SetValElm(idata, val_pre + 1.0);
}

void DataArrayNerr1d::Fill(long idata, double weight)
{
    double val_pre = GetValElm(idata);
    SetValElm(idata, val_pre + weight);
}

void DataArrayNerr1d::FillByMax(long idata, double oval)
{
    double val_pre = GetValElm(idata);
    if(val_pre < oval){
        SetValElm(idata, oval);
    }
}

void DataArrayNerr1d::FillByMin(long idata, double oval)
{
    double val_pre = GetValElm(idata);
    if(val_pre > oval){
        SetValElm(idata, oval);
    }
}

void DataArrayNerr1d::SetConst(double constant)
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, constant);        
    }
}

DataArrayNerr1d* const DataArrayNerr1d::Clone() const
{
    DataArrayNerr1d* obj_new = new DataArrayNerr1d;
    obj_new->Copy(this);
    return obj_new;
}


void DataArrayNerr1d::Load(string file)
{
    NullDataArray1d();

    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
        if(1 != ncolumn){
            MPrintWarnClass("ncolumn != 1");
        }
        istringstream iss(line_arr[idata]);
        double val_tmp;
        iss >> val_tmp;
        SetValElm(idata, val_tmp);
    }
    MiIolib::DelReadFile(line_arr);

    int flag_val_sorted = 0;
    ReadInfo(file, &flag_val_sorted);
    SetFlagValSorted(flag_val_sorted);
}


void DataArrayNerr1d::Sort()
{
    if(1 == GetFlagValSorted()){
        MPrintInfoClass("It has been already sorted.");
        return;
    }
    if(NULL == GetVal()){
        MPrintErrClass("GetVal() == NULL");
        abort();
    }
    long ndata = GetNdata();
    double* val_org = new double [ndata];
    for(long idata = 0; idata < ndata; idata++){
        val_org[idata] = GetValElm(idata);
    }

    long* index = new long [ndata];  // to store sort result
    TMath::Sort(ndata, val_org, index, kFALSE);

    for(long idata = 0; idata < ndata; idata++){
        SetValElm(idata, val_org[index[idata]]);
    }

    delete [] index; index = NULL;
    delete [] val_org; val_org = NULL;

    SetFlagValSorted(1);
}

double DataArrayNerr1d::GetValAndErrMin() const
{
    double min = MirMath::GetMin(GetNdata(), GetVal());
    return min;
}

double DataArrayNerr1d::GetValAndErrMax() const
{
    double max = MirMath::GetMax(GetNdata(), GetVal());
    return max;
}

void DataArrayNerr1d::PrintData(FILE* fp, int mode,
                                double offset_val) const
{
    long ndata = GetNdata();    
    if(0 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.10e\n",
                    GetValElm(idata) - offset_val);
        }
    } else if (1 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%ld   %.10e\n",
                    idata, GetValElm(idata) - offset_val);
        }
    } else if (2 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.10e  1.0\n",
                    GetValElm(idata) - offset_val);
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad mode (=%d).", mode);
        MPrintErrClass(msg);
        abort();
    }
}

double DataArrayNerr1d::GetOffsetValFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = MirMath::GetMin(GetNdata(), GetVal());
    } else if ("ed" == offset_tag){
        offset = MirMath::GetMax(GetNdata(), GetVal());
    } else if ("md" == offset_tag){
        offset = ( MirMath::GetMin(GetNdata(), GetVal()) +
                   MirMath::GetMax(GetNdata(), GetVal()) ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}
