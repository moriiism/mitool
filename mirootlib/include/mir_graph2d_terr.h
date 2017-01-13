#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_TERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_TERR_H_

#include "mir_graph2d.h"

class GraphDataTerr2d : public GraphData2d{
public:
    explicit GraphDataTerr2d(string title = "") :
        GraphData2d("GraphDataTerr2d", title) {}
    ~GraphDataTerr2d() {
        NullGraphData2d();
    }

    // Init
    void Init();

    // Set point
    using GraphData2d::SetPoint;
    void SetPoint(long idata,
                  double xval,
                  double xval_terr_plus,
                  double xval_terr_minus,
                  double oval,
                  double oval_terr_plus,
                  double oval_terr_minus);

    void SetOvalErrArrByPoissonErr();


    GraphDataTerr2d* const Clone() const;

    void Load(string file);
    void Load(string file, string format);    

    // operation
    void Sort();

    //
    // const functions
    //

    // get
    const DataArrayTerr1d* const GetXvalArr() const;
    const DataArrayTerr1d* const GetOvalArr() const;

    // get Range Qdp
    void GetXRangeQdp(double* const low_ptr,
                      double* const up_ptr) const;
    void GetORangeQdp(double* const low_ptr,
                      double* const up_ptr) const;
    
    // output
    void PrintData(FILE* fp, string format,
                   double offset_xval = 0.0,
                   double offset_oval = 0.0) const;

    TGraphAsymmErrors* const GenTGraph(double offset_xval = 0.0,
                                       double offset_oval = 0.0) const;

    Interval* const GenInterval() const;    
    Interval* const GenIntervalAboveThreshold(double threshold) const;
    Interval* const GenIntervalBelowThreshold(double threshold) const;

    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;    
};

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_TERR_H_
