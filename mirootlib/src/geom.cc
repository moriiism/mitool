#include "mir_geom.h"

Vect2d* MirGeom::GenShift(const Vect2d* const vect,
                          double shiftx, double shifty, int flag)
{
    Vect2d* vect_new = new Vect2d;
    vect_new->Init(vect->GetPosX() + flag * shiftx,
                   vect->GetPosY() + flag * shifty);
    return vect_new;
}

Vect2d* MirGeom::GenRot(const Vect2d* const vect,
                        double angle, int flag)
{
    double posx_new =
        + cos(flag * angle) * vect->GetPosX() +
        - sin(flag * angle) * vect->GetPosY();
    double posy_new =
        + sin(flag * angle) * vect->GetPosX() +
        + cos(flag * angle) * vect->GetPosY();
    Vect2d* vect_new = new Vect2d;
    vect_new->Init(posx_new, posy_new);
    return vect_new;
}

// 1: shift, 2: rot
Vect2d* MirGeom::GenMotion(const Vect2d* const vect,
                           double shiftx, double shifty,
                           double angle, int flag)
{
    Vect2d* vect_shift = GenShift(vect, shiftx, shifty, flag);
    Vect2d* vect_mot = GenRot(vect_shift, angle, flag);
    delete vect_shift;
    return vect_mot;
}


