#include "mir_graph2d_ope.h"

void GraphData2dOpe::GetMotion(const GraphData2d* const gd2d,
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

void GraphData2dOpe::GetSelectGd2dByIntervalCenter(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphDataNerr2d* const graph_out)
{
    vector<double> xval_new;
    vector<double> oval_new;
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata++){
        double xval            = graph_data->GetXvalElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
            if(interval->GetTstartElm(iterm) <= xval &&
               xval <= interval->GetTstopElm(iterm)    ){
                xval_new.push_back(xval);
                oval_new.push_back(oval);
            }
        }
    }
    graph_out->Init(xval_new.size());
    graph_out->SetXvalArr(xval_new);
    graph_out->SetOvalArr(oval_new);
}

void GraphData2dOpe::GetSelectGd2dByIntervalCenter(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphDataSerr2d* const graph_out)
{
    vector<double> xval_new;
    vector<double> xval_serr_new;
    vector<double> oval_new;
    vector<double> oval_serr_new;
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata++){
        double xval      = graph_data->GetXvalElm(idata);
        double xval_serr = graph_data->GetXvalSerrElm(idata);
        double oval      = graph_data->GetOvalElm(idata);
        double oval_serr = graph_data->GetOvalSerrElm(idata);
        for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
            if(interval->GetTstartElm(iterm) <= xval &&
               xval <= interval->GetTstopElm(iterm)    ){
                xval_new.push_back(xval);
                xval_serr_new.push_back(xval_serr);
                oval_new.push_back(oval);
                oval_serr_new.push_back(oval_serr);
            }
        }
    }
    graph_out->Init(xval_new.size());
    graph_out->SetXvalArr(xval_new);
    graph_out->SetXvalSerrArr(xval_serr_new);
    graph_out->SetOvalArr(oval_new);
    graph_out->SetOvalSerrArr(oval_serr_new);
}

void GraphData2dOpe::GetSelectGd2dByIntervalCenter(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphDataTerr2d* const graph_out)
{
    vector<double> xval_new;
    vector<double> xval_terr_plus_new;
    vector<double> xval_terr_minus_new;
    vector<double> oval_new;
    vector<double> oval_terr_plus_new;
    vector<double> oval_terr_minus_new;
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata++){
        double xval            = graph_data->GetXvalElm(idata);
        double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
        double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
        double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
        for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
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
    graph_out->Init(xval_new.size());
    graph_out->SetXvalArr(xval_new);
    graph_out->SetXvalTerrArr(xval_terr_plus_new, xval_terr_minus_new);
    graph_out->SetOvalArr(oval_new);
    graph_out->SetOvalTerrArr(oval_terr_plus_new, oval_terr_minus_new);
}



void GraphData2dOpe::GetSelectGd2dByIntervalExclusive(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphDataNerr2d* const graph_out)
{
    vector<double> xval_new;
    vector<double> oval_new;
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata++){
        double xval            = graph_data->GetXvalElm(idata);
        double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
        double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
            if( interval->GetTstartElm(iterm) <= xval + xval_terr_minus &&
                xval + xval_terr_plus <= interval->GetTstopElm(iterm)     ){
                xval_new.push_back(xval);
                oval_new.push_back(oval);
            }
        }
    }
    graph_out->Init(xval_new.size());
    graph_out->SetXvalArr(xval_new);
    graph_out->SetOvalArr(oval_new);
}

void GraphData2dOpe::GetSelectGd2dByIntervalExclusive(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphDataSerr2d* const graph_out)
{
    vector<double> xval_new;
    vector<double> xval_serr_new;
    vector<double> oval_new;
    vector<double> oval_serr_new;
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata++){
        double xval            = graph_data->GetXvalElm(idata);
        double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
        double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
        double xval_serr       = graph_data->GetXvalSerrElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        double oval_serr       = graph_data->GetOvalSerrElm(idata);
        for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
            if( interval->GetTstartElm(iterm) <= xval + xval_terr_minus &&
                xval + xval_terr_plus <= interval->GetTstopElm(iterm)     ){
                xval_new.push_back(xval);
                xval_serr_new.push_back(xval_serr);
                oval_new.push_back(oval);
                oval_serr_new.push_back(oval_serr);
            }
        }
    }
    graph_out->Init(xval_new.size());
    graph_out->SetXvalArr(xval_new);
    graph_out->SetXvalSerrArr(xval_serr_new);
    graph_out->SetOvalArr(oval_new);
    graph_out->SetOvalSerrArr(oval_serr_new);
}

void GraphData2dOpe::GetSelectGd2dByIntervalExclusive(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphDataTerr2d* const graph_out)
{
    vector<double> xval_new;
    vector<double> xval_terr_plus_new;
    vector<double> xval_terr_minus_new;
    vector<double> oval_new;
    vector<double> oval_terr_plus_new;
    vector<double> oval_terr_minus_new;
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata++){
        double xval            = graph_data->GetXvalElm(idata);
        double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
        double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
        double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
        for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
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
    graph_out->Init(xval_new.size());
    graph_out->SetXvalArr(xval_new);
    graph_out->SetXvalTerrArr(xval_terr_plus_new, xval_terr_minus_new);
    graph_out->SetOvalArr(oval_new);
    graph_out->SetOvalTerrArr(oval_terr_plus_new, oval_terr_minus_new);
}

void GraphData2dOpe::GetSelectGd2dByIntervalVarbinwidth(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphDataTerr2d* const graph_out)
{
    vector<double> xval_new;
    vector<double> xval_terr_plus_new;
    vector<double> xval_terr_minus_new;
    vector<double> oval_new;
    vector<double> oval_terr_plus_new;
    vector<double> oval_terr_minus_new;
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata++){
        double xval            = graph_data->GetXvalElm(idata);
        double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
        double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
        double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
        for(int iterm = 0; iterm < interval->GetNterm(); iterm ++){
            if(interval->GetTstartElm(iterm) <= xval &&
               xval <= interval->GetTstopElm(iterm)    ){
                xval_new.push_back(xval);
                oval_new.push_back(oval);
                oval_terr_plus_new.push_back(oval_terr_plus);
                oval_terr_minus_new.push_back(oval_terr_minus);

                double xval_terr_minus_this = xval_terr_minus;
                if(xval + xval_terr_minus < interval->GetTstartElm(iterm)){
                    xval_terr_minus_this = -1 * (xval - interval->GetTstartElm(iterm));
                }
                xval_terr_minus_new.push_back(xval_terr_minus_this);

                double xval_terr_plus_this = xval_terr_plus;
                if(interval->GetTstopElm(iterm) < xval + xval_terr_plus){
                    xval_terr_plus_this = interval->GetTstopElm(iterm) - xval;
                }
                xval_terr_plus_new.push_back(xval_terr_plus_this);                
            }
        }
    }
    graph_out->Init(xval_new.size());
    graph_out->SetXvalArr(xval_new);
    graph_out->SetXvalTerrArr(xval_terr_plus_new, xval_terr_minus_new);
    graph_out->SetOvalArr(oval_new);
    graph_out->SetOvalTerrArr(oval_terr_plus_new, oval_terr_minus_new);
}


void GraphData2dOpe::GenSelectGd2dArrByIntervalCenterNerr(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphData2d*** const gd2d_arr_ptr)
    
{
    long nterm = interval->GetNterm();
    GraphData2d** gd2d_arr = new GraphData2d* [nterm];
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm] = new GraphDataTerr2d;
    }
    vector<double>* xval_vec_arr = new vector<double> [nterm];
    vector<double>* oval_vec_arr = new vector<double> [nterm];
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata ++){
        double xval            = graph_data->GetXvalElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        for(long iterm = 0; iterm < nterm; iterm ++){
            if(interval->GetTstartElm(iterm) <= xval &&
               xval <= interval->GetTstopElm(iterm)    ){
                xval_vec_arr[iterm].push_back(xval);
                oval_vec_arr[iterm].push_back(oval);
            }
        }
    }
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm]->Init(xval_vec_arr[iterm].size());
        gd2d_arr[iterm]->SetXvalArr(xval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalArr(oval_vec_arr[iterm]);
    }
    delete [] xval_vec_arr;
    delete [] oval_vec_arr;
    *gd2d_arr_ptr = gd2d_arr;
}

void GraphData2dOpe::GenSelectGd2dArrByIntervalCenterSerr(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphData2d*** const gd2d_arr_ptr)
    
{
    long nterm = interval->GetNterm();
    GraphData2d** gd2d_arr = new GraphData2d* [nterm];
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm] = new GraphDataTerr2d;
    }
    vector<double>* xval_vec_arr = new vector<double> [nterm];
    vector<double>* xval_serr_vec_arr = new vector<double> [nterm];
    vector<double>* oval_vec_arr = new vector<double> [nterm];
    vector<double>* oval_serr_vec_arr = new vector<double> [nterm];
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata ++){
        double xval      = graph_data->GetXvalElm(idata);
        double xval_serr = graph_data->GetXvalSerrElm(idata);
        double oval      = graph_data->GetOvalElm(idata);
        double oval_serr = graph_data->GetOvalSerrElm(idata);
        for(long iterm = 0; iterm < nterm; iterm ++){
            if(interval->GetTstartElm(iterm) <= xval &&
               xval <= interval->GetTstopElm(iterm)    ){
                xval_vec_arr[iterm].push_back(xval);
                xval_serr_vec_arr[iterm].push_back(xval_serr);
                oval_vec_arr[iterm].push_back(oval);
                oval_serr_vec_arr[iterm].push_back(oval_serr);
            }
        }
    }
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm]->Init(xval_vec_arr[iterm].size());
        gd2d_arr[iterm]->SetXvalArr(xval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetXvalSerrArr(xval_serr_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalArr(oval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalSerrArr(oval_serr_vec_arr[iterm]);
    }
    delete [] xval_vec_arr;
    delete [] xval_serr_vec_arr;
    delete [] oval_vec_arr;
    delete [] oval_serr_vec_arr;
    *gd2d_arr_ptr = gd2d_arr;
}

void GraphData2dOpe::GenSelectGd2dArrByIntervalCenterTerr(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphData2d*** const gd2d_arr_ptr)
    
{
    long nterm = interval->GetNterm();
    GraphData2d** gd2d_arr = new GraphData2d* [nterm];
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm] = new GraphDataTerr2d;
    }
    vector<double>* xval_vec_arr = new vector<double> [nterm];
    vector<double>* xval_terr_plus_vec_arr = new vector<double> [nterm];
    vector<double>* xval_terr_minus_vec_arr = new vector<double> [nterm];    
    vector<double>* oval_vec_arr = new vector<double> [nterm];
    vector<double>* oval_terr_plus_vec_arr = new vector<double> [nterm];
    vector<double>* oval_terr_minus_vec_arr = new vector<double> [nterm];
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata ++){
        double xval            = graph_data->GetXvalElm(idata);
        double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
        double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
        double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
        for(long iterm = 0; iterm < nterm; iterm ++){
            if(interval->GetTstartElm(iterm) <= xval &&
               xval <= interval->GetTstopElm(iterm)    ){
                xval_vec_arr[iterm].push_back(xval);
                xval_terr_minus_vec_arr[iterm].push_back(xval_terr_minus);
                xval_terr_plus_vec_arr[iterm].push_back(xval_terr_plus);
                oval_vec_arr[iterm].push_back(oval);
                oval_terr_plus_vec_arr[iterm].push_back(oval_terr_plus);
                oval_terr_minus_vec_arr[iterm].push_back(oval_terr_minus);
            }
        }
    }
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm]->Init(xval_vec_arr[iterm].size());
        gd2d_arr[iterm]->SetXvalArr(xval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetXvalTerrArr(xval_terr_plus_vec_arr[iterm],
                                        xval_terr_minus_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalArr(oval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalTerrArr(oval_terr_plus_vec_arr[iterm],
                                        oval_terr_minus_vec_arr[iterm]);
        
    }
    delete [] xval_vec_arr;
    delete [] xval_terr_plus_vec_arr;
    delete [] xval_terr_minus_vec_arr;    
    delete [] oval_vec_arr;
    delete [] oval_terr_plus_vec_arr;
    delete [] oval_terr_minus_vec_arr;
    *gd2d_arr_ptr = gd2d_arr;
}

void GraphData2dOpe::GenSelectGd2dArrByIntervalExclusiveNerr(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphData2d*** const gd2d_arr_ptr)
    
{
    long nterm = interval->GetNterm();
    GraphData2d** gd2d_arr = new GraphData2d* [nterm];
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm] = new GraphDataNerr2d;
    }
    vector<double>* xval_vec_arr = new vector<double> [nterm];
    vector<double>* oval_vec_arr = new vector<double> [nterm];
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata ++){
        double xval            = graph_data->GetXvalElm(idata);
        double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
        double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        for(long iterm = 0; iterm < nterm; iterm ++){
            if(interval->GetTstartElm(iterm) <= xval + xval_terr_minus &&
               xval + xval_terr_plus <= interval->GetTstopElm(iterm)    ){
                xval_vec_arr[iterm].push_back(xval);
                oval_vec_arr[iterm].push_back(oval);
            }
        }
    }
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm]->Init(xval_vec_arr[iterm].size());
        gd2d_arr[iterm]->SetXvalArr(xval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalArr(oval_vec_arr[iterm]);
    }
    delete [] xval_vec_arr;
    delete [] oval_vec_arr;
    *gd2d_arr_ptr = gd2d_arr;
}


void GraphData2dOpe::GenSelectGd2dArrByIntervalExclusiveSerr(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphData2d*** const gd2d_arr_ptr)
    
{
    long nterm = interval->GetNterm();
    GraphData2d** gd2d_arr = new GraphData2d* [nterm];
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm] = new GraphDataSerr2d;
    }
    vector<double>* xval_vec_arr = new vector<double> [nterm];
    vector<double>* xval_serr_vec_arr = new vector<double> [nterm];    
    vector<double>* oval_vec_arr = new vector<double> [nterm];
    vector<double>* oval_serr_vec_arr = new vector<double> [nterm];
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata ++){
        double xval            = graph_data->GetXvalElm(idata);
        double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
        double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
        double xval_serr       = graph_data->GetXvalSerrElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        double oval_serr       = graph_data->GetOvalSerrElm(idata);
        for(long iterm = 0; iterm < nterm; iterm ++){
            if(interval->GetTstartElm(iterm) <= xval + xval_terr_minus &&
               xval + xval_terr_plus <= interval->GetTstopElm(iterm)    ){
                xval_vec_arr[iterm].push_back(xval);
                xval_serr_vec_arr[iterm].push_back(xval_serr);
                oval_vec_arr[iterm].push_back(oval);
                oval_serr_vec_arr[iterm].push_back(oval_serr);
            }
        }
    }
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm]->Init(xval_vec_arr[iterm].size());
        gd2d_arr[iterm]->SetXvalArr(xval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetXvalSerrArr(xval_serr_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalArr(oval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalSerrArr(oval_serr_vec_arr[iterm]);
    }
    delete [] xval_vec_arr;
    delete [] xval_serr_vec_arr;
    delete [] oval_vec_arr;
    delete [] oval_serr_vec_arr;
    *gd2d_arr_ptr = gd2d_arr;
}

void GraphData2dOpe::GenSelectGd2dArrByIntervalExclusiveTerr(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphData2d*** const gd2d_arr_ptr)
    
{
    long nterm = interval->GetNterm();
    GraphData2d** gd2d_arr = new GraphData2d* [nterm];
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm] = new GraphDataTerr2d;
    }
    vector<double>* xval_vec_arr = new vector<double> [nterm];
    vector<double>* xval_terr_plus_vec_arr = new vector<double> [nterm];
    vector<double>* xval_terr_minus_vec_arr = new vector<double> [nterm];    
    vector<double>* oval_vec_arr = new vector<double> [nterm];
    vector<double>* oval_terr_plus_vec_arr = new vector<double> [nterm];
    vector<double>* oval_terr_minus_vec_arr = new vector<double> [nterm];
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata ++){
        double xval            = graph_data->GetXvalElm(idata);
        double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
        double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
        double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
        for(long iterm = 0; iterm < nterm; iterm ++){
            if(interval->GetTstartElm(iterm) <= xval + xval_terr_minus &&
               xval + xval_terr_plus <= interval->GetTstopElm(iterm)    ){
                xval_vec_arr[iterm].push_back(xval);
                xval_terr_minus_vec_arr[iterm].push_back(xval_terr_minus);
                xval_terr_plus_vec_arr[iterm].push_back(xval_terr_plus);
                oval_vec_arr[iterm].push_back(oval);
                oval_terr_plus_vec_arr[iterm].push_back(oval_terr_plus);
                oval_terr_minus_vec_arr[iterm].push_back(oval_terr_minus);
            }
        }
    }
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm]->Init(xval_vec_arr[iterm].size());
        gd2d_arr[iterm]->SetXvalArr(xval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetXvalTerrArr(xval_terr_plus_vec_arr[iterm],
                                        xval_terr_minus_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalArr(oval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalTerrArr(oval_terr_plus_vec_arr[iterm],
                                        oval_terr_minus_vec_arr[iterm]);
        
    }
    delete [] xval_vec_arr;
    delete [] xval_terr_plus_vec_arr;
    delete [] xval_terr_minus_vec_arr;    
    delete [] oval_vec_arr;
    delete [] oval_terr_plus_vec_arr;
    delete [] oval_terr_minus_vec_arr;
    *gd2d_arr_ptr = gd2d_arr;
}



void GraphData2dOpe::GenSelectGd2dArrByIntervalVarbinwidthTerr(
    const GraphData2d* const graph_data,
    const Interval* const interval,
    GraphData2d*** const gd2d_arr_ptr)
    
{
    long nterm = interval->GetNterm();
    GraphData2d** gd2d_arr = new GraphData2d* [nterm];
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm] = new GraphDataTerr2d;
    }
    vector<double>* xval_vec_arr = new vector<double> [nterm];
    vector<double>* xval_terr_plus_vec_arr = new vector<double> [nterm];
    vector<double>* xval_terr_minus_vec_arr = new vector<double> [nterm];    
    vector<double>* oval_vec_arr = new vector<double> [nterm];
    vector<double>* oval_terr_plus_vec_arr = new vector<double> [nterm];
    vector<double>* oval_terr_minus_vec_arr = new vector<double> [nterm];
    long ndata = graph_data->GetNdata();
    for(long idata = 0; idata < ndata; idata ++){
        double xval            = graph_data->GetXvalElm(idata);
        double xval_terr_plus  = graph_data->GetXvalTerrPlusElm(idata);
        double xval_terr_minus = graph_data->GetXvalTerrMinusElm(idata);
        double oval            = graph_data->GetOvalElm(idata);
        double oval_terr_plus  = graph_data->GetOvalTerrPlusElm(idata);
        double oval_terr_minus = graph_data->GetOvalTerrMinusElm(idata);
        for(long iterm = 0; iterm < nterm; iterm ++){
            if(interval->GetTstartElm(iterm) <= xval &&
               xval <= interval->GetTstopElm(iterm)    ){
                xval_vec_arr[iterm].push_back(xval);
                oval_vec_arr[iterm].push_back(oval);
                oval_terr_plus_vec_arr[iterm].push_back(oval_terr_plus);
                oval_terr_minus_vec_arr[iterm].push_back(oval_terr_minus);

                double xval_terr_minus_this = xval_terr_minus;
                if(xval + xval_terr_minus < interval->GetTstartElm(iterm)){
                    xval_terr_minus_this = -1 * (xval - interval->GetTstartElm(iterm));
                }
                xval_terr_minus_vec_arr[iterm].push_back(xval_terr_minus_this);

                double xval_terr_plus_this = xval_terr_plus;
                if(interval->GetTstopElm(iterm) < xval + xval_terr_plus){
                    xval_terr_plus_this = interval->GetTstopElm(iterm) - xval;
                }
                xval_terr_plus_vec_arr[iterm].push_back(xval_terr_plus_this);
            }
        }
    }
    for(long iterm = 0; iterm < nterm; iterm ++){
        gd2d_arr[iterm]->Init(xval_vec_arr[iterm].size());
        gd2d_arr[iterm]->SetXvalArr(xval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetXvalTerrArr(xval_terr_plus_vec_arr[iterm],
                                        xval_terr_minus_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalArr(oval_vec_arr[iterm]);
        gd2d_arr[iterm]->SetOvalTerrArr(oval_terr_plus_vec_arr[iterm],
                                        oval_terr_minus_vec_arr[iterm]);
        
    }
    delete [] xval_vec_arr;
    delete [] xval_terr_plus_vec_arr;
    delete [] xval_terr_minus_vec_arr;    
    delete [] oval_vec_arr;
    delete [] oval_terr_plus_vec_arr;
    delete [] oval_terr_minus_vec_arr;
    *gd2d_arr_ptr = gd2d_arr;
}


void GraphData2dOpe::GetGd2dByMergeGd2dArr(long ngraph,
                                           const GraphData2d* const* const gd2d_arr,
                                           GraphDataNerr2d* const gd2d_out)
{
    vector<double> xval_vec;
    vector<double> oval_vec;
    for(long igraph = 0; igraph < ngraph; igraph ++){
        for(long idata = 0; idata < gd2d_arr[igraph]->GetNdata(); idata ++){
            double xval = gd2d_arr[igraph]->GetXvalElm(idata);
            double oval = gd2d_arr[igraph]->GetOvalElm(idata);
            xval_vec.push_back(xval);
            oval_vec.push_back(oval);
        }
    }
    gd2d_out->Init(xval_vec.size());
    gd2d_out->SetXvalArr(xval_vec);
    gd2d_out->SetOvalArr(oval_vec);
}

void GraphData2dOpe::GetGd2dByMergeGd2dArr(long ngraph,
                                           const GraphData2d* const* const gd2d_arr,
                                           GraphDataSerr2d* const gd2d_out)
{
    vector<double> xval_vec;
    vector<double> xval_serr_vec;
    vector<double> oval_vec;
    vector<double> oval_serr_vec;
    for(long igraph = 0; igraph < ngraph; igraph ++){
        for(long idata = 0; idata < gd2d_arr[igraph]->GetNdata(); idata ++){
            double xval      = gd2d_arr[igraph]->GetXvalElm(idata);
            double xval_serr = gd2d_arr[igraph]->GetXvalSerrElm(idata);
            double oval      = gd2d_arr[igraph]->GetOvalElm(idata);
            double oval_serr = gd2d_arr[igraph]->GetOvalSerrElm(idata);
            xval_vec.push_back(xval);
            xval_serr_vec.push_back(xval_serr);
            oval_vec.push_back(oval);
            oval_serr_vec.push_back(oval_serr);
        }
    }
    gd2d_out->Init(xval_vec.size());
    gd2d_out->SetXvalArr(xval_vec);
    gd2d_out->SetXvalSerrArr(xval_serr_vec);
    gd2d_out->SetOvalArr(oval_vec);
    gd2d_out->SetOvalSerrArr(oval_serr_vec);
}


void GraphData2dOpe::GetGd2dByMergeGd2dArr(long ngraph,
                                           const GraphData2d* const* const gd2d_arr,
                                           GraphDataTerr2d* const gd2d_out)
{
    vector<double> xval_vec;
    vector<double> xval_terr_plus_vec;
    vector<double> xval_terr_minus_vec;    
    vector<double> oval_vec;
    vector<double> oval_terr_plus_vec;
    vector<double> oval_terr_minus_vec;
    for(long igraph = 0; igraph < ngraph; igraph ++){
        for(long idata = 0; idata < gd2d_arr[igraph]->GetNdata(); idata ++){
            double xval = gd2d_arr[igraph]->GetXvalElm(idata);
            double xval_terr_plus  = gd2d_arr[igraph]->GetXvalTerrPlusElm(idata);
            double xval_terr_minus = gd2d_arr[igraph]->GetXvalTerrMinusElm(idata);
            double oval = gd2d_arr[igraph]->GetOvalElm(idata);
            double oval_terr_plus = gd2d_arr[igraph]->GetOvalTerrPlusElm(idata);
            double oval_terr_minus = gd2d_arr[igraph]->GetOvalTerrMinusElm(idata);
            xval_vec.push_back(xval);
            xval_terr_plus_vec.push_back(xval_terr_plus);
            xval_terr_minus_vec.push_back(xval_terr_minus);            
            oval_vec.push_back(oval);
            oval_terr_plus_vec.push_back(oval_terr_plus);
            oval_terr_minus_vec.push_back(oval_terr_minus);
        }
    }
    gd2d_out->Init(xval_vec.size());
    gd2d_out->SetXvalArr(xval_vec);
    gd2d_out->SetXvalTerrArr(xval_terr_plus_vec, xval_terr_minus_vec);
    gd2d_out->SetOvalArr(oval_vec);
    gd2d_out->SetOvalTerrArr(oval_terr_plus_vec, oval_terr_minus_vec);
}

void GraphData2dOpe::GetResValGd2d(const GraphData2d* const data,
                                   const MirFunc* const func,
                                   const double* const par,
                                   GraphDataNerr2d* const out)
{
    long ndata = data->GetNdata();
    double* oval_res = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = data->GetXvalElm(idata);
        oval_res[idata] = data->GetOvalElm(idata) - func->Eval(xval, par);
    }
    out->Init(ndata);
    out->SetXvalArr(ndata, data->GetXvalArr()->GetVal());
    out->SetOvalArr(ndata, oval_res);
  
    delete [] oval_res;
}

void GraphData2dOpe::GetResValGd2d(const GraphData2d* const data,
                                   const MirFunc* const func,
                                   const double* const par,
                                   GraphDataSerr2d* const out)
{
    long ndata = data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_serr = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = data->GetXvalElm(idata);
        oval_res[idata] = data->GetOvalElm(idata) - func->Eval(xval, par);
        oval_res_serr[idata] = data->GetOvalSerrElm(idata);
    }
    out->Init(ndata);
    out->SetXvalArr(ndata, data->GetXvalArr()->GetVal());
    out->SetXvalSerrArr(ndata, data->GetXvalArr()->GetValSerr());
    out->SetOvalArr(ndata, oval_res);
    out->SetOvalSerrArr(ndata, oval_res_serr);
  
    delete [] oval_res;
    delete [] oval_res_serr;
}

void GraphData2dOpe::GetResValGd2d(const GraphData2d* const data,
                                   const MirFunc* const func,
                                   const double* const par,
                                   GraphDataTerr2d* const out)
{
    long ndata = data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_terr_plus  = new double[ndata];
    double* oval_res_terr_minus = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = data->GetXvalElm(idata);
        oval_res[idata] = data->GetOvalElm(idata) - func->Eval(xval, par);
        oval_res_terr_plus[idata]  = data->GetOvalTerrPlusElm(idata);
        oval_res_terr_minus[idata] = data->GetOvalTerrMinusElm(idata);
    }

    out->Init(ndata);
    out->SetXvalArr(ndata, data->GetXvalArr()->GetVal());
    out->SetXvalTerrArr(ndata,
                        data->GetXvalArr()->GetValTerrPlus(),
                        data->GetXvalArr()->GetValTerrMinus());
    out->SetOvalArr(ndata, data->GetOvalArr()->GetVal());
    out->SetOvalTerrArr(ndata,
                        data->GetOvalArr()->GetValTerrPlus(),
                        data->GetOvalArr()->GetValTerrMinus());
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;
}


void GraphData2dOpe::GetResRatioGd2d(const GraphData2d* const data,
                                     const MirFunc* const func,
                                     const double* const par,
                                     GraphDataNerr2d* const out)
{
    long ndata = data->GetNdata();
    double* oval_res = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = data->GetXvalElm(idata);
        oval_res[idata] = (data->GetOvalElm(idata) - func->Eval(xval, par)) /
            func->Eval(xval, par);
    }
    out->Init(ndata);
    out->SetXvalArr(ndata, data->GetXvalArr()->GetVal());
    out->SetOvalArr(ndata, oval_res);
  
    delete [] oval_res;
}


void GraphData2dOpe::GetResRatioGd2d(const GraphData2d* const data,
                                     const MirFunc* const func,
                                     const double* const par,
                                     GraphDataSerr2d* const out)
{
    long ndata = data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_serr = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = data->GetXvalElm(idata);
        oval_res[idata] = (data->GetOvalElm(idata) - func->Eval(xval, par)) /
            func->Eval(xval, par);
        oval_res_serr[idata] = fabs(data->GetOvalSerrElm(idata) / func->Eval(xval, par));
    }

    out->Init(ndata);
    out->SetXvalArr(ndata, data->GetXvalArr()->GetVal());
    out->SetXvalSerrArr(ndata, data->GetXvalArr()->GetValSerr());
    out->SetOvalArr(ndata, oval_res);
    out->SetOvalSerrArr(ndata, oval_res_serr);

    delete [] oval_res;
    delete [] oval_res_serr;
}

void GraphData2dOpe::GetResRatioGd2d(const GraphData2d* const data,
                                     const MirFunc* const func,
                                     const double* const par,
                                     GraphDataTerr2d* const out)
{
    long ndata = data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_terr_plus  = new double[ndata];
    double* oval_res_terr_minus = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = data->GetXvalElm(idata);
        oval_res[idata] = (data->GetOvalElm(idata) - func->Eval(xval, par)) /
            func->Eval(xval, par);
        oval_res_terr_plus[idata]  =
            fabs(data->GetOvalTerrPlusElm(idata) / func->Eval(xval, par));
        oval_res_terr_minus[idata] =
            -1 * fabs(data->GetOvalTerrMinusElm(idata) / func->Eval(xval, par));
    }

    out->Init(ndata);
    out->SetXvalArr(ndata, data->GetXvalArr()->GetVal());
    out->SetXvalTerrArr(ndata,
                        data->GetXvalArr()->GetValTerrPlus(),
                        data->GetXvalArr()->GetValTerrMinus());
    out->SetOvalArr(ndata, oval_res);
    out->SetOvalTerrArr(ndata,
                        oval_res_terr_plus,
                        oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;
}


void GraphData2dOpe::GetResChiGd2d(const GraphData2d* const data,
                                   const MirFunc* const func,
                                   const double* const par,
                                   GraphDataSerr2d* const out)
{
    long ndata = data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_serr = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = data->GetXvalElm(idata);
        oval_res[idata] = (data->GetOvalElm(idata) - func->Eval(xval, par)) /
            data->GetOvalSerrElm(idata);
        oval_res_serr[idata] = 1.0;
    }
    out->Init(ndata);
    out->SetXvalArr(ndata, data->GetXvalArr()->GetVal());
    out->SetXvalSerrArr(ndata, data->GetXvalArr()->GetValSerr());
    out->SetOvalArr(ndata, oval_res);
    out->SetOvalSerrArr(ndata, oval_res_serr);

    delete [] oval_res;
    delete [] oval_res_serr;
}
 

void GraphData2dOpe::GetResChiGd2d(const GraphData2d* const data,
                                   const MirFunc* const func,
                                   const double* const par,
                                   GraphDataTerr2d* const out)
{
    long ndata = data->GetNdata();
    double* oval_res = new double[ndata];
    double* oval_res_terr_plus  = new double[ndata];
    double* oval_res_terr_minus = new double[ndata];
    for(long idata = 0; idata < ndata; idata++){
        double xval[1];
        xval[0] = data->GetXvalElm(idata);
        if( 0 <= data->GetOvalElm(idata) - func->Eval(xval, par) ){
            oval_res[idata] = (data->GetOvalElm(idata) - func->Eval(xval, par)) /
                (-1 * data->GetOvalTerrMinusElm(idata));
        } else {
            oval_res[idata] = (data->GetOvalElm(idata) - func->Eval(xval, par)) /
                data->GetOvalTerrPlusElm(idata);
        }
        oval_res_terr_plus[idata] = 1.0;
        oval_res_terr_minus[idata] = -1.0;
    }
    
    out->Init(ndata);
    out->SetXvalArr(ndata, data->GetXvalArr()->GetVal());
    out->SetXvalTerrArr(ndata,
                        data->GetXvalArr()->GetValTerrPlus(),
                        data->GetXvalArr()->GetValTerrMinus());
    out->SetOvalArr(ndata, oval_res);
    out->SetOvalTerrArr(ndata,
                        oval_res_terr_plus,
                        oval_res_terr_minus);
    delete [] oval_res;
    delete [] oval_res_terr_plus;
    delete [] oval_res_terr_minus;
}


double GraphData2dOpe::GetIntegral(const GraphData2d* const gd2d,
                                   double xval_lo, double xval_up)
{
    // assert before calculation
    assert( 2 <= gd2d->GetNdata() );
    assert( 1 == gd2d->GetFlagXvalSorted() );
    
    double ans = 0.0;
    if(xval_lo < xval_up){
        ans = GetIntegralPlus(gd2d, xval_lo, xval_up);
    } else if (xval_lo > xval_up){
        ans = -1 * GetIntegralPlus(gd2d, xval_up, xval_lo);
    } else {
        ans = 0.0;
    }
    return ans;
}

double GraphData2dOpe::GetIntegralPlus(const GraphData2d* const gd2d,
                                       double xval_lo, double xval_up)
{
    // assert before calculation
    assert( 2 <= gd2d->GetNdata() );
    assert( 1 == gd2d->GetFlagXvalSorted() );
    assert( xval_lo <= xval_up);
    assert( gd2d->GetXvalElm(0) <= xval_lo );
    assert( xval_up <= gd2d->GetXvalElm( gd2d->GetNdata() - 1) );
    
    double oval_lo = gd2d->GetOvalIntPolLin(xval_lo);
    double oval_up = gd2d->GetOvalIntPolLin(xval_up);

    Interval* interval = new Interval;
    interval->InitSet(xval_lo, xval_up);
    GraphDataNerr2d* gd2d_sel = new GraphDataNerr2d;
    GetSelectGd2dByIntervalCenter(gd2d,
                                  interval,
                                  gd2d_sel);
    // add two points
    vector<double> vec_xval;
    vector<double> vec_oval;
    vec_xval.push_back(xval_lo);
    vec_oval.push_back(oval_lo);
    for(int idata = 0; idata < gd2d_sel->GetNdata(); idata++){
        vec_xval.push_back(gd2d_sel->GetXvalElm(idata));
        vec_oval.push_back(gd2d_sel->GetOvalElm(idata));
    }
    vec_xval.push_back(xval_up);
    vec_oval.push_back(oval_up);
    GraphDataNerr2d* gd2d_new = new GraphDataNerr2d;
    gd2d_new->Init(vec_xval.size());
    gd2d_new->SetXvalArr(vec_xval);
    gd2d_new->SetOvalArr(vec_oval);
    gd2d_new->Sort();
    double ans = GetIntegralByTrapezoidApprox(gd2d_new, 0, gd2d_new->GetNdata() - 1);
    delete interval;
    delete gd2d_sel;
    delete gd2d_new;
    return ans;
}


double GraphData2dOpe::GetIntegralByTrapezoidApprox(const GraphData2d* const gd2d,
                                                    long idata_st, long idata_ed)
{
    // assert before calculation
    assert( 2 <= gd2d->GetNdata() );
    assert( 0 <= idata_st );
    assert( idata_ed <= gd2d->GetNdata() - 1 );
    assert( idata_st <= idata_ed );
    assert( 1 == gd2d->GetFlagXvalSorted() );

    double ans = 0.0;
    for(long idata = idata_st; idata < idata_ed; idata ++){
        ans += ( gd2d->GetOvalElm(idata) + gd2d->GetOvalElm(idata + 1) ) *
            ( gd2d->GetXvalElm(idata + 1) - gd2d->GetXvalElm(idata) ) / 2.0;
    }
    return ans;
}

GraphDataSerr2d* const GraphData2dOpe::GenGd2dBinBySigVar(const GraphData2d* const gd2d,
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

        double* oval_arr_pre = MiBase::GenArray(oval_vec_pre);
        double* oval_serr_arr_pre = MiBase::GenArray(oval_serr_vec_pre);
        double chi2_pre = 0.0;
        long dof_pre = 0;
        if(1 == oval_vec_pre.size()){
            chi2_pre = 0.0;
            dof_pre = 0;
        } else {
            double chi2_red_pre = 0.0;
            double prob_pre = 0.0;
            double wmean = 0.0;
            double wmean_err = 0.0;
            long nsel = 0;
            int* mask_sel_arr = NULL;  
            int ret = MirMath::GetChi2byConst(oval_vec_pre.size(),
                                              oval_arr_pre,
                                              oval_serr_arr_pre,
                                              &wmean,
                                              &wmean_err,
                                              &nsel,
                                              &mask_sel_arr,
                                              &chi2_pre,
                                              &dof_pre,
                                              &chi2_red_pre,
                                              &prob_pre);
            if(kRetNormal != ret){
                printf("warning: ret != %d\n", kRetNormal);
            }
            
        }
        if(2 > oval_vec.size()){
            MPrintErr("something is wrong.\n");
            abort();
        }
        double* oval_arr = MiBase::GenArray(oval_vec);
        double* oval_serr_arr = MiBase::GenArray(oval_serr_vec);
        double wmean = 0.0;
        double wmean_err = 0.0;
        long nsel = 0;
        int* mask_sel_arr = NULL;  
        double chi2 = 0.0;
        long dof = 0;
        double chi2_red = 0.0;
        double prob = 0.0;
        int ret = MirMath::GetChi2byConst(oval_vec.size(),
                                          oval_arr,
                                          oval_serr_arr,
                                          &wmean,
                                          &wmean_err,
                                          &nsel,
                                          &mask_sel_arr,
                                          &chi2,
                                          &dof,
                                          &chi2_red,
                                          &prob);
        if(kRetNormal != ret){
            printf("warning: ret != %d\n", kRetNormal);
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
            GetPoint2dSerrByBinning(xval_vec_pre,
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
    GetPoint2dSerrByBinning(xval_vec_pre,
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
    gd2d_binned->Init(xval_binned_vec.size());
    gd2d_binned->SetXvalArr(xval_binned_vec);
    gd2d_binned->SetXvalSerrArr(xval_serr_binned_vec);
    gd2d_binned->SetOvalArr(oval_binned_vec);
    gd2d_binned->SetOvalSerrArr(oval_serr_binned_vec);

    return gd2d_binned;
}


GraphDataSerr2d* const GraphData2dOpe::GenGd2dBinBySigDet(const GraphData2d* const gd2d,
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
                    GetPoint2dSerrByBinning(xval_vec,
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

        double* oval_arr = MiBase::GenArray(oval_vec);
        double* oval_serr_arr = MiBase::GenArray(oval_serr_vec);
        double wmean = 0.0;
        double wmean_serr = 0.0;
        long nsel = 0;
        int* mask_sel_arr = NULL;
        MirMath::GetWMean(oval_vec.size(),
                          oval_arr,
                          oval_serr_arr,
                          &wmean, &wmean_serr,
                          &nsel, &mask_sel_arr);
        delete [] oval_arr;
        delete [] oval_serr_arr;
        delete [] mask_sel_arr;

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
            GetPoint2dSerrByBinning(xval_vec,
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
        GetPoint2dSerrByBinning(xval_vec,
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
    gd2d_binned->Init(xval_binned_vec.size());
    gd2d_binned->SetXvalArr(xval_binned_vec);
    gd2d_binned->SetXvalSerrArr(xval_serr_binned_vec);
    gd2d_binned->SetOvalArr(oval_binned_vec);
    gd2d_binned->SetOvalSerrArr(oval_serr_binned_vec);

    return gd2d_binned;
}


void GraphData2dOpe::GetPoint2dSerrByBinning(long narr,
                                             const double* const xval_arr,
                                             const double* const xval_serr_arr,
                                             const double* const oval_arr,
                                             const double* const oval_serr_arr,
                                             double* const xval_bin_center_ptr,
                                             double* const xval_bin_half_width_ptr,
                                             double* const wmean_ptr,
                                             double* const wmean_err_ptr)
{
    double wmean = 0.0;
    double wmean_err = 0.0;
    long nsel = 0;
    int* mask_sel_arr = NULL;
    MirMath::GetWMean(narr, oval_arr, oval_serr_arr,
                      &wmean, &wmean_err,
                      &nsel, &mask_sel_arr);

    double* xval_serr_min_arr = new double [narr];
    double* xval_serr_max_arr = new double [narr];
    for(long iarr = 0; iarr < narr; iarr++){
        xval_serr_min_arr[iarr] = xval_arr[iarr] - xval_serr_arr[iarr];
        xval_serr_max_arr[iarr] = xval_arr[iarr] + xval_serr_arr[iarr];
    }
    long index_min = MirMath::GetLocMin(narr, xval_serr_min_arr);
    long index_max = MirMath::GetLocMax(narr, xval_serr_min_arr);
            
    double xval_lo = xval_serr_min_arr[index_min];
    double xval_up = xval_serr_max_arr[index_max];
    double xval_bin_center     = (xval_lo + xval_up) / 2.;
    double xval_bin_half_width = (xval_up - xval_lo) / 2.;

    *xval_bin_center_ptr = xval_bin_center;
    *xval_bin_half_width_ptr = xval_bin_half_width;
    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
}

void GraphData2dOpe::GetPoint2dSerrByBinning(vector<double> xval_vec,
                                             vector<double> xval_serr_vec,
                                             vector<double> oval_vec,
                                             vector<double> oval_serr_vec,
                                             double* const xval_bin_center_ptr,
                                             double* const xval_bin_half_width_ptr,
                                             double* const wmean_ptr,
                                             double* const wmean_err_ptr)
{
    long narr_xval = 0;
    long narr_xval_serr = 0;
    long narr_oval = 0;
    long narr_oval_serr = 0;        
    double* xval_arr = NULL;
    double* xval_serr_arr = NULL;
    double* oval_arr = NULL;
    double* oval_serr_arr = NULL;
    MiBase::GenArray(xval_vec, &narr_xval, &xval_arr);
    MiBase::GenArray(xval_serr_vec, &narr_xval_serr, &xval_serr_arr);
    MiBase::GenArray(oval_vec, &narr_oval, &oval_arr);
    MiBase::GenArray(oval_serr_vec, &narr_oval_serr, &oval_serr_arr);

    assert(narr_xval == narr_xval_serr);
    assert(narr_xval == narr_oval);
    assert(narr_xval == narr_oval_serr);
    
    double xval_bin_center = 0.0;
    double xval_bin_half_width = 0.0;
    double wmean = 0.0;
    double wmean_err = 0.0;
    GetPoint2dSerrByBinning(narr_xval, 
                            xval_arr,
                            xval_serr_arr,
                            oval_arr,
                            oval_serr_arr,
                            &xval_bin_center,
                            &xval_bin_half_width,
                            &wmean,
                            &wmean_err);
    MiBase::DelArray(xval_arr);
    MiBase::DelArray(xval_serr_arr);
    MiBase::DelArray(oval_arr);
    MiBase::DelArray(oval_serr_arr);

    *xval_bin_center_ptr = xval_bin_center;
    *xval_bin_half_width_ptr = xval_bin_half_width;
    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
}



