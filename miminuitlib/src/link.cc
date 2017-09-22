#include "mim_link.h"

//
// public
//

void MimLink::Init()
{
    ptr_ = NULL;
    val_ = 0;
}

void MimLink::SetLink(MimLink* link)
{
    ptr_ = link;
}

void MimLink::SetVal(int val)
{
    val_ = val;
}

void MimLink::Copy(const MimLink* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);

    Null();
    
    ptr_ = org->GetPtr();
    val_ = org->GetVal();
}


MimLink* const MimLink::Clone() const
{
    MimLink* obj_new = new MimLink;
    obj_new->Copy(this);
    return obj_new;
}


int MimLink::GetValLink() const
{
    int ret = 0;
    if(NULL == GetPtr()){
        ret = GetVal();
    } else {
        ret = GetPtr()->GetValLink();
    }
    return ret;
}


//
// private
//

void MimLink::Null()
{
    if(NULL != ptr_){
        ptr_ = NULL;
    }
    val_ = 0;
}
