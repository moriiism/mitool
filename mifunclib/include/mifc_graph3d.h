#ifndef MORIIISM_MITOOL_MIFUNCLIB_GRAPH3D_H_
#define MORIIISM_MITOOL_MIFUNCLIB_GRAPH3D_H_

#include "mir_graph3d.h"

// function made from GraphData3d

class Gd3dFunc : public MirFunc{
public:
    explicit Gd3dFunc(string title = "") :
        MirFunc("Gd3dFunc", title)
        {
            SetNpar(0);
            SetNdim(2);
        }
    ~Gd3dFunc()
        {
            Null();
        }

    void InitSetGd3d(const GraphData3d* const gd3d);
    void Copy(const Gd3dFunc* const org);
    Gd3dFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    const GraphData3d* const GetGd3d() const {return gd3d_;};
private:
    GraphData3d* gd3d_;
    void Null();    
};

#endif // MORIIISM_MITOOL_MIFUNCLIB_GRAPH3D_H_
