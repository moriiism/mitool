#ifndef MORIIISM_MITOOL_MIUTIL_MISELIMG_ZEROLINE_ARG_MISELIMG_ZEROLINE_H_
#define MORIIISM_MITOOL_MIUTIL_MISELIMG_ZEROLINE_ARG_MISELIMG_ZEROLINE_H_

#include "mi_base.h"

class ArgValMiselimgZeroline : public MiArgBase{
public:
    ArgValMiselimgZeroline() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        row_or_col_(""),
        stddev_threshold_(0.0),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMiselimgZeroline(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile() const {return infile_;};
    string GetRowOrCol() const {return row_or_col_;};
    double GetStddevThreshold() const {return stddev_threshold_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    string row_or_col_;
    double stddev_threshold_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MISELIMG_ZEROLINE_ARG_MISELIMG_ZEROLINE_H_
