#ifndef MORIIISM_MITOOL_MIFUNCLIB_HIST1D_H_
#define MORIIISM_MITOOL_MIFUNCLIB_HIST1D_H_

#include "mir_hist1d.h"

// function made from HistData1d

class Hd1dFunc : public MirFunc{
public:
    explicit Hd1dFunc(string title = "") :
        MirFunc("Hd1dFunc", title),
        hd1d_(NULL)
        {
            SetNpar(0);
            SetNdim(1);
        }
    ~Hd1dFunc()
        {
            Null();
        }
    void InitSetHd1d(const HistData1d* const hd1d);
    void Copy(const Hd1dFunc* const org);
    Hd1dFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    const HistData1d* const GetHd1d() const {return hd1d_;};
private:
    HistData1d* hd1d_;
    void Null();
};

class Hd1dInvFunc : public MirFunc{
public:
    explicit Hd1dInvFunc(string title = "") :
        MirFunc("Hd1dInvFunc", title),
        hd1d_(NULL),
        index_sort_arr_(NULL),
        oval_sort_arr_(NULL)
        {
            SetNpar(0);
            SetNdim(1);
        }
    ~Hd1dInvFunc()
        {
            Null();
        }
    void InitSetHd1d(const HistData1d* const hd1d);
    void Copy(const Hd1dInvFunc* const org);
    Hd1dInvFunc* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;

    const HistData1d* const GetHd1d() const {return hd1d_;};
private:
    HistData1d* hd1d_;

    long* index_sort_arr_;
    double* oval_sort_arr_;

    long GetIndexSortArrElm(long index) const {return index_sort_arr_[index];};
    const double* const GetOvalSortArr() const {return oval_sort_arr_;};

    void SetOvalArrSort();
    void Null();
};

#endif // MORIIISM_MITOOL_MIFUNCLIB_HIST1D_H_
