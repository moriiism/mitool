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

    void Init(long ndata);
    void SetValTerr(long ndata,
                    const double* const val_serr);
    void SetValTerr(vector<double> val_serr);
    void SetValTerr(long ndata, 
                    const double* const val_terr_plus,
                    const double* const val_terr_minus);
    void SetValTerr(vector<double> val_terr_plus,
                    vector<double> val_terr_minus);
    void SetValTerrElm(long idata, double val_serr);
    void SetValTerrPlusElm(long idata, double val_terr_plus);
    void SetValTerrMinusElm(long idata, double val_terr_minus);
    
    void Fill(long idata);
    void Fill(long idata, double weight);
    void FillByMax(long idata, double val);
    void FillByMax(long idata,
                   double val,
                   double val_serr);
    void FillByMax(long idata,
                   double val,
                   double val_terr_plus,
                   double val_terr_minus);
    void FillByMin(long idata, double val);
    void FillByMin(long idata,
                   double val,
                   double val_serr);
    void FillByMin(long idata,
                   double val,
                   double val_terr_plus,
                   double val_terr_minus);
    void SetConst(double constant);
    void SetValErrByPoissonErr();
    DataArrayTerr1d* const Clone() const;
    void Load(string file);
    void Sort();

    //
    // const functions
    //
    const double* const GetValTerrPlus() const {return val_terr_plus_;};
    const double* const GetValTerrMinus() const {return val_terr_minus_;};
    double GetValSerrElm(long idata) const;    
    double GetValTerrPlusElm(long idata) const;
    double GetValTerrMinusElm(long idata) const;
    double* const GenValSerr() const;

    double GetValAndErrMin() const;
    double GetValAndErrMax() const;
    void PrintData(FILE* fp, int mode,
                   double offset_val) const;
    double GetOffsetValFromTag(string offset_tag) const;
    
private:
    double* val_terr_plus_;   // >= 0
    double* val_terr_minus_;  // <= 0

    void NullDataArrayTerr1d();
    void InitDataArrayTerr1d(long ndata);
    void IsValTerrNotNull() const;
    void IsValTerrPlusPlus(double val_terr_plus) const;
    void IsValTerrMinusMinus(double val_terr_minus) const;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_DATA1D_TERR_H_
