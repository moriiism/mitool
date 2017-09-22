#ifndef MORIIISM_MITOOL_MIMINUITLIB_MINFCN_H_
#define MORIIISM_MITOOL_MIMINUITLIB_MINFCN_H_

#include "Minuit2/FCNBase.h"
#include "Math/QuantFuncMathMore.h"

#include "mir_func.h"
#include "mir_hist1d_nerr.h"
#include "mir_hist2d_nerr.h"
#include "mim_func_par_index.h"

class MinFcn : public ROOT::Minuit2::FCNBase, public MiObject{
public:
    explicit MinFcn(string title = "") :
        MiObject("MinFcn", title),
        up_minfcn_(0.0),
        flag_bad_neg_ptr_assign_(NULL){}
    MinFcn(string class_name, string title) :
        MiObject(class_name, title),
        up_minfcn_(0.0),
        flag_bad_neg_ptr_assign_(NULL){}
    virtual ~MinFcn()
        {
            NullMinFcn();
        }

    // --- necessary functions in Minuit2/FCNBase.h

    double operator()(const vector<double>& par_vec) const {return Eval(par_vec);};
    double Up() const {return up_minfcn_;};
    double Eval(vector<double> par_vec) const;
    virtual double Eval(int npar, const double* const par_arr) const = 0;
    void SetErrorDef(double up_minfcn);
    
    // === necessary functions in Minuit2/FCNBase.h

    void SetFlagBadNegPtrAssign(int* flag_bad_neg_ptr) {flag_bad_neg_ptr_assign_ = flag_bad_neg_ptr;};
    void SetFlagBadNeg(int flag_bad_neg) const {*flag_bad_neg_ptr_assign_ = flag_bad_neg;};

    virtual MinFcn* const Clone() const = 0;
    
    // const func
    virtual int GetFlagBadNeg() const {return *flag_bad_neg_ptr_assign_;};

    double GetRepulsion(double val_neg) const;
    virtual long GetNdataValid() const = 0;

    static double GetUpMinfcn(double value, string mode, int as_npar);

protected:
    void CopyMinFcn(const MinFcn* const org);

private:
    double up_minfcn_;
    int* flag_bad_neg_ptr_assign_;
    
    void NullMinFcn();
};


class MinFcnOne : public MinFcn{
public:
    explicit MinFcnOne(string title = "") :
        MinFcn("MinFcnOne", title),
        func_(NULL),
        ndata_(0),
        xval_arr_(NULL),
        yval_arr_(NULL),
        oval_arr_(NULL),
        oval_serr_arr_(NULL),
        oval_terr_plus_arr_(NULL),
        oval_terr_minus_arr_(NULL),
        flag_bad_arr_(NULL) {}
    MinFcnOne(string class_name, string title) :
        MinFcn(class_name, title),
        func_(NULL),
        ndata_(0),
        xval_arr_(NULL),
        yval_arr_(NULL),
        oval_arr_(NULL),
        oval_serr_arr_(NULL),
        oval_terr_plus_arr_(NULL),
        oval_terr_minus_arr_(NULL),
        flag_bad_arr_(NULL) {}
    virtual ~MinFcnOne()
        {
            NullMinFcnOne();
        }

    //
    // Init & Set
    //
    void InitSetFunc(const MirFunc* const func);

    //
    // 1d function
    //
    void InitSetData1d(long ndata,
                       const double* const xval_arr);
    void InitSetData1d(long ndata,
                       const double* const xval_arr,
                       const double* const oval_arr);
    void InitSetData1d(long ndata,
                       const double* const xval_arr,
                       const double* const oval_arr,
                       const double* const oval_serr_arr);
    void InitSetData1d(long ndata,
                       const double* const xval_arr,
                       const double* const oval_arr,
                       const double* const oval_terr_plus_arr,
                       const double* const oval_terr_minus_arr);
    //
    // 2d function
    //
    void InitSetData2d(long ndata,
                       const double* const xval_arr,
                       const double* const yval_arr);
    void InitSetData2d(long ndata,
                       const double* const xval_arr,
                       const double* const yval_arr,
                       const double* const oval_arr);
    void InitSetData2d(long ndata,
                       const double* const xval_arr,
                       const double* const yval_arr,
                       const double* const oval_arr,
                       const double* const oval_serr_arr);
    void InitSetData2d(long ndata,
                       const double* const xval_arr,
                       const double* const yval_arr,
                       const double* const oval_arr,
                       const double* const oval_terr_plus_arr,
                       const double* const oval_terr_minus_arr);

    // oval > 0
    void InitSetData1d_ValGt0(long ndata,
                           const double* const xval_arr,
                           const double* const oval_arr);
    // oval >= 0
    void InitSetData1d_ValGe0(long ndata,
                           const double* const xval_arr,
                           const double* const oval_arr);    
    // oval_serr > 0
    void InitSetData1d_ErrGt0(long ndata,
                              const double* const xval_arr,
                              const double* const oval_arr,
                              const double* const oval_serr_arr);
    // oval_terr_plus  > 0
    // oval_terr_minus > 0
    void InitSetData1d_ErrGt0(long ndata,
                              const double* const xval_arr,
                              const double* const oval_arr,
                              const double* const oval_terr_plus_arr,
                              const double* const oval_terr_minus_arr);

    // oval > 0
    void InitSetData2d_ValGt0(long ndata,
                              const double* const xval_arr,
                              const double* const yval_arr,
                              const double* const oval_arr);
    // oval >= 0
    void InitSetData2d_ValGe0(long ndata,
                              const double* const xval_arr,
                              const double* const yval_arr,
                              const double* const oval_arr);    
    // oval_serr > 0
    void InitSetData2d_ErrGt0(long ndata,
                              const double* const xval_arr,
                              const double* const yval_arr,
                              const double* const oval_arr,
                              const double* const oval_serr_arr);
    // oval_terr_plus  > 0
    // oval_terr_minus > 0
    void InitSetData2d_ErrGt0(long ndata,
                              const double* const xval_arr,
                              const double* const yval_arr,
                              const double* const oval_arr,
                              const double* const oval_terr_plus_arr,
                              const double* const oval_terr_minus_arr);

    virtual MinFcnOne* const Clone() const = 0;

    // const func
    const MirFunc* const GetFunc() const {return func_;};
    long GetNdata() const {return ndata_;};
    double* const GetXvalArr() const {return xval_arr_;};
    double* const GetYvalArr() const {return yval_arr_;};
    double* const GetOvalArr() const {return oval_arr_;};
    double* const GetOvalSerrArr() const {return oval_serr_arr_;};
    double* const GetOvalTerrPlusArr() const {return oval_terr_plus_arr_;};
    double* const GetOvalTerrMinusArr() const {return oval_terr_minus_arr_;};
    int* const GetFlagBadArr() const {return flag_bad_arr_;};

    double GetXvalArrElm(long idata) const {return xval_arr_[idata];};
    double GetYvalArrElm(long idata) const {return yval_arr_[idata];};
    double GetOvalArrElm(long idata) const {return oval_arr_[idata];};
    double GetOvalSerrArrElm(long idata) const {return oval_serr_arr_[idata];};
    double GetOvalTerrPlusArrElm(long idata) const {return oval_terr_plus_arr_[idata];};
    double GetOvalTerrMinusArrElm(long idata) const {return oval_terr_minus_arr_[idata];};
    int    GetFlagBadArrElm(long idata) const {return flag_bad_arr_[idata];};
    
    long GetNdataValid() const;

    static MinFcnOne* const GenMinFcnOne(string minfcn_name,
                                         const MirFunc* const func,
                                         long ndata,
                                         const double* const xval_arr,
                                         const double* const yval_arr,
                                         const double* const oval_arr,
                                         const double* const oval_serr_arr,
                                         const double* const oval_terr_plus_arr,
                                         const double* const oval_terr_minus_arr,
                                         const HistData1d* const hd1d_mask,
                                         const HistData2d* const hd2d_mask);

protected:
    void CopyMinFcnOne(const MinFcnOne* const org);

private:
    // data: xval_arr, yval_arr, ... ---> oval_arr
    // function: f(x, y, z, ...)
    
    MirFunc* func_;
    long ndata_;    
    double* xval_arr_;
    double* yval_arr_;
    double* oval_arr_;
    double* oval_serr_arr_;
    double* oval_terr_plus_arr_;
    double* oval_terr_minus_arr_;
    int* flag_bad_arr_;
    
    void NullMinFcnOne();
};


//
// 1-dim
//

//
// Gaussian
//

class Chi2Fcn1d : public MinFcnOne{
public:
    explicit Chi2Fcn1d(string title = "") :
        MinFcnOne("Chi2Fcn1d", title) {}
    ~Chi2Fcn1d() {}
    void Copy(const Chi2Fcn1d* const org);
    Chi2Fcn1d* const Clone() const;
    double Eval(int npar, const double* const par_arr) const;
};

class Chi2FcnAsym1d : public MinFcnOne{
public:
    explicit Chi2FcnAsym1d(string title = "") :
        MinFcnOne("Chi2FcnAsym1d", title) {}
    ~Chi2FcnAsym1d() {}
    void Copy(const Chi2FcnAsym1d* const org);
    Chi2FcnAsym1d* const Clone() const;
    double Eval(int npar, const double* const par_arr) const;
};

//
// Poisson
//

// Pearson's Chi2 statistic
class Chi2PearsonFcn1d : public MinFcnOne{
public:
    explicit Chi2PearsonFcn1d(string title = "") :
        MinFcnOne("Chi2PearsonFcn1d", title) {}
    ~Chi2PearsonFcn1d() {}
    void Copy(const Chi2PearsonFcn1d* const org);
    Chi2PearsonFcn1d* const Clone() const;
    double Eval(int npar, const double* const par_arr) const;
};

// Pearson's Chi2 statistic in physical region
class Chi2PearsonPhysFcn1d : public MinFcnOne{
public:
    explicit Chi2PearsonPhysFcn1d(string title = "") :
        MinFcnOne("Chi2PearsonPhysFcn1d", title) {}
    ~Chi2PearsonPhysFcn1d() {}
    void Copy(const Chi2PearsonPhysFcn1d* const org);
    Chi2PearsonPhysFcn1d* const Clone() const;    
    double Eval(int npar, const double* const par_arr) const;
};

// Neyman's Chi2 statistic
class Chi2NeymanFcn1d : public MinFcnOne{
public:
    explicit Chi2NeymanFcn1d(string title = "") :
        MinFcnOne("Chi2NeymanFcn1d", title) {}
    ~Chi2NeymanFcn1d() {}
    void Copy(const Chi2NeymanFcn1d* const org);
    Chi2NeymanFcn1d* const Clone() const;        
    double Eval(int npar, const double* const par_arr) const;
};

// Neyman's Chi2 statistic in physical region
class Chi2NeymanPhysFcn1d : public MinFcnOne{
public:
    explicit Chi2NeymanPhysFcn1d(string title = "") :
        MinFcnOne("Chi2NeymanPhysFcn1d", title) {}
    ~Chi2NeymanPhysFcn1d() {}
    void Copy(const Chi2NeymanPhysFcn1d* const org);
    Chi2NeymanPhysFcn1d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};

// modified Neyman's Chi2 statistic
class Chi2NeymanModFcn1d : public MinFcnOne{
public:
    explicit Chi2NeymanModFcn1d(string title = "") :
        MinFcnOne("Chi2NeymanModFcn1d", title) {}
    ~Chi2NeymanModFcn1d() {}
    void Copy(const Chi2NeymanModFcn1d* const org);
    Chi2NeymanModFcn1d* const Clone() const;       
    double Eval(int npar, const double* const par_arr) const;
};

// modified Neyman's Chi2 statistic in physical region
class Chi2NeymanModPhysFcn1d : public MinFcnOne{
public:
    explicit Chi2NeymanModPhysFcn1d(string title = "") :
        MinFcnOne("Chi2NeymanModPhysFcn1d", title) {}
    ~Chi2NeymanModPhysFcn1d() {}
    void Copy(const Chi2NeymanModPhysFcn1d* const org);
    Chi2NeymanModPhysFcn1d* const Clone() const;       
    double Eval(int npar, const double* const par_arr) const;
};

// Mighell's Chi2 Gamma statistic
class Chi2GammaFcn1d : public MinFcnOne{
public:
    explicit Chi2GammaFcn1d(string title = "") :
        MinFcnOne("Chi2GammaFcn1d", title) {}
    ~Chi2GammaFcn1d() {}
    void Copy(const Chi2GammaFcn1d* const org);
    Chi2GammaFcn1d* const Clone() const;       
    double Eval(int npar, const double* const par_arr) const;
};

// Mighell's Chi2 Gamma statistic in physical region
class Chi2GammaPhysFcn1d : public MinFcnOne{
public:
    explicit Chi2GammaPhysFcn1d(string title = "") :
        MinFcnOne("Chi2GammaPhysFcn1d", title) {}
    ~Chi2GammaPhysFcn1d() {}
    void Copy(const Chi2GammaPhysFcn1d* const org);
    Chi2GammaPhysFcn1d* const Clone() const;       
    double Eval(int npar, const double* const par_arr) const;
};


//
// Poisson c-stat
//

// Cash's c-stat
class CstatFcn1d : public MinFcnOne{
public:
    explicit CstatFcn1d(string title = "") :
        MinFcnOne("CstatFcn1d", title) {}
    ~CstatFcn1d() {}
    void Copy(const CstatFcn1d* const org);
    CstatFcn1d* const Clone() const;          
    double Eval(int npar, const double* const par_arr) const;
};

// Cash's c-stat in physical region
class CstatPhysFcn1d : public MinFcnOne{
public:
    explicit CstatPhysFcn1d(string title = "") :
        MinFcnOne("CstatPhysFcn1d", title) {}
    ~CstatPhysFcn1d() {}
    void Copy(const CstatPhysFcn1d* const org);
    CstatPhysFcn1d* const Clone() const;       
    double Eval(int npar, const double* const par_arr) const;
};

// chi2_lambda statistic
class CstatDeltaFcn1d : public MinFcnOne{
public:
    explicit CstatDeltaFcn1d(string title = "") :
        MinFcnOne("CstatDeltaFcn1d", title) {}
    ~CstatDeltaFcn1d() {}
    void Copy(const CstatDeltaFcn1d* const org);
    CstatDeltaFcn1d* const Clone() const;       
    double Eval(int npar, const double* const par_arr) const;
};

// chi2_lambda statistic in physical region
class CstatDeltaPhysFcn1d : public MinFcnOne{
public:
    explicit CstatDeltaPhysFcn1d(string title = "") :
        MinFcnOne("CstatDeltaPhysFcn1d", title) {}
    ~CstatDeltaPhysFcn1d() {}
    void Copy(const CstatDeltaPhysFcn1d* const org);
    CstatDeltaPhysFcn1d* const Clone() const;       
    double Eval(int npar, const double* const par_arr) const;
};

// Cash's c-stat unbin 
class CstatUnbinFcn1d : public MinFcnOne{
public:
    explicit CstatUnbinFcn1d(string title = "") :
        MinFcnOne("CstatUnbinFcn1d", title),
        hd1d_mask_(NULL),
        hd1d_inner_(NULL) {}
    ~CstatUnbinFcn1d() {
        Null();
    }
    void InitSetHd1dMask(const HistData1d* const hd1d_mask);

    void Copy(const CstatUnbinFcn1d* const org);
    CstatUnbinFcn1d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
    HistData1d* const GetHd1dMask() const {return hd1d_mask_;};
    HistData1d* const GetHd1dInner() const {return hd1d_inner_;};
private:
    HistData1d* hd1d_mask_;
    HistData1d* hd1d_inner_;
    double GetIntegral(int npar, const double* const par_arr) const;

    void Null();
};

// Cash's c-stat unbin in physical region
class CstatUnbinPhysFcn1d : public MinFcnOne{
public:
    explicit CstatUnbinPhysFcn1d(string title = "") :
        MinFcnOne("CstatUnbinPhysFcn1d", title),
        hd1d_mask_(NULL),
        hd1d_inner_(NULL) {}
    ~CstatUnbinPhysFcn1d() {
        Null();
    }
    void InitSetHd1dMask(const HistData1d* const hd1d_mask);

    void Copy(const CstatUnbinPhysFcn1d* const org);
    CstatUnbinPhysFcn1d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
    HistData1d* const GetHd1dMask() const {return hd1d_mask_;};
    HistData1d* const GetHd1dInner() const {return hd1d_inner_;};
private:
    HistData1d* hd1d_mask_;
    HistData1d* hd1d_inner_;
    double GetIntegral(int npar, const double* const par_arr,
                       double* const sum_of_val_minus_ptr) const;
    void Null();
};

//
// 2-dim
//

//
// Gaussian
// 

class Chi2Fcn2d : public MinFcnOne{
public:
    explicit Chi2Fcn2d(string title = "") :
        MinFcnOne("Chi2Fcn2d", title) {}
    ~Chi2Fcn2d() {}
    void Copy(const Chi2Fcn2d* const org);
    Chi2Fcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};

class Chi2FcnAsym2d : public MinFcnOne{
public:
    explicit Chi2FcnAsym2d(string title = "") :
        MinFcnOne("Chi2FcnAsym2d", title) {}
    ~Chi2FcnAsym2d() {}
    void Copy(const Chi2FcnAsym2d* const org);
    Chi2FcnAsym2d* const Clone() const;       
    double Eval(int npar, const double* const par_arr) const;
};

//
// Poisson
//

// Pearson's Chi2 statistic
class Chi2PearsonFcn2d : public MinFcnOne{
public:
    explicit Chi2PearsonFcn2d(string title = "") :
        MinFcnOne("Chi2PearsonFcn2d", title) {}
    ~Chi2PearsonFcn2d() {}
    void Copy(const Chi2PearsonFcn2d* const org);
    Chi2PearsonFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};

// Pearson's Chi2 statistic in physical region
class Chi2PearsonPhysFcn2d : public MinFcnOne{
public:
    explicit Chi2PearsonPhysFcn2d(string title = "") :
        MinFcnOne("Chi2PearsonPhysFcn2d", title) {}
    ~Chi2PearsonPhysFcn2d() {}
    void Copy(const Chi2PearsonPhysFcn2d* const org);
    Chi2PearsonPhysFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};


// Neyman's Chi2 statistic
class Chi2NeymanFcn2d : public MinFcnOne{
public:
    explicit Chi2NeymanFcn2d(string title = "") :
        MinFcnOne("Chi2NeymanFcn2d", title) {}
    ~Chi2NeymanFcn2d() {}
    void Copy(const Chi2NeymanFcn2d* const org);
    Chi2NeymanFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};

// Neyman's Chi2 statistic in physical region
class Chi2NeymanPhysFcn2d : public MinFcnOne{
public:
    explicit Chi2NeymanPhysFcn2d(string title = "") :
        MinFcnOne("Chi2NeymanPhysFcn2d", title) {}
    ~Chi2NeymanPhysFcn2d() {}
    void Copy(const Chi2NeymanPhysFcn2d* const org);
    Chi2NeymanPhysFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};

// modified Neyman's Chi2 statistic
class Chi2NeymanModFcn2d : public MinFcnOne{
public:
    explicit Chi2NeymanModFcn2d(string title = "") :
        MinFcnOne("Chi2NeymanModFcn2d", title) {}
    ~Chi2NeymanModFcn2d() {}
    void Copy(const Chi2NeymanModFcn2d* const org);
    Chi2NeymanModFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};

// modified Neyman's Chi2 statistic in physical region
class Chi2NeymanModPhysFcn2d : public MinFcnOne{
public:
    explicit Chi2NeymanModPhysFcn2d(string title = "") :
        MinFcnOne("Chi2NeymanModPhysFcn2d", title) {}
    ~Chi2NeymanModPhysFcn2d() {}
    void Copy(const Chi2NeymanModPhysFcn2d* const org);
    Chi2NeymanModPhysFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};


// Mighell's Chi2 Gamma statistic
class Chi2GammaFcn2d : public MinFcnOne{
public:
    explicit Chi2GammaFcn2d(string title = "") :
        MinFcnOne("Chi2GammaFcn2d", title) {}
    ~Chi2GammaFcn2d() {}
    void Copy(const Chi2GammaFcn2d* const org);
    Chi2GammaFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};

// Mighell's Chi2 Gamma statistic in physical region
class Chi2GammaPhysFcn2d : public MinFcnOne{
public:
    explicit Chi2GammaPhysFcn2d(string title = "") :
        MinFcnOne("Chi2GammaPhysFcn2d", title) {}
    ~Chi2GammaPhysFcn2d() {}
    void Copy(const Chi2GammaPhysFcn2d* const org);
    Chi2GammaPhysFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};


//
// Poisson c-stat
//

// Cash's c-stat
class CstatFcn2d : public MinFcnOne{
public:
    explicit CstatFcn2d(string title = "") :
        MinFcnOne("CstatFcn2d", title) {}
    ~CstatFcn2d() {}
    void Copy(const CstatFcn2d* const org);
    CstatFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};

// Cash's c-stat in physical region
class CstatPhysFcn2d : public MinFcnOne{
public:
    explicit CstatPhysFcn2d(string title = "") :
        MinFcnOne("CstatPhysFcn2d", title) {}
    ~CstatPhysFcn2d() {}
    void Copy(const CstatPhysFcn2d* const org);
    CstatPhysFcn2d* const Clone() const;
    double Eval(int npar, const double* const par_arr) const;
    double GetProb(int npar, const double* const par_arr) const;
};

// chi2_lambda statistic
class CstatDeltaFcn2d : public MinFcnOne{
public:
    explicit CstatDeltaFcn2d(string title = "") :
        MinFcnOne("CstatDeltaFcn2d", title) {}
    ~CstatDeltaFcn2d() {}
    void Copy(const CstatDeltaFcn2d* const org);
    CstatDeltaFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};

// chi2_lambda statistic in physical region
class CstatDeltaPhysFcn2d : public MinFcnOne{
public:
    explicit CstatDeltaPhysFcn2d(string title = "") :
        MinFcnOne("CstatDeltaPhysFcn2d", title) {}
    ~CstatDeltaPhysFcn2d() {}
    void Copy(const CstatDeltaPhysFcn2d* const org);
    CstatDeltaPhysFcn2d* const Clone() const;       
    double Eval(int npar, const double* const par_arr) const;
};

// Cash's c-stat unbin 
class CstatUnbinFcn2d : public MinFcnOne{
public:
    explicit CstatUnbinFcn2d(string title = "") :
        MinFcnOne("CstatUnbinFcn2d", title),
        hd2d_mask_(NULL),
        hd2d_inner_(NULL) {}
    ~CstatUnbinFcn2d() {
        Null();
    }
    void InitSetHd2dMask(const HistData2d* const hd2d_mask);

    void Copy(const CstatUnbinFcn2d* const org);
    CstatUnbinFcn2d* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
    HistData2d* const GetHd2dMask() const {return hd2d_mask_;};
    HistData2d* const GetHd2dInner() const {return hd2d_inner_;};
private:
    HistData2d* hd2d_mask_;
    HistData2d* hd2d_inner_;
    double GetIntegral(int npar, const double* const par_arr) const;
    void Null();
};

// Cash's c-stat unbin in physical region
class CstatUnbinPhysFcn2d : public MinFcnOne{
public:
    explicit CstatUnbinPhysFcn2d(string title = "") :
        MinFcnOne("CstatUnbinPhysFcn2d", title),
        hd2d_mask_(NULL),
        hd2d_inner_(NULL) {}
    ~CstatUnbinPhysFcn2d() {
        Null();
    }
    void InitSetHd2dMask(const HistData2d* const hd2d_mask);

    void Copy(const CstatUnbinPhysFcn2d* const org);
    CstatUnbinPhysFcn2d* const Clone() const;       
    double Eval(int npar, const double* const par_arr) const;
    HistData2d* const GetHd2dMask() const {return hd2d_mask_;};
    HistData2d* const GetHd2dInner() const {return hd2d_inner_;};
private:
    HistData2d* hd2d_mask_;
    HistData2d* hd2d_inner_;
    double GetIntegral(int npar, const double* const par_arr,
                       double* const sum_of_val_minus_ptr) const;
    void Null();
};


////
//// PSD
////
//
//// 1-dim 
//class PsdFcn1d : public MinFcnOne{
//public:
//    explicit PsdFcn1d(string title = "") :
//        MinFcnOne("PsdFcn1d", title) {}
//    ~PsdFcn1d() {}
//    void Copy(const PsdFcn1d* const org);
//    PsdFcn1d* const Clone() const;       
//    double Eval(int npar, const double* const par_arr) const;
//};



class MinFcnMulti : public MinFcn{
public:
    explicit MinFcnMulti(string title = "") :
        MinFcn("MinFcnMulti", title),
        num_minfcn1_(0),
        minfcn1_arr_(NULL) {}
    MinFcnMulti(string class_name, string title) :
        MinFcn(class_name, title),
        num_minfcn1_(0),
        minfcn1_arr_(NULL) {}
    virtual ~MinFcnMulti()
        {
            NullMinFcnMulti();
        }
    void InitSetMinfcn1Arr(int num_minfcn1, MinFcnOne** const minfcn1_arr);

    virtual MinFcnMulti* const Clone() const = 0;
    virtual double Eval(int npar, const double* const par_arr) const = 0;
    
    // const func
    int GetNumMinfcn1() const {return num_minfcn1_;};
    MinFcnOne** GetMinfcn1Arr() const {return minfcn1_arr_;};
    MinFcnOne* GetMinfcn1ArrElm(int iminfcn) const {return minfcn1_arr_[iminfcn];};

    int GetFlagBadNeg() const;
    long GetNdataValid() const;

protected:
    void CopyMinFcnMulti(const MinFcnMulti* const org);
    
private:
    int num_minfcn1_;
    MinFcnOne** minfcn1_arr_;
    
    void NullMinFcnMulti();
};


class MinFcnMultiSame : public MinFcnMulti{
public:
    explicit MinFcnMultiSame(string title = "") :
        MinFcnMulti("MinFcnMultiSame", title) {}
    ~MinFcnMultiSame() {}
    void Copy(const MinFcnMultiSame* const org);
    MinFcnMultiSame* const Clone() const;           
    double Eval(int npar, const double* const par_arr) const;
};


class MinFcnLincombMultiTie : public MinFcnMulti{
public:
    explicit MinFcnLincombMultiTie(string title = "") :
        MinFcnMulti("MinFcnLincombMultiTie", title),
        func_lincomb_par_index_assign_(NULL) {}
    ~MinFcnLincombMultiTie() {
        Null();
    }

    void SetFuncLincombParIndex(const MimFuncLincombParIndex* const func_lincomb_par_index);
    void Copy(const MinFcnLincombMultiTie* const org);
    
    double Eval(int npar, const double* const par_arr) const;
    MinFcnLincombMultiTie* const Clone() const;
    const MimFuncLincombParIndex* const GetFuncLincombParIndex() const {return func_lincomb_par_index_assign_;};

private:
    const MimFuncLincombParIndex* func_lincomb_par_index_assign_;
    void Null();
};


//
// Phot
//

class MinFcnPhot : public MinFcn{
public:
    explicit MinFcnPhot(string title = "") :
        MinFcn("MinFcnPhot", title),
        ndata_(0),
        nevt_src_arr_(NULL),
        nevt_bg_arr_(NULL),
        effarea_arr_(NULL),
        area_src_arr_(NULL),
        area_bg_arr_(NULL),
        exposure_arr_(NULL) {}
    ~MinFcnPhot()
        {
            Null();
        }
    void InitSet(int ndata,
                 const int* const nevt_src_arr,
                 const int* const nevt_bg_arr,
                 const double* const effarea_arr,
                 const double* const area_src_arr,
                 const double* const area_bg_arr,
                 const double* const exposure_arr);
    void Copy(const MinFcnPhot* const org);
    MinFcnPhot* const Clone() const;    
    double Eval(int npar, const double* const par_arr) const;
    long GetNdataValid() const;

    // const func
    int GetNdata() const {return ndata_;};
    int* GetNevtSrcArr() const {return nevt_src_arr_;};
    int* GetNevtBgArr() const {return nevt_bg_arr_;};
    double* GetEffareaArr() const {return effarea_arr_;};
    double* GetAreaSrcArr() const {return area_src_arr_;};
    double* GetAreaBgArr() const {return area_bg_arr_;};
    double* GetExposureArr() const {return exposure_arr_;};

    int GetNevtSrcArrElm(int idata) const {return nevt_src_arr_[idata];};
    int GetNevtBgArrElm(int idata) const {return nevt_bg_arr_[idata];};
    double GetEffareaArrElm(int idata) const {return effarea_arr_[idata];};
    double GetAreaSrcArrElm(int idata) const {return area_src_arr_[idata];};
    double GetAreaBgArrElm(int idata) const {return area_bg_arr_[idata];};
    double GetExposureArrElm(int idata) const {return exposure_arr_[idata];};
    
private:
    int ndata_;
    int* nevt_src_arr_;
    int* nevt_bg_arr_;
    double* effarea_arr_;
    double* area_src_arr_;
    double* area_bg_arr_;
    double* exposure_arr_;

    void Null();
};


class MinFcnPhotScan : public MinFcn{
public:
    explicit MinFcnPhotScan(string title = "") :
        MinFcn("MinFcnPhotScan", title),
        ndata_(0),
        nevt_src_arr_(NULL),
        nevt_bg_arr_(NULL),
        effarea_time_arr_(NULL),
        area_src_arr_(NULL),
        area_bg_arr_(NULL) {}
    ~MinFcnPhotScan()
        {
            Null();
        }
    void InitSet(int ndata,
                 const int* const nevt_src_arr,
                 const int* const nevt_bg_arr,
                 const double* const effarea_time_arr,
                 const double* const area_src_arr,
                 const double* const area_bg_arr);
    void Copy(const MinFcnPhotScan* const org);
    MinFcnPhotScan* const Clone() const;    
    double Eval(int npar, const double* const par_arr) const;
    long GetNdataValid() const;

    // const func
    int GetNdata() const {return ndata_;};
    int* GetNevtSrcArr() const {return nevt_src_arr_;};
    int* GetNevtBgArr() const {return nevt_bg_arr_;};
    double* GetEffareaTimeArr() const {return effarea_time_arr_;};
    double* GetAreaSrcArr() const {return area_src_arr_;};
    double* GetAreaBgArr() const {return area_bg_arr_;};

    int GetNevtSrcArrElm(int idata) const {return nevt_src_arr_[idata];};
    int GetNevtBgArrElm(int idata) const {return nevt_bg_arr_[idata];};
    double GetEffareaTimeArrElm(int idata) const {return effarea_time_arr_[idata];};
    double GetAreaSrcArrElm(int idata) const {return area_src_arr_[idata];};
    double GetAreaBgArrElm(int idata) const {return area_bg_arr_[idata];};
    
private:
    int ndata_;
    int* nevt_src_arr_;
    int* nevt_bg_arr_;
    double* effarea_time_arr_;
    double* area_src_arr_;
    double* area_bg_arr_;

    void Null();
};

#endif // MORIIISM_MITOOL_MIMINUITLIB_MINFCN_H_
