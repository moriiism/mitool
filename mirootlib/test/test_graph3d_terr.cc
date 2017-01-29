#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_graph3d_terr.h"
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
//                  double xval, double xval_terr_plus, double xval_terr_minus,
//                  double yval, double yval_terr_plus, double yval_terr_minus,
//                  double oval, double oval_terr_plus, double oval_terr_minus);
    {
        printf("--- test Init;\n");
        printf("--- test SetPoint\n");
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, -0.2,   10.0, 0.5, -1.5,   5.0, 0.9, -2.5);
        gd3d->SetPoint(1, 1.0, 0.2, -0.4,   11.0, 0.6, -1.6,   6.0, 1.0, -2.6);
        gd3d->SetPoint(2, 2.0, 0.3, -0.6,   12.0, 0.7, -1.7,   7.0, 1.1, -2.7);
        gd3d->SetPoint(3, 3.0, 0.4, -0.8,   13.0, 0.8, -1.8,   8.0, 1.2, -2.8);
	gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
        gd3d->Save("temp.dat", "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-");
	delete gd3d;

        printf("=== \n");
    }

//    void SetXvalTerrArr(long ndata, const double* const val_serr);
//    void SetYvalTerrArr(long ndata, const double* const val_serr);
//    void SetOvalTerrArr(long ndata, const double* const val_serr);
    {
        printf("--- test SetXvalTerrArr\n");
        printf("--- test SetYvalTerrArr\n");        
        printf("--- test SetOvalTerrArr\n");        
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
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

        yval[0] = 4.0;
        yval[1] = 5.0;
        yval[2] = 6.0;
        yval[3] = 7.0;
        yval_serr[0] = 0.5;
        yval_serr[1] = 0.6;
        yval_serr[2] = 0.7;
        yval_serr[3] = 0.8;
        
        oval[0] = 10.0;
        oval[1] = 10.1;
        oval[2] = 10.2;
        oval[3] = 10.3;
        oval_serr[0] = 1.5;
        oval_serr[1] = 1.6;
        oval_serr[2] = 1.7;
        oval_serr[3] = 1.8;

        gd3d->SetXvalArr(4, xval);
        gd3d->SetXvalTerrArr(4, xval_serr);
        gd3d->SetYvalArr(4, yval);
        gd3d->SetYvalTerrArr(4, yval_serr);        
        gd3d->SetOvalArr(4, oval);
        gd3d->SetOvalTerrArr(4, oval_serr);
	gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

//    void SetXvalTerrArr(vector<double> val_serr);
//    void SetYvalTerrArr(vector<double> val_serr);
//    void SetOvalTerrArr(vector<double> val_serr);

    {
        printf("--- test SetXvalTerrArr\n");
        printf("--- test SetYvalTerrArr\n");        
        printf("--- test SetOvalTerrArr\n");        
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
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

        yval[0] = 4.0;
        yval[1] = 5.0;
        yval[2] = 6.0;
        yval[3] = 7.0;
        yval_serr[0] = 0.5;
        yval_serr[1] = 0.6;
        yval_serr[2] = 0.7;
        yval_serr[3] = 0.8;
        
        oval[0] = 10.0;
        oval[1] = 10.1;
        oval[2] = 10.2;
        oval[3] = 10.3;
        oval_serr[0] = 1.5;
        oval_serr[1] = 1.6;
        oval_serr[2] = 1.7;
        oval_serr[3] = 1.8;

        gd3d->SetXvalArr(xval);
        gd3d->SetXvalTerrArr(xval_serr);
        gd3d->SetYvalArr(yval);
        gd3d->SetYvalTerrArr(yval_serr);        
        gd3d->SetOvalArr(oval);
        gd3d->SetOvalTerrArr(oval_serr);
	gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

//    void SetXvalTerrArr(long ndata,
//                        const double* const val_terr_plus,
//                        const double* const val_terr_minus);
//    void SetYvalTerrArr(long ndata,
//                        const double* const val_terr_plus,
//                        const double* const val_terr_minus);
//    void SetOvalTerrArr(long ndata,
//                        const double* const val_terr_plus,
//                        const double* const val_terr_minus);
   {
        printf("--- test SetXvalTerrArr\n");
        printf("--- test SetYvalTerrArr\n");        
        printf("--- test SetOvalTerrArr\n");        
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
	gd3d->Init(4);
        double xval[4];
        double xval_terr_plus[4];
        double xval_terr_minus[4];
        double yval[4];
        double yval_terr_plus[4];
        double yval_terr_minus[4];        
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

        yval[0] = 10.0;
        yval[1] = 12.0;
        yval[2] = 14.0;
        yval[3] = 16.0;
        yval_terr_plus[0] = 1.1;
        yval_terr_plus[1] = 1.2;
        yval_terr_plus[2] = 1.3;
        yval_terr_plus[3] = 1.4;
        yval_terr_minus[0] = -10.0;
        yval_terr_minus[1] = -11.0;
        yval_terr_minus[2] = -12.0;
        yval_terr_minus[3] = -13.0;
        
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
        
        gd3d->SetXvalArr(4, xval);
        gd3d->SetXvalTerrArr(4, xval_terr_plus, xval_terr_minus);
        gd3d->SetYvalArr(4, yval);
        gd3d->SetYvalTerrArr(4, yval_terr_plus, yval_terr_minus);
        gd3d->SetOvalArr(4, oval);
        gd3d->SetOvalTerrArr(4, oval_terr_plus, oval_terr_minus);
	gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

//    void SetXvalTerrArr(vector<double> val_terr_plus,
//                        vector<double> val_terr_minus);
//    void SetYvalTerrArr(vector<double> val_terr_plus,
//                        vector<double> val_terr_minus);
//    void SetOvalTerrArr(vector<double> val_terr_plus,
//                        vector<double> val_terr_minus);

   {
        printf("--- test SetXvalTerrArr\n");
        printf("--- test SetYvalTerrArr\n");        
        printf("--- test SetOvalTerrArr\n");        
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
	gd3d->Init(4);
        vector<double> xval(4);
        vector<double> xval_terr_plus(4);
        vector<double> xval_terr_minus(4);
        vector<double> yval(4);
        vector<double> yval_terr_plus(4);
        vector<double> yval_terr_minus(4);        
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

        yval[0] = 10.0;
        yval[1] = 12.0;
        yval[2] = 14.0;
        yval[3] = 16.0;
        yval_terr_plus[0] = 1.1;
        yval_terr_plus[1] = 1.2;
        yval_terr_plus[2] = 1.3;
        yval_terr_plus[3] = 1.4;
        yval_terr_minus[0] = -10.0;
        yval_terr_minus[1] = -11.0;
        yval_terr_minus[2] = -12.0;
        yval_terr_minus[3] = -13.0;
        
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
        
        gd3d->SetXvalArr(xval);
        gd3d->SetXvalTerrArr(xval_terr_plus, xval_terr_minus);
        gd3d->SetYvalArr(yval);
        gd3d->SetYvalTerrArr(yval_terr_plus, yval_terr_minus);
        gd3d->SetOvalArr(oval);
        gd3d->SetOvalTerrArr(oval_terr_plus, oval_terr_minus);
	gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

//    using GraphData3d::SetPoint;
    {
        printf("--- test using GraphData3d::SetPoint\n");
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 10.0, 20.0);
        gd3d->SetPoint(1, 1.0, 10.1, 21.0);
        gd3d->SetPoint(2, 2.0, 10.2, 22.0);
        gd3d->SetPoint(3, 3.0, 10.3, 23.0);
	gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }
   
//    void SetOvalErrArrByPoissonErr();
    {
        printf("--- test SetOvalErrArrByPoissonErr()\n");
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
	gd3d->Init(2);
        gd3d->SetPoint(0, 0.0, 2.0, 4.0);
        gd3d->SetPoint(1, 1.0, 3.0, 5.0);
        gd3d->SetOvalErrArrByPoissonErr();
	gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

   
//    GraphDataTerr3d* const Clone() const;
    {
        printf("--- test Clone\n");
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, -0.2,   10.0, 0.5, -1.5,   5.0, 0.9, -2.5);
        gd3d->SetPoint(1, 1.0, 0.2, -0.4,   11.0, 0.6, -1.6,   6.0, 1.0, -2.6);
        gd3d->SetPoint(2, 2.0, 0.3, -0.6,   12.0, 0.7, -1.7,   7.0, 1.1, -2.7);
        gd3d->SetPoint(3, 3.0, 0.4, -0.8,   13.0, 0.8, -1.8,   8.0, 1.2, -2.8);
	gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
        printf("--- \n");
        GraphDataTerr3d* gd3d_new = gd3d->Clone();
	gd3d_new->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
	delete gd3d;
	delete gd3d_new;

        printf("=== \n");
    }

//    void Load(string file);
    {
        printf("--- test Load(string file)\n");
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
	//gd3d->Init(4);
        //gd3d->SetPoint(0, 0.0, 0.1, -0.2,   10.0, 0.5, -1.5,   5.0, 0.9, -2.5);
        //gd3d->SetPoint(1, 1.0, 0.2, -0.4,   11.0, 0.6, -1.6,   6.0, 1.0, -2.6);
        //gd3d->SetPoint(2, 2.0, 0.3, -0.6,   12.0, 0.7, -1.7,   7.0, 1.1, -2.7);
        //gd3d->SetPoint(3, 3.0, 0.4, -0.8,   13.0, 0.8, -1.8,   8.0, 1.2, -2.8);
        //gd3d->Save("temp.dat", "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);

        gd3d->Load("data/test_graph3d_terr.dat");
        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);

//        gd3d->Load("data/test_graph3d_nerr.dat");
//        gd3d->PrintInfo(stdout);
//        gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);

//        gd3d->Load("data/test_graph3d_serr.dat");
//        gd3d->PrintInfo(stdout);
//        gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
        
	delete gd3d;

        printf("=== \n");
    }
   
//    void Load(string file, string format);
    {
        printf("--- test Load(string file, string format)\n");
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
        gd3d->Load("data/test_graph3d_terr.dat", "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-");
        gd3d->PrintInfo(stdout);
        gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);


//        gd3d->Load("data/test_graph3d_serr.dat", "x,xe,y,ye,z,ze");
//        gd3d->PrintInfo(stdout);
//        gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);

//        gd3d->Load("data/test_graph3d_nerr.dat", "x,y,z");
//        gd3d->PrintInfo(stdout);
//        gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
        
	delete gd3d;

        printf("=== \n");
    }

//    const DataArrayTerr1d* const GetXvalArr() const;
//    const DataArrayTerr1d* const GetYvalArr() const;
//    const DataArrayTerr1d* const GetOvalArr() const;
    {
        printf("--- test GetXvalArr()\n");
        printf("--- test GetYvalArr()\n");
        printf("--- test GetOvalArr()\n");        
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, -0.2,   10.0, 0.5, -1.5,   5.0, 0.9, -2.5);
        gd3d->SetPoint(1, 1.0, 0.2, -0.4,   11.0, 0.6, -1.6,   6.0, 1.0, -2.6);
        gd3d->SetPoint(2, 2.0, 0.3, -0.6,   12.0, 0.7, -1.7,   7.0, 1.1, -2.7);
        gd3d->SetPoint(3, 3.0, 0.4, -0.8,   13.0, 0.8, -1.8,   8.0, 1.2, -2.8);
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd3d->GetXvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValTerrPlusElm(%ld) = %e\n",
                   idata, gd3d->GetXvalArr()->GetValTerrPlusElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValTerrMinusElm(%ld) = %e\n",
                   idata, gd3d->GetXvalArr()->GetValTerrMinusElm(idata));
        }

        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd3d->GetYvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalArr()->GetValTerrPlusElm(%ld) = %e\n",
                   idata, gd3d->GetYvalArr()->GetValTerrPlusElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalArr()->GetValTerrMinusElm(%ld) = %e\n",
                   idata, gd3d->GetYvalArr()->GetValTerrMinusElm(idata));
        }
        
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd3d->GetOvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValTerrPlusElm(%ld) = %e\n",
                   idata, gd3d->GetOvalArr()->GetValTerrPlusElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValTerrMinusElm(%ld) = %e\n",
                   idata, gd3d->GetOvalArr()->GetValTerrMinusElm(idata));
        }
        
	delete gd3d;

        printf("=== \n");
    }

//    double GetXvalTerrPlusElm(long idata) const
//    double GetXvalTerrMinusElm(long idata) const
//    double GetYvalTerrPlusElm(long idata) const
//    double GetYvalTerrMinusElm(long idata) const
//    double GetOvalTerrPlusElm(long idata) const
//    double GetOvalTerrMinusElm(long idata) const
    {
        printf("--- test GetXvalTerrPlusElm(long idata)\n");
        printf("--- test GetXvalTerrMinusElm(long idata)\n");
        printf("--- test GetYvalTerrPlusElm(long idata)\n");
        printf("--- test GetYvalTerrMinusElm(long idata)\n");
        printf("--- test GetOvalTerrPlusElm(long idata)\n");
        printf("--- test GetOvalTerrMinusElm(long idata)\n");                

	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, -0.2,   10.0, 0.5, -1.5,   5.0, 0.9, -2.5);
        gd3d->SetPoint(1, 1.0, 0.2, -0.4,   11.0, 0.6, -1.6,   6.0, 1.0, -2.6);
        gd3d->SetPoint(2, 2.0, 0.3, -0.6,   12.0, 0.7, -1.7,   7.0, 1.1, -2.7);
        gd3d->SetPoint(3, 3.0, 0.4, -0.8,   13.0, 0.8, -1.8,   8.0, 1.2, -2.8);
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalElm(%ld) = %e\n",
                   idata, gd3d->GetXvalElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalTerrPlusElm(%ld) = %e\n",
                   idata, gd3d->GetXvalTerrPlusElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalTerrMinusElm(%ld) = %e\n",
                   idata, gd3d->GetXvalTerrMinusElm(idata));
        }

        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalElm(%ld) = %e\n",
                   idata, gd3d->GetYvalElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalTerrPlusElm(%ld) = %e\n",
                   idata, gd3d->GetYvalTerrPlusElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalTerrMinusElm(%ld) = %e\n",
                   idata, gd3d->GetYvalTerrMinusElm(idata));
        }
        
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalElm(%ld) = %e\n",
                   idata, gd3d->GetOvalElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalTerrPlusElm(%ld) = %e\n",
                   idata, gd3d->GetOvalTerrPlusElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalTerrMinusElm(%ld) = %e\n",
                   idata, gd3d->GetOvalTerrMinusElm(idata));
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
	GraphDataTerr3d* gd3d = new GraphDataTerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.1, -0.2,   10.0, 0.5, -1.5,   5.0, 0.9, -2.5);
        gd3d->SetPoint(1, 1.0, 0.2, -0.4,   11.0, 0.6, -1.6,   6.0, 1.0, -2.6);
        gd3d->SetPoint(2, 2.0, 0.3, -0.6,   12.0, 0.7, -1.7,   7.0, 1.1, -2.7);
        gd3d->SetPoint(3, 3.0, 0.4, -0.8,   13.0, 0.8, -1.8,   8.0, 1.2, -2.8);

        gd3d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);
        
	delete gd3d;

        printf("=== \n");
    }


    return status_prog;
}



