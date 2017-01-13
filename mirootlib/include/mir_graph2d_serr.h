#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_SERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_SERR_H_

#include "mir_graph2d.h"

class GraphDataSerr2d : public GraphData2d{
public:
    explicit GraphDataSerr2d(string title = "") :
        GraphData2d("GraphDataSerr2d", title) {}
    ~GraphDataSerr2d() {
        NullGraphData2d();
    }
    
    // Init
    void Init();

    // Set point
    using GraphData2d::SetPoint;    
    void SetPoint(long idata,
                  double xval, double xval_serr,
                  double oval, double oval_serr);

    void SetOvalErrArrByPoissonErr();
    
    GraphDataSerr2d* const Clone() const;
    
    void Load(string file);
    void Load(string file, string format);

    // operation
    void Sort();

    //
    // const functions
    //
    
    // get
    const DataArraySerr1d* const GetXvalArr() const;
    const DataArraySerr1d* const GetOvalArr() const;
    
    // get Range Qdp
    void GetXRangeQdp(double* const low_ptr,
                      double* const up_ptr) const;
    void GetORangeQdp(double* const low_ptr,
                      double* const up_ptr) const;
    
    // output
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_oval) const;

    TGraphErrors* const GenTGraph(double offset_xval,
                                  double offset_oval) const;

    Interval* const GenInterval() const;
    Interval* const GenIntervalAboveThreshold(double threshold) const;
    Interval* const GenIntervalBelowThreshold(double threshold) const;

    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;

};

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_SERR_H_
