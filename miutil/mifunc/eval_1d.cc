#include "mi_iolib.h"
#include "mir_math.h"
#include "func_user.h"
#include "arg_eval_1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValEval1d* argval = new ArgValEval1d;
    argval->Init(argc, argv);
    if(0 < g_flag_verbose){
        argval->Print(stdout);
    }

    MirFuncPar* func_par = new MirFuncPar;
    func_par->Load(argval->GetParFile());
    if(0 < g_flag_verbose){
        func_par->Print(stdout);
    }
    
    MirFunc* func = FuncUser::GenFunc(argval->GetFuncName());
    double xval_arr[1];
    xval_arr[0] = argval->GetXval();
    double oval = func->Eval(xval_arr, func_par->GetPar());
    printf("%e\n", oval);
    
    delete argval;
    delete func_par;
    delete func;
  
    return status;
}
