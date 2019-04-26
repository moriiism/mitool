#include "mi_iolib.h"
#include "mir_vect.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;
    
//    void Init(double pos_x, double pos_y);
    {
        printf("--- test Init(double pos_x, double pos_y)\n");
        Vect2d* vect = new Vect2d("aaaa");
        vect->Init(1, 2);
        vect->Print(stdout);

        assert( "Vect2d" == vect->GetClassName() );
        assert( "aaaa" == vect->GetTitle() );
        assert( 1 == vect->GetPosX() );
        assert( 2 == vect->GetPosY() );

        delete vect;
        printf("=== \n");
    }
    
//    void Copy(const Vect2d* const org);
    {
        printf("--- test Copy(const Vect2d* const org)\n");
        Vect2d* vect = new Vect2d("org");
        vect->Init(1, 2);
        Vect2d* vect_new = new Vect2d("new");
        assert( "new" == vect_new->GetTitle() );
        
        vect_new->Copy(vect);
        vect_new->Print(stdout);

        assert( "Vect2d" == vect->GetClassName() );
        assert( "org" == vect->GetTitle() );
        assert( 1 == vect->GetPosX() );
        assert( 2 == vect->GetPosY() );

        assert( "Vect2d" == vect_new->GetClassName() );
        assert( "org" == vect_new->GetTitle() );
        assert( 1 == vect_new->GetPosX() );
        assert( 2 == vect_new->GetPosY() );
        
        delete vect;
        delete vect_new;
        printf("=== \n");
    }
   
//    Vect2d* const Clone() const;
    {
        printf("--- test Clone()\n");
        Vect2d* vect = new Vect2d("org");
        vect->Init(1, 2);
        assert( "Vect2d" == vect->GetClassName() );
        assert( "org" == vect->GetTitle() );
        assert( 1 == vect->GetPosX() );
        assert( 2 == vect->GetPosY() );

        Vect2d* vect_new = vect->Clone();
        vect_new->Print(stdout);

        assert( "Vect2d" == vect_new->GetClassName() );
        assert( "org" == vect_new->GetTitle() );
        assert( 1 == vect_new->GetPosX() );
        assert( 2 == vect_new->GetPosY() );

        delete vect;
        delete vect_new;
        
        printf("=== \n");
    }

//    double GetPosX() const {return pos_x_;};
//    double GetPosY() const {return pos_y_;};
//    double GetLength() const;    
    {
        printf("--- test GetPosX() GetPosY()\n");
        Vect2d* vect = new Vect2d("org");
        vect->Init(1, 2);

        printf("GetPosX: %e\n", vect->GetPosX());
        printf("GetPosY: %e\n", vect->GetPosY());
        printf("GetLength: %e\n", vect->GetLength());

        assert( "Vect2d" == vect->GetClassName() );
        assert( "org" == vect->GetTitle() );
        assert( 1 == vect->GetPosX() );
        assert( 2 == vect->GetPosY() );
        assert( sqrt( pow(1,2) + pow(2,2) ) == vect->GetLength() );

        delete vect;

        // sqrt(1**2 + 2**2) = 2.23606797749979
        printf("=== \n");
    }

//    Vect2d* const GenVectUnit() const;
    {
        printf("--- test GenVectUnit()\n");
        Vect2d* vect = new Vect2d("org");
        vect->Init(1, 2);

        assert( "Vect2d" == vect->GetClassName() );
        assert( "org" == vect->GetTitle() );
        assert( 1 == vect->GetPosX() );
        assert( 2 == vect->GetPosY() );
        
        Vect2d* vect_unit = vect->GenVectUnit();
        vect_unit->Print(stdout);
        printf("length = %e\n", vect_unit->GetLength());
        printf("length - 1 , DBL_EPSILON = %e, %e\n",
               vect_unit->GetLength() - 1, DBL_EPSILON);

        assert( "Vect2d" == vect_unit->GetClassName() );
        assert( "" == vect_unit->GetTitle() );
        assert( 1. / sqrt( pow(1,2) + pow(2,2) ) == vect_unit->GetPosX() );
        assert( 2. / sqrt( pow(1,2) + pow(2,2) ) == vect_unit->GetPosY() );
        assert( DBL_EPSILON > abs(vect_unit->GetLength() - 1.0));
        
        delete vect;
        delete vect_unit;

        // 0.447213590999916
        // 0.894427181999832
        printf("=== \n");
    }
    
//    Vect2d* const GenVectWithLength(double length) const;
    {
        printf("--- test GenVectWithLength(double length)\n");
        Vect2d* vect = new Vect2d;
        vect->Init(1, 2);
        double length = 2.0;
        Vect2d* vect_with_length = vect->GenVectWithLength(length);
        vect_with_length->Print(stdout);

        assert( "Vect2d" == vect_with_length->GetClassName() );
        assert( "" == vect_with_length->GetTitle() );
        assert( 1. / sqrt( pow(1,2) + pow(2,2) ) * 2.0 == vect_with_length->GetPosX() );
        assert( 2. / sqrt( pow(1,2) + pow(2,2) ) * 2.0 == vect_with_length->GetPosY() );
        assert( DBL_EPSILON > abs(vect_with_length->GetLength() - 2.0));

        delete vect;
        delete vect_with_length;

        // 0.894427181999832
        // 1.78885436399966
        printf("=== \n");
    }

    printf("=== end ===\n");

    return status_prog;
}
