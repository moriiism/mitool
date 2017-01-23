#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_graph2d_nerr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_root_tool.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;


    
//    virtual void Init(long ndata) = 0;
//    void SetXvalArr(const DataArray1d* const val_arr);
//    void SetOvalArr(const DataArray1d* const val_arr);
//    void SetFlagXvalSorted(int flag) {flag_xval_sorted_ = flag;};
//    void SetXvalArr(long ndata, const double* const val);
//    void SetXvalArr(vector<double> val);
//    void SetOvalArr(long ndata, const double* const val);
//    void SetOvalArr(vector<double> val);    
//    void SetXvalSerrArr(long ndata, const double* const val_serr)
//    void SetXvalSerrArr(vector<double> val_serr)
//    void SetOvalSerrArr(long ndata, const double* const val_serr)
//    void SetOvalSerrArr(vector<double> val_serr)
//    void SetXvalTerrArr(long ndata, const double* const val_serr)
//    void SetXvalTerrArr(vector<double> val_serr)
//    void SetXvalTerrArr(long ndata,
//                        const double* const val_terr_plus,
//                        const double* const val_terr_minus)
//    void SetXvalTerrArr(vector<double> val_terr_plus,
//                        vector<double> val_terr_minus)
//    void SetOvalTerrArr(long ndata, const double* const val_serr)
//    void SetOvalTerrArr(vector<double> val_serr)
//    void SetOvalTerrArr(long ndata,
//                        const double* const val_terr_plus,
//                        const double* const val_terr_minus)
//    void SetOvalTerrArr(vector<double> val_terr_plus,
//                        vector<double> val_terr_minus)
//    void SetPoint(long idata, double xval, double oval);
//    virtual void SetPoint(long idata,
//                          double xval, double xval_serr,
//                          double oval, double oval_serr)
//    virtual void SetPoint(long idata,
//                          double xval,
//                          double xval_terr_plus,
//                          double xval_terr_minus,
//                          double oval,
//                          double oval_terr_plus,
//                          double oval_terr_minus)
//    virtual void SetOvalErrArrByPoissonErr()
//    void InitSetByFunc(const MirFunc* const func, const double* const par,
//                       long nbin_xval, double xval_lo, double xval_up,
//                       string scale);
//    void Copy(const GraphData2d* const org);
//    virtual void Load(string file) = 0;
//    virtual void Load(string file, string format) = 0;
//    virtual void Sort() = 0;
//    virtual const DataArray1d* const GetXvalArr() const = 0;
//    virtual const DataArray1d* const GetOvalArr() const = 0;
//    int GetFlagXvalSorted() const {return flag_xval_sorted_;};
//    long GetNdata() const;
//    double GetXvalElm(long idata) const
//        {return GetXvalArr()->GetValElm(idata);};
//    virtual double GetXvalSerrElm(long idata) const
//        {MPrintErrVFunc; abort();};
//    virtual double GetXvalTerrPlusElm(long idata) const
//        {MPrintErrVFunc; abort();};
//    virtual double GetXvalTerrMinusElm(long idata) const
//        {MPrintErrVFunc; abort();};        
//    double GetOvalElm(long idata) const
//        {return GetOvalArr()->GetValElm(idata);};
//    virtual double GetOvalSerrElm(long idata) const
//        {MPrintErrVFunc; abort();};
//    virtual double GetOvalTerrPlusElm(long idata) const
//        {MPrintErrVFunc; abort();};
//    virtual double GetOvalTerrMinusElm(long idata) const
//        {MPrintErrVFunc; abort();};
//    
//    // stat
//    double GetXvalAtOvalMin() const;
//    double GetXvalAtOvalMax() const;
//    double GetOvalAtXvalMin() const;
//    double GetOvalAtXvalMax() const;
//    
//    // output
//    void Save(string outfile, string format,
//              double offset_xval = 0.0,
//              double offset_oval = 0.0) const;
//    void SaveData(string outfile, string format,
//                  double offset_xval = 0.0,
//                  double offset_oval = 0.0) const;
//    void PrintInfo(FILE* fp) const;
//    virtual void PrintData(FILE* fp, string format,
//                           double offset_xval,
//                           double offset_oval) const = 0;
//
//    virtual TGraph* const GenTGraph(double offset_xval,
//                                    double offset_oval) const = 0;
//
//    double GetOvalIntPolLin(double xval) const;
//    // ichiji hokan
//
//    virtual Interval* const GenInterval() const
//        {MPrintErrVFunc; abort();};
//    virtual Interval* const GenIntervalAboveThreshold(double threshold) const
//        {MPrintErrVFunc; abort();};
//    virtual Interval* const GenIntervalBelowThreshold(double threshold) const
//        {MPrintErrVFunc; abort();};
//
//    // offset_tag = "st", "md", "ed", "no", value
//    double GetOffsetXFromTag(string offset_tag) const;
//    double GetOffsetOFromTag(string offset_tag) const;
//
//    int IsEqualSpaceX() const;
//
//    //
//    // static
//    //
//    static void ReadInfo(string file, int* flag_xval_sorted_ptr);

    
    return status_prog;
}
