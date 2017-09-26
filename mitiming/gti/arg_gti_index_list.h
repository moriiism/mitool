#ifndef MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_INDEX_LIST_H_
#define MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_INDEX_LIST_H_

#include "mi_base.h"

class ArgValGtiIndexList : public MiArgBase{
public:
    ArgValGtiIndexList() :
        MiArgBase(),
        progname_(""),
        gti_(""),
        time_list_(""),
        index_list_out_("") {}
    ~ArgValGtiIndexList(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetGti() const {return gti_;};
    string GetTimeList() const {return time_list_;};
    string GetIndexListOut() const {return index_list_out_;};

private:
    string progname_;
    string gti_;
    string time_list_;
    string index_list_out_;
    
    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MORIIISM_MITOOL_MITIMING_GTI_ARG_GTI_INDEX_LIST_H_
