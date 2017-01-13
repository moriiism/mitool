#include "mir_label_conf.h"

// public

void MirLabelConf::Init(long nlabel)
{
    Null();

    nlabel_ = nlabel;
    xval_ = new double [nlabel];
    yval_ = new double [nlabel];
    line_style_ = new int [nlabel];
    line_color_ = new int [nlabel];
    label_size_ = new double [nlabel];
    label_ = new string [nlabel];
    
    for(long ilabel = 0; ilabel < nlabel_; ilabel ++){
        xval_[ilabel] = 0.0;
        yval_[ilabel] = 0.0;
        line_style_[ilabel] = 0;
        line_color_[ilabel] = 0;
        label_size_[ilabel] = 0.0;
        label_[ilabel] = "";
    }
}

void MirLabelConf::Load(string file)
{
    Null();

    string* line_arr = NULL;
    long nlabel = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &nlabel);
    Init(nlabel);
    for(long ilabel = 0; ilabel < nlabel; ilabel ++){
        int ncolumn = MirStr::GetNcolumn(line_arr[ilabel]);
        if(5 >  ncolumn){
            MPrintWarnClass("ncolumn < 5");
        }
        sscanf(line_arr[ilabel].c_str(), "%lf  %lf  %d  %d  %lf",
               &xval_[ilabel], &yval_[ilabel],
               &line_style_[ilabel], &line_color_[ilabel],
               &label_size_[ilabel]);
        string line_str = line_arr[ilabel];
        int ipos_delim = line_str.find("!");
        label_[ilabel] = line_str.substr(ipos_delim + 1);
    }
    MirIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void MirLabelConf::Print() const
{
    printf("%s: nlabel = %d\n", GetClassName().c_str(), nlabel_);
    for(int ilabel = 0; ilabel < nlabel_; ilabel ++){
        printf("%s: xval_[%d] = %e\n",
               GetClassName().c_str(), ilabel, xval_[ilabel]);
        printf("%s: yval_[%d] = %e\n",
               GetClassName().c_str(), ilabel, yval_[ilabel]);
        printf("%s: line_style_[%d] = %d\n",
               GetClassName().c_str(), ilabel, line_style_[ilabel]);
        printf("%s: line_color_[%d] = %d\n",
               GetClassName().c_str(), ilabel, line_color_[ilabel]);
        printf("%s: label_size_[%d] = %e\n",
               GetClassName().c_str(), ilabel, label_size_[ilabel]);
        printf("%s: label_[%d] = %s\n",
               GetClassName().c_str(), ilabel, label_[ilabel].c_str());
    }
}


// private

void MirLabelConf::Null()
{
    nlabel_ = 0;
    if(NULL != xval_) {delete [] xval_; xval_ = NULL;}
    if(NULL != yval_) {delete [] yval_; yval_ = NULL;}
    if(NULL != line_style_) {delete [] line_style_; line_style_ = NULL;}
    if(NULL != line_color_) {delete [] line_color_; line_color_ = NULL;}
    if(NULL != label_size_) {delete [] label_size_; label_size_ = NULL;}
    if(NULL != label_) {delete [] label_; label_ = NULL;}
}

