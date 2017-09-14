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
        delete da1d;
        printf("=== \n");
    }

    {
        printf("--- test GenDa1dByLoad(string file, string format)\n");
        DataArray1d* da1d = DataArray1dOpe::GenDa1dByLoad("data/test_data1d_serr.dat", "x,xe");
        printf("da1d->GetClassName() = %s\n", da1d->GetClassName().c_str());
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);
        delete da1d;
        printf("=== \n");
    }

    {
        printf("--- test GenDa1dByLoad(string file, string format)\n");
        DataArray1d* da1d = DataArray1dOpe::GenDa1dByLoad("data/test_data1d_terr.dat", "x,xe+,xe-");
        printf("da1d->GetClassName() = %s\n", da1d->GetClassName().c_str());
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);
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
        //da1d->SetValSerrElm(0, 0.5);
        //da1d->SetValSerrElm(1, 0.6);
        //da1d->SetValSerrElm(2, 0.7);
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

        assert( 100.0 == da1d_new->GetValElm(0) );
        
        delete da1d_1;
        delete da1d_2;
        delete da1d_new;
        printf("=== \n");
    }
    
//    void GetMax(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArraySerr1d* const data_array_out);
//    void GetMax(const DataArray1d* const data_array1,
//                const DataArray1d* const data_array2,
//                DataArrayTerr1d* const data_array_out);
    



    

    /// ----------------------------------------------
    
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
        da1d_arr[iarr]->SetValElm(1, 2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);
        iarr = 1;
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, 2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        iarr = 2;
        da1d_arr[iarr] = new DataArrayTerr1d;
        da1d_arr[iarr]->Init(3);
        da1d_arr[iarr]->SetValElm(0, 1.0);
        da1d_arr[iarr]->SetValElm(1, 2.0);
        da1d_arr[iarr]->SetValElm(2, 3.0);
        da1d_arr[iarr]->PrintInfo(stdout);
        da1d_arr[iarr]->PrintData(stdout, 1, 0.0);        
        
        DataArrayNerr1d* da1d_new = new DataArrayNerr1d;
        DataArray1dOpe::GetMin(da1d_arr, narr, da1d_new);
        da1d_new->PrintInfo(stdout);
        da1d_new->PrintData(stdout, 1, 0.0);

        for(int iarr = 0; iarr < narr; iarr ++){
            delete da1d_arr[iarr];
        }
        delete [] da1d_arr;
        delete da1d_new;
        printf("=== \n");
    }
    
    return status_prog;
}



//    void GetMin(const DataArraySerr1d* const* const data_array_arr,
//                int ndata_array,
//                DataArraySerr1d* data_array_out);
//    void GetMin(const DataArrayTerr1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayTerr1d* data_array_out);
//    void GetMax(const DataArrayNerr1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayNerr1d* data_array_out);
//    void GetMax(const DataArraySerr1d* const* const data_array_arr,
//                int ndata_array,
//                DataArraySerr1d* data_array_out);
//    void GetMax(const DataArrayTerr1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayTerr1d* data_array_out);
//    void GetAdd(const DataArrayNerr1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayNerr1d* data_array_out);
//    void GetAdd(const DataArraySerr1d* const* const data_array_arr,
//                int ndata_array,
//                DataArraySerr1d* data_array_out);
//    void GetAMean(const DataArrayNerr1d* const* const data_array_arr,
//                  int ndata_array,
//                  DataArrayNerr1d* data_array_out);
//    void GetAMean(const DataArraySerr1d* const* const data_array_arr,
//                  int ndata_array,
//                  DataArraySerr1d* data_array_out);
//    long GetWMean(const DataArraySerr1d* const* const data_array_arr,
//                  int ndata_array,
//                  vector<long>* const index_bad_vec_ptr,
//                  DataArraySerr1d* data_array_out);
//    void GetVariance(const DataArrayNerr1d* const* const data_array_arr,
//                     int ndata_array,
//                     DataArrayNerr1d* data_array_out);
//    void GetStddev(const DataArrayNerr1d* const* const data_array_arr,
//                   int ndata_array,
//                   DataArrayNerr1d* data_array_out);
//    void GetUnbiasedVariance(const DataArrayNerr1d* const* const data_array_arr,
//                             int ndata_array,
//                             DataArrayNerr1d* data_array_out);
//    void GetSqrtOfUnbiasedVariance(const DataArrayNerr1d* const* const data_array_arr,
//                                   int ndata_array,
//                                   DataArrayNerr1d* data_array_out);
//    void GetRMS(const DataArrayNerr1d* const* const data_array_arr,
//                int ndata_array,
//                DataArrayNerr1d* data_array_out);
//    void GetMedian(const DataArrayNerr1d* const* const data_array_arr,
//                   int ndata_array,
//                   DataArrayNerr1d* data_array_out);
//    void GetAddWithMask(const DataArrayNerr1d* const* const data_array_arr,
//                        const DataArrayNerr1d* const* const mask_array_arr,
//                        int ndata_array,
//                        DataArrayNerr1d* data_array_out);
//    void GetAddWithMask(const DataArraySerr1d* const* const data_array_arr,
//                        const DataArrayNerr1d* const* const mask_array_arr,
//                        int ndata_array,
//                        DataArraySerr1d* data_array_out);
//    void GetAMeanWithMask(const DataArrayNerr1d* const* const data_array_arr,
//                          const DataArrayNerr1d* const* const mask_array_arr,
//                          int ndata_array,
//                          DataArrayNerr1d* const nvalid_array_out,
//                          DataArrayNerr1d* data_array_out);
//    void GetAMeanWithMask(const DataArraySerr1d* const* const data_array_arr,
//                          const DataArrayNerr1d* const* const mask_array_arr,
//                          int ndata_array,
//                          DataArrayNerr1d* const nvalid_array_out,
//                          DataArraySerr1d* data_array_out);
//    long GetWMeanWithMask(const DataArraySerr1d* const* const data_array_arr,
//                          const DataArrayNerr1d* const* const mask_array_arr,
//                          int ndata_array,
//                          vector<long>* const index_bad_vec_ptr,
//                          DataArraySerr1d* const nvalid_array_out,
//                          DataArraySerr1d* data_array_out);
//    int IsFormatSame(const DataArray1d* const data_array1,
//                     const DataArray1d* const data_array2);
//    int IsFormatSame(const DataArrayNerr1d* const* const data_array_arr,
//                     int ndata_array);
//    int IsFormatSame(const DataArraySerr1d* const* const data_array_arr,
//                     int ndata_array);
//    int IsFormatSame(const DataArrayTerr1d* const* const data_array_arr,
//                     int ndata_array);
//    void GetSelectDa1dByInterval(const DataArrayNerr1d* const data_array,
//                                 const Interval* const interval,
//                                 DataArrayNerr1d* const data_array_out);
//    void GetSelectDa1dByInterval(const DataArraySerr1d* const data_array,
//                                 const Interval* const interval,
//                                 DataArraySerr1d* const data_array_out);
//    void GetSelectDa1dByInterval(const DataArrayTerr1d* const data_array,
//                                 const Interval* const interval,
//                                 DataArrayTerr1d* const data_array_out);
//    void GenSelectDa1dArrByInterval(const DataArrayNerr1d* const data_array,
//                                    const Interval* const interval,
//                                    DataArrayNerr1d*** data_array_arr_ptr);
//    void GenSelectDa1dArrByInterval(const DataArraySerr1d* const data_array,
//                                    const Interval* const interval,
//                                    DataArraySerr1d*** data_array_arr_ptr);
//    void GenSelectDa1dArrByInterval(const DataArrayTerr1d* const data_array,
//                                    const Interval* const interval,
//                                    DataArrayTerr1d*** data_array_arr_ptr);    
