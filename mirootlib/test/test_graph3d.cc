#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_graph3d_nerr.h"
#include "mir_graph3d_serr.h"
#include "mir_graph3d_terr.h"
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
            SetNdim(2);           
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
    double argy = xval[1];
    double ans = par[0] + par[1] * pow(argx, 2) + par[2] * pow(argy, 2.);
    return ans;
}

    
int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    virtual void Init(long ndata) = 0;
    {
        printf("--- test Init(long ndata)\n");
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);
        gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        delete gd3d;
        printf("=== \n");
    }

//    void SetXvalArr(const DataArray1d* const val_arr);
//    void SetYvalArr(const DataArray1d* const val_arr);    
//    void SetOvalArr(const DataArray1d* const val_arr);
    {
        printf("--- test SetXvalArr(const DataArray1d* const val_arr)\n");
        printf("--- test SetYvalArr(const DataArray1d* const val_arr)\n");        
        printf("--- test SetOvalArr(const DataArray1d* const val_arr)\n");

        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);
        DataArrayNerr1d* da1d_x = new DataArrayNerr1d;
        da1d_x->Init(4);
        da1d_x->SetValElm(0, 0.0);
        da1d_x->SetValElm(1, 1.0);
        da1d_x->SetValElm(2, 2.0);
        da1d_x->SetValElm(3, 3.0);
        gd3d->SetXvalArr(da1d_x);

        DataArrayNerr1d* da1d_y = new DataArrayNerr1d;
        da1d_y->Init(4);
        da1d_y->SetValElm(0, 0.5);
        da1d_y->SetValElm(1, 1.5);
        da1d_y->SetValElm(2, 2.5);
        da1d_y->SetValElm(3, 3.5);
        gd3d->SetYvalArr(da1d_y);
        
        DataArrayNerr1d* da1d_o = new DataArrayNerr1d;
        da1d_o->Init(4);
        da1d_o->SetValElm(0, 0.1);
        da1d_o->SetValElm(1, 1.1);
        da1d_o->SetValElm(2, 2.1);
        da1d_o->SetValElm(3, 3.1);
        gd3d->SetOvalArr(da1d_o);

        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        delete da1d_x;
        delete da1d_y;
        delete da1d_o;        
        delete gd3d;
        printf("=== \n");
    }

//    void SetXvalArr(long ndata, const double* const val);
//    void SetYvalArr(long ndata, const double* const val);
//    void SetOvalArr(long ndata, const double* const val);    
    {
        printf("--- test SetXvalArr(long ndata, const double* const val)\n");
        printf("--- test SetYvalArr(long ndata, const double* const val)\n");        
        printf("--- test SetOvalArr(long ndata, const double* const val)\n");
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);

        double xval[4];
        xval[0] = 0.0;
        xval[1] = 1.0;
        xval[2] = 2.0;
        xval[3] = 3.0;
        gd3d->SetXvalArr(4, xval);

        double yval[4];
        yval[0] = 0.5;
        yval[1] = 1.5;
        yval[2] = 2.5;
        yval[3] = 3.5;
        gd3d->SetYvalArr(4, yval);

        double oval[4];
        oval[0] = 0.1;
        oval[1] = 1.1;
        oval[2] = 2.1;
        oval[3] = 3.1;        
        gd3d->SetOvalArr(4, oval);
        
        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        delete gd3d;
        printf("=== \n");
    }

   
//    void SetXvalArr(vector<double> val);
//    void SetYvalArr(vector<double> val);
//    void SetOvalArr(vector<double> val);
    {
        printf("--- test SetXvalArr(vector<double> val)\n");
        printf("--- test SetYvalArr(vector<double> val)\n");        
        printf("--- test SetOvalArr(vector<double> val)\n");
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);
        
        vector<double> xval(4);
        xval[0] = 0.0;
        xval[1] = 1.0;
        xval[2] = 2.0;
        xval[3] = 3.0;
        gd3d->SetXvalArr(xval);

        vector<double> yval(4);
        yval[0] = 0.5;
        yval[1] = 1.5;
        yval[2] = 2.5;
        yval[3] = 3.5;
        gd3d->SetYvalArr(yval);
        
        vector<double> oval(4);
        oval[0] = 0.1;
        oval[1] = 1.1;
        oval[2] = 2.1;
        oval[3] = 3.1;        
        gd3d->SetOvalArr(oval);
        
        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        delete gd3d;
        
        printf("=== \n");
    }

//    void SetPoint(long idata, double xval, double yval, double oval);    
    {
        printf("--- test SetPoint\n");
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.5, 1.1);
        gd3d->SetPoint(2, 2.0, 1.5, 2.1);
        gd3d->SetPoint(3, 3.0, 1.5, 3.1);
        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        delete gd3d;
        printf("=== \n");
    }


//    void InitSetByFunc(const MirFunc* const func, const double* const par,
//                       long nbin_xval, double xval_lo, double xval_up,
//                       long nbin_yval, double yval_lo, double yval_up,
//                       string scale_xval, string scale_yval);
    {
        printf("--- test InitSetByFunc\n");

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        FuncTest* func = new FuncTest;
        double par[3] = {100.0, 2.0, 3.0};
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");

        long nbin_xval = 100;
        double xval_lo =  1.0;
        double xval_up = 10.0;
        long nbin_yval = 100;
        double yval_lo =  1.0;
        double yval_up = 10.0;        
        string scale_xval = "log";
        string scale_yval = "log";

        gd3d->InitSetByFunc(func, par,
                            nbin_xval, xval_lo, xval_up,
                            nbin_yval, yval_lo, yval_up,
                            scale_xval, scale_yval);
        gd3d->PrintInfo(stdout);
        TGraph2D* tg2d = gd3d->GenTGraph2D(0.0, 0.0, 0.0);

        tg2d->Draw("line");
        root_tool->GetTCanvas()->Print("temp.png");

        delete func;
        delete gd3d;
        delete root_tool;
        delete tg2d;
        printf("=== \n");
    }

//    void Copy(const GraphData3d* const org);          
    {
        printf("--- test Copy(const GraphData3d* const org)\n");
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.5, 1.1);
        gd3d->SetPoint(2, 2.0, 1.5, 2.1);
        gd3d->SetPoint(3, 3.0, 1.5, 3.1);
        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);        

        GraphDataNerr3d* gd3d_new = new GraphDataNerr3d("gd3d_new");
        gd3d_new->Copy(gd3d);
        gd3d_new->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);                
        
        delete gd3d;
        delete gd3d_new;
        printf("=== \n");
    }

//    long GetNdata() const;
//    double GetXvalElm(long idata) const
//    double GetYvalElm(long idata) const    
//    double GetOvalElm(long idata) const
    {
        printf("--- test GetNdata()\n");        
        printf("--- test GetXvalElm(long idata)\n");
        printf("--- test GetYvalElm(long idata)\n");
        printf("--- test GetOvalElm(long idata)\n");
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.5, 1.1);
        gd3d->SetPoint(2, 2.0, 2.5, 2.1);
        gd3d->SetPoint(3, 3.0, 3.5, 3.1);
        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);        
        printf("gd3d->GetNdata() = %ld\n",
               gd3d->GetNdata());
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("gd3d->GetXvalElm(%ld) = %e "
                   "gd3d->GetYvalElm(%ld) = %e "
                   "gd3d->GetOvalElm(%ld) = %e\n",
                   idata, gd3d->GetXvalElm(idata),
                   idata, gd3d->GetYvalElm(idata),
                   idata, gd3d->GetOvalElm(idata));
        }
        
        delete gd3d;

        printf("=== \n");
    }
   
//    double GetYvalAtXvalMin() const;
//    double GetYvalAtXvalMax() const;
//    double GetOvalAtXvalMin() const;
//    double GetOvalAtXvalMax() const;
//    
//    double GetXvalAtYvalMin() const;
//    double GetXvalAtYvalMax() const;
//    double GetOvalAtYvalMin() const;
//    double GetOvalAtYvalMax() const;
//
//    double GetXvalAtOvalMin() const;
//    double GetXvalAtOvalMax() const;
//    double GetYvalAtOvalMin() const;
//    double GetYvalAtOvalMax() const;
    {
        printf("--- test GetYvalAtXvalMin()\n");
        printf("--- test GetYvalAtXvalMax()\n");
        printf("--- test GetOvalAtXvalMin()\n");
        printf("--- test GetOvalAtXvalMax()\n");
                                           
        printf("--- test GetXvalAtYvalMin()\n");
        printf("--- test GetXvalAtYvalMax()\n");
        printf("--- test GetOvalAtYvalMin()\n");
        printf("--- test GetOvalAtYvalMax()\n");
                                           
        printf("--- test GetXvalAtOvalMin()\n");
        printf("--- test GetXvalAtOvalMax()\n");
        printf("--- test GetYvalAtOvalMin()\n");
        printf("--- test GetYvalAtOvalMax()\n");
        
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.5, 1.1);
        gd3d->SetPoint(2, 2.0, 2.5, 2.1);
        gd3d->SetPoint(3, 3.0, 3.5, 3.1);        
        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);                

        printf("GetYvalAtXvalMin() = %e\n", gd3d->GetYvalAtXvalMin());
        printf("GetYvalAtXvalMax() = %e\n", gd3d->GetYvalAtXvalMax());
        printf("GetOvalAtXvalMin() = %e\n", gd3d->GetOvalAtXvalMin());
        printf("GetOvalAtXvalMax() = %e\n", gd3d->GetOvalAtXvalMax());
                                                                    
        printf("GetXvalAtYvalMin() = %e\n", gd3d->GetXvalAtYvalMin());
        printf("GetXvalAtYvalMax() = %e\n", gd3d->GetXvalAtYvalMax());
        printf("GetOvalAtYvalMin() = %e\n", gd3d->GetOvalAtYvalMin());
        printf("GetOvalAtYvalMax() = %e\n", gd3d->GetOvalAtYvalMax());
                                                                    
        printf("GetXvalAtOvalMin() = %e\n", gd3d->GetXvalAtOvalMin());
        printf("GetXvalAtOvalMax() = %e\n", gd3d->GetXvalAtOvalMax());
        printf("GetYvalAtOvalMin() = %e\n", gd3d->GetYvalAtOvalMin());
        printf("GetYvalAtOvalMax() = %e\n", gd3d->GetYvalAtOvalMax());
        
        delete gd3d;

        printf("=== \n");
    }

//    void Save(string outfile, string format,
//              double offset_xval = 0.0,
//              double offset_yval = 0.0,
//              double offset_oval = 0.0) const;
    {
        printf("--- test Save\n");
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.5, 1.1);
        gd3d->SetPoint(2, 2.0, 2.5, 2.1);
        gd3d->SetPoint(3, 3.0, 3.5, 3.1);        
        gd3d->Save("temp.dat", "x,y,z", 0.0, 0.0, 0.0);

        delete gd3d;

        printf("=== \n");
    }

//   void SaveData(string outfile, string format,
//                  double offset_xval = 0.0,
//                  double offset_yval = 0.0,
//                  double offset_oval = 0.0) const;
//    void PrintInfo(FILE* fp) const;    
    {
        printf("--- test SaveData\n");
        printf("--- test PrintInfo\n");
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.5, 1.1);
        gd3d->SetPoint(2, 2.0, 2.5, 2.1);
        gd3d->SetPoint(3, 3.0, 3.5, 3.1);
        gd3d->PrintInfo(stdout);        
        gd3d->SaveData("temp.dat", "x,y,z", 0.0, 0.0, 0.0);

        delete gd3d;

        printf("=== \n");
    }

//    double GetOffsetXFromTag(string offset_tag) const;
//    double GetOffsetYFromTag(string offset_tag) const;
//    double GetOffsetOFromTag(string offset_tag) const;
    {
        printf("--- test GetOffsetXFromTag(string offset_tag)\n");
        printf("--- test GetOffsetYFromTag(string offset_tag)\n");        
        printf("--- test GetOffsetOFromTag(string offset_tag)\n");
        GraphDataNerr3d* gd3d = new GraphDataNerr3d("gd3d");
        gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.5, 1.1);
        gd3d->SetPoint(2, 2.0, 2.5, 2.1);
        gd3d->SetPoint(3, 3.0, 3.5, 3.1);        
        {
            double val_st = gd3d->GetOffsetXFromTag("st");
            printf("val_st = %e\n", val_st);

            double val_md = gd3d->GetOffsetXFromTag("md");
            printf("val_md = %e\n", val_md);        

            double val_ed = gd3d->GetOffsetXFromTag("ed");
            printf("val_ed = %e\n", val_ed);

            double val_no = gd3d->GetOffsetXFromTag("no");
            printf("val_no = %e\n", val_no);

            double val_val = gd3d->GetOffsetXFromTag("777.0");
            printf("val_val = %e\n", val_val);                        
        }

        {
            double val_st = gd3d->GetOffsetYFromTag("st");
            printf("val_st = %e\n", val_st);

            double val_md = gd3d->GetOffsetYFromTag("md");
            printf("val_md = %e\n", val_md);        

            double val_ed = gd3d->GetOffsetYFromTag("ed");
            printf("val_ed = %e\n", val_ed);

            double val_no = gd3d->GetOffsetYFromTag("no");
            printf("val_no = %e\n", val_no);

            double val_val = gd3d->GetOffsetYFromTag("777.0");
            printf("val_val = %e\n", val_val);                        
        }
        
        {
            double val_st = gd3d->GetOffsetOFromTag("st");
            printf("val_st = %e\n", val_st);

            double val_md = gd3d->GetOffsetOFromTag("md");
            printf("val_md = %e\n", val_md);        

            double val_ed = gd3d->GetOffsetOFromTag("ed");
            printf("val_ed = %e\n", val_ed);

            double val_no = gd3d->GetOffsetOFromTag("no");
            printf("val_no = %e\n", val_no);

            double val_val = gd3d->GetOffsetOFromTag("777.0");
            printf("val_val = %e\n", val_val);                        
        }
        
        delete gd3d;

        printf("=== \n");
    }

  
    
    return status_prog;
}



 
