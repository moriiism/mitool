#include "mir_hist2d_ope.h"

void HistData2dOpe::GetResValHd2(const HistData2d* const hist_data,
                                 const MirFunc* const func, const double* const par,
                                 HistData2d* const hist_res_out)
{
    long nbinx = hist_data->GetNbinX();
    long nbiny = hist_data->GetNbinY();
    long nbin = nbinx * nbiny;
  
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = hist_data->GetIbinX(ibin);
        long ibin_y = hist_data->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        hist_data->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = hist_data->GetOvalElm(ibin_x, ibin_y) - func->Eval(xval_arg, par);
    }

    hist_res_out->InitSet(nbinx, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          nbiny, hist_data->GetYvalLo(), hist_data->GetYvalUp(),
                          oval_res);
    delete [] oval_res;
}

void HistData2dOpe::GetResValHd2(const HistDataSerr2d* const hist_data,
                                 const MirFunc* const func, const double* const par,
                                 HistDataSerr2d* const hist_res_out)
{
    long nbinx = hist_data->GetNbinX();
    long nbiny = hist_data->GetNbinY();
    long nbin = nbinx * nbiny;
  
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = hist_data->GetIbinX(ibin);
        long ibin_y = hist_data->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        hist_data->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = hist_data->GetOvalElm(ibin_x, ibin_y) - func->Eval(xval_arg, par);
        oval_res_serr[ibin] = hist_data->GetOvalSerrElm(ibin_x, ibin_y);
    }

    hist_res_out->InitSet(nbinx, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          nbiny, hist_data->GetYvalLo(), hist_data->GetYvalUp(),
                          oval_res, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}

void HistData2dOpe::GetResValHd2(const HistDataTerr2d* const hist_data,
                                 const MirFunc* const func, const double* const par,
                                 HistDataTerr2d* const hist_res_out)
{
    long nbinx = hist_data->GetNbinX();
    long nbiny = hist_data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_terr_plus  = new double[nbin];
    double* oval_res_terr_minus = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = hist_data->GetIbinX(ibin);
        long ibin_y = hist_data->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        hist_data->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        double func_val = func->Eval(xval_arg, par);
        oval_res[ibin] = hist_data->GetOvalElm(ibin_x, ibin_y) - func_val;
        oval_res_terr_plus[ibin]  = hist_data->GetOvalTerrPlusElm(ibin_x, ibin_y);
        oval_res_terr_minus[ibin] = hist_data->GetOvalTerrMinusElm(ibin_x, ibin_y);
    }
    hist_res_out->InitSet(nbinx, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          nbiny, hist_data->GetYvalLo(), hist_data->GetYvalUp(),
                          oval_res, oval_res_terr_plus, oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;    
}




void HistData2dOpe::GetResRatioHd2(const HistData2d* const hist_data,
                                const MirFunc* const func, const double* const par,
                                HistData2d* const hist_res_out)
{
    long nbinx = hist_data->GetNbinX();
    long nbiny = hist_data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = hist_data->GetIbinX(ibin);
        long ibin_y = hist_data->GetIbinY(ibin);        
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        hist_data->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = (hist_data->GetOvalElm(ibin_x, ibin_y) - func->Eval(xval_arg, par)) /
            func->Eval(xval_arg, par);
    }

    hist_res_out->InitSet(nbinx, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          nbiny, hist_data->GetYvalLo(), hist_data->GetYvalUp(),
                          oval_res);
    delete [] oval_res;
}

void HistData2dOpe::GetResRatioHd2(const HistDataSerr2d* const hist_data,
                                   const MirFunc* const func, const double* const par,
                                   HistDataSerr2d* const hist_res_out)
{
    long nbinx = hist_data->GetNbinX();
    long nbiny = hist_data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = hist_data->GetIbinX(ibin);
        long ibin_y = hist_data->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        hist_data->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = (hist_data->GetOvalElm(ibin_x, ibin_y) - func->Eval(xval_arg, par)) /
            func->Eval(xval_arg, par);
        oval_res_serr[ibin] = fabs( hist_data->GetOvalSerrElm(ibin_x, ibin_y)
                                    / func->Eval(xval_arg, par) );
    }

    hist_res_out->InitSet(nbinx, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          nbiny, hist_data->GetYvalLo(), hist_data->GetYvalUp(),
                          oval_res, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}


void HistData2dOpe::GetResRatioHd2(const HistDataTerr2d* const hist_data,
                                   const MirFunc* const func, const double* const par,
                                   HistDataTerr2d* const hist_res_out)
{
    long nbinx = hist_data->GetNbinX();
    long nbiny = hist_data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_terr_plus  = new double[nbin];
    double* oval_res_terr_minus = new double[nbin];    
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = hist_data->GetIbinX(ibin);
        long ibin_y = hist_data->GetIbinY(ibin);        
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        hist_data->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        double func_val = func->Eval(xval_arg, par);
        
        oval_res[ibin] = (hist_data->GetOvalElm(ibin_x, ibin_y) - func_val )
            / func_val;
        oval_res_terr_plus[ibin]  = fabs(hist_data->GetOvalTerrPlusElm(ibin_x, ibin_y) / func_val);
        oval_res_terr_minus[ibin] = -1 * fabs(hist_data->GetOvalTerrMinusElm(ibin_x, ibin_y) / func_val);
    }

    hist_res_out->InitSet(nbinx, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          nbiny, hist_data->GetYvalLo(), hist_data->GetYvalUp(),
                          oval_res, oval_res_terr_plus, oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;
}


void HistData2dOpe::GetResChiHd2(const HistDataSerr2d* const hist_data,
                                 const MirFunc* const func, const double* const par,
                                 HistDataSerr2d* const hist_res_out)
{
    long nbinx = hist_data->GetNbinX();
    long nbiny = hist_data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = hist_data->GetIbinX(ibin);
        long ibin_y = hist_data->GetIbinY(ibin);        
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        hist_data->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = (hist_data->GetOvalElm(ibin_x, ibin_y) - func->Eval(xval_arg, par)) /
            hist_data->GetOvalSerrElm(ibin_x, ibin_y);
        oval_res_serr[ibin] = 1.0;
    }

    hist_res_out->InitSet(nbinx, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          nbiny, hist_data->GetYvalLo(), hist_data->GetYvalUp(),
                          oval_res, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}


void HistData2dOpe::GetResChiHd2(const HistDataTerr2d* const hist_data,
                                 const MirFunc* const func, const double* const par,
                                 HistDataTerr2d* const hist_res_out)
{
    long nbinx = hist_data->GetNbinX();
    long nbiny = hist_data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_terr_plus  = new double[nbin];
    double* oval_res_terr_minus = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = hist_data->GetIbinX(ibin);
        long ibin_y = hist_data->GetIbinY(ibin);        
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        hist_data->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        double func_val = func->Eval(xval_arg, par);
        if(hist_data->GetOvalElm(ibin_x, ibin_y) > func_val){
            oval_res[ibin] = -1 * (hist_data->GetOvalElm(ibin_x, ibin_y) - func_val) /
                hist_data->GetOvalTerrMinusElm(ibin_x, ibin_y);
        } else {
            oval_res[ibin] = (hist_data->GetOvalElm(ibin_x, ibin_y) - func_val) /
                hist_data->GetOvalTerrPlusElm(ibin_x, ibin_y);
        }
        oval_res_terr_plus[ibin] = 1.0;
        oval_res_terr_minus[ibin] = 1.0;
    }

    hist_res_out->InitSet(nbinx, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          nbiny, hist_data->GetYvalLo(), hist_data->GetYvalUp(),
                          oval_res, oval_res_terr_plus, oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;
}



int HistData2dOpe::IsFormatSame(const HistData2d* const hist_data1,
                                const HistData2d* const hist_data2)
{
    if(hist_data1->GetNbinX()  != hist_data2->GetNbinX()  ||
       hist_data1->GetXvalLo() != hist_data2->GetXvalLo() ||
       hist_data1->GetXvalUp() != hist_data2->GetXvalUp() ||
       hist_data1->GetNbinY()  != hist_data2->GetNbinY()  ||
       hist_data1->GetYvalLo() != hist_data2->GetYvalLo() ||
       hist_data1->GetYvalUp() != hist_data2->GetYvalUp()   ){
        MPrintErr("format of hist_data1 and hist_data2 are diffenret.");
        char msg[kLineSize];
        sprintf(msg, "hist_data1: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)\n",
                hist_data1->GetNbinX(),
                hist_data1->GetXvalLo(),
                hist_data1->GetXvalUp());
        MPrintErr(msg);
        sprintf(msg, "hist_data1: (GetNbinY(), GetYvalLo(), GetYvalUp()) = (%ld, %e, %e)\n",
                hist_data1->GetNbinY(),
                hist_data1->GetYvalLo(),
                hist_data1->GetYvalUp());
        MPrintErr(msg);        
        sprintf(msg, "hist_data2: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)\n",
                hist_data2->GetNbinX(),
                hist_data2->GetXvalLo(),
                hist_data2->GetXvalUp());
        MPrintErr(msg);        
        sprintf(msg, "hist_data2: (GetNbinY(), GetYvalLo(), GetYvalUp()) = (%ld, %e, %e)\n",
                hist_data2->GetNbinY(),
                hist_data2->GetYvalLo(),
                hist_data2->GetYvalUp());
        MPrintErr(msg);        
        abort();
    }
    return 1;
}


int HistData2dOpe::IsFormatSame(const HistData2d* const* const hist_data_arr,
                             int nhist)
{
    if(nhist < 2){
        char msg[kLineSize];
        sprintf(msg, "nhist(=%d) < 2\n", nhist);
        MPrintWarn(msg);
        MPrintWarn("skip check");
        return 0;
    }
    for(int ihist = 1; ihist < nhist; ihist++){
        if(hist_data_arr[0]->GetNbinX()  != hist_data_arr[ihist]->GetNbinX()  ||
           hist_data_arr[0]->GetXvalLo() != hist_data_arr[ihist]->GetXvalLo() ||
           hist_data_arr[0]->GetXvalUp() != hist_data_arr[ihist]->GetXvalUp() ||
           hist_data_arr[0]->GetNbinY()  != hist_data_arr[ihist]->GetNbinY()  ||
           hist_data_arr[0]->GetYvalLo() != hist_data_arr[ihist]->GetYvalLo() ||
           hist_data_arr[0]->GetYvalUp() != hist_data_arr[ihist]->GetYvalUp()   ){
            char msg[kLineSize];
            sprintf(msg, "format of hist_data_arr[0] and hist_data_arr[%d] are diffenret\n",
                    ihist);
            MPrintErr(msg);
            sprintf(msg, "hist_data_arr[0]: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)\n",
                    hist_data_arr[0]->GetNbinX(),
                    hist_data_arr[0]->GetXvalLo(),
                    hist_data_arr[0]->GetXvalUp());
            MPrintErr(msg);            
            sprintf(msg, "hist_data_arr[0]: (GetNbinY(), GetYvalLo(), GetYvalUp()) = (%ld, %e, %e)\n",
                    hist_data_arr[0]->GetNbinY(),
                    hist_data_arr[0]->GetYvalLo(),
                    hist_data_arr[0]->GetYvalUp());
            MPrintErr(msg);                        
            sprintf(msg, "hist_data_arr[%d]: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)\n",
                    ihist,
                    hist_data_arr[ihist]->GetNbinX(),
                    hist_data_arr[ihist]->GetXvalLo(),
                    hist_data_arr[ihist]->GetXvalUp());
            MPrintErr(msg);                                    
            sprintf(msg, "hist_data_arr[%d]: (GetNbinY(), GetYvalLo(), GetYvalUp()) = (%ld, %e, %e)\n",
                    ihist,
                    hist_data_arr[ihist]->GetNbinY(),
                    hist_data_arr[ihist]->GetYvalLo(),
                    hist_data_arr[ihist]->GetYvalUp());
            MPrintErr(msg);                                    
            abort();
        }
    }
    return 1;
}


int HistData2dOpe::IsFormatSame(const HistDataSerr2d* const* const hist_data_arr,
                                int nhist)
{
    HistData2d** h2d_arr = new HistData2d* [nhist];
    for(int ihist = 1; ihist < nhist; ihist++){
        h2d_arr[ihist] = new HistData2d;
        h2d_arr[ihist]->Copy(hist_data_arr[ihist]);
    }
    IsFormatSame(h2d_arr, nhist);

    for(int ihist = 1; ihist < nhist; ihist++){
        delete h2d_arr[ihist]; h2d_arr[ihist] = NULL;
    }
    delete [] h2d_arr;
    return 1;
}


void HistData2dOpe::GenContMinFcn(const HistData2d* const hd2d,
                                  double zval_min,
                                  int nlevel,
                                  const double* const delta_minfcn_arr,
                                  MirCont*** const cont_arr_ptr,
                                  MirRootTool* const root_tool,
                                  double offset_xval,
                                  double offset_yval)
{
    TH2D* th2d = hd2d->GenTH2D(offset_xval, offset_yval);
    double* cont_level = new double [nlevel];
    for(int ilevel = 0; ilevel < nlevel; ilevel++){
        cont_level[ilevel] = zval_min + delta_minfcn_arr[ilevel];
    }
    th2d->SetContour(nlevel, cont_level);


    // http://root.cern.ch/root/html/tutorials/hist/ContourList.C.html
    // Draw contours as filled regions, and Save points
    th2d->Draw("CONT Z LIST");
    root_tool->GetTCanvas()->Update();
    // Needed to force the plotting and retrieve the contours in TGraphs

    
    // Get Contours
    TObjArray* cont_tobj_arr = dynamic_cast<TObjArray*>(gROOT->GetListOfSpecials()->FindObject("contours"));
    int ncont = 0;
    if(NULL != cont_tobj_arr){
        ncont = cont_tobj_arr->GetSize();
    } else {
        printf("%s: error: No Contours Were Extracted!\n", __func__);
        abort();
    }
    printf("ncont = %d\n", ncont);

    MirCont** cont_arr = new MirCont* [nlevel];
    for(int ilevel = 0; ilevel < nlevel; ilevel++){
        cont_arr[ilevel] = new MirCont;
    }
  
    for(int icont = 0; icont < ncont; icont++){
        TList* list_graph = (TList*) cont_tobj_arr->At(icont);

        int ngraph = list_graph->GetSize();
        GraphData2d** g2d_arr = new GraphData2d* [ngraph];
        for(int igraph = 0; igraph < ngraph; igraph++){
            g2d_arr[igraph] = new GraphData2d;
            g2d_arr[igraph]->Init();
        }

        for(int igraph = 0; igraph < ngraph; igraph++){
            TGraph* graph_curve = (TGraph*) list_graph->At(igraph);
            int npoint = graph_curve->GetN();
            vector<double> xval, oval;
            for(int ipoint = 0; ipoint < npoint; ipoint++){
                double point_x, point_y;
                graph_curve->GetPoint(ipoint, point_x, point_y);
                xval.push_back(point_x);
                oval.push_back(point_y);
            }
            g2d_arr[igraph]->SetXvalArrDbl(xval);
            g2d_arr[igraph]->SetOvalArrDbl(oval);
        }
        cont_arr[icont]->Init(ngraph);
        cont_arr[icont]->SetGd2dArr(ngraph, g2d_arr);
      
        for(int igraph = 0; igraph < ngraph; igraph++){
            delete g2d_arr[igraph];
        }
        delete [] g2d_arr;
    }
  
    delete [] cont_level;
    delete th2d;
    *cont_arr_ptr = cont_arr;
}


void HistData2dOpe::GenContWithBestMinFcn(const HistData2d* const hd2d,
                                          double zval_min, double xval_best, double yval_best,
                                          int nlevel, const double* const delta_minfcn_arr,
                                          MirContWithBest*** const cont_with_best_arr_ptr,
                                          MirRootTool* const root_tool,
                                          double offset_xval, double offset_yval)
{
    MirCont** cont_arr = NULL;
    GenContMinFcn(hd2d, zval_min, nlevel, delta_minfcn_arr,
                  &cont_arr, root_tool, offset_xval, offset_yval);

    MirContWithBest** cont_with_best_arr = new MirContWithBest* [nlevel];
    for(int ilevel = 0; ilevel < nlevel; ilevel++){
        cont_with_best_arr[ilevel] = new MirContWithBest;
        cont_with_best_arr[ilevel]->Init();
        cont_with_best_arr[ilevel]->SetBest(xval_best, yval_best);
        cont_with_best_arr[ilevel]->SetCont(cont_arr[ilevel]);
    }
    for(int ilevel = 0; ilevel < nlevel; ilevel++){
        delete cont_arr[ilevel]; cont_arr[ilevel] = NULL;
    }
    delete [] cont_arr; cont_arr = NULL;
    
    *cont_with_best_arr_ptr = cont_with_best_arr;
}

void HistData2dOpe::GetHd2dMaskWithMargin(const HistData2d* const hd2d_mask,
                                          double xval_margin, double yval_margin,
                                          HistData2d* const hd2d_with_margin_out)
{
    if(xval_margin < 0.0 || yval_margin < 0.0){
        abort();
    }
    long nbin_x = hd2d_mask->GetNbinX();
    long nbin_y = hd2d_mask->GetNbinY();
    for(long ibin_x = 0; ibin_x < nbin_x; ibin_x ++){
        for(long ibin_y = 0; ibin_y < nbin_y; ibin_y ++){
            if(0 < hd2d_mask->GetOvalElm(ibin_x, ibin_y)){
                double xval = hd2d_mask->GetBinCenterXFromIbinX(ibin_x);
                double yval = hd2d_mask->GetBinCenterYFromIbinY(ibin_y);

                long ibin_x_lo = hd2d_with_margin_out->GetIbinXFromX(
                    MirMath::GetMax(xval - xval_margin, hd2d_with_margin_out->GetXvalLo()) );
                long ibin_x_up = hd2d_with_margin_out->GetIbinXFromX(
                    MirMath::GetMin(xval + xval_margin, hd2d_with_margin_out->GetXvalUp()) );
                long ibin_y_lo = hd2d_with_margin_out->GetIbinYFromY(
                    MirMath::GetMax(yval - yval_margin, hd2d_with_margin_out->GetYvalLo()) );
                long ibin_y_up = hd2d_with_margin_out->GetIbinYFromY(
                    MirMath::GetMin(yval + yval_margin, hd2d_with_margin_out->GetYvalUp()) );

                for(long ifill_x = ibin_x_lo; ifill_x <= ibin_x_up; ifill_x ++){
                    for(long ifill_y = ibin_y_lo; ifill_y <= ibin_y_up; ifill_y ++){
                        hd2d_with_margin_out->SetOvalElm(ifill_x, ifill_y, 1.0);
                    }
                }
            }
        }
    }
}
