#ifndef MORIIISM_MITOOL_MITIMING_FOLD_ARG_FOLD_H_
#define MORIIISM_MITOOL_MITIMING_FOLD_ARG_FOLD_H_

#include "mi_base.h"

class ArgValFold : public MiArgBase{
public:
    ArgValFold() :
        MiArgBase(),
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

#endif // MORIIISM_MITOOL_MITIMING_FOLD_ARG_FOLD_H_
