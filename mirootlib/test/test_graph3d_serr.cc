#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_graph3d_serr.h"
#include "mir_root_tool.h"
#include "mir_qdp_tool.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Init(long ndata);
//    void SetPoint(long idata,
//                  double xval, double xval_serr,
//                  double yval, double yval_serr,
//                  double oval, double oval_serr);
    {
        printf("--- test Init;\n");
        printf("--- test SetPoint\n");
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, 10.0, 0.5, 100.0, 1.5);
        gd3d->SetPoint(1, 1.0, 0.2, 10.1, 0.6, 110.1, 1.6);
        gd3d->SetPoint(2, 2.0, 0.3, 10.2, 0.7, 120.2, 1.7);
        gd3d->SetPoint(3, 3.0, 0.4, 10.3, 0.8, 130.3, 1.8);
	gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        gd3d->Save("temp.dat", "x,xe,y,ye,z,ze");
	delete gd3d;

        printf("=== \n");
    }

    
//    void SetXvalSerrArr(long ndata, const double* const val_serr);
//    void SetYvalSerrArr(long ndata, const double* const val_serr);    
//    void SetOvalSerrArr(long ndata, const double* const val_serr);
    {
        printf("--- test SetXvalSerrArr\n");
        printf("--- test SetYvalSerrArr\n");
        printf("--- test SetOvalSerrArr\n");        
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
	gd3d->Init(4);
        double xval[4];
        double xval_serr[4];
        double yval[4];
        double yval_serr[4];        
        double oval[4];
        double oval_serr[4];
        xval[0] = 0.0;
        xval[1] = 1.0;
        xval[2] = 2.0;
        xval[3] = 3.0;
        xval_serr[0] = 0.1;
        xval_serr[1] = 0.2;
        xval_serr[2] = 0.3;
        xval_serr[3] = 0.4;

        yval[0] = 0.0;
        yval[1] = 1.0;
        yval[2] = 2.0;
        yval[3] = 3.0;
        yval_serr[0] = 0.1;
        yval_serr[1] = 0.2;
        yval_serr[2] = 0.3;
        yval_serr[3] = 0.4;
        
        oval[0] = 10.0;
        oval[1] = 10.1;
        oval[2] = 10.2;
        oval[3] = 10.3;
        oval_serr[0] = 0.5;
        oval_serr[1] = 0.6;
        oval_serr[2] = 0.7;
        oval_serr[3] = 0.8;

        gd3d->SetXvalArr(4, xval);
        gd3d->SetXvalSerrArr(4, xval_serr);
        gd3d->SetYvalArr(4, yval);
        gd3d->SetYvalSerrArr(4, yval_serr);        
        gd3d->SetOvalArr(4, oval);
        gd3d->SetOvalSerrArr(4, oval_serr);
	gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

//    void SetXvalSerrArr(vector<double> val_serr);
//    void SetYvalSerrArr(vector<double> val_serr);    
//    void SetOvalSerrArr(vector<double> val_serr);
    {
        printf("--- test SetXvalSerrArr\n");
        printf("--- test SetYvalSerrArr\n");        
        printf("--- test SetOvalSerrArr\n");        
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
	gd3d->Init(4);
        vector<double> xval(4);
        vector<double> xval_serr(4);
        vector<double> yval(4);
        vector<double> yval_serr(4);
        vector<double> oval(4);
        vector<double> oval_serr(4);
        xval[0] = 0.0;
        xval[1] = 1.0;
        xval[2] = 2.0;
        xval[3] = 3.0;
        xval_serr[0] = 0.1;
        xval_serr[1] = 0.2;
        xval_serr[2] = 0.3;
        xval_serr[3] = 0.4;

        yval[0] = 0.5;
        yval[1] = 1.5;
        yval[2] = 2.5;
        yval[3] = 3.5;
        yval_serr[0] = 0.16;
        yval_serr[1] = 0.26;
        yval_serr[2] = 0.36;
        yval_serr[3] = 0.46;
        
        oval[0] = 10.0;
        oval[1] = 10.1;
        oval[2] = 10.2;
        oval[3] = 10.3;
        oval_serr[0] = 0.5;
        oval_serr[1] = 0.6;
        oval_serr[2] = 0.7;
        oval_serr[3] = 0.8;

        gd3d->SetXvalArr(xval);
        gd3d->SetXvalSerrArr(xval_serr);
        gd3d->SetYvalArr(yval);
        gd3d->SetYvalSerrArr(yval_serr);        
        gd3d->SetOvalArr(oval);
        gd3d->SetOvalSerrArr(oval_serr);
	gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

   
//    using GraphData3d::SetPoint;
    {
        printf("--- test using GraphData3d::SetPoint\n");
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 10.0, 100.0);
        gd3d->SetPoint(1, 1.0, 10.1, 110.1);
        gd3d->SetPoint(2, 2.0, 10.2, 120.2);
        gd3d->SetPoint(3, 3.0, 10.3, 130.3);
	gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }
   
//    void SetOvalErrArrByPoissonErr();
    {
        printf("--- test SetOvalErrArrByPoissonErr()\n");
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 2.0, 1.0);
        gd3d->SetPoint(1, 1.0, 3.0, 2.0);
        gd3d->SetPoint(2, 2.0, 4.0, 3.0);
        gd3d->SetPoint(3, 3.0, 5.0, 4.0);
        gd3d->SetOvalErrArrByPoissonErr();
	gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

//    GraphDataSerr3d* const Clone() const;
    {
        printf("--- test Clone\n");
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, 10.0, 0.5, 100.0, 1.5);
        gd3d->SetPoint(1, 1.0, 0.2, 10.1, 0.6, 110.1, 1.6);
        gd3d->SetPoint(2, 2.0, 0.3, 10.2, 0.7, 120.2, 1.7);
        gd3d->SetPoint(3, 3.0, 0.4, 10.3, 0.8, 130.3, 1.8);        
        gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);

        printf("--- \n");
        GraphDataSerr3d* gd3d_new = gd3d->Clone();
	gd3d_new->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
	delete gd3d;
	delete gd3d_new;

        printf("=== \n");
    }

   
//    void Load(string file);
    {
        printf("--- test Load(string file)\n");
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
        gd3d->Load("data/test_graph3d_serr.dat");
        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);

//        gd3d->Load("data/test_graph3d_nerr.dat");
//        gd3d->PrintInfo(stdout);
//        gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
	delete gd3d;

        printf("=== \n");
    }

   
//    void Load(string file, string format);
    {
        printf("--- test Load(string file, string format)\n");
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
        gd3d->Load("data/test_graph3d_serr.dat", "x,xe,y,ye,z,ze");
        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);

//        gd3d->Load("data/test_graph3d_nerr.dat", "x,y,z");
//        gd3d->PrintInfo(stdout);
//        gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);

	delete gd3d;

        printf("=== \n");
    }

//    const DataArraySerr1d* const GetXvalArr() const;
//    const DataArraySerr1d* const GetYvalArr() const;
//    const DataArraySerr1d* const GetOvalArr() const;
    {
        printf("--- test GetXvalArr()\n");
        printf("--- test GetYvalArr()\n");        
        printf("--- test GetOvalArr()\n");        
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, 10.0, 0.5, 100.0, 1.5);
        gd3d->SetPoint(1, 1.0, 0.2, 10.1, 0.6, 110.1, 1.6);
        gd3d->SetPoint(2, 2.0, 0.3, 10.2, 0.7, 120.2, 1.7);
        gd3d->SetPoint(3, 3.0, 0.4, 10.3, 0.8, 130.3, 1.8);        
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd3d->GetXvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValSerrElm(%ld) = %e\n",
                   idata, gd3d->GetXvalArr()->GetValSerrElm(idata));
        }

        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd3d->GetYvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalArr()->GetValSerrElm(%ld) = %e\n",
                   idata, gd3d->GetYvalArr()->GetValSerrElm(idata));
        }
        
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd3d->GetOvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValSerrElm(%ld) = %e\n",
                   idata, gd3d->GetOvalArr()->GetValSerrElm(idata));
        }

	delete gd3d;

        printf("=== \n");
    }

   
//    double GetXvalSerrElm(long idata) const;
//    double GetYvalSerrElm(long idata) const;    
//    double GetOvalSerrElm(long idata) const;
    {
        printf("--- test GetXvalSerrElm(long idata)\n");
        printf("--- test GetYvalSerrElm(long idata)\n");        
        printf("--- test GetOvalSerrElm(long idata)\n");        
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, 10.0, 0.5, 100.0, 1.5);
        gd3d->SetPoint(1, 1.0, 0.2, 10.1, 0.6, 110.1, 1.6);
        gd3d->SetPoint(2, 2.0, 0.3, 10.2, 0.7, 120.2, 1.7);
        gd3d->SetPoint(3, 3.0, 0.4, 10.3, 0.8, 130.3, 1.8);        
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalElm(%ld) = %e\n",
                   idata, gd3d->GetXvalElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalSerrElm(%ld) = %e\n",
                   idata, gd3d->GetXvalSerrElm(idata));
        }

        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalElm(%ld) = %e\n",
                   idata, gd3d->GetYvalElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalSerrElm(%ld) = %e\n",
                   idata, gd3d->GetYvalSerrElm(idata));
        }
        
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalElm(%ld) = %e\n",
                   idata, gd3d->GetOvalElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalSerrElm(%ld) = %e\n",
                   idata, gd3d->GetOvalSerrElm(idata));
        }

	delete gd3d;

        printf("=== \n");
    }


//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_yval,
//                   double offset_oval) const;
    {
        printf("--- test PrintData\n");
	GraphDataSerr3d* gd3d = new GraphDataSerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, 10.0, 0.5, 100.0, 1.5);
        gd3d->SetPoint(1, 1.0, 0.2, 10.1, 0.6, 110.1, 1.6);
        gd3d->SetPoint(2, 2.0, 0.3, 10.2, 0.7, 120.2, 1.7);
        gd3d->SetPoint(3, 3.0, 0.4, 10.3, 0.8, 130.3, 1.8);        

        printf("--- \n");
        gd3d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        
	delete gd3d;

        printf("=== \n");
    }


//    TGraph2DErrors* const GenTGraph2D(double offset_xval,
//                                      double offset_yval,
//                                      double offset_oval) const;
    {
        printf("--- test GenTGraph2D\n");
        GraphDataSerr3d* gd3d = new GraphDataSerr3d;
        gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, 10.0, 0.5, 100.0, 1.5);
        gd3d->SetPoint(1, 1.0, 0.2, 10.1, 0.6, 110.1, 1.6);
        gd3d->SetPoint(2, 2.0, 0.3, 10.2, 0.7, 120.2, 1.7);
        gd3d->SetPoint(3, 3.0, 0.4, 10.3, 0.8, 130.3, 1.8);        

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        
        TGraph2DErrors* tg2d = gd3d->GenTGraph2D(0.0, 0.0, 0.0);
        tg2d->Draw("");
        root_tool->GetTCanvas()->Print("aaa.png");

        delete gd3d;
        delete tg2d;
        delete root_tool;

        printf("=== \n");
    }


    return status_prog;
}

