#include "mi_iolib.h"
#include "mir_qdp_tool.h"
#include "arg_miselcol.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMiselcol* argval = new ArgValMiselcol;
    argval->Init(argc, argv);
    argval->Print(stdout);

    int nindex_sel = 0;
    string* index_sel_str_arr = NULL;
    MiStr::GenSplit(argval->GetSelcol(),
                    &nindex_sel, &index_sel_str_arr, ",");
    int* index_sel_arr = new int [nindex_sel];
    for(int index_sel = 0; index_sel < nindex_sel; index_sel++){
        index_sel_arr[index_sel] = atoi(index_sel_str_arr[index_sel].c_str());
        printf("index_sel_arr = %d\n", index_sel_arr[index_sel]);
    }
    
    string* lines_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(argval->GetInfile(),
                                    &lines_arr,
                                    &nline);
    printf("nline = %ld\n", nline);
    FILE* fp = fopen(argval->GetOutfile().c_str(), "w");
    for(long iline = 0; iline < nline; iline ++){
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(lines_arr[iline], &nsplit, &split_arr);

        for(int index_sel = 0; index_sel < nindex_sel; index_sel++){
            int icol = index_sel_arr[index_sel];
            fprintf(fp, "%s  ", split_arr[icol].c_str());
        }
        fprintf(fp, "\n");
        delete [] split_arr;
    }
    fclose(fp);

    delete [] index_sel_str_arr;
    delete [] index_sel_arr;
    delete [] lines_arr;
    delete argval;
    return status;
}
