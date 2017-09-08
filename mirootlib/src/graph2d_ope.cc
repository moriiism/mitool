#include "mir_graph2d_ope.h"

void GraphData2dOpe::GetMotion(const GraphDataNerr2d* const gd2d,
                               double shiftx, double shifty, double angle, int flag,
                               GraphDataNerr2d* const gd2d_out)
{
    gd2d_out->Init(gd2d->GetNdata());
    for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
        Vect2d* vect = new Vect2d;
        vect->Init(gd2d->GetXvalElm(idata), gd2d->GetOvalElm(idata));
        Vect2d* vect_conv = MirGeom::GenMotion(vect, shiftx, shifty, angle, flag);
        gd2d_out->SetPoint(idata, vect_conv->GetPosX(), vect_conv->GetPosY());
        delete vect;
        delete vect_conv;
    }
}


GraphData2d* const GraphData2dOpe::GenGd2dByLoad(string file, string format)
{
    GraphData2d* gd2d = NULL;
    if("x,y" == format){
        gd2d = new GraphDataNerr2d;
    } else if("x,y,ye" == format){
        gd2d = new GraphDataSerr2d;
    } else if("x,y,ye+,ye-" == format){
        gd2d = new GraphDataTerr2d;        
    } else if("x,xe,y" == format){
        gd2d = new GraphDataSerr2d;
    } else if("x,xe,y,ye" == format){
        gd2d = new GraphDataSerr2d;
    } else if("x,xe,y,ye+,ye-" == format){
        gd2d = new GraphDataTerr2d;
    } else if("x,xe+,xe-,y" == format){
        gd2d = new GraphDataTerr2d;
    } else if("x,xe+,xe-,y,ye" == format){
        gd2d = new GraphDataTerr2d;        
    } else if("x,xe+,xe-,y,ye+,ye-" == format){
        gd2d = new GraphDataTerr2d;
    } else {
        MPrintErr("bad format");
        abort();
    }
    gd2d->Load(file, format);
    return gd2d;
}


//
//void GraphData2dOpe::GetSelectG2dByInterval(const GraphData2d* const graph_data,
//                                            const Interval* const interval,
//                                            GraphData2d* const graph_out)
//{
//    vector<double> xval_new;
//    vector<double> oval_new;
//    long ndata = graph_data->GetNdata();
//    long nterm = interval->GetNterm();
//    for(long idata = 0; idata < ndata; idata++){
//        for(int iterm = 0; iterm < nterm; iterm ++){
//            double xval = graph_data->GetXvalElm(idata);
//            double oval = graph_data->GetOvalElm(idata);
//            if(interval->GetTstartElm(iterm) <= xval &&
//               xval <= interval->GetTstopElm(iterm) ){
//                xval_new.push_back(xval);
//                oval_new.push_back(oval);
//            }
//        }
//    }
//    graph_out->Init(xval_new.size());
//    graph_out->SetXvalArr(xval_new);
//    graph_out->SetOvalArr(oval_new);
//}
//
//void GraphData2dOpe::GetSelectG2dByInterval(const GraphDataSerr2d* const graph_data,
//                                            const Interval* const interval,
//                                            GraphDataSerr2d* const graph_out,
//                                            string select_type)
//{
//    vector<double> xval_new;
//    vector<double> xval_serr_new;
//    vector<double> oval_new;
//    vector<double> oval_serr_new;
//    long ndata = graph_data->GetNdata();
//    if("exclusive" == select_type){
//        for(long idata = 0; idata < ndata; idata++){
//            for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
//                double xval      = graph_data->GetXvalElm(idata);
//                double xval_serr = graph_data->GetXvalSerrElm(idata);
//                double oval      = graph_data->GetOvalElm(idata);
//                double oval_serr = graph_data->GetOvalSerrElm(idata);
//                if( interval->GetTstart()[iterm] <= xval - xval_serr &&
//                    xval + xval_serr <= interval->GetTstop()[iterm]     ){
//                    xval_new.push_back(xval);
//                    xval_serr_new.push_back(xval_serr);
//                    oval_new.push_back(oval);
//                    oval_serr_new.push_back(oval_serr);
//                }
//            }
//        }
//    } else if ("center" == select_type){
//        for(long idata = 0; idata < ndata; idata++){
//            for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
//                double xval      = graph_data->GetXvalElm(idata);
//                double xval_serr = graph_data->GetXvalSerrElm(idata);
//                double oval      = graph_data->GetOvalElm(idata);
//                double oval_serr = graph_data->GetOvalSerrElm(idata);
//                if(interval->GetTstart()[iterm] <= xval &&
//                   xval <= interval->GetTstop()[iterm]){
//                    xval_new.push_back(xval);
//                    xval_serr_new.push_back(xval_serr);
//                    oval_new.push_back(oval);
//                    oval_serr_new.push_back(oval_serr);
//                }
//            }
//        }
//    } else {
//        char msg[kLineSize];
//        sprintf(msg, "select_type(=%s)", select_type.c_str());
//        MPrintErr(msg);
//        abort();
//    }
//
//    graph_out->Init(xval_new.size());
//    graph_out->SetXvalArr(xval_new);
//    graph_out->SetXvalSerrArr(xval_serr_new);
//    graph_out->SetOvalArr(oval_new);
//    graph_out->SetOvalSerrArr(oval_serr_new);
//}
//
//
//void GraphData2dOpe::GetSelectG2dByInterval(const GraphDataTerr2d* const graph_data,
//                                            const Interval* const interval,
//                                            GraphDataTerr2d* const graph_out,
//                                            string select_type)
//{
//    vector<double> xval_new;
//    vector<double> xval_terr_plus_new;
//    vector<double> xval_terr_minus_new;
//    vector<double> oval_new;
//    vector<double> oval_terr_plus_new;
//    vector<double> oval_terr_minus_new;
//    long ndata = graph_data->GetNdata();
//    if("exclusive" == select_type){
//        for(long idata = 0; idata < ndata; idata++){
//            for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
//                double xval            = graph_data->GetXvalElm(idata);
//                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
//                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
//                double oval            = graph_data->GetOvalElm(idata);
//                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
//                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
//                if( interval->GetTstartElm(iterm) <= xval + xval_terr_minus &&
//                    xval + xval_terr_plus <= interval->GetTstopElm(iterm)     ){
//                    xval_new.push_back(xval);
//                    xval_terr_plus_new.push_back(xval_terr_plus);
//                    xval_terr_minus_new.push_back(xval_terr_minus);
//                    oval_new.push_back(oval);
//                    oval_terr_plus_new.push_back(oval_terr_plus);
//                    oval_terr_minus_new.push_back(oval_terr_minus);
//                }
//            }
//        }
//    } else if ("center" == select_type){
//        for(long idata = 0; idata < ndata; idata++){
//            for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
//                double xval            = graph_data->GetXvalElm(idata);
//                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
//                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
//                double oval            = graph_data->GetOvalElm(idata);
//                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
//                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
//                if(interval->GetTstartElm(iterm) <= xval &&
//                   xval <= interval->GetTstopElm(iterm)    ){
//                    xval_new.push_back(xval);
//                    xval_terr_plus_new.push_back(xval_terr_plus);
//                    xval_terr_minus_new.push_back(xval_terr_minus);
//                    oval_new.push_back(oval);
//                    oval_terr_plus_new.push_back(oval_terr_plus);
//                    oval_terr_minus_new.push_back(oval_terr_minus);
//                }
//            }
//        }
//    } else if ("varbinwidth" == select_type){
//        for(long idata = 0; idata < ndata; idata++){
//            for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
//                double xval            = graph_data->GetXvalElm(idata);
//                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
//                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
//                double oval            = graph_data->GetOvalElm(idata);
//                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
//                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
//                if(interval->GetTstartElm(iterm) <= xval &&
//                   xval <= interval->GetTstopElm(iterm)    ){
//                    xval_new.push_back(xval);
//                    oval_new.push_back(oval);
//                    oval_terr_plus_new.push_back(oval_terr_plus);
//                    oval_terr_minus_new.push_back(oval_terr_minus);
//
//                    if(xval + xval_terr_minus < interval->GetTstartElm(iterm)){
//                        double xval_terr_minus_this = -1 * (xval - interval->GetTstartElm(iterm));
//                        xval_terr_minus_new.push_back(xval_terr_minus_this);
//                    }
//                    if(interval->GetTstopElm(iterm) < xval + xval_terr_plus){
//                        double xval_terr_plus_this = interval->GetTstopElm(iterm) - xval;
//                        xval_terr_plus_new.push_back(xval_terr_plus_this);
//                    }
//                }
//            }
//        }
//    } else {
//        char msg[kLineSize];
//        sprintf(msg, "select_type(=%s)", select_type.c_str());
//        MPrintErr(msg);
//        abort();
//    }
//
//    graph_out->Init(xval_new.size());
//    graph_out->SetXvalArr(xval_new);
//    graph_out->SetXvalTerrArr(xval_terr_plus_new, xval_terr_minus_new);
//    graph_out->SetOvalArr(oval_new);
//    graph_out->SetOvalTerrArr(oval_terr_plus_new, oval_terr_minus_new);
//}
//
//void GraphData2dOpe::GenSelectG2dArrByInterval(const GraphDataNerr2d* const graph_data,
//                                               const Interval* const interval,
//                                               GraphDataNerr2d*** g2d_arr_ptr)
//{
//    long nterm = interval->GetNterm();
//    GraphDataNerr2d** g2d_arr = new GraphDataNerr2d* [nterm];
//    for(long iterm = 0; iterm < nterm; iterm ++){
//        g2d_arr[iterm] = new GraphDataNerr2d;
//    }
//    vector<double>* xval_vec_arr = new vector<double> [nterm];
//    vector<double>* oval_vec_arr = new vector<double> [nterm];
//
//    long ndata = graph_data->GetNdata();
//    for(long idata = 0; idata < ndata; idata ++){
//        for(long iterm = 0; iterm < nterm; iterm ++){
//            double xval = graph_data->GetXvalElm(idata);
//            double oval = graph_data->GetOvalElm(idata);
//            if(interval->GetTstartElm(iterm) <= xval &&
//               xval <= interval->GetTstopElm(iterm)){
//                xval_vec_arr[iterm].push_back(xval);
//                oval_vec_arr[iterm].push_back(oval);
//            }
//        }
//    }
//    for(long iterm = 0; iterm < nterm; iterm ++){
//        g2d_arr[iterm]->Init(xval_vec_arr[iterm].size());
//        g2d_arr[iterm]->SetXvalArr(xval_vec_arr[iterm]);
//        g2d_arr[iterm]->SetOvalArr(oval_vec_arr[iterm]);
//    }
//    delete [] xval_vec_arr;
//    delete [] oval_vec_arr;
//    *g2d_arr_ptr = g2d_arr;
//}
//
//void GraphData2dOpe::GenSelectG2dArrByInterval(const GraphDataSerr2d* const graph_data,
//                                               const Interval* const interval,
//                                               GraphDataSerr2d*** g2d_arr_ptr,
//                                               string select_type)
//{
//    long nterm = interval->GetNterm();
//    GraphDataSerr2d** g2d_arr = new GraphDataSerr2d* [nterm];
//    for(long iterm = 0; iterm < nterm; iterm ++){
//        g2d_arr[iterm] = new GraphDataSerr2d;
//    }
//    vector<double>* xval_vec_arr      = new vector<double> [nterm];
//    vector<double>* xval_serr_vec_arr = new vector<double> [nterm];
//    vector<double>* oval_vec_arr      = new vector<double> [nterm];
//    vector<double>* oval_serr_vec_arr = new vector<double> [nterm];
//    long ndata = graph_data->GetNdata();    
//    if("exclusive" == select_type){
//        for(long idata = 0; idata < ndata; idata ++){
//            for(long iterm = 0; iterm < nterm; iterm ++){
//                double xval      = graph_data->GetXvalElm(idata);
//                double xval_serr = graph_data->GetXvalSerrElm(idata);
//                double oval      = graph_data->GetOvalElm(idata);
//                double oval_serr = graph_data->GetOvalSerrElm(idata);
//                if(interval->GetTstartElm(iterm) <= xval - xval_serr &&
//                   xval + xval_serr <= interval->GetTstopElm(iterm)){
//                    xval_vec_arr[iterm].push_back(xval);
//                    xval_serr_vec_arr[iterm].push_back(xval_serr);
//                    oval_vec_arr[iterm].push_back(oval);
//                    oval_serr_vec_arr[iterm].push_back(oval_serr);
//                }
//            }
//        }
//    } else if ("center" == select_type){
//        for(long idata = 0; idata < ndata; idata ++){
//            for(long iterm = 0; iterm < nterm; iterm ++){
//                double xval      = graph_data->GetXvalElm(idata);
//                double xval_serr = graph_data->GetXvalSerrElm(idata);
//                double oval      = graph_data->GetOvalElm(idata);
//                double oval_serr = graph_data->GetOvalSerrElm(idata);
//                if(interval->GetTstartElm(iterm) <= xval &&
//                   xval <= interval->GetTstopElm(iterm)){
//                    xval_vec_arr[iterm].push_back(xval);
//                    xval_serr_vec_arr[iterm].push_back(xval_serr);
//                    oval_vec_arr[iterm].push_back(oval);
//                    oval_serr_vec_arr[iterm].push_back(oval_serr);
//                }
//            }
//        }
//    } else {
//        char msg[kLineSize];
//        sprintf(msg, "select_type(=%s)", select_type.c_str());
//        MPrintErr(msg);
//        abort();        
//    }
//        
//    for(long iterm = 0; iterm < nterm; iterm ++){
//        g2d_arr[iterm]->Init(xval_vec_arr[iterm].size());
//        g2d_arr[iterm]->SetXvalArr(xval_vec_arr[iterm]);
//        g2d_arr[iterm]->SetXvalSerrArr(xval_serr_vec_arr[iterm]);
//        g2d_arr[iterm]->SetOvalArr(oval_vec_arr[iterm]);
//        g2d_arr[iterm]->SetOvalSerrArr(oval_serr_vec_arr[iterm]);
//    }
//    delete [] xval_vec_arr;
//    delete [] xval_serr_vec_arr;
//    delete [] oval_vec_arr;
//    delete [] oval_serr_vec_arr;
//    *g2d_arr_ptr = g2d_arr;
//}
//
//void GraphData2dOpe::GenSelectG2dArrByInterval(const GraphDataTerr2d* const graph_data,
//                                               const Interval* const interval,
//                                               GraphDataTerr2d*** g2d_arr_ptr,
//                                               string select_type)
//{
//    long nterm = interval->GetNterm();
//    GraphDataTerr2d** g2d_arr = new GraphDataTerr2d* [nterm];
//    for(long iterm = 0; iterm < nterm; iterm ++){
//        g2d_arr[iterm] = new GraphDataTerr2d;
//    }
//    vector<double>* xval_vec_arr = new vector<double> [nterm];
//    vector<double>* xval_terr_plus_vec_arr = new vector<double> [nterm];
//    vector<double>* xval_terr_minus_vec_arr = new vector<double> [nterm];    
//    vector<double>* oval_vec_arr = new vector<double> [nterm];
//    vector<double>* oval_terr_plus_vec_arr = new vector<double> [nterm];
//    vector<double>* oval_terr_minus_vec_arr = new vector<double> [nterm];
//    long ndata = graph_data->GetNdata();
//    if("exclusive" == select_type){
//        for(long idata = 0; idata < ndata; idata ++){
//            for(long iterm = 0; iterm < nterm; iterm ++){
//                double xval            = graph_data->GetXvalElm(idata);
//                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
//                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
//                double oval            = graph_data->GetOvalElm(idata);
//                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
//                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
//                if(interval->GetTstartElm(iterm) <= xval + xval_terr_minus &&
//                   xval + xval_terr_plus <= interval->GetTstopElm(iterm)){
//                    xval_vec_arr[iterm].push_back(xval);
//                    xval_terr_plus_vec_arr[iterm].push_back(xval_terr_plus);
//                    xval_terr_minus_vec_arr[iterm].push_back(xval_terr_minus);
//                    oval_vec_arr[iterm].push_back(oval);
//                    oval_terr_plus_vec_arr[iterm].push_back(oval_terr_plus);
//                    oval_terr_minus_vec_arr[iterm].push_back(oval_terr_minus);
//                }
//            }
//        }
//    } else if ("center" == select_type){
//        for(long idata = 0; idata < ndata; idata ++){
//            for(long iterm = 0; iterm < nterm; iterm ++){
//                double xval            = graph_data->GetXvalElm(idata);
//                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
//                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
//                double oval            = graph_data->GetOvalElm(idata);
//                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
//                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
//                if(interval->GetTstartElm(iterm) <= xval &&
//                   xval <= interval->GetTstopElm(iterm)){
//                    xval_vec_arr[iterm].push_back(xval);
//                    xval_terr_plus_vec_arr[iterm].push_back(xval_terr_plus);
//                    xval_terr_minus_vec_arr[iterm].push_back(xval_terr_minus);
//                    oval_vec_arr[iterm].push_back(oval);
//                    oval_terr_plus_vec_arr[iterm].push_back(oval_terr_plus);
//                    oval_terr_minus_vec_arr[iterm].push_back(oval_terr_minus);
//                }
//            }
//        }
//    } else if ("varbinwidth" == select_type){
//        for(long idata = 0; idata < ndata; idata ++){
//            for(long iterm = 0; iterm < nterm; iterm ++){
//                double xval            = graph_data->GetXvalElm(idata);
//                double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
//                double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
//                double oval            = graph_data->GetOvalElm(idata);
//                double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
//                double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
//                if(interval->GetTstartElm(iterm) <= xval &&
//                   xval <= interval->GetTstopElm(iterm)    ){
//                    xval_vec_arr[iterm].push_back(xval);
//                    oval_vec_arr[iterm].push_back(oval);
//                    oval_terr_plus_vec_arr[iterm].push_back(oval_terr_plus);
//                    oval_terr_minus_vec_arr[iterm].push_back(oval_terr_minus);
//
//                    if(xval + xval_terr_minus < interval->GetTstartElm(iterm)){
//                        double xval_terr_minus_this = -1 * (xval - interval->GetTstartElm(iterm));
//                        xval_terr_minus_vec_arr[iterm].push_back(xval_terr_minus_this);
//                    }
//                    if(interval->GetTstopElm(iterm) < xval + xval_terr_plus){
//                        double xval_terr_plus_this = interval->GetTstopElm(iterm) - xval;
//                        xval_terr_plus_vec_arr[iterm].push_back(xval_terr_plus_this);
//                    }
//                }
//            }
//        }
//    } else {
//        char msg[kLineSize];
//        sprintf(msg, "select_type(=%s)", select_type.c_str());
//        MPrintErr(msg);
//        abort();        
//    }
//        
//    for(long iterm = 0; iterm < nterm; iterm ++){
//        g2d_arr[iterm]->Init(xval_vec_arr[iterm].size());
//        g2d_arr[iterm]->SetXvalArr(xval_vec_arr[iterm]);
//        g2d_arr[iterm]->SetXvalTerrArr(xval_terr_plus_vec_arr[iterm],
//                                       xval_terr_minus_vec_arr[iterm]);
//        g2d_arr[iterm]->SetOvalArr(oval_vec_arr[iterm]);
//        g2d_arr[iterm]->SetOvalTerrArr(oval_terr_plus_vec_arr[iterm],
//                                       oval_terr_minus_vec_arr[iterm]);
//        
//    }
//    delete [] xval_vec_arr;
//    delete [] xval_terr_plus_vec_arr;
//    delete [] xval_terr_minus_vec_arr;    
//    delete [] oval_vec_arr;
//    delete [] oval_terr_plus_vec_arr;
//    delete [] oval_terr_minus_vec_arr;
//    *g2d_arr_ptr = g2d_arr;
//}
//
//
//GraphDataSerr2d* const GraphData2dOpe::GenGd2dByMergeGd2dArr(long ngraph,
//                                                             const GraphDataSerr2d* const* const gd2d_arr)
//{
//    vector<double> xval_vec;
//    vector<double> xval_serr_vec;
//    vector<double> oval_vec;
//    vector<double> oval_serr_vec;
//    for(long igraph = 0; igraph < ngraph; igraph ++){
//        for(long idata = 0; idata < gd2d_arr[igraph]->GetNdata(); idata ++){
//            double xval = gd2d_arr[igraph]->GetXvalElm(idata);
//            double xval_serr = gd2d_arr[igraph]->GetXvalSerrElm(idata);
//            double oval = gd2d_arr[igraph]->GetOvalElm(idata);
//            double oval_serr = gd2d_arr[igraph]->GetOvalSerrElm(idata);
//            xval_vec.push_back(xval);
//            xval_serr_vec.push_back(xval_serr);
//            oval_vec.push_back(oval);
//            oval_serr_vec.push_back(oval_serr);
//        }
//    }
//    GraphDataSerr2d* gd2d_merge = new GraphDataSerr2d;
//    gd2d_merge->Init(xval_vec.size());
//    gd2d_merge->SetXvalArr(xval_vec);
//    gd2d_merge->SetXvalSerrArr(xval_serr_vec);
//    gd2d_merge->SetOvalArr(oval_vec);
//    gd2d_merge->SetOvalSerrArr(oval_serr_vec);
//    return gd2d_merge;
//}
//
//void GraphData2dOpe::GetResValGd2(const GraphData2d* const graph_data,
//                                  const MirFunc* const func,
//                                  const double* const par,
//                                  GraphData2d* const graph_res_out)
//{
//    long ndata = graph_data->GetNdata();
//    double* oval_res = new double[ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        double xval[1];
//        xval[0] = graph_data->GetXvalElm(idata);
//        oval_res[idata] = graph_data->GetOvalElm(idata) - func->Eval(xval, par);
//    }
//    graph_res_out->Init(ndata);
//    graph_res_out->SetXvalArr(ndata, graph_data->GetXvalArr()->GetVal());
//    graph_res_out->SetOvalArr(ndata, oval_res);
//  
//    delete [] oval_res;
//    if(0 < g_flag_verbose){
//        MPrintInfo("done.");
//    }
//}
//
//void GraphData2dOpe::GetResValGd2(const GraphDataSerr2d* const graph_data,
//                                  const MirFunc* const func,
//                                  const double* const par,
//                                  GraphDataSerr2d* const graph_res_out)
//{
//    long ndata = graph_data->GetNdata();
//    double* oval_res = new double[ndata];
//    double* oval_res_serr = new double[ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        double xval[1];
//        xval[0] = graph_data->GetXvalElm(idata);
//        oval_res[idata] = graph_data->GetOvalElm(idata) - func->Eval(xval, par);
//        oval_res_serr[idata] = graph_data->GetOvalSerrElm(idata);
//    }
//    
//    graph_res_out->Init(ndata);
//    graph_res_out->SetXvalArr(ndata, graph_data->GetXvalArr()->GetVal());
//    graph_res_out->SetXvalSerrArr(ndata, graph_data->GetXvalArr()->GetValSerr());
//    graph_res_out->SetOvalArr(ndata, oval_res);
//    graph_res_out->SetOvalSerrArr(ndata, oval_res_serr);
//  
//    delete [] oval_res;
//    delete [] oval_res_serr;
//}
//
//void GraphData2dOpe::GetResValGd2(const GraphDataTerr2d* const graph_data,
//                                  const MirFunc* const func,
//                                  const double* const par,
//                                  GraphDataTerr2d* const graph_res_out)
//{
//    long ndata = graph_data->GetNdata();
//    double* oval_res = new double[ndata];
//    double* oval_res_terr_plus  = new double[ndata];
//    double* oval_res_terr_minus = new double[ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        double xval[1];
//        xval[0] = graph_data->GetXvalElm(idata);
//        oval_res[idata] = graph_data->GetOvalElm(idata) - func->Eval(xval, par);
//        oval_res_terr_plus[idata]  = graph_data->GetOvalTerrPlusElm(idata);
//        oval_res_terr_minus[idata] = graph_data->GetOvalTerrMinusElm(idata);
//    }
//
//    graph_res_out->Init(ndata);
//    graph_res_out->SetXvalArr(ndata, graph_data->GetXvalArr()->GetVal());
//    graph_res_out->SetXvalTerrArr(ndata,
//                                  graph_data->GetXvalArr()->GetValTerrPlus(),
//                                  graph_data->GetXvalArr()->GetValTerrMinus());
//    graph_res_out->SetOvalArr(ndata, graph_data->GetOvalArr()->GetVal());
//    graph_res_out->SetOvalTerrArr(ndata,
//                                  graph_data->GetOvalArr()->GetValTerrPlus(),
//                                  graph_data->GetOvalArr()->GetValTerrMinus());
//    delete [] oval_res;
//    delete [] oval_res_terr_plus;
//    delete [] oval_res_terr_minus;
//}
//
//void GraphData2dOpe::GetResRatioGd2(const GraphDataNerr2d* const graph_data,
//                                    const MirFunc* const func,
//                                    const double* const par,
//                                    GraphDataNerr2d* const graph_res_out)
//{
//    long ndata = graph_data->GetNdata();
//    double* oval_res = new double[ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        double xval[1];
//        xval[0] = graph_data->GetXvalElm(idata);
//        oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
//            func->Eval(xval, par);
//    }
//    graph_res_out->Init(ndata);
//    graph_res_out->SetXvalArr(ndata, graph_data->GetXvalArr()->GetVal());
//    graph_res_out->SetOvalArr(ndata, oval_res);
//  
//    delete [] oval_res;
//}
//
//
//void GraphData2dOpe::GetResRatioGd2(const GraphDataSerr2d* const graph_data,
//                                    const MirFunc* const func,
//                                    const double* const par,
//                                    GraphDataSerr2d* const graph_res_out)
//{
//    long ndata = graph_data->GetNdata();
//    double* oval_res = new double[ndata];
//    double* oval_res_serr = new double[ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        double xval[1];
//        xval[0] = graph_data->GetXvalElm(idata);
//        oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
//            func->Eval(xval, par);
//        oval_res_serr[idata] = fabs(graph_data->GetOvalSerrElm(idata) / func->Eval(xval, par));
//    }
//
//    graph_res_out->Init(ndata);
//    graph_res_out->SetXvalArr(ndata, graph_data->GetXvalArr()->GetVal());
//    graph_res_out->SetXvalSerrArr(ndata, graph_data->GetXvalArr()->GetValSerr());
//    graph_res_out->SetOvalArr(ndata, oval_res);
//    graph_res_out->SetOvalSerrArr(ndata, oval_res_serr);
//
//    delete [] oval_res;
//    delete [] oval_res_serr;
//}
//
//void GraphData2dOpe::GetResRatioGd2(const GraphDataTerr2d* const graph_data,
//                                    const MirFunc* const func,
//                                    const double* const par,
//                                    GraphDataTerr2d* const graph_res_out)
//{
//    long ndata = graph_data->GetNdata();
//    double* oval_res = new double[ndata];
//    double* oval_res_terr_plus  = new double[ndata];
//    double* oval_res_terr_minus = new double[ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        double xval[1];
//        xval[0] = graph_data->GetXvalElm(idata);
//        oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
//            func->Eval(xval, par);
//        oval_res_terr_plus[idata]  = fabs(graph_data->GetOvalTerrPlusElm(idata) / func->Eval(xval, par));
//        oval_res_terr_minus[idata] = -1 * fabs(graph_data->GetOvalTerrMinusElm(idata) / func->Eval(xval, par));
//    }
//
//    graph_res_out->Init(ndata);
//    graph_res_out->SetXvalArr(ndata, graph_data->GetXvalArr()->GetVal());
//    graph_res_out->SetXvalTerrArr(ndata,
//                                  graph_data->GetXvalArr()->GetValTerrPlus(),
//                                  graph_data->GetXvalArr()->GetValTerrMinus());
//    graph_res_out->SetOvalArr(ndata, oval_res);
//    graph_res_out->SetOvalTerrArr(ndata,
//                                  oval_res_terr_plus,
//                                  oval_res_terr_minus);
//    delete [] oval_res;
//    delete [] oval_res_terr_plus;
//    delete [] oval_res_terr_minus;
//}
//
//void GraphData2dOpe::GetResChiGd2(const GraphDataSerr2d* const graph_data,
//                                  const MirFunc* const func,
//                                  const double* const par,
//                                  GraphDataSerr2d* const graph_res_out)
//{
//    long ndata = graph_data->GetNdata();
//    double* oval_res = new double[ndata];
//    double* oval_res_serr = new double[ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        double xval[1];
//        xval[0] = graph_data->GetXvalElm(idata);
//        oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
//            graph_data->GetOvalSerrElm(idata);
//        oval_res_serr[idata] = 1.0;
//    }
//
//    graph_res_out->Init(ndata);
//    graph_res_out->SetXvalArr(ndata, graph_data->GetXvalArr()->GetVal());
//    graph_res_out->SetXvalSerrArr(ndata, graph_data->GetXvalArr()->GetValSerr());
//    graph_res_out->SetOvalArr(ndata, oval_res);
//    graph_res_out->SetOvalSerrArr(ndata, oval_res_serr);
//
//    delete [] oval_res;
//    delete [] oval_res_serr;
//}
// 
//
//void GraphData2dOpe::GetResChiGd2(const GraphDataTerr2d* const graph_data,
//                                  const MirFunc* const func,
//                                  const double* const par,
//                                  GraphDataTerr2d* const graph_res_out)
//{
//    long ndata = graph_data->GetNdata();
//    double* oval_res = new double[ndata];
//    double* oval_res_terr_plus  = new double[ndata];
//    double* oval_res_terr_minus = new double[ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        double xval[1];
//        xval[0] = graph_data->GetXvalElm(idata);
//        if( 0 <= graph_data->GetOvalElm(idata) - func->Eval(xval, par) ){
//            oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
//                (-1 * graph_data->GetOvalTerrMinusElm(idata));
//        } else {
//            oval_res[idata] = (graph_data->GetOvalElm(idata) - func->Eval(xval, par)) /
//                graph_data->GetOvalTerrPlusElm(idata);
//        }
//        oval_res_terr_plus[idata] = 1.0;
//        oval_res_terr_minus[idata] = -1.0;
//    }
//    
//    graph_res_out->Init(ndata);
//    graph_res_out->SetXvalArr(ndata, graph_data->GetXvalArr()->GetVal());
//    graph_res_out->SetXvalTerrArr(ndata,
//                                  graph_data->GetXvalArr()->GetValTerrPlus(),
//                                  graph_data->GetXvalArr()->GetValTerrMinus());
//    graph_res_out->SetOvalArr(ndata, oval_res);
//    graph_res_out->SetOvalTerrArr(ndata,
//                                  oval_res_terr_plus,
//                                  oval_res_terr_minus);
//    delete [] oval_res;
//    delete [] oval_res_terr_plus;
//    delete [] oval_res_terr_minus;
//}

