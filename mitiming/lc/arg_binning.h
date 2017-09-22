#ifndef MXKWTOOL_MXKWTIMING_LC_ARG_BINNING_H_
#define MXKWTOOL_MXKWTIMING_LC_ARG_BINNING_H_

#include "mxkw_base.h"

class ArgValBinning : public MxkwArgBase{
public:
    explicit ArgValBinning(string title = "") :
        MxkwArgBase("ArgValBinning", title),
        progname_(""),
        file_(""),
        hist_info_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValBinning(){}
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetHistInfo() const {return hist_info_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string file_;
    string hist_info_;
    string outdir_;
    string outfile_head_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXKWTOOL_MXKWTIMING_LC_ARG_BINNING_H_
