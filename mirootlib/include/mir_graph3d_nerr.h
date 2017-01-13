#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_NERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_NERR_H_

#include "TGraph2D.h"
#include "TGraph2DErrors.h"

#include "mir_data_nerr.h"
#include "mir_data_serr.h"
#include "mir_data_terr.h"
#include "mir_func.h"
#include "mir_hist_info.h"

class GraphDataNerr3d : public GraphData3d{
public:
    GraphDataNerr3d(string title = "") :
        GraphData3d("GraphDataNerr3d", title),
        xval_arr_(NULL), yval_arr_(NULL), oval_arr_(NULL) {}
    virtual ~GraphDataNerr3d() {
        Null();
    }

    // Init
    virtual void Init();

    // Set
    void Set(const GraphData3d* const org);
    void Set(const DataArray1d* const xval_arr,
             const DataArray1d* const yval_arr,
             const DataArray1d* const oval_arr);

    // Init & Set
    void InitSet(const DataArray1d* const xval_arr,
                 const DataArray1d* const yval_arr,
                 const DataArray1d* const oval_arr);

    // Set xval_arr
    void SetXvalArr(const DataArray1d* const val_arr);

    // Set xval_arr(val)
    void SetXvalArrDbl(long ndata, const double* const val);
    void SetXvalArrDbl(vector<double> val);

    // Set xval_arr(val_serr)
    virtual void SetXvalSerrArrDbl(long ndata,
                                   const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetXvalSerrArrDbl(vector<double> val_serr)
        {MPrintErrVFunc; abort();};

    // Set xval_arr(val, val_serr)
    virtual void SetXvalAndSerrArrDbl(long ndata,
                                      const double* const val,
                                      const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetXvalAndSerrArrDbl(vector<double> val,
                                      vector<double> val_serr)
        {MPrintErrVFunc; abort();};

    // Set xval_arr(val_terr_plus, val_terr_minus)
    virtual void SetXvalTerrArrDbl(long ndata,
                                   const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetXvalTerrArrDbl(vector<double> val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetXvalTerrArrDbl(long ndata,
                                   const double* const val_terr_plus,
                                   const double* const val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void SetXvalTerrArrDbl(vector<double> val_terr_plus,
                                   vector<double> val_terr_minus)
        {MPrintErrVFunc; abort();};

    // Set xval_arr(val, val_terr_plus, val_terr_minus)    
    virtual void SetXvalAndTerrArrDbl(long ndata,
                                      const double* const val,
                                      const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetXvalAndTerrArrDbl(vector<double> val,
                                      vector<double> val_serr)
        {MPrintErrVFunc; abort();};    
    virtual void SetXvalAndTerrArrDbl(long ndata,
                                      const double* const val,
                                      const double* const val_terr_plus,
                                      const double* const val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void SetXvalAndTerrArrDbl(vector<double> val,
                                      vector<double> val_terr_plus,
                                      vector<double> val_terr_minus)
        {MPrintErrVFunc; abort();};

    // Set yval_arr    
    void SetYvalArr(const DataArray1d* const val_arr);

    // Set yval_arr(val)
    void SetYvalArrDbl(long ndata, const double* const val);
    void SetYvalArrDbl(vector<double> val);

    // Set yval_arr(val_serr)
    virtual void SetYvalSerrArrDbl(long ndata,
                                   const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetYvalSerrArrDbl(vector<double> val_serr)
        {MPrintErrVFunc; abort();};

    // Set yval_arr(val, val_serr)
    virtual void SetYvalAndSerrArrDbl(long ndata,
                                      const double* const val,
                                      const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetYvalAndSerrArrDbl(vector<double> val,
                                      vector<double> val_serr)
        {MPrintErrVFunc; abort();};

    // Set yval_arr(val_terr_plus, val_terr_minus)
    virtual void SetYvalTerrArrDbl(long ndata,
                                   const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetYvalTerrArrDbl(vector<double> val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetYvalTerrArrDbl(long ndata,
                                   const double* const val_terr_plus,
                                   const double* const val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void SetYvalTerrArrDbl(vector<double> val_terr_plus,
                                   vector<double> val_terr_minus)
        {MPrintErrVFunc; abort();};

    // Set yval_arr(val, val_terr_plus, val_terr_minus)    
    virtual void SetYvalAndTerrArrDbl(long ndata,
                                      const double* const val,
                                      const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetYvalAndTerrArrDbl(vector<double> val,
                                      vector<double> val_serr)
        {MPrintErrVFunc; abort();};    
    virtual void SetYvalAndTerrArrDbl(long ndata,
                                      const double* const val,
                                      const double* const val_terr_plus,
                                      const double* const val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void SetYvalAndTerrArrDbl(vector<double> val,
                                      vector<double> val_terr_plus,
                                      vector<double> val_terr_minus)
        {MPrintErrVFunc; abort();};
    
    
    // Set oval_arr
    void SetOvalArr(const DataArray1d* const val_arr);

    // Set oval_arr(val)
    void SetOvalArrDbl(long ndata, const double* const val);
    void SetOvalArrDbl(vector<double> val);

    // Set oval_arr(val_serr)
    virtual void SetOvalSerrArrDbl(long ndata,
                                   const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalSerrArrDbl(vector<double> val_serr)
        {MPrintErrVFunc; abort();};

    // Set oval_arr(val, val_serr)
    virtual void SetOvalAndSerrArrDbl(long ndata,
                                      const double* const val,
                                      const double* const val_serr)
        {MPrintErrVFunc; abort();};        
    virtual void SetOvalAndSerrArrDbl(vector<double> val,
                                      vector<double> val_serr)
        {MPrintErrVFunc; abort();};

    // Set oval_arr(val_terr_plus, val_terr_minus)
    virtual void SetOvalTerrArrDbl(long ndata,
                                   const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrArrDbl(vector<double> val_serr)
        {MPrintErrVFunc; abort();};    
    virtual void SetOvalTerrArrDbl(long ndata,
                                   const double* const val_terr_plus,
                                   const double* const val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrArrDbl(vector<double> val_terr_plus,
                                   vector<double> val_terr_minus)
        {MPrintErrVFunc; abort();};
    
    // Set oval_arr(val, val_terr_plus, val_terr_minus)
    virtual void SetOvalAndTerrArrDbl(long ndata,
                                      const double* const val,
                                      const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalAndTerrArrDbl(vector<double> val,
                                      vector<double> val_serr)
        {MPrintErrVFunc; abort();};    
    virtual void SetOvalAndTerrArrDbl(long ndata,
                                      const double* const val,
                                      const double* const val_terr_plus,
                                      const double* const val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalAndTerrArrDbl(vector<double> val,
                                      vector<double> val_terr_plus,
                                      vector<double> val_terr_minus)
        {MPrintErrVFunc; abort();};


    // Init & Set
    void SetPoint(long idata, double xval, double yval, double oval);
    virtual void SetPoint(long idata,
                          double xval, double xval_serr,
                          double yval, double yval_serr,
                          double oval, double oval_serr)
        {MPrintErrVFunc; abort();};    
    virtual void SetPoint(long idata,
                          double xval,
                          double xval_terr_plus,
                          double xval_terr_minus,
                          double yval,
                          double yval_terr_plus,
                          double yval_terr_minus,
                          double oval,
                          double oval_terr_plus,
                          double oval_terr_minus)
        {MPrintErrVFunc; abort();};

    virtual void SetOvalErrArrByPoissonErr()
        {MPrintErrVFunc; abort();};

    // Init & Set by Func
    void InitSetByFunc(const MirFunc* const func, const double* const par,
                       long nbin_xval, double xval_lo, double xval_up,
                       long nbin_yval, double yval_lo, double yval_up,
                       string scale_xval, string scale_yval);
    
    void Copy(const GraphData3d* const org);
    virtual GraphData3d* const Clone() const;
    
    virtual void Load(string file);
    virtual void Load(string file, string format);

    //
    // const functions
    //
    
    // get
    virtual const DataArray1d* const GetXvalArr() const
        {return xval_arr_;};
    virtual const DataArray1d* const GetYvalArr() const
        {return yval_arr_;};
    virtual const DataArray1d* const GetOvalArr() const
        {return oval_arr_;};

    // get internal of xval_arr_, yval_arr_ and oval_arr_
    long GetNdata() const {return GetXvalArr()->GetNdata();};
    
    const double* const GetXvalArrDbl() const
        {return GetXvalArr()->GetVal();};
    virtual const double* const GetXvalSerrArrDbl() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetXvalTerrPlusArrDbl() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetXvalTerrMinusArrDbl() const
        {MPrintErrVFunc; abort();};

    const double* const GetYvalArrDbl() const
        {return GetYvalArr()->GetVal();};
    virtual const double* const GetYvalSerrArrDbl() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetYvalTerrPlusArrDbl() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetYvalTerrMinusArrDbl() const
        {MPrintErrVFunc; abort();};

    const double* const GetOvalArrDbl() const
        {return GetOvalArr()->GetVal();};
    virtual const double* const GetOvalSerrArrDbl() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetOvalTerrPlusArrDbl() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetOvalTerrMinusArrDbl() const
        {MPrintErrVFunc; abort();};
    
    double GetXvalElm(long idata) const
        {return GetXvalArr()->GetValElm(idata);};
    virtual double GetXvalSerrElm(long idata) const
        {MPrintErrVFunc; abort();};
    virtual double GetXvalTerrPlusElm(long idata) const
        {MPrintErrVFunc; abort();};
    virtual double GetXvalTerrMinusElm(long idata) const
        {MPrintErrVFunc; abort();};
    
    double GetYvalElm(long idata) const
        {return GetYvalArr()->GetValElm(idata);};
    virtual double GetYvalSerrElm(long idata) const
        {MPrintErrVFunc; abort();};
    virtual double GetYvalTerrPlusElm(long idata) const
        {MPrintErrVFunc; abort();};
    virtual double GetYvalTerrMinusElm(long idata) const
        {MPrintErrVFunc; abort();};

    double GetOvalElm(long idata) const
        {return GetOvalArr()->GetValElm(idata);};
    virtual double GetOvalSerrElm(long idata) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrPlusElm(long idata) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrMinusElm(long idata) const
        {MPrintErrVFunc; abort();};

    // stat
    double GetYvalAtXvalMin() const;
    double GetYvalAtXvalMax() const;
    double GetOvalAtXvalMin() const;
    double GetOvalAtXvalMax() const;
    
    double GetXvalAtYvalMin() const;
    double GetXvalAtYvalMax() const;
    double GetOvalAtYvalMin() const;
    double GetOvalAtYvalMax() const;

    double GetXvalAtOvalMin() const;
    double GetXvalAtOvalMax() const;
    double GetYvalAtOvalMin() const;
    double GetYvalAtOvalMax() const;
  

    // output
    void Save(string outfile, string format,
              double offset_xval = 0.0,
              double offset_yval = 0.0,
              double offset_oval = 0.0) const;
    virtual void PrintData(FILE* fp, string format,
                           double offset_xval = 0.0,
                           double offset_yval = 0.0,
                           double offset_oval = 0.0) const;

    TGraph2D* const GenTGraph2D(double offset_xval = 0.0,
                                double offset_yval = 0.0,
                                double offset_oval = 0.0) const;

    virtual TGraph2DErrors* const GenTGraph2DErrors(double offset_xval = 0.0,
                                                    double offset_yval = 0.0,
                                                    double offset_oval = 0.0) const
        {MPrintErrVFunc; abort();};

    virtual double GetOffsetXFromTag(string offset_tag) const;
    virtual double GetOffsetYFromTag(string offset_tag) const;
    virtual double GetOffsetOFromTag(string offset_tag) const;

protected:
    void Null();
    
    void NewXvalArrAsDataArray1d();
    void NewXvalArrAsDataArraySerr1d();
    void NewXvalArrAsDataArrayTerr1d();
    DataArray1d* GetXvalArrNonConst() const {return xval_arr_;};

    void NewYvalArrAsDataArray1d();
    void NewYvalArrAsDataArraySerr1d();
    void NewYvalArrAsDataArrayTerr1d();
    DataArray1d* GetYvalArrNonConst() const {return yval_arr_;};
    
    void NewOvalArrAsDataArray1d();
    void NewOvalArrAsDataArraySerr1d();
    void NewOvalArrAsDataArrayTerr1d();
    DataArray1d* GetOvalArrNonConst() const {return oval_arr_;};

private:    
    DataArray1d* xval_arr_;
    DataArray1d* yval_arr_;
    DataArray1d* oval_arr_;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_NERR_H_
