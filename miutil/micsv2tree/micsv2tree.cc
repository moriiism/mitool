#include "TFile.h"
#include "TTree.h"
#include "TMath.h"

#include "mi_iolib.h"
#include "mir_math.h"

#include "arg_micsv2tree.h"
#include "sub.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMicsv2tree* argval = new ArgValMicsv2tree;
    argval->Init(argc, argv);
    argval->Print(stdout);

    TTreeFormat* treefmt = new TTreeFormat;
    treefmt->Load(argval->GetFormat());
    treefmt->Print();
    
    int* nval_type_arr = new int [kNType];
    for(int itype = 0; itype < kNType; itype ++){
        nval_type_arr[itype] = treefmt->GetNumOfType(kTypeArr[itype]);
    }

    UChar_t*  val_UChar_t_arr  = NULL;
    Short_t*  val_Short_t_arr  = NULL;
    Int_t*    val_Int_t_arr    = NULL;
    Long64_t* val_Long64_t_arr = NULL;
    Float_t*  val_Float_t_arr  = NULL;
    Double_t* val_Double_t_arr = NULL;
    
    int itype = 0;
    if(0 != nval_type_arr[itype]){
        val_UChar_t_arr = new UChar_t [nval_type_arr[itype]];
    }
    
    itype ++;
    if(0 != nval_type_arr[itype]){
        val_Short_t_arr = new Short_t [nval_type_arr[itype]];
    }

    itype ++;
    if(0 != nval_type_arr[itype]){
        val_Int_t_arr = new Int_t [nval_type_arr[itype]];
    }

    itype ++;
    if(0 != nval_type_arr[itype]){
        val_Long64_t_arr = new Long64_t [nval_type_arr[itype]];
    }
    
    itype ++;
    if(0 != nval_type_arr[itype]){
        val_Float_t_arr = new Float_t [nval_type_arr[itype]];
    }

    itype ++;
    if(0 != nval_type_arr[itype]){
        val_Double_t_arr = new Double_t [nval_type_arr[itype]];
    }

    TFile* tfile = new TFile(argval->GetOutfile().c_str(), "RECREATE", "tmp");
    TTree* tree = new TTree("DATA", "DATA");
    
    for(int ival = 0; ival < treefmt->GetNval(); ival++){
        if(kTypeArr[0] == treefmt->GetTypeArrElm(ival)){
            tree->Branch(treefmt->GetValnameArrElm(ival).c_str(),
                         &val_UChar_t_arr[treefmt->GetIndexInTypeArrElm(ival)]);

        } else if(kTypeArr[1] == treefmt->GetTypeArrElm(ival)){
            tree->Branch(treefmt->GetValnameArrElm(ival).c_str(),
                         &val_Short_t_arr[treefmt->GetIndexInTypeArrElm(ival)]);

        } else if(kTypeArr[2] == treefmt->GetTypeArrElm(ival)){
            tree->Branch(treefmt->GetValnameArrElm(ival).c_str(),
                         &val_Int_t_arr[treefmt->GetIndexInTypeArrElm(ival)]);
            
        } else if(kTypeArr[3] == treefmt->GetTypeArrElm(ival)){
            tree->Branch(treefmt->GetValnameArrElm(ival).c_str(),
                         &val_Long64_t_arr[treefmt->GetIndexInTypeArrElm(ival)]);
            
        } else if(kTypeArr[4] == treefmt->GetTypeArrElm(ival)){
            tree->Branch(treefmt->GetValnameArrElm(ival).c_str(),
                         &val_Float_t_arr[treefmt->GetIndexInTypeArrElm(ival)]);
            
        } else if(kTypeArr[5] == treefmt->GetTypeArrElm(ival)){
            tree->Branch(treefmt->GetValnameArrElm(ival).c_str(),
                         &val_Double_t_arr[treefmt->GetIndexInTypeArrElm(ival)]);
        } else {
            printf("error\n");
            exit(1);
        }
    }
    
    //
    // data file
    //
    long nline;
    string* data_file_line_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetInfile(),
                                    &data_file_line_arr, &nline);
    printf("nline = %ld\n", nline);
    for(long iline = 0; iline < nline; iline ++){
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(data_file_line_arr[iline], &nsplit, &split_arr,
                          argval->GetDelimit().c_str());
        // printf("nsplit = %d\n", nsplit);
        for(int isplit = 0; isplit < treefmt->GetNval(); isplit++){
            if(kTypeArr[0] == treefmt->GetTypeArrElm(isplit)){
                val_UChar_t_arr[treefmt->GetIndexInTypeArrElm(isplit)]
                    = (UChar_t) split_arr[isplit].c_str()[0];
                
            } else if(kTypeArr[1] == treefmt->GetTypeArrElm(isplit)){
                val_Short_t_arr[treefmt->GetIndexInTypeArrElm(isplit)]
                    = (Short_t) atoi(split_arr[isplit].c_str());
                
            } else if(kTypeArr[2] == treefmt->GetTypeArrElm(isplit)){
                val_Int_t_arr[treefmt->GetIndexInTypeArrElm(isplit)]
                    = (Int_t) atoi(split_arr[isplit].c_str());
                
            } else if(kTypeArr[3] == treefmt->GetTypeArrElm(isplit)){
                val_Long64_t_arr[treefmt->GetIndexInTypeArrElm(isplit)]
                    = (Long64_t) atol(split_arr[isplit].c_str());
                
            } else if(kTypeArr[4] == treefmt->GetTypeArrElm(isplit)){
                val_Float_t_arr[treefmt->GetIndexInTypeArrElm(isplit)]
                    = (Float_t) atof(split_arr[isplit].c_str());
                
            } else if(kTypeArr[5] == treefmt->GetTypeArrElm(isplit)){
                val_Double_t_arr[treefmt->GetIndexInTypeArrElm(isplit)]
                    = (Double_t) atof(split_arr[isplit].c_str());
                
            } else {
                printf("error\n");
                exit(1);
            }
        }
        tree->Fill();
        delete [] split_arr;
    }
    MiIolib::DelReadFile(data_file_line_arr);

    tfile->Write();
    tree->Delete();
    delete tfile;
    delete argval;
    
    return status;
}

