#include "mi_base.h"

//
// MiObject
//

// protected

void MiObject::CopyTitle(const MiObject* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}

    title_      = org->title_;
}

// private

void MiObject::NullMiObject()
{
    class_name_ = "";
    title_      = "";
}

//
// MiBase
//

void MiBase::IsValidArray(long narr, const int* const val_arr)
{
    if(narr < 1){
        char msg[kLineSize];
        sprintf(msg, "narr (=%ld) < 1", narr);
        MPrintErr(msg);
        abort();
    }
    if(NULL == val_arr){
        char msg[kLineSize];
        sprintf(msg, "val_arr == NULL");
        MPrintErr(msg);
        abort();
    }
}

void MiBase::IsValidArray(long narr, const double* const val_arr)
{
    if(narr < 1){
        char msg[kLineSize];
        sprintf(msg, "narr (=%ld) < 1", narr);
        MPrintErr(msg);
        abort();
    }
    if(NULL == val_arr){
        char msg[kLineSize];
        sprintf(msg, "val_arr == NULL");
        MPrintErr(msg);
        abort();
    }
}

void MiBase::GenArray(vector<double> vec,
                      long* narr_ptr,
                      double** val_arr_ptr)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    *narr_ptr = narr;
    *val_arr_ptr = val_arr;
}

void MiBase::DelArray(double* val_arr)
{
    delete [] val_arr; val_arr = NULL;
}
