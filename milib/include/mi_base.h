#ifndef MORIIISM_MITOOL_MILIB_BASE_H_
#define MORIIISM_MITOOL_MILIB_BASE_H_

#include "mi_par.h"

#define MPrintErr(msg)       (printf("ERROR: %s: %u: %s(): %s\n", \
                             __FILE__, __LINE__, __func__, msg))
#define MPrintWarn(msg)      (printf("WARNING: %s: %u: %s(): %s\n", \
                             __FILE__, __LINE__, __func__, msg))
#define MPrintInfo(msg)      (printf("INFO: %s: %u: %s(): %s\n", \
                             __FILE__, __LINE__, __func__, msg))
#define MPrintErrClass(msg)  (printf("ERROR: %s: %u: %s::%s():%s: %s\n", \
                             __FILE__, __LINE__, GetClassName().c_str(), \
                             __func__, GetTitle().c_str(), msg))
#define MPrintWarnClass(msg) (printf("WARNING: %s: %u: %s::%s():%s: %s\n", \
                             __FILE__, __LINE__, GetClassName().c_str(), \
                             __func__, GetTitle().c_str(), msg))
#define MPrintInfoClass(msg) (printf("INFO: %s: %u: %s::%s():%s: %s\n", \
                             __FILE__, __LINE__, GetClassName().c_str(), \
                             __func__, GetTitle().c_str(), msg))
#define MPrintErrVFunc       (MPrintErr("Wrong virtual function call."))

#include <string.h>
#include <typeinfo>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

using std::vector;
using std::map;
using std::multimap;
using std::make_pair;
using std::pair;
using std::type_info;
using std::istringstream;
using std::stringstream;
using std::isinf;

#include <getopt.h>

// see effective C++ section 6
class Uncopyable{
protected:
    Uncopyable(){}
    ~Uncopyable(){}
private:
    Uncopyable(const Uncopyable &);
    Uncopyable& operator=(const Uncopyable &);
};

class MiObject: private Uncopyable{
public:
    MiObject(string class_name, string title) :
        class_name_(class_name),
        title_(title) {}
    virtual ~MiObject() {
        NullMiObject();
    }

    virtual MiObject* const Clone() const = 0;
    
    string GetClassName() const {return class_name_;};
    string GetTitle() const {return title_;};

    void SetTitle(string title) {title_ = title;};
    // There is no SetClassName function, because
    // class_name_ should be set at the initialization.

protected:
    void CopyMiObject(const MiObject* const org);
    // class_name_ should not be copied.
    // only title_ is copied.
    
private:
    string class_name_;  
    string title_;

    void NullMiObject();
};

class MiArgBase: public MiObject{
public:
    MiArgBase(string class_name, string title) :
        MiObject(class_name, title) {}
    virtual ~MiArgBase() {}
    
    virtual void Init(int argc, char* argv[]) = 0;
    virtual void Print(FILE* fp) const = 0;

private:
    virtual void Null() = 0;
    virtual void SetOption(int argc, char* argv[], option* long_options) = 0;
    virtual void Usage(FILE* fp) const = 0;
};

#endif // MORIIISM_MITOOL_MILIB_BASE_H_
