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
//    double GetBinLo(long ibin, string scale = "lin") const;
//    double GetBinUp(long ibin, string scale = "lin") const;
//    long GetIbin_WithHalfBinShifted(double val) const;
//    
//    void GenValArr(double** const val_arr_ptr,
//                    long* const nbin_ptr,
//                    string scale = "lin") const;
//    void GenValSerrArr(double** const val_serr_arr_ptr,
//                       long* const nbin_ptr,
//                       string scale = "lin") const;
//    void GenValTerrArr(double** const val_terr_plus_arr_ptr,
//                       double** const val_terr_minus_arr_ptr,
//                       long* const nbin_ptr,
//                       string scale = "lin") const;  
//    
//    // offset_tag = "st", "md", "ed", "no"
//    double GetOffsetFromTag(string offset_tag) const;
//    
//    void Print(FILE* fp) const;
//
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
