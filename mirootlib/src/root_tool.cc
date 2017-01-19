#include "mir_root_tool.h"

void MirRootTool::InitTApp()
{
    if(NULL != theApp_){
        delete theApp_; theApp_ = NULL;
    }
    theApp_ = new TApplication("theApp", 0, 0);
}

void MirRootTool::InitTCanvas(string type)
{
    string canvas_name = "mirtool";
    
    if(NULL != tcanvas_){
        delete tcanvas_; tcanvas_ = NULL;
    }
    tcanvas_ = new TCanvas(canvas_name.c_str(),
                           canvas_name.c_str());
    tcanvas_->SetLineWidth(2);

    gROOT->SetStyle("Plain");
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetCanvasBorderSize(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadBorderSize(0);
    gStyle->SetPadColor(0);
    gStyle->SetFrameBorderSize(0);
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameFillColor(0);
    gStyle->SetTitleFillColor(0);

    gStyle->SetTitleBorderSize(2);
    gStyle->SetOptStat(kFALSE);
    gStyle->SetOptFit(kFALSE);
    gStyle->SetOptTitle(0);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);

    gStyle->SetPalette(1);
    gStyle->SetTitleFontSize(0.06);
    gStyle->SetTitleSize(0.06, "T");

    tcanvas_->SetLineWidth(2);
    tcanvas_->SetLeftMargin(0.2);
    tcanvas_->SetRightMargin(0.15);
    tcanvas_->SetBottomMargin(0.15);
    tcanvas_->SetTickx(1);
    tcanvas_->SetTicky(1);
    tcanvas_->SetBorderMode(0);
    tcanvas_->SetBorderSize(0);
    tcanvas_->SetFillColor(0);

    // TPaletteAxis *palette = new TPaletteAxis(2.156863,-2,2.392157,2,cont00_HistData2d);
    
    if("def" == type){
        gROOT->SetStyle("Default");
        gStyle->SetCanvasBorderMode(0);
        gStyle->SetCanvasBorderSize(0);
        gStyle->SetCanvasColor(0);

        gStyle->SetPadBorderMode(0);
        gStyle->SetPadBorderSize(0);
        gStyle->SetPadColor(0);

        gStyle->SetFrameBorderSize(0);
        gStyle->SetFrameBorderMode(0);
        gStyle->SetFrameFillColor(0);

        gStyle->SetTitleFillColor(0);

        gStyle->SetOptFit(1); // default = "111"
        gStyle->SetOptTitle(1);

        gStyle->SetFillColor(0);
        gStyle->SetPalette(1);
    } else if ("std" == type){
        gStyle->SetOptTitle(1);
        gStyle->SetPalette(1);
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(0111); //draw without chi2
    } else if ("pub" == type){

        //gROOT->SetStyle("Pub");
        //gROOT->SetStyle("Plain");
      
        //gStyle->SetFillColor(0);
        //gStyle->SetPalette(1);
        //gStyle->SetFillStyle(0);
        //  gStyle->SetFillColor(1);
        //  gStyle->SetFillStyle(1);
        //gStyle->SetLineWidth(2);
        // gStyle->SetLineStyle(2);

        //gStyle->SetPadTickX(1);
        //gStyle->SetPadTickY(1);

        printf("root_tool: pub\n");
        
    } else if ("detail" == type){

        //gROOT->SetStyle("Plain");
        //gROOT->SetStyle("Default");
        gStyle->SetLineWidth(2);

        gStyle->SetOptTitle(1);
    
        // void SetOptFit(Int_t fit = 1)
        // pcev
        //  p = 1;  print Probability
        //  c = 1;  print Chisquare/Number of degress of freedom
        //  e = 1;  print errors (if e=1, v must be 1)
        //  v = 1;  print name/values of parameters
        //   When "v"=1 is specified, only the non-fixed parameters are shown.
        //   When "v"=2 all parameters are shown.
    
        gStyle->SetOptFit(1112);

        // void SetOptStat(Int_t stat = 1)
        // ksiourmen  (default = 000001111)
        //  k = 1;  kurtosis printed
        //  k = 2;  kurtosis and kurtosis error printed
        //  s = 1;  skewness printed
        //  s = 2;  skewness and skewness error printed
        //  i = 1;  integral of bins printed
        //  o = 1;  number of overflows printed
        //  u = 1;  number of underflows printed
        //  r = 1;  rms printed
        //  r = 2;  rms and rms error printed
        //  m = 1;  mean value printed
        //  m = 2;  mean and mean error values printed
        //  e = 1;  number of entries printed
        //  n = 1;  name of histogram is printed
        gStyle->SetOptStat(221112211);

        //gStyle->SetStatFormat("6.6g");
        //gStyle->SetStripDecimals(kFALSE);
        //gStyle->SetEndErrorSize(0);


        //gStyle->SetFillColor(0);
//    gStyle->SetTextFont(132);
        //gStyle->SetOptStat(0);
        // gStyle->SetLabelFont(132, "XYZ");
//    gStyle->SetTitleFont(132, "xyz");
//    gStyle->SetTitleFont(132, "");
        //  gStyle->SetTitleBorderSize(0);
//    gStyle->SetTitleAlign(13);
//    gStyle->SetTextAlign(12);
//    gStyle->SetTitleX(0.09);
//    gStyle->SetTitleY(0.95);

        gStyle->SetPalette(1);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad root style (= %s).\n", type.c_str());
        MPrintErr(msg);
        abort();
    }

    gROOT->ForceStyle();
  
}

void MirRootTool::SetPlotConf(const MirPlotConf* const plot_conf)
{
    if("lin" == plot_conf->GetScaleElm(0)){
        gPad->SetLogx(0);
    } else if ("log" == plot_conf->GetScaleElm(0)){
        gPad->SetLogx(1);
    } else {
        //printf("error: %s: bad scale_elm(0) (=%s)\n",
        //       func_name.c_str(),
        //       plot_conf->GetScaleElm(0).c_str());
        exit(1);
    }

    if("lin" == plot_conf->GetScaleElm(1)){
        gPad->SetLogy(0);
    } else if ("log" == plot_conf->GetScaleElm(1)){
        gPad->SetLogy(1);
    } else {
        //printf("error: %s: bad scale_elm(1) (=%s)\n",
        //       func_name.c_str(),
        //       plot_conf->GetScaleElm(1).c_str());
        exit(1);
    }

    TH1D* th1d_waku = new TH1D("waku", "waku",
                               1,
                               atof(plot_conf->GetLoStrElm(0).c_str()),
                               atof(plot_conf->GetUpStrElm(0).c_str()));

    th1d_waku->SetMinimum( atof( plot_conf->GetLoStrElm(1).c_str()) );
    th1d_waku->SetMaximum( atof( plot_conf->GetUpStrElm(1).c_str()) );
    th1d_waku->SetXTitle(plot_conf->GetLabelElm(0).c_str());
    th1d_waku->SetYTitle(plot_conf->GetLabelElm(1).c_str());

    th1d_waku->GetXaxis()->SetLabelSize(0.06);
    th1d_waku->GetXaxis()->SetLabelOffset(0.008);
    th1d_waku->GetXaxis()->SetTitleOffset(1.2);
    th1d_waku->GetXaxis()->SetTitleSize(0.06);

    th1d_waku->GetYaxis()->SetLabelSize(0.06);
    th1d_waku->GetYaxis()->SetLabelOffset(0.015);
    th1d_waku->GetYaxis()->SetTitleOffset(1.5);
    th1d_waku->GetYaxis()->SetTitleSize(0.06);
    
    th1d_waku->Draw();
}

void MirRootTool::InitSetTFile(string tfile_name)
{
    if(NULL != tfile_arr_){
        for(int ifile = 0; ifile < GetNfile(); ifile ++){
            if(NULL != tfile_arr_[ifile]){
                delete tfile_arr_[ifile]; tfile_arr_[ifile] = NULL;
            }
        }
        delete [] tfile_arr_; tfile_arr_ = NULL;
    }
    nfile_ = 1;
    tfile_arr_ = new TFile* [1];
    for(int ifile = 0; ifile < nfile_; ifile ++){
        tfile_arr_[0] = new TFile(tfile_name.c_str());
    }
}

void MirRootTool::InitSetTFileArr(int nfile, const string* const tfile_name_arr)
{
    if(NULL != tfile_arr_){
        for(int ifile = 0; ifile < GetNfile(); ifile ++){
            if(NULL != tfile_arr_[ifile]){
                delete tfile_arr_[ifile]; tfile_arr_[ifile] = NULL;
            }
        }
        delete [] tfile_arr_; tfile_arr_ = NULL;
    }
    nfile_ = nfile;
    tfile_arr_ = new TFile* [nfile_];
    for(int ifile = 0; ifile < nfile_; ifile ++){
        tfile_arr_[ifile] = new TFile(tfile_name_arr[ifile].c_str());
    }
}

TFile* const MirRootTool::GetTFile() const
{
    if(1 != nfile_){
        MPrintErr("bad nfile_\n");
        abort();
    }
    return tfile_arr_[0];
}

TFile* const MirRootTool::GetTFileArrElm(int ifile) const
{
    return tfile_arr_[ifile];
}

TTree* const MirRootTool::GetEvtTree() const
{
    if(1 != nfile_){
        MPrintErr("bad nfile_\n");
        abort();
    }
    TTree* evtree = dynamic_cast<TTree*>( GetTFile()->Get("EVENTS") );
    return evtree;
}

TTree* const MirRootTool::GetEvtTreeArrElm(int ifile) const
{
    TTree* evtree = dynamic_cast<TTree*>( GetTFileArrElm(ifile)->Get("EVENTS") );
    return evtree;
}

int MirRootTool::GetFirstFromTree(TTree* const evtree, const char* const  key, double* const first_ptr)
{
    evtree->SetBranchStatus("*", 0);
    evtree->SetBranchStatus(key, 1);
    evtree->Draw(key);
    double first = evtree->GetHistogram()->GetXaxis()->GetXmin();

    evtree->SetBranchStatus("*", 1);
    *first_ptr = first;
    return kRetNormal;
}

int MirRootTool::GetLastFromTree(TTree* const evtree, const char* const key, double* const last_ptr)
{
    evtree->SetBranchStatus("*", 0);
    evtree->SetBranchStatus(key, 1);
    evtree->Draw(key);
    double last = evtree->GetHistogram()->GetXaxis()->GetXmax();
    evtree->SetBranchStatus("*", 1);
    *last_ptr = last;
    return kRetNormal;
}

int MirRootTool::GetMidFromTree(TTree* const evtree, const char* const key, double* const mid_ptr)
{
    evtree->SetBranchStatus("*", 0);
    evtree->SetBranchStatus(key, 1);
    evtree->Draw(key);
    double xmax = evtree->GetHistogram()->GetXaxis()->GetXmax();
    double xmin = evtree->GetHistogram()->GetXaxis()->GetXmin();

    evtree->SetBranchStatus("*", 1);
  
    double mid = (xmax + xmin)/2.;
    *mid_ptr = mid;
    return kRetNormal;
}


int MirRootTool::GetFirstFromTreeSel(TTree* const evtree, const char* const  key,
                                      const char* const select, double* const first_ptr)
{
    evtree->SetBranchStatus("*", 1);
    evtree->Draw(key, select);
    double first = evtree->GetHistogram()->GetXaxis()->GetXmin();
    *first_ptr = first;
    return kRetNormal;
}

int MirRootTool::GetLastFromTreeSel(TTree* const evtree, const char* const key,
                                     const char* const select, double* const last_ptr)
{
    evtree->SetBranchStatus("*", 1);
    evtree->Draw(key, select);
    evtree->Draw(key);
    double last = evtree->GetHistogram()->GetXaxis()->GetXmax();
    *last_ptr = last;
    return kRetNormal;
}

int MirRootTool::GetMidFromTreeSel(TTree* const evtree, const char* const key,
                                    const char* const select, double* const mid_ptr)
{
    evtree->SetBranchStatus("*", 1);
    evtree->Draw(key, select);
    double xmax = evtree->GetHistogram()->GetXaxis()->GetXmax();
    double xmin = evtree->GetHistogram()->GetXaxis()->GetXmin();

    double mid = (xmax + xmin)/2.;
    *mid_ptr = mid;
    return kRetNormal;
}


// private

void MirRootTool::Null()
{
    if(NULL != theApp_){
        delete theApp_; theApp_ = NULL;
    }
    if(NULL != tcanvas_){
        delete tcanvas_; tcanvas_ = NULL;
    }
    if(NULL != tfile_arr_){
        for(int ifile = 0; ifile < GetNfile(); ifile ++){
            if(NULL != tfile_arr_[ifile]){
                delete tfile_arr_[ifile]; tfile_arr_[ifile] = NULL;
            }
        }
        delete [] tfile_arr_; tfile_arr_ = NULL;
    }
    nfile_ = 0;
}
