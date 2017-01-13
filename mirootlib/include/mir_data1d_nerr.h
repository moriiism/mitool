#ifndef MORIIISM_MITOOL_MIROOTLIB_DATA1D_NERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_DATA1D_NERR_H_

#include "mi_iolib.h"
#include "mir_data1d.h"
#include "mir_math.h"

class DataArrayNerr1d : public DataArray1d{
public:
    explicit DataArrayNerr1d(string title = "") :
        DataArray1d("DataArrayNerr1d", title) {}
    ~DataArrayNerr1d() {
        NullDataArray1d();
    }

    // Init
    void Init(long ndata);
    
    void Fill(long idata);
    void Fill(long idata, double weight);
    void FillByMax(long idata, double val);
    void FillByMin(long idata, double val);

    void SetConst(double constant);

    // kinds of InitSet
    DataArrayNerr1d* const Clone() const;
    void Load(string file);

    //
    // const functions
    //
    void PrintData(FILE* fp, int mode,
                   double offset_val) const;

    double GetOffsetValFromTag(string offset_tag) const;
};


#endif // MORIIISM_MITOOL_MIROOTLIB_DATA1D_NERR_H_
