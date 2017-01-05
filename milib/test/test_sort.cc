#include "mi_sort.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

    //template <typename Element, typename Index>
    // void Sort(Index n, const Element* a, Index* index, bool down)
    {
        printf("--- test Sort()\n");
        
        int narr = 5;
        double* val_arr = new double [narr];
        val_arr[0] = 5.;
        val_arr[1] = 1.;
        val_arr[2] = 3.;
        val_arr[3] = 2.;
        val_arr[4] = 4.;
        int* index_arr = new int [5];
        MiSort::Sort(5, val_arr, index_arr, 0);
        for(int iarr = 0; iarr < narr; iarr ++){
            printf("%d\n", index_arr[iarr]);
        }
        delete [] val_arr;
        delete [] index_arr;

        printf("=== \n");
    }

    {
        printf("--- test Sort()\n");
        
        int narr = 5;
        double* val_arr = new double [narr];
        val_arr[0] = 5.;
        val_arr[1] = 1.;
        val_arr[2] = 3.;
        val_arr[3] = 2.;
        val_arr[4] = 4.;
        int* index_arr = new int [5];
        MiSort::Sort(5, val_arr, index_arr, 1);
        for(int iarr = 0; iarr < narr; iarr ++){
            printf("%d\n", index_arr[iarr]);
        }
        delete [] val_arr;
        delete [] index_arr;

        printf("=== \n");
    }

    
    // 0, ..., k,..., n
    // template <typename Element, typename Index>
    // void KthElement(Index k, Index n, const Element* a, Index* index, bool down)

    {
        printf("--- test KthElement()\n");
        
        int narr = 5;
        double* val_arr = new double [narr];
        val_arr[0] = 5.;
        val_arr[1] = 1.;
        val_arr[2] = 3.;
        val_arr[3] = 2.;
        val_arr[4] = 4.;
        int* index_arr = new int [5];
        MiSort::KthElement(2, 5, val_arr, index_arr, 0);
        for(int iarr = 0; iarr < narr; iarr ++){
            printf("%d\n", index_arr[iarr]);
        }
        delete [] val_arr;
        delete [] index_arr;

        printf("=== \n");
    }

    // template <typename T>
    // long BinarySearch(long n, const T *array, T value)

    {
        printf("--- test BinarySearch()\n");
        
        int narr = 5;
        int* val_arr = new int [narr];
        val_arr[0] = 5.;
        val_arr[1] = 1.;
        val_arr[2] = 3.;
        val_arr[3] = 2.;
        val_arr[4] = 4.;
        long index = MiSort::BinarySearch(5, val_arr, 3);
        printf("index = %ld\n", index);
        delete [] val_arr;

        printf("=== \n");
    }

    
    
    return status_prog;
}
