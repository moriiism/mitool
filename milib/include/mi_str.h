#ifndef MORIIISM_MITOOL_MILIB_STR_H_
#define MORIIISM_MITOOL_MILIB_STR_H_

#include "mi_base.h"

namespace MiStr
{
    int IsSpace(string buf);
    // If the string buf is composed of only ' ' and '\t',
    // this returns 1.
    // If the string buf is "", this returns also 1.
    // In the other cases, this returns 0.

    int Chomp(char* const buf);
    int Chomp(string* const buf_ptr);
    // If the string buf contains '\n' at the last point,
    // this remove the '\n'.
    // The function name is the same as such a function in perl.

    void RmStSpace(string* const buf_ptr);
    // This removes successive spaces at the head of buf.
    void RmEdSpace(string* const buf_ptr);
    // This removes successive spaces at the tail of buf.
    void RmStEdSpace(string* const buf_ptr);
    // This removes successive spaces at the head and tails of buf.
    
    void GenSplit(string str_in, int* nsplit_ptr, string** split_arr_ptr,
                  const char* const delim = " \t");
    void DelSplit(string* split_arr);
    
    int GetNcolumn(string str_in, const char* const delim = " \t");
    
}  //  namespace MiStr

#endif // MORIIISM_MITOOL_MILIB_STR_H_
