#include "mi_base.h"
#include "mi_rand.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

    // void Init(long seed);
    // double Uniform(void);    
    {
        int ndat = 100;
        MiRand::Init(2);
        FILE* fp = fopen("out.dat", "w");
        for(int idat = 0; idat < ndat; idat ++){
            double rand = MiRand::Uniform();
            fprintf(fp, "%e\n", rand);
        }
        fclose(fp);
    }
    
    // double Normal(double mu, double sigma);
    {
        double mu = 10.0;
        double sigma = 2.0;
        int ndat = 100;
        MiRand::Init(2);
        FILE* fp = fopen("out.dat", "w");
        for(int idat = 0; idat < ndat; idat ++){
            double rand = MiRand::Normal(mu, sigma);
            fprintf(fp, "%e\n", rand);
        }
        fclose(fp);
    }
    

   
    return status_prog;
}
