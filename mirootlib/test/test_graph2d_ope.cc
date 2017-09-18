#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_graph2d_ope.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    DataArray1d* const GenDa1dByLoad(string file, string format);    
    {
        printf("--- test GenDa1dByLoad(string file, string format)\n");
        DataArray1d* da1d = DataArray1dOpe::GenDa1dByLoad("data/test_data1d_nerr.dat", "x");
        printf("da1d->GetClassName() = %s\n", da1d->GetClassName().c_str());
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);

        assert( "DataArrayNerr1d" == da1d->GetClassName() );
        assert( 3 == da1d->GetNdata() );
        assert( 0 == da1d->GetFlagValSorted() );
        assert( 22 == da1d->GetValElm(0) );
        assert( 33 == da1d->GetValElm(1) );
        assert( 44 == da1d->GetValElm(2) );
        
        delete da1d;
        printf("=== \n");
    }
    
    return status_prog;
}

