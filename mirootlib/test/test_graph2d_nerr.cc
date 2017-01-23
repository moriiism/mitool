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

//    void Init();
    {
        printf("--- test Init;\n");
	GraphDataNerr2d* gd2d = new GraphDataNerr2d;
	gd2d->Init();
	gd2d->PrintData(stdout, "x,y", 0.0, 0.0);
	delete gd2d;

        printf("=== \n");
    }

//    GraphDataNerr2d* const Clone() const;
    {
        printf("--- test Clone;\n");
	GraphDataNerr2d* gd2d_1 = new GraphDataNerr2d;
	gd2d_1->Init();
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
	gd2d_1->Load("");
	gd2d_1->PrintData(stdout, "x,y", 0.0, 0.0);
	delete gd2d_1;

        printf("=== \n");
    }


//    void Load(string file, string format);
    {
        printf("--- test Load\n");
	GraphDataNerr2d* gd2d_1 = new GraphDataNerr2d;
	gd2d_1->Load("");
	gd2d_1->PrintData(stdout, "x,y", 0.0, 0.0);
	delete gd2d_1;

        printf("=== \n");
    }

//    void Sort();
    {
        printf("--- test Sort\n");
	
	long ndata = 5;
	vector<double> xval_vec(ndata);
	vector<double> oval_vec(ndata);
	xval_vec[0] = -1.0;
	xval_vec[1] =  0.0;
	xval_vec[2] =  1.0;
	xval_vec[3] =  2.0;
	xval_vec[4] =  3.0;
	oval_vec[0] = -10.0;
	oval_vec[1] =  0.0;
	oval_vec[2] =  10.0;
	oval_vec[3] =  20.0;
	oval_vec[4] =  30.0;

        DataArrayNerr1d* da1d_x = new DataArrayNerr1d;
	da1d_x->Init(5);
	da1d_x->SetVal(xval_vec);
        DataArrayNerr1d* da1d_o = new DataArrayNerr1d;
	da1d_o->Init(5);
	da1d_o->SetVal(oval_vec);

	GraphDataNerr2d* gd2d_1 = new GraphDataNerr2d;
	gd2d_1->Init();
	gd2d_1->SetXvalArr(da1d_x);
	gd2d_1->SetOvalArr(da1d_o);

	delete da1d_x;
	delete da1d_o;
	gd2d_1->PrintData(stdout, "x,y", 0.0, 0.0);
	gd2d_1->Sort();

	gd2d_1->PrintData(stdout, "x,y", 0.0, 0.0);
	delete gd2d_1;

        printf("=== \n");
    }



//    
//    const DataArrayNerr1d* const GetXvalArr() const;
//    const DataArrayNerr1d* const GetOvalArr() const;
//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_oval) const;
//    TGraph* const GenTGraph(double offset_xval,
//                            double offset_oval) const;



    return status_prog;
}
