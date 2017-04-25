#include "sub.h"

void TTreeFormat::Load(string file)
{
    string buf;
    vector<string> buf_vec;

    ifstream ifs(file.c_str());
    while(ifs && getline(ifs, buf)){
        buf_vec.push_back(buf);
    }
    ifs.close();

    nval_ = buf_vec.size();

    printf("nval = %d\n", nval_);
    
    type_arr_ = new string [nval_];
    valname_arr_ = new string [nval_];
    istringstream iss;
    for(int ival = 0; ival < nval_; ival ++){
        iss.str("");
        iss.clear(stringstream::goodbit);
        iss.str(buf_vec[ival]);
        iss >> type_arr_[ival] >> valname_arr_[ival];

        printf("type_arr %s\n", type_arr_[ival].c_str());
    }
    
    
    SetIndexInTypeArr();
}

void TTreeFormat::SetIndexInTypeArr()
{
    index_in_type_arr_ = new int [nval_];

    int* index_of_type = new int [kNType];
    for(int itype = 0; itype < kNType; itype++){
        index_of_type[itype] = 0;
    }
    for(int ival = 0; ival < nval_; ival ++){
        index_in_type_arr_[ival] = index_of_type[GetTypeID(type_arr_[ival])];
        index_of_type[GetTypeID(type_arr_[ival])] ++;
    }
    delete [] index_of_type;
}



int TTreeFormat::GetNumOfType(string type) const
{
    int num = 0;
    for(int ival = 0; ival < nval_; ival++){
        if(type == type_arr_[ival]){
            num ++;
        }
    }
    return num;
}



int TTreeFormat::GetTypeID(string type)
{
    int type_id;
    for(int itype = 0; itype < kNType; itype ++){
        if(kTypeArr[itype] == type){
            type_id = itype;
        }
    }
    return type_id;
}


void TTreeFormat::Print() const
{
    for(int ival = 0; ival < nval_; ival++){
        printf("%10s  %10s  %2.2d\n",
               type_arr_[ival].c_str(),
               valname_arr_[ival].c_str(),
               index_in_type_arr_[ival]);
    }
}


//
//void* TTreeFormat::GenValArrOfType(string type, int nval) const
//{
//    void* val_arr = NULL;
//    if(type == kTypeArr[0]){
//        val_arr = new UChar_t [nval];
//    } else if (type == kTypeArr[1]){
//        val_arr = new Short_t [nval];
//    } else if (type == kTypeArr[2]){
//        val_arr = new Int_t [nval];
//    } else if (type == kTypeArr[3]){
//        val_arr = new Long64_t [nval];
//    } else if (type == kTypeArr[4]){
//        val_arr = new Float_t [nval];
//    } else if (type == kTypeArr[5]){
//        val_arr = new Double_t [nval];
//    } else {
//        exit(1);
//    }
//    return val_arr;
//}
//
