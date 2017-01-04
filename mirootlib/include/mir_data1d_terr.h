#ifndef MORIIISM_MITOOL_MIROOTLIB_DATA1D_TERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_DATA1D_TERR_H_

#include "mir_data1d.h"

//
//  val_terr_plus_ >= 0
//  val_terr_minus_ <= 0
//

class DataArrayTerr1d : public DataArray1d{
public:
    explicit DataArrayTerr1d(string title = "") :
        DataArray1d("DataArrayTerr1d", title),
        val_terr_plus_(NULL),
        val_terr_minus_(NULL) {}
    ~DataArrayTerr1d() {
        NullDataArray1d();
        NullDataArrayTerr1d();
    }

    // Init
    void Init(long ndata);

    // Set
    void SetValTerr(long ndata,
                    const double* const val_serr);
    void SetValTerr(vector<double> val_serr);
    void SetValTerr(long ndata, 
                    const double* const val_terr_plus,
                    const double* const val_terr_minus);
    void SetValTerr(vector<double> val_terr_plus,
                    vector<double> val_terr_minus);
    void SetValAndTerr(long ndata,
                       const double* const val,
                       const double* const val_serr);
    void SetValAndTerr(vector<double> val,
                       vector<double> val_serr);
    void SetValAndTerr(long ndata,
                       const double* const val,
                       const double* const val_terr_plus,
                       const double* const val_terr_minus);
    void SetValAndTerr(vector<double> val,
                       vector<double> val_terr_plus,
                       vector<double> val_terr_minus);

    // Init & Set
    void InitSetValAndTerr(long ndata,
                           const double* const val,
                           const double* const val_serr);
    void InitSetValAndTerr(vector<double> val,
                           vector<double> val_serr);
    void InitSetValAndTerr(long ndata,
                           const double* const val,
                           const double* const val_terr_plus,
                           const double* const val_terr_minus);
    void InitSetValAndTerr(vector<double> val,
                           vector<double> val_terr_plus,
                           vector<double> val_terr_minus);
    // kinds of Set
    void SetValTerrElm(long idata, double val_serr);
    void SetValTerrPlusElm(long idata, double val_terr_plus);
    void SetValTerrMinusElm(long idata, double val_terr_minus);
    
    void Fill(long idata);
    void Fill(long idata, double weight);
    // poisson error    
    void FillByMax(long idata, double val);
    void FillByMax(long idata,
                   double val,
                   double val_terr_plus,
                   double val_terr_minus);
    void FillByMin(long idata, double val);
    void FillByMin(long idata,
                   double val,
                   double val_terr_plus,
                   double val_terr_minus);

    void SetZero();
    void SetOne();
    void SetConst(double constant);

    void SetValErrByPoissonErr();

    // kinds of InitSet
    DataArrayTerr1d* const Clone() const;
    void Load(string file);

//    // operation
//    void Sort();
//    void Scale(const DataArray1d* const data_array,
//               double scale, double offset);

    //
    // const functions
    //
      
    // get
    const double* const GetValTerrPlus() const {return val_terr_plus_;};
    const double* const GetValTerrMinus() const {return val_terr_minus_;};
    double GetValTerrPlusElm(long idata) const;
    double GetValTerrMinusElm(long idata) const;

    double* const GenValSerr() const;
    double GetValSerrElm(long idata) const;

    // useful for qdp
    // min of val + val_terr_minus
    // max of val + val_terr_plus
    double GetValAndErrMin() const;
    double GetValAndErrMax() const;
    void GetRangeValQdp(double* const lo_ptr,
                        double* const up_ptr) const;
    
    // output
    void PrintData(FILE* fp, int mode,
                   double offset_val) const;

    double GetOffsetValFromTag(string offset_tag) const;
    
private:
    double* val_terr_plus_;   // >= 0
    double* val_terr_minus_;  // <= 0

    void NullDataArrayTerr1d();
    void InitDataArrayTerr1d(long ndata);
    int IsValTerrNotNull() const;
    int IsValTerrPlusPlus(double val_terr_plus) const;
    int IsValTerrMinusMinus(double val_terr_minus) const;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_DATA1D_TERR_H_
