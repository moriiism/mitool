#include "mir_vect.h"
#include "mir_hist2d_ope.h"

HistData2d* const HistData2dOpe::GenHd2dByLoad(string file)
{
    HistData2d* hd2d = NULL;
    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    long nbin_yval = 0;
    double yval_lo = 0.0;
    double yval_up = 0.0;
    string format = "";
    HistData2d::ReadInfo(file,
                         &nbin_xval, &xval_lo, &xval_up,
                         &nbin_yval, &yval_lo, &yval_up,
                         &format);
    if("x,y,z" == format){
        hd2d = new HistDataNerr2d;
    } else if("x,y,z,ze" == format){
        hd2d = new HistDataSerr2d;
    } else if("x,y,z,ze+,ze-" == format){
        hd2d = new HistDataTerr2d;        
    } else {
        MPrintErr("bad format");
        abort();
    }
    hd2d->Load(file);
    return hd2d;
}

DataArray1d** const HistData2dOpe::GenDa1dArrNerr(const HistData2d* const* const hd2d_arr,
                                                  int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Copy(hd2d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

DataArray1d** const HistData2dOpe::GenDa1dArrSerr(const HistData2d* const* const hd2d_arr,
                                                  int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Copy(hd2d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

DataArray1d** const HistData2dOpe::GenDa1dArrTerr(const HistData2d* const* const hd2d_arr,
                                                  int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Copy(hd2d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

void HistData2dOpe::DelHd2dArr(HistData2d** const hd2d_arr, int narr)
{
    for(int iarr = 0; iarr < narr; iarr ++){
        delete hd2d_arr[iarr];
    }
    delete [] hd2d_arr;
}

int HistData2dOpe::IsFormatSame(const HistData2d* const data1,
                                const HistData2d* const data2)
{
    if(data1->GetNbinX()  != data2->GetNbinX()  ||
       data1->GetXvalLo() != data2->GetXvalLo() ||
       data1->GetXvalUp() != data2->GetXvalUp() ||
       data1->GetNbinY()  != data2->GetNbinY()  ||
       data1->GetYvalLo() != data2->GetYvalLo() ||
       data1->GetYvalUp() != data2->GetYvalUp()   ){
        MPrintErr("format of data1 and data2 are diffenret.");
        char msg[kLineSize];
        sprintf(msg, "data1: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)\n",
                data1->GetNbinX(),
                data1->GetXvalLo(),
                data1->GetXvalUp());
        MPrintErr(msg);
        sprintf(msg, "data1: (GetNbinY(), GetYvalLo(), GetYvalUp()) = (%ld, %e, %e)\n",
                data1->GetNbinY(),
                data1->GetYvalLo(),
                data1->GetYvalUp());
        MPrintErr(msg);        
        sprintf(msg, "data2: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)\n",
                data2->GetNbinX(),
                data2->GetXvalLo(),
                data2->GetXvalUp());
        MPrintErr(msg);        
        sprintf(msg, "data2: (GetNbinY(), GetYvalLo(), GetYvalUp()) = (%ld, %e, %e)\n",
                data2->GetNbinY(),
                data2->GetYvalLo(),
                data2->GetYvalUp());
        MPrintErr(msg);        
        abort();
    }
    return 1;
}

int HistData2dOpe::IsFormatSame(const HistData2d* const* const data_arr,
                                int nhist)
{
    if(nhist < 2){
        char msg[kLineSize];
        sprintf(msg, "nhist(=%d) < 2\n", nhist);
        MPrintWarn(msg);
        MPrintWarn("skip check");
        return 0;
    }
    for(int ihist = 1; ihist < nhist; ihist++){
        if(data_arr[0]->GetNbinX()  != data_arr[ihist]->GetNbinX()  ||
           data_arr[0]->GetXvalLo() != data_arr[ihist]->GetXvalLo() ||
           data_arr[0]->GetXvalUp() != data_arr[ihist]->GetXvalUp() ||
           data_arr[0]->GetNbinY()  != data_arr[ihist]->GetNbinY()  ||
           data_arr[0]->GetYvalLo() != data_arr[ihist]->GetYvalLo() ||
           data_arr[0]->GetYvalUp() != data_arr[ihist]->GetYvalUp()   ){
            char msg[kLineSize];
            sprintf(msg, "format of data_arr[0] and data_arr[%d] are different\n",
                    ihist);
            MPrintErr(msg);
            sprintf(msg, "data_arr[0]: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)\n",
                    data_arr[0]->GetNbinX(),
                    data_arr[0]->GetXvalLo(),
                    data_arr[0]->GetXvalUp());
            MPrintErr(msg);            
            sprintf(msg, "data_arr[0]: (GetNbinY(), GetYvalLo(), GetYvalUp()) = (%ld, %e, %e)\n",
                    data_arr[0]->GetNbinY(),
                    data_arr[0]->GetYvalLo(),
                    data_arr[0]->GetYvalUp());
            MPrintErr(msg);                        
            sprintf(msg, "data_arr[%d]: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)\n",
                    ihist,
                    data_arr[ihist]->GetNbinX(),
                    data_arr[ihist]->GetXvalLo(),
                    data_arr[ihist]->GetXvalUp());
            MPrintErr(msg);                                    
            sprintf(msg, "data_arr[%d]: (GetNbinY(), GetYvalLo(), GetYvalUp()) = (%ld, %e, %e)\n",
                    ihist,
                    data_arr[ihist]->GetNbinY(),
                    data_arr[ihist]->GetYvalLo(),
                    data_arr[ihist]->GetYvalUp());
            MPrintErr(msg);                                    
            abort();
        }
    }
    return 1;
}


// For one HistData2d
void HistData2dOpe::GetNot(const HistData2d* const in,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetNot(in->GetOvalArr(),
                           da1d);
    out->Init(in->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}

void HistData2dOpe::GetNot(const HistData2d* const in,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetNot(in->GetOvalArr(),
                           da1d);
    out->Init(in->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}

void HistData2dOpe::GetNot(const HistData2d* const in,
                           HistDataTerr2d* const out)
{
    DataArrayTerr1d* da1d = new DataArrayTerr1d;
    DataArray1dOpe::GetNot(in->GetOvalArr(),
                           da1d);
    out->Init(in->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}

void HistData2dOpe::GetScale(const HistData2d* const in,
                             double scale, double offset,
                             HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetScale(in->GetOvalArr(),
                             scale, offset,
                             da1d);
    out->Init(in->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
   
void HistData2dOpe::GetScale(const HistData2d* const in,
                             double scale, double offset,
                             HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetScale(in->GetOvalArr(),
                             scale, offset,
                             da1d);
    out->Init(in->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}

void HistData2dOpe::GetScale(const HistData2d* const in,
                             double scale, double offset,
                             HistDataTerr2d* const out)
{
    DataArrayTerr1d* da1d = new DataArrayTerr1d;
    DataArray1dOpe::GetScale(in->GetOvalArr(),
                             scale, offset,
                             da1d);
    out->Init(in->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
// For two HistData2d
void HistData2dOpe::GetMin(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMin(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetMin(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMin(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetMin(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataTerr2d* const out)
{
    DataArrayTerr1d* da1d = new DataArrayTerr1d;
    DataArray1dOpe::GetMin(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
void HistData2dOpe::GetMax(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMax(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetMax(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMax(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetMax(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataTerr2d* const out)
{
    DataArrayTerr1d* da1d = new DataArrayTerr1d;
    DataArray1dOpe::GetMax(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}

void HistData2dOpe::GetAdd(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAdd(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetAdd(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAdd(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
void HistData2dOpe::GetSub(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSub(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetSub(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetSub(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
void HistData2dOpe::GetMul(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMul(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    

void HistData2dOpe::GetMul(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMul(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
int HistData2dOpe::GetDiv(const HistData2d* const num,
                          const HistData2d* const den,
                          HistDataNerr2d* const mask_sel_out,
                          HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetDiv(num->GetOvalArr(),
                                     den->GetOvalArr(),
                                     da1d_mask,
                                     da1d);
    out->Init(num->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(num->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    
int HistData2dOpe::GetDiv(const HistData2d* const num,
                          const HistData2d* const den,
                          HistDataNerr2d* const mask_sel_out,
                          HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetDiv(num->GetOvalArr(),
                                     den->GetOvalArr(),
                                     da1d_mask,
                                     da1d);
    out->Init(num->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(num->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    
    
void HistData2dOpe::GetAMean(const HistData2d* const in1,
                             const HistData2d* const in2,
                             HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAMean(in1->GetOvalArr(),
                             in2->GetOvalArr(),
                             da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetAMean(const HistData2d* const in1,
                             const HistData2d* const in2,
                             HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAMean(in1->GetOvalArr(),
                             in2->GetOvalArr(),
                             da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
int HistData2dOpe::GetWMean(const HistData2d* const in1,
                            const HistData2d* const in2,
                            HistDataNerr2d* const mask_sel_out,
                            HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetWMean(in1->GetOvalArr(),
                                       in2->GetOvalArr(),
                                       da1d_mask,
                                       da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in1->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    

int HistData2dOpe::GetSubAddRatio(const HistData2d* const in1,
                                  const HistData2d* const in2,
                                  HistDataNerr2d* const mask_sel_out,
                                  HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetSubAddRatio(in1->GetOvalArr(),
                                             in2->GetOvalArr(),
                                             da1d_mask,
                                             da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in1->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    

int HistData2dOpe::GetSubAddRatio(const HistData2d* const in1,
                                  const HistData2d* const in2,
                                  HistDataNerr2d* const mask_sel_out,
                                  HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetSubAddRatio(in1->GetOvalArr(),
                                             in2->GetOvalArr(),
                                             da1d_mask,
                                             da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in1->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    

// For N HistData1d
void HistData2dOpe::GetMin(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMin(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetMin(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMin(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}

void HistData2dOpe::GetMin(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataTerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrTerr(in_arr, narr);
    DataArrayTerr1d* da1d = new DataArrayTerr1d;
    DataArray1dOpe::GetMin(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}

    
void HistData2dOpe::GetMax(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMax(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetMax(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMax(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}

void HistData2dOpe::GetMax(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataTerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrTerr(in_arr, narr);
    DataArrayTerr1d* da1d = new DataArrayTerr1d;
    DataArray1dOpe::GetMax(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
    
void HistData2dOpe::GetSum(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSum(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetSum(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetSum(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
    
void HistData2dOpe::GetAMean(const HistData2d* const* const in_arr,
                             int narr,
                             HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAMean(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetAMean(const HistData2d* const* const in_arr,
                             int narr,
                             HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAMean(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
    
int HistData2dOpe::GetWMean(const HistData2d* const* const in_arr,
                            int narr,
                            HistDataNerr2d* const mask_sel_out,
                            HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask_sel = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetWMean(da1d_arr, narr, da1d_mask_sel, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in_arr[0]->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask_sel);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
    delete da1d_mask_sel;
    return ret;
}
    
    
void HistData2dOpe::GetVariance(const HistData2d* const* const in_arr,
                                int narr,
                                HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetVariance(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetStddev(const HistData2d* const* const in_arr,
                              int narr,
                              HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetStddev(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetUnbiasedVariance(const HistData2d* const* const in_arr,
                                        int narr,
                                        HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetUnbiasedVariance(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetSqrtOfUnbiasedVariance(const HistData2d* const* const in_arr,
                                              int narr,
                                              HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSqrtOfUnbiasedVariance(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetRMS(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetRMS(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetMedian(const HistData2d* const* const in_arr,
                              int narr,
                              HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMedian(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
                   
void HistData2dOpe::GetSumWithMask(const HistData2d* const* const in_arr,
                                   const HistData2d* const* const mask_arr,
                                   int narr,
                                   HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSumWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetSumWithMask(const HistData2d* const* const in_arr,
                                   const HistData2d* const* const mask_arr,
                                   int narr,
                                   HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetSumWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
    
void HistData2dOpe::GetAMeanWithMask(const HistData2d* const* const in_arr,
                                     const HistData2d* const* const mask_arr,
                                     int narr,
                                     HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAMeanWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetAMeanWithMask(const HistData2d* const* const in_arr,
                                     const HistData2d* const* const mask_arr,
                                     int narr,
                                     HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAMeanWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
    
int HistData2dOpe::GetWMeanWithMask(const HistData2d* const* const in_arr,
                                    const HistData2d* const* const mask_arr,
                                    int narr,
                                    HistDataNerr2d* const mask_sel_out,
                                    HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);    
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask_sel = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetWMeanWithMask(da1d_arr, da1d_mask_arr,
                                               narr, da1d_mask_sel, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in_arr[0]->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask_sel);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
    delete da1d_mask_sel;
    return ret;
}

void HistData2dOpe::GetResValHd2d(const HistData2d* const data,
                                  const MirFunc* const func,
                                  const double* const par,
                                  HistDataNerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = data->GetOvalElm(ibin_x, ibin_y) - func->Eval(xval_arg, par);
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    delete [] oval_res;
}

void HistData2dOpe::GetResValHd2d(const HistData2d* const data,
                                  const MirFunc* const func,
                                  const double* const par,
                                  HistDataSerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = data->GetOvalElm(ibin_x, ibin_y) - func->Eval(xval_arg, par);
        oval_res_serr[ibin] = data->GetOvalSerrElm(ibin_x, ibin_y);
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    out->SetOvalSerrArr(nbinx * nbiny, oval_res_serr);    
    delete [] oval_res;
    delete [] oval_res_serr;
}

void HistData2dOpe::GetResValHd2d(const HistData2d* const data,
                                  const MirFunc* const func,
                                  const double* const par,
                                  HistDataTerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_terr_plus  = new double[nbin];
    double* oval_res_terr_minus = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        double func_val = func->Eval(xval_arg, par);
        oval_res[ibin] = data->GetOvalElm(ibin_x, ibin_y) - func_val;
        oval_res_terr_plus[ibin]  = data->GetOvalTerrPlusElm(ibin_x, ibin_y);
        oval_res_terr_minus[ibin] = data->GetOvalTerrMinusElm(ibin_x, ibin_y);
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    out->SetOvalTerrArr(nbinx * nbiny,
                        oval_res_terr_plus, oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;    
}

void HistData2dOpe::GetResRatioHd2d(const HistData2d* const data,
                                    const MirFunc* const func,
                                    const double* const par,
                                    HistDataNerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = (data->GetOvalElm(ibin_x, ibin_y) - func->Eval(xval_arg, par)) /
            func->Eval(xval_arg, par);
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    delete [] oval_res;
}

void HistData2dOpe::GetResRatioHd2d(const HistData2d* const data,
                                    const MirFunc* const func,
                                    const double* const par,
                                    HistDataSerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = (data->GetOvalElm(ibin_x, ibin_y) - func->Eval(xval_arg, par)) /
            func->Eval(xval_arg, par);
        oval_res_serr[ibin] = fabs( data->GetOvalSerrElm(ibin_x, ibin_y)
                                    / func->Eval(xval_arg, par) );
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    out->SetOvalSerrArr(nbinx * nbiny, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}


void HistData2dOpe::GetResRatioHd2d(const HistData2d* const data,
                                    const MirFunc* const func,
                                    const double* const par,
                                    HistDataTerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_terr_plus  = new double[nbin];
    double* oval_res_terr_minus = new double[nbin];    
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);        
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        double func_val = func->Eval(xval_arg, par);
        oval_res[ibin] = (data->GetOvalElm(ibin_x, ibin_y) - func_val )
            / func_val;
        oval_res_terr_plus[ibin]  = fabs(data->GetOvalTerrPlusElm(ibin_x, ibin_y) / func_val);
        oval_res_terr_minus[ibin] = -1 * fabs(data->GetOvalTerrMinusElm(ibin_x, ibin_y) / func_val);
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    out->SetOvalTerrArr(nbinx * nbiny,
                        oval_res_terr_plus, oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;
}


void HistData2dOpe::GetResChiHd2d(const HistData2d* const data,
                                  const MirFunc* const func,
                                  const double* const par,
                                  HistDataSerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = (data->GetOvalElm(ibin_x, ibin_y) - func->Eval(xval_arg, par)) /
            data->GetOvalSerrElm(ibin_x, ibin_y);
        oval_res_serr[ibin] = 1.0;
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    out->SetOvalSerrArr(nbinx * nbiny, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}


void HistData2dOpe::GetResChiHd2d(const HistData2d* const data,
                                  const MirFunc* const func,
                                  const double* const par,
                                  HistDataTerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_terr_plus  = new double[nbin];
    double* oval_res_terr_minus = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);        
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        double func_val = func->Eval(xval_arg, par);
        if(data->GetOvalElm(ibin_x, ibin_y) > func_val){
            oval_res[ibin] = -1 * (data->GetOvalElm(ibin_x, ibin_y) - func_val) /
                data->GetOvalTerrMinusElm(ibin_x, ibin_y);
        } else {
            oval_res[ibin] = (data->GetOvalElm(ibin_x, ibin_y) - func_val) /
                data->GetOvalTerrPlusElm(ibin_x, ibin_y);
        }
        oval_res_terr_plus[ibin] = 1.0;
        oval_res_terr_minus[ibin] = 1.0;
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    out->SetOvalTerrArr(nbinx * nbiny,
                        oval_res_terr_plus, oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;
}


void HistData2dOpe::FillGd2d(const GraphDataNerr2d* const gd2d,
                             HistDataNerr2d* const hist_res_out)
{
    vector<double> xval_vec;
    vector<double> yval_vec;
    hist_res_out->SetConst(0.0);
    int nfine = 10;
    for(long idata = 0; idata < gd2d->GetNdata() - 1; idata++){
        double bin_width_x_fine = hist_res_out->GetBinWidthX() / nfine;
        double bin_width_y_fine = hist_res_out->GetBinWidthY() / nfine;
        int nbin_x = (int) ceil( fabs(gd2d->GetXvalElm(idata + 1) - gd2d->GetXvalElm(idata) ) / bin_width_x_fine );
        int nbin_y = (int) ceil( fabs(gd2d->GetOvalElm(idata + 1) - gd2d->GetOvalElm(idata) ) / bin_width_y_fine );
        int nbin = TMath::Max(nbin_x, nbin_y);
        Vect2d* vect = new Vect2d;
        vect->Init(gd2d->GetXvalElm(idata + 1) - gd2d->GetXvalElm(idata), 
                   gd2d->GetOvalElm(idata + 1) - gd2d->GetOvalElm(idata));
        double step_length = vect->GetLength() / nbin;
        Vect2d* vect_step = vect->GenVectWithLength(step_length);
        
        for(long ibin = 0; ibin <= nbin; ibin ++){
            double xval = gd2d->GetXvalElm(idata) + vect_step->GetPosX() * ibin;
            double yval = gd2d->GetOvalElm(idata) + vect_step->GetPosY() * ibin;
            hist_res_out->FillByLarger(xval, yval, 1.0);
        }
        delete vect;
        delete vect_step;
    }
}

double HistData2dOpe::FindMdXbyEdge(const HistDataNerr2d* const hd2d)
{
    vector<double> md_vec;
    for(long ibiny = 0; ibiny < hd2d->GetNbinY(); ibiny ++){
        vector<double> on_vec;
        for(long ibinx = 0; ibinx < hd2d->GetNbinX(); ibinx ++){
            if( fabs(hd2d->GetOvalElm(ibinx, ibiny) - 1.0) < DBL_EPSILON){
                on_vec.push_back(ibinx);
            }
        }
        if(0 < on_vec.size()){
            double index_min = MirMath::GetMin(on_vec);
            double index_max = MirMath::GetMax(on_vec);
            double index_md = (index_min + index_max)/2.;
            md_vec.push_back(index_md);
        }
    }
    double md_index_amean = MirMath::GetAMean(md_vec);
    double xval_md = hd2d->GetXvalLo() + hd2d->GetBinWidthX() * md_index_amean;
    return xval_md;
}

double HistData2dOpe::FindMdYbyEdge(const HistDataNerr2d* const hd2d)
{
    vector<double> md_vec;
    for(long ibinx = 0; ibinx < hd2d->GetNbinX(); ibinx ++){    
        vector<double> on_vec;
        for(long ibiny = 0; ibiny < hd2d->GetNbinY(); ibiny ++){
            if( fabs(hd2d->GetOvalElm(ibinx, ibiny) - 1.0) < DBL_EPSILON){
                on_vec.push_back(ibiny);
            }
        }
        if(0 < on_vec.size()){
            double index_min = MirMath::GetMin(on_vec);
            double index_max = MirMath::GetMax(on_vec);
            double index_md = (index_min + index_max)/2.;
            md_vec.push_back(index_md);
        }
    }
    double md_index_amean = MirMath::GetAMean(md_vec);
    double yval_md = hd2d->GetYvalLo() + hd2d->GetBinWidthY() * md_index_amean;
    return yval_md;
}


//void HistData2dOpe::FillRect(double x_lo, double x_up, double y_lo, double y_up,
//                             HistDataNerr2d* const hist_res_out)
//{
//    long ibin_x_lo = hist_res_out->GetHi2d()->GetIbinXFromX(x_lo);
//    long ibin_x_up = hist_res_out->GetHi2d()->GetIbinXFromX(x_up);
//    long ibin_y_lo = hist_res_out->GetHi2d()->GetIbinYFromY(y_lo);
//    long ibin_y_up = hist_res_out->GetHi2d()->GetIbinYFromY(y_up);
//
//    // width 
//    if( (x_up - x_lo) < hist_res_out->GetHi2d()->GetBinWidthX() ){
//        ratio_x = (x_up - x_lo) / hist_res_out->GetHi2d()->GetBinWidthX();
//    } else {
//        for(long ibin_x = ibin_x_lo; ibin_x <= ibin_x_up; ibin_x ++){
//
//
//        }
//    }
//    
//
//
//
//
//        
//        for(long ibin_y = ibin_y_lo; ibin_y <= ibin_y_up; ibin_y ++){
//
//            
//
//            
//
//            
//        }
//    }
//
//    hist_res_out->FillByLarger(xval, yval, 1.0);
//
//
//}
//


void HistData2dOpe::GenContMinFcn(const HistDataNerr2d* const hd2d,
                                  double zval_min,
                                  int nlevel,
                                  const double* const delta_minfcn_arr,
                                  MirCont*** const cont_arr_ptr,
                                  MirRootTool* const root_tool,
                                  double offset_xval,
                                  double offset_yval)
{
    TH2D* th2d = hd2d->GenTH2D(offset_xval, offset_yval, 0.0);
    double* cont_level = new double [nlevel];
    for(int ilevel = 0; ilevel < nlevel; ilevel++){
        cont_level[ilevel] = zval_min + delta_minfcn_arr[ilevel];
    }
    th2d->SetContour(nlevel, cont_level);


    // http://root.cern.ch/root/html/tutorials/hist/ContourList.C.html
    // Draw contours as filled regions, and Save points
    th2d->Draw("CONT Z LIST");
    root_tool->GetTCanvas()->Update();
    // Needed to force the plotting and retrieve the contours in TGraphs

    
    // Get Contours
    TObjArray* cont_tobj_arr = dynamic_cast<TObjArray*>(gROOT->GetListOfSpecials()->FindObject("contours"));
    int ncont = 0;
    if(NULL != cont_tobj_arr){
        ncont = cont_tobj_arr->GetSize();
    } else {
        printf("%s: error: No Contours Were Extracted!\n", __func__);
        abort();
    }
    printf("ncont = %d\n", ncont);

    MirCont** cont_arr = new MirCont* [nlevel];
    for(int ilevel = 0; ilevel < nlevel; ilevel++){
        cont_arr[ilevel] = new MirCont;
    }
  
    for(int icont = 0; icont < ncont; icont++){
        TList* list_graph = (TList*) cont_tobj_arr->At(icont);

        int ngraph = list_graph->GetSize();
        GraphDataNerr2d** g2d_arr = new GraphDataNerr2d* [ngraph];
        for(int igraph = 0; igraph < ngraph; igraph++){
            g2d_arr[igraph] = new GraphDataNerr2d;
        }

        for(int igraph = 0; igraph < ngraph; igraph++){
            TGraph* graph_curve = (TGraph*) list_graph->At(igraph);
            int npoint = graph_curve->GetN();
            vector<double> xval, oval;
            for(int ipoint = 0; ipoint < npoint; ipoint++){
                double point_x, point_y;
                graph_curve->GetPoint(ipoint, point_x, point_y);
                xval.push_back(point_x);
                oval.push_back(point_y);
            }
            g2d_arr[igraph]->Init(xval.size()); 
            g2d_arr[igraph]->SetXvalArr(xval);
            g2d_arr[igraph]->SetOvalArr(oval);
        }
        cont_arr[icont]->Init(ngraph);
        cont_arr[icont]->SetGd2dArr(ngraph, g2d_arr);
      
        for(int igraph = 0; igraph < ngraph; igraph++){
            delete g2d_arr[igraph];
        }
        delete [] g2d_arr;
    }
  
    delete [] cont_level;
    delete th2d;
    *cont_arr_ptr = cont_arr;
}


void HistData2dOpe::GenContWithBestMinFcn(const HistDataNerr2d* const hd2d,
                                          double zval_min, double xval_best, double yval_best,
                                          int nlevel, const double* const delta_minfcn_arr,
                                          MirContWithBest*** const cont_with_best_arr_ptr,
                                          MirRootTool* const root_tool,
                                          double offset_xval, double offset_yval)
{
    MirCont** cont_arr = NULL;
    GenContMinFcn(hd2d, zval_min, nlevel, delta_minfcn_arr,
                  &cont_arr, root_tool, offset_xval, offset_yval);

    MirContWithBest** cont_with_best_arr = new MirContWithBest* [nlevel];
    for(int ilevel = 0; ilevel < nlevel; ilevel++){
        cont_with_best_arr[ilevel] = new MirContWithBest;
        cont_with_best_arr[ilevel]->Init();
        cont_with_best_arr[ilevel]->SetBest(xval_best, yval_best);
        cont_with_best_arr[ilevel]->SetCont(cont_arr[ilevel]);
    }
    for(int ilevel = 0; ilevel < nlevel; ilevel++){
        delete cont_arr[ilevel]; cont_arr[ilevel] = NULL;
    }
    delete [] cont_arr; cont_arr = NULL;
    
    *cont_with_best_arr_ptr = cont_with_best_arr;
}

void HistData2dOpe::GetHd2dMaskWithMargin(const HistDataNerr2d* const hd2d_mask,
                                          double xval_margin, double yval_margin,
                                          HistData2d* const hd2d_with_margin_out)
{
    if(xval_margin < 0.0 || yval_margin < 0.0){
        abort();
    }
    long nbin_x = hd2d_mask->GetNbinX();
    long nbin_y = hd2d_mask->GetNbinY();
    for(long ibin_x = 0; ibin_x < nbin_x; ibin_x ++){
        for(long ibin_y = 0; ibin_y < nbin_y; ibin_y ++){
            if(0 < hd2d_mask->GetOvalElm(ibin_x, ibin_y)){
                double xval = hd2d_mask->GetHi2d()->GetBinCenterXFromIbinX(ibin_x);
                double yval = hd2d_mask->GetHi2d()->GetBinCenterYFromIbinY(ibin_y);

                long ibin_x_lo = hd2d_with_margin_out->GetHi2d()->GetIbinXFromX(
                    MirMath::GetMax(xval - xval_margin, hd2d_with_margin_out->GetXvalLo()) );
                long ibin_x_up = hd2d_with_margin_out->GetHi2d()->GetIbinXFromX(
                    MirMath::GetMin(xval + xval_margin, hd2d_with_margin_out->GetXvalUp()) );
                long ibin_y_lo = hd2d_with_margin_out->GetHi2d()->GetIbinYFromY(
                    MirMath::GetMax(yval - yval_margin, hd2d_with_margin_out->GetYvalLo()) );
                long ibin_y_up = hd2d_with_margin_out->GetHi2d()->GetIbinYFromY(
                    MirMath::GetMin(yval + yval_margin, hd2d_with_margin_out->GetYvalUp()) );

                for(long ifill_x = ibin_x_lo; ifill_x <= ibin_x_up; ifill_x ++){
                    for(long ifill_y = ibin_y_lo; ifill_y <= ibin_y_up; ifill_y ++){
                        hd2d_with_margin_out->SetOvalElm(ifill_x, ifill_y, 1.0);
                    }
                }
            }
        }
    }
}
