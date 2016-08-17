#ifndef MORIIISM_MILIB_IOLIB_H_
#define MORIIISM_MILIB_IOLIB_H_

#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <cstdarg>

#include <iostream>
#include <fstream>
#include <sstream>

using std::istringstream;
using std::ifstream;
using std::stringstream;

#include "mi_str.h"

namespace MiIolib
{

    int GenReadFile(string file,
                    double** const valx_arr_ptr,
                    long* const nline_ptr);

    int GenReadFile(string file,
                    double** const valx1_arr_ptr,
                    double** const valx2_arr_ptr,
                    long* const nline_ptr);

    int GenReadFile(string file,
                    double** const valx1_arr_ptr,
                    double** const valx2_arr_ptr,
                    double** const valx3_arr_ptr,
                    long* const nline_ptr);

    int GenReadFile(string file,
                    char*** const lines_ptr,
                    long* const nline_ptr);

    int GenReadFile(string file,
                    string** const lines_ptr,
                    long* const nline_ptr);

    int GenReadFileSkipComment(string file,
                               string** const lines_ptr,
                               long* const nline_ptr);

    int GenReadFileComment(string file,
                           string** const lines_ptr,
                           long* const nline_ptr);

    int GenRowsByReadFileSkipComment(string file,
                                     vector<long> sel_row_list_vec,
                                     string** const lines_ptr,
                                     long* const nline_ptr);
    

    void DelReadFile(double* val_arr);
    void DelReadFile(long nline, char** line_arr);
    void DelReadFile(string* line_arr);

    int TestFileExist(string fname);


    // int GenReadFileOrFilelist(string name,
    //                           string** const filelist_ptr,
    //                           int* const nfile_ptr);

    int Printf2(FILE* fp_log, const char* const format, ...);
    void Qstop();
    // query stop: this function is useful, when you want to stop program.

}  // namespace MiIolib

#endif // MORIIISM_MILIB_IOLIB_H_
