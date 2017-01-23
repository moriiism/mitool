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

    void Init(long ndata);
    void SetXvalTerrArr(long ndata, const double* const val_serr);
    void SetXvalTerrArr(vector<double> val_serr);
    void SetXvalTerrArr(long ndata,
                        const double* const val_terr_plus,
                        const double* const val_terr_minus);
    void SetXvalTerrArr(vector<double> val_terr_plus,
                        vector<double> val_terr_minus);
    void SetOvalTerrArr(long ndata, const double* const val_serr);
    void SetOvalTerrArr(vector<double> val_serr);
    void SetOvalTerrArr(long ndata,
                        const double* const val_terr_plus,
                        const double* const val_terr_minus);
    void SetOvalTerrArr(vector<double> val_terr_plus,
                        vector<double> val_terr_minus);
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
    void Sort();

    const DataArrayTerr1d* const GetXvalArr() const;
    const DataArrayTerr1d* const GetOvalArr() const;
    double GetXvalTerrPlusElm(long idata) const;
    double GetXvalTerrMinusElm(long idata) const;
    double GetOvalTerrPlusElm(long idata) const;
    double GetOvalTerrMinusElm(long idata) const;
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_oval) const;
    TGraphAsymmErrors* const GenTGraph(double offset_xval,
                                       double offset_oval) const;
    Interval* const GenInterval() const;    
    Interval* const GenIntervalAboveThreshold(double threshold) const;
    Interval* const GenIntervalBelowThreshold(double threshold) const;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_TERR_H_
