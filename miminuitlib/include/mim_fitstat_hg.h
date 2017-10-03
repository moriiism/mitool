#ifndef MORIIISM_MITOOL_MIMINUITLIB_FITSTAT_HG_H_
#define MORIIISM_MITOOL_MIMINUITLIB_FITSTAT_HG_H_

#include "mir_data1d_serr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_ope.h"
#include "mir_hist1d_serr.h"
#include "mir_hist2d_serr.h"
#include "mir_qdp_tool.h"
#include "mim_chi2plot.h"
#include "mim_qdp_tool.h"

// FitStat for Graph and Hist
class FitStatHG : public MiObject{
public:
    explicit FitStatHG(string title = "") :
        MiObject("FitStatHG", title),
        fit_stat_init_(NULL),
        fit_stat_(NULL),
        hist1d_res_val_(NULL),
        hist1d_res_chi_(NULL),
        hist1d_res_ratio_(NULL),
        hist2d_res_val_(NULL),
        hist2d_res_chi_(NULL),
        hist2d_res_ratio_(NULL),
        graph2d_res_val_(NULL),
        graph2d_res_chi_(NULL),
        graph2d_res_ratio_(NULL),
        graph3d_res_val_(NULL),
        graph3d_res_chi_(NULL),
        graph3d_res_ratio_(NULL),

        nhist_chi2_(0),
        chi2plot_par_(NULL),
        hist_chi2_arr_(NULL),
        hist_valid_arr_(NULL),
        hist_edm_arr_(NULL),
        hist_flag_bad_neg_arr_(NULL),
        hist_index1_arr_(NULL),
        fit_stat_chi2_search_arr_(NULL),
        par_at_min_chi2plot_arr_(NULL),
        par_err_plus_end_chi2plot_arr_(NULL),
        par_err_minus_end_chi2plot_arr_(NULL),

        nhist_chi2_cont_(0),
        chi2plot_cont_par_(NULL),
        hist_chi2_cont_arr_(NULL),
        hist_valid_cont_arr_(NULL),
        hist_edm_cont_arr_(NULL),
        hist_flag_bad_neg_cont_arr_(NULL),
        hist_index2_cont_arr_(NULL),
        fit_stat_chi2cont_search_arr_(NULL),
        par0_at_min_chi2plot_cont_arr_(NULL),
        par0_err_plus_end_chi2plot_cont_arr_(NULL),
        par0_err_minus_end_chi2plot_cont_arr_(NULL),
        par1_at_min_chi2plot_cont_arr_(NULL),
        par1_err_plus_end_chi2plot_cont_arr_(NULL),
        par1_err_minus_end_chi2plot_cont_arr_(NULL),

        fit_param_best_(NULL) {}
    ~FitStatHG() {
        Null();
    }

    // Init & Set
    
    void InitSetFitStatInit(const FitStat* const fit_stat_init);
    void InitSetFitStat(const FitStat* const fit_stat);
    void InitSetHd1(const HistDataSerr1d* const hist1d_res_val,
                    const HistDataSerr1d* const hist1d_res_chi,
                    const HistDataSerr1d* const hist1d_res_ratio);
    void InitSetHd2(const HistDataSerr2d* const hist2d_res_val,
                    const HistDataSerr2d* const hist2d_res_chi,
                    const HistDataSerr2d* const hist2d_res_ratio);
    void InitSetGd2(const GraphDataSerr2d* const graph2d_res_val,
                    const GraphDataSerr2d* const graph2d_res_chi,
                    const GraphDataSerr2d* const graph2d_res_ratio);
    void InitSetGd3(const GraphDataSerr3d* const graph3d_res_val,
                    const GraphDataSerr3d* const graph3d_res_chi,
                    const GraphDataSerr3d* const graph3d_res_ratio);
    void InitSetChi2(const Chi2PlotPar* const chi2plot_par,
                     const HistData1d* const* const hist_chi2_arr,
                     const HistData1d* const* const hist_valid_arr,
                     const HistData1d* const* const hist_edm_arr,
                     const HistData1d* const* const hist_flag_bad_neg_arr,
                     const HistData1d* const* const* const hist_index1_arr,
                     const FitStat* const* const* const fit_stat_chi2_search_arr);
    void InitSetChi2Cont(const Chi2PlotContPar* const chi2plot_cont_par,
                         const HistData2d* const* const hist_chi2_cont_arr,
                         const HistData2d* const* const hist_valid_cont_arr,
                         const HistData2d* const* const hist_edm_cont_arr,
                         const HistData2d* const* const hist_flag_bad_neg_cont_arr,
                         const HistData2d* const* const* const hist_index2_cont_arr,
                         const FitStat* const* const* const* const fit_stat_chi2cont_search_arr);

    void InitSetChi2ErrEnd(int nhist,
                           const double* const par_at_min_chi2plot_arr,
                           const double* const par_err_plus_end_chi2plot_arr,
                           const double* const par_err_minus_end_chi2plot_arr);
    void InitSetChi2ContErrEnd(int nhist,
                               const double* const par0_at_min_chi2plot_cont_arr,
                               const double* const par0_err_plus_end_chi2plot_cont_arr,
                               const double* const par0_err_minus_end_chi2plot_cont_arr,
                               const double* const par1_at_min_chi2plot_cont_arr,
                               const double* const par1_err_plus_end_chi2plot_cont_arr,
                               const double* const par1_err_minus_end_chi2plot_cont_arr);

    void InitSetH1dByFunc(const HistDataSerr1d* const h1d_data, const MirFunc* const func);
    void InitSetH2dByFunc(const HistDataSerr2d* const h2d_data, const MirFunc* const func);
    void InitSetG2dByFunc(const GraphDataSerr2d* const g2d_data, const MirFunc* const func);
    void InitSetG3dByFunc(const GraphDataSerr3d* const g3d_data, const MirFunc* const func);

    void InitSetFitParamBest(const FitParam* const fit_param_best);

    FitStatHG* const Clone() const { abort();};
    
    //
    // const functions
    //
    
    // Get
    const FitStat* const GetFitStatInit() const {return fit_stat_init_;};
    const FitStat* const GetFitStat() const {return fit_stat_;};
    const HistDataSerr1d* const GetHist1dResVal() const {return hist1d_res_val_;};
    const HistDataSerr1d* const GetHist1dResChi() const {return hist1d_res_chi_;};
    const HistDataSerr1d* const GetHist1dResRatio() const {return hist1d_res_ratio_;};

    const HistDataSerr2d* const GetHist2dResVal() const {return hist2d_res_val_;};
    const HistDataSerr2d* const GetHist2dResChi() const {return hist2d_res_chi_;};
    const HistDataSerr2d* const GetHist2dResRatio() const {return hist2d_res_ratio_;};

    const GraphDataSerr2d* const GetGraph2dResVal() const {return graph2d_res_val_;};
    const GraphDataSerr2d* const GetGraph2dResChi() const {return graph2d_res_chi_;};
    const GraphDataSerr2d* const GetGraph2dResRatio() const {return graph2d_res_ratio_;};
  
    const GraphDataSerr3d* const GetGraph3dResVal() const {return graph3d_res_val_;};
    const GraphDataSerr3d* const GetGraph3dResChi() const {return graph3d_res_chi_;};
    const GraphDataSerr3d* const GetGraph3dResRatio() const {return graph3d_res_ratio_;};

    int GetNhistChi2() const {return nhist_chi2_;};
    const Chi2PlotPar* const GetChi2PlotPar() const {return chi2plot_par_;};
    const HistData1d* const* const GetHistChi2Arr() const {return hist_chi2_arr_;};
    const HistData1d* const* const GetHistValidArr() const {return hist_valid_arr_;};
    const HistData1d* const* const GetHistEdmArr() const {return hist_edm_arr_;};
    const HistData1d* const* const GetHistFlagBadNegArr() const {return hist_flag_bad_neg_arr_;};
    const HistData1d* const* const* const GetHistIndex1Arr() const {return hist_index1_arr_;};
    
    const HistData1d* const GetHistChi2ArrElm(int ihist) const {return hist_chi2_arr_[ihist];};
    const HistData1d* const GetHistValidArrElm(int ihist) const {return hist_valid_arr_[ihist];};
    const HistData1d* const GetHistEdmArrElm(int ihist) const {return hist_edm_arr_[ihist];};
    const HistData1d* const GetHistFlagBadNegArrElm(int ihist) const
        {return hist_flag_bad_neg_arr_[ihist];};
    const HistData1d* const GetHistIndex1ArrElm(int ihist, int inum) const
        {return hist_index1_arr_[ihist][inum];};
    const FitStat* const* const* const GetFitStatChi2SearchArr() const
        {return fit_stat_chi2_search_arr_;};

    const double* const GetParAtMinChi2plotArr() const
        {return par_at_min_chi2plot_arr_;};
    const double* const GetParErrPlusEndChi2plotArr() const
        {return par_err_plus_end_chi2plot_arr_;};
    const double* const GetParErrMinusEndChi2plotArr() const
        {return par_err_minus_end_chi2plot_arr_;};
    double GetParAtMinChi2plotArrElm(int ihist) const
        {return par_at_min_chi2plot_arr_[ihist];};
    double GetParErrPlusEndChi2plotArrElm(int ihist) const
        {return par_err_plus_end_chi2plot_arr_[ihist];};
    double GetParErrMinusEndChi2plotArrElm(int ihist) const
        {return par_err_minus_end_chi2plot_arr_[ihist];};

    
    int GetNhistChi2Cont() const {return nhist_chi2_cont_;};
    const Chi2PlotContPar* const GetChi2PlotContPar() const {return chi2plot_cont_par_;};
    const HistData2d* const* const GetHistChi2ContArr() const {return hist_chi2_cont_arr_;};
    const HistData2d* const* const GetHistValidContArr() const {return hist_valid_cont_arr_;};
    const HistData2d* const* const GetHistEdmContArr() const {return hist_edm_cont_arr_;};
    const HistData2d* const* const GetHistFlagBadNegContArr() const {return hist_flag_bad_neg_cont_arr_;};
    const HistData2d* const* const* const GetHistIndex2ContArr() const {return hist_index2_cont_arr_;};
    
    const HistData2d* const GetHistChi2ContArrElm(int ihist) const {return hist_chi2_cont_arr_[ihist];};    
    const HistData2d* const GetHistValidContArrElm(int ihist) const {return hist_valid_cont_arr_[ihist];};
    const HistData2d* const GetHistEdmContArrElm(int ihist) const {return hist_edm_cont_arr_[ihist];};
    const HistData2d* const GetHistFlagBadNegContArrElm(int ihist) const {return hist_flag_bad_neg_cont_arr_[ihist];};
    const HistData2d* const GetHistIndex2ContArrElm(int ihist, int inum) const
        {return hist_index2_cont_arr_[ihist][inum];};
    
    const FitStat* const* const* const* const GetFitStatChi2ContSearchArr() const {return fit_stat_chi2cont_search_arr_;};

    const double* const GetPar0AtMinChi2plotContArr() const
        {return par0_at_min_chi2plot_cont_arr_;};
    const double* const GetPar0ErrPlusEndChi2plotContArr() const
        {return par0_err_plus_end_chi2plot_cont_arr_;};
    const double* const GetPar0ErrMinusEndChi2plotContArr() const
        {return par0_err_minus_end_chi2plot_cont_arr_;};
    const double* const GetPar1AtMinChi2plotContArr() const
        {return par1_at_min_chi2plot_cont_arr_;};    
    const double* const GetPar1ErrPlusEndChi2plotContArr() const
        {return par1_err_plus_end_chi2plot_cont_arr_;};
    const double* const GetPar1ErrMinusEndChi2plotContArr() const
        {return par1_err_minus_end_chi2plot_cont_arr_;};

    double GetPar0AtMinChi2plotContArrElm(int ihist) const
        {return par0_at_min_chi2plot_cont_arr_[ihist];};
    double GetPar0ErrPlusEndChi2plotContArrElm(int ihist) const
        {return par0_err_plus_end_chi2plot_cont_arr_[ihist];};
    double GetPar0ErrMinusEndChi2plotContArrElm(int ihist) const
        {return par0_err_minus_end_chi2plot_cont_arr_[ihist];};
    double GetPar1AtMinChi2plotContArrElm(int ihist) const
        {return par1_at_min_chi2plot_cont_arr_[ihist];};    
    double GetPar1ErrPlusEndChi2plotContArrElm(int ihist) const
        {return par1_err_plus_end_chi2plot_cont_arr_[ihist];};
    double GetPar1ErrMinusEndChi2plotContArrElm(int ihist) const
        {return par1_err_minus_end_chi2plot_cont_arr_[ihist];};    

    FitParam* const GetFitParamBest() const {return fit_param_best_;};
    
    void PrintInfo(FILE* fp) const;
                      
    void MkOutParSearch1d(string outdir,
                          string outfile_head,
                          string flag_name_length) const;
    void MkOutParSearch2d(string outdir,
                          string outfile_head,
                          string flag_name_length,
                          MirRootTool* const root_tool) const;
    void PrintErrByParSearch1d(FILE* fp) const;
    void PrintErrByParSearch2d(FILE* fp) const;


    // MkOutBestFit --> MkOutFitPlot

    static void MkOutFitPlot(const HistDataSerr1d* const h1d_data,
                             const MirFunc* const func,
                             const double* const par_arr,
                             int npoint_func,
                             string outdir,
                             string outfile_head,
                             const MirPlotConf* const plot_conf);
    static void MkOutFitPlot(const HistDataSerr2d* const h2d_data,
                             const MirFunc* const func,
                             const double* const par_arr,
                             string outdir,
                             string outfile_head,
                             const MirPlotConf* const plot_conf_projx,
                             const MirPlotConf* const plot_conf_projy,
                             MirRootTool* const root_tool);
    static void MkOutFitPlot(const GraphDataSerr2d* const g2d_data,
                             const MirFunc* const func,
                             const double* const par_arr,
                             int npoint_func,
                             string outdir,
                             string outfile_head,
                             const MirPlotConf* const plot_conf);

private:

    FitStat* fit_stat_init_;  // before fit
    FitStat* fit_stat_;

    HistDataSerr1d* hist1d_res_val_;
    HistDataSerr1d* hist1d_res_chi_;
    HistDataSerr1d* hist1d_res_ratio_;

    HistDataSerr2d* hist2d_res_val_;
    HistDataSerr2d* hist2d_res_chi_;
    HistDataSerr2d* hist2d_res_ratio_;

    GraphDataSerr2d* graph2d_res_val_;
    GraphDataSerr2d* graph2d_res_chi_;
    GraphDataSerr2d* graph2d_res_ratio_;

    GraphDataSerr3d* graph3d_res_val_;
    GraphDataSerr3d* graph3d_res_chi_;
    GraphDataSerr3d* graph3d_res_ratio_;

    int nhist_chi2_;
    Chi2PlotPar* chi2plot_par_; 
    HistData1d** hist_chi2_arr_;
    HistData1d** hist_valid_arr_;
    HistData1d** hist_edm_arr_;
    HistData1d** hist_flag_bad_neg_arr_;
    HistData1d*** hist_index1_arr_;
    // histogram to check the parameter of index1
    FitStat*** fit_stat_chi2_search_arr_;
    double* par_at_min_chi2plot_arr_;
    double* par_err_plus_end_chi2plot_arr_;
    double* par_err_minus_end_chi2plot_arr_;

    int nhist_chi2_cont_;
    Chi2PlotContPar* chi2plot_cont_par_;
    HistData2d** hist_chi2_cont_arr_;
    HistData2d** hist_valid_cont_arr_;
    HistData2d** hist_edm_cont_arr_;
    HistData2d** hist_flag_bad_neg_cont_arr_;
    HistData2d*** hist_index2_cont_arr_;
    // histogram to check the parameter of index2
    FitStat**** fit_stat_chi2cont_search_arr_;
    double* par0_at_min_chi2plot_cont_arr_;
    double* par0_err_plus_end_chi2plot_cont_arr_;
    double* par0_err_minus_end_chi2plot_cont_arr_;
    double* par1_at_min_chi2plot_cont_arr_;
    double* par1_err_plus_end_chi2plot_cont_arr_;
    double* par1_err_minus_end_chi2plot_cont_arr_;

    // compile of the best values and error regions
    FitParam* fit_param_best_;
    
    void Null();
    void NullFitStatInit();
    void NullFitStat();
    void NullHd1();
    void NullHd2();
    void NullGd2();
    void NullGd3();
    void NullParSearch1d();
    void NullParSearch2d();
    void NullChi2ErrEnd();
    void NullChi2ContErrEnd();
    void NullFitParamBest();
};


#endif // MORIIISM_MITOOL_MIMINUITLIB_FITSTAT_HG_H_
