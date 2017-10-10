#include "mi_base.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

class TestObject: public MiObject{
public:
    explicit TestObject(string title = "") :
        MiObject("TestObject", title),
        member_("") {}
    ~TestObject() {
        Null();
    }
    void Set(string member) {member_ = member;};
    void Copy(const TestObject* const org);
    TestObject* const Clone() const;
    
    string GetMember() const {return member_;};

    void TestPrintErrWarnInfo() const;

private:
    string member_;
    void Null();
};

void TestObject::Copy(const TestObject* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}

    CopyTitle(org);
    Null();
    Set(org->GetMember());
}

TestObject* const TestObject::Clone() const
{
    TestObject* obj_new = new TestObject;
    obj_new->Copy(this);
    return obj_new;
}

void TestObject::TestPrintErrWarnInfo() const
{
    MPrintErrClass("aaa");
    MPrintWarnClass("bbb");
    MPrintInfoClass("ccc");
}

void TestObject::Null()
{
    member_ = "";
}


int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

   
// MPrintErr(msg)
// MPrintWarn(msg)
// MPrintInfo(msg)
// MPrintErrVFunc
    {
        printf("--- test MPrintErr, MPrintWarn, MPrintInfo, MPrintErrVFunc\n");
        MPrintErr("aaa");
        MPrintWarn("bbb");
        MPrintInfo("ccc");
        MPrintErrVFunc;
        printf("=== \n");
    }

// MPrintErrClass(msg)
// MPrintWarnClass(msg)
// MPrintInfoClass(msg)
    {
        printf("--- test MPrintErrClass, MPrintWarnClass, MPrintInfoClass\n");
        TestObject* test_obj = new TestObject("title");
        test_obj->TestPrintErrWarnInfo();
        printf("=== \n");
    }
    
//    void IsValidArray(long narr, const int* const val_arr);
    {
        printf("--- test IsValidArray(long narr, const int* const val_arr)\n");
        long narr = 10;
        int* val_arr = new int[narr];
        MiBase::IsValidArray(narr, val_arr);
        delete [] val_arr;
        printf("=== \n");
    }

//    {
//        printf("--- test IsValidArray(long narr, const int* const val_arr)\n");
//        long narr = 10;
//        int* val_arr = new int[narr];
//        MiBase::IsValidArray(0, val_arr);
//        delete [] val_arr;
//        printf("=== \n");
//    }

//    {
//        printf("--- test IsValidArray(long narr, const int* const val_arr)\n");
//        long narr = 10;
//        int* val_arr = NULL;
//        MiBase::IsValidArray(narr, val_arr);
//        delete [] val_arr;
//        printf("=== \n");
//    }

//    void IsValidArray(long narr, const double* const val_arr);
    {
        printf("--- test IsValidArray(long narr, const double* const val_arr)\n");
        long narr = 10;
        double* val_arr = new double[narr];
        MiBase::IsValidArray(narr, val_arr);
        delete [] val_arr;
        printf("=== \n");
    }

//    {
//        printf("--- test IsValidArray(long narr, const double* const val_arr)\n");
//        long narr = 10;
//        double* val_arr = new double[narr];
//        MiBase::IsValidArray(0, val_arr);
//        delete [] val_arr;
//        printf("=== \n");
//    }

//    {
//        printf("--- test IsValidArray(long narr, const double* const val_arr)\n");
//        long narr = 10;
//        double* val_arr = NULL;
//        MiBase::IsValidArray(narr, val_arr);
//        delete [] val_arr;
//        printf("=== \n");
//    }

//    void GenArray(vector<double> vec,
//                  long* narr_ptr,
//                  double** val_arr_ptr);
//    void DelArray(double* val_arr);
    {
        printf("--- test GenArray, DelArray\n");
        vector<double> vec(3);
        vec[0] = 1.0;
        vec[1] = 2.0;
        vec[2] = 3.0;
        long narr = 0;
        double* val_arr = NULL;
        MiBase::GenArray(vec, &narr, &val_arr);
        for(long iarr = 0; iarr < narr; iarr ++){
            printf("%e\n", val_arr[iarr]);
        }
        MiBase::DelArray(val_arr);

        printf("=== \n");
    }
    
    return status_prog;
}
