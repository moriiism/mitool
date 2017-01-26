#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_graph2d_nerr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_func.h"
#include "mir_root_tool.h"
#include "mir_qdp_tool.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

class FuncTest : public MirFunc{
public:
    explicit FuncTest(string title = "") :
        MirFunc("FuncTest", title)
        {
            SetNpar(3);
            SetNdim(1);           
        }
    ~FuncTest() {
        NullMirFunc();
    }

    void Copy(const FuncTest* const org);
    FuncTest* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;
};

void FuncTest::Copy(const FuncTest* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    NullMirFunc();
    SetNpar(org->GetNpar());
    SetNdim(org->GetNdim());
}

FuncTest* const FuncTest::Clone() const
{
    FuncTest* obj_new = new FuncTest;
    obj_new->Copy(this);
    return obj_new;
}

double FuncTest::Eval(const double* const xval,
                      const double* const par) const
{
    double argx = xval[0];
    double ans = par[0] + par[1] * argx + par[2] * pow(argx, 2.);
    return ans;
}

    
int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    virtual void Init(long ndata) = 0;
    {
        printf("--- test Init(long ndata)\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);

        delete gd2d;
        printf("=== \n");
    }

//    void SetXvalArr(const DataArray1d* const val_arr);
//    void SetOvalArr(const DataArray1d* const val_arr);
//    void SetFlagXvalSorted(int flag) {flag_xval_sorted_ = flag;};    
    {
        printf("--- test SetXvalArr(const DataArray1d* const val_arr)\n");
        printf("--- test SetOvalArr(const DataArray1d* const val_arr)\n");
        printf("--- test SetFlagXvalSorted(int flag)\n");

        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        DataArrayNerr1d* da1d_x = new DataArrayNerr1d;
        da1d_x->Init(4);
        da1d_x->SetValElm(0, 0.0);
        da1d_x->SetValElm(1, 1.0);
        da1d_x->SetValElm(2, 2.0);
        da1d_x->SetValElm(3, 3.0);
        gd2d->SetXvalArr(da1d_x);

        DataArrayNerr1d* da1d_o = new DataArrayNerr1d;
        da1d_o->Init(4);
        da1d_o->SetValElm(0, 0.1);
        da1d_o->SetValElm(1, 1.1);
        da1d_o->SetValElm(2, 2.1);
        da1d_o->SetValElm(3, 3.1);
        gd2d->SetOvalArr(da1d_o);

        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);

        gd2d->SetFlagXvalSorted(1);
        gd2d->PrintInfo(stdout);

        delete da1d_x;
        delete da1d_o;        
        delete gd2d;
        printf("=== \n");
    }


//    void SetXvalArr(long ndata, const double* const val);
//    void SetOvalArr(long ndata, const double* const val);
    {
        printf("--- test SetXvalArr(long ndata, const double* const val)\n");
        printf("--- test SetOvalArr(long ndata, const double* const val)\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        double xval[4];
        xval[0] = 0.0;
        xval[1] = 1.0;
        xval[2] = 2.0;
        xval[3] = 3.0;
        gd2d->SetXvalArr(4, xval);
        double oval[4];
        oval[0] = 0.1;
        oval[1] = 1.1;
        oval[2] = 2.1;
        oval[3] = 3.1;        
        gd2d->SetOvalArr(4, oval);
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);
        delete gd2d;
        printf("=== \n");
    }

//    void SetXvalArr(vector<double> val);    
//    void SetOvalArr(vector<double> val);
    {
        printf("--- test SetXvalArr(vector<double> val)\n");
        printf("--- test SetOvalArr(vector<double> val)\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        vector<double> xval(4);
        xval[0] = 0.0;
        xval[1] = 1.0;
        xval[2] = 2.0;
        xval[3] = 3.0;
        gd2d->SetXvalArr(xval);
        vector<double> oval(4);
        oval[0] = 0.1;
        oval[1] = 1.1;
        oval[2] = 2.1;
        oval[3] = 3.1;        
        gd2d->SetOvalArr(oval);
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);
        delete gd2d;
        printf("=== \n");
    }

//    void SetPoint(long idata, double xval, double oval);
    {
        printf("--- test SetPoint(long idata, double xval, double oval)\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1);
        gd2d->SetPoint(1, 1.0, 1.1);
        gd2d->SetPoint(2, 2.0, 2.1);
        gd2d->SetPoint(3, 3.0, 3.1);
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);
        delete gd2d;
        printf("=== \n");
    }

//    void InitSetByFunc(const MirFunc* const func, const double* const par,
//                       long nbin_xval, double xval_lo, double xval_up,
//                       string scale);
    {
        printf("--- test InitSetByFunc\n");

        FuncTest* func = new FuncTest;
        double par[3] = {100.0, 2.0, 3.0};
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");

        long nbin_xval = 100;
        double xval_lo =  1.0;
        double xval_up = 10.0;
        string scale = "log";
        gd2d->InitSetByFunc(func, par, nbin_xval, xval_lo, xval_up, scale);

        gd2d->PrintInfo(stdout);
        // gd2d->PrintData(stdout, "x,y", 0.0, 0.0);
        MirQdpTool::MkQdp(gd2d, "temp.qdp", "x,y");
        delete func;
        delete gd2d;
        printf("=== \n");
    }

   
//    void Copy(const GraphData2d* const org);
    {
        printf("--- test Copy(const GraphData2d* const org)\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1);
        gd2d->SetPoint(1, 1.0, 1.1);
        gd2d->SetPoint(2, 2.0, 2.1);
        gd2d->SetPoint(3, 3.0, 3.1);
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);

        GraphDataNerr2d* gd2d_new = new GraphDataNerr2d("gd2d_new");
        gd2d_new->Copy(gd2d);
        gd2d_new->PrintInfo(stdout);
        gd2d_new->PrintData(stdout, "x,y", 0.0, 0.0);
        
        delete gd2d;
        delete gd2d_new;
        printf("=== \n");
    }

  
//    int GetFlagXvalSorted() const {return flag_xval_sorted_;};
//    long GetNdata() const;
//    double GetXvalElm(long idata) const
//    double GetOvalElm(long idata) const
    {
        printf("--- test GetFlagXvalSorted()\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1);
        gd2d->SetPoint(1, 1.0, 1.1);
        gd2d->SetPoint(2, 2.0, 2.1);
        gd2d->SetPoint(3, 3.0, 3.1);
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);

        printf("gd2d->GetFlagXvalSorted() = %d\n",
               gd2d->GetFlagXvalSorted());
        printf("gd2d->GetNdata() = %ld\n",
               gd2d->GetNdata());
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("gd2d->GetXvalElm(%ld) = %e, gd2d->GetOvalElm(%ld) = %e\n",
                   idata, gd2d->GetXvalElm(idata),
                   idata, gd2d->GetOvalElm(idata));
        }
        
        delete gd2d;

        printf("=== \n");
    }
    
//    double GetXvalAtOvalMin() const;
//    double GetXvalAtOvalMax() const;
//    double GetOvalAtXvalMin() const;
//    double GetOvalAtXvalMax() const;
    {
        printf("--- test GetXvalAtOvalMin()\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1);
        gd2d->SetPoint(1, 1.0, 1.1);
        gd2d->SetPoint(2, 2.0, 2.1);
        gd2d->SetPoint(3, 3.0, 3.1);
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);

        printf("GetXvalAtOvalMin() = %e\n",
               gd2d->GetXvalAtOvalMin());
        printf("GetXvalAtOvalMax() = %e\n",
               gd2d->GetXvalAtOvalMax());
        printf("GetOvalAtXvalMin() = %e\n",
               gd2d->GetOvalAtXvalMin());
        printf("GetOvalAtXvalMax() = %e\n",
               gd2d->GetOvalAtXvalMax());          
        
        delete gd2d;

        printf("=== \n");
    }

//    void Save(string outfile, string format,
//              double offset_xval = 0.0,
//              double offset_oval = 0.0) const;
    {
        printf("--- test Save\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1);
        gd2d->SetPoint(1, 1.0, 1.1);
        gd2d->SetPoint(2, 2.0, 2.1);
        gd2d->SetPoint(3, 3.0, 3.1);

        gd2d->Save("temp.dat", "x,y", -0.1, -0.1);

        delete gd2d;

        printf("=== \n");
    }

    
//    void SaveData(string outfile, string format,
//                  double offset_xval = 0.0,
//                  double offset_oval = 0.0) const;
//    void PrintInfo(FILE* fp) const;    
    {
        printf("--- test SaveData\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1);
        gd2d->SetPoint(1, 1.0, 1.1);
        gd2d->SetPoint(2, 2.0, 2.1);
        gd2d->SetPoint(3, 3.0, 3.1);

        gd2d->SaveData("temp.dat", "x,y", -0.1, -0.1);
        gd2d->PrintInfo(stdout);

        delete gd2d;

        printf("=== \n");
    }

//    double GetOvalIntPolLin(double xval) const;
    {
        printf("--- test GetOvalIntPolLin(double xval)\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.0);
        gd2d->SetPoint(1, 1.0, 10.0);
        gd2d->SetPoint(2, 2.0, 20.0);
        gd2d->SetPoint(3, 3.0, 30.0);
        gd2d->Sort();
        printf("gd2d->GetOvalIntPolLin(0.5) = %e\n",
               gd2d->GetOvalIntPolLin(0.5));
        delete gd2d;

        printf("=== \n");
    }
    
//    double GetOffsetXFromTag(string offset_tag) const;
//    double GetOffsetOFromTag(string offset_tag) const;
    {
        printf("--- test GetOffsetXFromTag(string offset_tag)\n");
        printf("--- test GetOffsetOFromTag(string offset_tag)\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.0);
        gd2d->SetPoint(1, 1.0, 10.0);
        gd2d->SetPoint(2, 2.0, 20.0);
        gd2d->SetPoint(3, 3.0, 30.0);

        {
            double val_st = gd2d->GetOffsetXFromTag("st");
            printf("val_st = %e\n", val_st);

            double val_md = gd2d->GetOffsetXFromTag("md");
            printf("val_md = %e\n", val_md);        

            double val_ed = gd2d->GetOffsetXFromTag("ed");
            printf("val_ed = %e\n", val_ed);

            double val_no = gd2d->GetOffsetXFromTag("no");
            printf("val_no = %e\n", val_no);

            double val_val = gd2d->GetOffsetXFromTag("777.0");
            printf("val_val = %e\n", val_val);                        
        }

        {
            double val_st = gd2d->GetOffsetOFromTag("st");
            printf("val_st = %e\n", val_st);

            double val_md = gd2d->GetOffsetOFromTag("md");
            printf("val_md = %e\n", val_md);        

            double val_ed = gd2d->GetOffsetOFromTag("ed");
            printf("val_ed = %e\n", val_ed);

            double val_no = gd2d->GetOffsetOFromTag("no");
            printf("val_no = %e\n", val_no);

            double val_val = gd2d->GetOffsetOFromTag("777.0");
            printf("val_val = %e\n", val_val);                        
        }
        
        delete gd2d;

        printf("=== \n");
    }
    
//    int IsEqualSpaceX() const;
    {
        printf("--- test IsEqualSpaceX()\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.0);
        gd2d->SetPoint(1, 1.0, 10.0);
        gd2d->SetPoint(2, 2.0, 20.0);
        gd2d->SetPoint(3, 3.0, 30.0);

        printf("IsEqualSpaceX() = %d\n", gd2d->IsEqualSpaceX());

        gd2d->SetPoint(0, 0.0, 0.0);
        gd2d->SetPoint(1, 1.0, 10.0);
        gd2d->SetPoint(2, 2.0, 20.0);
        gd2d->SetPoint(3, 5.0, 30.0);

        printf("IsEqualSpaceX() = %d\n", gd2d->IsEqualSpaceX());        
        
        delete gd2d;

        printf("=== \n");
    }
    
//    static void ReadInfo(string file, int* flag_xval_sorted_ptr);
    {
        printf("--- test ReadInfo(string file, int* flag_xval_sorted_ptr)\n");
        GraphDataNerr2d* gd2d = new GraphDataNerr2d("gd2d");
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.0);
        gd2d->SetPoint(1, 1.0, 10.0);
        gd2d->SetPoint(2, 2.0, 20.0);
        gd2d->SetPoint(3, 3.0, 30.0);
        gd2d->Sort();
        gd2d->Save("temp.dat", "x,y");
        delete gd2d;

        int flag_xval_sorted = 0;
        GraphData2d::ReadInfo("temp.dat", &flag_xval_sorted);
        printf("flag_xval_sorted = %d\n", flag_xval_sorted);

        printf("=== \n");
    }

    
    return status_prog;
}





