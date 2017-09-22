#ifndef MORIIISM_MITOOL_MIFUNCLIB_GRAPH2D_H_
#define MORIIISM_MITOOL_MIFUNCLIB_GRAPH2D_H_

#include "mir_graph2d.h"

// function made from GraphData2d

class Gd2dFunc : public MirFunc{
public:
    explicit Gd2dFunc(string title = "") :
        MirFunc("Gd2dFunc", title),
        gd2d_(NULL)
        {
            SetNpar(0);
            SetNdim(1);
        }
    ~Gd2dFunc()
        {
            Null();
        }
    void InitSetGd2d(const GraphData2d* const gd2d);
    void Copy(const Gd2dFunc* const org);
    Gd2dFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    const GraphData2d* const GetGd2d() const {return gd2d_;};
private:
    GraphData2d* gd2d_;
    void Null();
};

#endif // MORIIISM_MITOOL_MIFUNCLIB_GRAPH2D_H_
