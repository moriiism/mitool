#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_graph2d_serr.h"
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
//                  double oval, double oval_serr);
    {
        printf("--- test Init;\n");
        printf("--- test SetPoint\n");
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, 10.0, 0.5);
        gd2d->SetPoint(1, 1.0, 0.2, 10.1, 0.6);
        gd2d->SetPoint(2, 2.0, 0.3, 10.2, 0.7);
        gd2d->SetPoint(3, 3.0, 0.4, 10.3, 0.8);
	gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        gd2d->Save("temp.dat", "x,xe,y,ye");
	delete gd2d;

        printf("=== \n");
    }

//    void SetXvalSerrArr(long ndata, const double* const val_serr);
//    void SetOvalSerrArr(long ndata, const double* const val_serr);
    {
        printf("--- test SetXvalSerrArr\n");
        printf("--- test SetOvalSerrArr\n");        
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
	gd2d->Init(4);
        double xval[4];
        double xval_serr[4];
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

        oval[0] = 10.0;
        oval[1] = 10.1;
        oval[2] = 10.2;
        oval[3] = 10.3;
        oval_serr[0] = 0.5;
        oval_serr[1] = 0.6;
        oval_serr[2] = 0.7;
        oval_serr[3] = 0.8;

        gd2d->SetXvalArr(4, xval);
        gd2d->SetXvalSerrArr(4, xval_serr);
        gd2d->SetOvalArr(4, oval);
        gd2d->SetOvalSerrArr(4, oval_serr);
	gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }
   
//    void SetXvalSerrArr(vector<double> val_serr);    
//    void SetOvalSerrArr(vector<double> val_serr);
    {
        printf("--- test SetXvalSerrArr\n");
        printf("--- test SetOvalSerrArr\n");        
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
	gd2d->Init(4);
        vector<double> xval(4);
        vector<double> xval_serr(4);
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

        oval[0] = 10.0;
        oval[1] = 10.1;
        oval[2] = 10.2;
        oval[3] = 10.3;
        oval_serr[0] = 0.5;
        oval_serr[1] = 0.6;
        oval_serr[2] = 0.7;
        oval_serr[3] = 0.8;

        gd2d->SetXvalArr(xval);
        gd2d->SetXvalSerrArr(xval_serr);
        gd2d->SetOvalArr(oval);
        gd2d->SetOvalSerrArr(oval_serr);
	gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }
    
//    using GraphData2d::SetPoint;
    {
        printf("--- test using GraphData2d::SetPoint\n");
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 10.0);
        gd2d->SetPoint(1, 1.0, 10.1);
        gd2d->SetPoint(2, 2.0, 10.2);
        gd2d->SetPoint(3, 3.0, 10.3);
	gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }
    
//    void SetOvalErrArrByPoissonErr();
    {
        printf("--- test SetOvalErrArrByPoissonErr()\n");
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 2.0);
        gd2d->SetPoint(1, 1.0, 3.0);
        gd2d->SetPoint(2, 2.0, 4.0);
        gd2d->SetPoint(3, 3.0, 5.0);
        gd2d->SetOvalErrArrByPoissonErr();
	gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }

//    GraphDataSerr2d* const Clone() const;
    {
        printf("--- test Clone\n");
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, 10.0, 0.5);
        gd2d->SetPoint(1, 1.0, 0.2, 10.1, 0.6);
        gd2d->SetPoint(2, 2.0, 0.3, 10.2, 0.7);
        gd2d->SetPoint(3, 3.0, 0.4, 10.3, 0.8);
        gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        printf("--- \n");
        GraphDataSerr2d* gd2d_new = gd2d->Clone();
	gd2d_new->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
	delete gd2d;
	delete gd2d_new;

        printf("=== \n");
    }

//    void Load(string file);
    {
        printf("--- test Load(string file)\n");
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
        gd2d->Load("data/test_graph2d_serr.dat");
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        gd2d->Load("data/test_graph2d_nerr.dat");
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        
	delete gd2d;

        printf("=== \n");
    }
    
//    void Load(string file, string format);
    {
        printf("--- test Load(string file, string format)\n");
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
        gd2d->Load("data/test_graph2d_serr.dat", "x,xe,y,ye");
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        gd2d->Load("data/test_graph2d_nerr.dat", "x,y");
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

	delete gd2d;

        printf("=== \n");
    }
    
//    void Sort();
    {
        printf("--- test Sort\n");
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, 10.0, 0.5);
        gd2d->SetPoint(1, 3.0, 0.2, 10.1, 0.6);
        gd2d->SetPoint(2, 2.0, 0.3, 10.2, 0.7);
        gd2d->SetPoint(3, 1.0, 0.4, 10.3, 0.8);
        gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        
        gd2d->Sort();
        gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

	delete gd2d;

        printf("=== \n");
    }

//    const DataArraySerr1d* const GetXvalArr() const;
//    const DataArraySerr1d* const GetOvalArr() const;
    {
        printf("--- test GetXvalArr()\n");
        printf("--- test GetOvalArr()\n");        
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, 10.0, 0.5);
        gd2d->SetPoint(1, 1.0, 0.2, 10.1, 0.6);
        gd2d->SetPoint(2, 2.0, 0.3, 10.2, 0.7);
        gd2d->SetPoint(3, 3.0, 0.4, 10.3, 0.8);
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd2d->GetXvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValSerrElm(%ld) = %e\n",
                   idata, gd2d->GetXvalArr()->GetValSerrElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd2d->GetOvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValSerrElm(%ld) = %e\n",
                   idata, gd2d->GetOvalArr()->GetValSerrElm(idata));
        }

	delete gd2d;

        printf("=== \n");
    }
//    double GetXvalSerrElm(long idata) const;
//    double GetOvalSerrElm(long idata) const;
    {
        printf("--- test GetXvalSerrElm(long idata)\n");
        printf("--- test GetOvalSerrElm(long idata)\n");        
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, 10.0, 0.5);
        gd2d->SetPoint(1, 1.0, 0.2, 10.1, 0.6);
        gd2d->SetPoint(2, 2.0, 0.3, 10.2, 0.7);
        gd2d->SetPoint(3, 3.0, 0.4, 10.3, 0.8);
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalElm(%ld) = %e\n",
                   idata, gd2d->GetXvalElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalSerrElm(%ld) = %e\n",
                   idata, gd2d->GetXvalSerrElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalElm(%ld) = %e\n",
                   idata, gd2d->GetOvalElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalSerrElm(%ld) = %e\n",
                   idata, gd2d->GetOvalSerrElm(idata));
        }

	delete gd2d;

        printf("=== \n");
    }

//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_oval) const;
    {
        printf("--- test PrintData\n");
	GraphDataSerr2d* gd2d = new GraphDataSerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, 10.0, 0.5);
        gd2d->SetPoint(1, 1.0, 0.2, 10.1, 0.6);
        gd2d->SetPoint(2, 2.0, 0.3, 10.2, 0.7);
        gd2d->SetPoint(3, 3.0, 0.4, 10.3, 0.8);

        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);

        printf("--- \n");
        gd2d->PrintData(stdout, "x,xe,y", 0.0, 0.0);

        printf("--- \n");
        gd2d->PrintData(stdout, "x,y,ye", 0.0, 0.0);

        printf("--- \n");
        gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        printf("--- \n");
        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
        
	delete gd2d;

        printf("=== \n");
    }
    
//    TGraphErrors* const GenTGraph(double offset_xval,
//                                  double offset_oval) const;
    {
        printf("--- test GenTGraph\n");
        GraphDataSerr2d* gd2d = new GraphDataSerr2d;
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, 10.0, 0.5);
        gd2d->SetPoint(1, 1.0, 0.2, 10.1, 0.6);
        gd2d->SetPoint(2, 2.0, 0.3, 10.2, 0.7);
        gd2d->SetPoint(3, 3.0, 0.4, 10.3, 0.8);

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("def");
        
        TGraph* tg = gd2d->GenTGraph(0.0, 0.0);
        tg->Draw();
        root_tool->GetTCanvas()->Print("aaaaa.png");

        delete gd2d;
        delete tg;
        delete root_tool;

        printf("=== \n");
    }
 
//    Interval* const GenInterval() const;
    {
        printf("--- test GenInterval()\n");
        GraphDataSerr2d* gd2d = new GraphDataSerr2d;
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, 10.0, 0.5);
        gd2d->SetPoint(1, 1.0, 0.2, 10.1, 0.6);
        gd2d->SetPoint(2, 2.0, 0.3, 10.2, 0.7);
        gd2d->SetPoint(3, 3.0, 0.4, 10.3, 0.8);

        Interval* interval = gd2d->GenInterval();
        MirQdpTool::MkQdp(interval, "temp.qdp");

        delete gd2d;


        printf("=== \n");
    }
   
//    Interval* const GenIntervalAboveThreshold(double threshold) const;
    {
        printf("--- test GenIntervalAboveThreshold(double threshold)\n");
        GraphDataSerr2d* gd2d = new GraphDataSerr2d;
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, 10.0, 0.5);
        gd2d->SetPoint(1, 1.0, 0.2, 10.1, 0.6);
        gd2d->SetPoint(2, 2.0, 0.3, 10.2, 0.7);
        gd2d->SetPoint(3, 3.0, 0.4, 10.3, 0.8);

        Interval* interval = gd2d->GenIntervalAboveThreshold(10.15);
        MirQdpTool::MkQdp(interval, "temp.qdp");

        delete gd2d;

        printf("=== \n");
    }
 
//    Interval* const GenIntervalBelowThreshold(double threshold) const;
    {
        printf("--- test GenIntervalBelowThreshold(double threshold)\n");
        GraphDataSerr2d* gd2d = new GraphDataSerr2d;
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, 10.0, 0.5);
        gd2d->SetPoint(1, 1.0, 0.2, 10.1, 0.6);
        gd2d->SetPoint(2, 2.0, 0.3, 10.2, 0.7);
        gd2d->SetPoint(3, 3.0, 0.4, 10.3, 0.8);

        Interval* interval = gd2d->GenIntervalBelowThreshold(10.15);
        MirQdpTool::MkQdp(interval, "temp.qdp");

        delete gd2d;

        printf("=== \n");
    }

    

    return status_prog;
}
