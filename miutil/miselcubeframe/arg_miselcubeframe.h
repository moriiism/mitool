#ifndef MORIIISM_MITOOL_MIUTIL_MISELCUBEFRAME_ARG_MISELCUBEFRAME_H_
#define MORIIISM_MITOOL_MIUTIL_MISELCUBEFRAME_ARG_MISELCUBEFRAME_H_

#include "mi_base.h"

class ArgValMiselcubeframe : public MiArgBase{
public:
    ArgValMiselcubeframe() :
        MiArgBase(),
        progname_(""),
        infile_(""),
        frame_st_(0),
        frame_ed_(0),
        outdir_(""),
        outfile_head_("") {}
    ~ArgValMiselcubeframe(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetInfile() const {return infile_;};
    int    GetFrameSt() const {return frame_st_;};
    int    GetFrameEd() const {return frame_ed_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string infile_;
    int    frame_st_;
    int    frame_ed_;
    string outdir_;
    string outfile_head_;

    void Null();
    void SetOption(int argc, char* argv[], option* long_options);
    void Usage(FILE* fp) const;
};

#endif // MORIIISM_MITOOL_MIUTIL_MISELCUBEFRAME_ARG_MISELCUBEFRAME_H_
