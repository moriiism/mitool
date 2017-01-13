#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_TERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_TERR_H_

#include "mir_graph3d.h"

class GraphDataTerr3d : public GraphData3d{
public:
    explicit GraphDataTerr3d(string title = "") :
        GraphData3d("GraphDataTerr3d", title) {}
    ~GraphDataTerr3d() {}

    // Init
    void Init();

    // Set xval_arr
    void SetXvalAndTerrArrDbl(long ndata,
                              const double* const val,
                              const double* const val_serr);
    void SetXvalAndTerrArrDbl(vector<double> val,
                              vector<double> val_serr);    
    void SetXvalAndTerrArrDbl(long ndata,
                              const double* const val,
                              const double* const val_terr_plus,
                              const double* const val_terr_minus);
    void SetXvalAndTerrArrDbl(vector<double> val,
                              vector<double> val_terr_plus,
                              vector<double> val_terr_minus);

    // Set yval_arr
    void SetYvalAndTerrArrDbl(long ndata,
                              const double* const val,
                              const double* const val_serr);
    void SetYvalAndTerrArrDbl(vector<double> val,
                              vector<double> val_serr);    
    void SetYvalAndTerrArrDbl(long ndata,
                              const double* const val,
                              const double* const val_terr_plus,
                              const double* const val_terr_minus);
    void SetYvalAndTerrArrDbl(vector<double> val,
                              vector<double> val_terr_plus,
                              vector<double> val_terr_minus);

    // Set oval_arr
    void SetOvalAndTerrArrDbl(long ndata,
                              const double* const val,
                              const double* const val_serr);
    void SetOvalAndTerrArrDbl(vector<double> val,
                              vector<double> val_serr);
    void SetOvalAndTerrArrDbl(long ndata,
                              const double* const val,
                              const double* const val_terr_plus,
                              const double* const val_terr_minus);
    void SetOvalAndTerrArrDbl(vector<double> val,
                              vector<double> val_terr_plus,
                              vector<double> val_terr_minus);

    // Set point
    using GraphData3d::SetPoint;    
    void SetPoint(long idata,
                  double xval, double xval_terr_plus, double xval_terr_minus,
                  double yval, double yval_terr_plus, double yval_terr_minus,
                  double oval, double oval_terr_plus, double oval_terr_minus);

    void SetOvalErrArrByPoissonErr();

    GraphDataTerr3d* const Clone() const;
    
    void Load(string file);
    void Load(string file, string format);

    //
    // const functions
    //
    
    // get
    const DataArrayTerr1d* const GetXvalArr() const;
    const DataArrayTerr1d* const GetYvalArr() const;
    const DataArrayTerr1d* const GetOvalArr() const;

    // get internal of xval_arr_, yval_arr_ and oval_arr_
    const double* const GetXvalTerrPlusArrDbl() const
        {return GetXvalArr()->GetValTerrPlus();};
    const double* const GetXvalTerrMinusArrDbl() const
        {return GetXvalArr()->GetValTerrMinus();};
    const double* const GetYvalTerrPlusArrDbl() const
        {return GetYvalArr()->GetValTerrPlus();};
    const double* const GetYvalTerrMinusArrDbl() const
        {return GetYvalArr()->GetValTerrMinus();};
    const double* const GetOvalTerrPlusArrDbl() const
        {return GetOvalArr()->GetValTerrPlus();};
    const double* const GetOvalTerrMinusArrDbl() const
        {return GetOvalArr()->GetValTerrMinus();};    
    
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
    
    // output
    void PrintData(FILE* fp, string format,
                   double offset_xval = 0.0,
                   double offset_yval = 0.0,
                   double offset_oval = 0.0) const;

    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetYFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_TERR_H_
