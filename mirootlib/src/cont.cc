#include "mir_cont.h"

//
// MirCont
//

// public

void MirCont::Init(int ngraph)
{
    Null();

    ngraph_ = ngraph;
    gd2d_arr_ = new GraphData2d* [ngraph_];
    for(int igraph = 0; igraph < ngraph_; igraph ++){
        gd2d_arr_[igraph] = new GraphData2d;
    }
}

void MirCont::SetGd2dArr(int ngraph, const GraphData2d* const* const gd2d_arr)
{
    if(ngraph != GetNgraph()){
        char msg[kLineSize];
        sprintf(msg, "ngraph (=%d) != ngraph_ (=%d).",
                ngraph, GetNgraph());
        MPrintErrClass(msg);
        abort();
    }
    for(int igraph = 0; igraph < GetNgraph(); igraph ++){
        gd2d_arr_[igraph]->Copy(gd2d_arr[igraph]);
    }
}

void MirCont::AddPolygon(int npoint,
                          const double* const xval_arr,
                          const double* const yval_arr)
{
    GraphData2d* gd2d_this = new GraphData2d;
    gd2d_this->Init();
    gd2d_this->SetXvalArrDbl(npoint, xval_arr);
    gd2d_this->SetOvalArrDbl(npoint, yval_arr);
    
    if(0 != GetNgraph()){

        // make temporary graph_array to save original contour
        int ngraph_org = GetNgraph();
        GraphData2d** gd2d_arr_tmp = new GraphData2d* [ngraph_org];
        for(int igraph = 0; igraph < ngraph_org; igraph ++){
            gd2d_arr_tmp[igraph] = new GraphData2d;
            gd2d_arr_tmp[igraph]->Copy(  GetGd2dArrElm(igraph) );
        }

        // allocate new graph_array
        int ngraph_new = ngraph_org + 1;
        Init(ngraph_new);
        for(int igraph = 0; igraph < ngraph_org; igraph ++){
            gd2d_arr_[igraph]->Copy(gd2d_arr_tmp[igraph]);
        }
        gd2d_arr_[ngraph_new - 1]->Copy(gd2d_this);

        // delete temporary graph_array
        for(int igraph = 0; igraph < ngraph_org; igraph ++){
            delete gd2d_arr_tmp[igraph]; gd2d_arr_tmp[igraph] = NULL;
        }
        delete [] gd2d_arr_tmp; gd2d_arr_tmp = NULL;

    } else {
        Init(1);
        gd2d_arr_[0]->Copy(gd2d_this);
    }
    delete gd2d_this;
}

void MirCont::Copy(const MirCont* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyMirObject(org);

    int ngraph_org = org->GetNgraph();
    Init(ngraph_org);
    SetGd2dArr(ngraph_org, org->GetGd2dArr());
}

string MirCont::GetPolygonStr(int igraph) const
{
    string format = string() + "polygon(";

    int npoint = GetGd2dArrElm(igraph)->GetNdata();
    for(int ipoint = 0; ipoint < npoint; ipoint ++){
        char buf[kLineSize];
        if(ipoint < npoint - 1){
            sprintf(buf, "%e,%e,  ",
                    GetGd2dArrElm(igraph)->GetXvalElm(ipoint),
                    GetGd2dArrElm(igraph)->GetOvalElm(ipoint));
        } else {
            sprintf(buf, "%e,%e)",
                    GetGd2dArrElm(igraph)->GetXvalElm(ipoint),
                    GetGd2dArrElm(igraph)->GetOvalElm(ipoint));
        }
        format += buf;
    }
    return format;
}

MirCont* const MirCont::GenShift(double delta_xval, double delta_yval) const
{
    int ngraph = GetNgraph();
    GraphData2d** gd2d_arr_shifted = new GraphData2d* [ngraph];
    for(int igraph = 0; igraph < ngraph; igraph++){
        gd2d_arr_shifted[igraph] = new GraphData2d;

        int npoint = GetGd2dArrElm(igraph)->GetNdata();
        double* xval_arr_shift = new double [npoint];
        double* yval_arr_shift = new double [npoint];
        for(int ipoint = 0; ipoint < npoint; ipoint++){
            xval_arr_shift[ipoint] = GetGd2dArrElm(igraph)->GetXvalElm(ipoint) + delta_xval;
            yval_arr_shift[ipoint] = GetGd2dArrElm(igraph)->GetOvalElm(ipoint) + delta_yval;
        }
        int flag_xval_sorted = GetGd2dArrElm(igraph)->GetFlagXvalSorted();

        gd2d_arr_shifted[igraph]->Init();
        gd2d_arr_shifted[igraph]->SetXvalArrDbl(npoint, xval_arr_shift);
        gd2d_arr_shifted[igraph]->SetOvalArrDbl(npoint, yval_arr_shift);
        gd2d_arr_shifted[igraph]->SetFlagXvalSorted(flag_xval_sorted);
        delete [] xval_arr_shift;
        delete [] yval_arr_shift;
    }

    MirCont* shifted = new MirCont;
    shifted->Init(ngraph);
    shifted->SetGd2dArr(ngraph, gd2d_arr_shifted);

    for(int igraph = 0; igraph < ngraph; igraph++){
        delete gd2d_arr_shifted[igraph]; gd2d_arr_shifted[igraph] = NULL;
    }
    delete [] gd2d_arr_shifted; gd2d_arr_shifted = NULL;
    return shifted;
}

// private

void MirCont::Null()
{
    if(NULL != gd2d_arr_){
        for(int igraph = 0; igraph < ngraph_; igraph++){
            delete gd2d_arr_[igraph]; gd2d_arr_[igraph] = NULL;
        }
        delete [] gd2d_arr_; gd2d_arr_ = NULL;
    }
    ngraph_ = 0;
}


//
// MirContWithBest
//

// public
 
void MirContWithBest::Init()
{
    Null();

    xval_best_ = 0.0;
    yval_best_ = 0.0;
    cont_ = new MirCont;
}

void MirContWithBest::SetBest(double xval_best, double yval_best)
{
    xval_best_ = xval_best;
    yval_best_ = yval_best;
}

void MirContWithBest::SetCont(const MirCont* const cont)
{
    cont_->Copy(cont);
}

void MirContWithBest::Copy(const MirContWithBest* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyMirObject(org);

    Init();
    SetBest(org->GetXvalBest(),
            org->GetYvalBest());
    SetCont(org->GetCont());
}

MirContWithBest* const MirContWithBest::GenShift(double delta_xval, double delta_yval) const
{
    MirCont* cont_shift = GetCont()->GenShift(delta_xval, delta_yval);
    
    MirContWithBest* cont_with_best = new MirContWithBest;
    cont_with_best->Init();
    cont_with_best->SetBest(GetXvalBest() + delta_xval,
                            GetYvalBest() + delta_yval);
    cont_with_best->SetCont(cont_shift);
    delete cont_shift;
    
    return cont_with_best;
}

// private

void MirContWithBest::Null()
{
    xval_best_ = 0.0;
    yval_best_ = 0.0;    
    if(NULL != cont_){delete cont_; cont_ = NULL;}
}
