#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_data1d_nerr.h"
#include "mir_data1d_serr.h"
#include "mir_data1d_terr.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Copy(const DataArray1d* const org);

    // --> Nerr
    
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- Nerr ---> Nerr\n");
        DataArrayNerr1d* da1d_org = new DataArrayNerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        da1d_org->SetVal(val_vec);

        DataArrayNerr1d* da1d_dist = new DataArrayNerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- poly Nerr ---> poly Nerr\n");
        DataArray1d* da1d_org = new DataArrayNerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        da1d_org->SetVal(val_vec);

        DataArray1d* da1d_dist = new DataArrayNerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }
    
    
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- Serr ---> Nerr\n");
        DataArraySerr1d* da1d_org = new DataArraySerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_serr(ndata);
        val_vec_serr[0] = 0.1;
        val_vec_serr[1] = 0.2;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValSerr(val_vec_serr);

        DataArrayNerr1d* da1d_dist = new DataArrayNerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- poly Serr ---> poly Nerr\n");
        DataArray1d* da1d_org = new DataArraySerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_serr(ndata);
        val_vec_serr[0] = 0.1;
        val_vec_serr[1] = 0.2;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValSerr(val_vec_serr);

        DataArray1d* da1d_dist = new DataArrayNerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- Terr ---> Nerr\n");
        DataArrayTerr1d* da1d_org = new DataArrayTerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_terr_plus(ndata);
        val_vec_terr_plus[0] = 0.1;
        val_vec_terr_plus[1] = 0.2;
        vector<double> val_vec_terr_minus(ndata);
        val_vec_terr_minus[0] = -0.5;
        val_vec_terr_minus[1] = -0.6;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValTerr(val_vec_terr_plus, val_vec_terr_minus);

        DataArrayNerr1d* da1d_dist = new DataArrayNerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- poly Terr ---> poly Nerr\n");
        DataArray1d* da1d_org = new DataArrayTerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_terr_plus(ndata);
        val_vec_terr_plus[0] = 0.1;
        val_vec_terr_plus[1] = 0.2;
        vector<double> val_vec_terr_minus(ndata);
        val_vec_terr_minus[0] = -0.5;
        val_vec_terr_minus[1] = -0.6;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValTerr(val_vec_terr_plus, val_vec_terr_minus);

        DataArray1d* da1d_dist = new DataArrayNerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    
    // ---> Serr
    
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- Nerr ---> Serr\n");
        DataArrayNerr1d* da1d_org = new DataArrayNerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        da1d_org->SetVal(val_vec);

        DataArraySerr1d* da1d_dist = new DataArraySerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- poly Nerr ---> poly Serr\n");
        DataArray1d* da1d_org = new DataArrayNerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        da1d_org->SetVal(val_vec);

        DataArray1d* da1d_dist = new DataArraySerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }
    
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- Serr ---> Serr\n");
        DataArraySerr1d* da1d_org = new DataArraySerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_serr(ndata);
        val_vec_serr[0] = 0.1;
        val_vec_serr[1] = 0.2;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValSerr(val_vec_serr);

        DataArraySerr1d* da1d_dist = new DataArraySerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- poly Serr ---> poly Serr\n");
        DataArray1d* da1d_org = new DataArraySerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_serr(ndata);
        val_vec_serr[0] = 0.1;
        val_vec_serr[1] = 0.2;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValSerr(val_vec_serr);

        DataArray1d* da1d_dist = new DataArraySerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- Terr ---> Serr\n");
        DataArrayTerr1d* da1d_org = new DataArrayTerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_terr_plus(ndata);
        val_vec_terr_plus[0] = 0.1;
        val_vec_terr_plus[1] = 0.2;
        vector<double> val_vec_terr_minus(ndata);
        val_vec_terr_minus[0] = -0.5;
        val_vec_terr_minus[1] = -0.6;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValTerr(val_vec_terr_plus, val_vec_terr_minus);

        DataArraySerr1d* da1d_dist = new DataArraySerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- poly Terr ---> poly Serr\n");
        DataArray1d* da1d_org = new DataArrayTerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_terr_plus(ndata);
        val_vec_terr_plus[0] = 0.1;
        val_vec_terr_plus[1] = 0.2;
        vector<double> val_vec_terr_minus(ndata);
        val_vec_terr_minus[0] = -0.5;
        val_vec_terr_minus[1] = -0.6;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValTerr(val_vec_terr_plus, val_vec_terr_minus);

        DataArray1d* da1d_dist = new DataArraySerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    
    // ---> Terr
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- Nerr ---> Terr\n");
        DataArrayNerr1d* da1d_org = new DataArrayNerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        da1d_org->SetVal(val_vec);

        DataArrayTerr1d* da1d_dist = new DataArrayTerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- poly Nerr ---> poly Terr\n");
        DataArray1d* da1d_org = new DataArrayNerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        da1d_org->SetVal(val_vec);

        DataArray1d* da1d_dist = new DataArrayTerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- Serr ---> Terr\n");
        DataArraySerr1d* da1d_org = new DataArraySerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_serr(ndata);
        val_vec_serr[0] = 0.1;
        val_vec_serr[1] = 0.2;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValSerr(val_vec_serr);

        DataArrayTerr1d* da1d_dist = new DataArrayTerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- poly Serr ---> poly Terr\n");
        DataArray1d* da1d_org = new DataArraySerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_serr(ndata);
        val_vec_serr[0] = 0.1;
        val_vec_serr[1] = 0.2;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValSerr(val_vec_serr);

        DataArray1d* da1d_dist = new DataArrayTerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- Terr ---> Terr\n");
        DataArrayTerr1d* da1d_org = new DataArrayTerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_terr_plus(ndata);
        val_vec_terr_plus[0] = 0.1;
        val_vec_terr_plus[1] = 0.2;
        vector<double> val_vec_terr_minus(ndata);
        val_vec_terr_minus[0] = -0.5;
        val_vec_terr_minus[1] = -0.6;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValTerr(val_vec_terr_plus, val_vec_terr_minus);

        DataArrayTerr1d* da1d_dist = new DataArrayTerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }

    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        printf("--- poly Terr ---> poly Terr\n");
        DataArray1d* da1d_org = new DataArrayTerr1d("org");
        int ndata = 2;
        da1d_org->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 2.0;
        vector<double> val_vec_terr_plus(ndata);
        val_vec_terr_plus[0] = 0.1;
        val_vec_terr_plus[1] = 0.2;
        vector<double> val_vec_terr_minus(ndata);
        val_vec_terr_minus[0] = -0.5;
        val_vec_terr_minus[1] = -0.6;        
        da1d_org->SetVal(val_vec);
        da1d_org->SetValTerr(val_vec_terr_plus, val_vec_terr_minus);

        DataArray1d* da1d_dist = new DataArrayTerr1d("dist");
        da1d_dist->Copy(da1d_org);
        da1d_dist->PrintInfo(stdout);
        da1d_dist->PrintData(stdout, 1, 0.0);

        delete da1d_org;
        delete da1d_dist;
        
        printf("=== \n");
    }
    
    





    return status_prog;
}
