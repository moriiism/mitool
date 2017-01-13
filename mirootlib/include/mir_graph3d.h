#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_H_

#include "TGraph2D.h"
#include "TGraph2DErrors.h"

#include "mir_data1d_nerr.h"
#include "mir_data1d_serr.h"
#include "mir_data1d_terr.h"
#include "mir_func.h"
#include "mir_hist_info.h"

class GraphDataSerr3d;
class GraphDataTerr3d;

class GraphData3d : public MiObject{
public:
    GraphData3d(string class_name, string title) :
        MiObject(class_name, title),
        xval_arr_(NULL), yval_arr_(NULL), oval_arr_(NULL) {}
    virtual ~GraphData3d() {
        Null();
    }

    // Init
    virtual void Init();

    void SetXvalArr(const DataArray1d* const val_arr);
    void SetYvalArr(const DataArray1d* const val_arr);
    void SetOvalArr(const DataArray1d* const val_arr);

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

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH3D_H_

