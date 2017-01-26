#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_graph2d_terr.h"
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
//                  double xval,
//                  double xval_terr_plus,
//                  double xval_terr_minus,
//                  double oval,
//                  double oval_terr_plus,
//                  double oval_terr_minus);
    {
        printf("--- test Init;\n");
        printf("--- test SetPoint\n");
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, -0.2, 10.0, 0.5, -1.5);
        gd2d->SetPoint(1, 1.0, 0.2, -0.4, 10.1, 0.6, -1.6);
        gd2d->SetPoint(2, 2.0, 0.3, -0.6, 10.2, 0.7, -1.7);
        gd2d->SetPoint(3, 3.0, 0.4, -0.8, 10.3, 0.8, -1.8);
	gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
        gd2d->Save("temp.dat", "x,xe+,xe-,y,ye+,ye-");
	delete gd2d;

        printf("=== \n");
    }

//    void SetXvalTerrArr(long ndata, const double* const val_serr);
//    void SetOvalTerrArr(long ndata, const double* const val_serr);    
    {
        printf("--- test SetXvalTerrArr\n");
        printf("--- test SetOvalTerrArr\n");        
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
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
        gd2d->SetXvalTerrArr(4, xval_serr);
        gd2d->SetOvalArr(4, oval);
        gd2d->SetOvalTerrArr(4, oval_serr);
	gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }

//    void SetXvalTerrArr(vector<double> val_serr);
//    void SetOvalTerrArr(vector<double> val_serr);
    {
        printf("--- test SetXvalTerrArr\n");
        printf("--- test SetOvalTerrArr\n");        
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
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
        gd2d->SetXvalTerrArr(xval_serr);
        gd2d->SetOvalArr(oval);
        gd2d->SetOvalTerrArr(oval_serr);
	gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }

//    void SetXvalTerrArr(long ndata,
//                        const double* const val_terr_plus,
//                        const double* const val_terr_minus);
//    void SetOvalTerrArr(long ndata,
//                        const double* const val_terr_plus,
//                        const double* const val_terr_minus);
    {
        printf("--- test SetXvalTerrArr\n");
        printf("--- test SetOvalTerrArr\n");        
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
	gd2d->Init(4);
        double xval[4];
        double xval_terr_plus[4];
        double xval_terr_minus[4];
        double oval[4];
        double oval_terr_plus[4];
        double oval_terr_minus[4];
        xval[0] = 0.0;
        xval[1] = 1.0;
        xval[2] = 2.0;
        xval[3] = 3.0;
        xval_terr_plus[0] = 0.1;
        xval_terr_plus[1] = 0.2;
        xval_terr_plus[2] = 0.3;
        xval_terr_plus[3] = 0.4;
        xval_terr_minus[0] = -0.11;
        xval_terr_minus[1] = -0.21;
        xval_terr_minus[2] = -0.31;
        xval_terr_minus[3] = -0.41;

        oval[0] = 10.0;
        oval[1] = 10.1;
        oval[2] = 10.2;
        oval[3] = 10.3;
        oval_terr_plus[0] = 0.5;
        oval_terr_plus[1] = 0.6;
        oval_terr_plus[2] = 0.7;
        oval_terr_plus[3] = 0.8;
        oval_terr_minus[0] = -1.5;
        oval_terr_minus[1] = -1.6;
        oval_terr_minus[2] = -1.7;
        oval_terr_minus[3] = -1.8;
        
        gd2d->SetXvalArr(4, xval);
        gd2d->SetXvalTerrArr(4, xval_terr_plus, xval_terr_minus);
        gd2d->SetOvalArr(4, oval);
        gd2d->SetOvalTerrArr(4, oval_terr_plus, oval_terr_minus);
	gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }

//    void SetXvalTerrArr(vector<double> val_terr_plus,
//                        vector<double> val_terr_minus);
//    void SetOvalTerrArr(vector<double> val_terr_plus,
//                        vector<double> val_terr_minus);
    {
        printf("--- test SetXvalTerrArr\n");
        printf("--- test SetOvalTerrArr\n");        
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
	gd2d->Init(4);
        vector<double> xval(4);
        vector<double> xval_terr_plus(4);
        vector<double> xval_terr_minus(4);
        vector<double> oval(4);
        vector<double> oval_terr_plus(4);
        vector<double> oval_terr_minus(4);
        xval[0] = 0.0;
        xval[1] = 1.0;
        xval[2] = 2.0;
        xval[3] = 3.0;
        xval_terr_plus[0] = 0.1;
        xval_terr_plus[1] = 0.2;
        xval_terr_plus[2] = 0.3;
        xval_terr_plus[3] = 0.4;
        xval_terr_minus[0] = -0.11;
        xval_terr_minus[1] = -0.21;
        xval_terr_minus[2] = -0.31;
        xval_terr_minus[3] = -0.41;

        oval[0] = 10.0;
        oval[1] = 10.1;
        oval[2] = 10.2;
        oval[3] = 10.3;
        oval_terr_plus[0] = 0.5;
        oval_terr_plus[1] = 0.6;
        oval_terr_plus[2] = 0.7;
        oval_terr_plus[3] = 0.8;
        oval_terr_minus[0] = -1.5;
        oval_terr_minus[1] = -1.6;
        oval_terr_minus[2] = -1.7;
        oval_terr_minus[3] = -1.8;
        
        gd2d->SetXvalArr(xval);
        gd2d->SetXvalTerrArr(xval_terr_plus, xval_terr_minus);
        gd2d->SetOvalArr(oval);
        gd2d->SetOvalTerrArr(oval_terr_plus, oval_terr_minus);
	gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }


//    using GraphData2d::SetPoint;
    {
        printf("--- test using GraphData2d::SetPoint\n");
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 10.0);
        gd2d->SetPoint(1, 1.0, 10.1);
        gd2d->SetPoint(2, 2.0, 10.2);
        gd2d->SetPoint(3, 3.0, 10.3);
	gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }

//    void SetOvalErrArrByPoissonErr();
    {
        printf("--- test SetOvalErrArrByPoissonErr()\n");
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 2.0);
        gd2d->SetPoint(1, 1.0, 3.0);
        gd2d->SetPoint(2, 2.0, 4.0);
        gd2d->SetPoint(3, 3.0, 5.0);
        gd2d->SetOvalErrArrByPoissonErr();
	gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }

//    GraphDataTerr2d* const Clone() const;
    {
        printf("--- test Clone\n");
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, -0.2, 10.0, 0.5, -1.5);
        gd2d->SetPoint(1, 1.0, 0.2, -0.4, 10.1, 0.6, -1.6);
        gd2d->SetPoint(2, 2.0, 0.3, -0.6, 10.2, 0.7, -1.7);
        gd2d->SetPoint(3, 3.0, 0.4, -0.8, 10.3, 0.8, -1.8);
	gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
        printf("--- \n");
        GraphDataTerr2d* gd2d_new = gd2d->Clone();
	gd2d_new->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
	delete gd2d;
	delete gd2d_new;

        printf("=== \n");
    }

//    void Load(string file);
    {
        printf("--- test Load(string file)\n");
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
        gd2d->Load("data/test_graph2d_terr.dat");
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);

//        gd2d->Load("data/test_graph2d_nerr.dat");
//        gd2d->PrintInfo(stdout);
//        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
        
	delete gd2d;

        printf("=== \n");
    }

    
//    void Load(string file, string format);
    {
        printf("--- test Load(string file, string format)\n");
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
        gd2d->Load("data/test_graph2d_terr.dat", "x,xe+,xe-,y,ye+,ye-");
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);

        gd2d->Load("data/test_graph2d_serr.dat", "x,xe,y,ye");
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);        

        gd2d->Load("data/test_graph2d_nerr.dat", "x,y");
        gd2d->PrintInfo(stdout);
        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);        
        
	delete gd2d;

        printf("=== \n");
    }
    
//    void Sort();
    {
        printf("--- test Sort\n");
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, -0.2, 10.0, 0.5, -1.5);
        gd2d->SetPoint(1, 3.0, 0.2, -0.4, 10.1, 0.6, -1.6);
        gd2d->SetPoint(2, 2.0, 0.3, -0.6, 10.2, 0.7, -1.7);
        gd2d->SetPoint(3, 1.0, 0.4, -0.8, 10.3, 0.8, -1.8);
        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
        gd2d->Sort();
        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);

	delete gd2d;

        printf("=== \n");
    }

//    const DataArrayTerr1d* const GetXvalArr() const;
//    const DataArrayTerr1d* const GetOvalArr() const;
    {
        printf("--- test GetXvalArr()\n");
        printf("--- test GetOvalArr()\n");        
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, -0.2, 10.0, 0.5, -1.5);
        gd2d->SetPoint(1, 1.0, 0.2, -0.4, 10.1, 0.6, -1.6);
        gd2d->SetPoint(2, 2.0, 0.3, -0.6, 10.2, 0.7, -1.7);
        gd2d->SetPoint(3, 3.0, 0.4, -0.8, 10.3, 0.8, -1.8);
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd2d->GetXvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValTerrPlusElm(%ld) = %e\n",
                   idata, gd2d->GetXvalArr()->GetValTerrPlusElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValTerrMinusElm(%ld) = %e\n",
                   idata, gd2d->GetXvalArr()->GetValTerrMinusElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd2d->GetOvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValTerrPlusElm(%ld) = %e\n",
                   idata, gd2d->GetOvalArr()->GetValTerrPlusElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValTerrMinusElm(%ld) = %e\n",
                   idata, gd2d->GetOvalArr()->GetValTerrMinusElm(idata));
        }
        
	delete gd2d;

        printf("=== \n");
    }

//    double GetXvalTerrPlusElm(long idata) const;
//    double GetXvalTerrMinusElm(long idata) const;
//    double GetOvalTerrPlusElm(long idata) const;
//    double GetOvalTerrMinusElm(long idata) const;
    {
        printf("--- test GetXvalTerrPlusElm(long idata)\n");
        printf("--- test GetXvalTerrMinusElm(long idata)\n");
        printf("--- test GetOvalTerrPlusElm(long idata)\n");
        printf("--- test GetOvalTerrMinusElm(long idata)\n");                

	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, -0.2, 10.0, 0.5, -1.5);
        gd2d->SetPoint(1, 1.0, 0.2, -0.4, 10.1, 0.6, -1.6);
        gd2d->SetPoint(2, 2.0, 0.3, -0.6, 10.2, 0.7, -1.7);
        gd2d->SetPoint(3, 3.0, 0.4, -0.8, 10.3, 0.8, -1.8);
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalElm(%ld) = %e\n",
                   idata, gd2d->GetXvalElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalTerrPlusElm(%ld) = %e\n",
                   idata, gd2d->GetXvalTerrPlusElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalTerrMinusElm(%ld) = %e\n",
                   idata, gd2d->GetXvalTerrMinusElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalElm(%ld) = %e\n",
                   idata, gd2d->GetOvalElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalTerrPlusElm(%ld) = %e\n",
                   idata, gd2d->GetOvalTerrPlusElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalTerrMinusElm(%ld) = %e\n",
                   idata, gd2d->GetOvalTerrMinusElm(idata));
        }
        
	delete gd2d;

        printf("=== \n");
    }

//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_oval) const;
    {
        printf("--- test PrintData\n");
	GraphDataTerr2d* gd2d = new GraphDataTerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, -0.2, 10.0, 0.5, -1.5);
        gd2d->SetPoint(1, 1.0, 0.2, -0.4, 10.1, 0.6, -1.6);
        gd2d->SetPoint(2, 2.0, 0.3, -0.6, 10.2, 0.7, -1.7);
        gd2d->SetPoint(3, 3.0, 0.4, -0.8, 10.3, 0.8, -1.8);

        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);

        printf("--- \n");
        gd2d->PrintData(stdout, "x,xe,y", 0.0, 0.0);

        printf("--- \n");
        gd2d->PrintData(stdout, "x,y,ye", 0.0, 0.0);

        printf("--- \n");
        gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        printf("--- \n");
        gd2d->PrintData(stdout, "x,y,ye+,ye-", 0.0, 0.0);

        printf("--- \n");
        gd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        printf("--- \n");
        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
        
	delete gd2d;

        printf("=== \n");
    }
    
//    TGraphAsymmErrors* const GenTGraph(double offset_xval,
//                                       double offset_oval) const;
    {
        printf("--- test GenTGraph\n");
        GraphDataTerr2d* gd2d = new GraphDataTerr2d;
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, -0.2, 10.0, 0.5, -1.5);
        gd2d->SetPoint(1, 1.0, 0.2, -0.4, 10.1, 0.6, -1.6);
        gd2d->SetPoint(2, 2.0, 0.3, -0.6, 10.2, 0.7, -1.7);
        gd2d->SetPoint(3, 3.0, 0.4, -0.8, 10.3, 0.8, -1.8);
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
        GraphDataTerr2d* gd2d = new GraphDataTerr2d;
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, -0.2, 10.0, 0.5, -1.5);
        gd2d->SetPoint(1, 1.0, 0.2, -0.4, 10.1, 0.6, -1.6);
        gd2d->SetPoint(2, 2.0, 0.3, -0.6, 10.2, 0.7, -1.7);
        gd2d->SetPoint(3, 3.0, 0.4, -0.8, 10.3, 0.8, -1.8);

        Interval* interval = gd2d->GenInterval();
        MirQdpTool::MkQdp(interval, "temp.qdp");

        delete gd2d;

        printf("=== \n");
    }
   
//    Interval* const GenIntervalAboveThreshold(double threshold) const;
    {
        printf("--- test GenIntervalAboveThreshold(double threshold)\n");
        GraphDataTerr2d* gd2d = new GraphDataTerr2d;
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, -0.2, 10.0, 0.5, -1.5);
        gd2d->SetPoint(1, 1.0, 0.2, -0.4, 10.1, 0.6, -1.6);
        gd2d->SetPoint(2, 2.0, 0.3, -0.6, 10.2, 0.7, -1.7);
        gd2d->SetPoint(3, 3.0, 0.4, -0.8, 10.3, 0.8, -1.8);

        Interval* interval = gd2d->GenIntervalAboveThreshold(10.15);
        MirQdpTool::MkQdp(interval, "temp.qdp");

        delete gd2d;

        printf("=== \n");
    }
 
//    Interval* const GenIntervalBelowThreshold(double threshold) const;
    {
        printf("--- test GenIntervalBelowThreshold(double threshold)\n");
        GraphDataTerr2d* gd2d = new GraphDataTerr2d;
        gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1, -0.2, 10.0, 0.5, -1.5);
        gd2d->SetPoint(1, 1.0, 0.2, -0.4, 10.1, 0.6, -1.6);
        gd2d->SetPoint(2, 2.0, 0.3, -0.6, 10.2, 0.7, -1.7);
        gd2d->SetPoint(3, 3.0, 0.4, -0.8, 10.3, 0.8, -1.8);

        Interval* interval = gd2d->GenIntervalBelowThreshold(10.15);
        MirQdpTool::MkQdp(interval, "temp.qdp");

        delete gd2d;

        printf("=== \n");
    }

    return status_prog;
}
