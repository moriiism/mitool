#ifndef MORIIISM_MITOOL_MIFUNCLIB_HIST2D_H_
#define MORIIISM_MITOOL_MIFUNCLIB_HIST2D_H_

#include "mir_hist2d.h"

// function made from HistData2d

class Hd2dFunc : public MirFunc{
public:
    explicit Hd2dFunc(string title = "") :
        MirFunc("Hd2dFunc", title),
        hd2d_(NULL)
        {
            SetNpar(0);
            SetNdim(2);
        }
    ~Hd2dFunc()
        {
            Null();
        }
    void InitSetHd2d(const HistData2d* const hd2d);
    void Copy(const Hd2dFunc* const org);
    Hd2dFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    const HistData2d* const GetHd2d() const {return hd2d_;};
private:
    HistData2d* hd2d_;
    void Null();
};

#endif // MORIIISM_MITOOL_MIFUNCLIB_HIST2D_H_
