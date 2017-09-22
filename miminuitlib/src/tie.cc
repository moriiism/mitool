#include "mim_tie.h"

//
// public
//

void MimTie::Init(int ntie)
{
    Null();
    
    ntie_ = ntie;
    id_data_lhs_arr_ = new int [ntie];
    id_func_lhs_arr_ = new int [ntie];
    id_data_rhs_arr_ = new int [ntie];
    id_func_rhs_arr_ = new int [ntie];
}


void MimTie::SetIdDataLhsElm(int itie, int id_data)
{
    id_data_lhs_arr_[itie] = id_data;
}

void MimTie::SetIdFuncLhsElm(int itie, int id_func)
{
    id_func_lhs_arr_[itie] = id_func;
}

void MimTie::SetIdDataRhsElm(int itie, int id_data)
{
    id_data_rhs_arr_[itie] = id_data;
}

void MimTie::SetIdFuncRhsElm(int itie, int id_func)
{
    id_func_rhs_arr_[itie] = id_func;
}

void MimTie::Load(string file)
{
    Null();
    
    long nline = 0;
    string* line_arr = NULL;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &nline);

    Init(nline);
    for(int itie = 0; itie < GetNtie(); itie ++){
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(line_arr[itie], &nsplit, &split_arr, " ");
        id_data_lhs_arr_[itie] = atoi(split_arr[0].c_str());
        id_func_lhs_arr_[itie] = atoi(split_arr[1].c_str());
        id_data_rhs_arr_[itie] = atoi(split_arr[3].c_str());
        id_func_rhs_arr_[itie] = atoi(split_arr[4].c_str());
        delete [] split_arr;
    }
    MiIolib::DelReadFile(line_arr);
}

void MimTie::Print(FILE* fp) const
{
    for(int itie = 0; itie < GetNtie(); itie ++){
        fprintf(fp, "%d  %d  =  %d  %d\n",
                GetIdDataLhsElm(itie),
                GetIdFuncLhsElm(itie),
                GetIdDataRhsElm(itie),
                GetIdFuncRhsElm(itie));
    }
}

MimTie* const MimTie::GenSel(const MimTie* const mim_tie,
                               const int* const nfunc_id_arr,
                               const int* const* const func_id_arr)
{
    MimTie* mim_tie_sel = new MimTie;
    int ntie = mim_tie->GetNtie();
    mim_tie_sel->Init(ntie);

    int* id_data_lhs_arr = new int [ntie];
    int* id_func_lhs_arr = new int [ntie];
    int* id_data_rhs_arr = new int [ntie];
    int* id_func_rhs_arr = new int [ntie];
    for(int itie = 0; itie < ntie; itie ++){
        int id_data_lhs = mim_tie->GetIdDataLhsElm(itie);
        id_data_lhs_arr[itie] = id_data_lhs;
        int ifunc_find = 0;
        for(int ifunc = 0; ifunc < nfunc_id_arr[id_data_lhs]; ifunc ++){
            if(mim_tie->GetIdFuncLhsElm(itie) == func_id_arr[id_data_lhs][ifunc]){
                ifunc_find = ifunc;
                break;
            }
        }
        id_func_lhs_arr[itie] = ifunc_find;
    }
    for(int itie = 0; itie < ntie; itie ++){
        int id_data_rhs = mim_tie->GetIdDataRhsElm(itie);
        id_data_rhs_arr[itie] = id_data_rhs;
        int ifunc_find = 0;
        for(int ifunc = 0; ifunc < nfunc_id_arr[id_data_rhs]; ifunc ++){
            if(mim_tie->GetIdFuncRhsElm(itie) == func_id_arr[id_data_rhs][ifunc]){
                ifunc_find = ifunc;
                break;
            }
        }
        id_func_rhs_arr[itie] = ifunc_find;
    }

    for(int itie = 0; itie < ntie; itie ++){
        mim_tie_sel->SetIdDataLhsElm(itie, id_data_lhs_arr[itie]);
        mim_tie_sel->SetIdFuncLhsElm(itie, id_func_lhs_arr[itie]);
        mim_tie_sel->SetIdDataRhsElm(itie, id_data_rhs_arr[itie]);
        mim_tie_sel->SetIdFuncRhsElm(itie, id_func_rhs_arr[itie]);
    }
    delete [] id_data_lhs_arr;
    delete [] id_func_lhs_arr;
    delete [] id_data_rhs_arr;
    delete [] id_func_rhs_arr;

    return mim_tie_sel;
}



//
// private
//

void MimTie::Null()
{
    if(NULL != id_data_lhs_arr_){ delete [] id_data_lhs_arr_;}
    if(NULL != id_func_lhs_arr_){ delete [] id_func_lhs_arr_;}
    if(NULL != id_data_rhs_arr_){ delete [] id_data_rhs_arr_;}
    if(NULL != id_func_rhs_arr_){ delete [] id_func_rhs_arr_;}
    ntie_ = 0;
}
