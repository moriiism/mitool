#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_interval.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

    void Init(long nterm);
    void Set(long nterm,
             const double* const tstart,
             const double* const tstop);
    void Set(vector<double> tstart,
             vector<double> tstop);
    void InitSet(long nterm,
                 const double* const tstart,
                 const double* const tstop);
    void InitSet(vector<double> tstart,
                 vector<double> tstop);
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


    return status_prog;
}
