#include "mir_math.h"
#include "arg_minfold.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMinfold* argval = new ArgValMinfold;
    argval->Init(argc, argv);

    long num   = argval->GetNum();
    long nfold = argval->GetNfold();

    //printf("# num: %ld \n", num);
    //printf("# nfold: %ld \n", nfold);
    
    //printf("# ndata in one  segment: %ld \n", num/nfold);
    //printf("# ndata in last segment: %ld \n", num/nfold + num % nfold);

    long res_threshold = 10;
    long nfold_find = nfold;
    long delta_nfold_max = MirMath::GetMax( num - nfold, nfold - 1);
    //printf("delta_nfold_max = %ld\n", delta_nfold_max);
    for(long delta_nfold = 0; delta_nfold < delta_nfold_max; delta_nfold ++){

        long nfold_plus = nfold + delta_nfold;
        long quo_plus = num / nfold_plus;
        long res_plus = num % nfold_plus;
        long nfold_minus = nfold - delta_nfold;
        long quo_minus = num / nfold_minus;
        long res_minus = num % nfold_minus;
        //printf("quo_plus  = %ld, res_plus  = %ld\n", quo_plus, res_plus);
        //printf("quo_minus = %ld, res_minus = %ld\n", quo_minus, res_minus);
        if(quo_plus <= res_plus && quo_minus <= res_minus){
            continue;
        }
        //printf("delta_nfold = %ld, res_plus = %ld, res_minus = %ld\n",
        //       delta_nfold, res_plus, res_minus);
        
        // we select nfold_minus rather than nfold_plus,
        // if residual is the same.
        if(quo_minus > res_minus){
            if(1 <= nfold_minus){
                if(res_threshold >= res_minus){
                    nfold_find = nfold_minus; 
                    break;
                }
            }
        }
        if(quo_plus > res_plus){
            if(nfold_plus <= num){
                if(res_threshold >= res_plus){
                    nfold_find = nfold_plus; 
                    break;
                }
            }
        }
        
        
    }

    printf("# ndata in one  segment: %ld \n", num/nfold_find);
    printf("# ndata in last segment: %ld = %ld + %ld\n",
           num/nfold_find + num % nfold_find, num/nfold_find, num % nfold_find);
    printf("nfold_find = %ld\n", nfold_find);
    
    delete argval;
    
    return status;
}

