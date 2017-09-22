#include "mim_func_par_index.h"

//
// func_lincomb_par_index
//

// public

void MimFuncLincombParIndex::InitSet(int nfile,
                                      const LinCombFunc* const* const func_lincomb_arr,
                                      const MimTie* const mim_tie)
{
    Null();

    nfile_                = nfile;
    nfunc_arr_            = new int [nfile];
    npar_base_arr_        = new int* [nfile];
    index_base_arr_       = new MimLink*** [nfile];
    npar_coeff_arr_       = new int [nfile];
    index_coeff_arr_      = new MimLink** [nfile];

    for(int ifile = 0; ifile < nfile; ifile ++){
        nfunc_arr_[ifile]      = func_lincomb_arr[ifile]->GetNfunc();

        // base
        npar_base_arr_[ifile]       = new int  [ nfunc_arr_[ifile] ];
        index_base_arr_[ifile]      = new MimLink** [ nfunc_arr_[ifile] ];
        for(int ifunc = 0; ifunc < nfunc_arr_[ifile]; ifunc ++){
            npar_base_arr_[ifile][ifunc]
                = func_lincomb_arr[ifile]->GetFuncObjArrElm(ifunc)->GetNpar();
            index_base_arr_[ifile][ifunc]      = new MimLink* [ npar_base_arr_[ifile][ifunc] ];
            for(int ipar = 0; ipar < npar_base_arr_[ifile][ifunc]; ipar ++){
                index_base_arr_[ifile][ifunc][ipar] = new MimLink;
            }
        }

        // coeff
        npar_coeff_arr_[ifile]     = nfunc_arr_[ifile];
        index_coeff_arr_[ifile]     = new MimLink* [ npar_coeff_arr_[ifile] ];
        for(int ipar = 0; ipar < npar_coeff_arr_[ifile]; ipar ++){
            index_coeff_arr_[ifile][ipar] = new MimLink;
        }
    }

    for(int itie = 0; itie < mim_tie->GetNtie(); itie ++){
        int ifile_lhs = mim_tie->GetIdDataLhsElm(itie);
        int ifunc_lhs = mim_tie->GetIdFuncLhsElm(itie);        
        int ifile_rhs = mim_tie->GetIdDataRhsElm(itie);
        int ifunc_rhs = mim_tie->GetIdFuncRhsElm(itie);

        printf("ifile_lhs ifunc_lhs = ifile_rhs ifunc_rhs: %d %d %d %d\n",
               ifile_lhs, ifunc_lhs, ifile_rhs, ifunc_rhs);
        
        for(int ipar = 0; ipar < npar_base_arr_[ifile_rhs][ifunc_rhs]; ipar ++){
            index_base_arr_[ifile_rhs][ifunc_rhs][ipar]->SetLink(
                index_base_arr_[ifile_lhs][ifunc_lhs][ipar]);
        }
        index_coeff_arr_[ifile_rhs][ifunc_rhs]->SetLink(
            index_coeff_arr_[ifile_lhs][ifunc_lhs]);
    }

    int ipar_tot = 0;
    for(int ifile = 0; ifile < nfile; ifile ++){
        // base
        for(int ifunc = 0; ifunc < nfunc_arr_[ifile]; ifunc ++){
            for(int ipar = 0; ipar < npar_base_arr_[ifile][ifunc]; ipar ++){
                if(NULL == index_base_arr_[ifile][ifunc][ipar]->GetPtr()){
                    index_base_arr_[ifile][ifunc][ipar]->SetVal(ipar_tot);
                    ipar_tot ++;
                }
            }
        }
        // coeff
        for(int ipar = 0; ipar < npar_coeff_arr_[ifile]; ipar ++){
            if(NULL == index_coeff_arr_[ifile][ipar]->GetPtr()){
                index_coeff_arr_[ifile][ipar]->SetVal(ipar_tot);
                ipar_tot ++;
            }
        }
    }
    npar_total_ = ipar_tot;
}


void MimFuncLincombParIndex::Print(FILE* fp) const
{
    fprintf(fp, "nfile_ = %d\n", GetNfile());
    for(int ifile = 0; ifile < GetNfile(); ifile ++){
        fprintf(fp, "GetNfuncArrElm(%d) = %d\n", ifile, GetNfuncArrElm(ifile));
    }
    for(int ifile = 0; ifile < GetNfile(); ifile ++){
        for(int ifunc = 0; ifunc < GetNfuncArrElm(ifile); ifunc ++){
            fprintf(fp, "GetNparBaseArrElm(%d, %d) = %d\n",
                    ifile, ifunc, GetNparBaseArrElm(ifile, ifunc));
        }
        fprintf(fp, "GetNparCoeffArrElm(%d) = %d\n", ifile, GetNparCoeffArrElm(ifile));
    }
    for(int ifile = 0; ifile < GetNfile(); ifile ++){
        for(int ifunc = 0; ifunc < GetNfuncArrElm(ifile); ifunc ++){
            for(int ipar = 0; ipar < GetNparBaseArrElm(ifile, ifunc); ipar ++){
                fprintf(fp, "GetIndexBaseArrElm(%d, %d, %d) = %d\n",
                        ifile, ifunc, ipar, GetIndexBaseArrElm(ifile, ifunc, ipar)->GetValLink());
            }
        }
        for(int ifunc = 0; ifunc < GetNfuncArrElm(ifile); ifunc ++){
            fprintf(fp, "GetIndexCoeffArrElm(%d, %d) = %d\n",
                    ifile, ifunc, GetIndexCoeffArrElm(ifile, ifunc)->GetValLink());
        }
    }
    fprintf(fp, "npar_total_ = %d\n", GetNparTotal());
}




//
// private
//


void MimFuncLincombParIndex::Null()
{
    if(NULL != index_base_arr_){
        for(int ifile = 0; ifile < nfile_; ifile ++){
            if(NULL != index_base_arr_[ifile]){
                for(int ifunc = 0; ifunc < nfunc_arr_[ifile]; ifunc ++){
                    if(NULL != index_base_arr_[ifile][ifunc]){
                        delete [] index_base_arr_[ifile][ifunc];
                    }
                }
                delete [] index_base_arr_[ifile];
            }
        }
        delete [] index_base_arr_;
    }
    if(NULL != npar_base_arr_){
        for(int ifile = 0; ifile < nfile_; ifile ++){
            if(NULL != npar_base_arr_[ifile]){
                delete [] npar_base_arr_[ifile];
            }
        }
        delete [] npar_base_arr_;
    }
    
    if(NULL != index_coeff_arr_){
        for(int ifile = 0; ifile < nfile_; ifile ++){
            if(NULL != index_coeff_arr_[ifile]){
                delete [] index_coeff_arr_[ifile];
            }
        }
        delete [] index_coeff_arr_;
    }

    if(NULL != npar_coeff_arr_){
        delete [] npar_coeff_arr_;
    }

    if(NULL != nfunc_arr_){
        delete [] nfunc_arr_;
    }

    nfile_ = 0;
    npar_total_ = 0;
}




