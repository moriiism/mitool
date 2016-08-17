#include "mi_base.h"

//
// MiObject
//

// public

void MiObject::CopyMiObject(const MiObject* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}

    title_      = org->title_;
}

// private

void MiObject::NullMiObject()
{
    class_name_ = "";
    title_      = "";
}

