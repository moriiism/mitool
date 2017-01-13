#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_SERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_SERR_H_

#include "mir_graph3d.h"

class GraphDataSerr3d : public GraphData3d{
public:
    explicit GraphDataSerr3d(string title = "") :
        GraphData3d("GraphDataSerr3d", title) {}
    ~GraphDataSerr3d() {}

    // Init
    void Init();

    // Set point
    using GraphData3d::SetPoint;
    void SetPoint(long idata,
                  double xval, double xval_serr,
                  double yval, double yval_serr,
                  double oval, double oval_serr);

    void SetOvalErrArrByPoissonErr();

    GraphDataSerr3d* const Clone() const;
    
    void Load(string file);
    void Load(string file, string format);


    //
    // const functions
    //
    
    // get
    const DataArraySerr1d* const GetXvalArr() const;
    const DataArraySerr1d* const GetYvalArr() const;
    const DataArraySerr1d* const GetOvalArr() const;

    // output
    void PrintData(FILE* fp, string format,
                   double offset_xval = 0.0,
                   double offset_yval = 0.0,
                   double offset_oval = 0.0) const;
    
    TGraph2DErrors* const GenTGraph2DErrors(double offset_xval = 0.0,
                                            double offset_yval = 0.0,
                                            double offset_oval = 0.0) const;

    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetYFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_SERR_H_
