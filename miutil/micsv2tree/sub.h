#ifndef MORIIISM_MITOOL_MIUTIL_MICSV2TREE_SUB_H_
#define MORIIISM_MITOOL_MIUTIL_MICSV2TREE_SUB_H_

#include "mi_base.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::istringstream;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

const int kNType = 6;
const string kTypeArr[kNType] = {"UChar_t", "Short_t", "Int_t",
                                 "Long64_t", "Float_t", "Double_t"};

//    UChar_t   8  bit
//    Short_t   16 bit
//    Int_t     32 bit
//    Long64_t  64 bit
//    Float_t   32 bit
//    Double_t  64 bit

class TTreeFormat{
public:
    TTreeFormat() :
        nval_(0),
        type_arr_(NULL),
        valname_arr_(NULL),
        index_in_type_arr_(NULL) {}
    ~TTreeFormat(){
        if(NULL != type_arr_){delete [] type_arr_; type_arr_ = NULL;}
        if(NULL != valname_arr_){delete [] valname_arr_; valname_arr_ = NULL;}
        if(NULL != index_in_type_arr_) {delete [] index_in_type_arr_; index_in_type_arr_ = NULL;}
    }
    void Load(string file);
    void SetIndexInTypeArr();
    void Print() const;
    
    int GetNval() const {return nval_;};

    string* GetTypeArr() const {return type_arr_;};
    string* GetValnameArr() const {return valname_arr_;};
    int* GetIndexInTypeArr() const {return index_in_type_arr_;};

    string GetTypeArrElm(int ival) const {return type_arr_[ival];};
    string GetValnameArrElm(int ival) const {return valname_arr_[ival];};
    int GetIndexInTypeArrElm(int ival) const {return index_in_type_arr_[ival];};

    int GetThisTypeID(int ival) const {return GetTypeID(type_arr_[ival]);};
    int GetNumOfType(string type) const;
    static int GetTypeID(string type);

    // void* GenValArrOfType(string type, int nval) const;
    
private:
    int nval_;
    string* type_arr_;
    string* valname_arr_;
    int* index_in_type_arr_;
};

#endif // MORIIISM_MITOOL_MIUTIL_MICSV2TREE_SUB_H_
