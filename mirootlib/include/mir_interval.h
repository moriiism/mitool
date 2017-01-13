#ifndef MORIIISM_MITOOL_MIROOTLIB_INTERVAL_H_
#define MORIIISM_MITOOL_MIROOTLIB_INTERVAL_H_

#include "mi_sort.h"
#include "mi_iolib.h"
#include "mir_math.h"

class Interval: public MiObject{
public:
    explicit Interval(string title = "") :
        MiObject("Interval", title),
        nterm_(0),
        tstart_(NULL),
        tstop_(NULL) {}
    ~Interval(){
        Null();
    }

    // Init
    void Init(long nterm);
    
    // set
    void Set(long nterm,
             const double* const tstart,
             const double* const tstop);
    void Set(vector<double> tstart,
             vector<double> tstop);

    // Init & Set
    void InitSet(long nterm,
                 const double* const tstart,
                 const double* const tstop);
    void InitSet(vector<double> tstart,
                 vector<double> tstop);

    // one interval
    void InitSet(double tstart, double tstop);

    void Load(string file);
    void Copy(const Interval* const org);
    Interval* const Clone() const;

    // get
    long GetNterm() const {return nterm_;};
    const double* const GetTstart() const {return tstart_;};
    const double* const GetTstop() const {return tstop_;};
    double GetTstartElm(long iterm) const {return tstart_[iterm];};
    double GetTstopElm(long iterm) const {return tstop_[iterm];};

    double* const GenTermCenter() const;
    double* const GenTermHalfWidth() const;
    double GetTermCenterElm(long iterm) const;
    double GetTermHalfWidthElm(long iterm) const;

    double GetTotalInterval() const;

    double GetFirst() const;
    double GetLast() const;

    void GetRangeQdp(double* const low_ptr, double* const up_ptr) const;
    
    int IsOrdered() const;
    int IsIn(double val) const;
    
    long GetIndexByTime(double time) const;
    long GetIndexByTimeQuick(double time) const;
    long GetIndexByTimeGE(double time) const;
    long GetIndexByTimeGEQuick(double time) const;
    double GetOffsetFromTag(string offset_tag) const;

    // save
    void Save(string file) const;
  
    // output
    void Print(FILE* fp) const;
    void PrintDataLc(FILE* fp, string lc_format, double offset = 0.0) const;

    //
    // operate
    //
    
    void Sort(string mode);
    // st: sort by start time
    // ed: sort by end time
    // md: sort by middle time
    
    void And(const Interval* const interval1, const Interval* const interval2);
    void And(const Interval* const* const interval_arr, int ninterval);
    void Or(const Interval* const interval1, const Interval* const interval2);
    void Or(const Interval* const* const interval_arr, int ninterval);
    void AddMargin(const Interval* const interval, double time_margin, double time_precision);

    void Split(const Interval* const interval_one, int ninterval);
    // divide an interval (consisting of one term) into N intervals.

    void Clean(double tdiff);
  
private:
    long    nterm_;    // number of term
    double* tstart_;
    double* tstop_;

    void Null();    
    int IsValid() const;  // valid: 1/0
};


//
// 2-dim interval: direct product of two intervals
//

class Interval2dim: public MiObject{
public:
    explicit Interval2dim(string title = "") :
        MiObject("Interval2dim", title),
        interval_x_(NULL), interval_y_(NULL) {}
    ~Interval2dim(){
        Null();
    }

    // Init
    void Init();
    
    // set
    void Set(const Interval* const interval_x,
             const Interval* const interval_y);

    // Init & Set
    void InitSet(const Interval* const interval_x,
                 const Interval* const interval_y);

    void Copy(const Interval2dim* const org);
    Interval2dim* const Clone() const;    

    // get
    const Interval* const GetIntervalX() const {return interval_x_;};
    const Interval* const GetIntervalY() const {return interval_y_;};

    int IsIn(double xval, double yval) const;
    
    // output
    void Print(FILE* fp) const;

private:
    Interval* interval_x_;
    Interval* interval_y_;

    void Null();
};


//
// n-dim interval: direct product of N intervals
//

class IntervalNdim: public MiObject{
public:
    explicit IntervalNdim(string title = "") :
        MiObject("Interval", title),
        ndim_(0),
        interval_arr_(NULL) {}
    ~IntervalNdim(){
        Null();
    }

    // Init
    void Init(long ndim);
    
    // set
    void Set(long ndim,
             const Interval* const* const interval_arr);

    // Init & Set
    void InitSet(long ndim,
                 const Interval* const* const interval_arr);

    void Copy(const IntervalNdim* const org);
    IntervalNdim* const Clone() const;

    // get
    long GetNdim() const {return ndim_;};
    const Interval* const* const GetIntervalArr() const {return interval_arr_;};
    const Interval* const GetIntervalElm(long idim) const {return interval_arr_[idim];};

    int IsIn(const double* const val_arr, long ndim) const;
    
    // output
    void Print(FILE* fp) const;

private:
    long    ndim_;
    Interval** interval_arr_;

    void Null();
};

#endif // MORIIISM_MITOOL_MIROOTLIB_INTERVAL_H_
