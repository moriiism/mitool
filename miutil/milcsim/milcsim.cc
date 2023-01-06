#include "mi_iolib.h"
#include "mir_graph2d_nerr.h"
#include "mir_graph2d_ope.h"
#include "mir_qdp_tool.h"
#include "mifc_std.h"
#include "arg_milcsim.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

void GenTrigFunc(string trig_func_info_file,
                 MirFunc** const func_ptr, double** par_arr_ptr);

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMilcsim* argval = new ArgValMilcsim;
    argval->Init(argc, argv);
    
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        int ret = system(cmd);
        (void) ret;
    }

    Interval* interval = new Interval;
    interval->Load(argval->GetGtiFile());
    HistInfo1d* hi1d = new HistInfo1d;
    hi1d->Load(argval->GetHistInfoFile());
    MirFunc* func = NULL;
    double* par_arr = NULL;
    GenTrigFunc(argval->GetTrigFuncInfoFile(),
                &func, &par_arr);
    HistDataSerr1d* hd1d = new HistDataSerr1d;
    hd1d->Init(hi1d);

    TRandom3* trand = new TRandom3(argval->GetSeed());
    for(long ibin = 0; ibin < hi1d->GetNbin(); ibin ++){
        double time = hi1d->GetBinCenter(ibin);
        double oval = func->Eval1d(time, par_arr);
        double oval_rand = trand->PoissonD(oval);
        hd1d->SetOvalElm(ibin, oval_rand);
        hd1d->SetOvalSerrElm(ibin, sqrt(oval_rand));
    }
    
    char outfile[kLineSize];
    sprintf(outfile, "%s/%s.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    MirQdpTool::MkQdp(hd1d, outfile, "x,xe,y,ye");
        
    delete argval;
    
    return status;
}

void GenTrigFunc(string trig_func_info_file,
                 MirFunc** const func_ptr, double** par_arr_ptr)
{
    string* lines_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(trig_func_info_file,
                                    &lines_arr, &nline);
    int nfunc = nline;
    printf("nfunc = %d\n", nfunc);
    
    MirFunc** func_arr = new MirFunc* [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc++){
        func_arr[ifunc] = new SinePlusConstFunc;
    }
    MirFunc* func = new LinCombFunc;
    dynamic_cast<LinCombFunc*>(func)->InitSet(nfunc, func_arr);

    double* par_arr = new double[5 * nline];
    double* norm_func_arr = new double [nline];
    int ipar = 0;
    for(long iline = 0; iline < nline; iline ++){
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(lines_arr[iline],
                        &nsplit, &split_arr);
        double freq  = atof(split_arr[0].c_str());
        double phase = atof(split_arr[1].c_str());
        double norm  = atof(split_arr[2].c_str());
        double cons  = atof(split_arr[3].c_str());
        norm_func_arr[iline]  = atof(split_arr[4].c_str());
        par_arr[ipar] = freq; ipar ++;
        par_arr[ipar] = phase; ipar ++;
        par_arr[ipar] = norm; ipar ++;
        par_arr[ipar] = cons; ipar ++;
        delete [] split_arr;
    }
    for(long iline = 0; iline < nline; iline ++){
        par_arr[ipar] = norm_func_arr[iline]; ipar ++;
    }
    // clean
    MiIolib::DelReadFile(lines_arr);
    for(int ifunc = 0; ifunc < nfunc; ifunc++){
        delete func_arr[ifunc];
    }
    delete [] func_arr;
    delete [] norm_func_arr;
    
    
    *func_ptr = func;
    *par_arr_ptr = par_arr;
    
}


