#ifndef MORIIISM_MITOOL_MIROOTLIB_DATA1D_SERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_DATA1D_SERR_H_

#include "mi_iolib.h"
#include "mir_data1d.h"

class DataArraySerr1d : public DataArray1d{
public:
    explicit DataArraySerr1d(string title = "") :
        DataArray1d("DataArraySerr1d", title),
        val_serr_(NULL) {}
    ~DataArraySerr1d() {
        NullDataArray1d();
        NullDataArraySerr1d();
    }

    // Init
    void Init(long ndata);

    // Set
    void SetValSerr(long ndata,
                    const double* const val_serr);
    void SetValSerr(vector<double> val_serr);

    // Set element
    void SetValSerrElm(long idata, double val_serr);
  
    void Fill(long idata);
    void Fill(long idata, double weight);
    // poisson error
    void FillByMax(long idata,
                   double val,
                   double val_serr);
    void FillByMin(long idata,
                   double val,
                   double val_serr);

    void SetConst(double constant);
    void SetValErrByPoissonErr();
    
    // kinds of InitSet
    DataArraySerr1d* const Clone() const;
    void Load(string file);

    //
    // const functions
    //
  
    // get
    const double* const GetValSerr() const {return val_serr_;};
    double GetValSerrElm(long idata) const;

    // output
    void PrintData(FILE* fp, int mode,
                   double offset_val) const;

    double GetOffsetValFromTag(string offset_tag) const;
    
private:
    double* val_serr_;  // >= 0
    
    void NullDataArraySerr1d();
    void InitDataArraySerr1d(long ndata);
    void IsValSerrNotNull() const;
    void IsValSerrPlus(double val_serr) const;
};


#endif // MORIIISM_MITOOL_MIROOTLIB_DATA1D_SERR_H_
