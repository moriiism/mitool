#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_hist2d_serr.h"
#include "mir_root_tool.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Init(long nbin_xval,
//              double xval_lo,
//              double xval_up);
    {
        printf("--- test Init;\n");
        HistDataSerr2d* hd2d = new HistDataSerr2d("hd2d");
        long nbin_xval = 10;
        double lo_xval = 0.0;
        double up_xval = 10.0;
        long nbin_yval = 10;
        double lo_yval = 0.0;
        double up_yval = 10.0;        
        hd2d->Init(nbin_xval, lo_xval, up_xval,
                   nbin_yval, lo_yval, up_yval);
        hd2d->SetConst(10.0);

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("def");
        
        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("colz");
        root_tool->GetTCanvas()->Print("temp.png");

        delete hd2d;
        delete root_tool;
        
        printf("=== \n");
    }

    return status_prog;
}
