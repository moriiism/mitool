#include "mi_str.h"
#include "mi_iolib.h"
#include "mi_data1d_serr.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

    DataArraySerr1d* da1d = new DataArraySerr1d;
    da1d->Init(2);
    double* val_arr = new double [2];
    val_arr[0] = 3;
    val_arr[1] = 5;
    da1d->SetVal(2, val_arr);
    da1d->SetValElm(1, 88);

    da1d->PrintData(stdout, 1, 0.0);

    da1d->SetValTerr(2, val_arr);

    // da1d->SetValSerr(2, val_arr);


    delete [] val_arr;
    delete da1d;
    
    return status_prog;
}
