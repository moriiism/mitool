#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_TERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_TERR_H_

#include "mir_graph3d.h"

class GraphDataTerr3d : public GraphData3d{
public:
    explicit GraphDataTerr3d(string title = "") :
        GraphData3d("GraphDataTerr3d", title) {}
    ~GraphDataTerr3d() {
        NullGraphData3d();
    }

    void Init();
    using GraphData3d::SetPoint;
    void SetPoint(long idata,
                  double xval, double xval_terr_plus, double xval_terr_minus,
                  double yval, double yval_terr_plus, double yval_terr_minus,
                  double oval, double oval_terr_plus, double oval_terr_minus);
    void SetOvalErrArrByPoissonErr();
    GraphDataTerr3d* const Clone() const;
    void Load(string file);
    void Load(string file, string format);

    const DataArrayTerr1d* const GetXvalArr() const;
    const DataArrayTerr1d* const GetYvalArr() const;
    const DataArrayTerr1d* const GetOvalArr() const;
    double GetXvalTerrPlusElm(long idata) const
        {return GetXvalArr()->GetValTerrPlusElm(idata);};
    double GetXvalTerrMinusElm(long idata) const
        {return GetXvalArr()->GetValTerrMinusElm(idata);};
    double GetYvalTerrPlusElm(long idata) const
        {return GetYvalArr()->GetValTerrPlusElm(idata);};
    double GetYvalTerrMinusElm(long idata) const
        {return GetYvalArr()->GetValTerrMinusElm(idata);};
    double GetOvalTerrPlusElm(long idata) const
        {return GetOvalArr()->GetValTerrPlusElm(idata);};
    double GetOvalTerrMinusElm(long idata) const
        {return GetOvalArr()->GetValTerrMinusElm(idata);};    
    
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_yval,
                   double offset_oval) const;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_TERR_H_
