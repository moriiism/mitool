#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_data1d_ope.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    DataArray1d* const GenDa1dByLoad(string file, string format);    
    {
        printf("--- test GenDa1dByLoad(string file, string format)\n");
        DataArray1d* da1d = DataArray1dOpe::GenDa1dByLoad("data/test_data1d_nerr.dat", "x");
        printf("da1d->GetClassName() = %s\n", da1d->GetClassName().c_str());
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d->GetClassName() );
        assert( 3 == da1d->GetNdata() );
        assert( 0 == da1d->GetFlagValSorted() );
        assert( 22 == da1d->GetValElm(0) );
        assert( 33 == da1d->GetValElm(1) );
        assert( 44 == da1d->GetValElm(2) );
        
        delete da1d;
        printf("=== \n");
    }

    {
        printf("--- test GenDa1dByLoad(string file, string format)\n");
        DataArray1d* da1d = DataArray1dOpe::GenDa1dByLoad("data/test_data1d_serr.dat", "x,xe");
        printf("da1d->GetClassName() = %s\n", da1d->GetClassName().c_str());
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d->GetClassName() );
        assert( 3 == da1d->GetNdata() );
        assert( 0 == da1d->GetFlagValSorted() );
        assert( 22 == da1d->GetValElm(0) );
        assert( 33 == da1d->GetValElm(1) );
        assert( 44 == da1d->GetValElm(2) );
        assert( 2.0 == da1d->GetValSerrElm(0) );
        assert( 3.0 == da1d->GetValSerrElm(1) );
        assert( 4.0 == da1d->GetValSerrElm(2) );
        
        delete da1d;
        printf("=== \n");
    }

    {
        printf("--- test GenDa1dByLoad(string file, string format)\n");
        DataArray1d* da1d = DataArray1dOpe::GenDa1dByLoad("data/test_data1d_terr.dat", "x,xe+,xe-");
        printf("da1d->GetClassName() = %s\n", da1d->GetClassName().c_str());
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        assert( "DataArrayTerr1d" == da1d->GetClassName() );
        assert( 3 == da1d->GetNdata() );
        assert( 0 == da1d->GetFlagValSorted() );
        assert( 22 == da1d->GetValElm(0) );
        assert( 33 == da1d->GetValElm(1) );
        assert( 44 == da1d->GetValElm(2) );
        assert( 2.0 == da1d->GetValTerrPlusElm(0) );
        assert( 3.0 == da1d->GetValTerrPlusElm(1) );
        assert( 4.0 == da1d->GetValTerrPlusElm(2) );
        assert( -0.2 == da1d->GetValTerrMinusElm(0) );
        assert( -0.3 == da1d->GetValTerrMinusElm(1) );
        assert( -0.4 == da1d->GetValTerrMinusElm(2) );
        
        delete da1d;
        printf("=== \n");
    }

//    void GetNot(const DataArray1d* const data_array,
//                DataArray1d* data_array_out);
    {
        printf("--- test GetNot\n");
        DataArrayNerr1d* da1d = new DataArrayNerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1.0);
        da1d->SetValElm(1, 1.0);
        da1d->SetValElm(2, 0.0);
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        DataArrayTerr1d* da1d_new = new DataArrayTerr1d;
        DataArray1dOpe::GetNot(da1d, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayTerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( 0.0 == da1d_new->GetValElm(0) );
        assert( 0.0 == da1d_new->GetValElm(1) );
        assert( 1.0 == da1d_new->GetValElm(2) );
        assert( 0.0 == da1d_new->GetValTerrPlusElm(0) );
        assert( 0.0 == da1d_new->GetValTerrPlusElm(1) );
        assert( 0.0 == da1d_new->GetValTerrPlusElm(2) );
        assert( 0.0 == da1d_new->GetValTerrMinusElm(0) );
        assert( 0.0 == da1d_new->GetValTerrMinusElm(1) );
        assert( 0.0 == da1d_new->GetValTerrMinusElm(2) );
        
        delete da1d;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetScale(const DataArray1d* const data_array,
//                  double scale, double offset,
//                  DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetScale\n");
        DataArrayTerr1d* da1d = new DataArrayTerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1.0);
        da1d->SetValElm(1, 2.0);
        da1d->SetValElm(2, 3.0);
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        double scale = 2.0;
        double offset = 1.0;
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetScale(da1d, scale, offset, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( 3.0 == da1d_new->GetValElm(0) );
        assert( 5.0 == da1d_new->GetValElm(1) );
        assert( 7.0 == da1d_new->GetValElm(2) );
        
        delete da1d;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetScale(const DataArray1d* const data_array,
//                  double scale, double offset,
//                  DataArraySerr1d* const data_array_out);    
    {
        printf("--- test GetScale\n");
        DataArray1d* da1d = new DataArrayTerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1.0);
        da1d->SetValElm(1, 2.0);
        da1d->SetValElm(2, 3.0);
        da1d->SetValTerrElm(0, 0.5);
        da1d->SetValTerrElm(1, 0.6);
        da1d->SetValTerrElm(2, 0.7);
        
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        double scale = 2.0;
        double offset = 1.0;
        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetScale(da1d, scale, offset, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( 3.0 == da1d_new->GetValElm(0) );
        assert( 5.0 == da1d_new->GetValElm(1) );
        assert( 7.0 == da1d_new->GetValElm(2) );
        assert( 0.5 * 2.0 == da1d_new->GetValSerrElm(0) );
        assert( 0.6 * 2.0 == da1d_new->GetValSerrElm(1) );
        assert( 0.7 * 2.0 == da1d_new->GetValSerrElm(2) );
        
        delete da1d;
        delete da1d_new;
        printf("=== \n");
    }

//   void GetScale(const DataArray1d* const data_array,
//                  double scale, double offset,
//                  DataArrayTerr1d* const data_array_out);
    {
        printf("--- test GetScale\n");
        DataArrayTerr1d* da1d = new DataArrayTerr1d;
        da1d->Init(3);
        da1d->SetValElm(0, 1.0);
        da1d->SetValElm(1, 2.0);
        da1d->SetValElm(2, 3.0);
        da1d->SetValTerrElm(0, 0.5);
        da1d->SetValTerrElm(1, 0.6);
        da1d->SetValTerrElm(2, 0.7);
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        double scale = 2.0;
        double offset = 1.0;
        DataArrayTerr1d* da1d_new = new DataArrayTerr1d;
        DataArray1dOpe::GetScale(da1d, scale, offset, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayTerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( 3.0 == da1d_new->GetValElm(0) );
        assert( 5.0 == da1d_new->GetValElm(1) );
        assert( 7.0 == da1d_new->GetValElm(2) );
        assert( 0.5 * 2.0 == da1d_new->GetValTerrPlusElm(0) );
        assert( 0.6 * 2.0 == da1d_new->GetValTerrPlusElm(1) );
        assert( 0.7 * 2.0 == da1d_new->GetValTerrPlusElm(2) );
        assert( -0.5 * 2.0 == da1d_new->GetValTerrMinusElm(0) );
        assert( -0.6 * 2.0 == da1d_new->GetValTerrMinusElm(1) );
        assert( -0.7 * 2.0 == da1d_new->GetValTerrMinusElm(2) );
        
        delete da1d;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetMin(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArrayNerr1d* const data_array_out);

    {
        printf("--- test GetMin\n");
        DataArray1d* da1d_1 = new DataArrayNerr1d;
        DataArray1d* da1d_2 = new DataArrayNerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 1.0);
        da1d_1->SetValElm(1, 2.0);
        da1d_1->SetValElm(2, 3.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetMin(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( -1.0 == da1d_new->GetValElm(0) );
        assert( -2.0 == da1d_new->GetValElm(1) );
        assert( -3.0 == da1d_new->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }

//        void GetMin(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetMin\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 1.0);
        da1d_1->SetValElm(1, 2.0);
        da1d_1->SetValElm(2, 3.0);
        da1d_1->SetValSerrElm(0, 0.5);
        da1d_1->SetValSerrElm(1, 0.6);
        da1d_1->SetValSerrElm(2, 0.7);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->SetValSerrElm(0, 0.5);
        da1d_2->SetValSerrElm(1, 0.6);
        da1d_2->SetValSerrElm(2, 0.7);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetMin(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( -1.0 == da1d_new->GetValElm(0) );
        assert( -2.0 == da1d_new->GetValElm(1) );
        assert( -3.0 == da1d_new->GetValElm(2) );
        assert( 0.5 == da1d_new->GetValSerrElm(0) );
        assert( 0.6 == da1d_new->GetValSerrElm(1) );
        assert( 0.7 == da1d_new->GetValSerrElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetMin(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArrayTerr1d* const data_array_out);
    {
        printf("--- test GetMin\n");
        DataArray1d* da1d_1 = new DataArrayTerr1d;
        DataArray1d* da1d_2 = new DataArrayTerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 1.0);
        da1d_1->SetValElm(1, 2.0);
        da1d_1->SetValElm(2, 3.0);
        da1d_1->SetValTerrElm(0, 0.5);
        da1d_1->SetValTerrElm(1, 0.6);
        da1d_1->SetValTerrElm(2, 0.7);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->SetValTerrElm(0, 0.5);
        da1d_2->SetValTerrElm(1, 0.6);
        da1d_2->SetValTerrElm(2, 0.7);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayTerr1d* da1d_new = new DataArrayTerr1d;
        DataArray1dOpe::GetMin(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayTerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( -1.0 == da1d_new->GetValElm(0) );
        assert( -2.0 == da1d_new->GetValElm(1) );
        assert( -3.0 == da1d_new->GetValElm(2) );
        assert( 0.5 == da1d_new->GetValTerrPlusElm(0) );
        assert( 0.6 == da1d_new->GetValTerrPlusElm(1) );
        assert( 0.7 == da1d_new->GetValTerrPlusElm(2) );
        assert( -0.5 == da1d_new->GetValTerrMinusElm(0) );
        assert( -0.6 == da1d_new->GetValTerrMinusElm(1) );
        assert( -0.7 == da1d_new->GetValTerrMinusElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }
    
//   void GetMax(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetMax\n");
        DataArray1d* da1d_1 = new DataArrayNerr1d;
        DataArray1d* da1d_2 = new DataArrayNerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 1.0);
        da1d_1->SetValElm(1, 2.0);
        da1d_1->SetValElm(2, 3.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetMax(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( 1.0 == da1d_new->GetValElm(0) );
        assert( 2.0 == da1d_new->GetValElm(1) );
        assert( 3.0 == da1d_new->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }
    
//    void GetMax(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetMax\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 1.0);
        da1d_1->SetValElm(1, 2.0);
        da1d_1->SetValElm(2, 3.0);
        da1d_1->SetValSerrElm(0, 0.1);
        da1d_1->SetValSerrElm(1, 0.2);
        da1d_1->SetValSerrElm(2, 0.3);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->SetValSerrElm(0, 0.4);
        da1d_2->SetValSerrElm(1, 0.5);
        da1d_2->SetValSerrElm(2, 0.6);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetMax(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );        
        assert( 1.0 == da1d_new->GetValElm(0) );
        assert( 2.0 == da1d_new->GetValElm(1) );
        assert( 3.0 == da1d_new->GetValElm(2) );
        assert( 0.1 == da1d_new->GetValSerrElm(0) );
        assert( 0.2 == da1d_new->GetValSerrElm(1) );
        assert( 0.3 == da1d_new->GetValSerrElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }
//    void GetMax(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArrayTerr1d* const data_array_out);
    {
        printf("--- test GetMax\n");
        DataArray1d* da1d_1 = new DataArrayTerr1d;
        DataArray1d* da1d_2 = new DataArrayTerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 1.0);
        da1d_1->SetValElm(1, 2.0);
        da1d_1->SetValElm(2, 3.0);
        da1d_1->SetValTerrPlusElm(0, 0.1);
        da1d_1->SetValTerrPlusElm(1, 0.2);
        da1d_1->SetValTerrPlusElm(2, 0.3);
        da1d_1->SetValTerrMinusElm(0, -0.15);
        da1d_1->SetValTerrMinusElm(1, -0.25);
        da1d_1->SetValTerrMinusElm(2, -0.35);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->SetValTerrPlusElm(0, 0.5);
        da1d_2->SetValTerrPlusElm(1, 0.6);
        da1d_2->SetValTerrPlusElm(2, 0.7);
        da1d_2->SetValTerrMinusElm(0, -0.55);
        da1d_2->SetValTerrMinusElm(1, -0.65);
        da1d_2->SetValTerrMinusElm(2, -0.75);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayTerr1d* da1d_new = new DataArrayTerr1d;
        DataArray1dOpe::GetMax(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayTerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                
        assert( 1.0 == da1d_new->GetValElm(0) );
        assert( 2.0 == da1d_new->GetValElm(1) );
        assert( 3.0 == da1d_new->GetValElm(2) );
        assert( 0.1 == da1d_new->GetValTerrPlusElm(0) );
        assert( 0.2 == da1d_new->GetValTerrPlusElm(1) );
        assert( 0.3 == da1d_new->GetValTerrPlusElm(2) );
        assert( -0.15 == da1d_new->GetValTerrMinusElm(0) );
        assert( -0.25 == da1d_new->GetValTerrMinusElm(1) );
        assert( -0.35 == da1d_new->GetValTerrMinusElm(2) );        
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetAdd(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetAdd\n");
        DataArray1d* da1d_1 = new DataArrayNerr1d;
        DataArray1d* da1d_2 = new DataArrayNerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetAdd(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( 4.0 == da1d_new->GetValElm(0) );
        assert( 4.0 == da1d_new->GetValElm(1) );
        assert( 4.0 == da1d_new->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }
    
//    void GetAdd(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetAdd\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->SetValSerrElm(0, 0.1);
        da1d_1->SetValSerrElm(1, 0.2);
        da1d_1->SetValSerrElm(2, 0.3);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -3.0);
        da1d_2->SetValElm(1, -6.0);
        da1d_2->SetValElm(2, -9.0);
        da1d_2->SetValSerrElm(0, 0.4);
        da1d_2->SetValSerrElm(1, 0.5);
        da1d_2->SetValSerrElm(2, 0.6);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetAdd(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);


        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( 2.0 == da1d_new->GetValElm(0) );
        assert( 0.0 == da1d_new->GetValElm(1) );
        assert( -2.0 == da1d_new->GetValElm(2) );
        assert( sqrt( pow(0.1,2) + pow(0.4,2) ) == da1d_new->GetValSerrElm(0) );
        assert( sqrt( pow(0.2,2) + pow(0.5,2) ) == da1d_new->GetValSerrElm(1) );
        assert( sqrt( pow(0.3,2) + pow(0.6,2) ) == da1d_new->GetValSerrElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }

//   void GetSub(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetSub\n");
        DataArray1d* da1d_1 = new DataArrayNerr1d;
        DataArray1d* da1d_2 = new DataArrayNerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetSub(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );        
        assert( 6.0 == da1d_new->GetValElm(0) );
        assert( 8.0 == da1d_new->GetValElm(1) );
        assert( 10.0 == da1d_new->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }

//   void GetSub(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetSub\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->SetValSerrElm(0, 0.1);
        da1d_1->SetValSerrElm(1, 0.2);
        da1d_1->SetValSerrElm(2, 0.3);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -3.0);
        da1d_2->SetValElm(1, -6.0);
        da1d_2->SetValElm(2, -9.0);
        da1d_2->SetValSerrElm(0, 0.4);
        da1d_2->SetValSerrElm(1, 0.5);
        da1d_2->SetValSerrElm(2, 0.6);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetSub(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );        
        assert( 8.0 == da1d_new->GetValElm(0) );
        assert( 12.0 == da1d_new->GetValElm(1) );
        assert( 16.0 == da1d_new->GetValElm(2) );
        assert( sqrt( pow(0.1,2) + pow(0.4,2) ) == da1d_new->GetValSerrElm(0) );
        assert( sqrt( pow(0.2,2) + pow(0.5,2) ) == da1d_new->GetValSerrElm(1) );
        assert( sqrt( pow(0.3,2) + pow(0.6,2) ) == da1d_new->GetValSerrElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetMul(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetMul\n");
        DataArray1d* da1d_1 = new DataArrayNerr1d;
        DataArray1d* da1d_2 = new DataArrayNerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetMul(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                
        assert( 5.0 * (-1.0) == da1d_new->GetValElm(0) );
        assert( 6.0 * (-2.0) == da1d_new->GetValElm(1) );
        assert( 7.0 * (-3.0) == da1d_new->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }
//    void GetMul(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetMul\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->SetValSerrElm(0, 0.1);
        da1d_1->SetValSerrElm(1, 0.2);
        da1d_1->SetValSerrElm(2, 0.3);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -3.0);
        da1d_2->SetValElm(1, -6.0);
        da1d_2->SetValElm(2, -9.0);
        da1d_2->SetValSerrElm(0, 0.4);
        da1d_2->SetValSerrElm(1, 0.5);
        da1d_2->SetValSerrElm(2, 0.6);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetMul(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                    
        assert( 5.0 * (-3.0) == da1d_new->GetValElm(0) );
        assert( 6.0 * (-6.0) == da1d_new->GetValElm(1) );
        assert( 7.0 * (-9.0) == da1d_new->GetValElm(2) );
        assert( sqrt( pow(5.0 * 0.4, 2) + pow( -3.0 * 0.1, 2) ) == da1d_new->GetValSerrElm(0) );
        assert( sqrt( pow(6.0 * 0.5, 2) + pow( -6.0 * 0.2, 2) ) == da1d_new->GetValSerrElm(1) );
        assert( sqrt( pow(7.0 * 0.6, 2) + pow( -9.0 * 0.3, 2) ) == da1d_new->GetValSerrElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }

//    int GetDiv(const DataArray1d* const data_array_num,
//               const DataArray1d* const data_array_den,
//               DataArrayNerr1d* const mask_sel_array_out,
//               DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetDiv\n");
        DataArray1d* da1d_1 = new DataArrayNerr1d;
        DataArray1d* da1d_2 = new DataArrayNerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
        int ret = DataArray1dOpe::GetDiv(da1d_1, da1d_2, da1d_mask, da1d_new);
        printf("ret = %d\n", ret);        
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        da1d_mask->PrintInfo(stdout);
        da1d_mask->PrintData(stdout, 1, 0.0);

        
        assert( kRetNormal == ret );
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                    
        assert( 5.0 / (-1.0) == da1d_new->GetValElm(0) );
        assert( 6.0 / (-2.0) == da1d_new->GetValElm(1) );
        assert( 7.0 / (-3.0) == da1d_new->GetValElm(2) );
        assert( 1 == da1d_mask->GetValElm(0) );
        assert( 1 == da1d_mask->GetValElm(1) );
        assert( 1 == da1d_mask->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        delete da1d_mask;
        printf("=== \n");
    }

    {
        printf("--- test GetDiv\n");
        DataArray1d* da1d_1 = new DataArrayNerr1d;
        DataArray1d* da1d_2 = new DataArrayNerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0,  0.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
        int ret = DataArray1dOpe::GetDiv(da1d_1, da1d_2, da1d_mask, da1d_new);
        printf("ret = %d\n", ret);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        da1d_mask->PrintInfo(stdout);
        da1d_mask->PrintData(stdout, 1, 0.0);
        
        assert( kRetError == ret );
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                    
        assert( 0.0 == da1d_new->GetValElm(0) );
        assert( 6.0 / (-2.0) == da1d_new->GetValElm(1) );
        assert( 7.0 / (-3.0) == da1d_new->GetValElm(2) );        
        assert( 0 == da1d_mask->GetValElm(0) );
        assert( 1 == da1d_mask->GetValElm(1) );
        assert( 1 == da1d_mask->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        delete da1d_mask;
        printf("=== \n");
    }
    
//    int GetDiv(const DataArray1d* const data_array_num,
//               const DataArray1d* const data_array_den,
//               DataArrayNerr1d* const mask_sel_array_out,
//               DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetDiv\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->SetValSerrElm(0, 0.1);
        da1d_1->SetValSerrElm(1, 0.2);
        da1d_1->SetValSerrElm(2, 0.3);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -3.0);
        da1d_2->SetValElm(1, -6.0);
        da1d_2->SetValElm(2, -9.0);
        da1d_2->SetValSerrElm(0, 0.4);
        da1d_2->SetValSerrElm(1, 0.5);
        da1d_2->SetValSerrElm(2, 0.6);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
        int ret = DataArray1dOpe::GetDiv(da1d_1, da1d_2, da1d_mask, da1d_new);
        printf("ret = %d\n", ret);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        da1d_mask->PrintInfo(stdout);
        da1d_mask->PrintData(stdout, 1, 0.0);        

        assert( kRetNormal == ret );
        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                    
        assert( 5.0 / (-3.0) == da1d_new->GetValElm(0) );
        assert( 6.0 / (-6.0) == da1d_new->GetValElm(1) );
        assert( 7.0 / (-9.0) == da1d_new->GetValElm(2) );
        assert( sqrt( pow(5.0 * 0.4, 2) + pow( -3.0 * 0.1, 2) ) / pow(-3.0, 2)
                == da1d_new->GetValSerrElm(0) );
        assert( sqrt( pow(6.0 * 0.5, 2) + pow( -6.0 * 0.2, 2) ) / pow(-6.0, 2)
                == da1d_new->GetValSerrElm(1) );
        assert( sqrt( pow(7.0 * 0.6, 2) + pow( -9.0 * 0.3, 2) ) / pow(-9.0, 2)
                == da1d_new->GetValSerrElm(2) );
        assert( 1 == da1d_mask->GetValElm(0) );
        assert( 1 == da1d_mask->GetValElm(1) );
        assert( 1 == da1d_mask->GetValElm(2) );        
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        delete da1d_mask;
        printf("=== \n");
    }
    
    {
        printf("--- test GetDiv\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->SetValSerrElm(0, 0.1);
        da1d_1->SetValSerrElm(1, 0.2);
        da1d_1->SetValSerrElm(2, 0.3);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, 0.0);
        da1d_2->SetValElm(1, -6.0);
        da1d_2->SetValElm(2, -9.0);
        da1d_2->SetValSerrElm(0, 0.4);
        da1d_2->SetValSerrElm(1, 0.5);
        da1d_2->SetValSerrElm(2, 0.6);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
        int ret = DataArray1dOpe::GetDiv(da1d_1, da1d_2, da1d_mask, da1d_new);
        printf("ret = %d\n", ret);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        da1d_mask->PrintInfo(stdout);
        da1d_mask->PrintData(stdout, 1, 0.0);        

        assert( kRetError == ret );
        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                    
        assert( 0.0 == da1d_new->GetValElm(0) );
        assert( 6.0 / (-6.0) == da1d_new->GetValElm(1) );
        assert( 7.0 / (-9.0) == da1d_new->GetValElm(2) );
        assert( 0.0 == da1d_new->GetValSerrElm(0) );
        assert( sqrt( pow(6.0 * 0.5, 2) + pow( -6.0 * 0.2, 2) ) / pow(-6.0, 2)
                == da1d_new->GetValSerrElm(1) );
        assert( sqrt( pow(7.0 * 0.6, 2) + pow( -9.0 * 0.3, 2) ) / pow(-9.0, 2)
                == da1d_new->GetValSerrElm(2) );
        assert( 0 == da1d_mask->GetValElm(0) );
        assert( 1 == da1d_mask->GetValElm(1) );
        assert( 1 == da1d_mask->GetValElm(2) );        
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        delete da1d_mask;
        printf("=== \n");
    }
    
//    void GetAMean(const DataArray1d* const data_array1,
//                  const DataArray1d* const data_array2,
//                  DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetAMean\n");
        DataArray1d* da1d_1 = new DataArrayNerr1d;
        DataArray1d* da1d_2 = new DataArrayNerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -3.0);
        da1d_2->SetValElm(2, -5.0);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetAMean(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                    
        assert( (5.0 -1.0)/2. == da1d_new->GetValElm(0) );
        assert( (6.0 -3.0)/2. == da1d_new->GetValElm(1) );
        assert( (7.0 -5.0)/2. == da1d_new->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }
    
//    void GetAMean(const DataArray1d* const data_array1,
//                  const DataArray1d* const data_array2,
//                  DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetAMean\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->SetValSerrElm(0, 0.1);
        da1d_1->SetValSerrElm(1, 0.2);
        da1d_1->SetValSerrElm(2, 0.3);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -3.0);
        da1d_2->SetValElm(1, -6.0);
        da1d_2->SetValElm(2, -9.0);
        da1d_2->SetValSerrElm(0, 0.4);
        da1d_2->SetValSerrElm(1, 0.5);
        da1d_2->SetValSerrElm(2, 0.6);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetAMean(da1d_1, da1d_2, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                    
        assert( (5.0 -3.0)/2. == da1d_new->GetValElm(0) );
        assert( (6.0 -6.0)/2. == da1d_new->GetValElm(1) );
        assert( (7.0 -9.0)/2. == da1d_new->GetValElm(2) );
        assert( sqrt( pow(0.1,2) + pow(0.4,2) )/2. == da1d_new->GetValSerrElm(0) );
        assert( sqrt( pow(0.2,2) + pow(0.5,2) )/2. == da1d_new->GetValSerrElm(1) );
        assert( sqrt( pow(0.3,2) + pow(0.6,2) )/2. == da1d_new->GetValSerrElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }
    
//    int GetWMean(const DataArray1d* const data_array1,
//                 const DataArray1d* const data_array2,
//                 DataArrayNerr1d* const mask_sel_array_out,
//                 DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetWMean\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->SetValSerrElm(0, 0.1);
        da1d_1->SetValSerrElm(1, 0.2);
        da1d_1->SetValSerrElm(2, 0.3);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -3.0);
        da1d_2->SetValElm(1, -6.0);
        da1d_2->SetValElm(2, -9.0);
        da1d_2->SetValSerrElm(0, 0.4);
        da1d_2->SetValSerrElm(1, 0.5);
        da1d_2->SetValSerrElm(2, 0.6);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;        
        int ret = DataArray1dOpe::GetWMean(da1d_1, da1d_2, da1d_mask, da1d_new);
        printf("ret = %d\n", ret);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        da1d_mask->PrintInfo(stdout);
        da1d_mask->PrintData(stdout, 1, 0.0);

        assert( kRetNormal == ret );
        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        
        double num = 5.0 / pow(0.1, 2) + (-3.0) / pow(0.4, 2);
        double den = 1.0 / pow(0.1, 2) + 1.0 / pow(0.4, 2);
        assert( num/den == da1d_new->GetValElm(0) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(0) );

        num = 6.0 / pow(0.2, 2) + (-6.0) / pow(0.5, 2);
        den = 1.0 / pow(0.2, 2) + 1.0 / pow(0.5, 2);
        assert( num/den == da1d_new->GetValElm(1) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(1) );

        num = 7.0 / pow(0.3, 2) + (-9.0) / pow(0.6, 2);
        den = 1.0 / pow(0.3, 2) + 1.0 / pow(0.6, 2);
        assert( num/den == da1d_new->GetValElm(2) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(2) );        

        assert( 1 == da1d_mask->GetValElm(0) );
        assert( 1 == da1d_mask->GetValElm(1) );
        assert( 1 == da1d_mask->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        delete da1d_mask;        
        printf("=== \n");
    }

    {
        printf("--- test GetWMean\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->SetValSerrElm(0, 0.0);
        da1d_1->SetValSerrElm(1, 0.2);
        da1d_1->SetValSerrElm(2, 0.3);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -3.0);
        da1d_2->SetValElm(1, -6.0);
        da1d_2->SetValElm(2, -9.0);
        da1d_2->SetValSerrElm(0, 0.4);
        da1d_2->SetValSerrElm(1, 0.5);
        da1d_2->SetValSerrElm(2, 0.6);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;        
        int ret = DataArray1dOpe::GetWMean(da1d_1, da1d_2, da1d_mask, da1d_new);
        printf("ret = %d\n", ret);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        da1d_mask->PrintInfo(stdout);
        da1d_mask->PrintData(stdout, 1, 0.0);

        assert( kRetError == ret );
        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                    
        double num = 0.0;
        double den = 0.0;
        assert( 0.0 == da1d_new->GetValElm(0) );
        assert( 0.0 == da1d_new->GetValSerrElm(0) );

        num = 6.0 / pow(0.2, 2) + (-6.0) / pow(0.5, 2);
        den = 1.0 / pow(0.2, 2) + 1.0 / pow(0.5, 2);
        assert( num/den == da1d_new->GetValElm(1) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(1) );

        num = 7.0 / pow(0.3, 2) + (-9.0) / pow(0.6, 2);
        den = 1.0 / pow(0.3, 2) + 1.0 / pow(0.6, 2);
        assert( num/den == da1d_new->GetValElm(2) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(2) );        

        assert( 0 == da1d_mask->GetValElm(0) );
        assert( 1 == da1d_mask->GetValElm(1) );
        assert( 1 == da1d_mask->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        delete da1d_mask;        
        printf("=== \n");
    }

//    int GetSubAddRatio(const DataArray1d* const data_array1,
//                       const DataArray1d* const data_array2,
//                       DataArrayNerr1d* const mask_sel_array_out,
//                       DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetSubAddRatio\n");
        DataArray1d* da1d_1 = new DataArrayNerr1d;
        DataArray1d* da1d_2 = new DataArrayNerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -3.0);
        da1d_2->SetValElm(1, -6.0);
        da1d_2->SetValElm(2, -9.0);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
        int ret = DataArray1dOpe::GetSubAddRatio(da1d_1, da1d_2, da1d_mask, da1d_new);
        printf("ret = %d\n", ret);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        da1d_mask->PrintInfo(stdout);
        da1d_mask->PrintData(stdout, 1, 0.0);

        assert( kRetError == ret );
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );                    
        assert( (5.0 - (-3.0))/(5.0 + (-3.0)) == da1d_new->GetValElm(0) );
        assert( 0.0 == da1d_new->GetValElm(1) );
        assert( (7.0 - (-9.0))/(7.0 + (-9.0)) == da1d_new->GetValElm(2) );
        assert( 1 == da1d_mask->GetValElm(0) );
        assert( 0 == da1d_mask->GetValElm(1) );
        assert( 1 == da1d_mask->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        delete da1d_mask;        
        printf("=== \n");
    }
   
//
//    int GetSubAddRatio(const DataArray1d* const data_array1,
//                       const DataArray1d* const data_array2,
//                       DataArrayNerr1d* const mask_sel_array_out,
//                       DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetSubAddRatio\n");
        DataArray1d* da1d_1 = new DataArraySerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 6.0);
        da1d_1->SetValElm(2, 7.0);
        da1d_1->SetValSerrElm(0, 0.1);
        da1d_1->SetValSerrElm(1, 0.3);
        da1d_1->SetValSerrElm(2, 0.5);        
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -3.0);
        da1d_2->SetValElm(1, -6.0);
        da1d_2->SetValElm(2, -9.0);
        da1d_2->SetValSerrElm(0, 0.2);
        da1d_2->SetValSerrElm(1, 0.4);
        da1d_2->SetValSerrElm(2, 0.6);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
        int ret = DataArray1dOpe::GetSubAddRatio(da1d_1, da1d_2, da1d_mask, da1d_new);
        printf("ret = %d\n", ret);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        da1d_mask->PrintInfo(stdout);
        da1d_mask->PrintData(stdout, 1, 0.0);

        assert( kRetError == ret );
        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( (5.0 - (-3.0))/(5.0 + (-3.0)) == da1d_new->GetValElm(0) );
        assert( 2 * sqrt( pow(-3.0 * 0.1, 2) +  pow(5.0 * 0.2, 2) ) / pow(5.0 + (-3.0), 2)
                == da1d_new->GetValSerrElm(0) );
        assert( 0.0 == da1d_new->GetValElm(1) );
        assert( 0.0 == da1d_new->GetValSerrElm(1) );
        assert( (7.0 - (-9.0))/(7.0 + (-9.0)) == da1d_new->GetValElm(2) );
        assert( 2 * sqrt( pow(-9.0 * 0.5, 2) +  pow(7.0 * 0.6, 2) ) / pow(7.0 + (-9.0), 2)
                == da1d_new->GetValSerrElm(2) );
        assert( 1 == da1d_mask->GetValElm(0) );
        assert( 0 == da1d_mask->GetValElm(1) );
        assert( 1 == da1d_mask->GetValElm(2) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        delete da1d_mask;        
        printf("=== \n");
    }

//    void GetMin(const DataArrayNerr1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayNerr1d* data_array_out);
    {
        printf("--- test GetMin\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetMin(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( -10.0 == da1d_new->GetValElm(0) );
        assert( -2.0 == da1d_new->GetValElm(1) );
        assert( -30.0 == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetMin(const DataArray1d* const* const data_array_arr,
//                int ndata_array,
//                DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetMin\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetMin(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( -10.0 == da1d_new->GetValElm(0) );
        assert(  -6.0 == da1d_new->GetValElm(1) );
        assert( -30.0 == da1d_new->GetValElm(2) );
        assert( (0.4 - (-1.0))/2. == da1d_new->GetValSerrElm(0) );
        assert( 0.2 == da1d_new->GetValSerrElm(1) );
        assert( (0.6 - (-5.0))/2. == da1d_new->GetValSerrElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetMin(const DataArray1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayTerr1d* const data_array_out);
    {
        printf("--- test GetMin\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayTerr1d* da1d_new = new DataArrayTerr1d;
        DataArray1dOpe::GetMin(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayTerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( -10.0 == da1d_new->GetValElm(0) );
        assert(  -6.0 == da1d_new->GetValElm(1) );
        assert( -30.0 == da1d_new->GetValElm(2) );
        assert( 0.4 == da1d_new->GetValTerrPlusElm(0) );
        assert( 0.2 == da1d_new->GetValTerrPlusElm(1) );
        assert( 0.6 == da1d_new->GetValTerrPlusElm(2) );
        assert( -1.0 == da1d_new->GetValTerrMinusElm(0) );
        assert( -0.2 == da1d_new->GetValTerrMinusElm(1) );
        assert( -5.0 == da1d_new->GetValTerrMinusElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetMax(const DataArray1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayNerr1d* const data_array_out);    
    {
        printf("--- test GetMax\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetMax(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( 1.0 == da1d_new->GetValElm(0) );
        assert( 20.0 == da1d_new->GetValElm(1) );
        assert( 3.0 == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetMax(const DataArray1d* const* const data_array_arr,
//                int ndata_array,
//                DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetMax\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetMax(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( 5.0  == da1d_new->GetValElm(0) );
        assert( 20.0 == da1d_new->GetValElm(1) );
        assert(  7.0 == da1d_new->GetValElm(2) );
        assert( 0.1 == da1d_new->GetValSerrElm(0) );
        assert( (0.5 - (-3.0))/2. == da1d_new->GetValSerrElm(1) );
        assert( 0.3 == da1d_new->GetValSerrElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetMax(const DataArray1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayTerr1d* const data_array_out);    
    {
        printf("--- test GetMax\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayTerr1d* da1d_new = new DataArrayTerr1d;
        DataArray1dOpe::GetMax(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayTerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( 5.0 == da1d_new->GetValElm(0) );
        assert( 20.0 == da1d_new->GetValElm(1) );
        assert( 7.0 == da1d_new->GetValElm(2) );
        assert( 0.1 == da1d_new->GetValTerrPlusElm(0) );
        assert( 0.5 == da1d_new->GetValTerrPlusElm(1) );
        assert( 0.3 == da1d_new->GetValTerrPlusElm(2) );
        assert( -0.1 == da1d_new->GetValTerrMinusElm(0) );
        assert( -3.0 == da1d_new->GetValTerrMinusElm(1) );
        assert( -0.3 == da1d_new->GetValTerrMinusElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }


//    void GetSum(const DataArray1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetSum\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetSum(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( 1.0 + 1.0 + (-10.0) == da1d_new->GetValElm(0) );
        assert( -2.0 + (-2.0) + 20.0 == da1d_new->GetValElm(1) );
        assert( 3.0 + 3.0 + (-30.0) == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetSum(const DataArray1d* const* const data_array_arr,
//                int ndata_array,
//                DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetSum\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetSum(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( 1.0 + 5.0 + (-10.0) == da1d_new->GetValElm(0) );
        assert( -2.0 + (-6.0) + 20.0 == da1d_new->GetValElm(1) );
        assert( 3.0 + 7.0 + (-30.0) == da1d_new->GetValElm(2) );
        assert( sqrt( pow(0.0, 2) + pow(0.1, 2) + pow((0.4 - (-1.0))/2., 2) )
                == da1d_new->GetValSerrElm(0) );
        assert( sqrt( pow(0.0, 2) + pow(0.2, 2) + pow((0.5 - (-3.0))/2., 2) )
                == da1d_new->GetValSerrElm(1) );
        assert( sqrt( pow(0.0, 2) + pow(0.3, 2) + pow((0.6 - (-5.0))/2., 2) )
                == da1d_new->GetValSerrElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }


//    void GetAMean(const DataArray1d* const* const data_array_arr,
//                  int ndata_array,
//                  DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetAMean\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetAMean(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( (1.0 + 1.0 + (-10.0))/3. == da1d_new->GetValElm(0) );
        assert( (-2.0 + (-2.0) + 20.0)/3. == da1d_new->GetValElm(1) );
        assert( (3.0 + 3.0 + (-30.0))/3. == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    
//    void GetAMean(const DataArray1d* const* const data_array_arr,
//                  int ndata_array,
//                  DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetAMean\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetAMean(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );            
        assert( (1.0 + 5.0 + (-10.0))/3. == da1d_new->GetValElm(0) );
        assert( (-2.0 + (-6.0) + 20.0)/3. == da1d_new->GetValElm(1) );
        assert( (3.0 + 7.0 + (-30.0))/3. == da1d_new->GetValElm(2) );
        assert( (sqrt( pow(0.0, 2) + pow(0.1, 2) + pow((0.4 - (-1.0))/2., 2) ))/3.
                == da1d_new->GetValSerrElm(0) );
        assert( (sqrt( pow(0.0, 2) + pow(0.2, 2) + pow((0.5 - (-3.0))/2., 2) ))/3.
                == da1d_new->GetValSerrElm(1) );
        assert( (sqrt( pow(0.0, 2) + pow(0.3, 2) + pow((0.6 - (-5.0))/2., 2) ))/3.
                == da1d_new->GetValSerrElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }


//    int GetWMean(const DataArray1d* const* const data_array_arr,
//                 int ndata_array,
//                 DataArrayNerr1d* const mask_sel_array_out,
//                 DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetWMean\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
        DataArray1dOpe::GetWMean(da1d_arr, narr, da1d_mask, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        da1d_mask->PrintInfo(stdout);
        da1d_mask->PrintData(stdout, 1, 0.0);
        
        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        double num = 5.0 / pow(0.1, 2) + (-10.0) / pow( (0.4 - (-1.0))/2., 2);
        double den = 1.0 / pow(0.1, 2) + 1.0 / pow((0.4 - (-1.0))/2., 2);
        assert( num / den == da1d_new->GetValElm(0) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(0) );

        num = -6.0/ pow(0.2, 2) + 20.0 / pow( (0.5 - (-3.0))/2., 2);
        den = 1.0 / pow(0.2, 2) + 1.0 / pow( (0.5 - (-3.0))/2., 2);
        assert( num / den == da1d_new->GetValElm(1) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(1) );

        num = 7.0/ pow(0.3, 2) + -30.0 / pow( (0.6 - (-5.0))/2., 2);
        den = 1.0 / pow(0.3, 2) + 1.0 / pow( (0.6 - (-5.0))/2., 2);
        assert( num / den == da1d_new->GetValElm(2) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(2) );

        assert( "DataArrayNerr1d" == da1d_mask->GetClassName() );
        assert( 3 == da1d_mask->GetNdata() );
        assert( 0 == da1d_mask->GetFlagValSorted() );
        assert( 0 == da1d_mask->GetValElm(0) );
        assert( 0 == da1d_mask->GetValElm(1) );
        assert( 0 == da1d_mask->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    
//       void GetVariance(const DataArray1d* const* const data_array_arr,
//                     int ndata_array,
//                     DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetVariance\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetVariance(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        double sum  = 1.0 + 5.0 + (-10.0);
        double sum2 = pow(1.0,2) + pow(5.0,2) + pow(-10.0,2);
        double variance = ( sum2 - pow(sum, 2) / 3. ) / 3.;
        assert( variance == da1d_new->GetValElm(0) );

        sum  = -2.0 + (-6.0) + 20.0;
        sum2 = pow(-2.0,2) + pow(-6.0,2) + pow(20.0,2);
        variance = ( sum2 - pow(sum, 2) / 3. ) / 3.;
        assert( variance == da1d_new->GetValElm(1) );

        sum  = 3.0 + 7.0 + (-30.0);
        sum2 = pow(3.0,2) + pow(7.0,2) + pow(-30.0,2);
        variance = ( sum2 - pow(sum, 2) / 3. ) / 3.;
        assert( variance == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    
//        void GetStddev(const DataArray1d* const* const data_array_arr,
//                   int ndata_array,
//                   DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetStddev\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetStddev(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        double sum  = 1.0 + 5.0 + (-10.0);
        double sum2 = pow(1.0,2) + pow(5.0,2) + pow(-10.0,2);
        double variance = ( sum2 - pow(sum, 2) / 3. ) / 3.;
        double stddev = sqrt(variance);
        assert( stddev == da1d_new->GetValElm(0) );

        sum  = -2.0 + (-6.0) + 20.0;
        sum2 = pow(-2.0,2) + pow(-6.0,2) + pow(20.0,2);
        variance = ( sum2 - pow(sum, 2) / 3. ) / 3.;
        stddev = sqrt(variance);
        assert( stddev == da1d_new->GetValElm(1) );

        sum  = 3.0 + 7.0 + (-30.0);
        sum2 = pow(3.0,2) + pow(7.0,2) + pow(-30.0,2);
        variance = ( sum2 - pow(sum, 2) / 3. ) / 3.;
        stddev = sqrt(variance);
        assert( stddev == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    
//        void GetUnbiasedVariance(const DataArray1d* const* const data_array_arr,
//                                 int ndata_array,
//                                 DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetUnbiasedVariance\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetUnbiasedVariance(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        double sum  = 1.0 + 5.0 + (-10.0);
        double sum2 = pow(1.0,2) + pow(5.0,2) + pow(-10.0,2);
        double unbiased_variance = ( sum2 - pow(sum, 2) / 3. ) / 2.;
        assert( unbiased_variance == da1d_new->GetValElm(0) );

        sum  = -2.0 + (-6.0) + 20.0;
        sum2 = pow(-2.0,2) + pow(-6.0,2) + pow(20.0,2);
        unbiased_variance = ( sum2 - pow(sum, 2) / 3. ) / 2.;
        assert( unbiased_variance == da1d_new->GetValElm(1) );

        sum  = 3.0 + 7.0 + (-30.0);
        sum2 = pow(3.0,2) + pow(7.0,2) + pow(-30.0,2);
        unbiased_variance = ( sum2 - pow(sum, 2) / 3. ) / 2.;
        assert( unbiased_variance == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    

//   void GetSqrtOfUnbiasedVariance(const DataArray1d* const* const data_array_arr,
//                                   int ndata_array,
//                                   DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetSqrtOfUnbiasedVariance\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetSqrtOfUnbiasedVariance(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        double sum  = 1.0 + 5.0 + (-10.0);
        double sum2 = pow(1.0,2) + pow(5.0,2) + pow(-10.0,2);
        double unbiased_variance = ( sum2 - pow(sum, 2) / 3. ) / 2.;
        double sqrt_of_unbiased_variance = sqrt(unbiased_variance);
        assert( sqrt_of_unbiased_variance == da1d_new->GetValElm(0) );

        sum  = -2.0 + (-6.0) + 20.0;
        sum2 = pow(-2.0,2) + pow(-6.0,2) + pow(20.0,2);
        unbiased_variance = ( sum2 - pow(sum, 2) / 3. ) / 2.;
        sqrt_of_unbiased_variance = sqrt(unbiased_variance);
        assert( sqrt_of_unbiased_variance == da1d_new->GetValElm(1) );

        sum  = 3.0 + 7.0 + (-30.0);
        sum2 = pow(3.0,2) + pow(7.0,2) + pow(-30.0,2);
        unbiased_variance = ( sum2 - pow(sum, 2) / 3. ) / 2.;
        sqrt_of_unbiased_variance = sqrt(unbiased_variance);
        assert( sqrt_of_unbiased_variance == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    
//   void GetRMS(const DataArray1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetRMS\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetRMS(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        double sum2 = pow(1.0,2) + pow(5.0,2) + pow(-10.0,2);
        double rms = sqrt(sum2 / 3.);
        assert( rms == da1d_new->GetValElm(0) );

        sum2 = pow(-2.0,2) + pow(-6.0,2) + pow(20.0,2);
        rms = sqrt(sum2 / 3.);
        assert( rms == da1d_new->GetValElm(1) );

        sum2 = pow(3.0,2) + pow(7.0,2) + pow(-30.0,2);
        rms = sqrt(sum2 / 3.);
        assert( rms == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    
//   void GetMedian(const DataArray1d* const* const data_array_arr,
//                   int ndata_array,
//                   DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetMedian\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetMedian(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        assert( 1.0 == da1d_new->GetValElm(0) );
        assert( -2.0 == da1d_new->GetValElm(1) );
        assert( 3.0 == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    

//    void GetSumWithMask(const DataArray1d* const* const data_array_arr,
//                        const DataArray1d* const* const mask_array_arr,
//                        int ndata_array,
//                        DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetSumWithMask\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        

        DataArray1d** da1d_mask_arr = new DataArray1d* [narr];

        iarr = 0;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 0.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 0.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 1.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetSumWithMask(da1d_arr, da1d_mask_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        assert( 1.0 + 5.0 + (-10.0) == da1d_new->GetValElm(0) );
        assert( -2.0 -6.0 + 20.0 == da1d_new->GetValElm(1) );
        assert( -30.0 == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    
//        void GetSumWithMask(const DataArray1d* const* const data_array_arr,
//                        const DataArray1d* const* const mask_array_arr,
//                        int ndata_array,
//                        DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetSumWithMask\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        

        DataArray1d** da1d_mask_arr = new DataArray1d* [narr];

        iarr = 0;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 0.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 0.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 1.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetSumWithMask(da1d_arr, da1d_mask_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        
        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        assert( 1.0 + 5.0 + (-10.0) == da1d_new->GetValElm(0) );
        assert( -2.0 -6.0 + 20.0 == da1d_new->GetValElm(1) );
        assert( -30.0 == da1d_new->GetValElm(2) );
        assert( sqrt( pow(0.1,2) + pow( (0.4 - (-1.0))/2., 2) ) == da1d_new->GetValSerrElm(0) );
        assert( sqrt( pow(0.2,2) + pow( (0.5 - (-3.0))/2., 2) ) == da1d_new->GetValSerrElm(1) );
        assert( (0.6 - (-5.0))/2. == da1d_new->GetValSerrElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    
//   void GetAMeanWithMask(const DataArray1d* const* const data_array_arr,
//                          const DataArray1d* const* const mask_array_arr,
//                          int ndata_array,
//                          DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetAMeanWithMask\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        

        DataArray1d** da1d_mask_arr = new DataArray1d* [narr];

        iarr = 0;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 0.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 0.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 1.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetAMeanWithMask(da1d_arr, da1d_mask_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        
        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        assert( (1.0 + 5.0 + (-10.0))/3. == da1d_new->GetValElm(0) );
        assert( (-2.0 -6.0 + 20.0)/3. == da1d_new->GetValElm(1) );
        assert( -30.0 == da1d_new->GetValElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }

//    void GetAMeanWithMask(const DataArray1d* const* const data_array_arr,
//                          const DataArray1d* const* const mask_array_arr,
//                          int ndata_array,
//                          DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetAMeanWithMask\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        

        DataArray1d** da1d_mask_arr = new DataArray1d* [narr];

        iarr = 0;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 0.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 0.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 1.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetAMeanWithMask(da1d_arr, da1d_mask_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        
        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        assert( (1.0 + 5.0 + (-10.0))/3. == da1d_new->GetValElm(0) );
        assert( (-2.0 -6.0 + 20.0)/3. == da1d_new->GetValElm(1) );
        assert( -30.0 == da1d_new->GetValElm(2) );
        assert( sqrt( pow(0.1,2) + pow( (0.4 - (-1.0))/2., 2) )/3. == da1d_new->GetValSerrElm(0) );
        assert( sqrt( pow(0.2,2) + pow( (0.5 - (-3.0))/2., 2) )/3. == da1d_new->GetValSerrElm(1) );
        assert( (0.6 - (-5.0))/2. == da1d_new->GetValSerrElm(2) );

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }

//    int GetWMeanWithMask(const DataArray1d* const* const data_array_arr,
//                         const DataArray1d* const* const mask_array_arr,
//                         int ndata_array,
//                         DataArrayNerr1d* const mask_sel_array_out,
//                         DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetWMeanWithMask\n");
        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];

        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        

        DataArray1d** da1d_mask_arr = new DataArray1d* [narr];

        iarr = 0;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 0.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 0.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_mask_arr[iarr] = new DataArrayNerr1d;
        da1d_mask_arr[iarr]->Init(3);
        da1d_mask_arr[iarr]->SetValElm(0, 1.0);
        da1d_mask_arr[iarr]->SetValElm(1, 1.0);
        da1d_mask_arr[iarr]->SetValElm(2, 1.0);
        da1d_mask_arr[iarr]->PrintInfo(stdout);
        da1d_mask_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArrayNerr1d* da1d_mask_sel = new DataArrayNerr1d;
        DataArray1dOpe::GetWMeanWithMask(da1d_arr, da1d_mask_arr, narr, da1d_mask_sel, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);
        da1d_mask_sel->PrintInfo(stdout);
        da1d_mask_sel->PrintData(stdout, 1, 0.0);
        
        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 3 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );

        double num = 5.0/pow(0.1,2) + (-10.0)/pow( (0.4 - (-1.0))/2., 2);
        double den = 1.0/pow(0.1,2) + 1.0/pow( (0.4 - (-1.0))/2., 2);
        assert( num / den == da1d_new->GetValElm(0) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(0) );

        num = -6.0/pow(0.2,2) + 20.0/pow( (0.5 - (-3.0))/2., 2);
        den = 1.0/pow(0.2,2) + 1.0/pow( (0.5 - (-3.0))/2., 2);
        assert( num / den == da1d_new->GetValElm(1) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(1) );

        num = -30.0/pow( (0.6 - (-5.0))/2., 2);
        den = 1.0/pow( (0.6 - (-5.0))/2., 2);
        assert( num / den == da1d_new->GetValElm(2) );
        assert( sqrt( 1. / den) == da1d_new->GetValSerrElm(2) );

        assert( "DataArrayNerr1d" == da1d_mask_sel->GetClassName() );
        assert( 3 == da1d_mask_sel->GetNdata() );
        assert( 0 == da1d_mask_sel->GetFlagValSorted() );
        assert( 0 == da1d_mask_sel->GetValElm(0) );
        assert( 0 == da1d_mask_sel->GetValElm(1) );
        assert( 1 == da1d_mask_sel->GetValElm(2) );
        
        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }

//     int IsFormatSame(const DataArray1d* const data_array1,
//                      const DataArray1d* const data_array2);
    {
        printf("--- test IsFormatSame\n");
        DataArray1d* da1d_1 = new DataArrayNerr1d;
        DataArray1d* da1d_2 = new DataArraySerr1d;
        da1d_1->Init(3);
        da1d_1->SetValElm(0, 1.0);
        da1d_1->SetValElm(1, 2.0);
        da1d_1->SetValElm(2, 3.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_2->Init(3);
        da1d_2->SetValElm(0, -1.0);
        da1d_2->SetValElm(1, -2.0);
        da1d_2->SetValElm(2, -3.0);
        da1d_2->SetValSerrElm(0, 0.5);
        da1d_2->SetValSerrElm(1, 0.7);
        da1d_2->SetValSerrElm(2, 0.9);        
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        int ret = DataArray1dOpe::IsFormatSame(da1d_1, da1d_2);
        printf("ret = %d\n", ret);
        assert(1 == ret);
        
        delete da1d_1;
        delete da1d_2;
        printf("=== \n");
    }

//    {
//        printf("--- test IsFormatSame\n");
//        DataArray1d* da1d_1 = new DataArrayNerr1d;
//        DataArray1d* da1d_2 = new DataArraySerr1d;
//        da1d_1->Init(3);
//        da1d_1->SetValElm(0, 1.0);
//        da1d_1->SetValElm(1, 2.0);
//        da1d_1->SetValElm(2, 3.0);
//        da1d_1->PrintInfo(stdout);
//        da1d_1->PrintData(stdout, 1, 0.0);
//
//        da1d_2->Init(4);
//        da1d_2->SetValElm(0, -1.0);
//        da1d_2->SetValElm(1, -2.0);
//        da1d_2->SetValElm(2, -3.0);
//        da1d_2->SetValElm(3, -4.0);        
//        da1d_2->SetValSerrElm(0, 0.5);
//        da1d_2->SetValSerrElm(1, 0.7);
//        da1d_2->SetValSerrElm(2, 0.9);
//        da1d_2->SetValSerrElm(3, 1.1);
//        da1d_2->PrintInfo(stdout);
//        da1d_2->PrintData(stdout, 1, 0.0);
//
//        int ret = DataArray1dOpe::IsFormatSame(da1d_1, da1d_2);
//
//        // ---> abort
//        
//        printf("ret = %d\n", ret);
//        assert(0 == ret);
//        
//        delete da1d_1;
//        delete da1d_2;
//        printf("=== \n");
//    }
    
//     int IsFormatSame(const DataArray1d* const* const data_array_arr,
//                     int ndata_array);
    {
        printf("--- test IsFormatSame\n");

        int narr = 3;
        DataArray1d** da1d_arr = new DataArray1d* [narr];
        int iarr = 0;
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, -2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 5.0);
        da1d_arr[iarr]->SetValElm(1, -6.0);
        da1d_arr[iarr]->SetValElm(2, 7.0);
        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, -10.0);
        da1d_arr[iarr]->SetValElm(1, 20.0);
        da1d_arr[iarr]->SetValElm(2, -30.0);
        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        

        int ret = DataArray1dOpe::IsFormatSame(da1d_arr, narr);
        printf("ret = %d\n", ret);
        assert(1 == ret);

        for(int iarr = 0; iarr < narr; iarr++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;

        printf("=== \n");
    }


//    {
//        printf("--- test IsFormatSame\n");
//
//        int narr = 3;
//        DataArray1d** da1d_arr = new DataArray1d* [narr];
//        int iarr = 0;
//        da1d_arr[iarr] = new DataArrayNerr1d;
//        da1d_arr[iarr]->Init(4);
//        da1d_arr[iarr]->SetValElm(0, 1.0);
//        da1d_arr[iarr]->SetValElm(1, -2.0);
//        da1d_arr[iarr]->SetValElm(2, 3.0);
//        da1d_arr[iarr]->SetValElm(3, 8.0);
//        da1d_arr[iarr]->PrintInfo(stdout);
//        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
//        iarr = 1;
//        da1d_arr[iarr] = new DataArraySerr1d;
//        da1d_arr[iarr]->Init(3);
//        da1d_arr[iarr]->SetValElm(0, 5.0);
//        da1d_arr[iarr]->SetValElm(1, -6.0);
//        da1d_arr[iarr]->SetValElm(2, 7.0);
//        da1d_arr[iarr]->SetValSerrElm(0, 0.1);
//        da1d_arr[iarr]->SetValSerrElm(1, 0.2);
//        da1d_arr[iarr]->SetValSerrElm(2, 0.3);
//        da1d_arr[iarr]->PrintInfo(stdout);
//        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
//        iarr = 2;
//        da1d_arr[iarr] = new DataArrayTerr1d;
//        da1d_arr[iarr]->Init(3);
//        da1d_arr[iarr]->SetValElm(0, -10.0);
//        da1d_arr[iarr]->SetValElm(1, 20.0);
//        da1d_arr[iarr]->SetValElm(2, -30.0);
//        da1d_arr[iarr]->SetValTerrPlusElm(0, 0.4);
//        da1d_arr[iarr]->SetValTerrPlusElm(1, 0.5);
//        da1d_arr[iarr]->SetValTerrPlusElm(2, 0.6);
//        da1d_arr[iarr]->SetValTerrMinusElm(0, -1.0);
//        da1d_arr[iarr]->SetValTerrMinusElm(1, -3.0);
//        da1d_arr[iarr]->SetValTerrMinusElm(2, -5.0);
//        da1d_arr[iarr]->PrintInfo(stdout);
//        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
//
//        int ret = DataArray1dOpe::IsFormatSame(da1d_arr, narr);
//        // ---> abort    
//        printf("ret = %d\n", ret);
//        assert(0 == ret);
//
//        for(int iarr = 0; iarr < narr; iarr++){
//            delete da1d_arr[iarr];
//        }
//        delete [] da1d_arr;
//
//        printf("=== \n");
//    }
    
//   void GetSelectDa1dByInterval(const DataArray1d* const data_array,
//                                 const Interval* const interval,
//                                 DataArrayNerr1d* const data_array_out);
    {
        printf("--- test GetSelectDa1dByInterval\n");
        DataArray1d* da1d = new DataArrayNerr1d;
        da1d->Init(5);
        da1d->SetValElm(0, 0.0);
        da1d->SetValElm(1, 3.0);
        da1d->SetValElm(2, 7.0);
        da1d->SetValElm(3, 9.0);
        da1d->SetValElm(4, 10.0);
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        Interval* interval = new Interval;
        interval->Init(2);
        double st_arr[2];
        double ed_arr[2];
        st_arr[0] = 1.0; ed_arr[0] = 4.0;
        st_arr[1] = 8.0; ed_arr[1] = 9.5;
        interval->Set(2, st_arr, ed_arr);
        interval->Print(stdout);
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetSelectDa1dByInterval(da1d, interval, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d_new->GetClassName() );
        assert( 2 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( 3.0 == da1d_new->GetValElm(0) );
        assert( 9.0 == da1d_new->GetValElm(1) );

        delete da1d;
        delete interval;
        delete da1d_new;
        printf("=== \n");
    }

//   void GetSelectDa1dByInterval(const DataArray1d* const data_array,
//                                const Interval* const interval,
//                                DataArraySerr1d* const data_array_out);
    {
        printf("--- test GetSelectDa1dByInterval\n");
        DataArray1d* da1d = new DataArraySerr1d;
        da1d->Init(5);
        da1d->SetValElm(0, 0.0);
        da1d->SetValElm(1, 3.0);
        da1d->SetValElm(2, 7.0);
        da1d->SetValElm(3, 9.0);
        da1d->SetValElm(4, 10.0);
        da1d->SetValSerrElm(0, 0.5);
        da1d->SetValSerrElm(1, 0.5);
        da1d->SetValSerrElm(2, 0.5);
        da1d->SetValSerrElm(3, 0.5);
        da1d->SetValSerrElm(4, 0.5);
        
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        Interval* interval = new Interval;
        interval->Init(2);
        double st_arr[2];
        double ed_arr[2];
        st_arr[0] = 1.0; ed_arr[0] = 4.0;
        st_arr[1] = 8.0; ed_arr[1] = 9.5;
        interval->Set(2, st_arr, ed_arr);
        interval->Print(stdout);
        
        DataArraySerr1d* da1d_new = new DataArraySerr1d;
        DataArray1dOpe::GetSelectDa1dByInterval(da1d, interval, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArraySerr1d" == da1d_new->GetClassName() );
        assert( 2 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( 3.0 == da1d_new->GetValElm(0) );
        assert( 9.0 == da1d_new->GetValElm(1) );
        assert( 0.5 == da1d_new->GetValSerrElm(0) );
        assert( 0.5 == da1d_new->GetValSerrElm(1) );

        delete da1d;
        delete interval;
        delete da1d_new;
        printf("=== \n");
    }

//void DataArray1dOpe::GetSelectDa1dByInterval(const DataArray1d* const data_array,
//                                             const Interval* const interval,
//                                             DataArrayTerr1d* const data_array_out)
    {
        printf("--- test GetSelectDa1dByInterval\n");
        DataArray1d* da1d = new DataArrayTerr1d;
        da1d->Init(5);
        da1d->SetValElm(0, 0.0);
        da1d->SetValElm(1, 3.0);
        da1d->SetValElm(2, 7.0);
        da1d->SetValElm(3, 9.0);
        da1d->SetValElm(4, 10.0);
        da1d->SetValTerrPlusElm(0, 0.5);
        da1d->SetValTerrPlusElm(1, 0.5);
        da1d->SetValTerrPlusElm(2, 0.5);
        da1d->SetValTerrPlusElm(3, 0.5);
        da1d->SetValTerrPlusElm(4, 0.5);
        da1d->SetValTerrMinusElm(0, -0.3);
        da1d->SetValTerrMinusElm(1, -0.3);
        da1d->SetValTerrMinusElm(2, -0.3);
        da1d->SetValTerrMinusElm(3, -0.3);
        da1d->SetValTerrMinusElm(4, -0.3);
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        Interval* interval = new Interval;
        interval->Init(2);
        double st_arr[2];
        double ed_arr[2];
        st_arr[0] = 1.0; ed_arr[0] = 4.0;
        st_arr[1] = 8.0; ed_arr[1] = 9.5;
        interval->Set(2, st_arr, ed_arr);
        interval->Print(stdout);
        
        DataArrayTerr1d* da1d_new = new DataArrayTerr1d;
        DataArray1dOpe::GetSelectDa1dByInterval(da1d, interval, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        assert( "DataArrayTerr1d" == da1d_new->GetClassName() );
        assert( 2 == da1d_new->GetNdata() );
        assert( 0 == da1d_new->GetFlagValSorted() );
        assert( 3.0 == da1d_new->GetValElm(0) );
        assert( 9.0 == da1d_new->GetValElm(1) );
        assert( 0.5 == da1d_new->GetValTerrPlusElm(0) );
        assert( 0.5 == da1d_new->GetValTerrPlusElm(1) );
        assert( -0.3 == da1d_new->GetValTerrMinusElm(0) );
        assert( -0.3 == da1d_new->GetValTerrMinusElm(1) );        

        delete da1d;
        delete interval;
        delete da1d_new;
        printf("=== \n");
    }


//    void GenSelectDa1dArrByIntervalNerr(const DataArray1d* const data_array,
//                                        const Interval* const interval,
//                                        DataArray1d*** const data_array_arr_ptr);
    {
        printf("--- test GenSelectDa1dArrByIntervalNerr\n");
        DataArray1d* da1d = new DataArrayNerr1d;
        da1d->Init(5);
        da1d->SetValElm(0, 0.0);
        da1d->SetValElm(1, 3.0);
        da1d->SetValElm(2, 7.0);
        da1d->SetValElm(3, 9.0);
        da1d->SetValElm(4, 10.0);
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        Interval* interval = new Interval;
        interval->Init(2);
        double st_arr[2];
        double ed_arr[2];
        st_arr[0] = 1.0; ed_arr[0] = 4.0;
        st_arr[1] = 8.0; ed_arr[1] = 9.5;
        interval->Set(2, st_arr, ed_arr);
        interval->Print(stdout);
        
        DataArray1d** da1d_new_arr = NULL;
        DataArray1dOpe::GenSelectDa1dArrByIntervalNerr(da1d, interval, &da1d_new_arr);

        for(int iterm = 0; iterm < 2; iterm ++){
            da1d_new_arr[iterm]->PrintInfo(stdout);
            da1d_new_arr[iterm]->PrintData(stdout, 1, 0.0);
        }

        assert( "DataArrayNerr1d" == da1d_new_arr[0]->GetClassName() );
        assert( 1 == da1d_new_arr[0]->GetNdata() );
        assert( 0 == da1d_new_arr[0]->GetFlagValSorted() );
        assert( 3.0 == da1d_new_arr[0]->GetValElm(0) );

        assert( "DataArrayNerr1d" == da1d_new_arr[1]->GetClassName() );
        assert( 1 == da1d_new_arr[1]->GetNdata() );
        assert( 0 == da1d_new_arr[1]->GetFlagValSorted() );
        assert( 9.0 == da1d_new_arr[1]->GetValElm(0) );

        for(int iterm = 0; iterm < 2; iterm ++){
            delete da1d_new_arr[iterm];
        }
        delete [] da1d_new_arr;
        delete da1d;
        delete interval;

        printf("=== \n");
    }

//   void GenSelectDa1dArrByIntervalSerr(const DataArray1d* const data_array,
//                                        const Interval* const interval,
//                                        DataArray1d*** const data_array_arr_ptr);
    {
        printf("--- test GenSelectDa1dArrByIntervalSerr\n");
        DataArray1d* da1d = new DataArraySerr1d;
        da1d->Init(5);
        da1d->SetValElm(0, 0.0);
        da1d->SetValElm(1, 3.0);
        da1d->SetValElm(2, 7.0);
        da1d->SetValElm(3, 9.0);
        da1d->SetValElm(4, 10.0);
        da1d->SetValSerrElm(0, 0.5);
        da1d->SetValSerrElm(1, 0.5);
        da1d->SetValSerrElm(2, 0.5);
        da1d->SetValSerrElm(3, 0.5);
        da1d->SetValSerrElm(4, 0.5);
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        Interval* interval = new Interval;
        interval->Init(2);
        double st_arr[2];
        double ed_arr[2];
        st_arr[0] = 1.0; ed_arr[0] = 4.0;
        st_arr[1] = 8.0; ed_arr[1] = 9.5;
        interval->Set(2, st_arr, ed_arr);
        interval->Print(stdout);
        
        DataArray1d** da1d_new_arr = NULL;
        DataArray1dOpe::GenSelectDa1dArrByIntervalSerr(da1d, interval, &da1d_new_arr);

        for(int iterm = 0; iterm < 2; iterm ++){
            da1d_new_arr[iterm]->PrintInfo(stdout);
            da1d_new_arr[iterm]->PrintData(stdout, 1, 0.0);
        }

        assert( "DataArraySerr1d" == da1d_new_arr[0]->GetClassName() );
        assert( 1 == da1d_new_arr[0]->GetNdata() );
        assert( 0 == da1d_new_arr[0]->GetFlagValSorted() );
        assert( 3.0 == da1d_new_arr[0]->GetValElm(0) );
        assert( 0.5 == da1d_new_arr[0]->GetValSerrElm(0) );

        assert( "DataArraySerr1d" == da1d_new_arr[1]->GetClassName() );
        assert( 1 == da1d_new_arr[1]->GetNdata() );
        assert( 0 == da1d_new_arr[1]->GetFlagValSorted() );
        assert( 9.0 == da1d_new_arr[1]->GetValElm(0) );
        assert( 0.5 == da1d_new_arr[1]->GetValSerrElm(0) );

        for(int iterm = 0; iterm < 2; iterm ++){
            delete da1d_new_arr[iterm];
        }
        delete [] da1d_new_arr;
        delete da1d;
        delete interval;

        printf("=== \n");
    }
    
//    void GenSelectDa1dArrByIntervalTerr(const DataArray1d* const data_array,
//                                        const Interval* const interval,
//                                        DataArray1d*** const data_array_arr_ptr);
    {
        printf("--- test GenSelectDa1dArrByIntervalTerr\n");
        DataArray1d* da1d = new DataArrayTerr1d;
        da1d->Init(5);
        da1d->SetValElm(0, 0.0);
        da1d->SetValElm(1, 3.0);
        da1d->SetValElm(2, 7.0);
        da1d->SetValElm(3, 9.0);
        da1d->SetValElm(4, 10.0);
        da1d->SetValTerrPlusElm(0, 0.5);
        da1d->SetValTerrPlusElm(1, 0.5);
        da1d->SetValTerrPlusElm(2, 0.5);
        da1d->SetValTerrPlusElm(3, 0.5);
        da1d->SetValTerrPlusElm(4, 0.5);
        da1d->SetValTerrMinusElm(0, -0.3);
        da1d->SetValTerrMinusElm(1, -0.3);
        da1d->SetValTerrMinusElm(2, -0.3);
        da1d->SetValTerrMinusElm(3, -0.3);
        da1d->SetValTerrMinusElm(4, -0.3);
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        Interval* interval = new Interval;
        interval->Init(2);
        double st_arr[2];
        double ed_arr[2];
        st_arr[0] = 1.0; ed_arr[0] = 4.0;
        st_arr[1] = 8.0; ed_arr[1] = 9.5;
        interval->Set(2, st_arr, ed_arr);
        interval->Print(stdout);
        
        DataArray1d** da1d_new_arr = NULL;
        DataArray1dOpe::GenSelectDa1dArrByIntervalTerr(da1d, interval, &da1d_new_arr);

        for(int iterm = 0; iterm < 2; iterm ++){
            da1d_new_arr[iterm]->PrintInfo(stdout);
            da1d_new_arr[iterm]->PrintData(stdout, 1, 0.0);
        }

        assert( "DataArrayTerr1d" == da1d_new_arr[0]->GetClassName() );
        assert( 1 == da1d_new_arr[0]->GetNdata() );
        assert( 0 == da1d_new_arr[0]->GetFlagValSorted() );
        assert( 3.0 == da1d_new_arr[0]->GetValElm(0) );
        assert( 0.5 == da1d_new_arr[0]->GetValTerrPlusElm(0) );
        assert( -0.3 == da1d_new_arr[0]->GetValTerrMinusElm(0) );        

        assert( "DataArrayTerr1d" == da1d_new_arr[1]->GetClassName() );
        assert( 1 == da1d_new_arr[1]->GetNdata() );
        assert( 0 == da1d_new_arr[1]->GetFlagValSorted() );
        assert( 9.0 == da1d_new_arr[1]->GetValElm(0) );
        assert( 0.5 == da1d_new_arr[1]->GetValTerrPlusElm(0) );
        assert( -0.3 == da1d_new_arr[1]->GetValTerrMinusElm(0) );

        for(int iterm = 0; iterm < 2; iterm ++){
            delete da1d_new_arr[iterm];
        }
        delete [] da1d_new_arr;
        delete da1d;
        delete interval;

        printf("=== \n");
    }
    

    


    
    return status_prog;
}

