#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_H_

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

#include "mir_interval.h"
#include "mir_data1d_nerr.h"
#include "mir_data1d_serr.h"
#include "mir_data1d_terr.h"
#include "mir_func.h"
#include "mir_hist_info.h"

class GraphDataNerr2d;
class GraphDataSerr2d;
class GraphDataTerr2d;

class GraphData2d : public MiObject{
public:
    GraphData2d(string class_name, string title) :
        MiObject(class_name, title),
        xval_arr_(NULL),
        oval_arr_(NULL),
        flag_xval_sorted_(0) {}
    virtual ~GraphData2d() {}

    // Init
    virtual void Init() = 0;

    // Set
    void SetXvalArr(const DataArray1d* const val_arr);
    void SetOvalArr(const DataArray1d* const val_arr);
    void SetFlagXvalSorted(int flag) {flag_xval_sorted_ = flag;};

    // Set point
    void SetPoint(long idata, double xval, double oval);
    virtual void SetPoint(long idata,
                          double xval, double xval_serr,
                          double oval, double oval_serr)
        {MPrintErrVFunc; abort();};    
    virtual void SetPoint(long idata,
                          double xval,
                          double xval_terr_plus,
                          double xval_terr_minus,
                          double oval,
                          double oval_terr_plus,
                          double oval_terr_minus)
        {MPrintErrVFunc; abort();};

    virtual void SetOvalErrArrByPoissonErr()
        {MPrintErrVFunc; abort();};
    
    // Init & Set by Func
    void InitSetByFunc(const MirFunc* const func, const double* const par,
                       long nbin_xval, double xval_lo, double xval_up,
                       string scale);
    void Copy(const GraphData2d* const org);

    virtual void Load(string file) = 0;
    virtual void Load(string file, string format) = 0;

    // operation
    virtual void Sort() = 0;
    
    //
    // const functions
    //
    
    // get
    virtual const DataArray1d* const GetXvalArr() const = 0;
    virtual const DataArray1d* const GetOvalArr() const = 0;
    int GetFlagXvalSorted() const {return flag_xval_sorted_;};

    long GetNdata() const;
    double GetXvalElm(long idata) const
        {return GetXvalArr()->GetValElm(idata);};
    virtual double GetXvalSerrElm(long idata) const
        {MPrintErrVFunc; abort();};
    virtual double GetXvalTerrPlusElm(long idata) const
        {MPrintErrVFunc; abort();};
    virtual double GetXvalTerrMinusElm(long idata) const
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
    double GetXvalAtOvalMin() const;
    double GetXvalAtOvalMax() const;
    double GetOvalAtXvalMin() const;
    double GetOvalAtXvalMax() const;
    
    // output
    void Save(string outfile, string format,
              double offset_xval = 0.0,
              double offset_oval = 0.0) const;
    void SaveData(string outfile, string format,
                  double offset_xval = 0.0,
                  double offset_oval = 0.0) const;
    void PrintInfo(FILE* fp) const;
    virtual void PrintData(FILE* fp, string format,
                           double offset_xval,
                           double offset_oval) const = 0;

    virtual TGraph* const GenTGraph(double offset_xval,
                                    double offset_oval) const = 0;

    double GetOvalIntPolLin(double xval) const;
    // ichiji hokan

    virtual Interval* const GenInterval() const
        {MPrintErrVFunc; abort();};
    virtual Interval* const GenIntervalAboveThreshold(double threshold) const
        {MPrintErrVFunc; abort();};
    virtual Interval* const GenIntervalBelowThreshold(double threshold) const
        {MPrintErrVFunc; abort();};

    // offset_tag = "st", "md", "ed", "no", value
    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;

    int IsEqualSpaceX() const;

    //
    // static
    //
    static void ReadInfo(string file, int* flag_xval_sorted_ptr);
  
protected:
    void NullGraphData2d();
    void NewXvalArrAsDataArrayNerr1d();
    void NewXvalArrAsDataArraySerr1d();
    void NewXvalArrAsDataArrayTerr1d();
    DataArray1d* GetXvalArrNonConst() const {return xval_arr_;};
    void NewOvalArrAsDataArrayNerr1d();
    void NewOvalArrAsDataArraySerr1d();
    void NewOvalArrAsDataArrayTerr1d();
    DataArray1d* GetOvalArrNonConst() const {return oval_arr_;};

private:
    DataArray1d* xval_arr_;
    DataArray1d* oval_arr_;
    int flag_xval_sorted_; // -1: not sorted, 0: not checked, 1: sorted
};

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_H_
