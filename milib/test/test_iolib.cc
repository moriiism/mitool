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
        MiIolib::DelReadFile(valx_arr);

        printf("=== \n");
    }

//    {
//        printf("--- test GenReadFile()\n");
//        
//        string file = "data/test1.bad.dat";
//        double* valx_arr = NULL;
//        long nline = 0;
//        MiIolib::GenReadFile(file, &valx_arr, &nline);
//        printf("nline = %ld\n", nline);
//        for(long iline = 0; iline < nline; iline ++){
//            printf("valx_arr[%ld] = %e\n",
//                   iline, valx_arr[iline]);
//        }
//        MiIolib::DelReadFile(valx_arr);
//
//        printf("=== \n");
//    }
//  
//    {
//        printf("--- test GenReadFile()\n");
//        
//        string file = "data/test2.dat";
//        double* valx_arr = NULL;
//        long nline = 0;
//        MiIolib::GenReadFile(file, &valx_arr, &nline);
//        printf("nline = %ld\n", nline);
//        for(long iline = 0; iline < nline; iline ++){
//            printf("valx_arr[%ld] = %e\n",
//                   iline, valx_arr[iline]);
//        }
//        MiIolib::DelReadFile(valx_arr);        
//
//        printf("=== \n");
//    }
//
//    {
//        printf("--- test GenReadFile()\n");
//        
//        string file = "data/test3.dat";
//        double* valx_arr = NULL;
//        long nline = 0;
//        MiIolib::GenReadFile(file, &valx_arr, &nline);
//        printf("nline = %ld\n", nline);
//        for(long iline = 0; iline < nline; iline ++){
//            printf("valx_arr[%ld] = %e\n",
//                   iline, valx_arr[iline]);
//        }
//        MiIolib::DelReadFile(valx_arr);
//
//        printf("=== \n");        
//    }
    
    
//    int GenReadFile(string file,
//                    double** const valx1_arr_ptr,
//                    double** const valx2_arr_ptr,
//                    long* const nline_ptr);
    {
        printf("--- test GenReadFile()\n");
        
        string file = "data/test2.dat";
        double* valx1_arr = NULL;
        double* valx2_arr = NULL;
        long nline = 0;
        MiIolib::GenReadFile(file, &valx1_arr, &valx2_arr, &nline);
        printf("nline = %ld\n", nline);
        for(long iline = 0; iline < nline; iline ++){
            printf("valx1_arr[%ld] = %e , valx2_arr[%ld] = %e \n",
                   iline, valx1_arr[iline],
                   iline, valx2_arr[iline]);
        }
        MiIolib::DelReadFile(valx1_arr);
        MiIolib::DelReadFile(valx2_arr);

        printf("=== \n");
    }

//    {
//        printf("--- test GenReadFile()\n");
//        
//        string file = "data/test3.dat";
//        double* valx1_arr = NULL;
//        double* valx2_arr = NULL;
//        long nline = 0;
//        MiIolib::GenReadFile(file, &valx1_arr, &valx2_arr, &nline);
//        printf("nline = %ld\n", nline);
//        for(long iline = 0; iline < nline; iline ++){
//            printf("valx1_arr[%ld] = %e , valx2_arr[%ld] = %e \n",
//                   iline, valx1_arr[iline],
//                   iline, valx2_arr[iline]);
//        }
//        MiIolib::DelReadFile(valx1_arr);
//        MiIolib::DelReadFile(valx2_arr);
//
//        printf("=== \n");
//    }

    
//    int GenReadFile(string file,
//                    double** const valx1_arr_ptr,
//                    double** const valx2_arr_ptr,
//                    double** const valx3_arr_ptr,
//                    long* const nline_ptr);

    {
        printf("--- test GenReadFile()\n");
        
        string file = "data/test3.dat";
        double* valx1_arr = NULL;
        double* valx2_arr = NULL;
        double* valx3_arr = NULL;
        long nline = 0;
        MiIolib::GenReadFile(file, &valx1_arr, &valx2_arr, &valx3_arr, &nline);
        printf("nline = %ld\n", nline);
        for(long iline = 0; iline < nline; iline ++){
            printf("valx1_arr[%ld] = %e , valx2_arr[%ld] = %e, "
                   "valx3_arr[%ld] = %e\n",
                   iline, valx1_arr[iline],
                   iline, valx2_arr[iline],
                   iline, valx3_arr[iline]);
        }
        MiIolib::DelReadFile(valx1_arr);
        MiIolib::DelReadFile(valx2_arr);
        MiIolib::DelReadFile(valx3_arr);

        printf("=== \n");
    }

//
//    int GenReadFile(string file,
//                    string** const lines_ptr,
//                    long* const nline_ptr);
//
    {
        printf("--- test GenReadFile()\n");
        
        string file = "data/test3.dat";
        string* lines_arr = NULL;
        long nline = 0;
        MiIolib::GenReadFile(file, &lines_arr, &nline);
        printf("nline = %ld\n", nline);
        for(long iline = 0; iline < nline; iline ++){
            printf("lines_arr[%ld] = %s\n",
                   iline, lines_arr[iline].c_str());
        }
        MiIolib::DelReadFile(lines_arr);

        printf("=== \n");
    }

   
//    int GenReadFileSkipComment(string file,
//                               string** const lines_ptr,
//                               long* const nline_ptr);

    {
        printf("--- test GenReadFileSkipComment()\n");
        
        string file = "data/test1.bad.dat";
        string* lines_arr = NULL;
        long nline = 0;
        MiIolib::GenReadFileSkipComment(file, &lines_arr, &nline);
        printf("nline = %ld\n", nline);
        for(long iline = 0; iline < nline; iline ++){
            printf("lines_arr[%ld] = %s\n",
                   iline, lines_arr[iline].c_str());
        }
        MiIolib::DelReadFile(lines_arr);

        printf("=== \n");
    }

    
//    int GenReadFileComment(string file,
//                           string** const lines_ptr,
//                           long* const nline_ptr);
//

    {
        printf("--- test GenReadFileComment()\n");
        
        string file = "data/test1.bad.dat";
        string* lines_arr = NULL;
        long nline = 0;
        MiIolib::GenReadFileComment(file, &lines_arr, &nline);
        printf("nline = %ld\n", nline);
        for(long iline = 0; iline < nline; iline ++){
            printf("lines_arr[%ld] = %s\n",
                   iline, lines_arr[iline].c_str());
        }
        MiIolib::DelReadFile(lines_arr);

        printf("=== \n");
    }

//    int GenRowsByReadFileSkipComment(string file,
//                                     vector<long> sel_row_list_vec,
//                                     string** const lines_ptr,
//                                     long* const nline_ptr);
//
    {
        printf("--- test GenRowsByReadFileSkipComment()\n");

        vector<long> sel_row_list_vec(2);
        sel_row_list_vec[0] = 1;
        sel_row_list_vec[1] = 2;
        
        string file = "data/test3.dat";
        string* lines_arr = NULL;
        long nline = 0;
        MiIolib::GenRowsByReadFileSkipComment(file,
                                              sel_row_list_vec,
                                              &lines_arr,
                                              &nline);
        printf("nline = %ld\n", nline);
        for(long iline = 0; iline < nline; iline ++){
            printf("lines_arr[%ld] = %s\n",
                   iline, lines_arr[iline].c_str());
        }
        MiIolib::DelReadFile(lines_arr);

        printf("=== \n");
    }

    
    return status_prog;
}
