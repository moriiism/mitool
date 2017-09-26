#include "mi_iolib.h"
#include "mir_qdp_tool.h"
#include "mifc_std.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void GetRangeQdp(double min, double max,
//                     double* const low_ptr, double* const up_ptr);
    {
        printf("--- test GetRangeQdp\n");
        double min = 0.0;
        double max = 10.0;
        double low = 0.0;
        double up  = 0.0;
        MirQdpTool::GetRangeQdp(min, max,
                                &low, &up);
        printf("low = %e\n", low);
        printf("up  = %e\n", up);
        assert( abs( low - (-1.0) ) < DBL_EPSILON );
        assert( abs( up  - (11.0) ) < DBL_EPSILON ); 
        printf("=== \n");
    }
    
//    void PrintQdpRead(FILE* fp, string format);
    {
        printf("--- test PrintQdpRead\n");
        //printf("format: x\n");
        //MirQdpTool::PrintQdpRead(stdout, "x");
        // --> abort

        printf("----\n");
        printf("format: x,y\n");
        MirQdpTool::PrintQdpRead(stdout, "x,y");

        printf("----\n");
        printf("format: x,y,ye\n");
        MirQdpTool::PrintQdpRead(stdout, "x,y,ye");

        printf("----\n");        
        printf("format: x,xe,y,ye\n");
        MirQdpTool::PrintQdpRead(stdout, "x,xe,y,ye");

        printf("----\n");        
        printf("format: x,xe,y\n");
        MirQdpTool::PrintQdpRead(stdout, "x,xe,y");

        printf("----\n");        
        printf("format: x,y,ye+,ye-\n");
        MirQdpTool::PrintQdpRead(stdout, "x,y,ye+,ye-");

        printf("----\n");
        printf("format: x,xe,y,ye+,ye-\n");
        MirQdpTool::PrintQdpRead(stdout, "x,xe,y,ye+,ye-");

        printf("----\n");        
        printf("format: x,xe+,xe-,y\n");        
        MirQdpTool::PrintQdpRead(stdout, "x,xe+,xe-,y");

        printf("----\n");        
        printf("format: x,xe+,xe-,y,ye\n");                
        MirQdpTool::PrintQdpRead(stdout, "x,xe+,xe-,y,ye");

        printf("----\n");        
        printf("format: x,xe+,xe-,y,ye+,ye-\n");
        MirQdpTool::PrintQdpRead(stdout, "x,xe+,xe-,y,ye+,ye-");
        
        printf("=== \n");
    }
   
//    void PrintQdpCmdStd(FILE* fp);
    {
        printf("--- test PrintQdpCmdStd\n");
        MirQdpTool::PrintQdpCmdStd(stdout);
        printf("=== \n");
    }
 
//    void PrintQdpAxisRescale(FILE* fp, string xy,
//                             double val_lo, double val_up);
    {
        printf("--- test PrintQdpAxisRescale\n");
        printf("---\n");
        MirQdpTool::PrintQdpAxisRescale(stdout, "x", 1.0, 2.0);

        printf("---\n");        
        MirQdpTool::PrintQdpAxisRescale(stdout, "y", 1.0, 2.0);

        printf("---\n");        
        MirQdpTool::PrintQdpAxisRescale(stdout, "x", 1.0, 1.0);
        printf("=== \n");
    }
    
//    void PrintQdpAxisTitle(FILE* fp, string xy,
//                           string title, double offset);
    {
        printf("--- test PrintQdpAxisTitle\n");
        printf("---\n");
        MirQdpTool::PrintQdpAxisTitle(stdout, "x", "time", 1.0);

        printf("---\n");
        MirQdpTool::PrintQdpAxisTitle(stdout, "y", "flux", 1.0);

        printf("---\n");
        MirQdpTool::PrintQdpAxisTitle(stdout, "x", "time", 0.0);
        printf("=== \n");
    }
   
//    void PrintQdpScale(FILE* fp, string xy, string scale);
    {
        printf("--- test PrintQdpScale\n");
        printf("---\n");
        MirQdpTool::PrintQdpScale(stdout, "x", "log");
        printf("---\n");
        MirQdpTool::PrintQdpScale(stdout, "y", "log");

        printf("---\n");
        MirQdpTool::PrintQdpScale(stdout, "x", "lin");
        printf("---\n");
        MirQdpTool::PrintQdpScale(stdout, "y", "lin");
        
        printf("=== \n");
    }
    
//    // format: index  data
//    void MkQdpMode1(const DataArray1d* const data_array,
//                    string qdpout,
//                    string title_oval = "",
//                    double offset_oval = 0.0,
//                    string scale_xval = "lin",
//                    string scale_oval = "lin");
    {
        printf("--- test MkQdpMode1\n");
        DataArrayNerr1d* da1d = new DataArrayNerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1);
        da1d->SetValElm(1, 2);
        da1d->SetValElm(2, 3);
        string qdpout = "/home/morii/temp/temp1.qdp";
        MirQdpTool::MkQdpMode1(da1d, qdpout, "flux", 1.0, "lin", "lin");
        delete da1d;
        printf("=== \n");
    }

    {
        printf("--- test MkQdpMode1\n");
        DataArray1d* da1d = new DataArraySerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1);
        da1d->SetValElm(1, 2);
        da1d->SetValElm(2, 3);
        da1d->SetValSerrElm(0, 0.5);
        da1d->SetValSerrElm(1, 1.0);
        da1d->SetValSerrElm(2, 1.5);
        string qdpout = "/home/morii/temp/temp2.qdp";
        MirQdpTool::MkQdpMode1(da1d, qdpout, "flux", 1.0, "log", "lin");
        delete da1d;
        printf("=== \n");
    }

    {
        printf("--- test MkQdpMode1\n");
        DataArray1d* da1d = new DataArrayTerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1);
        da1d->SetValElm(1, 2);
        da1d->SetValElm(2, 3);
        da1d->SetValTerrPlusElm(0, 0.5);
        da1d->SetValTerrPlusElm(1, 1.0);
        da1d->SetValTerrPlusElm(2, 1.5);
        da1d->SetValTerrMinusElm(0, -1.0);
        da1d->SetValTerrMinusElm(1, -2.0);
        da1d->SetValTerrMinusElm(2, -3.0);
        string qdpout = "/home/morii/temp/temp3.qdp";
        MirQdpTool::MkQdpMode1(da1d, qdpout, "flux", 1.0, "lin", "lin");
        delete da1d;
        printf("=== \n");
    }

    
//    void MkQdpMode1(const DataArray1d* const data_array,
//                    string qdpout,
//                    const MirPlotConf* const plot_conf);
    {
        printf("--- test MkQdpMode1, plotconf\n");
        DataArray1d* da1d = new DataArrayNerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1);
        da1d->SetValElm(1, 2);
        da1d->SetValElm(2, 3);

        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Init(2);
        plot_conf->SetIdimElm(0, "-3", "5", "no",
                              "lin", "index");
        plot_conf->SetIdimElm(1, "-1", "5", "100",
                              "lin", "luminosity");
        
        string qdpout = "/home/morii/temp/temp4.qdp";
        MirQdpTool::MkQdpMode1(da1d, qdpout, plot_conf);
        delete da1d;
        printf("=== \n");
    }


    {
        printf("--- test MkQdpMode1, plotconf\n");
        DataArray1d* da1d = new DataArrayNerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1);
        da1d->SetValElm(1, 2);
        da1d->SetValElm(2, 3);

        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Init(2);
        plot_conf->SetIdimElm(0, "-3", "5", "no",
                              "lin", "index");
        plot_conf->SetIdimElm(1, "-1", "5", "no",
                              "lin", "luminosity");
        
        string qdpout = "/home/morii/temp/temp5.qdp";
        MirQdpTool::MkQdpMode1(da1d, qdpout, plot_conf);
        delete da1d;
        printf("=== \n");
    }
    
//    // format: data  1.0
//   void MkQdpMode2(const DataArray1d* const data_array,
//                    string qdpout,
//                    string title_xval = "",
//                    double offset_xval = 0.0,
//                    string scale_xval = "lin");
    {
        printf("--- test MkQdpMode2\n");
        DataArrayNerr1d* da1d = new DataArrayNerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1);
        da1d->SetValElm(1, 2);
        da1d->SetValElm(2, 3);
        string qdpout = "/home/morii/temp/temp6.qdp";
        MirQdpTool::MkQdpMode2(da1d, qdpout, "flux", 1.0);
        delete da1d;
        printf("=== \n");
    }

//    void MkQdpMode2(const DataArray1d* const data_array,
//                    string qdpout,
//                    const MirPlotConf* const plot_conf);
    {
        printf("--- test MkQdpMode2, plotconf\n");
        DataArray1d* da1d = new DataArraySerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1);
        da1d->SetValElm(1, 2);
        da1d->SetValElm(2, 3);
        da1d->SetValSerrElm(0, 0.1);
        da1d->SetValSerrElm(1, 0.2);
        da1d->SetValSerrElm(2, 0.3);

        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Init(2);
        plot_conf->SetIdimElm(0, "-3", "5", "no",
                              "lin", "index");
        plot_conf->SetIdimElm(1, "-1", "5", "no",
                              "lin", "luminosity");
        string qdpout = "/home/morii/temp/temp7.qdp";
        MirQdpTool::MkQdpMode2(da1d, qdpout, plot_conf);
        delete da1d;
        printf("=== \n");
    }
    
//    // also valid for GraphDataSerr2d, GraphDataTerr2d by polymorphism
//    void MkQdp(const GraphData2d* const graph_data,
//               string qdpout,
//               string format,
//               string title_xval = "",
//               string title_oval = "",
//               double offset_xval = 0.0,
//               double offset_oval = 0.0,
//               string scale_xval = "lin",
//               string scale_oval = "lin");
    {
        printf("--- test MkQdp, GraphDataNerr2d\n");
        GraphData2d* gd2d = new GraphDataNerr2d;
        gd2d->Init(3);
        gd2d->SetPoint(0, 1, 2);
        gd2d->SetPoint(1, 2, 4);
        gd2d->SetPoint(2, 3, 6);
        string qdpout = "/home/morii/temp/temp8.qdp";
        MirQdpTool::MkQdp(gd2d, qdpout, "x,y");
        delete gd2d;
        printf("=== \n");
    }

    {
        printf("--- test MkQdp, GraphDataNerr2d\n");
        GraphData2d* gd2d = new GraphDataNerr2d;
        gd2d->Init(3);
        gd2d->SetPoint(0, 1, 2);
        gd2d->SetPoint(1, 2, 4);
        gd2d->SetPoint(2, 3, 6);
        string qdpout = "/home/morii/temp/temp9.qdp";
        MirQdpTool::MkQdp(gd2d, qdpout, "x,y", "x", "y", 10, 10, "lin", "lin");
        delete gd2d;
        printf("=== \n");
    }

    {
        printf("--- test MkQdp, GraphDataSerr2d\n");
        GraphData2d* gd2d = new GraphDataSerr2d;
        gd2d->Init(3);
        gd2d->SetPoint(0, 1, 0.1, 2, 0.1);
        gd2d->SetPoint(1, 2, 0.2, 4, 0.2);
        gd2d->SetPoint(2, 3, 0.3, 6, 0.3);
        
        string qdpout = "/home/morii/temp/temp10.qdp";
        MirQdpTool::MkQdp(gd2d, qdpout, "x,y,ye", "x", "y", 10, 10);
        delete gd2d;
        printf("=== \n");
    }

    
//    void MkQdp(const GraphData2d* const graph_data,
//               string qdpout,
//               string format,
//               const MirPlotConf* const plot_conf);
    {
        printf("--- test MkQdp, GraphDataNerr2d, plot_conf\n");
        GraphData2d* gd2d = new GraphDataNerr2d;
        gd2d->Init(3);
        gd2d->SetPoint(0, 1, 2);
        gd2d->SetPoint(1, 2, 4);
        gd2d->SetPoint(2, 3, 6);
        string qdpout = "/home/morii/temp/temp11.qdp";

        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Init(2);
        plot_conf->SetIdimElm(0, "-3", "7", "no",
                              "lin", "xx");
        plot_conf->SetIdimElm(1, "-1", "7", "no",
                              "lin", "yy");
        MirQdpTool::MkQdp(gd2d, qdpout, "x,y", plot_conf);
        delete gd2d;
        printf("=== \n");
    }

    {
        printf("--- test MkQdp, GraphDataTerr2d, plot_conf\n");
        GraphData2d* gd2d = new GraphDataTerr2d;
        gd2d->Init(3);
        gd2d->SetPoint(0, 1, 0.3, -0.5, 2, 0.4, -0.1);
        gd2d->SetPoint(1, 2, 0.3, -0.5, 4, 0.4, -0.5);
        gd2d->SetPoint(2, 3, 0.3, -0.5, 6, 0.4, -0.5);
        string qdpout = "/home/morii/temp/temp12.qdp";

        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Init(2);
        plot_conf->SetIdimElm(0, "-3", "7", "no",
                              "lin", "xx");
        plot_conf->SetIdimElm(1, "-1", "7", "no",
                              "lin", "yy");
        MirQdpTool::MkQdp(gd2d, qdpout, "x,xe+,xe-,y,ye+,ye-", plot_conf);
        delete gd2d;
        printf("=== \n");
    }
    
//    // also valid for HistDataSerr1d, HistDataTerr1d by polymorphism
//    void MkQdp(const HistData1d* const hist_data,
//               string outqdp,
//               string format,
//               string title_xval = "",
//               string title_oval = "",
//               double offset_xval = 0.0,
//               double offset_oval = 0.0,
//               string scale_xval = "lin",
//               string scale_oval = "lin");
    {
        printf("--- test MkQdp, HistDataNerr1d\n");
        HistData1d* hd1d = new HistDataNerr1d;
        hd1d->Init(10, 0.0, 10.0);
        for(int ibin = 0; ibin < 10; ibin ++){
            hd1d->SetOvalElm(ibin, ibin);
        }
        string qdpout = "/home/morii/temp/temp13.qdp";
        MirQdpTool::MkQdp(hd1d, qdpout, "x,y");
        delete hd1d;
        printf("=== \n");
    }

    {
        printf("--- test MkQdp, HistDataSerr1d\n");
        HistData1d* hd1d = new HistDataSerr1d;
        hd1d->Init(10, 0.0, 10.0);
        for(int ibin = 0; ibin < 10; ibin ++){
            hd1d->SetOvalElm(ibin, ibin);
            hd1d->SetOvalSerrElm(ibin, ibin * 0.1);
        }
        string qdpout = "/home/morii/temp/temp14.qdp";
        MirQdpTool::MkQdp(hd1d, qdpout, "x,y,ye");
        delete hd1d;
        printf("=== \n");
    }
    
    
//    void MkQdp(const HistData1d* const hist_data,
//               string outqdp,
//               string format,
//               const MirPlotConf* const plot_conf);
    {
        printf("--- test MkQdp, HistDataNerr1d, plot_conf\n");
        HistData1d* hd1d = new HistDataNerr1d;
        hd1d->Init(10, 0.0, 10.0);
        for(int ibin = 0; ibin < 10; ibin ++){
            hd1d->SetOvalElm(ibin, ibin);
        }
        string qdpout = "/home/morii/temp/temp15.qdp";
        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Init(2);
        plot_conf->SetIdimElm(0, "-3", "7", "no",
                              "lin", "xx");
        plot_conf->SetIdimElm(1, "-1", "7", "no",
                              "lin", "yy");
        MirQdpTool::MkQdp(hd1d, qdpout, "x,y", plot_conf);
        delete hd1d;
        printf("=== \n");
    }

//    void MkQdp(const MirFunc* const func, const double* const par,
//               int npoint, double xval_lo, double xval_up,
//               string outqdp,
//               string title_xval = "",
//               string title_oval = "",
//               double offset_xval = 0.0,
//               double offset_oval = 0.0,
//               string scale_xval = "lin",
//               string scale_oval = "lin");
    {
        printf("--- test MkQdp, MirFunc\n");
        MirFunc* func = new Gauss1dFunc;

        double mu = 1.0;
        double sigma = 1.0;
        double norm = 1.0;
        double par[3];
        par[0] = mu;
        par[1] = sigma;
        par[2] = norm;
        string qdpout = "/home/morii/temp/temp16.qdp";
        MirQdpTool::MkQdp(func, par, 1000, -10, 10, qdpout);
        delete func;
        printf("=== \n");
    }

//    void MkQdp(const MirFunc* const func, const double* const par,
//               int npoint, double xval_lo, double xval_up,
//               string outqdp,
//               const MirPlotConf* const plot_conf);
    {
        printf("--- test MkQdp, MirFunc\n");
        MirFunc* func = new Gauss1dFunc;

        double mu = 1.0;
        double sigma = 1.0;
        double norm = 1.0;
        double par[3];
        par[0] = mu;
        par[1] = sigma;
        par[2] = norm;
        string qdpout = "/home/morii/temp/temp17.qdp";

        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Init(2);
        plot_conf->SetIdimElm(0, "-3", "7", "no",
                              "lin", "xx");
        plot_conf->SetIdimElm(1, "-1", "7", "no",
                              "lin", "yy");
        MirQdpTool::MkQdp(func, par, 1000, -10, 10, qdpout, plot_conf);
        delete func;
        printf("=== \n");
    }

//    void MkQdp(const Interval* const interval,
//               string qdpout,
//               string title_xval = "",
//               double offset_xval = 0.0,
//               string scale_xval = "lin");
//    void MkQdp(const Interval* const interval,
//               string qdpout,
//               const MirPlotConf* const plot_conf);
//
//    void MkQdpDiff(const GraphData2d* const graph_data,
//                   const GraphData2d* const graph_model,
//                   const GraphData2d* const graph_res,
//                   string qdpout,
//                   string format,
//                   string title_xval = "",
//                   string title_oval = "",
//                   string title_oval_res = "",
//                   double offset_xval = 0.0,
//                   double offset_oval = 0.0,
//                   double offset_oval_res = 0.0,
//                   string scale_xval = "lin",
//                   string scale_oval = "lin",
//                   string scale_oval_res = "lin");
//    void MkQdpDiff(const GraphData2d* const graph_data,
//                   const GraphData2d* const graph_model,
//                   const GraphData2d* const graph_res,
//                   string qdpout,
//                   string format,
//                   const MirPlotConf* const plot_conf);
//    
//    void MkQdpDiff(const HistData1d* const hist_data,
//                   const HistData1d* const hist_model,
//                   const HistData1d* const hist_res,
//                   string qdpout,
//                   string format,
//                   string title_xval = "",
//                   string title_oval = "",
//                   string title_oval_res = "",
//                   double offset_xval = 0.0,
//                   double offset_oval = 0.0,
//                   double offset_oval_res = 0.0,
//                   string scale_xval = "lin",
//                   string scale_oval = "lin",
//                   string scale_oval_res = "lin");
//    void MkQdpDiff(const HistData1d* const hist_data,
//                   const HistData1d* const hist_model,
//                   const HistData1d* const hist_res,
//                   string qdpout,
//                   string format,
//                   const MirPlotConf* const plot_conf);
//    
//    void MkQdpDiff3(const GraphDataSerr2d* const graph_data,
//                    const MirFunc* const func, const double* const par,
//                    int npoint_func,
//                    string outdir, string qdpout_head,
//                    string title_xval = "",
//                    string title_oval = "",
//                    double offset_xval = 0.0,
//                    double offset_oval = 0.0,
//                    string scale_xval = "lin",
//                    string scale_oval = "lin");
//    void MkQdpDiff3(const GraphDataSerr2d* const graph_data,
//                    const MirFunc* const func, const double* const par,
//                    int npoint_func,
//                    string outdir, string qdpout_head,
//                    const MirPlotConf* const plot_conf);
//    void MkQdpDiff3(const GraphDataSerr2d* const graph_data,
//                    const GraphData2d* const graph_model,
//                    string outdir, string qdpout_head,
//                    const MirPlotConf* const plot_conf);
//    
//    void MkQdpDiff3(const HistDataSerr1d* const hist_data,
//                    const MirFunc* const func, const double* const par,
//                    int npoint_func,
//                    string outdir, string qdpout_head,
//                    string title_xval = "",
//                    string title_oval = "",
//                    double offset_xval = 0.0,
//                    double offset_oval = 0.0,
//                    string scale_xval = "lin",
//                    string scale_oval = "lin");
//    void MkQdpDiff3(const HistDataSerr1d* const hist_data,
//                    const MirFunc* const func, const double* const par,
//                    int npoint_func,
//                    string outdir, string qdpout_head,
//                    const MirPlotConf* const plot_conf);
//    void MkQdpDiff3(const HistDataSerr1d* const hist_data,
//                    const HistData1d* const hist_model,
//                    string outdir, string qdpout_head,
//                    const MirPlotConf* const plot_conf);
//
//    void MkQdpMinFcn(const HistData1d* const hist_data,
//                     string outqdp,
//                     double xval_at_fcnmin,
//                     double xval_terr_minus,
//                     double xval_terr_plus,
//                     double fcnmin,
//                     string title_xval = "");
//    
//    // plot N HistData in one qdp file
//    void MkQdpNhist(const HistData1d* const* const hist_arr, int nhist,
//                    string qdpout,
//                    double offset_xval = 0.0);
//
//    void MkQdpProj(const MirFunc* const func, const double* const par,
//                   double xval_lo, double xval_up, double yval_lo, double yval_up,
//                   string outdir, string qdpout_head, string calc_mode,
//                   int npoint_func,
//                   string title_xval = "",
//                   string title_yval = "",
//                   string title_oval = "",
//                   double offset_xval = 0.0,
//                   double offset_yval = 0.0,
//                   double offset_oval = 0.0,
//                   string scale_xval = "lin",
//                   string scale_yval = "lin",
//                   string scale_oval = "lin");
//    void MkQdpProj(const MirFunc* const func, const double* const par,
//                   double xval_lo, double xval_up, double yval_lo, double yval_up,
//                   string outdir, string qdpout_head, string calc_mode,
//                   int npoint_func,
//                   const MirPlotConf* const plot_conf_projx,
//                   const MirPlotConf* const plot_conf_projy);
//    
//    void MkQdpDiffProj(const HistDataSerr2d* const hist_data,
//                       const MirFunc* const func, const double* const par,
//                       string outdir, string qdpout_head,
//                       string add_mode, string error_mode,
//                       string title_xval = "",
//                       string title_yval = "",
//                       string title_oval = "",                              
//                       double offset_xval = 0.0,
//                       double offset_yval = 0.0,
//                       double offset_oval = 0.0,
//                       string scale_xval = "lin",
//                       string scale_yval = "lin",
//                       string scale_oval = "lin");
//    void MkQdpDiffProj(const HistDataSerr2d* const hist_data,
//                       const MirFunc* const func, const double* const par,
//                       string outdir, string qdpout_head,
//                       string add_mode, string error_mode,
//                       const MirPlotConf* const plot_conf_projx,
//                       const MirPlotConf* const plot_conf_projy);
//    
//    void MkQdpCont(const HistData2d* const h2d,
//                   string qdpout, int ncont,
//                   string title_xval = "",
//                   string title_yval = "",
//                   string title_oval = "",
//                   double offset_xval = 0.0,
//                   double offset_yval = 0.0,
//                   double offset_oval = 0.0);
//
//    void MkQdpContMinFcn(const HistData2d* const h2d,
//                         string qdpout,
//                         string title_xval = "",
//                         string title_yval = "",
//                         string title_oval = "",
//                         double offset_xval = 0.0,
//                         double offset_yval = 0.0,
//                         double offset_oval = 0.0);
//
//    void MkQdpContMinFcnWithBest(const HistData2d* const h2d,
//                                 string qdpout,
//                                 double xval_best,
//                                 double yval_best,
//                                 double zval_best,
//                                 string title_xval = "",
//                                 string title_yval = "",
//                                 string title_oval = "",
//                                 double offset_xval = 0.0,
//                                 double offset_yval = 0.0,
//                                 double offset_oval = 0.0);
  

    return status_prog;
}