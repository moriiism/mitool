#ifndef MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_SPEC_DATA_LIST_H_
#define MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_SPEC_DATA_LIST_H_

#include "mi_base.h"

class ArgValDrawSpecDataList : public MiArgBase{
public:
    ArgValDrawSpecDataList() :
        MiArgBase(),
        progname_(""),
        data_file_list_(""),
        func_par_list_(""),
        spec_type_(""),        
        plot_conf_file_(""),
        outdir_(""),
        outfile_head_(""),
        plotmode_(""), printmode_(""),
        root_style_("") {}
    ~ArgValDrawSpecDataList(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;
    
    string GetProgname() const {return progname_;};
    string GetDataFileList() const {return data_file_list_;};
    string GetFuncParList() const {return func_par_list_;};
    string GetSpecType() const {return spec_type_;};    
    string GetPlotConfFile() const {return plot_conf_file_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetPlotmode() const {return plotmode_;};
    string GetPrintmode() const {return printmode_;};
    string GetRootStyle() const {return root_style_;};

private:
    string progname_;
    string data_file_list_;
    string func_par_list_;
    string spec_type_;    
    string plot_conf_file_;
    string outdir_;
    string outfile_head_;
    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;    
};

#endif // MORIIISM_MITOOL_MIUTIL_MIFUNC_ARG_DRAW_SPEC_DATA_LIST_H_
