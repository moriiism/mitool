#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_NERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_NERR_H_

#include "mir_graph2d.h"

class GraphDataNerr2d : public GraphData2d{
public:
    explicit GraphDataNerr2d(string title = "") :
        GraphData2d("GraphDataNerr2d", title) {}
    ~GraphDataNerr2d() {
        NullGraphData2d();
    }

    // Init
    void Init();

    // Init & Set by Func
    void InitSetByFunc(const MirFunc* const func, const double* const par,
                       long nbin_xval, double xval_lo, double xval_up,
                       string scale);

    virtual GraphDataNerr2d* const Clone() const;

    //
    // const functions
    //

    // stat
    double GetXvalAtOvalMin() const;
    double GetXvalAtOvalMax() const;
    double GetOvalAtXvalMin() const;
    double GetOvalAtXvalMax() const;

    // get Range Qdp
    void GetXRangeQdp(double* const low_ptr,
                      double* const up_ptr) const;
    void GetORangeQdp(double* const low_ptr,
                      double* const up_ptr) const;
    
    // output
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_oval) const;

    TGraph* const GenTGraph(double offset_xval,
                            double offset_oval) const;
    
    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;

};

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_NERR_H_
