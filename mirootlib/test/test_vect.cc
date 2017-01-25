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
        Vect2d* vect = new Vect2d;
        vect->Init(1, 2);
        vect->Print(stdout);

        delete vect;

        printf("=== \n");
    }
    
//    void Copy(const Vect2d* const org);
    {
        printf("--- test Copy(const Vect2d* const org)\n");
        Vect2d* vect = new Vect2d;
        vect->Init(1, 2);
        Vect2d* vect_new = new Vect2d;
        vect_new->Copy(vect);
        vect_new->Print(stdout);

        delete vect;
        delete vect_new;
        
        printf("=== \n");
    }
   
//    Vect2d* const Clone() const;
    {
        printf("--- test Clone()\n");
        Vect2d* vect = new Vect2d;
        vect->Init(1, 2);

        Vect2d* vect_new = vect->Clone();
        vect_new->Print(stdout);

        delete vect;
        delete vect_new;
        
        printf("=== \n");
    }

//    double GetPosX() const {return pos_x_;};
//    double GetPosY() const {return pos_y_;};
//    double GetLength() const;    
    {
        printf("--- test GetPosX() GetPosY()\n");
        Vect2d* vect = new Vect2d;
        vect->Init(1, 2);

        printf("GetPosX: %e\n", vect->GetPosX());
        printf("GetPosY: %e\n", vect->GetPosY());
        printf("GetLength: %e\n", vect->GetLength());

        delete vect;

        // sqrt(1**2 + 2**2) = 2.23606797749979
        printf("=== \n");
    }

//    Vect2d* const GenVectUnit() const;
    {
        printf("--- test GenVectUnit()\n");
        Vect2d* vect = new Vect2d;
        vect->Init(1, 2);
        Vect2d* vect_unit = vect->GenVectUnit();
        vect_unit->Print(stdout);

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
        Vect2d* vect_unit = vect->GenVectWithLength(length);
        vect_unit->Print(stdout);

        delete vect;
        delete vect_unit;

        // 0.894427181999832
        // 1.78885436399966
        printf("=== \n");
    }

    return status_prog;
}
