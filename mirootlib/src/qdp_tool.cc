#include "mir_qdp_tool.h"

void MirQdpTool::GetRangeQdp(double min, double max,
                             double* const low_ptr, double* const up_ptr)
{
    double width = (max - min) * 1.2;
    double center = (max + min) / 2.;
    double low = center - width / 2.;
    double up  = center + width / 2.;
    *low_ptr = low;
    *up_ptr  = up;
}

void MirQdpTool::GetRangeQdp(const Interval* const interval,
                             double* const low_ptr, double* const up_ptr)
{
    double xval_lo = 0.0;
    double xval_up = 0.0;
    GetRangeQdp(interval->GetFirst(), interval->GetLast(), &xval_lo, &xval_up);
    *low_ptr = xval_lo;
    *up_ptr = xval_up;
}

//void MirQdpTool::GetXRangeQdp(double* const low_ptr, double* const up_ptr) const
//{
//    double low, up;
//    MirMath::GetRangeQdp(GetXvalArr()->GetValMin(), GetXvalArr()->GetValMax(), &low, &up);
//    *low_ptr = low;
//    *up_ptr  = up;
//}
//
//void GraphData2d::GetORangeQdp(double* const low_ptr, double* const up_ptr) const
//{
//    double low, up;
//    MirMath::GetRangeQdp(GetOvalArr()->GetValMin(), GetOvalArr()->GetValMax(), &low, &up);
//    *low_ptr = low;
//    *up_ptr  = up;
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
//void DataArrayTerr1d::GetRangeValQdp(const DataArray1d* const da1d,
//                                     double* const lo_ptr,
//                                     double* const up_ptr) const
//{
//    double lo, up;
//    GetRangeQdp(da1d->GetValAndErrMin(), da1d->GetValAndErrMax(), &lo, &up);
//    *lo_ptr = lo;
//    *up_ptr = up;
//}
//
//
//// get Range Qdp
//
//void GraphDataSerr2d::GetXRangeQdp(double* const low_ptr, double* const up_ptr) const
//{
//    double low, up;
//    MirMath::GetRangeQdp(GetXvalArr()->GetValAndErrMin(), GetXvalArr()->GetValAndErrMax(), &low, &up);
//    *low_ptr = low;
//    *up_ptr  = up;
//    if(0 < g_flag_verbose){
//        MPrintInfo("done.");
//    }
//}
//
//void GraphDataSerr2d::GetORangeQdp(double* const low_ptr, double* const up_ptr) const
//{
//    double low, up;
//    MirMath::GetRangeQdp(GetOvalArr()->GetValAndErrMin(), GetOvalArr()->GetValAndErrMax(), &low, &up);
//    *low_ptr = low;
//    *up_ptr  = up;
//    if(0 < g_flag_verbose){
//        MPrintInfo("done.");
//    }
//}
//



void MirQdpTool::PrintQdpRead(FILE* fp, string format)
{
    fprintf(fp, "\n");    
    if("x" == format){
        MPrintErr("bad format");
        abort();

    } else if ("x,y" == format){
        fprintf(fp, "\n");
    } else if ("x,y,ye" == format){
        fprintf(fp, "read serr 2\n");
    } else if ("x,xe,y,ye" == format){
        fprintf(fp, "read serr 1 2\n");
    } else if ("x,xe,y" == format){
        fprintf(fp, "read serr 1\n");
    } else if ("x,y,ye+,ye-" == format){
        fprintf(fp, "read terr 2\n");
    } else if ("x,xe,y,ye+,ye-" == format){
        fprintf(fp, "read serr 1\n");
        fprintf(fp, "read terr 2\n");
    } else if ("x,xe+,xe-,y" == format){
        fprintf(fp, "read terr 1\n");
    } else if ("x,xe+,xe-,y,ye" == format){
        fprintf(fp, "read terr 1\n");
        fprintf(fp, "read serr 2\n");
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        fprintf(fp, "read terr 1 2\n");
    } else {
        MPrintErr("bad format");
        abort();        
    }
    fprintf(fp, "\n");
}

void MirQdpTool::PrintQdpCmdStd(FILE* fp)
{
    fprintf(fp, "\n");
    fprintf(fp, "la file\n");
    fprintf(fp, "time off\n");    
    fprintf(fp, "lw 5\n");
    fprintf(fp, "csize 1.2\n");
    fprintf(fp, "la rot \n");
    fprintf(fp, "\n");    
}

void MirQdpTool::PrintQdpAxisRescale(FILE* fp, string xy,
                                     double val_lo, double val_up)
{
    char cmd[kLineSize];
    sprintf(cmd, "r  %s  %.15e  %.15e", xy.c_str(), val_lo, val_up);
    if( fabs(val_up - val_lo) > DBL_EPSILON ){
        fprintf(fp, "%s\n", cmd);
    }
}


void MirQdpTool::PrintQdpAxisTitle(FILE* fp, string xy,
                                   string title, double offset)
{
    char cmd[kLineSize];
    if(fabs(offset) < DBL_EPSILON){
        sprintf(cmd, "la %s %s",
                xy.c_str(), title.c_str());
    } else {
        sprintf(cmd, "la %s %s (offset = %.15e)",
                xy.c_str(), title.c_str(), offset);
    }
    fprintf(fp, "%s\n", cmd);
}

void MirQdpTool::PrintQdpScale(FILE* fp, string xy, string scale)
{
    if("log" == scale){
        fprintf(fp, "log   %s  on\n",
                xy.c_str());
    }
}

void MirQdpTool::MkQdpMode1(const DataArray1d* const data_array,
                            string qdpout,
                            string title_oval,
                            double offset_oval,
                            string scale_xval,
                            string scale_oval)
{
    //
    // index  data
    //
    
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    if("DataArray1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y");
    } else if ("DataArraySerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y,ye");
    } else if ("DataArrayTerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y,ye+,ye-");
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad class name");
        MPrintErr(msg);
        abort();
    }

    string title_xval = "index";
    double offset_xval = 0.0;

    int mode = 1;
    data_array->PrintData(fp, mode, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    data_array->GetRangeIndexQdp(&xval_lo, &xval_up);
    data_array->GetRangeValQdp(&oval_lo, &oval_up);
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;

    PrintQdpCmdStd(fp);
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);
    fclose(fp);
}


void MirQdpTool::MkQdpMode1(const DataArray1d* const data_array,
                            string qdpout,
                            const MirPlotConf* const plot_conf)
{
    //
    // index  data
    //

    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MPrintErr(msg);
        abort();
    }

    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    if("DataArray1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y");
    } else if ("DataArraySerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y,ye");
    } else if ("DataArrayTerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y,ye+,ye-");
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad class name");
        MPrintErr(msg);
        abort();
    }

    string title_xval  = plot_conf->GetLabelElm(0);
    string title_oval  = plot_conf->GetLabelElm(1);
    // offset_xval must be zero
    if("no" !=  plot_conf->GetOffsetTagElm(0) &&
       fabs(atof(plot_conf->GetOffsetTagElm(0).c_str())) > DBL_EPSILON ){
        char msg[kLineSize];
        sprintf(msg, "offset_xval must be zero");
        MPrintErr(msg);
        abort();
    }
    double offset_xval = 0.0;
    double offset_oval = data_array->GetOffsetValFromTag(plot_conf->GetOffsetTagElm(1));

    int mode = 1;
    data_array->PrintData(fp, mode, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    data_array->GetRangeIndexQdp(&xval_lo, &xval_up);
    data_array->GetRangeValQdp(&oval_lo, &oval_up);

    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_shifted = 0.0;
    double oval_up_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }

    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_shifted = oval_lo - offset_oval;
    } else {
        oval_lo_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_shifted = oval_up - offset_oval;
    } else {
        oval_up_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }

    PrintQdpCmdStd(fp);
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);    
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    PrintQdpScale(fp, "y", plot_conf->GetScaleElm(1));
    
    fclose(fp);
}


void MirQdpTool::MkQdpMode2(const DataArray1d* const data_array,
                            string qdpout,
                            string title_xval,
                            double offset_xval,
                            string scale_xval)
{
    //
    // data  1.0
    //
    
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    if("DataArray1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y");
    } else if ("DataArraySerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,xe,y");
    } else if ("DataArrayTerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,xe+,xe-,y");
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad class name");
        MPrintErr(msg);
        abort();
    }

    string title_oval = "event";
    double offset_oval = 0.0;

    int mode = 2;
    data_array->PrintData(fp, mode, offset_xval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = -0.5;
    double oval_up = +1.5;
    data_array->GetRangeValQdp(&xval_lo, &xval_up);
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;

    PrintQdpCmdStd(fp);
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    fclose(fp);
}


void MirQdpTool::MkQdpMode2(const DataArray1d* const data_array,
                            string qdpout,
                            const MirPlotConf* const plot_conf)
{
    //
    // data  1.0
    //

    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MPrintErr(msg);
        abort();
    }
    
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    if("DataArray1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y");
    } else if ("DataArraySerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,xe,y");
    } else if ("DataArrayTerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,xe+,xe-,y");
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad class name");
        MPrintErr(msg);
        abort();
    }

    string title_xval = plot_conf->GetLabelElm(0);
    string title_oval = plot_conf->GetLabelElm(1);
    double offset_xval = data_array->GetOffsetValFromTag(plot_conf->GetOffsetTagElm(0));    
    // offset_oval must be zero
    if("no" !=  plot_conf->GetOffsetTagElm(1) &&
       fabs(atof(plot_conf->GetOffsetTagElm(1).c_str())) > DBL_EPSILON ){
        char msg[kLineSize];
        sprintf(msg, "offset_oval must be zero");
        MPrintErr(msg);
        abort();
    }
    double offset_oval = 0.0;

    int mode = 2;
    data_array->PrintData(fp, mode, offset_xval);


    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = -0.5;
    double oval_up = +1.5;
    data_array->GetRangeValQdp(&xval_lo, &xval_up);
    
    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_shifted = 0.0;
    double oval_up_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }
    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_shifted = oval_lo - offset_oval;
    } else {
        oval_lo_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_shifted = oval_up - offset_oval;
    } else {
        oval_up_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }

    PrintQdpCmdStd(fp);
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);    
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    fclose(fp);
}


void MirQdpTool::MkQdp(const GraphData2d* const graph_data,
                       string qdpout,
                       string format,
                       string title_xval,
                       string title_oval,
                       double offset_xval,
                       double offset_oval,
                       string scale_xval,
                       string scale_oval)
{
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    PrintQdpRead(fp, format);

    graph_data->PrintData(fp, format, offset_xval, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    graph_data->GetXRangeQdp(&xval_lo, &xval_up);
    graph_data->GetORangeQdp(&oval_lo, &oval_up);
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;
    
    PrintQdpCmdStd(fp);
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);
    fclose(fp);
}


void MirQdpTool::MkQdp(const GraphData2d* const graph_data,
                       string qdpout,
                       string format,
                       const MirPlotConf* const plot_conf)
{
    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MPrintErr(msg);
        abort();
    }
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    PrintQdpRead(fp, format);

    string title_xval = plot_conf->GetLabelElm(0);
    string title_oval = plot_conf->GetLabelElm(1);
    double offset_xval = graph_data->GetOffsetXFromTag(plot_conf->GetOffsetTagElm(0));
    double offset_oval = graph_data->GetOffsetOFromTag(plot_conf->GetOffsetTagElm(1));

    graph_data->PrintData(fp, format, offset_xval, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    graph_data->GetXRangeQdp(&xval_lo, &xval_up);
    graph_data->GetORangeQdp(&oval_lo, &oval_up);

    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_shifted = 0.0;
    double oval_up_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }
    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_shifted = oval_lo - offset_oval;
    } else {
        oval_lo_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_shifted = oval_up - offset_oval;
    } else {
        oval_up_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }
    
    PrintQdpCmdStd(fp);
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    PrintQdpScale(fp, "y", plot_conf->GetScaleElm(1));
    fclose(fp);
}


void MirQdpTool::MkQdp(const HistData1d* const hist_data,
                       string outqdp,
                       string format,
                       string title_xval,
                       string title_oval,
                       double offset_xval,
                       double offset_oval,
                       string scale_xval,
                       string scale_oval)
{
    string format_this = "";
    if("def" == format){
        if("HistData1d" == hist_data->GetClassName()){
            format_this = "x,y";
        } else if ("HistDataSerr1d" == hist_data->GetClassName()){
            format_this = "x,y,ye";
        } else if ("HistDataTerr1d" == hist_data->GetClassName()){
            format_this = "x,y,ye+,ye-";
        } else {
            MPrintErr("bad classname");
            abort();
        }
    } else {
        format_this = format;
    }
    
    FILE* fp = fopen(outqdp.c_str(), "w");
    fprintf(fp, "skip sing \n");
    PrintQdpRead(fp, format_this);
    
    hist_data->PrintData(fp, format_this, offset_xval, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    hist_data->GetXRangeQdp(&xval_lo, &xval_up);
    hist_data->GetORangeQdp(&oval_lo, &oval_up);
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;

    PrintQdpCmdStd(fp);
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);
    fclose(fp);
}


void MirQdpTool::MkQdp(const HistData1d* const hist_data,
                       string outqdp,
                       string format,
                       const MirPlotConf* const plot_conf)
{
    string format_this = "";
    if("def" == format){
        if("HistData1d" == hist_data->GetClassName()){
            format_this = "x,y";
        } else if ("HistDataSerr1d" == hist_data->GetClassName()){
            format_this = "x,y,ye";
        } else if ("HistDataTerr1d" == hist_data->GetClassName()){
            format_this = "x,y,ye+,ye-";
        } else {
            MPrintErr("bad classname");
            abort();
        }
    } else {
        format_this = format;
    }
    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MPrintErr(msg);
        abort();
    }

    FILE* fp = fopen(outqdp.c_str(), "w");
    fprintf(fp, "skip sing \n");
    PrintQdpRead(fp, format_this);

    string title_xval = plot_conf->GetLabelElm(0);
    string title_oval = plot_conf->GetLabelElm(1);
    double offset_xval = hist_data->GetOffsetXFromTag(plot_conf->GetOffsetTagElm(0));
    double offset_oval = hist_data->GetOffsetOFromTag(plot_conf->GetOffsetTagElm(1));

    hist_data->PrintData(fp, format_this, offset_xval, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    hist_data->GetXRangeQdp(&xval_lo, &xval_up);
    hist_data->GetORangeQdp(&oval_lo, &oval_up);
    
    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_shifted = 0.0;
    double oval_up_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }
    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_shifted = oval_lo - offset_oval;
    } else {
        oval_lo_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_shifted = oval_up - offset_oval;
    } else {
        oval_up_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }

    PrintQdpCmdStd(fp);
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    PrintQdpScale(fp, "y", plot_conf->GetScaleElm(1));
    fclose(fp);
}


void MirQdpTool::MkQdp(const MirFunc* const func, const double* const par,
                       int npoint, double xval_lo, double xval_up,
                       string outqdp,
                       string title_xval,
                       string title_oval,
                       double offset_xval,
                       double offset_oval,
                       string scale_xval,
                       string scale_oval)
{
    GraphData2d* gd2d = new GraphData2d;
    gd2d->InitSetByFunc(func, par, npoint, xval_lo, xval_up, scale_xval);
    MkQdp(gd2d, outqdp, "x,y",
          title_xval, title_oval,
          offset_xval, offset_oval,
          scale_xval, scale_oval);
    delete gd2d;
}

void MirQdpTool::MkQdp(const MirFunc* const func, const double* const par,
                       int npoint, double xval_lo, double xval_up,
                       string outqdp,
                       const MirPlotConf* const plot_conf)
{
    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MPrintErr(msg);
        abort();
    }
    GraphData2d* gd2d = new GraphData2d;
    gd2d->InitSetByFunc(func, par, npoint, xval_lo, xval_up, plot_conf->GetScaleElm(0));
    MkQdp(gd2d, outqdp, "x,y", plot_conf);
    delete gd2d;
}


void MirQdpTool::MkQdp(const Interval* const interval,
                       string qdpout,
                       string title_xval,
                       double offset_xval,
                       string scale_xval)
{
    vector<double> xval_vec;
    vector<double> oval_vec;
    for(int iterm = 0; iterm < interval->GetNterm(); iterm++){
        xval_vec.push_back(interval->GetTstartElm(iterm));
        oval_vec.push_back(0.0);
        xval_vec.push_back(interval->GetTstartElm(iterm));
        oval_vec.push_back(1.0);
        xval_vec.push_back(interval->GetTstopElm(iterm));
        oval_vec.push_back(1.0);
        xval_vec.push_back(interval->GetTstopElm(iterm));
        oval_vec.push_back(0.0);
    }
    GraphData2d* gd2d = new GraphData2d;
    gd2d->Init();
    gd2d->SetXvalArrDbl(xval_vec);
    gd2d->SetOvalArrDbl(oval_vec);
    gd2d->SetFlagXvalSorted(0);

    string title_oval = "GTI";
    double offset_oval = 0.0;
    MkQdp(gd2d, qdpout, "x,y",
          title_xval, title_oval,
          offset_xval, offset_oval,
          scale_xval, "lin");
    delete gd2d;
}


void MirQdpTool::MkQdp(const Interval* const interval,
                       string qdpout,
                       const MirPlotConf* const plot_conf)
{
    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MPrintErr(msg);
        abort();
    }
    
    vector<double> xval_vec;
    vector<double> oval_vec;
    for(int iterm = 0; iterm < interval->GetNterm(); iterm++){
        xval_vec.push_back(interval->GetTstartElm(iterm));
        oval_vec.push_back(0.0);
        xval_vec.push_back(interval->GetTstartElm(iterm));
        oval_vec.push_back(1.0);
        xval_vec.push_back(interval->GetTstopElm(iterm));
        oval_vec.push_back(1.0);
        xval_vec.push_back(interval->GetTstopElm(iterm));
        oval_vec.push_back(0.0);
    }
    GraphData2d* gd2d = new GraphData2d;
    gd2d->Init();
    gd2d->SetXvalArrDbl(xval_vec);
    gd2d->SetOvalArrDbl(oval_vec);
    gd2d->SetFlagXvalSorted(0);

    MkQdp(gd2d, qdpout, "x,y", plot_conf);
    delete gd2d;
}


void MirQdpTool::MkQdpDiff(const GraphData2d* const graph_data,
                           const GraphData2d* const graph_model,
                           const GraphData2d* const graph_res,
                           string qdpout,
                           string format, 
                           string title_xval,
                           string title_oval,
                           string title_oval_res,
                           double offset_xval,
                           double offset_oval,
                           double offset_oval_res,
                           string scale_xval,
                           string scale_oval,
                           string scale_oval_res)
{
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing\n");
    PrintQdpRead(fp, format);
    fprintf(fp, "\n");

    graph_data->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    graph_model->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    graph_res->PrintData(fp, format, offset_xval, offset_oval_res);

    fprintf(fp, "\n");

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo_w1 = 0.0;
    double oval_up_w1 = 0.0;
    double oval_lo_w2 = 0.0;
    double oval_up_w2 = 0.0;    
    graph_data->GetXRangeQdp(&xval_lo, &xval_up);
    graph_data->GetORangeQdp(&oval_lo_w1, &oval_up_w1);
    graph_res->GetORangeQdp(&oval_lo_w2, &oval_up_w2);

    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_w1_shifted = oval_lo_w1 - offset_oval;
    double oval_up_w1_shifted = oval_up_w1 - offset_oval;
    double oval_lo_w2_shifted = oval_lo_w2 - offset_oval_res;
    double oval_up_w2_shifted = oval_up_w2 - offset_oval_res;

    PrintQdpCmdStd(fp);
    fprintf(fp, "win 1\n");
    fprintf(fp, "LOC  0 0.301999986 1 0.899999976\n");
    fprintf(fp, "LAB  NX OFF\n");
    fprintf(fp, "yplot 1 2\n");
    fprintf(fp, "line st on 2\n");
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);    
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w1_shifted, oval_up_w1_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);    

    fprintf(fp, "win 2\n");
    fprintf(fp, "LOC  0 0.100000001 1 0.389999986\n");
    fprintf(fp, "yplot 3\n");
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval_res, offset_oval_res);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w2_shifted, oval_up_w2_shifted);
    PrintQdpScale(fp, "y", scale_oval_res);        
    
    fprintf(fp, "mark 22 on 1 3\n");
    fprintf(fp, "la 1 line 0.0 1.0 pos %.15e %.15e \" \" lst 4\n",
            xval_lo_shifted, 0.0);

    fclose(fp);
}


void MirQdpTool::MkQdpDiff(const GraphData2d* const graph_data,
                           const GraphData2d* const graph_model,
                           const GraphData2d* const graph_res,
                           string qdpout,
                           string format,
                           const MirPlotConf* const plot_conf)

{
    if(3 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 3");
        MPrintErr(msg);
        abort();
    }
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing\n");
    PrintQdpRead(fp, format);
    fprintf(fp, "\n");

    string title_xval = plot_conf->GetLabelElm(0);
    string title_oval = plot_conf->GetLabelElm(1);
    string title_oval_res = plot_conf->GetLabelElm(2);
    double offset_xval = graph_data->GetOffsetXFromTag(plot_conf->GetOffsetTagElm(0));
    double offset_oval = graph_data->GetOffsetOFromTag(plot_conf->GetOffsetTagElm(1));
    double offset_oval_res = graph_res->GetOffsetOFromTag(plot_conf->GetOffsetTagElm(2));
    
    graph_data->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    graph_model->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    graph_res->PrintData(fp, format, offset_xval, offset_oval_res);

    fprintf(fp, "\n");

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo_w1 = 0.0;
    double oval_up_w1 = 0.0;
    double oval_lo_w2 = 0.0;
    double oval_up_w2 = 0.0;    
    graph_data->GetXRangeQdp(&xval_lo, &xval_up);
    graph_data->GetORangeQdp(&oval_lo_w1, &oval_up_w1);
    graph_res->GetORangeQdp(&oval_lo_w2, &oval_up_w2);

    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_w1_shifted = 0.0;
    double oval_up_w1_shifted = 0.0;
    double oval_lo_w2_shifted = 0.0;
    double oval_up_w2_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }
    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_w1_shifted = oval_lo_w1 - offset_oval;
    } else {
        oval_lo_w1_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_w1_shifted = oval_up_w1 - offset_oval;
    } else {
        oval_up_w1_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }

    if("none" == plot_conf->GetLoStrElm(2)){
        oval_lo_w2_shifted = oval_lo_w2 - offset_oval_res;
    } else {
        oval_lo_w2_shifted = atof(plot_conf->GetLoStrElm(2).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(2)){
        oval_up_w2_shifted = oval_up_w2 - offset_oval_res;
    } else {
        oval_up_w2_shifted = atof(plot_conf->GetUpStrElm(2).c_str());
    }

    PrintQdpCmdStd(fp);
    fprintf(fp, "win 1\n");
    fprintf(fp, "LOC  0 0.301999986 1 0.899999976\n");
    fprintf(fp, "LAB  NX OFF\n");
    fprintf(fp, "yplot 1 2\n");
    fprintf(fp, "line st on 2\n");
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w1_shifted, oval_up_w1_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    PrintQdpScale(fp, "y", plot_conf->GetScaleElm(1));
    
    fprintf(fp, "win 2\n");
    fprintf(fp, "LOC  0 0.100000001 1 0.389999986\n");
    fprintf(fp, "yplot 3\n");
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval_res, offset_oval_res);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w2_shifted, oval_up_w2_shifted);
    PrintQdpScale(fp, "y", plot_conf->GetScaleElm(2));

    fprintf(fp, "mark 22 on 1 3\n");
    fprintf(fp, "la 1 line 0.0 1.0 pos %.15e %.15e \" \" lst 4\n",
            xval_lo_shifted, 0.0);
    fclose(fp);
}


void MirQdpTool::MkQdpDiff(const HistData1d* const hist_data,
                           const HistData1d* const hist_model,
                           const HistData1d* const hist_res,
                           string qdpout,
                           string format, 
                           string title_xval,
                           string title_oval,
                           string title_oval_res,
                           double offset_xval,
                           double offset_oval,
                           double offset_oval_res,
                           string scale_xval,
                           string scale_oval,
                           string scale_oval_res)
{
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing\n");
    PrintQdpRead(fp, format);    
    fprintf(fp, "\n");

    hist_data->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    hist_model->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    hist_res->PrintData(fp, format, offset_xval, offset_oval_res);

    fprintf(fp, "\n");

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo_w1 = 0.0;
    double oval_up_w1 = 0.0;
    double oval_lo_w2 = 0.0;
    double oval_up_w2 = 0.0;    
    hist_data->GetXRangeQdp(&xval_lo, &xval_up);
    hist_data->GetORangeQdp(&oval_lo_w1, &oval_up_w1);
    hist_res->GetORangeQdp(&oval_lo_w2, &oval_up_w2);

    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_w1_shifted = oval_lo_w1 - offset_oval;
    double oval_up_w1_shifted = oval_up_w1 - offset_oval;
    double oval_lo_w2_shifted = oval_lo_w2 - offset_oval_res;
    double oval_up_w2_shifted = oval_up_w2 - offset_oval_res;

    PrintQdpCmdStd(fp);
    fprintf(fp, "win 1\n");
    fprintf(fp, "LOC  0 0.301999986 1 0.899999976\n");
    fprintf(fp, "LAB  NX OFF\n");
    fprintf(fp, "yplot 1 2\n");
    fprintf(fp, "line st on 2\n");
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);    
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w1_shifted, oval_up_w1_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);    

    fprintf(fp, "win 2\n");
    fprintf(fp, "LOC  0 0.100000001 1 0.389999986\n");
    fprintf(fp, "yplot 3\n");
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval_res, offset_oval_res);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w2_shifted, oval_up_w2_shifted);
    PrintQdpScale(fp, "x", scale_xval);    
    PrintQdpScale(fp, "y", scale_oval_res);    

    fprintf(fp, "mark 22 on 1 3\n");
    fprintf(fp, "la 1 line 0.0 1.0 pos %.15e %.15e \" \" lst 4\n",
            xval_lo_shifted, 0.0);
    fclose(fp);
}


void MirQdpTool::MkQdpDiff(const HistData1d* const hist_data,
                           const HistData1d* const hist_model,
                           const HistData1d* const hist_res,
                           string qdpout,
                           string format,
                           const MirPlotConf* const plot_conf)
{
    if(3 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 3");
        MPrintErr(msg);
        abort();
    }
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing\n");
    PrintQdpRead(fp, format);
    fprintf(fp, "\n");

    string title_xval = plot_conf->GetLabelElm(0);
    string title_oval = plot_conf->GetLabelElm(1);
    string title_oval_res = plot_conf->GetLabelElm(2);
    double offset_xval = hist_data->GetOffsetXFromTag(plot_conf->GetOffsetTagElm(0));
    double offset_oval = hist_data->GetOffsetOFromTag(plot_conf->GetOffsetTagElm(1));
    double offset_oval_res = hist_res->GetOffsetOFromTag(plot_conf->GetOffsetTagElm(2));
    
    hist_data->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    hist_model->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    hist_res->PrintData(fp, format, offset_xval, offset_oval_res);

    fprintf(fp, "\n");

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo_w1 = 0.0;
    double oval_up_w1 = 0.0;
    double oval_lo_w2 = 0.0;
    double oval_up_w2 = 0.0;    
    hist_data->GetXRangeQdp(&xval_lo, &xval_up);
    hist_data->GetORangeQdp(&oval_lo_w1, &oval_up_w1);
    hist_res->GetORangeQdp(&oval_lo_w2, &oval_up_w2);

    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_w1_shifted = 0.0;
    double oval_up_w1_shifted = 0.0;
    double oval_lo_w2_shifted = 0.0;
    double oval_up_w2_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }
    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_w1_shifted = oval_lo_w1 - offset_oval;
    } else {
        oval_lo_w1_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_w1_shifted = oval_up_w1 - offset_oval;
    } else {
        oval_up_w1_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }

    if("none" == plot_conf->GetLoStrElm(2)){
        oval_lo_w2_shifted = oval_lo_w2 - offset_oval_res;
    } else {
        oval_lo_w2_shifted = atof(plot_conf->GetLoStrElm(2).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(2)){
        oval_up_w2_shifted = oval_up_w2 - offset_oval_res;
    } else {
        oval_up_w2_shifted = atof(plot_conf->GetUpStrElm(2).c_str());
    }

    PrintQdpCmdStd(fp);
    fprintf(fp, "win 1\n");
    fprintf(fp, "LOC  0 0.301999986 1 0.899999976\n");
    fprintf(fp, "LAB  NX OFF\n");
    fprintf(fp, "yplot 1 2\n");
    fprintf(fp, "line st on 2\n");
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w1_shifted, oval_up_w1_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    PrintQdpScale(fp, "y", plot_conf->GetScaleElm(1));    

    fprintf(fp, "win 2\n");
    fprintf(fp, "LOC  0 0.100000001 1 0.389999986\n");
    fprintf(fp, "yplot 3\n");
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval_res, offset_oval_res);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w2_shifted, oval_up_w2_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    PrintQdpScale(fp, "y", plot_conf->GetScaleElm(2));

    fprintf(fp, "mark 22 on 1 3\n");
    fprintf(fp, "la 1 line 0.0 1.0 pos %.15e %.15e \" \" lst 4\n",
            xval_lo_shifted, 0.0);
    fclose(fp);
}



void MirQdpTool::MkQdpDiff3(const GraphDataSerr2d* const graph_data,
                            const MirFunc* const func, const double* const par,
                            int npoint_func,
                            string outdir, string qdpout_head,
                            string title_xval,
                            string title_oval,
                            double offset_xval,
                            double offset_oval,
                            string scale_xval,
                            string scale_oval)
{
    double xval_lo, xval_up;
    graph_data->GetXRangeQdp(&xval_lo, &xval_up);

    GraphData2d* graph_func = new GraphData2d;
    graph_func->InitSetByFunc(func, par,
                              npoint_func, xval_lo, xval_up,
                              scale_xval);

    GraphDataSerr2d* graph_res_val   = new GraphDataSerr2d;
    GraphDataSerr2d* graph_res_chi   = new GraphDataSerr2d;
    GraphDataSerr2d* graph_res_ratio = new GraphDataSerr2d;
    GraphData2dOpe::GetResValGd2(graph_data, func, par,
                                 graph_res_val);
    GraphData2dOpe::GetResChiGd2(graph_data, func, par,
                                 graph_res_chi);
    GraphData2dOpe::GetResRatioGd2(graph_data, func, par,
                                   graph_res_ratio);
    string format = "x,xe,y,ye";
    MkQdpDiff(graph_data, graph_func, graph_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              title_xval, title_oval, "res_val",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");

    MkQdpDiff(graph_data, graph_func, graph_res_chi, 
              outdir + "/" + qdpout_head + "_diff_chi.qdp",
              format, 
              title_xval, title_oval, "chi",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");

    MkQdpDiff(graph_data, graph_func, graph_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              title_xval, title_oval, "ratio",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");

    delete graph_res_val;
    delete graph_res_chi;
    delete graph_res_ratio;
    delete graph_func;
}

void MirQdpTool::MkQdpDiff3(const GraphDataSerr2d* const graph_data,
                            const MirFunc* const func, const double* const par,
                            int npoint_func,
                            string outdir, string qdpout_head,
                            const MirPlotConf* const plot_conf)
{
    if(5 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 5");
        MPrintErr(msg);
        abort();
    }
    double xval_lo, xval_up;
    graph_data->GetXRangeQdp(&xval_lo, &xval_up);

    GraphData2d* graph_func = new GraphData2d;
    graph_func->InitSetByFunc(func, par,
                              npoint_func, xval_lo, xval_up,
                              plot_conf->GetScaleElm(0));

    GraphDataSerr2d* graph_res_val   = new GraphDataSerr2d;
    GraphDataSerr2d* graph_res_chi   = new GraphDataSerr2d;
    GraphDataSerr2d* graph_res_ratio = new GraphDataSerr2d;
    GraphData2dOpe::GetResValGd2(graph_data, func, par,
                                 graph_res_val);
    GraphData2dOpe::GetResChiGd2(graph_data, func, par,
                                 graph_res_chi);
    GraphData2dOpe::GetResRatioGd2(graph_data, func, par,
                                   graph_res_ratio);

    
    MirPlotConf* plot_conf_val   = NULL;
    MirPlotConf* plot_conf_chi   = NULL;
    MirPlotConf* plot_conf_ratio = NULL;
    MirPlotConf::GenPlotConf3(plot_conf,
                              &plot_conf_val,
                              &plot_conf_chi,
                              &plot_conf_ratio);

    string format = "x,xe,y,ye";
    MkQdpDiff(graph_data, graph_func, graph_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              plot_conf_val);

    MkQdpDiff(graph_data, graph_func, graph_res_chi, 
              outdir + "/" + qdpout_head + "_diff_chi.qdp",
              format,
              plot_conf_chi);

    MkQdpDiff(graph_data, graph_func, graph_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              plot_conf_ratio);

    delete graph_res_val;
    delete graph_res_chi;
    delete graph_res_ratio;
    delete graph_func;
    delete plot_conf_val;
    delete plot_conf_chi;
    delete plot_conf_ratio;
}


void MirQdpTool::MkQdpDiff3(const HistDataSerr1d* const hist_data,
                            const MirFunc* const func, const double* const par,
                            int npoint_func,
                            string outdir, string qdpout_head,
                            string title_xval,
                            string title_oval,
                            double offset_xval,
                            double offset_oval,
                            string scale_xval,
                            string scale_oval)
{
    double xval_lo, xval_up;
    hist_data->GetXRangeQdp(&xval_lo, &xval_up);

    HistData1d* hist_func = new HistData1d;
    hist_func->Init(npoint_func, xval_lo, xval_up);
    hist_func->SetByFunc(func, par);

    HistDataSerr1d* hist_res_val   = new HistDataSerr1d;
    HistDataSerr1d* hist_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* hist_res_ratio = new HistDataSerr1d;
    hist_res_val->Init(npoint_func, xval_lo, xval_up);
    hist_res_chi->Init(npoint_func, xval_lo, xval_up);
    hist_res_ratio->Init(npoint_func, xval_lo, xval_up);
    
    HistData1dOpe::GetResValHd1(hist_data, func, par,
                                hist_res_val);
    HistData1dOpe::GetResChiHd1(hist_data, func, par,
                                hist_res_chi);
    HistData1dOpe::GetResRatioHd1(hist_data, func, par,
                                  hist_res_ratio);

    string format = "x,xe,y,ye";
    MkQdpDiff(hist_data, hist_func, hist_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              title_xval, title_oval, "res_val",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");
              
    MkQdpDiff(hist_data, hist_func, hist_res_chi, 
              outdir + "/" + qdpout_head + "_diff_chi.qdp",
              format,
              title_xval, title_oval, "chi",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");              

    MkQdpDiff(hist_data, hist_func, hist_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              title_xval, title_oval, "ratio",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");

    delete hist_res_val;
    delete hist_res_chi;
    delete hist_res_ratio;
    delete hist_func;
}



void MirQdpTool::MkQdpDiff3(const HistDataSerr1d* const hist_data,
                            const MirFunc* const func, const double* const par,
                            int npoint_func,
                            string outdir, string qdpout_head,
                            const MirPlotConf* const plot_conf)
{
    if(5 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 5");
        MPrintErr(msg);
        abort();
    }
    double xval_lo, xval_up;
    hist_data->GetXRangeQdp(&xval_lo, &xval_up);

    HistData1d* hist_func = new HistData1d;
    hist_func->Init(npoint_func, xval_lo, xval_up);
    hist_func->SetByFunc(func, par);

    HistDataSerr1d* hist_res_val   = new HistDataSerr1d;
    HistDataSerr1d* hist_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* hist_res_ratio = new HistDataSerr1d;
    hist_res_val->Init(npoint_func, xval_lo, xval_up);
    hist_res_chi->Init(npoint_func, xval_lo, xval_up);
    hist_res_ratio->Init(npoint_func, xval_lo, xval_up);
    
    HistData1dOpe::GetResValHd1(hist_data, func, par,
                                hist_res_val);
    HistData1dOpe::GetResChiHd1(hist_data, func, par,
                                hist_res_chi);
    HistData1dOpe::GetResRatioHd1(hist_data, func, par,
                                  hist_res_ratio);

    MirPlotConf* plot_conf_val   = NULL;
    MirPlotConf* plot_conf_chi   = NULL;
    MirPlotConf* plot_conf_ratio = NULL;
    MirPlotConf::GenPlotConf3(plot_conf,
                              &plot_conf_val,
                              &plot_conf_chi,
                              &plot_conf_ratio);    

    string format = "x,xe,y,ye";
    MkQdpDiff(hist_data, hist_func, hist_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              plot_conf_val);
              
    MkQdpDiff(hist_data, hist_func, hist_res_chi, 
              outdir + "/" + qdpout_head + "_diff_chi.qdp",
              format,
              plot_conf_chi);

    MkQdpDiff(hist_data, hist_func, hist_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              plot_conf_ratio);

    delete hist_res_val;
    delete hist_res_chi;
    delete hist_res_ratio;
    delete hist_func;
    delete plot_conf_val;
    delete plot_conf_chi;
    delete plot_conf_ratio;
}


void MirQdpTool::MkQdpMinFcn(const HistData1d* const hist_data,
                             string outqdp,
                             double xval_at_fcnmin,
                             double xval_terr_minus,
                             double xval_terr_plus,
                             double fcnmin,
                             string title_xval)
{
    FILE *fp = fopen(outqdp.c_str(), "w");
    fprintf(fp, "skip sing \n");
    fprintf(fp, "\n");
    hist_data->PrintData(fp, "x,y");
    fprintf(fp, "\n");
    fprintf(fp, "csize 1.5\n");
    fprintf(fp, "line on \n");
    fprintf(fp, "mark 22 on \n");
    fprintf(fp, "view 0.2 0.1 0.95 0.95\n");
    fprintf(fp, "la pos y 4.0\n");

    double x_lo, x_up;
    hist_data->GetXRangeQdp(&x_lo, &x_up);
    double y_lo, y_up;
    hist_data->GetORangeQdp(&y_lo, &y_up);
    
    double oval_1sigma   = fcnmin + MirMath::GetUpMinfcn(1.0, "sigma", 1);
    double oval_90cl1p   = fcnmin + MirMath::GetUpMinfcn(0.90, "cl", 1);
    double oval_99cl1p   = fcnmin + MirMath::GetUpMinfcn(0.99, "cl", 1);

    int ilab = 1;

    // horizontal lines
    // line at chi2min
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 0.0 1.0 lst 4\n",
            ilab, x_lo, fcnmin);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%s\" jus left cen bot csize 1.2\n",
            ilab, x_lo, fcnmin, "best");
    ilab ++;

    // line at chi2min + 1 sigma
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 0.0 1.0 lst 4\n",
            ilab, x_lo, oval_1sigma);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%s\" jus left cen bot csize 1.2\n",
            ilab, x_lo, oval_1sigma, "1sigma");
    ilab ++;

    // line at chi2min + 90%CL
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 0.0 1.0 lst 4\n",
            ilab, x_lo, oval_90cl1p);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%s\" jus left cen bot csize 1.2\n",
            ilab, x_lo, oval_90cl1p, "90%CL");
    ilab ++;

    // line at chi2min + 99%CL
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 0.0 1.0 lst 4\n",
            ilab, x_lo, oval_99cl1p);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%s\" jus left cen bot csize 1.2\n",
            ilab, x_lo, oval_99cl1p, "99%CL");
    ilab ++;

    // vertical lines
    double pos_y_print = y_up - (y_up - y_lo) * 0.05;
    double pos_x_shift_print = (x_up - x_lo) * 0.01;
        
    // line at chi2min
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 90.0 1.0 lst 4\n",
            ilab, xval_at_fcnmin, y_lo);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%.3e\" rot 90 jus right cen bot csize 1.2\n",
            ilab, xval_at_fcnmin - pos_x_shift_print, pos_y_print,  xval_at_fcnmin);
    ilab ++;

    // line at chi2min - 1 sigma
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 90.0 1.0 lst 4\n",
            ilab, xval_at_fcnmin + xval_terr_minus, y_lo);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%.3e\" rot 90 jus right cen bot csize 1.2\n",
            ilab, xval_at_fcnmin + xval_terr_minus - pos_x_shift_print, pos_y_print,
            xval_at_fcnmin  + xval_terr_minus);
    ilab ++;

    // line at chi2min + 1 sigma
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 90.0 1.0 lst 4\n",
            ilab, xval_at_fcnmin + xval_terr_plus, y_lo);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%.3e\" rot 90 jus right cen bot csize 1.2\n",
            ilab, xval_at_fcnmin + xval_terr_plus - pos_x_shift_print, pos_y_print,
            xval_at_fcnmin  + xval_terr_plus);
    ilab ++;

    fprintf(fp, "la rot\n");
    fprintf(fp, "la file\n");
    fprintf(fp, "time off\n");
    fprintf(fp, "la y fcn (chi2 or c-stat)\n");
    fprintf(fp, "la t %s\n", hist_data->GetTitle().c_str());
    fprintf(fp, "r x %.15e %.15e\n", x_lo, x_up);
    fprintf(fp, "r y %.15e %.15e\n", y_lo, y_up);
    fprintf(fp, "la x %s\n", title_xval.c_str());
  
    fclose(fp);
}


// plot N HistData in one qdp file
void MirQdpTool::MkQdpNhist(const HistData1d* const* const hist_arr, int nhist,
                            string qdpout, double offset_xval)
{
    string func_name = "HistData1d::MkQdpNhist()";
    int nwin = nhist;
    FILE* fp = fopen(qdpout.c_str(), "w");

    fprintf(fp, "skip sing\n");
    fprintf(fp, "\n");

    for(int ihist = 0; ihist < nhist - 1; ihist++){
        hist_arr[ihist]->PrintData(fp, "x,y", offset_xval);

        fprintf(fp, "\n");
        fprintf(fp, "no\n");
        fprintf(fp, "\n");
    }
    hist_arr[nhist - 1]->PrintData(fp, "x,y", offset_xval);
    fprintf(fp, "\n");

    
    double* x_lo = new double [nhist];
    double* x_up  = new double [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        hist_arr[ihist]->GetXRangeQdp(&x_lo[ihist], &x_up[ihist]);
    }
    double x_lo_common = TMath:: MinElement(nhist, x_lo);
    double x_up_common  = TMath:: MaxElement(nhist, x_up);

    double* y_lo = new double [nhist];
    double* y_up  = new double [nhist];    
    for(int ihist = 0; ihist < nhist; ihist++){
        hist_arr[ihist]->GetORangeQdp(&y_lo[ihist], &y_up[ihist]);
    }
  
    fprintf(fp, "\n");
    fprintf(fp, "p v\n");
    fprintf(fp, "lw 5\n");
    fprintf(fp, "la rot\n");
    fprintf(fp, "csize 1.2\n");

    int ilabel = 1;
    for(int iwin = 0; iwin < nwin; iwin++){
        fprintf(fp, "win %d\n", iwin + 1);
        if(nwin - 1 != iwin){
            fprintf(fp, "LAB  NX OFF\n");
        }
        fprintf(fp, "r y %.15e %.15e\n", y_lo[iwin], y_up[iwin]);
        if(y_lo[iwin] <= 0 && 0 <= y_up[iwin]){
            fprintf(fp, "la %d line 0.0 1.0 pos %.15e %.15e \" \" lst 4\n",
                    ilabel, x_lo_common - offset_xval, 0.0);
            ilabel ++;
        }
        fprintf(fp, "la y %s\n", hist_arr[iwin]->GetTitle().c_str());
    }
    fprintf(fp, "la x offset = %.10e\n", offset_xval);
    
    fprintf(fp, "win all\n");
    fprintf(fp, "r x %.15e %.15e\n", x_lo_common - offset_xval, x_up_common - offset_xval);
    fprintf(fp, "line on \n");
    
    fclose(fp);
}


void MirQdpTool::MkQdpProj(const MirFunc* const func, const double* const par,
                           double xval_lo, double xval_up, double yval_lo, double yval_up,
                           string outdir, string qdpout_head, string calc_mode,
                           int npoint_func,
                           string title_xval, string title_yval, string title_oval,
                           double offset_xval, double offset_yval, double offset_oval,
                           string scale_xval, string scale_yval, string scale_oval)
{
    int nbin_func_x = npoint_func;
    int nbin_func_y = npoint_func;
    HistData2d* h2d_func = new HistData2d;
    h2d_func->Init(nbin_func_x, xval_lo, xval_up,
                   nbin_func_y, yval_lo, yval_up);
    h2d_func->SetByFunc(func, par);

    HistData1d* h1d_func_projx = h2d_func->GenProjectX(0, h2d_func->GetNbinY() - 1,
                                                       calc_mode);
    HistData1d* h1d_func_projy = h2d_func->GenProjectY(0, h2d_func->GetNbinX() - 1,
                                                       calc_mode);
    string outqdp_projx = outdir + "/" + qdpout_head + "_projx.qdp";
    string outqdp_projy = outdir + "/" + qdpout_head + "_projy.qdp";

    MkQdp(h1d_func_projx, outqdp_projx, "x,y",
          title_xval, title_oval,
          offset_xval, offset_oval,
          scale_xval, scale_oval);
    MkQdp(h1d_func_projy, outqdp_projy, "x,y",
          title_yval, title_oval,
          offset_yval, offset_oval,
          scale_yval, scale_oval);

    delete h2d_func;    
    delete h1d_func_projx;
    delete h1d_func_projy;
}


void MirQdpTool::MkQdpProj(const MirFunc* const func, const double* const par,
                           double xval_lo, double xval_up, double yval_lo, double yval_up,
                           string outdir, string qdpout_head, string calc_mode,
                           int npoint_func,
                           const MirPlotConf* const plot_conf_projx,
                           const MirPlotConf* const plot_conf_projy)
{
    if(2 != plot_conf_projx->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf_projx->GetNdim() != 2");
        MPrintErr(msg);
        abort();
    }
    if(2 != plot_conf_projy->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf_projy->GetNdim() != 2");
        MPrintErr(msg);
        abort();
    }
    
    int nbin_func_x = npoint_func;
    int nbin_func_y = npoint_func;
    HistData2d* h2d_func = new HistData2d;
    h2d_func->Init(nbin_func_x, xval_lo, xval_up,
                   nbin_func_y, yval_lo, yval_up);
    h2d_func->SetByFunc(func, par);

    HistData1d* h1d_func_projx = h2d_func->GenProjectX(0, h2d_func->GetNbinY() - 1,
                                                       calc_mode);
    HistData1d* h1d_func_projy = h2d_func->GenProjectY(0, h2d_func->GetNbinX() - 1,
                                                       calc_mode);
    string outqdp_projx = outdir + "/" + qdpout_head + "_projx.qdp";
    string outqdp_projy = outdir + "/" + qdpout_head + "_projy.qdp";

    MkQdp(h1d_func_projx, outqdp_projx, "x,y",
          plot_conf_projx);
    MkQdp(h1d_func_projy, outqdp_projy, "x,y",
          plot_conf_projy);

    delete h2d_func;    
    delete h1d_func_projx;
    delete h1d_func_projy;
}


void MirQdpTool::MkQdpDiffProj(const HistDataSerr2d* const hist_data,
                               const MirFunc* const func, const double* const par,
                               string outdir, string qdpout_head,
                               string add_mode, string error_mode,
                               string title_xval,
                               string title_yval,
                               string title_oval,
                               double offset_xval,
                               double offset_yval,
                               double offset_oval,
                               string scale_xval,
                               string scale_yval,
                               string scale_oval)
{
    // add_mode  :   add, mean, integral
    // error_mode: gauss, poisson, zero
    HistDataSerr1d* h1d_projx = hist_data->GenProjectX(0, hist_data->GetNbinY() - 1,
                                                       add_mode, error_mode);
    HistDataSerr1d* h1d_projy = hist_data->GenProjectY(0, hist_data->GetNbinX() - 1,
                                                       add_mode, error_mode);
    long nbin_func_x = hist_data->GetNbinX();
    long nbin_func_y = hist_data->GetNbinY();    
    double xval_lo = hist_data->GetXvalLo();
    double xval_up = hist_data->GetXvalUp();
    double yval_lo = hist_data->GetYvalLo();
    double yval_up = hist_data->GetYvalUp();

    HistData2d* h2d_func = new HistData2d;
    h2d_func->Init(nbin_func_x, xval_lo, xval_up,
                   nbin_func_y, yval_lo, yval_up);

    h2d_func->SetByFunc(func, par);
    HistData1d* h1d_func_projx = h2d_func->GenProjectX(0, h2d_func->GetNbinY() - 1,
                                                       add_mode);
    HistData1d* h1d_func_projy = h2d_func->GenProjectY(0, h2d_func->GetNbinX() - 1,
                                                       add_mode);
    HistDataSerr1d* h1d_projx_res_val   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projx_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projx_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1(h1d_projx, h1d_func_projx,
                                h1d_projx_res_val);
    HistData1dOpe::GetResChiHd1(h1d_projx, h1d_func_projx,
                                h1d_projx_res_chi);
    HistData1dOpe::GetResRatioHd1(h1d_projx, h1d_func_projx,
                                  h1d_projx_res_ratio);

    HistDataSerr1d* h1d_projy_res_val   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projy_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projy_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1(h1d_projy, h1d_func_projy,
                                h1d_projy_res_val);
    HistData1dOpe::GetResChiHd1(h1d_projy, h1d_func_projy,
                                h1d_projy_res_chi);
    HistData1dOpe::GetResRatioHd1(h1d_projy, h1d_func_projy,
                                  h1d_projy_res_ratio);
    string format = "x,xe,y,ye";
    MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_val, 
              outdir + "/" + qdpout_head + "_projx_diff_val.qdp",
              format,
              title_xval, title_oval, "res_val",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");
    MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_val, 
              outdir + "/" + qdpout_head + "_projy_diff_val.qdp",
              format,
              title_yval, title_oval, "res_val",
              offset_yval, offset_oval, 0.0,
              scale_yval, scale_oval, "lin");

    if(0 < g_flag_verbose){
        MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_chi, 
                  outdir + "/" + qdpout_head + "_projx_diff_chi.qdp",
                  format,
                  title_xval, title_oval, "chi",
                  offset_xval, offset_oval, 0.0,
                  scale_xval, scale_oval, "lin");

        MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_ratio, 
                  outdir + "/" + qdpout_head + "_projx_diff_ratio.qdp",
                  format,
                  title_xval, title_oval, "ratio",
                  offset_xval, offset_oval, 0.0,
                  scale_xval, scale_oval, "lin");

        MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_chi, 
                  outdir + "/" + qdpout_head + "_projy_diff_chi.qdp",
                  format,
                  title_yval, title_oval, "chi",
                  offset_yval, offset_oval, 0.0,
                  scale_yval, scale_oval, "lin");

        MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_ratio, 
                  outdir + "/" + qdpout_head + "_projy_diff_ratio.qdp",
                  format,
                  title_yval, title_oval, "ratio",
                  offset_yval, offset_oval, 0.0,
                  scale_yval, scale_oval, "lin");
    }
    
    delete h1d_projx;
    delete h1d_projy;
    delete h2d_func;
    delete h1d_func_projx;
    delete h1d_func_projy;
    delete h1d_projx_res_val;
    delete h1d_projx_res_chi;
    delete h1d_projx_res_ratio;
    delete h1d_projy_res_val;
    delete h1d_projy_res_chi;
    delete h1d_projy_res_ratio;
}



void MirQdpTool::MkQdpDiffProj(const HistDataSerr2d* const hist_data,
                               const MirFunc* const func, const double* const par,
                               string outdir, string qdpout_head,
                               string add_mode, string error_mode,
                               const MirPlotConf* const plot_conf_projx,
                               const MirPlotConf* const plot_conf_projy)
{
    if(5 != plot_conf_projx->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf_projx->GetNdim() != 5");
        MPrintErr(msg);
        abort();
    }
    if(5 != plot_conf_projy->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf_projy->GetNdim() != 5");
        MPrintErr(msg);
        abort();
    }
   
    // add_mode  :   add, mean, integral
    // error_mode: gauss, poisson, zero
    HistDataSerr1d* h1d_projx = hist_data->GenProjectX(0, hist_data->GetNbinY() - 1,
                                                       add_mode, error_mode);
    HistDataSerr1d* h1d_projy = hist_data->GenProjectY(0, hist_data->GetNbinX() - 1,
                                                       add_mode, error_mode);
    long nbin_func_x = hist_data->GetNbinX();
    long nbin_func_y = hist_data->GetNbinY();    
    double xval_lo = hist_data->GetXvalLo();
    double xval_up = hist_data->GetXvalUp();
    double yval_lo = hist_data->GetYvalLo();
    double yval_up = hist_data->GetYvalUp();

    HistData2d* h2d_func = new HistData2d;
    h2d_func->Init(nbin_func_x, xval_lo, xval_up,
                   nbin_func_y, yval_lo, yval_up);

    h2d_func->SetByFunc(func, par);
    HistData1d* h1d_func_projx = h2d_func->GenProjectX(0, h2d_func->GetNbinY() - 1,
                                                       add_mode);
    HistData1d* h1d_func_projy = h2d_func->GenProjectY(0, h2d_func->GetNbinX() - 1,
                                                       add_mode);
    HistDataSerr1d* h1d_projx_res_val   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projx_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projx_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1(h1d_projx, h1d_func_projx,
                                h1d_projx_res_val);
    HistData1dOpe::GetResChiHd1(h1d_projx, h1d_func_projx,
                                h1d_projx_res_chi);
    HistData1dOpe::GetResRatioHd1(h1d_projx, h1d_func_projx,
                                  h1d_projx_res_ratio);

    HistDataSerr1d* h1d_projy_res_val   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projy_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projy_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1(h1d_projy, h1d_func_projy,
                                h1d_projy_res_val);
    HistData1dOpe::GetResChiHd1(h1d_projy, h1d_func_projy,
                                h1d_projy_res_chi);
    HistData1dOpe::GetResRatioHd1(h1d_projy, h1d_func_projy,
                                  h1d_projy_res_ratio);

    MirPlotConf* plot_conf_val_projx   = NULL;
    MirPlotConf* plot_conf_chi_projx   = NULL;
    MirPlotConf* plot_conf_ratio_projx = NULL;
    MirPlotConf* plot_conf_val_projy   = NULL;
    MirPlotConf* plot_conf_chi_projy   = NULL;
    MirPlotConf* plot_conf_ratio_projy = NULL;
    MirPlotConf::GenPlotConf3(plot_conf_projx,
                              &plot_conf_val_projx,
                              &plot_conf_chi_projx,
                              &plot_conf_ratio_projx);
    MirPlotConf::GenPlotConf3(plot_conf_projy,
                              &plot_conf_val_projy,
                              &plot_conf_chi_projy,
                              &plot_conf_ratio_projy);    
    
    string format = "x,xe,y,ye";
    MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_val, 
              outdir + "/" + qdpout_head + "_projx_diff_val.qdp",
              format,
              plot_conf_val_projx);
    MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_val, 
              outdir + "/" + qdpout_head + "_projy_diff_val.qdp",
              format,
              plot_conf_val_projy);

    if(0 < g_flag_verbose){
        MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_chi, 
                  outdir + "/" + qdpout_head + "_projx_diff_chi.qdp",
                  format,
                  plot_conf_chi_projx);

        MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_ratio, 
                  outdir + "/" + qdpout_head + "_projx_diff_ratio.qdp",
                  format,
                  plot_conf_ratio_projx);

        MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_chi, 
                  outdir + "/" + qdpout_head + "_projy_diff_chi.qdp",
                  format,
                  plot_conf_chi_projy);

        MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_ratio, 
                  outdir + "/" + qdpout_head + "_projy_diff_ratio.qdp",
                  format,
                  plot_conf_ratio_projy);
    }
    
    delete h1d_projx;
    delete h1d_projy;
    delete h2d_func;
    delete h1d_func_projx;
    delete h1d_func_projy;
    delete h1d_projx_res_val;
    delete h1d_projx_res_chi;
    delete h1d_projx_res_ratio;
    delete h1d_projy_res_val;
    delete h1d_projy_res_chi;
    delete h1d_projy_res_ratio;
    delete plot_conf_val_projx;
    delete plot_conf_chi_projx;
    delete plot_conf_ratio_projx;
    delete plot_conf_val_projy;
    delete plot_conf_chi_projy;
    delete plot_conf_ratio_projy;
}


//
// contour
//

void MirQdpTool::MkQdpCont(const HistData2d* const h2d,
                           string qdpout, int ncont,
                           string title_xval,
                           string title_yval,
                           string title_oval,
                           double offset_xval,
                           double offset_yval,
                           double offset_oval)
{
    long nbin_xval = h2d->GetNbinX();
    long nbin_yval = h2d->GetNbinY();
    double xval_lo = h2d->GetXvalLo();
    double xval_up = h2d->GetXvalUp();
    double yval_lo = h2d->GetYvalLo();
    double yval_up = h2d->GetYvalUp();
    
    double xval_step = (xval_up - xval_lo)/ nbin_xval;
    double yval_step = (yval_up - yval_lo)/ nbin_yval;

    double xval_lo_qdpcont = xval_lo + 0.5 * xval_step;
    double xval_up_qdpcont = xval_up - 0.5 * xval_step;
    double yval_lo_qdpcont = yval_lo + 0.5 * yval_step;    
    double yval_up_qdpcont = yval_up - 0.5 * yval_step;

    double xval_lo_qdpcont_new = xval_lo_qdpcont - offset_xval;
    double xval_up_qdpcont_new = xval_up_qdpcont - offset_xval;
    double yval_lo_qdpcont_new = yval_lo_qdpcont - offset_yval;
    double yval_up_qdpcont_new = yval_up_qdpcont - offset_yval;

  
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "\n");
    for(long index_xval = 0; index_xval < nbin_xval; index_xval++){
        for(long index_yval = 0; index_yval < nbin_yval - 1; index_yval++){
            fprintf(fp, "  %e ", h2d->GetOvalElm(index_xval, index_yval) - offset_oval);
        }
        fprintf(fp, "  %e\n", h2d->GetOvalElm(index_xval, nbin_yval - 1) - offset_oval);
    }
  
    fprintf(fp, "\n");
    fprintf(fp, "COlor OFf 1..999\n");
    fprintf(fp, "xax lin  %.5e  %.5e\n", xval_lo_qdpcont_new, xval_step);
    fprintf(fp, "yax lin  %.5e  %.5e\n", yval_lo_qdpcont_new, yval_step);
  
    fprintf(fp, "\n");
    fprintf(fp, "lw 5\n");
    fprintf(fp, "la rot \n");
    fprintf(fp, "la pos y 2.5\n");
    fprintf(fp, "grid on\n");
    fprintf(fp, "lst 4 on grid\n");
    
    double zval_min = h2d->GetOvalArr()->GetValMin();
    double zval_max = h2d->GetOvalArr()->GetValMax();
    double zval_range = zval_max - zval_min;
    zval_min = zval_min - zval_range * 0.1;
    zval_max = zval_max + zval_range * 0.1;
    double zstep = (zval_max - zval_min) / ncont;

    fprintf(fp, "ima min %.5e max %.5e cct 2 cb\n", zval_min, zval_max);
    
    double* cont_level_arr = new double [ncont];
    for(int icont = 0; icont < ncont; icont++){
        cont_level_arr[icont] = zval_min + (icont + 0.5) * zstep;
    }

    fprintf(fp, "DG     1       1      1     %ld     %ld\n",  nbin_xval, nbin_yval);

    char cmd_cont[1000];
    char cmd_col[1000];
    char cmd_lst[1000];
    char cmd_lw[1000];
    sprintf(cmd_cont, "CONT  1 LEVEL ");
    sprintf(cmd_col, "CONT  1 COLOR ");
    sprintf(cmd_lst, "CONT  1 LSTYL ");
    sprintf(cmd_lw, "CONT  1 LWID ");
    for(int icont = 0; icont < ncont; icont++){
        sprintf(cmd_cont, "%s  %.15e  ", cmd_cont, cont_level_arr[icont]);
        sprintf(cmd_col,  "%s  %d  ", cmd_col, icont + 1);
        sprintf(cmd_lst,  "%s  %d  ", cmd_lst, 1);
        sprintf(cmd_lw,   "%s  %d  ", cmd_lw,  5);
    }
    fprintf(fp, "%s\n", cmd_cont);
    fprintf(fp, "%s\n", cmd_col);
    fprintf(fp, "%s\n", cmd_lst);
    fprintf(fp, "%s\n", cmd_lw);
    fprintf(fp, "r x %.5e %.5e\n", xval_lo_qdpcont_new, xval_up_qdpcont_new);
    fprintf(fp, "r y %.5e %.5e\n", yval_lo_qdpcont_new, yval_up_qdpcont_new);
    fprintf(fp, "la x %s (offset = %.5e)\n", title_xval.c_str(), offset_xval);
    fprintf(fp, "la y %s (offset = %.5e)\n", title_yval.c_str(), offset_yval);
    fprintf(fp, "la file\n");
    fprintf(fp, "time off\n");

    delete [] cont_level_arr;
  
    fclose(fp);
}


void MirQdpTool::MkQdpContMinFcn(const HistData2d* const h2d,
                                 string qdpout,
                                 string title_xval,
                                 string title_yval,
                                 string title_oval,
                                 double offset_xval,
                                 double offset_yval,
                                 double offset_oval)
{
    double zval_best = h2d->GetOvalArr()->GetValMin();
    double xval_best, yval_best;
    h2d->GetBinCenterXYFromIbin(h2d->GetOvalArr()->GetLocValMin(), &xval_best, &yval_best);
    MkQdpContMinFcnWithBest(h2d, qdpout,
                            xval_best, yval_best, zval_best,
                            title_xval, title_yval, title_oval,
                            offset_xval, offset_yval, offset_oval);
}

void MirQdpTool::MkQdpContMinFcnWithBest(const HistData2d* const h2d,
                                         string qdpout,
                                         double xval_best,
                                         double yval_best,
                                         double zval_best,
                                         string title_xval,
                                         string title_yval,
                                         string title_oval,
                                         double offset_xval,
                                         double offset_yval,
                                         double offset_oval)
{
    long nbin_xval = h2d->GetNbinX();
    long nbin_yval = h2d->GetNbinY();
    double xval_lo = h2d->GetXvalLo();
    double xval_up = h2d->GetXvalUp();
    double yval_lo = h2d->GetYvalLo();
    double yval_up = h2d->GetYvalUp();    

    double xval_step = (xval_up - xval_lo)/ nbin_xval;
    double yval_step = (yval_up - yval_lo)/ nbin_yval;

    double xval_lo_qdpcont = xval_lo + 0.5 * xval_step;
    double yval_lo_qdpcont = yval_lo + 0.5 * yval_step;
    double xval_up_qdpcont = xval_up - 0.5 * xval_step;
    double yval_up_qdpcont = yval_up - 0.5 * yval_step;

    double xval_range = xval_up_qdpcont - xval_lo_qdpcont;
    double yval_range = yval_up_qdpcont - yval_lo_qdpcont;

    double xval_lo_qdpcont_new = xval_lo_qdpcont - offset_xval;
    double xval_up_qdpcont_new = xval_up_qdpcont - offset_xval;
    double yval_lo_qdpcont_new = yval_lo_qdpcont - offset_yval;
    double yval_up_qdpcont_new = yval_up_qdpcont - offset_yval;

  
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "\n");
    for(long index_xval = 0; index_xval < nbin_xval; index_xval++){
        for(long index_yval = 0; index_yval < nbin_yval - 1; index_yval++){
            fprintf(fp, "  %.5e ", h2d->GetOvalElm(index_xval, index_yval) - offset_oval);
        }
        fprintf(fp, "  %.5e\n", h2d->GetOvalElm(index_xval, nbin_yval - 1) - offset_oval);
    }

    fprintf(fp, "\n");
    fprintf(fp, "COlor OFf 1..999\n");
    fprintf(fp, "xax lin  %.5e  %.5e\n", xval_lo_qdpcont_new, xval_step);
    fprintf(fp, "yax lin  %.5e  %.5e\n", yval_lo_qdpcont_new, yval_step);
  
    fprintf(fp, "\n");
    fprintf(fp, "lw 5\n");
    fprintf(fp, "la rot \n");
    fprintf(fp, "la pos y 2.5\n");

    double xval_at_zmin = xval_best;
    double yval_at_zmin = yval_best;
    double zmin = zval_best;

    double xval_at_zmin_new = xval_at_zmin - offset_xval;
    double yval_at_zmin_new = yval_at_zmin - offset_yval;
    double zmin_new = zmin - offset_oval;
  
    double cont_level_0 = zmin_new + MirMath::GetUpMinfcn(1.0, "sigma", 1);
    double cont_level_1 = zmin_new + MirMath::GetUpMinfcn(0.900, "cl", 1);
    double cont_level_2 = zmin_new + MirMath::GetUpMinfcn(0.900, "cl", 2);

    fprintf(fp, "DG     1       1      1     %ld     %ld\n",  nbin_xval, nbin_yval);
    fprintf(fp, "CONT  1 LEVEL  %.5e   %.5e   %.5e\n",
            cont_level_0, cont_level_1, cont_level_2);
    fprintf(fp, "CONT  1 COLOR       1       2       3\n");
    fprintf(fp, "CONT  1 LSTYL       1       1       1\n");
    fprintf(fp, "CONT  1 LWID        5       5       5\n");

    fprintf(fp, "lab 1 pos %.5e %.5e \"+\"\n", xval_at_zmin_new, yval_at_zmin_new);
    fprintf(fp, "LAB 2 csize 1.0 CEN Top JUS Lef\n");
    fprintf(fp, "LAB 2 POS %.5e %.5e \"\\gx\\u2\\d\\dmin\\u = %.5e @ (%.2e, %.2e)\"\n",
            xval_lo_qdpcont_new + xval_range * 0.05,
            yval_lo_qdpcont_new + yval_range * 0.95,
            zmin_new, xval_at_zmin, yval_at_zmin);
    fprintf(fp, "LAB 3 csize 1.0 CEN Top JUS Lef\n");
    fprintf(fp, "LAB 3 POS %.5e %.5e \"\\gD\\gx\\u2\\d = %.2e (1\\gs: 1 par)\"\n",
            xval_lo_qdpcont_new + xval_range * 0.05,
            yval_lo_qdpcont_new + yval_range * 0.90,
            cont_level_0 - zmin_new);
    fprintf(fp, "LAB 4 csize 1.0 CEN Top JUS Lef\n");
    fprintf(fp, "LAB 4 POS %.5e %.5e \"\\gD\\gx\\u2\\d = %.2e (90%%CL: 1 par)\"\n",
            xval_lo_qdpcont_new + xval_range * 0.05,
            yval_lo_qdpcont_new + yval_range * 0.85,
            cont_level_1 - zmin_new);  
    fprintf(fp, "LAB 5 csize 1.0 CEN Top JUS Lef\n");
    fprintf(fp, "LAB 5 POS %.5e %.5e \"\\gD\\gx\\u2\\d = %.2e (90%%CL: 2 par)\"\n",
            xval_lo_qdpcont_new + xval_range * 0.05,
            yval_lo_qdpcont_new + yval_range * 0.80,
            cont_level_2 - zmin_new);  

    fprintf(fp, "r x %.5e %.5e\n", xval_lo_qdpcont_new, xval_up_qdpcont_new);
    fprintf(fp, "r y %.5e %.5e\n", yval_lo_qdpcont_new, yval_up_qdpcont_new);
    fprintf(fp, "la x %s\n", title_xval.c_str());
    fprintf(fp, "la y %s\n", title_oval.c_str());
  
    fclose(fp);
}
