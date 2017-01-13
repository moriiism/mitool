#include "mir_graph2d_ope.h"

void GraphData2dOpe::GetSelectG2dByInterval(const GraphData2d* const graph_data,
                                            const Interval* const interval,
                                            GraphData2d* const graph_out)
{
    vector<double> xval_new;
    vector<double> oval_new;
    long ndata = graph_data->GetNdata();
    long nterm = interval->GetNterm();
    for(long idata = 0; idata < ndata; idata++){
        for(int iterm = 0; iterm < nterm; iterm ++){
            double xval = graph_data->GetXvalElm(idata);
            double oval = graph_data->GetOvalElm(idata);
            if(interval->GetTstartElm(iterm) <= xval &&
               xval <= interval->GetTstopElm(iterm) ){
                xval_new.push_back(xval);
                oval_new.push_back(oval);
            }
        }
    }
    graph_out->Init();
    graph_out->SetXvalArrDbl(xval_new);
    graph_out->SetOvalArrDbl(oval_new);
}

void GraphData2dOpe::GetSelectG2dByInterval(const GraphDataSerr2d* const graph_data,
                                            const Interval* const interval,
                                            GraphDataSerr2d* const graph_out,
                                            string select_type)
{
    vector<double> xval_new;
    vector<double> xval_serr_new;
    vector<double> oval_new;
    vector<double> oval_serr_new;
    long ndata = graph_data->GetNdata();
    if("exclusive" == select_type){
        for(long idata = 0; idata < ndata; idata++){
            for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
                double xval      = graph_data->GetXvalElm(idata);
                double xval_serr = graph_data->GetXvalSerrElm(idata);
                double oval      = graph_data->GetOvalElm(idata);
                double oval_serr = graph_data->GetOvalSerrElm(idata);
                if( interval->GetTstart()[iterm] <= xval - xval_serr &&
                    xval + xval_serr <= interval->GetTstop()[iterm]     ){
                    xval_new.push_back(xval);
                    xval_serr_new.push_back(xval_serr);
                    oval_new.push_back(oval);
                    oval_serr_new.push_back(oval_serr);
                }
            }
        }
    } else if ("center" == select_type){
        for(long idata = 0; idata < ndata; idata++){
            for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
                double xval      = graph_data->GetXvalElm(idata);
                double xval_serr = graph_data->GetXvalSerrElm(idata);
                double oval      = graph_data->GetOvalElm(idata);
                double oval_serr = graph_data->GetOvalSerrElm(idata);
                if(interval->GetTstart()[iterm] <= xval &&
                   xval <= interval->GetTstop()[iterm]){
                    xval_new.push_back(xval);
                    xval_serr_new.push_back(xval_serr);
                    oval_new.push_back(oval);
                    oval_serr_new.push_back(oval_serr);
                }
            }
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "select_type(=%s)", select_type.c_str());
        MPrintErr(msg);
        abort();
    }

    graph_out->Init();
    graph_out->SetXvalAndSerrArrDbl(xval_new, xval_serr_new);
    graph_out->SetOvalAndSerrArrDbl(oval_new, oval_serr_new);
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


void GraphData2dOpe::GetSelectG2dByInterval(const GraphDataTerr2d* const graph_data,
                                            const Interval* const interval,
                                            GraphDataTerr2d* const graph_out,
                                            string select_type)
{
    vector<double> xval_new;
    vector<double> xval_terr_plus_new;
    vector<double> xval_terr_minus_new;
    vector<double> oval_new;
    vector<double> oval_terr_plus_new;
    vector<double> oval_terr_minus_new;
    long ndata = graph_data->GetNdata();
    if("exclusive" == select_type){
        for(long idata = 0; idata < ndata; idata++){
            for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
                double xval            = graph_data->GetXvalElm(idata);
                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
                double oval            = graph_data->GetOvalElm(idata);
                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
                if( interval->GetTstartElm(iterm) <= xval + xval_terr_minus &&
                    xval + xval_terr_plus <= interval->GetTstopElm(iterm)     ){
                    xval_new.push_back(xval);
                    xval_terr_plus_new.push_back(xval_terr_plus);
                    xval_terr_minus_new.push_back(xval_terr_minus);
                    oval_new.push_back(oval);
                    oval_terr_plus_new.push_back(oval_terr_plus);
                    oval_terr_minus_new.push_back(oval_terr_minus);
                }
            }
        }
    } else if ("center" == select_type){
        for(long idata = 0; idata < ndata; idata++){
            for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
                double xval            = graph_data->GetXvalElm(idata);
                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
                double oval            = graph_data->GetOvalElm(idata);
                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
                if(interval->GetTstartElm(iterm) <= xval &&
                   xval <= interval->GetTstopElm(iterm)    ){
                    xval_new.push_back(xval);
                    xval_terr_plus_new.push_back(xval_terr_plus);
                    xval_terr_minus_new.push_back(xval_terr_minus);
                    oval_new.push_back(oval);
                    oval_terr_plus_new.push_back(oval_terr_plus);
                    oval_terr_minus_new.push_back(oval_terr_minus);
                }
            }
        }
    } else if ("varbinwidth" == select_type){
        for(long idata = 0; idata < ndata; idata++){
            for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
                double xval            = graph_data->GetXvalElm(idata);
                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
                double oval            = graph_data->GetOvalElm(idata);
                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
                if(interval->GetTstartElm(iterm) <= xval &&
                   xval <= interval->GetTstopElm(iterm)    ){
                    xval_new.push_back(xval);
                    oval_new.push_back(oval);
                    oval_terr_plus_new.push_back(oval_terr_plus);
                    oval_terr_minus_new.push_back(oval_terr_minus);

                    if(xval + xval_terr_minus < interval->GetTstartElm(iterm)){
                        double xval_terr_minus_this = -1 * (xval - interval->GetTstartElm(iterm));
                        xval_terr_minus_new.push_back(xval_terr_minus_this);
                    }
                    if(interval->GetTstopElm(iterm) < xval + xval_terr_plus){
                        double xval_terr_plus_this = interval->GetTstopElm(iterm) - xval;
                        xval_terr_plus_new.push_back(xval_terr_plus_this);
                    }
                }
            }
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "select_type(=%s)", select_type.c_str());
        MPrintErr(msg);
        abort();
    }

    graph_out->Init();
    graph_out->SetXvalAndTerrArrDbl(xval_new, xval_terr_plus_new, xval_terr_minus_new);
    graph_out->SetOvalAndTerrArrDbl(oval_new, oval_terr_plus_new, oval_terr_minus_new);
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}




void GraphData2dOpe::GenSelectG2dArrByInterval(const GraphData2d* const graph_data,
                                               const Interval* const interval,
                                               GraphData2d*** g2d_arr_ptr)
{
    long nterm = interval->GetNterm();
    GraphData2d** g2d_arr = new GraphData2d* [nterm];
    for(long iterm = 0; iterm < nterm; iterm ++){
        g2d_arr[iterm] = new GraphData2d;
    }
    vector<double>* xval_vec_arr = new vector<double> [nterm];
    vector<double>* oval_vec_arr = new vector<double> [nterm];

    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata ++){
        for(long iterm = 0; iterm < nterm; iterm ++){
            double xval = graph_data->GetXvalElm(idata);
            double oval = graph_data->GetOvalElm(idata);
            if(interval->GetTstartElm(iterm) <= xval &&
               xval <= interval->GetTstopElm(iterm)){
                xval_vec_arr[iterm].push_back(xval);
                oval_vec_arr[iterm].push_back(oval);
            }
        }
    }
    for(long iterm = 0; iterm < nterm; iterm ++){
        g2d_arr[iterm]->Init();
        g2d_arr[iterm]->SetXvalArrDbl(xval_vec_arr[iterm]);
        g2d_arr[iterm]->SetOvalArrDbl(oval_vec_arr[iterm]);
    }
    delete [] xval_vec_arr;
    delete [] oval_vec_arr;
    *g2d_arr_ptr = g2d_arr;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void GraphData2dOpe::GenSelectG2dArrByInterval(const GraphDataSerr2d* const graph_data,
                                               const Interval* const interval,
                                               GraphDataSerr2d*** g2d_arr_ptr,
                                               string select_type)
{
    long nterm = interval->GetNterm();
    GraphDataSerr2d** g2d_arr = new GraphDataSerr2d* [nterm];
    for(long iterm = 0; iterm < nterm; iterm ++){
        g2d_arr[iterm] = new GraphDataSerr2d;
    }
    vector<double>* xval_vec_arr      = new vector<double> [nterm];
    vector<double>* xval_serr_vec_arr = new vector<double> [nterm];
    vector<double>* oval_vec_arr      = new vector<double> [nterm];
    vector<double>* oval_serr_vec_arr = new vector<double> [nterm];
    long ndata = graph_data->GetNdata();    
    if("exclusive" == select_type){
        for(long idata = 0; idata < ndata; idata ++){
            for(long iterm = 0; iterm < nterm; iterm ++){
                double xval      = graph_data->GetXvalElm(idata);
                double xval_serr = graph_data->GetXvalSerrElm(idata);
                double oval      = graph_data->GetOvalElm(idata);
                double oval_serr = graph_data->GetOvalSerrElm(idata);
                if(interval->GetTstartElm(iterm) <= xval - xval_serr &&
                   xval + xval_serr <= interval->GetTstopElm(iterm)){
                    xval_vec_arr[iterm].push_back(xval);
                    xval_serr_vec_arr[iterm].push_back(xval_serr);
                    oval_vec_arr[iterm].push_back(oval);
                    oval_serr_vec_arr[iterm].push_back(oval_serr);
                }
            }
        }
    } else if ("center" == select_type){
        for(long idata = 0; idata < ndata; idata ++){
            for(long iterm = 0; iterm < nterm; iterm ++){
                double xval      = graph_data->GetXvalElm(idata);
                double xval_serr = graph_data->GetXvalSerrElm(idata);
                double oval      = graph_data->GetOvalElm(idata);
                double oval_serr = graph_data->GetOvalSerrElm(idata);
                if(interval->GetTstartElm(iterm) <= xval &&
                   xval <= interval->GetTstopElm(iterm)){
                    xval_vec_arr[iterm].push_back(xval);
                    xval_serr_vec_arr[iterm].push_back(xval_serr);
                    oval_vec_arr[iterm].push_back(oval);
                    oval_serr_vec_arr[iterm].push_back(oval_serr);
                }
            }
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "select_type(=%s)", select_type.c_str());
        MPrintErr(msg);
        abort();        
    }
        
    for(long iterm = 0; iterm < nterm; iterm ++){
        g2d_arr[iterm]->Init();
        g2d_arr[iterm]->SetXvalAndSerrArrDbl(xval_vec_arr[iterm], xval_serr_vec_arr[iterm]);
        g2d_arr[iterm]->SetOvalAndSerrArrDbl(oval_vec_arr[iterm], oval_serr_vec_arr[iterm]);
    }
    delete [] xval_vec_arr;
    delete [] xval_serr_vec_arr;
    delete [] oval_vec_arr;
    delete [] oval_serr_vec_arr;
    *g2d_arr_ptr = g2d_arr;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void GraphData2dOpe::GenSelectG2dArrByInterval(const GraphDataTerr2d* const graph_data,
                                               const Interval* const interval,
                                               GraphDataTerr2d*** g2d_arr_ptr,
                                               string select_type)
{
    long nterm = interval->GetNterm();
    GraphDataTerr2d** g2d_arr = new GraphDataTerr2d* [nterm];
    for(long iterm = 0; iterm < nterm; iterm ++){
        g2d_arr[iterm] = new GraphDataTerr2d;
    }
    vector<double>* xval_vec_arr = new vector<double> [nterm];
    vector<double>* xval_terr_plus_vec_arr = new vector<double> [nterm];
    vector<double>* xval_terr_minus_vec_arr = new vector<double> [nterm];    
    vector<double>* oval_vec_arr = new vector<double> [nterm];
    vector<double>* oval_terr_plus_vec_arr = new vector<double> [nterm];
    vector<double>* oval_terr_minus_vec_arr = new vector<double> [nterm];
    long ndata = graph_data->GetNdata();
    if("exclusive" == select_type){
        for(long idata = 0; idata < ndata; idata ++){
            for(long iterm = 0; iterm < nterm; iterm ++){
                double xval            = graph_data->GetXvalElm(idata);
                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
                double oval            = graph_data->GetOvalElm(idata);
                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
                if(interval->GetTstartElm(iterm) <= xval + xval_terr_minus &&
                   xval + xval_terr_plus <= interval->GetTstopElm(iterm)){
                    xval_vec_arr[iterm].push_back(xval);
                    xval_terr_plus_vec_arr[iterm].push_back(xval_terr_plus);
                    xval_terr_minus_vec_arr[iterm].push_back(xval_terr_minus);
                    oval_vec_arr[iterm].push_back(oval);
                    oval_terr_plus_vec_arr[iterm].push_back(oval_terr_plus);
                    oval_terr_minus_vec_arr[iterm].push_back(oval_terr_minus);
                }
            }
        }
    } else if ("center" == select_type){
        for(long idata = 0; idata < ndata; idata ++){
            for(long iterm = 0; iterm < nterm; iterm ++){
                double xval            = graph_data->GetXvalElm(idata);
                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
                double oval            = graph_data->GetOvalElm(idata);
                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
                if(interval->GetTstartElm(iterm) <= xval &&
                   xval <= interval->GetTstopElm(iterm)){
                    xval_vec_arr[iterm].push_back(xval);
                    xval_terr_plus_vec_arr[iterm].push_back(xval_terr_plus);
                    xval_terr_minus_vec_arr[iterm].push_back(xval_terr_minus);
                    oval_vec_arr[iterm].push_back(oval);
                    oval_terr_plus_vec_arr[iterm].push_back(oval_terr_plus);
                    oval_terr_minus_vec_arr[iterm].push_back(oval_terr_minus);
                }
            }
        }
    } else if ("varbinwidth" == select_type){
        for(long idata = 0; idata < ndata; idata ++){
            for(long iterm = 0; iterm < nterm; iterm ++){
                double xval            = graph_data->GetXvalElm(idata);
                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
                double oval            = graph_data->GetOvalElm(idata);
                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
                if(interval->GetTstartElm(iterm) <= xval &&
                   xval <= interval->GetTstopElm(iterm)    ){
                    xval_vec_arr[iterm].push_back(xval);
                    oval_vec_arr[iterm].push_back(oval);
                    oval_terr_plus_vec_arr[iterm].push_back(oval_terr_plus);
                    oval_terr_minus_vec_arr[iterm].push_back(oval_terr_minus);

                    if(xval + xval_terr_minus < interval->GetTstartElm(iterm)){
                        double xval_terr_minus_this = -1 * (xval - interval->GetTstartElm(iterm));
                        xval_terr_minus_vec_arr[iterm].push_back(xval_terr_minus_this);
                    }
                    if(interval->GetTstopElm(iterm) < xval + xval_terr_plus){
                        double xval_terr_plus_this = interval->GetTstopElm(iterm) - xval;
                        xval_terr_plus_vec_arr[iterm].push_back(xval_terr_plus_this);
                    }
                }
            }
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "select_type(=%s)", select_type.c_str());
        MPrintErr(msg);
        abort();        
    }
        
    for(long iterm = 0; iterm < nterm; iterm ++){
        g2d_arr[iterm]->Init();
        g2d_arr[iterm]->SetXvalAndTerrArrDbl(xval_vec_arr[iterm],
                                             xval_terr_plus_vec_arr[iterm],
                                             xval_terr_minus_vec_arr[iterm]);
        g2d_arr[iterm]->SetOvalAndTerrArrDbl(oval_vec_arr[iterm],
                                             oval_terr_plus_vec_arr[iterm],
                                             oval_terr_minus_vec_arr[iterm]);
    }
    delete [] xval_vec_arr;
    delete [] xval_terr_plus_vec_arr;
    delete [] xval_terr_minus_vec_arr;    
    delete [] oval_vec_arr;
    delete [] oval_terr_plus_vec_arr;
    delete [] oval_terr_minus_vec_arr;
    *g2d_arr_ptr = g2d_arr;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


GraphDataSerr2d* const GraphData2dOpe::GenGd2dByMergeGd2dArr(long ngraph,
                                                             const GraphDataSerr2d* const* const gd2d_arr)
{
    vector<double> xval_vec;
    vector<double> xval_serr_vec;
    vector<double> oval_vec;
    vector<double> oval_serr_vec;
    for(long igraph = 0; igraph < ngraph; igraph ++){
        for(long idata = 0; idata < gd2d_arr[igraph]->GetNdata(); idata ++){
            double xval = gd2d_arr[igraph]->GetXvalElm(idata);
            double xval_serr = gd2d_arr[igraph]->GetXvalSerrElm(idata);
            double oval = gd2d_arr[igraph]->GetOvalElm(idata);
            double oval_serr = gd2d_arr[igraph]->GetOvalSerrElm(idata);
            xval_vec.push_back(xval);
            xval_serr_vec.push_back(xval_serr);
            oval_vec.push_back(oval);
            oval_serr_vec.push_back(oval_serr);
        }
    }
    GraphDataSerr2d* gd2d_merge = new GraphDataSerr2d;
    gd2d_merge->Init();
    gd2d_merge->SetXvalAndSerrArrDbl(xval_vec, xval_serr_vec);
    gd2d_merge->SetOvalAndSerrArrDbl(oval_vec, oval_serr_vec);
    return gd2d_merge;
}

void GraphData2dOpe::GetResValGd2(const GraphData2d* const graph_data,
                                  const MirFunc* const func,
                                  const double* const par,
                                  GraphData2d* const graph_res_out)
{
    long ndata = graph_data->GetNdata();
    double* oval_res = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = graph_data->GetXvalElm(idata);
        oval_res[idata] = graph_data->GetOvalElm(idata) - func->Eval(xval, par);
    }
    graph_res_out->Init();
    graph_res_out->SetXvalArrDbl(ndata, graph_data->GetXvalArrDbl());
    graph_res_out->SetOvalArrDbl(ndata, oval_res);
  
    delete [] oval_res;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void GraphData2dOpe::GetResValGd2(const GraphDataSerr2d* const graph_data,
                                  const MirFunc* const func,
                                  const double* const par,
                                  GraphDataSerr2d* const graph_res_out)
{
    long ndata = graph_data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_serr = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = graph_data->GetXvalElm(idata);
        oval_res[idata] = graph_data->GetOvalElm(idata) - func->Eval(xval, par);
        oval_res_serr[idata] = graph_data->GetOvalSerrElm(idata);
    }
    
    graph_res_out->Init();
    graph_res_out->SetXvalAndSerrArrDbl(ndata,
                                        graph_data->GetXvalArrDbl(),
                                        graph_data->GetXvalSerrArrDbl());
    graph_res_out->SetOvalAndSerrArrDbl(ndata, oval_res, oval_res_serr);
  
    delete [] oval_res;
    delete [] oval_res_serr;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void GraphData2dOpe::GetResValGd2(const GraphDataTerr2d* const graph_data,
                                  const MirFunc* const func,
                                  const double* const par,
                                  GraphDataTerr2d* const graph_res_out)
{
    long ndata = graph_data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_terr_plus  = new double[ndata];
    double* oval_res_terr_minus = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = graph_data->GetXvalElm(idata);
        oval_res[idata] = graph_data->GetOvalElm(idata) - func->Eval(xval, par);
        oval_res_terr_plus[idata]  = graph_data->GetOvalTerrPlusElm(idata);
        oval_res_terr_minus[idata] = graph_data->GetOvalTerrMinusElm(idata);
    }

    graph_res_out->Init();
    graph_res_out->SetXvalAndTerrArrDbl(ndata,
                                        graph_data->GetXvalArrDbl(),
                                        graph_data->GetXvalTerrPlusArrDbl(),
                                        graph_data->GetXvalTerrMinusArrDbl());
    graph_res_out->SetOvalAndTerrArrDbl(ndata,
                                        oval_res,
                                        oval_res_terr_plus,
                                        oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void GraphData2dOpe::GetResRatioGd2(const GraphData2d* const graph_data,
                                    const MirFunc* const func,
                                    const double* const par,
                                    GraphData2d* const graph_res_out)
{
    long ndata = graph_data->GetNdata();
    double* oval_res = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = graph_data->GetXvalElm(idata);
        oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
            func->Eval(xval, par);
    }
    graph_res_out->Init();
    graph_res_out->SetXvalArrDbl(ndata, graph_data->GetXvalArrDbl());
    graph_res_out->SetOvalArrDbl(ndata, oval_res);
  
    delete [] oval_res;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


void GraphData2dOpe::GetResRatioGd2(const GraphDataSerr2d* const graph_data,
                                    const MirFunc* const func,
                                    const double* const par,
                                    GraphDataSerr2d* const graph_res_out)
{
    long ndata = graph_data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_serr = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = graph_data->GetXvalElm(idata);
        oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
            func->Eval(xval, par);
        oval_res_serr[idata] = fabs(graph_data->GetOvalSerrElm(idata) / func->Eval(xval, par));
    }

    graph_res_out->Init();
    graph_res_out->SetXvalAndSerrArrDbl(ndata,
                                        graph_data->GetXvalArrDbl(),
                                        graph_data->GetXvalSerrArrDbl());
    graph_res_out->SetOvalAndSerrArrDbl(ndata, oval_res, oval_res_serr);
  
    delete [] oval_res;
    delete [] oval_res_serr;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void GraphData2dOpe::GetResRatioGd2(const GraphDataTerr2d* const graph_data,
                                    const MirFunc* const func,
                                    const double* const par,
                                    GraphDataTerr2d* const graph_res_out)
{
    long ndata = graph_data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_terr_plus  = new double[ndata];
    double* oval_res_terr_minus = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = graph_data->GetXvalElm(idata);
        oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
            func->Eval(xval, par);
        oval_res_terr_plus[idata]  = fabs(graph_data->GetOvalTerrPlusElm(idata) / func->Eval(xval, par));
        oval_res_terr_minus[idata] = -1 * fabs(graph_data->GetOvalTerrMinusElm(idata) / func->Eval(xval, par));
    }

    graph_res_out->Init();
    graph_res_out->SetXvalAndTerrArrDbl(ndata,
                                        graph_data->GetXvalArrDbl(),
                                        graph_data->GetXvalTerrPlusArrDbl(),
                                        graph_data->GetXvalTerrMinusArrDbl());
    graph_res_out->SetOvalAndTerrArrDbl(ndata,
                                        oval_res,
                                        oval_res_terr_plus,
                                        oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void GraphData2dOpe::GetResChiGd2(const GraphDataSerr2d* const graph_data,
                                  const MirFunc* const func,
                                  const double* const par,
                                  GraphDataSerr2d* const graph_res_out)
{
    long ndata = graph_data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_serr = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = graph_data->GetXvalElm(idata);
        oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
            graph_data->GetOvalSerrElm(idata);
        oval_res_serr[idata] = 1.0;
    }

    graph_res_out->Init();
    graph_res_out->SetXvalAndSerrArrDbl(ndata,
                                        graph_data->GetXvalArrDbl(),
                                        graph_data->GetXvalSerrArrDbl());
    graph_res_out->SetOvalAndSerrArrDbl(ndata, oval_res, oval_res_serr);
  
    delete [] oval_res;
    delete [] oval_res_serr;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}
 

void GraphData2dOpe::GetResChiGd2(const GraphDataTerr2d* const graph_data,
                                  const MirFunc* const func,
                                  const double* const par,
                                  GraphDataTerr2d* const graph_res_out)
{
    long ndata = graph_data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_terr_plus  = new double[ndata];
    double* oval_res_terr_minus = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = graph_data->GetXvalElm(idata);
        if( 0 <= graph_data->GetOvalElm(idata) - func->Eval(xval, par) ){
            oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
                (-1 * graph_data->GetOvalTerrMinusElm(idata));
        } else {
            oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
                graph_data->GetOvalTerrPlusElm(idata);
        }
        oval_res_terr_plus[idata] = 1.0;
        oval_res_terr_minus[idata] = -1.0;
    }
    
    graph_res_out->Init();
    graph_res_out->SetXvalAndTerrArrDbl(ndata,
                                        graph_data->GetXvalArrDbl(),
                                        graph_data->GetXvalTerrPlusArrDbl(),
                                        graph_data->GetXvalTerrMinusArrDbl());
    graph_res_out->SetOvalAndTerrArrDbl(ndata,
                                        oval_res,
                                        oval_res_terr_plus,
                                        oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


GraphDataSerr2d* const GraphData2dOpe::GenGd2dBinBySigVar(const GraphDataSerr2d* const gd2d,
                                                          double pval_threshold)
{
    vector<double> xval_binned_vec;
    vector<double> xval_serr_binned_vec;
    vector<double> oval_binned_vec;
    vector<double> oval_serr_binned_vec;
    
    vector<double> xval_vec_pre;
    vector<double> xval_serr_vec_pre;
    vector<double> oval_vec_pre;
    vector<double> oval_serr_vec_pre;

    vector<double> xval_vec;
    vector<double> xval_serr_vec;
    vector<double> oval_vec;
    vector<double> oval_serr_vec;
    
    for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
        double xval = gd2d->GetXvalElm(idata);
        double xval_serr = gd2d->GetXvalSerrElm(idata);
        double oval = gd2d->GetOvalElm(idata);
        double oval_serr = gd2d->GetOvalSerrElm(idata);
        if(0 == oval_vec_pre.size()){
            xval_vec_pre.push_back(xval);
            xval_serr_vec_pre.push_back(xval_serr);
            oval_vec_pre.push_back(oval);
            oval_serr_vec_pre.push_back(oval_serr);
            continue;
        }
        
        xval_vec = xval_vec_pre;
        xval_serr_vec = xval_serr_vec_pre;
        oval_vec = oval_vec_pre;
        oval_serr_vec = oval_serr_vec_pre;
        xval_vec.push_back(xval);
        xval_serr_vec.push_back(xval_serr);
        oval_vec.push_back(oval);
        oval_serr_vec.push_back(oval_serr);

        double* oval_arr_pre = MirMath::GenArray(oval_vec_pre);
        double* oval_serr_arr_pre = MirMath::GenArray(oval_serr_vec_pre);
        double chi2_pre = 0.0;
        long dof_pre = 0;
        if(1 == oval_vec_pre.size()){
            chi2_pre = 0.0;
            dof_pre = 0;
        } else {
            double chi2_red_pre = 0.0;
            double prob_pre = 0.0;
            int num_bad_pre = MirMath::GetChi2byConst(oval_vec_pre.size(),
                                                       oval_arr_pre,
                                                       oval_serr_arr_pre,
                                                       &chi2_pre,
                                                       &dof_pre,
                                                       &chi2_red_pre,
                                                       &prob_pre);
            if(num_bad_pre > 0){
                printf("warning: num_bad_pre = %d\n", num_bad_pre);
            }
            
        }
        if(2 > oval_vec.size()){
            MPrintErr("something is wrong.\n");
            abort();
        }
        double* oval_arr = MirMath::GenArray(oval_vec);
        double* oval_serr_arr = MirMath::GenArray(oval_serr_vec);
        double chi2 = 0.0;
        long dof = 0;
        double chi2_red = 0.0;
        double prob = 0.0;
        int num_bad = MirMath::GetChi2byConst(oval_vec.size(),
                                               oval_arr,
                                               oval_serr_arr,
                                               &chi2,
                                               &dof,
                                               &chi2_red,
                                               &prob);
        if(num_bad > 0){
            printf("warning: num_bad = %d\n", num_bad);
        }
        delete [] oval_arr_pre;
        delete [] oval_serr_arr_pre;
        delete [] oval_arr;
        delete [] oval_serr_arr;

        long delta_dof = dof - dof_pre;
        if(1 != delta_dof){
            MPrintErr("something is wrong.\n");
            printf("dof, dof_pre = %d, %d\n", (int) dof, (int) dof_pre);
            printf("idata = %d\n", (int) idata);
            abort();
        }
        double delta_chi2 = chi2 - chi2_pre;
        double p_value = TMath::Prob(delta_chi2, delta_dof);
        if(p_value < pval_threshold){
            // significant
            double xval_bin_center = 0.0;
            double xval_bin_half_width = 0.0;
            double wmean = 0.0;
            double wmean_err = 0.0;
            GraphDataSerr2d::GetValBinned(xval_vec_pre,
                                          xval_serr_vec_pre,
                                          oval_vec_pre,
                                          oval_serr_vec_pre,
                                          &xval_bin_center,
                                          &xval_bin_half_width,
                                          &wmean,
                                          &wmean_err);
            xval_binned_vec.push_back(xval_bin_center);
            xval_serr_binned_vec.push_back(xval_bin_half_width);
            oval_binned_vec.push_back(wmean);
            oval_serr_binned_vec.push_back(wmean_err);

            // for next turn
            xval_vec_pre.clear();
            xval_serr_vec_pre.clear();
            oval_vec_pre.clear();
            oval_serr_vec_pre.clear();
            xval_vec_pre.push_back(xval);
            xval_serr_vec_pre.push_back(xval_serr);
            oval_vec_pre.push_back(oval);
            oval_serr_vec_pre.push_back(oval_serr);
        } else {
            // not significant

            // for next turn            
            xval_vec_pre = xval_vec;
            xval_serr_vec_pre = xval_serr_vec;
            oval_vec_pre = oval_vec;
            oval_serr_vec_pre = oval_serr_vec;
        }

    }

    double xval_bin_center = 0.0;
    double xval_bin_half_width = 0.0;
    double wmean = 0.0;
    double wmean_err = 0.0;
    GraphDataSerr2d::GetValBinned(xval_vec_pre,
                                  xval_serr_vec_pre,
                                  oval_vec_pre,
                                  oval_serr_vec_pre,
                                  &xval_bin_center,
                                  &xval_bin_half_width,
                                  &wmean,
                                  &wmean_err);
    xval_binned_vec.push_back(xval_bin_center);
    xval_serr_binned_vec.push_back(xval_bin_half_width);
    oval_binned_vec.push_back(wmean);
    oval_serr_binned_vec.push_back(wmean_err);

    GraphDataSerr2d* gd2d_binned = new GraphDataSerr2d;
    gd2d_binned->Init();
    gd2d_binned->SetXvalAndSerrArrDbl(xval_binned_vec, xval_serr_binned_vec);
    gd2d_binned->SetOvalAndSerrArrDbl(oval_binned_vec, oval_serr_binned_vec);

    return gd2d_binned;
}


GraphDataSerr2d* const GraphData2dOpe::GenGd2dBinBySigDet(const GraphDataSerr2d* const gd2d,
                                                          double pval_threshold)
{
    vector<double> xval_binned_vec;
    vector<double> xval_serr_binned_vec;
    vector<double> oval_binned_vec;
    vector<double> oval_serr_binned_vec;
    
    vector<double> xval_vec;
    vector<double> xval_serr_vec;
    vector<double> oval_vec;
    vector<double> oval_serr_vec;
    
    for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
        double xval = gd2d->GetXvalElm(idata);
        double xval_serr = gd2d->GetXvalSerrElm(idata);
        double oval = gd2d->GetOvalElm(idata);
        double oval_serr = gd2d->GetOvalSerrElm(idata);

        // check single detection
        if(oval >= 0.0 &&  oval_serr > DBL_EPSILON){
            double sig_sigma = oval / oval_serr;
            double sig_prob = MirMath::Sigma2CL(sig_sigma);
            double p_value = 1.0 - sig_prob;
            if(p_value < pval_threshold){

                if(0 < xval_vec.size()){
                    double xval_bin_center = 0.0;
                    double xval_bin_half_width = 0.0;
                    double wmean_this = 0.0;
                    double wmean_serr_this = 0.0;
                    GraphDataSerr2d::GetValBinned(xval_vec,
                                                  xval_serr_vec,
                                                  oval_vec,
                                                  oval_serr_vec,
                                                  &xval_bin_center,
                                                  &xval_bin_half_width,
                                                  &wmean_this,
                                                  &wmean_serr_this);
                    xval_binned_vec.push_back(xval_bin_center);
                    xval_serr_binned_vec.push_back(xval_bin_half_width);
                    oval_binned_vec.push_back(wmean_this);
                    oval_serr_binned_vec.push_back(wmean_serr_this);

                    xval_vec.clear();
                    xval_serr_vec.clear();
                    oval_vec.clear();
                    oval_serr_vec.clear();
                }
            }
        }

        xval_vec.push_back(xval);
        xval_serr_vec.push_back(xval_serr);
        oval_vec.push_back(oval);
        oval_serr_vec.push_back(oval_serr);        

        double* oval_arr = MirMath::GenArray(oval_vec);
        double* oval_serr_arr = MirMath::GenArray(oval_serr_vec);
        double wmean = 0.0;
        double wmean_serr = 0.0;
        vector<long> index_bad_vec;
        MirMath::GetWMean(oval_vec.size(),
                           oval_arr,
                           oval_serr_arr,
                           &wmean, &wmean_serr, &index_bad_vec);
        delete [] oval_arr;
        delete [] oval_serr_arr;

        if(wmean < 0.0){
            continue;
        }
        if(wmean_serr < DBL_EPSILON){
            MPrintErr("wmean_serr < DBL_EPSILON, then something is wrong.\n");
            abort();
        }
        double sig_sigma = wmean / wmean_serr;
        double sig_prob = MirMath::Sigma2CL(sig_sigma);
        double p_value = 1.0 - sig_prob;
        
        if(p_value < pval_threshold){
            // significant
            double xval_bin_center = 0.0;
            double xval_bin_half_width = 0.0;
            double wmean_this = 0.0;
            double wmean_serr_this = 0.0;
            GraphDataSerr2d::GetValBinned(xval_vec,
                                          xval_serr_vec,
                                          oval_vec,
                                          oval_serr_vec,
                                          &xval_bin_center,
                                          &xval_bin_half_width,
                                          &wmean_this,
                                          &wmean_serr_this);
            xval_binned_vec.push_back(xval_bin_center);
            xval_serr_binned_vec.push_back(xval_bin_half_width);
            oval_binned_vec.push_back(wmean_this);
            oval_serr_binned_vec.push_back(wmean_serr_this);

            // for next turn
            xval_vec.clear();
            xval_serr_vec.clear();
            oval_vec.clear();
            oval_serr_vec.clear();
        }
    }

    // bin last one
    if(0 < xval_vec.size()){
        double xval_bin_center = 0.0;
        double xval_bin_half_width = 0.0;
        double wmean_this = 0.0;
        double wmean_serr_this = 0.0;
        GraphDataSerr2d::GetValBinned(xval_vec,
                                      xval_serr_vec,
                                      oval_vec,
                                      oval_serr_vec,
                                      &xval_bin_center,
                                      &xval_bin_half_width,
                                      &wmean_this,
                                      &wmean_serr_this);
        xval_binned_vec.push_back(xval_bin_center);
        xval_serr_binned_vec.push_back(xval_bin_half_width);
        oval_binned_vec.push_back(wmean_this);
        oval_serr_binned_vec.push_back(wmean_serr_this);
    }

    GraphDataSerr2d* gd2d_binned = new GraphDataSerr2d;
    gd2d_binned->Init();
    gd2d_binned->SetXvalAndSerrArrDbl(xval_binned_vec, xval_serr_binned_vec);
    gd2d_binned->SetOvalAndSerrArrDbl(oval_binned_vec, oval_serr_binned_vec);

    return gd2d_binned;
}

