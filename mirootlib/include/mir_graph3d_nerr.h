#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_NERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_NERR_H_

#include "mir_graph3d.h"

class GraphDataNerr3d : public GraphData3d{
public:
    explicit GraphDataNerr3d(string title = "") :
        GraphData3d("GraphDataNerr3d", title) {}
    ~GraphDataNerr3d() {
        NullGraphData3d();
    }

    void Init();
    GraphDataNerr3d* const Clone() const;
    void Load(string file);
    void Load(string file, string format);
    
    const DataArrayNerr1d* const GetXvalArr() const;
    const DataArrayNerr1d* const GetYvalArr() const;
    const DataArrayNerr1d* const GetOvalArr() const;

    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_yval,
                   double offset_oval) const;
    TGraph2D* const GenTGraph2D(double offset_xval,
                                double offset_yval,
                                double offset_oval) const;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_NERR_H_
