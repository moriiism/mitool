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



//
//double GraphData2dOpe::GetIntegralByTrapezoidApprox(const GraphData2d* const gd2d,
//                                                    long idata_st, long idata_ed) const
//{
//    // assert before calculation
//    assert( 2 <= gd2d->GetNdata() );
//    assert( 0 <= idata_st );
//    assert( idata_ed <= gd2d->GetNdata() - 1 );
//    assert( idata_st <= idata_ed );
//    assert( 1 == gd2d->GetFlagXvalSorted() );
//
//    double ans = 0.0;
//    for(long idata = idata_st; idata < idata_ed; idata ++){
//        ans += ( gd2d->GetOvalElm(idata) + gd2d->GetOvalElm(idata + 1) ) *
//            ( gd2d->GetXvalElm(idata + 1) - gd2d->GetXvalElm(idata) ) / 2.0;
//    }
//    return ans;
//}
//
//double GraphData2dOpe::GetIntegralInner(const GraphData2d* const gd2d,
//                                        double xval_lo, double xval_up) const
//{
//    // assert before calculation
//    assert( 2 <= gd2d->GetNdata() );
//    assert( 0 <= idata_st );
//    assert( idata_ed <= gd2d->GetNdata() - 1 );
//    assert( idata_st <= idata_ed );
//    assert( 1 == gd2d->GetFlagXvalSorted() );
//
//    
//
//    if(xval_lo > xval_up){
//        MPrintErrClass("xval_lo > xval_up");
//        abort();
//    }
//    double oval_lo = GetOvalIntPolLin(xval_lo);
//    double oval_up = GetOvalIntPolLin(xval_up);
//
//    Interval* interval = new Interval;
//    interval->InitSet(xval_lo, xval_up);
//    GraphData2d* g2d_sel = new GraphData2d;
//    GraphData2dOpe::GetSelectG2dByInterval(this,
//                                           interval,
//                                           g2d_sel);
//
//    // add two points
//    vector<double> vec_xval;
//    vector<double> vec_oval;
//    vec_xval.push_back(xval_lo);
//    vec_oval.push_back(oval_lo);
//    for(int idata = 0; idata < g2d_sel->GetNdata(); idata++){
//        vec_xval.push_back(g2d_sel->GetXvalElm(idata));
//        vec_oval.push_back(g2d_sel->GetOvalElm(idata));
//    }
//    vec_xval.push_back(xval_up);
//    vec_oval.push_back(oval_up);
//    GraphData2d* g2d_new = new GraphData2d;
//    g2d_new->Init();
//    g2d_new->SetXvalArrDbl(vec_xval);
//    g2d_new->SetOvalArrDbl(vec_oval);
//    delete interval;
//    delete g2d_sel;
//    g2d_new->Sort();
//
//    double ans = g2d_new->GetIntegralByTrapezoidApprox();
//    delete g2d_new;
//    return ans;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//double GraphData2dOpe::GetIntegral(const GraphData2d* const gd2d,
//                                   double xval_lo, double xval_up) const
//{
//    if(1 != GetFlagXvalSorted()){
//        MPrintErrClass("1 != GetFlagXvalSorted()");
//        abort();
//    }
//    long ndata = GetNdata();
//    if(ndata < 2){
//        MPrintErrClass("ndata < 2");
//        abort();
//    }
//    if(xval_lo < GetXvalElm(0) || GetXvalElm(ndata - 1) < xval_lo ){
//        MPrintErrClass("xval_lo is not within the graph range.");
//        abort();
//    }
//    if(xval_up < GetXvalElm(0) || GetXvalElm(ndata - 1) < xval_up ){
//        MPrintErrClass("xval_up is not within the graph range.");
//        abort();
//    }
//    
//    double ans = 0.0;
//    if(xval_lo < xval_up){
//        ans = GetIntegralInner(xval_lo, xval_up);
//    } else if (xval_lo > xval_up){
//        ans = -1 * GetIntegralInner(xval_up, xval_lo);
//    } else {
//        ans = 0.0;
//    }
//    if(0 < g_flag_verbose){
//        MPrintInfoClass("done.");
//    }
//    return ans;
//}
