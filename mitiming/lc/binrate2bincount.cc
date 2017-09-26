#include "mi_graph2d_serr.h"
#include "mit_telescope.h"
#include "arg.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValBinRate2BinCount* argval = new ArgValBinRate2BinCount;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MiIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");
    
    GraphDataSerr2d* g2d_count = NULL;
    if("x,y,ye" == argval->GetLcFormat()){
        if("none" == argval->GetTbinfwidthStr()){
            MPrintErr("bad");
            abort();
        }
        double tbinfwidth = atof(argval->GetTbinfwidthStr().c_str());
        GraphDataSerr2d* g2d_rate  = new GraphDataSerr2d;
        g2d_rate->Load(argval->GetLcFile(), argval->GetLcFormat());
        long ndata = g2d_rate->GetNdata();

        g2d_count = new GraphDataSerr2d;
        g2d_count->Init(ndata);
        for(long idata = 0; idata < ndata; idata ++){
            g2d_count->SetPoint(idata,
                                g2d_rate->GetXvalElm(idata),
                                g2d_rate->GetXvalSerrElm(idata),
                                g2d_rate->GetOvalElm(idata) * tbinfwidth,
                                g2d_rate->GetOvalSerrElm(idata) * tbinfwidth);
        }
        delete g2d_rate;
    } else {
        MPrintErr("not yet supported.");
        abort();
    }
        
    string outqdp = argval->GetOutdir() + "/" + argval->GetOutfileHead()
        + "_bin-count.qdp";
    g2d_count->MkQdp(outqdp);
    string outfile = argval->GetOutdir() + "/" + argval->GetOutfileHead()
        + "_bin-count.dat";
    g2d_count->Save(outfile);
    
    // cleaning
    delete argval;
    delete g2d_count;

    return status;
}

