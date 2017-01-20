#ifndef MORIIISM_MITOOL_MIROOTLIB_CONT_H_
#define MORIIISM_MITOOL_MIROOTLIB_CONT_H_

#include "mir_graph2d.h"

//
// to hold contour
//

class MirCont : public MiObject{
public:
    explicit MirCont(string title = "") :
        MiObject("MirCont", title),
        ngraph_(0),
        gd2d_arr_(NULL) {}
    ~MirCont() {
        Null();
    }
    void Init(int ngraph);
    void SetGd2dArr(int ngraph,
                    const GraphData2d* const* const gd2d_arr);
    void AddPolygon(int npoint,
                    const double* const xval_arr,
                    const double* const yval_arr);

    void Copy(const MirCont* const org);
    
    int GetNgraph() const {return ngraph_;};
    const GraphData2d* const* const GetGd2dArr() const {return gd2d_arr_;};
    const GraphData2d* const GetGd2dArrElm(int igraph) const {return gd2d_arr_[igraph];};

    string GetPolygonStr(int igraph) const;
    MirCont* const GenShift(double delta_xval, double delta_yval) const;

private:
    // fill in counter-clockwise
    // each graph is closed polygon.
    int ngraph_;
    GraphData2d** gd2d_arr_;

    void Null();
};


class MirContWithBest : public MiObject{
public:
    explicit MirContWithBest(string title = "") :
        MiObject("MirContWithBest", title),
        xval_best_(0.0),
        yval_best_(0.0),
        cont_(NULL) {}
    ~MirContWithBest() {
        Null();
    }
    void Init();
    void SetBest(double xval_best, double yval_best);
    void SetCont(const MirCont* const cont);

    void Copy(const MirContWithBest* const org);
    
    double GetXvalBest() const {return xval_best_;};
    double GetYvalBest() const {return yval_best_;};
    const MirCont* const GetCont() const {return cont_;};

    MirContWithBest* const GenShift(double delta_xval, double delta_yval) const;
    
private:
    double xval_best_;
    double yval_best_;
    MirCont* cont_;
    void Null();
};

#endif // MORIIISM_MITOOL_MIROOTLIB_CONT_H_
