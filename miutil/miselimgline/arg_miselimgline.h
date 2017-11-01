#ifndef MORIIISM_MITOOL_MIUTIL_MISELIMGLINE_ARG_MISELIMGLINE_H_
#define MORIIISM_MITOOL_MIUTIL_MISELIMGLINE_ARG_MISELIMGLINE_H_

#include "mi_base.h"

class ArgValMiselimgline : public MiArgBase{
public:
    ArgValMiselimgline() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        row_or_col_(""),
        line_st_(0),
        line_ed_(0),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMiselimgline(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile() const {return infile_;};
    string GetRowOrCol() const {return row_or_col_;};
    int    GetLineSt() const {return line_st_;};
    int    GetLineEd() const {return line_ed_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    string row_or_col_;
    int    line_st_;
    int    line_ed_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MISELIMGLINE_ARG_MISELIMGLINE_H_
