#include "mi_iolib.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    int GenReadFile(string file,
//                    double** const valx_arr_ptr,
//                    long* const nline_ptr);
    {
        printf("--- test GenReadFile()\n");
        
        string file = "data/test1.dat";
        double* valx_arr = NULL;
        long nline = 0;
        MiIolib::GenReadFile(file, &valx_arr, &nline);
        printf("nline = %ld\n", nline);
        for(long iline = 0; iline < nline; iline ++){
            printf("valx_arr[%ld] = %e\n",
                   iline, valx_arr[iline]);
        }
        delete [] valx_arr;

        printf("=== \n");
    }

    {
        printf("--- test GenReadFile()\n");
        
        string file = "data/test2.dat";
        double* valx_arr = NULL;
        long nline = 0;
        MiIolib::GenReadFile(file, &valx_arr, &nline);
        printf("nline = %ld\n", nline);
        for(long iline = 0; iline < nline; iline ++){
            printf("valx_arr[%ld] = %e\n",
                   iline, valx_arr[iline]);
        }
        delete [] valx_arr;

        printf("=== \n");
    }

    {
        printf("--- test GenReadFile()\n");
        
        string file = "data/test3.dat";
        double* valx_arr = NULL;
        long nline = 0;
        MiIolib::GenReadFile(file, &valx_arr, &nline);
        printf("nline = %ld\n", nline);
        for(long iline = 0; iline < nline; iline ++){
            printf("valx_arr[%ld] = %e\n",
                   iline, valx_arr[iline]);
        }
        delete [] valx_arr;

        printf("=== \n");        
    }
    
    
//    int GenReadFile(string file,
//                    double** const valx1_arr_ptr,
//                    double** const valx2_arr_ptr,
//                    long* const nline_ptr);
//
//    int GenReadFile(string file,
//                    double** const valx1_arr_ptr,
//                    double** const valx2_arr_ptr,
//                    double** const valx3_arr_ptr,
//                    long* const nline_ptr);
//
//    int GenReadFile(string file,
//                    string** const lines_ptr,
//                    long* const nline_ptr);
//
//    int GenReadFileSkipComment(string file,
//                               string** const lines_ptr,
//                               long* const nline_ptr);
//
//    int GenReadFileComment(string file,
//                           string** const lines_ptr,
//                           long* const nline_ptr);
//
//    int GenRowsByReadFileSkipComment(string file,
//                                     vector<long> sel_row_list_vec,
//                                     string** const lines_ptr,
//                                     long* const nline_ptr);
//    
//
//    void DelReadFile(double* val_arr);
//    void DelReadFile(string* line_arr);
//
//    int TestFileExist(string fname);
//
//
//    // int GenReadFileOrFilelist(string name,
//    //                           string** const filelist_ptr,
//    //                           int* const nfile_ptr);
//
//    int Printf2(FILE* fp_log, const char* const format, ...);
//    void Qstop();
//    // query stop: this function is useful, when you want to stop program.
//
//
//

    
    return status_prog;
}
