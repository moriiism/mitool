#include "mi_iolib.h"
#include "mit_estimate.h"

#include "arg_nyquist.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValNyquist* argval = new ArgValNyquist;
    argval->Init(argc, argv);
    argval->Print(stdout);

    double nyquist_freq =
        MitEstimate::GetNyquistFreq(argval->GetDeltaTime());
    printf("nyquist_freq = %e (Hz)\n",
           nyquist_freq);
    
    return status;
}

