#include "mir_data1d_terr.h"
#include "mir_data1d_ope.h"

//
// public
//

void DataArrayTerr1d::Init(long ndata)
{
    InitDataArray1d(ndata);
    InitDataArrayTerr1d(ndata);
}

// Set

void DataArrayTerr1d::SetValTerr(long ndata,
                                 const double* const val_serr)
{
    if(GetNdata() != ndata){
        MPrintErrClass("GetNdata() != ndata");
        abort();
    }
    if(1 != IsValTerrNotNull()){
        abort();
    }
    for(long idata = 0; idata < ndata; idata++){
        IsValSerrPlus(val_serr[idata]);
        val_terr_plus_[idata]  = val_serr[idata];
        val_terr_minus_[idata] = -1 * val_serr[idata];
    }
}

void DataArrayTerr1d::SetValTerr(vector<double> val_serr)
{
    if(GetNdata() != (long) val_serr.size()){
        MPrintErrClass("GetNdata() != val_serr.size()");
        abort();
    }
    if(1 != IsValTerrNotNull()){
        abort();
    }
    for(long idata = 0; idata < GetNdata(); idata++){
        IsValSerrPlus(val_serr[idata]);
        val_terr_plus_[idata]  = val_serr[idata];
        val_terr_minus_[idata] = -1 * val_serr[idata];
    }
}

void DataArrayTerr1d::SetValTerr(long ndata,
                                 const double* const val_terr_plus,
                                 const double* const val_terr_minus)
{
    if(GetNdata() != ndata){
        MPrintErrClass("GetNdata() != ndata");
        abort();
    }
    if(1 != IsValTerrNotNull()){
        abort();
    }
    for(long idata = 0; idata < ndata; idata++){
        IsValTerrPlusPlus(val_terr_plus[idata]);
        IsValTerrMinusMinus(val_terr_minus[idata]);
        val_terr_plus_[idata]  = val_terr_plus[idata];
        val_terr_minus_[idata] = val_terr_minus[idata];
    }
}



void DataArrayTerr1d::SetValTerr(vector<double> val_terr_plus,
                                 vector<double> val_terr_minus)
{
    if(GetNdata() != (long) val_terr_plus.size()){
        MPrintErrClass("GetNdata() != val_terr_plus.size()");
        abort();
    }
    if(1 != IsValTerrNotNull()){
        abort();
    }
    for(long idata = 0; idata < GetNdata(); idata++){
        IsValTerrPlusPlus(val_terr_plus[idata]);
        IsValTerrMinusMinus(val_terr_minus[idata]);
        val_terr_plus_[idata]  = val_terr_plus[idata];
        val_terr_minus_[idata] = val_terr_minus[idata];
    }
}


void DataArrayTerr1d::SetValAndTerr(long ndata,
                                    const double* const val,
                                    const double* const val_serr)
{
    SetVal(ndata, val);
    SetValTerr(ndata, val_serr);
}

void DataArrayTerr1d::SetValAndTerr(vector<double> val,
                                    vector<double> val_serr)
{
    SetVal(val);
    SetValTerr(val_serr);
}


void DataArrayTerr1d::SetValAndTerr(long ndata,
                                    const double* const val,
                                    const double* const val_terr_plus,
                                    const double* const val_terr_minus)
{
    SetVal(ndata, val);
    SetValTerr(ndata, val_terr_plus, val_terr_minus);
}

void DataArrayTerr1d::SetValAndTerr(vector<double> val,
                                    vector<double> val_terr_plus,
                                    vector<double> val_terr_minus)
{
    SetVal(val);
    SetValTerr(val_terr_plus, val_terr_minus);
}

// Init & Set

void DataArrayTerr1d::InitSetValAndTerr(long ndata,
                                        const double* const val,
                                        const double* const val_serr)
{
    Init(ndata);
    SetValAndTerr(ndata, val, val_serr);
}
    
void DataArrayTerr1d::InitSetValAndTerr(vector<double> val,
                                        vector<double> val_serr)
{
    Init(val.size());
    SetValAndTerr(val, val_serr);
}

void DataArrayTerr1d::InitSetValAndTerr(long ndata,
                                        const double* const val,
                                        const double* const val_terr_plus,
                                        const double* const val_terr_minus)
{
    Init(ndata);
    SetValAndTerr(ndata, val, val_terr_plus, val_terr_minus);
}

void DataArrayTerr1d::InitSetValAndTerr(vector<double> val,
                                        vector<double> val_terr_plus,
                                        vector<double> val_terr_minus)
{
    Init(val.size());
    SetValAndTerr(val, val_terr_plus, val_terr_minus);
}


void DataArrayTerr1d::SetValTerrElm(long idata, double val_serr)
{
    if(1 != IsValTerrNotNull()){
        abort();
    }
    IsValSerrPlus(val_serr);
    if(1 == IsValidRange(idata)){
        val_terr_plus_[idata]  = val_serr;
        val_terr_minus_[idata] = -1 * val_serr;
    }
}

void DataArrayTerr1d::SetValTerrPlusElm(long idata, double val_terr_plus)
{
    if(1 != IsValTerrNotNull()){
        abort();
    }
    IsValTerrPlusPlus(val_terr_plus);
    if(1 == IsValidRange(idata)){
        val_terr_plus_[idata] = val_terr_plus;
    }
}

void DataArrayTerr1d::SetValTerrMinusElm(long idata, double val_terr_minus)
{
    if(1 != IsValTerrNotNull()){
        abort();
    }
    IsValTerrMinusMinus(val_terr_minus);
    if(1 == IsValidRange(idata)){
        val_terr_minus_[idata] = val_terr_minus;
    }
}


void DataArrayTerr1d::Fill(long idata)
{
    double val_pre = GetValElm(idata);
    double val_new = val_pre + 1.0;
    SetValElm(idata, val_new);
    SetValTerrPlusElm(idata, sqrt(val_new));
    SetValTerrMinusElm(idata, -1 * sqrt(val_new));
    // poisson error    
}

void DataArrayTerr1d::Fill(long idata, double weight)
{
    double val_pre = GetValElm(idata);
    double val_new = val_pre + weight;
    SetValElm(idata, val_new);
    SetValTerrPlusElm(idata, sqrt(val_new));
    SetValTerrMinusElm(idata, -1 * sqrt(val_new));
    // poisson error    
}

void DataArrayTerr1d::FillByMax(long idata, double val)
{
    double val_pre = GetValElm(idata);
    if(val_pre < val){
        SetValElm(idata, val);
        if(val < 0.0){
            SetValTerrElm(idata, 0.0);
        } else {
            SetValTerrElm(idata, sqrt(val));
        }
    }
}

void DataArrayTerr1d::FillByMax(long idata,
                                double val,
                                double val_terr_plus,
                                double val_terr_minus)
{
    double val_pre = GetValElm(idata);
    if(val_pre < val){
        SetValElm(idata, val);
        SetValTerrPlusElm(idata, val_terr_plus);
        SetValTerrMinusElm(idata, val_terr_minus);
    }
}


void DataArrayTerr1d::FillByMin(long idata, double val)
{
    double val_pre = GetValElm(idata);
    if(val_pre > val){
        SetValElm(idata, val);
        if(val < 0.0){
            SetValTerrElm(idata, 0.0);
        } else {
            SetValTerrElm(idata, sqrt(val));
        }
    }
}

void DataArrayTerr1d::FillByMin(long idata,
                                double val,
                                double val_terr_plus,
                                double val_terr_minus)
{
    double val_pre = GetValElm(idata);
    if(val_pre > val){
        SetValElm(idata, val);
        SetValTerrPlusElm(idata, val_terr_plus);
        SetValTerrMinusElm(idata, val_terr_minus);
    }
}

void DataArrayTerr1d::SetZero()
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, 0.0);
        SetValTerrPlusElm(idata, 0.0);
        SetValTerrMinusElm(idata, 0.0);
    }
}

void DataArrayTerr1d::SetOne()
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, 1.0);
        SetValTerrPlusElm(idata, 1.0);
        SetValTerrMinusElm(idata, -1.0);
    }
}

void DataArrayTerr1d::SetConst(double constant)
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, constant);
        SetValTerrPlusElm(idata, sqrt(constant));
        SetValTerrMinusElm(idata, -1 * sqrt(constant));
    }
}

void DataArrayTerr1d::SetValErrByPoissonErr()
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        double val = GetValElm(idata);
        SetValTerrPlusElm(idata, sqrt(val));
        SetValTerrMinusElm(idata, -1 * sqrt(val));
    }
}

DataArrayTerr1d* const DataArrayTerr1d::Clone() const
{
    DataArrayTerr1d* obj_new = new DataArrayTerr1d;
    obj_new->Copy(this);
    return obj_new;
}


void DataArrayTerr1d::Load(string file)
{
    NullDataArray1d();
    NullDataArrayTerr1d();

    string* line_arr = NULL;
    long ndata = 0;    
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
        if(3 != ncolumn){
            MPrintWarnClass("ncolumn != 3");
        }
        istringstream iss(line_arr[idata]);
        double val_tmp;
        double val_terr_plus_tmp;
        double val_terr_minus_tmp;                
        iss >> val_tmp >> val_terr_plus_tmp >> val_terr_minus_tmp;
        SetValElm(idata, val_tmp);
        SetValTerrPlusElm(idata, val_terr_plus_tmp);
        SetValTerrMinusElm(idata, val_terr_minus_tmp);
    }
    MiIolib::DelReadFile(line_arr);

    int flag_val_sorted = 0;
    ReadInfo(file, &flag_val_sorted);
    SetFlagValSorted(flag_val_sorted);
}

//
//// operation
//
//void DataArrayTerr1d::Sort()
//{
//    if(1 == GetFlagValSorted()){
//        MPrintInfoClass("It has been already sorted.");
//        return;
//    }
//    if(NULL == GetVal() ||
//       NULL == GetValTerrPlus() ||
//       NULL == GetValTerrMinus() ){
//        MPrintErrClass("GetVal() == NULL or "
//                       "GetValTerrPlus() == NULL or GetValTerrMinus() == NULL");
//        abort();
//    }
//
//    long ndata = GetNdata();
//    double* val_org = new double [ndata];
//    double* val_terr_plus_org  = new double [ndata];
//    double* val_terr_minus_org = new double [ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        val_org[idata]            = GetValElm(idata);
//        val_terr_plus_org[idata]  = GetValTerrPlusElm(idata);
//        val_terr_minus_org[idata] = GetValTerrMinusElm(idata);
//    }
//
//    long* index = new long [ndata];  // to store sort result
//    TMath::Sort(ndata, val_org, index, kFALSE);
//
//    for(long idata = 0; idata < ndata; idata++){
//        SetValElm(idata, val_org[index[idata]]);
//        SetValTerrPlusElm(idata, val_terr_plus_org[index[idata]]);
//        SetValTerrMinusElm(idata, val_terr_minus_org[index[idata]]);
//    }
//
//    delete [] index;               index = NULL;
//    delete [] val_org;             val_org = NULL;
//    delete [] val_terr_plus_org;   val_terr_plus_org = NULL;
//    delete [] val_terr_minus_org;  val_terr_minus_org = NULL;
//
//    SetFlagValSorted(1);    
//    if(0 < g_flag_verbose){
//        MPrintInfoClass("sorted.");
//    }
//}
//
//
//void DataArrayTerr1d::Scale(const DataArray1d* const data_array,
//                            double scale, double offset)
//{
//    DataArrayTerr1d* data_array_tmp = new DataArrayTerr1d;
//    data_array_tmp->Copy(data_array);
//    DataArrayTerr1d* out = new DataArrayTerr1d;
//    DataArray1dOpe::GetScale(data_array_tmp, scale, offset, out);
//    Copy(out);
//    delete data_array_tmp;
//    delete out;
//}

// get

double DataArrayTerr1d::GetValTerrPlusElm(long idata) const
{

    if(1 == IsValidRange(idata)){
        return val_terr_plus_[idata];
    } else {
        abort();
    }
}

double DataArrayTerr1d::GetValTerrMinusElm(long idata) const
{
    if(1 == IsValidRange(idata)){
        return val_terr_minus_[idata];
    } else {
        abort();
    }
}

double* const DataArrayTerr1d::GenValSerr() const
{
    long ndata = GetNdata();
    double* val_serr = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        val_serr[idata] = (GetValTerrPlusElm(idata) - GetValTerrMinusElm(idata)) / 2.;
    }
    return val_serr;
}

double DataArrayTerr1d::GetValSerrElm(long idata) const
{
    double val_serr = (GetValTerrPlusElm(idata) - GetValTerrMinusElm(idata)) / 2.;
    return val_serr;
}

// for qdp

double DataArrayTerr1d::GetValAndErrMin() const
{
    long ndata = GetNdata();
    double* val_tmp = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        val_tmp[idata] = GetValElm(idata) + GetValTerrMinusElm(idata);
    }
    double min = MirMath::GetMin(ndata, val_tmp);
    delete [] val_tmp;
    return min;
}

double DataArrayTerr1d::GetValAndErrMax() const
{
    long ndata = GetNdata();
    double* val_tmp = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        val_tmp[idata] = GetValElm(idata) + GetValTerrPlusElm(idata);
    }
    double max = MirMath::GetMin(ndata, val_tmp);
    delete [] val_tmp;
    return max;
}

void DataArrayTerr1d::GetRangeValQdp(double* const lo_ptr,
                                     double* const up_ptr) const
{
    double lo, up;
    MirMath::GetRangeQdp(GetValAndErrMin(), GetValAndErrMax(), &lo, &up);
    *lo_ptr = lo;
    *up_ptr = up;
}


// output

void DataArrayTerr1d::PrintData(FILE* fp, int mode,
                                double offset_val) const
{
    long ndata = GetNdata();    
    if(0 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.10e  %.10e  %.10e\n",
                    GetValElm(idata) - offset_val,
                    GetValTerrPlusElm(idata),
                    GetValTerrMinusElm(idata));
        }
    } else if (1 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%ld   %.10e  %.10e  %.10e\n",
                    idata,
                    GetValElm(idata) - offset_val,
                    GetValTerrPlusElm(idata),
                    GetValTerrMinusElm(idata));
        }
    } else if (2 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.10e  %.10e  %.10e  1.0\n",
                    GetValElm(idata) - offset_val,
                    GetValTerrPlusElm(idata),
                    GetValTerrMinusElm(idata));
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad mode (=%d).", mode);
        MPrintErrClass(msg);
        abort();
    }
}

double DataArrayTerr1d::GetOffsetValFromTag(string offset_tag) const
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

void DataArrayTerr1d::NullDataArrayTerr1d()
{
    if(NULL != val_terr_plus_)  {delete [] val_terr_plus_; val_terr_plus_ = NULL;}
    if(NULL != val_terr_minus_) {delete [] val_terr_minus_; val_terr_minus_ = NULL;}
}

void DataArrayTerr1d::InitDataArrayTerr1d(long ndata)
{
    NullDataArrayTerr1d();
    if(GetNdata() != ndata){
        MPrintErrClass("GetNdata() != ndata");
        abort();
    }
    val_terr_plus_  = new double [ndata];
    val_terr_minus_ = new double [ndata];
    for(long idata = 0; idata < ndata; idata++){
        val_terr_plus_[idata]  = 0.0;
        val_terr_minus_[idata] = 0.0;
    }
}

int DataArrayTerr1d::IsValTerrNotNull() const
{
    if(NULL == GetValTerrPlus() || NULL == GetValTerrMinus()){
        MPrintErrClass("bad GetValTerrPlus() (=NULL) or "
                       "GetValTerrMinus() (=NULL)");
        abort();
    }
    return 1;
}


int DataArrayTerr1d::IsValTerrPlusPlus(double val_terr_plus) const
{
    if(val_terr_plus < 0.0){
        MPrintErrClass("val_terr_plus < 0.0");
        abort();
    }
    return 1;    
}

int DataArrayTerr1d::IsValTerrMinusMinus(double val_terr_minus) const
{
    if(val_terr_minus > 0.0){
        MPrintErrClass("val_terr_minus > 0.0");
        abort();
    }
    return 1;
}

