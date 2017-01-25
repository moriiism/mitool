#ifndef MORIIISM_MITOOL_MIROOTLIB_GEOM_H_
#define MORIIISM_MITOOL_MIROOTLIB_GEOM_H_

#include "mir_vect.h"

// function of conversion is for coordinate.

namespace MirGeom
{
    // flag: -1: coordinate
    //        1: object
    Vect2d* GenShift(const Vect2d* const vect,
                     double shiftx, double shifty, int flag);
    Vect2d* GenRot(const Vect2d* const vect,
                   double angle, int flag);
    Vect2d* GenMotion(const Vect2d* const vect,
                      double shiftx, double shifty,
                      double angle, int flag);
}

#endif // MORIIISM_MITOOL_MIROOTLIB_GEOM_H_
