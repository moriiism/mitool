#include "mi_iolib.h"
#include "mir_root_tool.h"
#include "mir_data1d_nerr.h"
#include "mir_graph2d_serr.h"
#include "mit_binary_orb.h"
#include "arg_t90_to_tperi.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValT90ToTperi* argval = new ArgValT90ToTperi;
    argval->Init(argc, argv);
    argval->Print(stdout);


    double time_peri
        = BinaryOrb::Time90ToTimePeri(argval->GetTime90(),
                                          argval->GetPeriod());
    printf("%e\n", time_peri);
    
    delete argval;
    return status;
}

