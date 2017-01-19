#ifndef MORIIISM_MITOOL_MIROOTLIB_ROOT_TOOL_H_
#define MORIIISM_MITOOL_MIROOTLIB_ROOT_TOOL_H_

#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TStyle.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"

#include "mi_base.h"
#include "mir_plot_conf.h"

class MirRootTool : private Uncopyable{
public:
    MirRootTool() :
        theApp_(NULL),
        tcanvas_(NULL),
        nfile_(0),
        tfile_arr_(NULL) {}
    ~MirRootTool() {
        Null();
    }

    void InitTApp();
    // type: def, std, pub, detail
    void InitTCanvas(string type);
    void InitSetTFile(string tfile_name);
    void InitSetTFileArr(int nfile, const string* const tfile_name_arr);
    
    void SetPlotConf(const MirPlotConf* const plot_conf);

    //
    // const func
    //
    TCanvas* const GetTCanvas() const {return tcanvas_;};
    int GetNfile() const {return nfile_;};
    TFile** const GetTfileArr() const {return tfile_arr_;};

    TFile* const GetTFile() const;
    TFile* const GetTFileArrElm(int ifile) const;
    TTree* const GetEvtTree() const;
    TTree* const GetEvtTreeArrElm(int ifile) const;

    // they are lower and upper range of axis for the histogram.
    // they are not minimum and maximum value.
    static int GetFirstFromTree(TTree* const evtree, const char* const key, double* const first_ptr);
    static int GetLastFromTree(TTree* const evtree, const char* const key, double* const last_ptr);
    static int GetMidFromTree(TTree* const evtree, const char* const key, double* const mid_ptr);

    static int GetFirstFromTreeSel(TTree* const evtree, const char* const  key,
                                   const char* const select, double* const first_ptr);
    static int GetLastFromTreeSel(TTree* const evtree, const char* const key,
                                  const char* const select, double* const last_ptr);
    static int GetMidFromTreeSel(TTree* const evtree, const char* const key,
                                 const char* const select, double* const mid_ptr);

private:
    TApplication* theApp_;
    TCanvas* tcanvas_;
    int nfile_;
    TFile** tfile_arr_;
    void Null();
};


#endif // MORIIISM_MITOOL_MIROOTLIB_ROOT_TOOL_H_
