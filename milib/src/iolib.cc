#include "mi_iolib.h"


//
// Read File
//


int MiIolib::GenReadFile(string file,
                           double** const valx_arr_ptr,
                           long* const nline_ptr)
{
    int ret = kRetNormal;    

    FILE* fp = NULL;
    if(NULL == (fp = fopen(file.c_str(), "r"))){
        MPrintErr("file open error.");
        abort();
    }

    long iline = 0;
    char line[kLineSize];    
    while(1){
        if(NULL == fgets( line, sizeof(line), fp))
            break;
        iline ++;
    }
    fclose(fp);
    long nline = iline;
    double* valx_arr = new double [nline];
    for(long iline = 0; iline < nline; iline ++){
        valx_arr[iline] = 0.0;
    }

    if(NULL == (fp = fopen(file.c_str(), "r"))){
        MPrintErr("file open error.");
        abort();
    }
    iline = 0;
    while(1){
        if(NULL == fgets( line, sizeof(line), fp))
            break;
        sscanf(line, "%lf", &valx_arr[iline]);
        iline++;
    }
    fclose(fp);

    *valx_arr_ptr = valx_arr;
    *nline_ptr = nline;
    return ret;
}

int MiIolib::GenReadFile(string file,
                           double** const valx1_arr_ptr,
                           double** const valx2_arr_ptr,
                           long* const nline_ptr)
{
    int ret = kRetNormal;
    
    FILE* fp = NULL;
    if(NULL == (fp = fopen(file.c_str(), "r"))){
        MPrintErr("file open error.");
        abort();
    }

    long iline = 0;
    char line[kLineSize];
    while(1){
        if(NULL == fgets( line, sizeof(line), fp))
            break;
        iline++;
    }
    fclose(fp);
    long nline = iline;
    double* valx1_arr = new double [nline];
    double* valx2_arr = new double [nline];
    for(long iline = 0; iline < nline; iline ++){
        valx1_arr[iline] = 0.0;
        valx2_arr[iline] = 0.0;
    }
    
    if(NULL == (fp = fopen(file.c_str(), "r"))){
        MPrintErr("file open error.");
        abort();
    }
    iline = 0;
    while(1){
        if(NULL == fgets( line, sizeof(line), fp))
            break;
        sscanf(line, "%lf %lf", &valx1_arr[iline], &valx2_arr[iline]);
        iline++;
    }
    fclose(fp);

    *valx1_arr_ptr = valx1_arr;
    *valx2_arr_ptr = valx2_arr;
    *nline_ptr = nline;
    return ret;
}


int MiIolib::GenReadFile(string file,
                           double** const valx1_arr_ptr,
                           double** const valx2_arr_ptr,
                           double** const valx3_arr_ptr,
                           long* const nline_ptr)
{
    int ret = kRetNormal;
    FILE* fp = NULL;
    if(NULL == (fp = fopen(file.c_str(), "r"))){
        MPrintErr("file open error.");
        abort();
    }
    long iline = 0;    
    char line[kLineSize];
    while(1){
        if(NULL == fgets( line, sizeof(line), fp))
            break;
        iline++;
    }
    fclose(fp);
    long nline = iline;
    double* valx1_arr = new double [nline];
    double* valx2_arr = new double [nline];
    double* valx3_arr = new double [nline];
    for(long iline = 0; iline < nline; iline ++){
        valx1_arr[iline] = 0.0;
        valx2_arr[iline] = 0.0;
        valx3_arr[iline] = 0.0;
    }
    

    if(NULL == (fp = fopen(file.c_str(), "r"))){
        MPrintErr("file open error.");
        abort();
    }
    iline = 0;
    while(1){
        if(NULL == fgets( line, sizeof(line), fp))
            break;
        sscanf(line, "%lf %lf %lf", &valx1_arr[iline], &valx2_arr[iline], &valx3_arr[iline]);
        iline++;
    }
    fclose(fp);

    *valx1_arr_ptr = valx1_arr;
    *valx2_arr_ptr = valx2_arr;
    *valx3_arr_ptr = valx3_arr;
    *nline_ptr = nline;
    return ret;
}


int MiIolib::GenReadFile(string file,              // file name
                           char*** const lines_ptr,  // To store the lines
                           long* const nline_ptr)     // # of lines
{
    int ret = kRetNormal;

    FILE* fp = NULL;
    if(NULL == (fp = fopen(file.c_str(), "r"))){
        MPrintErr("file open error.");
        abort();
    }

    long iline = 0;    
    char line[kLineSize];
    while(1){
        if(NULL == fgets( line, sizeof(line), fp))
            break;
        iline++;
    }
    fclose(fp);
    long nline = iline;

    char** lines = new char* [nline];
    for(long iline = 0; iline < nline; iline ++){
        lines[iline] = new char [kLineSize];
    }
    
    if(NULL == (fp = fopen(file.c_str(), "r"))){
        MPrintErr("file open error.");
        abort();
    }
    iline = 0;
    while(1){
        if(NULL == fgets( line, sizeof(line), fp))
            break;
        strcpy(lines[iline], line);
        MiStr::Chomp(lines[iline]);
        iline ++;
    }
    fclose(fp);

    *lines_ptr = lines;
    *nline_ptr = nline;
    return ret;
}

int MiIolib::GenReadFile(string file,
                           string** const lines_ptr,
                           long* const nline_ptr)
{
    int ret = kRetNormal;
    string buf;
    vector<string> buf_vec;

    ifstream ifs(file.c_str());
    while(ifs && getline(ifs, buf)){
        buf_vec.push_back(buf);
    }
    ifs.close();

    printf("debug: buf_vec.size() = %d\n", (int) buf_vec.size());

    long nline = buf_vec.size();
    string* lines = new string [nline];
    for(long iline = 0; iline < nline; iline ++){
        lines[iline] = buf_vec[iline];
    }

    *lines_ptr = lines;
    *nline_ptr = nline;
    return ret;
}


//
// Read File by skipping comment lines and blank lines
//

int MiIolib::GenReadFileSkipComment(string file,
                                      string** const lines_ptr,
                                      long* const nline_ptr)
{
    int ret = kRetNormal;
    string buf;
    vector<string> buf_vec;

    ifstream ifs(file.c_str());
    if (! ifs.is_open()){
        MPrintErr("file open error.");
        abort();
    }
    while(ifs && getline(ifs, buf)){
        if ("#" == buf.substr(0, 1)){
            continue;
        }
        if ("!" == buf.substr(0, 1)){
            continue;
        }
        if(MiStr::IsSpace(buf)){
            continue;
        }
        buf_vec.push_back(buf);
    }
    ifs.close();

    long nline = buf_vec.size();
    string* lines = new string [nline];
    for(long iline = 0; iline < nline; iline ++){
        lines[iline] = buf_vec[iline];
    }

    *lines_ptr = lines;
    *nline_ptr = nline;
    return ret;
}


//
// Read comment lines of file
//

int MiIolib::GenReadFileComment(string file,
                                  string** const lines_ptr,
                                  long* const nline_ptr)
{
    int ret = kRetNormal;
    string buf;
    vector<string> buf_vec;

    ifstream ifs(file.c_str());
    if (! ifs.is_open()){
        MPrintErr("file open error.");
        abort();
    }
    while(ifs && getline(ifs, buf)){
        if ("#" == buf.substr(0, 1) || "!" == buf.substr(0, 1) ){
            buf_vec.push_back(buf);
        }
    }
    ifs.close();

    long nline = buf_vec.size();
    string* lines = new string [nline];
    for(long iline = 0; iline < nline; iline ++){
        lines[iline] = buf_vec[iline];
    }

    *lines_ptr = lines;
    *nline_ptr = nline;
    return ret;
}



//
// Get rows by using ReadFileSkipComment
//

int MiIolib::GenRowsByReadFileSkipComment(string file,
                                            vector<long> sel_row_list_vec,
                                            string** const lines_ptr,
                                            long* const nline_ptr)
{
    string* lines_tmp = NULL;
    long nline_tmp = 0;
    int ret = GenReadFileSkipComment(file,
                                     &lines_tmp,
                                     &nline_tmp);
    long nline = sel_row_list_vec.size();
    string* lines = new string [nline];
    for(long iline = 0; iline < nline; iline ++){
        lines[iline] = lines_tmp[sel_row_list_vec[iline]];
    }
    *lines_ptr = lines;
    *nline_ptr = nline;
    return ret;
}


void MiIolib::DelReadFile(double* val_arr)
{
    delete [] val_arr; val_arr = NULL;
}

void MiIolib::DelReadFile(long nline, char** line_arr)
{
    for(long iline = 0; iline < nline; iline ++){
        delete [] line_arr[iline]; line_arr[iline] = NULL;
    }
    delete [] line_arr; line_arr = NULL;
}

void MiIolib::DelReadFile(string* line_arr)
{
    delete [] line_arr; line_arr = NULL;
}


int MiIolib::TestFileExist(string fname)
{
    // if not exist, return 1
    // if exist, return 0
    int iret = 0;
    char cmd[kLineSize];
    sprintf(cmd, "/usr/bin/test -e %s; echo $?", fname.c_str());
    FILE* fp_sh = popen(cmd, "r");
    char line[kLineSize], cmdans[kLineSize];
    if (fgets( line, sizeof(line), fp_sh) == NULL){
        MPrintErr("file open error.");
        abort();
    } else{
        sscanf( line, "%s", cmdans);
    }
    pclose(fp_sh);
    iret = atoi(cmdans);
    return iret;
}



int MiIolib::Printf2(FILE* fp_log, const char* const format, ...)
{
    int ret = 0;

    va_list ap;

    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);

    va_start(ap, format);
    vfprintf(fp_log, format, ap);
    va_end(ap);
  
    return ret;
  
}

void MiIolib::Qstop()
{
    int idummy;
    scanf("%d", &idummy);
}

