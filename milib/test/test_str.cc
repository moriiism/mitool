#include "mi_str.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    int IsSpace(string buf);
    {
        string buf = " ";
        printf("%d\n", MiStr::IsSpace(buf));
    }
    
    {
        string buf = "";
        printf("%d\n", MiStr::IsSpace(buf));
    }
    
    {
        string buf = "9";
        printf("%d\n", MiStr::IsSpace(buf));
    }

    {
        string buf = "\t";
        printf("%d\n", MiStr::IsSpace(buf));
    }

    {
        string buf = "\n";
        printf("%d\n", MiStr::IsSpace(buf));
    }
    
//    int Chomp(char* const buf);
    {
        printf("--- Chomp(char* const buf)\n");
        char buf[7] = "12345\n";
        printf("%s\nA\n", buf);
        MiStr::Chomp(buf);
        printf("%s\nA\n", buf);
        MiStr::Chomp(buf);
        printf("%s\nA\n", buf);
        printf("=== \n");
    }
    
//    int Chomp(string* const buf_ptr);
    {
        printf("--- Chomp(string* const buf_ptr)\n");
        string buf = "12345\n";
        printf("%s\nA\n", buf.c_str());
        MiStr::Chomp(&buf);
        printf("%s\nA\n", buf.c_str());
        MiStr::Chomp(&buf);
        printf("%s\nA\n", buf.c_str());
        printf("=== \n");
    }

//    void GenSplit(string str_in, int* nsplit_ptr, string** split_arr_ptr,
//                  const char* const delim = " \t");
//    void DelSplit(string* split_arr);
    {
        printf("--- GenSplit()\n");
        string str_in = "aaa bbbb cccccc    ddd eeee\n";
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(str_in, &nsplit, &split_arr, " ");
        printf("nsplit = %d\n", nsplit);
        for(int isplit = 0; isplit < nsplit; isplit ++){
            printf("%s|\n", split_arr[isplit].c_str());
        }
        printf("=== \n");
    }

    {
        printf("--- GenSplit()\n");
        string str_in = "aaa bbbb cccccc    ddd eeee\n";
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(str_in, &nsplit, &split_arr, " \n");
        printf("nsplit = %d\n", nsplit);
        for(int isplit = 0; isplit < nsplit; isplit ++){
            printf("%s|\n", split_arr[isplit].c_str());
        }
        printf("=== \n");
    }

    {
        printf("--- GenSplit()\n");
        string str_in = "aaa, bbbb ,cccccc  ,  ddd,eeee\n";
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(str_in, &nsplit, &split_arr, " \n");
        printf("nsplit = %d\n", nsplit);
        for(int isplit = 0; isplit < nsplit; isplit ++){
            printf("%s|\n", split_arr[isplit].c_str());
        }
        printf("=== \n");
    }

    {
        printf("--- GenSplit()\n");
        string str_in = "aaa, bbbb ,cccccc  ,  ddd,eeee\n";
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(str_in, &nsplit, &split_arr, ", \n");
        printf("nsplit = %d\n", nsplit);
        for(int isplit = 0; isplit < nsplit; isplit ++){
            printf("%s|\n", split_arr[isplit].c_str());
        }
        printf("=== \n");
    }

    
//    int GetNcolumn(string str_in, const char* const delim = " \t");
    {
        printf("--- GetNcolumn()\n");
        string str_in = "aaa, bbbb ,cccccc  ,  ddd,eeee\n";
        int nsplit = MiStr::GetNcolumn(str_in, ", \n");
        printf("nsplit = %d\n", nsplit);
        printf("=== \n");
    }


    
    return status_prog;
}
