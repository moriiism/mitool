#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_graph2d_nerr.h"
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
	GraphDataNerr2d* gd2d = new GraphDataNerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1);
        gd2d->SetPoint(1, 1.0, 1.1);
        gd2d->SetPoint(2, 2.0, 2.1);
        gd2d->SetPoint(3, 3.0, 3.1);
        gd2d->Save("temp.dat", "x,y");
	gd2d->PrintData(stdout, "x,y", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }

//    GraphDataNerr2d* const Clone() const;
    {
        printf("--- test Clone;\n");
	GraphDataNerr2d* gd2d_1 = new GraphDataNerr2d;
	gd2d_1->Init(4);
        gd2d_1->SetPoint(0, 0.0, 0.1);
        gd2d_1->SetPoint(1, 1.0, 1.1);
        gd2d_1->SetPoint(2, 2.0, 2.1);
        gd2d_1->SetPoint(3, 3.0, 3.1);
	gd2d_1->PrintData(stdout, "x,y", 0.0, 0.0);

	GraphDataNerr2d* gd2d_2 = gd2d_1->Clone();
	gd2d_2->PrintData(stdout, "x,y", 0.0, 0.0);

	delete gd2d_1;
	delete gd2d_2;

        printf("=== \n");
    }

//    void Load(string file);
    {
        printf("--- test Load\n");
	GraphDataNerr2d* gd2d_1 = new GraphDataNerr2d;
	gd2d_1->Load("data/test_graph2d_nerr.dat");
        gd2d_1->PrintInfo(stdout);
	gd2d_1->PrintData(stdout, "x,y", 0.0, 0.0);
	delete gd2d_1;

        printf("=== \n");
    }


//    void Load(string file, string format);
    {
        printf("--- test Load\n");
	GraphDataNerr2d* gd2d_1 = new GraphDataNerr2d;
	gd2d_1->Load("data/test_graph2d_nerr.dat", "x,y");
        gd2d_1->PrintInfo(stdout);
	gd2d_1->PrintData(stdout, "x,y", 0.0, 0.0);
	delete gd2d_1;

        printf("=== \n");
    }
   
//    void Sort();
    {
        printf("--- test Init;\n");
	GraphDataNerr2d* gd2d = new GraphDataNerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1);
        gd2d->SetPoint(1, 3.0, 1.1);
        gd2d->SetPoint(2, 2.0, 2.1);
        gd2d->SetPoint(3, 1.0, 3.1);
        gd2d->PrintInfo(stdout);        
	gd2d->PrintData(stdout, "x,y", 0.0, 0.0);
        gd2d->Sort();
        printf("--- \n");
        gd2d->PrintInfo(stdout);        
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);
        
	delete gd2d;

        printf("=== \n");
    }
  
//    const DataArrayNerr1d* const GetXvalArr() const;
//    const DataArrayNerr1d* const GetOvalArr() const;
    {
        printf("--- test GetXvalArr()\n");
        printf("--- test GetOvalArr()\n");        
	GraphDataNerr2d* gd2d = new GraphDataNerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1);
        gd2d->SetPoint(1, 3.0, 1.1);
        gd2d->SetPoint(2, 2.0, 2.1);
        gd2d->SetPoint(3, 1.0, 3.1);
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetXvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd2d->GetXvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
            printf("GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, gd2d->GetOvalArr()->GetValElm(idata));
        }
        
	delete gd2d;

        printf("=== \n");
    }


//    TGraph* const GenTGraph(double offset_xval,
//                            double offset_oval) const;
    {
        printf("--- test GenTGraph\n");
	GraphDataNerr2d* gd2d = new GraphDataNerr2d;
	gd2d->Init(4);
        gd2d->SetPoint(0, 0.0, 0.1);
        gd2d->SetPoint(1, 3.0, 1.1);
        gd2d->SetPoint(2, 2.0, 2.1);
        gd2d->SetPoint(3, 1.0, 5.1);

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("def");
        
        TGraph* tg = gd2d->GenTGraph(-0.1, -10.0);
        tg->Draw();
        root_tool->GetTCanvas()->Print("aaaaa.png");

	delete gd2d;
        delete tg;
        delete root_tool;

        printf("=== \n");
    }




    return status_prog;
}
