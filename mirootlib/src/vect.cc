#include "mir_vect.h"

// public

void Vect2d::Init(double pos_x, double pos_y)
{
    Null();
    pos_x_ = pos_x;
    pos_y_ = pos_y;
}

void Vect2d::Copy(const Vect2d* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    Init(org->GetPosX(), org->GetPosY());
}

Vect2d* const Vect2d::Clone() const
{
    Vect2d* obj_new = new Vect2d;
    obj_new->Copy(this);
    return obj_new;
}

double Vect2d::GetLength() const
{
    double length = sqrt(pow(GetPosX(), 2.) +
                         pow(GetPosY(), 2.));
    return length;
}

Vect2d* const Vect2d::GenVectUnit() const
{
    Vect2d* vect = new Vect2d;
    double posx = GetPosX() / GetLength();
    double posy = GetPosY() / GetLength();
    vect->Init(posx, posy);
    return vect;
}

Vect2d* const Vect2d::GenVectWithLength(double length) const
{
    Vect2d* vect = new Vect2d;
    double posx = GetPosX() / GetLength() * length;
    double posy = GetPosY() / GetLength() * length;
    vect->Init(posx, posy);
    return vect;
}

void Vect2d::Print(FILE* fp) const
{
    fprintf(fp, "%e  %e\n", GetPosX(), GetPosY());
}

// private
void Vect2d::Null()
{
    pos_x_ = 0.0;
    pos_y_ = 0.0;
}
