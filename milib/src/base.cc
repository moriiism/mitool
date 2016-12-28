#include "mi_base.h"

//
// MiObject
//

// protected

void MiObject::CopyMiObject(const MiObject* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}

    // class_name_ should not be copied.
    // only title_ is copied.
    title_      = org->title_;
}

// private

void MiObject::NullMiObject()
{
    class_name_ = "";
    title_      = "";
}

