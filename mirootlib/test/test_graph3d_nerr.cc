#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_graph3d_nerr.h"
#include "mir_root_tool.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Init(long ndata);    
    {
        printf("--- test Init;\n");
	GraphDataNerr3d* gd3d = new GraphDataNerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.5, 1.1);
        gd3d->SetPoint(2, 2.0, 2.5, 2.1);
        gd3d->SetPoint(3, 3.0, 3.5, 3.1);
        gd3d->Save("temp.dat", "x,y,z");
	gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

//    GraphDataNerr3d* const Clone() const;
    {
        printf("--- test Clone;\n");
	GraphDataNerr3d* gd3d = new GraphDataNerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.5, 1.1);
        gd3d->SetPoint(2, 2.0, 2.5, 2.1);
        gd3d->SetPoint(3, 3.0, 3.5, 3.1);
	gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

	GraphDataNerr3d* gd3d_new = gd3d->Clone();
	gd3d_new->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

	delete gd3d;
	delete gd3d_new;

        printf("=== \n");
    }

//    void Load(string file);
    {
        printf("--- test Load\n");
	GraphDataNerr3d* gd3d = new GraphDataNerr3d;
	gd3d->Load("data/test_graph3d_nerr.dat");
        gd3d->PrintInfo(stdout);
	gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

   
//    void Load(string file, string format);
    {
        printf("--- test Load\n");
	GraphDataNerr3d* gd3d = new GraphDataNerr3d;
	gd3d->Load("data/test_graph3d_nerr.dat", "x,y,z");
        gd3d->PrintInfo(stdout);
	gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
	delete gd3d;

        printf("=== \n");
    }

 
//    const DataArrayNerr1d* const GetXvalArr() const;
//    const DataArrayNerr1d* const GetYvalArr() const;
//    const DataArrayNerr1d* const GetOvalArr() const;
    {
        printf("--- test GetXvalArr()\n");
        printf("--- test GetYvalArr()\n");        
        printf("--- test GetOvalArr()\n");        
	GraphDataNerr3d* gd3d = new GraphDataNerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.5, 1.1);
        gd3d->SetPoint(2, 2.0, 2.5, 2.1);
        gd3d->SetPoint(3, 3.0, 3.5, 3.1);
	gd3d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd3d->GetXvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetYvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd3d->GetYvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd3d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd3d->GetOvalArr()->GetValElm(idata));
        }
        
	delete gd3d;

        printf("=== \n");
    }

//    TGraph2D* const GenTGraph2D(double offset_xval,
//                                double offset_yval,
//                                double offset_oval) const;
    {
        printf("--- test GenTGraph2D\n");
	GraphDataNerr3d* gd3d = new GraphDataNerr3d;
	gd3d->Init(4);
        gd3d->SetPoint(0, 0.0, 0.5, 0.1);
        gd3d->SetPoint(1, 1.0, 1.0, 1.1);
        gd3d->SetPoint(2, 2.0, 2.5, 5.1);
        gd3d->SetPoint(3, 3.0, 5.5, 9.1);        

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        
        TGraph2D* tg2d = gd3d->GenTGraph2D(0.0, 0.0, 0.0);
        tg2d->Draw("line");
        root_tool->GetTCanvas()->Print("aaa.png");

	delete gd3d;
        delete tg2d;
        delete root_tool;

        printf("=== \n");
    }

    return status_prog;
}



