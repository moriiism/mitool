#include "mim_fitstat_hg.h"

//
// public
//

void FitStatHG::InitSetFitStatInit(const FitStat* const fit_stat_init)
{
    NullFitStatInit();
    
    fit_stat_init_ = new FitStat;
    fit_stat_init_->Copy(fit_stat_init);
}

void FitStatHG::InitSetFitStat(const FitStat* const fit_stat)
{
    NullFitStat();
    
    fit_stat_ = new FitStat;
    fit_stat_->Copy(fit_stat);
}

void FitStatHG::InitSetHd1(const HistDataSerr1d* const hist1d_res_val,
                           const HistDataSerr1d* const hist1d_res_chi,
                           const HistDataSerr1d* const hist1d_res_ratio)
{
    NullHd1();
    
    hist1d_res_val_ = new HistDataSerr1d;
    hist1d_res_val_->Copy(hist1d_res_val);
    hist1d_res_chi_ = new HistDataSerr1d;
    hist1d_res_chi_->Copy(hist1d_res_chi);
    hist1d_res_ratio_ = new HistDataSerr1d;
    hist1d_res_ratio_->Copy(hist1d_res_ratio);
}

void FitStatHG::InitSetHd2(const HistDataSerr2d* const hist2d_res_val,
                           const HistDataSerr2d* const hist2d_res_chi,
                           const HistDataSerr2d* const hist2d_res_ratio)
{
    NullHd2();
    
    hist2d_res_val_ = new HistDataSerr2d;
    hist2d_res_val_->Copy(hist2d_res_val);
    hist2d_res_chi_ = new HistDataSerr2d;
    hist2d_res_chi_->Copy(hist2d_res_chi);
    hist2d_res_ratio_ = new HistDataSerr2d;
    hist2d_res_ratio_->Copy(hist2d_res_ratio);
}


void FitStatHG::InitSetGd2(const GraphDataSerr2d* const graph2d_res_val,
                           const GraphDataSerr2d* const graph2d_res_chi,
                           const GraphDataSerr2d* const graph2d_res_ratio)
{
    NullGd2();
    
    graph2d_res_val_  = new GraphDataSerr2d;
    graph2d_res_val_->Copy(graph2d_res_val);
    graph2d_res_chi_  = new GraphDataSerr2d;
    graph2d_res_chi_->Copy(graph2d_res_chi);
    graph2d_res_ratio_ = new GraphDataSerr2d;
    graph2d_res_ratio_->Copy(graph2d_res_ratio);
}

void FitStatHG::InitSetGd3(const GraphDataSerr3d* const graph3d_res_val,
                           const GraphDataSerr3d* const graph3d_res_chi,
                           const GraphDataSerr3d* const graph3d_res_ratio)
{
    NullGd3();
    
    graph3d_res_val_ = new GraphDataSerr3d;
    graph3d_res_val_->Copy(graph3d_res_val);
    graph3d_res_chi_ = new GraphDataSerr3d;
    graph3d_res_chi_->Copy(graph3d_res_chi);
    graph3d_res_ratio_ = new GraphDataSerr3d;
    graph3d_res_ratio_->Copy(graph3d_res_ratio);
}

void FitStatHG::InitSetChi2(const Chi2PlotPar* const chi2plot_par,
                            const HistData1d* const* const hist_chi2_arr,
                            const HistData1d* const* const hist_valid_arr,
                            const HistData1d* const* const hist_edm_arr,
                            const HistData1d* const* const hist_flag_bad_neg_arr,
                            const HistData1d* const* const* const hist_index1_arr,
                            const FitStat* const* const* const fit_stat_chi2_search_arr)
{
    if(0 < g_flag_verbose){
        MPrintInfoClass("start...");
    }

    NullParSearch1d();
    
    chi2plot_par_ = new Chi2PlotPar;
    chi2plot_par_->Copy(chi2plot_par);

    nhist_chi2_ = chi2plot_par_->GetNpar();
    hist_chi2_arr_  = new HistData1d* [nhist_chi2_];
    hist_valid_arr_ = new HistData1d* [nhist_chi2_];
    hist_edm_arr_   = new HistData1d* [nhist_chi2_];
    hist_flag_bad_neg_arr_ = new HistData1d* [nhist_chi2_];
    hist_index1_arr_  = new HistData1d** [nhist_chi2_];
    for(int ihist = 0; ihist < nhist_chi2_; ihist++){
        hist_chi2_arr_[ihist] = new HistDataNerr1d;
        hist_chi2_arr_[ihist]->Copy(hist_chi2_arr[ihist]);
        hist_valid_arr_[ihist] = new HistDataNerr1d;
        hist_valid_arr_[ihist]->Copy(hist_valid_arr[ihist]);
        hist_edm_arr_[ihist] = new HistDataNerr1d;
        hist_edm_arr_[ihist]->Copy(hist_edm_arr[ihist]);
        hist_flag_bad_neg_arr_[ihist] = new HistDataNerr1d;
        hist_flag_bad_neg_arr_[ihist]->Copy(hist_flag_bad_neg_arr[ihist]);

        int num_index1 = chi2plot_par_->GetNumIndex1Elm(ihist);
        hist_index1_arr_[ihist] = new HistData1d* [num_index1];
        for(int inum = 0; inum < num_index1; inum++){
            hist_index1_arr_[ihist][inum] = new HistDataNerr1d;
            hist_index1_arr_[ihist][inum]->Copy(hist_index1_arr[ihist][inum]);
        }
    }

    fit_stat_chi2_search_arr_ = new FitStat** [nhist_chi2_];
    for(int ihist = 0; ihist < nhist_chi2_; ihist++){
        int nstep = chi2plot_par_->GetNstepElm(ihist);
        fit_stat_chi2_search_arr_[ihist] = new FitStat* [nstep];
        for(int istep = 0; istep < nstep; istep++){
            fit_stat_chi2_search_arr_[ihist][istep] = new FitStat;
            fit_stat_chi2_search_arr_[ihist][istep]->Copy(fit_stat_chi2_search_arr[ihist][istep]);
        }
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}
  
void FitStatHG::InitSetChi2Cont(const Chi2PlotContPar* const chi2plot_cont_par,
                                const HistData2d* const* const hist_chi2_cont_arr,
                                const HistData2d* const* const hist_valid_cont_arr,
                                const HistData2d* const* const hist_edm_cont_arr,
                                const HistData2d* const* const hist_flag_bad_neg_cont_arr,
                                const HistData2d* const* const* const hist_index2_cont_arr,
                                const FitStat* const* const* const* const fit_stat_chi2cont_search_arr)
{
    if(0 < g_flag_verbose){
        MPrintInfoClass("start...");
    }

    NullParSearch2d();
    
    chi2plot_cont_par_ = new Chi2PlotContPar;
    chi2plot_cont_par_->Copy(chi2plot_cont_par);
    
    nhist_chi2_cont_ = chi2plot_cont_par_->GetNcont();
    hist_chi2_cont_arr_  = new HistData2d* [nhist_chi2_cont_];
    hist_valid_cont_arr_ = new HistData2d* [nhist_chi2_cont_];
    hist_edm_cont_arr_   = new HistData2d* [nhist_chi2_cont_];
    hist_flag_bad_neg_cont_arr_ = new HistData2d* [nhist_chi2_cont_];
    
    hist_index2_cont_arr_  = new HistData2d** [nhist_chi2_cont_];
    for(int ihist = 0; ihist < nhist_chi2_cont_; ihist++){
        hist_chi2_cont_arr_[ihist] = new HistDataNerr2d;
        hist_chi2_cont_arr_[ihist]->Copy(hist_chi2_cont_arr[ihist]);
        hist_valid_cont_arr_[ihist] = new HistDataNerr2d;
        hist_valid_cont_arr_[ihist]->Copy(hist_valid_cont_arr[ihist]);
        hist_edm_cont_arr_[ihist] = new HistDataNerr2d;
        hist_edm_cont_arr_[ihist]->Copy(hist_edm_cont_arr[ihist]);
        hist_flag_bad_neg_cont_arr_[ihist] = new HistDataNerr2d;
        hist_flag_bad_neg_cont_arr_[ihist]->Copy(hist_flag_bad_neg_cont_arr[ihist]);

        int num_index2 = chi2plot_cont_par_->GetNumIndex2Elm(ihist);
        hist_index2_cont_arr_[ihist] = new HistData2d* [num_index2];
        for(int inum = 0; inum < num_index2; inum++){
            hist_index2_cont_arr_[ihist][inum] = new HistDataNerr2d;
            hist_index2_cont_arr_[ihist][inum]->Copy(hist_index2_cont_arr[ihist][inum]);
        }
    }
    
    fit_stat_chi2cont_search_arr_ = new FitStat*** [nhist_chi2_cont_];
    for(int ihist = 0; ihist < nhist_chi2_cont_; ihist++){
        int nstep0 = chi2plot_cont_par_->GetNstep0Elm(ihist);
        int nstep1 = chi2plot_cont_par_->GetNstep1Elm(ihist);
        fit_stat_chi2cont_search_arr_[ihist] = new FitStat** [nstep0];
        for(int istep0 = 0; istep0 < nstep0; istep0++){
            fit_stat_chi2cont_search_arr_[ihist][istep0] = new FitStat* [nstep1];
            for(int istep1 = 0; istep1 < nstep1; istep1++){
                fit_stat_chi2cont_search_arr_[ihist][istep0][istep1] = new FitStat;
                fit_stat_chi2cont_search_arr_[ihist][istep0][istep1]
                    ->Copy(fit_stat_chi2cont_search_arr[ihist][istep0][istep1]);
            }
        }
    }
    
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void FitStatHG::InitSetChi2ErrEnd(int nhist,
                                  const double* const par_at_min_chi2plot_arr,
                                  const double* const par_err_plus_end_chi2plot_arr,
                                  const double* const par_err_minus_end_chi2plot_arr)
{
    NullChi2ErrEnd();

    par_at_min_chi2plot_arr_        = new double [nhist];
    par_err_plus_end_chi2plot_arr_  = new double [nhist];
    par_err_minus_end_chi2plot_arr_ = new double [nhist];
    for(int ihist = 0; ihist < nhist; ihist ++){
        par_at_min_chi2plot_arr_[ihist]        = par_at_min_chi2plot_arr[ihist];
        par_err_plus_end_chi2plot_arr_[ihist]  = par_err_plus_end_chi2plot_arr[ihist];
        par_err_minus_end_chi2plot_arr_[ihist] = par_err_minus_end_chi2plot_arr[ihist];
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    
}

void FitStatHG::InitSetChi2ContErrEnd(int nhist,
                                      const double* const par0_at_min_chi2plot_cont_arr,
                                      const double* const par0_err_plus_end_chi2plot_cont_arr,
                                      const double* const par0_err_minus_end_chi2plot_cont_arr,
                                      const double* const par1_at_min_chi2plot_cont_arr,
                                      const double* const par1_err_plus_end_chi2plot_cont_arr,
                                      const double* const par1_err_minus_end_chi2plot_cont_arr)
{
    NullChi2ContErrEnd();

    par0_at_min_chi2plot_cont_arr_        = new double [nhist];
    par0_err_plus_end_chi2plot_cont_arr_  = new double [nhist];
    par0_err_minus_end_chi2plot_cont_arr_ = new double [nhist];
    par1_at_min_chi2plot_cont_arr_        = new double [nhist];
    par1_err_plus_end_chi2plot_cont_arr_  = new double [nhist];
    par1_err_minus_end_chi2plot_cont_arr_ = new double [nhist];
    for(int ihist = 0; ihist < nhist; ihist ++){
        par0_at_min_chi2plot_cont_arr_[ihist]        = par0_at_min_chi2plot_cont_arr[ihist];
        par0_err_plus_end_chi2plot_cont_arr_[ihist]  = par0_err_plus_end_chi2plot_cont_arr[ihist];
        par0_err_minus_end_chi2plot_cont_arr_[ihist] = par0_err_minus_end_chi2plot_cont_arr[ihist];
        par1_at_min_chi2plot_cont_arr_[ihist]        = par1_at_min_chi2plot_cont_arr[ihist];
        par1_err_plus_end_chi2plot_cont_arr_[ihist]  = par1_err_plus_end_chi2plot_cont_arr[ihist];
        par1_err_minus_end_chi2plot_cont_arr_[ihist] = par1_err_minus_end_chi2plot_cont_arr[ihist];
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    
}


void FitStatHG::InitSetH1dByFunc(const HistDataSerr1d* const h1d_data, const MirFunc* const func)
{
    HistDataSerr1d* h1d_res_val = new HistDataSerr1d;
    HistDataSerr1d* h1d_res_chi = new HistDataSerr1d;
    HistDataSerr1d* h1d_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1d(h1d_data,
                                 func, GetFitStat()->GetFitParam()->GetPar(),
                                 h1d_res_val);
    HistData1dOpe::GetResChiHd1d(h1d_data,
                                func, GetFitStat()->GetFitParam()->GetPar(),
                                h1d_res_chi);
    HistData1dOpe::GetResRatioHd1d(h1d_data,
                                  func, GetFitStat()->GetFitParam()->GetPar(),
                                  h1d_res_ratio);
    InitSetHd1(h1d_res_val, h1d_res_chi, h1d_res_ratio);
    delete h1d_res_val;
    delete h1d_res_chi;
    delete h1d_res_ratio;
}

void FitStatHG::InitSetH2dByFunc(const HistDataSerr2d* const h2d_data, const MirFunc* const func)
{
    HistDataSerr2d* h2d_res_val = new HistDataSerr2d;
    HistDataSerr2d* h2d_res_chi = new HistDataSerr2d;
    HistDataSerr2d* h2d_res_ratio = new HistDataSerr2d;

    HistData2dOpe::GetResValHd2d(h2d_data,
                                func, GetFitStat()->GetFitParam()->GetPar(),
                                h2d_res_val);
    HistData2dOpe::GetResChiHd2d(h2d_data, 
                                func, GetFitStat()->GetFitParam()->GetPar(),
                                h2d_res_chi);
    HistData2dOpe::GetResRatioHd2d(h2d_data, 
                                  func, GetFitStat()->GetFitParam()->GetPar(),
                                  h2d_res_ratio);
    InitSetHd2(h2d_res_val, h2d_res_chi, h2d_res_ratio);
    delete h2d_res_val;
    delete h2d_res_chi;
    delete h2d_res_ratio;
}



void FitStatHG::InitSetG2dByFunc(const GraphDataSerr2d* const g2d_data, const MirFunc* const func)
{
    GraphDataSerr2d* g2d_res_val   = new GraphDataSerr2d;
    GraphDataSerr2d* g2d_res_chi   = new GraphDataSerr2d;
    GraphDataSerr2d* g2d_res_ratio = new GraphDataSerr2d;

    GraphData2dOpe::GetResValGd2d(g2d_data,
                                 func, GetFitStat()->GetFitParam()->GetPar(),
                                 g2d_res_val);
    GraphData2dOpe::GetResChiGd2d(g2d_data,
                                 func, GetFitStat()->GetFitParam()->GetPar(),
                                 g2d_res_chi);
    GraphData2dOpe::GetResRatioGd2d(g2d_data,
                                   func, GetFitStat()->GetFitParam()->GetPar(),
                                   g2d_res_ratio);
    InitSetGd2(g2d_res_val, g2d_res_chi, g2d_res_ratio);
    delete g2d_res_val;
    delete g2d_res_chi;
    delete g2d_res_ratio;
}


void FitStatHG::InitSetFitParamBest(const FitParam* const fit_param_best)
{
    NullFitParamBest();
    fit_param_best_ = new FitParam;
    fit_param_best_->Copy(fit_param_best);
}


// Print

void FitStatHG::PrintInfo(FILE* fp) const
{
    fprintf(fp, "--- before fit ---\n");
    GetFitStatInit()->Print(fp);
    fprintf(fp, "=== before fit ===\n");

    fprintf(fp, "--- after fit ---\n");
    GetFitStat()->Print(fp);

    char msg[kLineSize];
    sprintf(msg, "nhist_chi2_ = %d", nhist_chi2_);
    MPrintInfoClass(msg);
    sprintf(msg, "nhist_chi2_cont_ = %d", nhist_chi2_cont_);
    MPrintInfoClass(msg);
    
    GetFitParamBest()->Print(fp);
    fprintf(fp, "=== after fit ===\n");    
}


void FitStatHG::MkOutParSearch1d(string outdir, string outfile_head, string flag_name_length) const
{
    int nhist_chi2 = GetNhistChi2();
    for(int ihist = 0; ihist < nhist_chi2; ihist++){
        char hist_char[kLineSize];
        int index_par = GetChi2PlotPar()->GetIndexElm(ihist);
        string par_name = GetFitStat()->GetFitParam()->GetParNameElm(index_par);
        string par_name_for_filename = "";
        if("def" == flag_name_length){
            par_name_for_filename = par_name;
        } else if("short" == flag_name_length){
            par_name_for_filename = "";
        } else {
            printf("bad flag name\n");
            abort();
        }
        
        sprintf(hist_char, "%2.2d%s", index_par, par_name_for_filename.c_str());
        //MirQdpTool::MkQdpMinFcn(GetHistChi2ArrElm(ihist),
        //                         outdir + "/" + outfile_head + "_" +
        //                         "chi2_" + hist_char + ".qdp",
        //                         GetFitStat()->GetFitParam()->GetParElm(index_par),
        //                         GetFitStat()->GetFitParam()->GetParTerrMinusElm(index_par),
        //                         GetFitStat()->GetFitParam()->GetParTerrPlusElm(index_par),
        //                         GetFitStat()->GetFcnMin(),
        //                         par_name);
        MimQdpTool::MkQdpMinFcn(GetHistChi2ArrElm(ihist),
                                 outdir + "/" + outfile_head + "_" +
                                 "chi2_" + hist_char + ".qdp",
                                 GetFitParamBest()->GetParElm(index_par),
                                 GetFitParamBest()->GetParTerrMinusElm(index_par),
                                 GetFitParamBest()->GetParTerrPlusElm(index_par),
                                 GetFitStat()->GetFcnMin(),
                                 par_name);

        
        MirQdpTool::MkQdp(GetHistValidArrElm(ihist),
                           outdir + "/" + outfile_head + "_" +
                           "valid" + "_" + hist_char + ".qdp",
                           "x,xe,y,ye",
                           par_name, "fit valid flag");

        MirQdpTool::MkQdp(GetHistFlagBadNegArrElm(ihist),
                           outdir + "/" + outfile_head + "_" +
                           "flag_bad_neg" + "_" + hist_char + ".qdp",
                           "x,xe,y,ye",
                           par_name, "flag bad negative");

        MirQdpTool::MkQdp(GetHistEdmArrElm(ihist),
                           outdir + "/" + outfile_head + "_" +
                           "edm" + "_" + hist_char + ".qdp",
                           "x,xe,y,ye",
                           par_name, "edm");
        
        //
        // root
        // 
        GetHistChi2ArrElm(ihist)->SaveRoot(
            outdir + "/" + outfile_head + "_" +
            "chi2_" + hist_char + ".root");
        GetHistValidArrElm(0)->SaveRoot(
            outdir + "/" + outfile_head + "_" +
            "valid_" + hist_char + ".root");
        GetHistFlagBadNegArrElm(ihist)->SaveRoot(
            outdir + "/" + outfile_head + "_" +
            "flag_bad_neg_" + hist_char + ".root");

        int num_index1 = GetChi2PlotPar()->GetNumIndex1Elm(ihist);

        printf("debug num_index1 = %d\n", num_index1);
        
        
        for(int inum = 0; inum < num_index1; inum++){
            char index1_char[kLineSize];
            int index1_index = GetChi2PlotPar()->GetIndex1ArrElm(ihist, inum);
            string par_name_index1 = GetFitStat()->GetFitParam()->GetParNameElm(index1_index);
            sprintf(index1_char, "index1-%2.2d%s_%2.2d",
                    index_par,
                    par_name_for_filename.c_str(),
                    index1_index);
            MirQdpTool::MkQdp(GetHistIndex1ArrElm(ihist, inum),
                               outdir + "/" + outfile_head + "_" +
                               index1_char + ".qdp",
                               "x,xe,y,ye",
                               par_name, par_name_index1);
        }
    }
}
    
void FitStatHG::MkOutParSearch2d(string outdir,
                                 string outfile_head,
                                 string flag_name_length,
                                 MirRootTool* const root_tool) const
{   
    int nhist_chi2_cont = GetNhistChi2Cont();
    for(int ihist = 0; ihist < nhist_chi2_cont; ihist++){
        char hist_char[kLineSize];
        int index_x   = GetChi2PlotContPar()->GetIndex0Elm(ihist);
        int index_y   = GetChi2PlotContPar()->GetIndex1Elm(ihist);
        string name_x = "";
        string name_y = "";
        if("def" == flag_name_length){
            name_x = GetFitStat()->GetFitParam()->GetParNameElm(index_x);
            name_y = GetFitStat()->GetFitParam()->GetParNameElm(index_y);
        } else if("short" == flag_name_length){
            name_x = "";
            name_y = "";
        } else {
            printf("bad flag name\n");
            abort();
        }
        sprintf(hist_char, "%2.2d%s-%2.2d%s",
                index_x, name_x.c_str(), index_y, name_y.c_str());

//        MirQdpTool::MkQdpContMinFcnWithBest(
//            GetHistChi2ContArrElm(ihist),
//            outdir + "/" + outfile_head + "_" +
//            "chi2_cont_" + hist_char + ".qdp",
//            GetFitStat()->GetFitParam()->GetParElm(index_x),
//            GetFitStat()->GetFitParam()->GetParElm(index_y),
//            GetFitStat()->GetFcnMin(),
//            name_x, name_y);

        MimQdpTool::MkQdpContMinFcnWithBest(
            GetHistChi2ContArrElm(ihist),
            outdir + "/" + outfile_head + "_" +
            "chi2_cont_" + hist_char + ".qdp",
            GetFitParamBest()->GetParElm(index_x),
            GetFitParamBest()->GetParElm(index_y),
            GetFitStat()->GetFcnMin(),
            name_x, name_y);
        
        GetHistChi2ContArrElm(ihist)->Save(
            outdir + "/" + outfile_head + "_" +
            "chi2_cont_" + hist_char + ".dat", "x,xe,y,ye,z,ze");
        //
        // png
        //
        double offset_xval = 0.0;
        double offset_yval = 0.0;
        double offset_oval = 0.0;
        GetHistChi2ContArrElm(ihist)->MkTH2Fig(
            outdir + "/" + outfile_head + "_" +
            "chi2_cont_" + hist_char + ".png",
            root_tool,
            offset_xval, offset_yval, offset_oval,
            name_x, name_y);

        // adhoc
        GetHistChi2ContArrElm(ihist)->MkTH2FigZrange(
            outdir + "/" + outfile_head + "_" +
            "chi2_cont_zrange_" + hist_char + ".png",
            root_tool,
            0.0, 1e3,
            offset_xval, offset_yval, offset_oval,
            name_x, name_y);
        
        GetHistValidContArrElm(ihist)->MkTH2Fig(
            outdir + "/" + outfile_head + "_" +
            "valid_cont_" + hist_char + ".png",
            root_tool,
            offset_xval, offset_yval, offset_oval,
            name_x, name_y);
        GetHistFlagBadNegContArrElm(ihist)->MkTH2Fig(
            outdir + "/" + outfile_head + "_" +
            "flag_bad_neg_cont_" + hist_char + ".png",
            root_tool,
            offset_xval, offset_yval, offset_oval,
            name_x, name_y);
        GetHistEdmContArrElm(ihist)->MkTH2Fig(
            outdir + "/" + outfile_head + "_" +
            "edm_cont_" + hist_char + ".png",
            root_tool,
            offset_xval, offset_yval, offset_oval,
            name_x, name_y);
        

        //
        // root
        // 
        GetHistChi2ContArrElm(ihist)->SaveRoot(
            outdir + "/" + outfile_head + "_" +
            "chi2_cont_" + hist_char + ".root",
            offset_xval, offset_yval, offset_oval);
        GetHistValidContArrElm(0)->SaveRoot(
            outdir + "/" + outfile_head + "_" +
            "valid_cont_" + hist_char + ".root",
            offset_xval, offset_yval, offset_oval);
        GetHistFlagBadNegContArrElm(ihist)->SaveRoot(
            outdir + "/" + outfile_head + "_" +
            "flag_bad_neg_cont_" + hist_char + ".root",
            offset_xval, offset_yval, offset_oval);
        GetHistEdmContArrElm(ihist)->SaveRoot(
            outdir + "/" + outfile_head + "_" +
            "edm_cont_" + hist_char + ".root",
            offset_xval, offset_yval, offset_oval);

        int num_index2 = GetChi2PlotContPar()->GetNumIndex2Elm(ihist);
        for(int inum = 0; inum < num_index2; inum++){
            char index2_char[kLineSize];
            int index2_index = GetChi2PlotContPar()->GetIndex2ArrElm(ihist, inum);
            string par_name_index2 = GetFitStat()->GetFitParam()->GetParNameElm(index2_index);
            sprintf(index2_char, "index2-%2.2d%s-%2.2d%s_cont_%2.2d",
                    index_x, name_x.c_str(), index_y, name_y.c_str(),
                    index2_index);
            GetHistIndex2ContArrElm(ihist, inum)->MkTH2Fig(
                outdir + "/" + outfile_head + "_" +
                index2_char + ".png",
                root_tool,
                offset_xval, offset_yval, offset_oval,
                name_x, name_y);
        }
    }
}


void FitStatHG::PrintErrByParSearch1d(FILE* fp) const
{
    char prompt[kLineSize];
    sprintf(prompt, "ParSearch1d");
    fprintf(fp, "%s: # ipar  name  min  [error_end_minus  error_end_plus]  (err+ / err-) \n", prompt);
    for(int ipar = 0; ipar < GetNhistChi2(); ipar ++){
        int index = GetChi2PlotPar()->GetIndexElm(ipar);
        fprintf(fp, "%s: %d:  %s  %e  [ %e  %e ] (%+e / %+e) \n", prompt,
                ipar, GetFitStat()->GetFitParam()->GetParNameElm(index).c_str(),
                GetParAtMinChi2plotArrElm(ipar),
                GetParErrMinusEndChi2plotArrElm(ipar),
                GetParErrPlusEndChi2plotArrElm(ipar),
                GetParErrPlusEndChi2plotArrElm(ipar) - GetParAtMinChi2plotArrElm(ipar),
                GetParErrMinusEndChi2plotArrElm(ipar) - GetParAtMinChi2plotArrElm(ipar));
    }

}

void FitStatHG::PrintErrByParSearch2d(FILE* fp) const
{
    char prompt[kLineSize];
    sprintf(prompt, "ParSearch2d");
    fprintf(fp, "%s: # icont:  name0:  min0  [error0_end_minus  error0_end_plus]  (err+ / err-) \n", prompt);
    fprintf(fp, "%s: # icont:  name1:  min1  [error1_end_minus  error1_end_plus]  (err+ / err-) \n", prompt);
    for(int ihist = 0; ihist < GetNhistChi2Cont(); ihist ++){
        int index0 = GetChi2PlotContPar()->GetIndex0Elm(ihist);
        int index1 = GetChi2PlotContPar()->GetIndex1Elm(ihist);
        printf("debug: index0 = %d\n", index0);
        printf("debug: index1 = %d\n", index1);
        
        fprintf(fp, "%s: %d:  %s:  %e  [ %e  %e ] (%+e / %+e) \n", prompt,
                ihist,
                GetFitStat()->GetFitParam()->GetParNameElm(index0).c_str(),
                GetPar0AtMinChi2plotContArrElm(ihist),
                GetPar0ErrMinusEndChi2plotContArrElm(ihist),
                GetPar0ErrPlusEndChi2plotContArrElm(ihist),
                GetPar0ErrPlusEndChi2plotContArrElm(ihist) - GetPar0AtMinChi2plotContArrElm(ihist),
                GetPar0ErrMinusEndChi2plotContArrElm(ihist) - GetPar0AtMinChi2plotContArrElm(ihist));
        fprintf(fp, "%s: %d:  %s:  %e  [ %e  %e ] (%+e / %+e) \n", prompt,
                ihist,
                GetFitStat()->GetFitParam()->GetParNameElm(index1).c_str(),
                GetPar1AtMinChi2plotContArrElm(ihist),
                GetPar1ErrMinusEndChi2plotContArrElm(ihist),
                GetPar1ErrPlusEndChi2plotContArrElm(ihist),
                GetPar1ErrPlusEndChi2plotContArrElm(ihist) - GetPar1AtMinChi2plotContArrElm(ihist),
                GetPar1ErrMinusEndChi2plotContArrElm(ihist) - GetPar1AtMinChi2plotContArrElm(ihist));
    }
}


void FitStatHG::MkOutFitPlot(const HistDataSerr1d* const h1d_data,
                             const MirFunc* const func,
                             const double* const par_arr,
                             int npoint_func,
                             string outdir,
                             string outfile_head,
                             const MirPlotConf* const plot_conf)
{
//    MirQdpTool::MkQdpDiff3(h1d_data, func, par_arr,
//                            npoint_func,
//                            outdir, outfile_head,
//                            plot_conf);
}

void FitStatHG::MkOutFitPlot(const HistDataSerr2d* const h2d_data,
                             const MirFunc* const func,
                             const double* const par_arr,
                             string outdir,
                             string outfile_head,
                             const MirPlotConf* const plot_conf_projx,
                             const MirPlotConf* const plot_conf_projy,
                             MirRootTool* const root_tool)
{
    string add_mode = "amean";
    string error_mode = "gauss";
    MirQdpTool::MkQdpDiffProjSerr(h2d_data, func, par_arr,
                                  outdir, outfile_head,
                                  add_mode, error_mode,
                                  plot_conf_projx,
                                  plot_conf_projy);

    
//    HistDataSerr2d* h2d_res = new HistDataSerr2d;
//    HistData2dOpe::GetResValHd2(h2d_data, func, par_arr,
//                                h2d_res);
//
//    h2d_res->MkTH2Fig(outdir + "/" + outfile_head + "_res" + ".png",
//                      root_tool,
//                      h2d_res->GetOffsetXFromTag(plot_conf_projx->GetOffsetTagElm(0)),
//                      h2d_res->GetOffsetYFromTag(plot_conf_projy->GetOffsetTagElm(0)),
//                      0.0,
//                      plot_conf_projx->GetLabelElm(0),
//                      plot_conf_projy->GetLabelElm(0));
//    delete h2d_res;

    HistData2d* h2d_func = new HistDataNerr2d;
    long nbin_func_x = h2d_data->GetNbinX();
    long nbin_func_y = h2d_data->GetNbinY();
    double xval_lo = h2d_data->GetXvalLo();
    double xval_up = h2d_data->GetXvalUp();
    double yval_lo = h2d_data->GetYvalLo();
    double yval_up = h2d_data->GetYvalUp();
    h2d_func->Init(nbin_func_x, xval_lo, xval_up,
                   nbin_func_y, yval_lo, yval_up);
    h2d_func->SetByFunc(func, par_arr);
    MimQdpTool::MkQdpCont(h2d_func, outdir + "/" + outfile_head + "_func_best" + ".qdp", 3,
                          plot_conf_projx->GetLabelElm(0),
                          plot_conf_projy->GetLabelElm(0),
                          plot_conf_projx->GetLabelElm(1),
                          h2d_func->GetOffsetXFromTag(plot_conf_projx->GetOffsetTagElm(0)),
                          h2d_func->GetOffsetYFromTag(plot_conf_projy->GetOffsetTagElm(0)));

    h2d_func->MkTH2Fig(outdir + "/" + outfile_head + "_func_best" + ".png",
                       root_tool,
                       h2d_func->GetOffsetXFromTag(plot_conf_projx->GetOffsetTagElm(0)),
                       h2d_func->GetOffsetYFromTag(plot_conf_projy->GetOffsetTagElm(0)),
                       0.0,
                       plot_conf_projx->GetLabelElm(0),
                       plot_conf_projy->GetLabelElm(0),
                       "",
                       "pub");
    
    delete h2d_func;
}


void FitStatHG::MkOutFitPlot(const GraphDataSerr2d* const g2d_data,
                             const MirFunc* const func,
                             const double* const par_arr,
                             int npoint_func,
                             string outdir,
                             string outfile_head,
                             const MirPlotConf* const plot_conf)
{
    MirQdpTool::MkQdpDiff3Serr(g2d_data, func, par_arr,
                               npoint_func,
                               outdir, outfile_head,
                               plot_conf);
}




//
// private
//

void FitStatHG::Null()
{
    NullFitStatInit();
    NullFitStat();
    NullHd1();
    NullHd2();
    NullGd2();
    NullGd3();
    NullParSearch1d();
    NullParSearch2d();
    NullChi2ErrEnd();
    NullChi2ContErrEnd();
    NullFitParamBest();
}

void FitStatHG::NullFitStatInit()
{
    if(NULL != fit_stat_init_)      {delete fit_stat_init_;     fit_stat_init_ = NULL;}
}

void FitStatHG::NullFitStat()
{
    if(NULL != fit_stat_)           {delete fit_stat_;          fit_stat_ = NULL;}
}

void FitStatHG::NullHd1()
{
    if(NULL != hist1d_res_val_)     {delete hist1d_res_val_;    hist1d_res_val_ = NULL;}
    if(NULL != hist1d_res_chi_)     {delete hist1d_res_chi_;    hist1d_res_chi_ = NULL;}
    if(NULL != hist1d_res_ratio_)   {delete hist1d_res_ratio_;  hist1d_res_ratio_ = NULL;}
}

void FitStatHG::NullHd2()
{
    if(NULL != hist2d_res_val_)     {delete hist2d_res_val_;    hist2d_res_val_ = NULL;}
    if(NULL != hist2d_res_chi_)     {delete hist2d_res_chi_;    hist2d_res_chi_ = NULL;}
    if(NULL != hist2d_res_ratio_)   {delete hist2d_res_ratio_;  hist2d_res_ratio_ = NULL;}
}

void FitStatHG::NullGd2()
{
    if(NULL != graph2d_res_val_)    {delete graph2d_res_val_;   graph2d_res_val_ = NULL;}
    if(NULL != graph2d_res_chi_)    {delete graph2d_res_chi_;   graph2d_res_chi_ = NULL;}
    if(NULL != graph2d_res_ratio_)  {delete graph2d_res_ratio_; graph2d_res_ratio_ = NULL;}
}

void FitStatHG::NullGd3()
{
    if(NULL != graph3d_res_val_)    {delete graph3d_res_val_;   graph3d_res_val_ = NULL;}
    if(NULL != graph3d_res_chi_)    {delete graph3d_res_chi_;   graph3d_res_chi_ = NULL;}
    if(NULL != graph3d_res_ratio_)  {delete graph3d_res_ratio_; graph3d_res_ratio_ = NULL;}
}

void FitStatHG::NullParSearch1d()
{
    if(NULL != hist_chi2_arr_){
        for(int ihist = 0; ihist < nhist_chi2_; ihist++){
            delete hist_chi2_arr_[ihist]; hist_chi2_arr_[ihist] = NULL;
        }
        delete [] hist_chi2_arr_; hist_chi2_arr_ = NULL;
    }
    if(NULL != hist_valid_arr_){
        for(int ihist = 0; ihist < nhist_chi2_; ihist++){
            delete hist_valid_arr_[ihist]; hist_valid_arr_[ihist] = NULL;
        }
        delete [] hist_valid_arr_; hist_valid_arr_ = NULL;
    }
    if(NULL != hist_edm_arr_){
        for(int ihist = 0; ihist < nhist_chi2_; ihist++){
            delete hist_edm_arr_[ihist]; hist_edm_arr_[ihist] = NULL;
        }
        delete [] hist_edm_arr_; hist_edm_arr_ = NULL;
    }
    if(NULL != hist_flag_bad_neg_arr_){
        for(int ihist = 0; ihist < nhist_chi2_; ihist++){
            delete hist_flag_bad_neg_arr_[ihist]; hist_flag_bad_neg_arr_[ihist] = NULL;
        }
        delete [] hist_flag_bad_neg_arr_; hist_flag_bad_neg_arr_ = NULL;
    }
    if(NULL != hist_index1_arr_){
        for(int ihist = 0; ihist < nhist_chi2_; ihist++){
            int num_index1 = chi2plot_par_->GetNumIndex1Elm(ihist);
            for(int inum = 0; inum < num_index1; inum++){
                delete hist_index1_arr_[ihist][inum]; hist_index1_arr_[ihist][inum] = NULL;
            }
            delete [] hist_index1_arr_[ihist]; hist_index1_arr_[ihist] = NULL;
        }
        delete [] hist_index1_arr_; hist_index1_arr_ = NULL;
    }
    if(NULL != fit_stat_chi2_search_arr_){
        for(int ihist = 0; ihist < nhist_chi2_; ihist++){
            int nstep = chi2plot_par_->GetNstepElm(ihist);
            for(int istep = 0; istep < nstep; istep++){
                delete fit_stat_chi2_search_arr_[ihist][istep];
                fit_stat_chi2_search_arr_[ihist][istep] = NULL;
            }
            delete [] fit_stat_chi2_search_arr_[ihist];
            fit_stat_chi2_search_arr_[ihist] = NULL;
        }
        delete [] fit_stat_chi2_search_arr_;
        fit_stat_chi2_search_arr_ = NULL;
    }
   
    if(NULL != chi2plot_par_) {delete chi2plot_par_; chi2plot_par_ = NULL;}    
}

void FitStatHG::NullParSearch2d()
{
    if(NULL != hist_chi2_cont_arr_){
        for(int ihist = 0; ihist < nhist_chi2_cont_; ihist++){
            delete hist_chi2_cont_arr_[ihist]; hist_chi2_cont_arr_[ihist] = NULL;
        }
        delete [] hist_chi2_cont_arr_; hist_chi2_cont_arr_ = NULL;
    }
    if(NULL != hist_valid_cont_arr_){
        for(int ihist = 0; ihist < nhist_chi2_cont_; ihist++){
            delete hist_valid_cont_arr_[ihist]; hist_valid_cont_arr_[ihist] = NULL;
        }
        delete [] hist_valid_cont_arr_; hist_valid_cont_arr_ = NULL;
    }
    if(NULL != hist_edm_cont_arr_){
        for(int ihist = 0; ihist < nhist_chi2_cont_; ihist++){
            delete hist_edm_cont_arr_[ihist]; hist_edm_cont_arr_[ihist] = NULL;
        }
        delete [] hist_edm_cont_arr_; hist_edm_cont_arr_ = NULL;
    }
    if(NULL != hist_flag_bad_neg_cont_arr_){
        for(int ihist = 0; ihist < nhist_chi2_cont_; ihist++){
            delete hist_flag_bad_neg_cont_arr_[ihist]; hist_flag_bad_neg_cont_arr_[ihist] = NULL;
        }
        delete [] hist_flag_bad_neg_cont_arr_; hist_flag_bad_neg_cont_arr_ = NULL;
    }
    if(NULL != hist_index2_cont_arr_){
        for(int ihist = 0; ihist < nhist_chi2_cont_; ihist++){
            int num_index2 = chi2plot_cont_par_->GetNumIndex2Elm(ihist);
            for(int inum = 0; inum < num_index2; inum++){
                delete hist_index2_cont_arr_[ihist][inum]; hist_index2_cont_arr_[ihist][inum] = NULL;
            }
            delete [] hist_index2_cont_arr_[ihist]; hist_index2_cont_arr_[ihist] = NULL;
        }
        delete [] hist_index2_cont_arr_; hist_index2_cont_arr_ = NULL;
    }

    if(NULL != fit_stat_chi2cont_search_arr_){
        for(int ihist = 0; ihist < nhist_chi2_cont_; ihist++){
            int nstep0 = chi2plot_cont_par_->GetNstep0Elm(ihist);
            int nstep1 = chi2plot_cont_par_->GetNstep1Elm(ihist);
            for(int istep0 = 0; istep0 < nstep0; istep0++){
                for(int istep1 = 0; istep1 < nstep1; istep1++){
                    delete fit_stat_chi2cont_search_arr_[ihist][istep0][istep1];
                    fit_stat_chi2cont_search_arr_[ihist][istep0][istep1] = NULL;
                }
                delete [] fit_stat_chi2cont_search_arr_[ihist][istep0];
                fit_stat_chi2cont_search_arr_[ihist][istep0] = NULL;
            }
            delete [] fit_stat_chi2cont_search_arr_[ihist];
            fit_stat_chi2cont_search_arr_[ihist] = NULL;
        }
        delete [] fit_stat_chi2cont_search_arr_;
        fit_stat_chi2cont_search_arr_ = NULL;
    }
    if(NULL != chi2plot_cont_par_){delete chi2plot_cont_par_; chi2plot_cont_par_ = NULL;}    
}


void FitStatHG::NullChi2ErrEnd()
{
    if(NULL != par_at_min_chi2plot_arr_){
        delete [] par_at_min_chi2plot_arr_; par_at_min_chi2plot_arr_ = NULL;
    }
    if(NULL != par_err_plus_end_chi2plot_arr_){
        delete [] par_err_plus_end_chi2plot_arr_; par_err_plus_end_chi2plot_arr_ = NULL;
    }
    if(NULL != par_err_minus_end_chi2plot_arr_){
        delete [] par_err_minus_end_chi2plot_arr_; par_err_minus_end_chi2plot_arr_ = NULL;
    }
}
    
void FitStatHG::NullChi2ContErrEnd()
{
    if(NULL != par0_at_min_chi2plot_cont_arr_){
        delete [] par0_at_min_chi2plot_cont_arr_; par0_at_min_chi2plot_cont_arr_ = NULL;
    }
    if(NULL != par0_err_plus_end_chi2plot_cont_arr_){
        delete [] par0_err_plus_end_chi2plot_cont_arr_; par0_err_plus_end_chi2plot_cont_arr_ = NULL;
    }
    if(NULL != par0_err_minus_end_chi2plot_cont_arr_){
        delete [] par0_err_minus_end_chi2plot_cont_arr_; par0_err_minus_end_chi2plot_cont_arr_ = NULL;
    }
    if(NULL != par1_at_min_chi2plot_cont_arr_){
        delete [] par1_at_min_chi2plot_cont_arr_; par1_at_min_chi2plot_cont_arr_ = NULL;
    }
    if(NULL != par1_err_plus_end_chi2plot_cont_arr_){
        delete [] par1_err_plus_end_chi2plot_cont_arr_; par1_err_plus_end_chi2plot_cont_arr_ = NULL;
    }
    if(NULL != par1_err_minus_end_chi2plot_cont_arr_){
        delete [] par1_err_minus_end_chi2plot_cont_arr_; par1_err_minus_end_chi2plot_cont_arr_ = NULL;
    }
}

void FitStatHG::NullFitParamBest()
{
    if(NULL != fit_param_best_){
        delete fit_param_best_;
        fit_param_best_ = NULL;
    }
}
