#ifndef MORIIISM_MITOOL_MILIB_PAR_H_
#define MORIIISM_MITOOL_MILIB_PAR_H_

#include <limits>
#include <cfloat>
#include <string>
using std::string;

const int kRetNormal = 0;
const int kRetError = -1;
const int kLineSize = 1000;

// global variable 
extern int g_flag_debug; 
extern int g_flag_help;
extern int g_flag_verbose;

#endif // MORIIISM_MITOOL_MILIB_PAR_H_
