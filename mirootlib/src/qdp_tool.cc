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
    fprintf(fp, "loc 0.05 0.05 0.95 0.95\n");
    fprintf(fp, "la pos y 3.0\n");
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
        sprintf(cmd, "la %s %s (offset = %.5e)",
                xy.c_str(), title.c_str(), offset);
    }
    fprintf(fp, "%s\n", cmd);
}

void MirQdpTool::PrintQdpScale(FILE* fp, string xy, string scale)
{
    if("log" == scale){
        fprintf(fp, "log   %s  on\n",
                xy.c_str());
    } else if("lin" == scale){
        fprintf(fp, "log   %s  off\n",
                xy.c_str());
    } else {
        abort();
    }
}

void MirQdpTool::PrintQdpCmdDiffPlot(FILE* fp,
                                     double xval_lo_data, double xval_up_data,
                                     double oval_lo_w1_data, double oval_up_w1_data,
                                     double oval_lo_w2_data, double oval_up_w2_data,
                                     double offset_xval,
                                     double offset_oval,
                                     double offset_oval_res,
                                     string title_xval,
                                     string title_oval,
                                     string title_oval_res,
                                     string scale_xval,
                                     string scale_oval,
                                     string scale_oval_res)
{
    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo_w1 = 0.0;
    double oval_up_w1 = 0.0;
    double oval_lo_w2 = 0.0;
    double oval_up_w2 = 0.0;
    GetRangeQdp(xval_lo_data,
                xval_up_data,
                &xval_lo, &xval_up);
    GetRangeQdp(oval_lo_w1_data,
                oval_up_w1_data,
                &oval_lo_w1, &oval_up_w1);
    GetRangeQdp(oval_lo_w2_data,
                oval_up_w2_data,
                &oval_lo_w2, &oval_up_w2);        
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_w1_shifted = oval_lo_w1 - offset_oval;
    double oval_up_w1_shifted = oval_up_w1 - offset_oval;
    double oval_lo_w2_shifted = oval_lo_w2 - offset_oval_res;
    double oval_up_w2_shifted = oval_up_w2 - offset_oval_res;
    
    PrintQdpCmdStd(fp);
    fprintf(fp, "win 1\n");
    fprintf(fp, "LOC  0.05 0.3 0.95 0.9\n");
    fprintf(fp, "LAB  NX OFF\n");
    fprintf(fp, "yplot 1 2\n");
    fprintf(fp, "line st on 2\n");
    fprintf(fp, "la pos y 3.0\n");    
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);    
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w1_shifted, oval_up_w1_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);    

    fprintf(fp, "win 2\n");
    fprintf(fp, "LOC  0.05 0.1 0.95 0.39\n");
    fprintf(fp, "yplot 3\n");
    fprintf(fp, "la pos y 3.0\n");    
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval_res, offset_oval_res);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w2_shifted, oval_up_w2_shifted);
    PrintQdpScale(fp, "y", scale_oval_res);        
    
    fprintf(fp, "mark 22 on 1 3\n");
    fprintf(fp, "la 1 line 0.0 1.0 pos %.15e %.15e \" \" lst 4\n",
            xval_lo_shifted, 0.0);
}


void MirQdpTool::PrintQdpCmdDiffPlot(FILE* fp,
                                     double xval_lo_data, double xval_up_data,
                                     double oval_lo_w1_data, double oval_up_w1_data,
                                     double oval_lo_w2_data, double oval_up_w2_data,
                                     double offset_xval,
                                     double offset_oval,
                                     double offset_oval_res,
                                     const MirPlotConf* const plot_conf)
{
    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo_w1 = 0.0;
    double oval_up_w1 = 0.0;
    double oval_lo_w2 = 0.0;
    double oval_up_w2 = 0.0;
    GetRangeQdp(xval_lo_data,
                xval_up_data,
                &xval_lo, &xval_up);
    GetRangeQdp(oval_lo_w1_data,
                oval_up_w1_data,
                &oval_lo_w1, &oval_up_w1);
    GetRangeQdp(oval_lo_w2_data,
                oval_up_w2_data,
                &oval_lo_w2, &oval_up_w2);        
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

    string title_xval = plot_conf->GetLabelElm(0);
    string title_oval = plot_conf->GetLabelElm(1);
    string title_oval_res = plot_conf->GetLabelElm(2);
    string scale_xval = plot_conf->GetScaleElm(0);
    string scale_oval = plot_conf->GetScaleElm(1);
    string scale_oval_res = plot_conf->GetScaleElm(2);
    
    PrintQdpCmdStd(fp);
    fprintf(fp, "win 1\n");
    fprintf(fp, "LOC  0.05 0.3 0.95 0.9\n");
    fprintf(fp, "LAB  NX OFF\n");
    fprintf(fp, "yplot 1 2\n");
    fprintf(fp, "line st on 2\n");
    fprintf(fp, "la pos y 3.0\n");    
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);    
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w1_shifted, oval_up_w1_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);    

    fprintf(fp, "win 2\n");
    fprintf(fp, "LOC  0.05 0.1 0.95 0.39\n");
    fprintf(fp, "yplot 3\n");
    fprintf(fp, "la pos y 3.0\n");    
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval_res, offset_oval_res);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w2_shifted, oval_up_w2_shifted);
    PrintQdpScale(fp, "y", scale_oval_res);        
    
    fprintf(fp, "mark 22 on 1 3\n");
    fprintf(fp, "la 1 line 0.0 1.0 pos %.15e %.15e \" \" lst 4\n",
            xval_lo_shifted, 0.0);
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
    if("DataArrayNerr1d" == data_array->GetClassName()){
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

    GetRangeQdp(0.0, data_array->GetNdata(),
                &xval_lo, &xval_up);
    GetRangeQdp(data_array->GetValAndErrMin(),
                data_array->GetValAndErrMax(),
                &oval_lo, &oval_up);
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;

    PrintQdpCmdStd(fp);
    fprintf(fp, "ma 6 on\n");
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
    if("DataArrayNerr1d" == data_array->GetClassName()){
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
    // offset_xval must be "no"
    if("no" !=  plot_conf->GetOffsetTagElm(0) ){
        char msg[kLineSize];
        sprintf(msg, "offset_xval must be zero. Then, set offset_xval = no.");
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
    GetRangeQdp(0.0, data_array->GetNdata(),
                &xval_lo, &xval_up);
    GetRangeQdp(data_array->GetValAndErrMin(),
                data_array->GetValAndErrMax(),
                &oval_lo, &oval_up);
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
    fprintf(fp, "ma 6 on\n");    
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
    if("DataArrayNerr1d" == data_array->GetClassName()){
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
    GetRangeQdp(0.0, data_array->GetNdata(),
                &xval_lo, &xval_up);
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;

    PrintQdpCmdStd(fp);
    fprintf(fp, "ma 6 on\n");
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
    if("DataArrayNerr1d" == data_array->GetClassName()){
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
    // offset_oval must be "no"
    if("no" !=  plot_conf->GetOffsetTagElm(1) ){
        char msg[kLineSize];
        sprintf(msg, "offset_oval must be zero. Then, set offset_oval = no.");
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
    GetRangeQdp(0.0, data_array->GetNdata(),
                &xval_lo, &xval_up);    
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
    fprintf(fp, "ma 6 on\n");    
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
                       string scale_oval,
                       int flag_line,
                       int flag_mark)
{
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    PrintQdpRead(fp, format);

    graph_data->PrintData(fp, format, offset_xval, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    GetRangeQdp(graph_data->GetXvalArr()->GetValAndErrMin(),
                graph_data->GetXvalArr()->GetValAndErrMax(),
                &xval_lo, &xval_up);
    GetRangeQdp(graph_data->GetOvalArr()->GetValAndErrMin(),
                graph_data->GetOvalArr()->GetValAndErrMax(),
                &oval_lo, &oval_up);    
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;
    
    PrintQdpCmdStd(fp);
    if(1 == flag_line){
        fprintf(fp, "line on\n");
    }
    if(1 == flag_mark){
        fprintf(fp, "ma 6 on\n");
    }
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
                       const MirPlotConf* const plot_conf,
                       int flag_line,
                       int flag_mark)
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
    GetRangeQdp(graph_data->GetXvalArr()->GetValAndErrMin(),
                graph_data->GetXvalArr()->GetValAndErrMax(),
                &xval_lo, &xval_up);
    GetRangeQdp(graph_data->GetOvalArr()->GetValAndErrMin(),
                graph_data->GetOvalArr()->GetValAndErrMax(),
                &oval_lo, &oval_up);    
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
    if(1 == flag_line){
        fprintf(fp, "line on\n");
    }
    if(1 == flag_mark){
        fprintf(fp, "ma 6 on\n");
    }
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
        if("HistDataNerr1d" == hist_data->GetClassName()){
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
    GetRangeQdp(hist_data->GetXvalLo(),
                hist_data->GetXvalUp(),
                &xval_lo, &xval_up);
    GetRangeQdp(hist_data->GetOvalArr()->GetValAndErrMin(),
                hist_data->GetOvalArr()->GetValAndErrMax(),
                &oval_lo, &oval_up);    
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;

    PrintQdpCmdStd(fp);
    fprintf(fp, "line st\n");
    fprintf(fp, "ma 6 on\n");
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
        if("HistDataNerr1d" == hist_data->GetClassName()){
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
    GetRangeQdp(hist_data->GetXvalLo(),
                hist_data->GetXvalUp(),
                &xval_lo, &xval_up);
    GetRangeQdp(hist_data->GetOvalArr()->GetValAndErrMin(),
                hist_data->GetOvalArr()->GetValAndErrMax(),
                &oval_lo, &oval_up);    
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
    fprintf(fp, "line st\n");
    fprintf(fp, "ma 6 on\n");    
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
    GraphDataNerr2d* gd2d = new GraphDataNerr2d;
    gd2d->InitSetByFunc(func, par, npoint, xval_lo, xval_up, scale_xval);
    MkQdp(gd2d, outqdp, "x,y",
          title_xval, title_oval,
          offset_xval, offset_oval,
          scale_xval, scale_oval, 1, 0);
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
    GraphDataNerr2d* gd2d = new GraphDataNerr2d;
    gd2d->InitSetByFunc(func, par, npoint, xval_lo, xval_up, plot_conf->GetScaleElm(0));
    MkQdp(gd2d, outqdp, "x,y", plot_conf, 1, 0);
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
    GraphDataNerr2d* gd2d = new GraphDataNerr2d;
    gd2d->Init(xval_vec.size());
    gd2d->SetXvalArr(xval_vec);
    gd2d->SetOvalArr(oval_vec);
    gd2d->SetFlagXvalSorted(0);

    string title_oval = "GTI";
    double offset_oval = 0.0;
    MkQdp(gd2d, qdpout, "x,y",
          title_xval, title_oval,
          offset_xval, offset_oval,
          scale_xval, "lin",
          1, 0);
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
    GraphDataNerr2d* gd2d = new GraphDataNerr2d;
    gd2d->Init(xval_vec.size());
    gd2d->SetXvalArr(xval_vec);
    gd2d->SetOvalArr(oval_vec);
    gd2d->SetFlagXvalSorted(0);
    MkQdp(gd2d, qdpout, "x,y", plot_conf, 1, 0);
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

    PrintQdpCmdDiffPlot(fp,
                        graph_data->GetXvalArr()->GetValAndErrMin(),
                        graph_data->GetXvalArr()->GetValAndErrMax(),
                        graph_data->GetOvalArr()->GetValAndErrMin(),
                        graph_data->GetOvalArr()->GetValAndErrMax(),
                        graph_res->GetOvalArr()->GetValAndErrMin(),
                        graph_res->GetOvalArr()->GetValAndErrMax(),
                        offset_xval, offset_oval, offset_oval_res,                        
                        title_xval, title_oval, title_oval_res,
                        scale_xval, scale_oval, scale_oval_res);
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

    PrintQdpCmdDiffPlot(fp,
                        graph_data->GetXvalArr()->GetValAndErrMin(),
                        graph_data->GetXvalArr()->GetValAndErrMax(),
                        graph_data->GetOvalArr()->GetValAndErrMin(),
                        graph_data->GetOvalArr()->GetValAndErrMax(),
                        graph_res->GetOvalArr()->GetValAndErrMin(),
                        graph_res->GetOvalArr()->GetValAndErrMax(),
                        offset_xval, offset_oval, offset_oval_res,
                        plot_conf);
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

    PrintQdpCmdDiffPlot(fp,
                        hist_data->GetXvalLo(),
                        hist_data->GetXvalUp(),
                        hist_data->GetOvalArr()->GetValAndErrMin(),
                        hist_data->GetOvalArr()->GetValAndErrMax(),
                        hist_res->GetOvalArr()->GetValAndErrMin(),
                        hist_res->GetOvalArr()->GetValAndErrMax(),
                        offset_xval, offset_oval, offset_oval_res,                        
                        title_xval, title_oval, title_oval_res,
                        scale_xval, scale_oval, scale_oval_res);
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

    PrintQdpCmdDiffPlot(fp,
                        hist_data->GetXvalLo(),
                        hist_data->GetXvalUp(),
                        hist_data->GetOvalArr()->GetValAndErrMin(),
                        hist_data->GetOvalArr()->GetValAndErrMax(),
                        hist_res->GetOvalArr()->GetValAndErrMin(),
                        hist_res->GetOvalArr()->GetValAndErrMax(),
                        offset_xval, offset_oval, offset_oval_res,
                        plot_conf);
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
        hist_arr[ihist]->PrintData(fp, "x,y", offset_xval, 0.0);

        fprintf(fp, "\n");
        fprintf(fp, "no\n");
        fprintf(fp, "\n");
    }
    hist_arr[nhist - 1]->PrintData(fp, "x,y", offset_xval, 0.0);
    fprintf(fp, "\n");

    
    double* x_lo = new double [nhist];
    double* x_up  = new double [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        GetRangeQdp(hist_arr[ihist]->GetXvalLo(),
                    hist_arr[ihist]->GetXvalUp(),
                    &x_lo[ihist], &x_up[ihist]);
    }
    double x_lo_common = TMath:: MinElement(nhist, x_lo);
    double x_up_common  = TMath:: MaxElement(nhist, x_up);

    double* y_lo = new double [nhist];
    double* y_up  = new double [nhist];    
    for(int ihist = 0; ihist < nhist; ihist++){
        GetRangeQdp(hist_arr[ihist]->GetOvalArr()->GetValAndErrMin(),
                    hist_arr[ihist]->GetOvalArr()->GetValAndErrMax(),
                    &y_lo[ihist], &y_up[ihist]);    
    }
  
    fprintf(fp, "\n");
    fprintf(fp, "p v\n");
    fprintf(fp, "lw 5\n");
    fprintf(fp, "la rot\n");
    fprintf(fp, "csize 1.2\n");
    fprintf(fp, "line st\n");

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
