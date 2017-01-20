#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_hist_info.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void InitSetByNbin(double lo, double up, long nbin);
    {
        printf("--- test InitSetByNbin(double lo, double up, long nbin);\n");
        HistInfo1d* hi1d = new HistInfo1d("hi1d");
        hi1d->InitSetByNbin(0, 5, 10);
        hi1d->Print(stdout);
        delete hi1d;
        printf("=== \n");
    }
    
//    void InitSetByWidth(double lo, double up, double bin_width, string mode);
    {
        printf("--- test InitSetByWidth(double lo, double up, double bin_width, string mode)\n");
        HistInfo1d* hi1d = new HistInfo1d("hi1d");
        hi1d->InitSetByWidth(0, 5, 0.1, "floor");
        hi1d->Print(stdout);
        delete hi1d;
        printf("=== \n");
    }
    
//    void InitSetByMidPoint(double md, double bin_width, double half_width, string mode);
    {
        printf("--- test InitSetByMidPoint\n");
        HistInfo1d* hi1d = new HistInfo1d("hi1d");
        hi1d->InitSetByMidPoint(5, 0.5, 5, "floor");
        hi1d->Print(stdout);
        delete hi1d;
        printf("=== \n");
    }
    
//    void Load(string file);
    {
        printf("--- test Load(string file)\n");
        HistInfo1d* hi1d = new HistInfo1d("hi1d");
        hi1d->Load("data/test_hist_info1d_1.dat");
        hi1d->Print(stdout);
        delete hi1d;
        printf("=== \n");
    }

    {
        printf("--- test Load(string file)\n");
        HistInfo1d* hi1d = new HistInfo1d("hi1d");
        hi1d->Load("data/test_hist_info1d_2.dat");
        hi1d->Print(stdout);
        delete hi1d;
        printf("=== \n");
    }

//    void Copy(const HistInfo1d* const org);
    {
        printf("--- test Copy(const HistInfo1d* const org)\n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 10);
        hi1d_1->Print(stdout);
        HistInfo1d* hi1d_2 = new HistInfo1d("hi1d_2");
        hi1d_2->Copy(hi1d_1);
        hi1d_2->Print(stdout);
        delete hi1d_1;
        delete hi1d_2;
        
        printf("=== \n");
    }
   
//    HistInfo1d* const Clone() const;
    {
        printf("--- test Clone()\n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 10);
        hi1d_1->Print(stdout);
        HistInfo1d* hi1d_2 = hi1d_1->Clone();
        hi1d_2->Print(stdout);
        delete hi1d_1;
        delete hi1d_2;
        
        printf("=== \n");
    }

//    long GetNbin() const {return nbin_;};
//    double GetLo() const {return lo_;};
//    double GetUp() const {return up_;};
    {
        printf("--- test GetNbin() , GetLo() , GetUp() \n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 10);
        printf("%e , %e , %ld\n",
               hi1d_1->GetLo(),
               hi1d_1->GetUp(),
               hi1d_1->GetNbin());
        delete hi1d_1;
        
        printf("=== \n");
    }
   
//    double GetMd() const;
    {
        printf("--- test GetMd() \n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 10);
        printf("%e \n",
               hi1d_1->GetMd());
        delete hi1d_1;
        
        printf("=== \n");
    }
    
//    double GetMdLog() const;
    {
        printf("--- test GetMdLog() \n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(1.0, 10.0, 10);
        printf("%e \n",
               hi1d_1->GetMdLog());
        delete hi1d_1;

        // 10**((log10(1.0) + log10(10.0))/2.) = 3.16227766016838
        printf("=== \n");
    }
   
//    double GetBinWidth() const;
    {
        printf("--- test GetBinWidth() \n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 10);
        printf("%e \n",
               hi1d_1->GetBinWidth());
        delete hi1d_1;

        printf("=== \n");
    }
    
//    double GetBinWidthLog(long ibin) const;
    {
        printf("--- test GetBinWidthLog(long ibin) \n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(1.0, 10.0, 2);
        printf("%e \n",
               hi1d_1->GetBinWidthLog(1));
        delete hi1d_1;

        // 10.0 - 10**((log10(1.0) + log10(10.0))/2.) = 6.83772233983162
        printf("=== \n");
    }

//    double GetFullWidth() const {return up_ - lo_;};
    {
        printf("--- test GetFullWidth() \n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
        printf("%e \n",
               hi1d_1->GetFullWidth());
        delete hi1d_1;

        printf("=== \n");
    }

//    long GetIbin(double val, string scale = "lin") const;
    {
        printf("--- test GetIbin(double val, string scale) \n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
        printf("%ld \n", hi1d_1->GetIbin(7.0));
        delete hi1d_1;

        printf("=== \n");
    }

//    {
//        printf("--- test GetIbin(double val, string scale) \n");
//        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
//        hi1d_1->InitSetByNbin(1.0, 10.0, 10);
//        printf("%ld \n", hi1d_1->GetIbin(7.0, "log"));
//        delete hi1d_1;
//
//        printf("=== \n");
//    }
    
    
//    double GetBinCenter(long ibin, string scale = "lin") const;
    {
        printf("--- test GetBinCenter(long ibin, string scale)\n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
        printf("%e \n", hi1d_1->GetBinCenter(1));
        delete hi1d_1;

        // 7.500000e+00 
        printf("=== \n");
    }

//    {
//        printf("--- test GetBinCenter(long ibin, string scale)\n");
//        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
//        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
//        printf("%e \n", hi1d_1->GetBinCenter(1, "log"));
//        delete hi1d_1;
//
//
//        printf("=== \n");
//    }

    
//    double GetBinLo(long ibin, string scale = "lin") const;
    {
        printf("--- test GetBinLo(long ibin, string scale)\n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
        printf("%e \n", hi1d_1->GetBinLo(1));
        delete hi1d_1;

        // 5.0
        printf("=== \n");
    }

//    {
//        printf("--- test GetBinLo(long ibin, string scale)\n");
//        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
//        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
//        printf("%e \n", hi1d_1->GetBinLo(1, "log"));
//        delete hi1d_1;
//
//
//        printf("=== \n");
//    }
   
   
//    double GetBinUp(long ibin, string scale = "lin") const;
    {
        printf("--- test GetBinUp(long ibin, string scale)\n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
        printf("%e \n", hi1d_1->GetBinUp(1));
        delete hi1d_1;

        // 10.0
        printf("=== \n");
    }

//    {
//        printf("--- test GetBinUp(long ibin, string scale)\n");
//        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
//        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
//        printf("%e \n", hi1d_1->GetBinUp(1, "log"));
//        delete hi1d_1;
//
//        printf("=== \n");
//    }

    
////    long GetIbin_WithHalfBinShifted(double val) const;
//    {
//        printf("--- test GetIbin_WithHalfBinShifted(double val)\n");
//        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
//        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
//        printf("%ld \n", hi1d_1->GetIbin_WithHalfBinShifted(3.0));
//        delete hi1d_1;
//
//        printf("=== \n");
//    }
    
    
//    void GenValArr(double** const val_arr_ptr,
//                    long* const nbin_ptr,
//                    string scale = "lin") const;
    {
        printf("--- test GenValArr\n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
        double* val_arr = NULL;
        long nbin = 0;
        hi1d_1->GenValArr(&val_arr, &nbin);
        printf("nbin = %ld\n", nbin);
        for(long ibin = 0; ibin < nbin; ibin ++){
            printf("val_arr[%ld] = %e\n", ibin, val_arr[ibin]);
        }
        delete [] val_arr;
        delete hi1d_1;

        // nbin = 2
        // val_arr[0] = 2.500000e+00
        // val_arr[1] = 7.500000e+00
        printf("=== \n");
    }
    
//    {
//        printf("--- test GenValArr\n");
//        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
//        hi1d_1->InitSetByNbin(1.0, 10.0, 2);
//        double* val_arr = NULL;
//        long nbin = 0;
//        hi1d_1->GenValArr(&val_arr, &nbin, "log");
//        printf("nbin = %ld\n", nbin);
//        for(long ibin = 0; ibin < nbin; ibin ++){
//            printf("val_arr[%ld] = %e\n", ibin, val_arr[ibin]);
//        }
//        delete [] val_arr;
//        delete hi1d_1;
//
//        printf("=== \n");
//    }


    
//    void GenValSerrArr(double** const val_serr_arr_ptr,
//                       long* const nbin_ptr,
//                       string scale = "lin") const;
    {
        printf("--- test GenValSerrArr\n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
        double* val_serr_arr = NULL;
        long nbin = 0;
        hi1d_1->GenValSerrArr(&val_serr_arr, &nbin);
        printf("nbin = %ld\n", nbin);
        for(long ibin = 0; ibin < nbin; ibin ++){
            printf("val_serr_arr[%ld] = %e\n", ibin, val_serr_arr[ibin]);
        }
        delete [] val_serr_arr;
        delete hi1d_1;

        // nbin = 2
        // val_arr[0] = 2.5
        // val_arr[1] = 2.5
        printf("=== \n");
    }

//    {
//        printf("--- test GenValSerrArr\n");
//        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
//        hi1d_1->InitSetByNbin(1.0, 10.0, 2);
//        double* val_serr_arr = NULL;
//        long nbin = 0;
//        hi1d_1->GenValSerrArr(&val_serr_arr, &nbin, "log");
//        printf("nbin = %ld\n", nbin);
//        for(long ibin = 0; ibin < nbin; ibin ++){
//            printf("val_serr_arr[%ld] = %e\n", ibin, val_serr_arr[ibin]);
//        }
//        delete [] val_serr_arr;
//        delete hi1d_1;
//
//        printf("=== \n");
//    }
//    

    
//    void GenValTerrArr(double** const val_terr_plus_arr_ptr,
//                       double** const val_terr_minus_arr_ptr,
//                       long* const nbin_ptr,
//                       string scale = "lin") const;  

    {
        printf("--- test GenValTerrArr\n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
        double* val_terr_plus_arr = NULL;
        double* val_terr_minus_arr = NULL;
        long nbin = 0;
        hi1d_1->GenValTerrArr(&val_terr_plus_arr, &val_terr_minus_arr, &nbin);
        printf("nbin = %ld\n", nbin);
        for(long ibin = 0; ibin < nbin; ibin ++){
            printf("val_terr_plus_arr[%ld] = %e , val_terr_minus_arr[%ld] = %e\n",
                   ibin, val_terr_plus_arr[ibin], ibin, val_terr_minus_arr[ibin]);
        }
        delete [] val_terr_plus_arr;
        delete [] val_terr_minus_arr;
        delete hi1d_1;

        // nbin = 2
        // val_terr_plus_arr[0] = 2.500000e+00 , val_terr_minus_arr[0] = -2.500000e+00
        // val_terr_plus_arr[1] = 2.500000e+00 , val_terr_minus_arr[1] = -2.500000e+00

        printf("=== \n");
    }

//    {
//        printf("--- test GenValTerrArr\n");
//        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
//        hi1d_1->InitSetByNbin(1.0, 10.0, 2);
//        double* val_terr_plus_arr = NULL;
//        double* val_terr_minus_arr = NULL;
//        long nbin = 0;
//        hi1d_1->GenValTerrArr(&val_terr_plus_arr, &val_terr_minus_arr, &nbin, "log");
//        printf("nbin = %ld\n", nbin);
//        for(long ibin = 0; ibin < nbin; ibin ++){
//            printf("val_terr_plus_arr[%ld] = %e , val_terr_minus_arr[%ld] = %e\n",
//                   ibin, val_terr_plus_arr[ibin], ibin, val_terr_minus_arr[ibin]);
//        }
//        delete [] val_terr_plus_arr;
//        delete [] val_terr_minus_arr;
//        delete hi1d_1;
//
//        printf("=== \n");
//    }

//    // offset_tag = "st", "md", "ed", "no"
//    double GetOffsetFromTag(string offset_tag) const;
    {
        printf("--- test GetOffsetFromTag(string offset_tag)\n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
        
        printf("st = %e\n", hi1d_1->GetOffsetFromTag("st"));
        printf("md = %e\n", hi1d_1->GetOffsetFromTag("md"));
        printf("ed = %e\n", hi1d_1->GetOffsetFromTag("ed"));
        printf("no = %e\n", hi1d_1->GetOffsetFromTag("no"));
        printf("val = %e\n", hi1d_1->GetOffsetFromTag("7.77"));        

        delete hi1d_1;

        // st = 0.000000e+00
        // md = 5.000000e+00
        // ed = 1.000000e+01
        // no = 0.000000e+00
        // val = 7.770000e+00
        printf("=== \n");
    }

//    void Print(FILE* fp) const;
    {
        printf("--- test GetOffsetFromTag(string offset_tag)\n");
        HistInfo1d* hi1d_1 = new HistInfo1d("hi1d_1");
        hi1d_1->InitSetByNbin(0.0, 10.0, 2);
        hi1d_1->Print(stdout);

        delete hi1d_1;

        printf("=== \n");
    }
    

//    void IsValidForLogScale() const;    
//    void IsValidIbin(long ibin) const;
//    void IsValidRange(double val) const;
//
//    //
//    // static
//    //
//    static void SetHistInfo(string line, HistInfo1d* const hist_info_out);

    
    return status_prog;
}
