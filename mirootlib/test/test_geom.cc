#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_geom.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    Vect2d* GenShift(const Vect2d* const vect,
//                     double shiftx, double shifty, int flag);
    {
        printf("--- test GenShift, flag = 1\n");

        Vect2d* vect = new Vect2d;
        double posx = 1.0;
        double posy = 2.0;
        vect->Init(posx, posy);
        vect->Print(stdout);

        double shiftx = 10.0;
        double shifty = 20.0;
        int flag = 1;
        Vect2d* vect_new = MirGeom::GenShift(vect, shiftx, shifty, flag);
        vect_new->Print(stdout);

        assert( fabs( (posx + shiftx) - vect_new->GetPosX() ) < DBL_EPSILON );
        assert( fabs( (posy + shifty) - vect_new->GetPosY() ) < DBL_EPSILON );
        
        delete vect;
        delete vect_new;
        printf("=== \n");
    }

    {
        printf("--- test GenShift, flag = -1\n");

        Vect2d* vect = new Vect2d;
        double posx = 1.0;
        double posy = 2.0;
        vect->Init(posx, posy);
        vect->Print(stdout);

        double shiftx = 10.0;
        double shifty = 20.0;
        int flag = -1;
        Vect2d* vect_new = MirGeom::GenShift(vect, shiftx, shifty, flag);
        vect_new->Print(stdout);

        assert( fabs( (posx - shiftx) - vect_new->GetPosX() ) < DBL_EPSILON );
        assert( fabs( (posy - shifty) - vect_new->GetPosY() ) < DBL_EPSILON );
        
        delete vect;
        delete vect_new;
        printf("=== \n");
    }

//    Vect2d* GenRot(const Vect2d* const vect,
//                   double angle, int flag);
    {
        printf("--- test GenRot, flag = 1\n");

        Vect2d* vect = new Vect2d;
        double posx = 1.0;
        double posy = 2.0;
        vect->Init(posx, posy);
        vect->Print(stdout);

        double angle = M_PI / 4.0;
        int flag = 1;
        Vect2d* vect_new = MirGeom::GenRot(vect, angle, flag);
        vect_new->Print(stdout);

        double posx_new = cos(angle) * posx - sin(angle) * posy;
        double posy_new = sin(angle) * posx + cos(angle) * posy;

        assert( fabs( posx_new - vect_new->GetPosX() ) < DBL_EPSILON );
        assert( fabs( posy_new - vect_new->GetPosY() ) < DBL_EPSILON );
        
        delete vect;
        delete vect_new;
        printf("=== \n");
    }

    {
        printf("--- test GenRot, flag = -1\n");

        Vect2d* vect = new Vect2d;
        double posx = 1.0;
        double posy = 2.0;
        vect->Init(posx, posy);
        vect->Print(stdout);

        double angle = M_PI / 4.0;
        int flag = -1;
        Vect2d* vect_new = MirGeom::GenRot(vect, angle, flag);
        vect_new->Print(stdout);

        double posx_new = cos(angle) * posx + sin(angle) * posy;
        double posy_new = -1 * sin(angle) * posx + cos(angle) * posy;

        assert( fabs( posx_new - vect_new->GetPosX() ) < DBL_EPSILON );
        assert( fabs( posy_new - vect_new->GetPosY() ) < DBL_EPSILON );
        
        delete vect;
        delete vect_new;
        printf("=== \n");
    }

//    Vect2d* GenMotion(const Vect2d* const vect,
//                      double shiftx, double shifty,
//                      double angle, int flag);
    {
        printf("--- test GenMotion, flag = 1\n");

        Vect2d* vect = new Vect2d;
        double posx = 1.0;
        double posy = 2.0;
        vect->Init(posx, posy);
        vect->Print(stdout);

        double shiftx = 10.0;
        double shifty = 20.0;
        double angle = M_PI / 4.0;
        int flag = 1;
        Vect2d* vect_new = MirGeom::GenMotion(vect, shiftx, shifty, angle, flag);
        vect_new->Print(stdout);

        double posx_new1 = posx + shiftx;
        double posy_new1 = posy + shifty;
        double posx_new2 = cos(angle) * posx_new1 - sin(angle) * posy_new1;
        double posy_new2= sin(angle) * posx_new1 + cos(angle) * posy_new1;

        assert( fabs( posx_new2 - vect_new->GetPosX() ) < DBL_EPSILON );
        assert( fabs( posy_new2 - vect_new->GetPosY() ) < DBL_EPSILON );
        
        delete vect;
        delete vect_new;
        printf("=== \n");
    }

    {
        printf("--- test GenMotion, flag = -1\n");

        Vect2d* vect = new Vect2d;
        double posx = 1.0;
        double posy = 2.0;
        vect->Init(posx, posy);
        vect->Print(stdout);

        double shiftx = 10.0;
        double shifty = 20.0;
        double angle = M_PI / 4.0;
        int flag = -1;
        Vect2d* vect_new = MirGeom::GenMotion(vect, shiftx, shifty, angle, flag);
        vect_new->Print(stdout);

        double posx_new1 = posx - shiftx;
        double posy_new1 = posy - shifty;
        double posx_new2 = cos(angle) * posx_new1 + sin(angle) * posy_new1;
        double posy_new2= -1 * sin(angle) * posx_new1 + cos(angle) * posy_new1;

        assert( fabs( posx_new2 - vect_new->GetPosX() ) < DBL_EPSILON );
        assert( fabs( posy_new2 - vect_new->GetPosY() ) < DBL_EPSILON );
        
        delete vect;
        delete vect_new;
        printf("=== \n");
    }
    
    
    return status_prog;
}
