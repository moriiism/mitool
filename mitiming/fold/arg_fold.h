#ifndef MXKWTOOL_MXKWTIMING_FOLD_ARG_FOLD_H_
#define MXKWTOOL_MXKWTIMING_FOLD_ARG_FOLD_H_

#include "mxkw_base.h"

class ArgValFold : public MxkwArgBase{
public:
    explicit ArgValFold(string title = "") :
        MxkwArgBase("ArgValFold", title),
        progname_(""),
        file_(""),
        telescope_(""),
        tunit_(""),
        format_(""),
        nbin_(0),
        ephfile_(""),
        outdir_(""),
        outfile_head_(""),
        plotmode_(""),
        printmode_(""),
        root_style_("") {}
    ~ArgValFold(){
        Null();
    }
    void Init(int argc, char *argv[]);
    void Print(FILE *fp) const;

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetTelescope() const {return telescope_;};
    string GetTunit() const {return tunit_;};
    string GetFormat() const {return format_;};
    int GetNbin() const {return nbin_;};
    string GetEphfile() const {return ephfile_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
  
private:
    string progname_;
    string file_;
    string telescope_;
    string tunit_;
    string format_;

    int    nbin_;
    string ephfile_;

    string outdir_;
    string outfile_head_;

    string plotmode_;
    string printmode_;
    string root_style_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};


#endif // MXKWTOOL_MXKWTIMING_FOLD_ARG_FOLD_H_
