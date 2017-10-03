#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_func_ope.h"
#include "mir_func_par.h"
#include "mir_root_tool.h"
#include "mifc_std.h"
#include "mir_hist1d_nerr.h"
#include "mir_qdp_tool.h"


// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    TF1* const GenTF1(const MirFunc* const func,
//                      double x_low, double x_up);
    {
        printf("--- test GenTF1\n");

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
            
        Gauss1dFunc* func = new Gauss1dFunc;
        double x_lo = -10.0;
        double x_up = 10.0;
        TF1* tf1 = MirFuncOpe::GenTF1(func, x_lo, x_up);
        tf1->SetParameters(2.0, 1.0, 10.0);
        tf1->Draw();
        root_tool->GetTCanvas()->Print("/home/morii/temp/func_ope1.png");

        delete root_tool;
        delete func;
        delete tf1;
        printf("=== \n");
    }
    
//    TF2* const GenTF2(const MirFunc* const func,
//                      double x_low, double x_up,
//                      double y_low, double y_up);
    {
        printf("--- test GenTF2\n");

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
            
        Gauss2dFunc* func = new Gauss2dFunc;
        double x_lo = -10.0;
        double x_up = 10.0;
        double y_lo = -10.0;
        double y_up = 10.0;
        TF2* tf2 = MirFuncOpe::GenTF2(func, x_lo, x_up, y_lo, y_up);

        double sigma_xp = 3.0;
        double sigma_yp = 7.0;
        double norm = 10.0;
        double rot_angle = M_PI/16.0;
        double mu_xp = 3.0;
        double mu_yp = -5.0;
        double shift_z = 10.0;
        double par[7];
        par[0] = sigma_xp;
        par[1] = sigma_yp;
        par[2] = norm;
        par[3] = rot_angle;
        par[4] = mu_xp;
        par[5] = mu_yp;
        par[6] = shift_z;
        tf2->SetParameters(par);
        tf2->Draw("colz");
        root_tool->GetTCanvas()->Print("/home/morii/temp/func_ope2.png");

        delete root_tool;
        delete func;
        delete tf2;
        printf("=== \n");
    }
    
//    void DrawFunc(const MirFunc* const func,
//                  const MirFuncPar* const func_par,
//                  MirRootTool* const root_tool,
//                  double x_low, double x_up,
//                  string outfig);
    {
        printf("--- test DrawFunc\n");

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
            
        Gauss1dFunc* func = new Gauss1dFunc;
        double x_lo = -10.0;
        double x_up = 10.0;

        int npar = 3;
        double* par = new double[npar];
        par[0] = 3.0;
        par[1] = 2.0;
        par[2] = 10.0;
        string* par_name = new string[npar];
        par_name[0] = "mu_xp";
        par_name[1] = "sigma_xp";
        par_name[2] = "norm";

        MirFuncPar* func_par = new MirFuncPar;        
        func_par->Init(npar);
        func_par->Set(npar, par_name, par);

        string outfig = "/home/morii/temp/func_ope3.png";
        MirFuncOpe::DrawFunc(func, func_par, root_tool, x_lo, x_up, outfig);

        delete root_tool;
        delete func;
        delete func_par;
        delete [] par;
        delete [] par_name;
        printf("=== \n");
    }
    
//    void DrawFunc(const MirFunc* const func,
//                  const MirFuncPar* const func_par,
//                  MirRootTool* const root_tool,
//                  double x_low, double x_up,
//                  double y_low, double y_up,
//                  string outfig);
    {
        printf("--- test DrawFunc\n");

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
            
        Gauss2dFunc* func = new Gauss2dFunc;
        double x_lo = -10.0;
        double x_up = 10.0;
        double y_lo = -10.0;
        double y_up = 10.0;

        double sigma_xp = 3.0;
        double sigma_yp = 7.0;
        double norm = 10.0;
        double rot_angle = M_PI/16.0;
        double mu_xp = 3.0;
        double mu_yp = -5.0;
        double shift_z = 10.0;
        
        int npar = 7;
        double* par = new double[npar];
        par[0] = sigma_xp;
        par[1] = sigma_yp;
        par[2] = norm;
        par[3] = rot_angle;
        par[4] = mu_xp;
        par[5] = mu_yp;
        par[6] = shift_z;
        string* par_name = new string[npar];
        par_name[0] = "sigma_xp";
        par_name[1] = "sigma_yp";
        par_name[2] = "norm";
        par_name[3] = "rot_angle";
        par_name[4] = "mu_xp";
        par_name[5] = "mu_yp";
        par_name[6] = "shift_z";

        MirFuncPar* func_par = new MirFuncPar;
        func_par->Init(npar);
        func_par->Set(npar, par_name, par);

        string outfig = "/home/morii/temp/func_ope4.png";
        MirFuncOpe::DrawFunc(func, func_par, root_tool, x_lo, x_up, y_lo, y_up, outfig);

        delete root_tool;
        delete func;
        delete func_par;
        delete [] par;
        delete [] par_name;
        
        printf("=== \n");
    }
    
//    double GetRandom(const MirFunc* const func,
//                     const MirFuncPar* const func_par,
//                     double x_low, double x_up,
//                     int rand_seed);
    {
        printf("--- test GetRandom\n");

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
            
        Gauss1dFunc* func = new Gauss1dFunc;
        double x_lo = -10.0;
        double x_up = 10.0;

        int npar = 3;
        double* par = new double[npar];
        par[0] = 3.0;
        par[1] = 2.0;
        par[2] = 10.0;
        string* par_name = new string[npar];
        par_name[0] = "mu_xp";
        par_name[1] = "sigma_xp";
        par_name[2] = "norm";

        MirFuncPar* func_par = new MirFuncPar;        
        func_par->Init(npar);
        func_par->Set(npar, par_name, par);

        HistDataSerr1d* hd1d = new HistDataSerr1d;
        long nbin = 100;
        hd1d->Init(nbin, x_lo, x_up);
        int rand_seed = 0;
        int ndata = 1000;
        for(int idata = 0; idata < ndata; idata ++){
            double val = MirFuncOpe::GetRandom(func, func_par, x_lo, x_up, rand_seed);
            hd1d->Fill(val);
        }
        int npoint_func = 1000;
        MirQdpTool::MkQdpDiff3Serr(hd1d, func, func_par->GetPar(),
                                   npoint_func,
                                   "/home/morii/temp", "func_ope");
        
        delete root_tool;
        delete func;
        delete func_par;
        delete [] par;
        delete [] par_name;
        delete hd1d;
        
        printf("=== \n");
    }
    
//    double GetRandom(const MirFunc* const func,
//                     const MirFuncPar* const func_par,
//                     double x_low, double x_up,
//                     double y_low, double y_up,
//                     int rand_seed);
    {
        printf("--- test GetRandom\n");
        printf("=== \n");
    }
    
    return status_prog;
}
