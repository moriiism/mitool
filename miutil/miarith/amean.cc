#include "mi_iolib.h"
#include "mir_math.h"
#include "arg_amean.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValAmean* argval = new ArgValAmean;
    argval->Init(argc, argv);
    argval->Print(stdout);

    string* lines_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(argval->GetInfile(),
                                    &lines_arr,
                                    &nline);
    double* val_arr = new double[nline];
    for(long iline = 0; iline < nline; iline ++){
        val_arr[iline] = atof(lines_arr[iline].c_str());
    }
    double amean = MirMath::GetAMean(nline, val_arr);
    printf("amean = %e\n", amean);

    delete [] lines_arr;
    delete [] val_arr;
    
    delete argval;
    return status;
}
