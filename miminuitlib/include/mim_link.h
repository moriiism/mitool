#ifndef MORIIISM_MITOOL_MIMINUITLIB_LINK_H_
#define MORIIISM_MITOOL_MIMINUITLIB_LINK_H_

#include "mi_iolib.h"

class MimLink : public MiObject{
public:
    explicit MimLink(string title = ""):
        MiObject("MimLink", title),
        ptr_(NULL),
        val_(0) {}
    ~MimLink(){
        Null();
    }
    void Init();
    void SetLink(MimLink* link);
    void SetVal(int val);

    void Copy(const MimLink* const org);
    MimLink* const Clone() const;

    //
    // const functions
    //
    MimLink* GetPtr() const {return ptr_;};
    int GetValLink() const;
    
private:
    MimLink* ptr_;
    int val_;

    void Null();
    int GetVal() const {return val_;};
};

#endif // MORIIISM_MITOOL_MIMINUITLIB_LINK_H_
