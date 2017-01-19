#include "mir_interval.h"

//
// Interval
//

//
// public
//

void Interval::Init(long nterm)
{
    Null();
    
    nterm_ = nterm;
    tstart_ = new double [nterm_];
    tstop_  = new double [nterm_];
    for(long iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = 0.0;
        tstop_[iterm]  = 0.0;
    }
}

void Interval::Set(long nterm,
                   const double* const tstart,
                   const double* const tstop)
{
    nterm_ = nterm;
    for(long iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = tstart[iterm];
        tstop_[iterm]  = tstop[iterm];
    }

    if(! IsValid()){
        MPrintErrClass("bad interval");
        abort();
    }
    if(! IsOrdered()){
        MPrintWarnClass("It is not ordered.");
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void Interval::Set(vector<double> tstart,
                   vector<double> tstop)
{
    nterm_ = tstart.size();
    for(long iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = tstart[iterm];
        tstop_[iterm] = tstop[iterm];
    }
    if(! IsValid()){
        MPrintErrClass("bad interval");
        abort();
    }
    if(! IsOrdered()){
        MPrintWarnClass("It is not ordered.");
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Interval::InitSet(long nterm,
                       const double* const tstart,
                       const double* const tstop)
{
    Init(nterm);
    Set(nterm, tstart, tstop);
}

void Interval::InitSet(vector<double> tstart,
                       vector<double> tstop)
{
    Init(tstart.size());
    Set(tstart, tstop);
}

void Interval::InitSet(double tstart, double tstop)
{
    Init(1);
    double tstart_arr[1];
    double tstop_arr[1];
    tstart_arr[0] = tstart;
    tstop_arr[0]  = tstop;
    Set(1, tstart_arr, tstop_arr);
}


void Interval::Load(string file)
{
    Null();

    long nline;    
    string* line_arr = NULL;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    nterm_ = nline;
    tstart_ = new double [nterm_];
    tstop_  = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        int nsplit;
        string* split_arr = NULL;
        MiStr::GenSplit(line_arr[iterm], &nsplit, &split_arr);
        if(2 != nsplit){
            MPrintWarnClass("ncolum != 2");
        }
        delete [] split_arr;
        istringstream iss(line_arr[iterm]);
        iss >> tstart_[iterm] >> tstop_[iterm];
    }
    MiIolib::DelReadFile(line_arr);

    if(! IsValid()){
        MPrintErrClass("bad interval");
        abort();
    }
    if(! IsOrdered()){
        MPrintWarnClass("It is not ordered.");
    }
}


void Interval::Copy(const Interval* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    InitSet(org->GetNterm(),
            org->GetTstart(),
            org->GetTstop());
}

Interval* const Interval::Clone() const
{
    Interval* obj_new = new Interval;
    obj_new->Copy(this);
    return obj_new;
}

double* const Interval::GenTermCenter() const
{
    double* term_center = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        term_center[iterm] = GetTermCenterElm(iterm);
    }
    return term_center;
}

double* const Interval::GenTermHalfWidth() const
{
    double* term_half_width = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        term_half_width[iterm] = GetTermHalfWidthElm(iterm);
    }
    return term_half_width;
}

double Interval::GetTermCenterElm(long iterm) const
{
    double term_center = ( GetTstartElm(iterm) + GetTstopElm(iterm) )/2.;
    return term_center;
}

double Interval::GetTermHalfWidthElm(long iterm) const
{
    double term_half_width = ( GetTstopElm(iterm) - GetTstartElm(iterm) )/2.;
    return term_half_width;
}

int Interval::IsOrdered() const
{
    int ans = 1;
    for(int iterm = 0; iterm < nterm_; iterm++){
        if(tstart_[iterm] > tstop_[iterm]){
            ans = 0;
            return ans;
        }
    }
    for(int iterm = 0; iterm < nterm_ - 1; iterm++){
        if(tstop_[iterm] > tstart_[iterm + 1]){
            ans = 0;
            return ans;
        }
    }
    return ans;
}

int Interval::IsIn(double val) const
{
    int flag = 0;
    for(int iterm = 0; iterm < nterm_; iterm++){
        if(tstart_[iterm] < val + DBL_EPSILON && val - DBL_EPSILON < tstop_[iterm]){
            flag = 1;
            break;
        }
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return flag;
}


double Interval::GetFirst() const
{
    double first = GetTstartElm(0);
    return first;
}
    
double Interval::GetLast() const
{
    double last = GetTstopElm(GetNterm() - 1);
    return last;
}


double Interval::GetTotalInterval() const
{
    if(! IsOrdered()){
        MPrintWarnClass("It is not ordered.");
    }
    
    double total = 0.0;
    for(int iterm = 0; iterm < nterm_; iterm++){
        total += tstop_[iterm] - tstart_[iterm];
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return total;
}


long Interval::GetIndexByTime(double time) const
{
    if(! IsOrdered()){
        MPrintErrClass("bad interval");
        abort();
    }
    long index = -1;
    for(long iterm = 0; iterm < nterm_; iterm++){
        if(tstart_[iterm] <= time && time <= tstop_[iterm]){
            index = iterm;
            break;
        }
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return index;
}

long Interval::GetIndexByTimeQuick(double time) const
{
    if(! IsOrdered()){
        MPrintErrClass("bad interval");
        abort();
    }
    long index = -1;
    long iterm_find = MiSort::BinarySearch(nterm_, tstart_, time);
    // printf("iterm_find = %ld\n", iterm_find);
    
    for(long iterm = iterm_find - 1; iterm < nterm_; iterm++){
        if(tstart_[iterm] <= time && time <= tstop_[iterm]){
            index = iterm;
            break;
        }
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return index;
}

long Interval::GetIndexByTimeGE(double time) const
{
    if(! IsOrdered()){
        MPrintErrClass("bad interval");
        abort();
    }

    long index = -1;
    for(long iterm = 0; iterm < nterm_; iterm++){
        if(tstart_[iterm] <= time){
            index ++;
        }
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return index;
}


long Interval::GetIndexByTimeGEQuick(double time) const
{
    if(! IsOrdered()){
        MPrintErrClass("bad interval");
        abort();
    }

    long index = -1;
    long iterm_find = MiSort::BinarySearch(nterm_, tstart_, time);
    for(long iterm = iterm_find - 1; iterm < nterm_; iterm++){
        if(tstart_[iterm] <= time){
            index ++;
        }
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return index;
}


double Interval::GetOffsetFromTag(string offset_tag) const
{
    if("st" == offset_tag ||
       "ed" == offset_tag ||
       "md" == offset_tag ){
        if(! IsOrdered()){
            MPrintErrClass("bad interval");
            abort();
        }
    }
    
    double offset = 0.0;
    if("st" == offset_tag){
        offset = tstart_[0];
    } else if ("ed" == offset_tag){
        offset = tstop_[nterm_ - 1];
    } else if ("md" == offset_tag){
        offset = (tstart_[0] + tstop_[nterm_ - 1])/2.;
    } else {
        offset = atof(offset_tag.c_str());
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return offset;
}



void Interval::Save(string file) const
{
    FILE* fp = fopen(file.c_str(), "w");
    for(long iterm = 0; iterm < nterm_; iterm++){
        fprintf(fp, "%.10e  %.10e\n",
                tstart_[iterm], tstop_[iterm]);
    }
    fclose(fp);

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Interval::Print(FILE* fp) const
{
    fprintf(fp, "Interval::Print: nterm_ = %ld\n", nterm_);
    for(long iterm = 0; iterm < nterm_; iterm++){
        fprintf(fp, "Interval::Print: %ld  %.10e  %.10e\n",
                iterm, tstart_[iterm], tstop_[iterm]);
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Interval::PrintDataLc(FILE* fp, string lc_format, double offset) const
{
    if("x,y" == lc_format){
        for(long iterm = 0; iterm < nterm_; iterm++){
            fprintf(fp, "%.10e %e\n",
                    tstart_[iterm] - offset, 0.0);
            fprintf(fp, "%.10e %e\n",
                    tstart_[iterm] - offset, 1.0);
            fprintf(fp, "%.10e %e\n",
                    tstop_[iterm] - offset,  1.0);
            fprintf(fp, "%.10e %e\n",
                    tstop_[iterm] - offset,  0.0);
        }
    } else if("x,y,ye" == lc_format){
        for(long iterm = 0; iterm < nterm_; iterm++){
            fprintf(fp, "%.10e %e 0.0\n",
                    tstart_[iterm] - offset, 0.0);
            fprintf(fp, "%.10e %e 0.0\n",
                    tstart_[iterm] - offset, 1.0);
            fprintf(fp, "%.10e %e 0.0\n",
                    tstop_[iterm] - offset,  1.0);
            fprintf(fp, "%.10e %e 0.0\n",
                    tstop_[iterm] - offset,  0.0);
        }
    } else if("x,xe,y,ye" == lc_format){
        for(long iterm = 0; iterm < nterm_; iterm++){
            fprintf(fp, "%.10e 0.0 %e 0.0\n",
                    tstart_[iterm] - offset, 0.0);
            fprintf(fp, "%.10e 0.0 %e 0.0\n",
                    tstart_[iterm] - offset, 1.0);
            fprintf(fp, "%.10e 0.0 %e 0.0\n",
                    tstop_[iterm] - offset,  1.0);
            fprintf(fp, "%.10e 0.0 %e 0.0\n",
                    tstop_[iterm] - offset,  0.0);
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad lc_format (=%s)", lc_format.c_str());
        MPrintErrClass(msg);
        abort();
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Interval::Sort(string mode)
{
    if(0 < g_flag_verbose){
        MPrintInfoClass("start...");
        char msg[kLineSize];
        sprintf(msg, "mode = %s", mode.c_str());
        MPrintInfoClass(msg);
    }
    long* index = new long [nterm_];
    double* tstart_sort = new double [nterm_];
    double* tstop_sort = new double [nterm_];
  
    if("st" == mode) {
        // sort by start time
        MiSort::Sort(nterm_, tstart_, index, 0);
    } else if ("ed" == mode) {
        // sort by end time
        MiSort::Sort(nterm_, tstop_, index, 0);
    } else if ("md" == mode){
        double* tmid = new double [nterm_];
        for(int iterm = 0; iterm < nterm_; iterm ++){
            tmid[iterm] = (tstart_[iterm] + tstop_[iterm]) / 2.;
        }
        // sort by middle time
        MiSort::Sort(nterm_, tmid, index, 0);
        delete [] tmid;
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad mode (=%s)", mode.c_str());
        MPrintErrClass(msg);
        abort();
    }
    
    for(int iterm = 0; iterm < nterm_; iterm ++){
        tstart_sort[iterm] = tstart_[index[iterm]];
        tstop_sort[iterm]  = tstop_[index[iterm]];
    }
    for(int iterm = 0; iterm < nterm_; iterm ++){
        tstart_[iterm] = tstart_sort[iterm];
        tstop_[iterm]  = tstop_sort[iterm];
    }
    delete [] index;
    delete [] tstart_sort;
    delete [] tstop_sort;
    if(0 < g_flag_verbose){
        MPrintInfoClass("end.");
    }
}

void Interval::And(const Interval* const interval1, const Interval* const interval2)
{
    Null();
    
    multimap<double, int> interval_map;
    int upval = +1;
    int dnval = -1;
    vector<double> interval_tstart;
    vector<double> interval_tstop;
  
    for(int iterm = 0; iterm < interval1->GetNterm(); iterm ++){
        interval_map.insert( make_pair(interval1->GetTstart()[iterm], upval));
        interval_map.insert( make_pair(interval1->GetTstop()[iterm], dnval));
    }
    for(int iterm = 0; iterm < interval2->GetNterm(); iterm ++){
        interval_map.insert( make_pair(interval2->GetTstart()[iterm], upval));
        interval_map.insert( make_pair(interval2->GetTstop()[iterm], dnval));
    }

    int sum = 0;
    int ival = 0;
    int find = 0;
    multimap<double, int>::iterator it;
    for(it = interval_map.begin(); it != interval_map.end(); ++it){
        sum += (*it).second;
        if(find == 0 && sum == 2){
            interval_tstart.push_back((*it).first);
            find = 1;
        }
        if(find == 1 && sum < 2){
            interval_tstop.push_back((*it).first);
            find = 0;
        }
        // printf("%f %d %d %d\n", (*it).first, (*it).second, sum, ival);
        ival ++;
    }
    if(interval_tstart.size() != interval_tstop.size()){
        printf("Interval::And: error: interval_tstart.size() != interval_tstop.size()\n");
        exit(1);
    }
    nterm_ = interval_tstart.size();
    tstart_ = new double [nterm_];
    tstop_ = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = interval_tstart[iterm];
        tstop_[iterm] = interval_tstop[iterm];
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void Interval::Or(const Interval* const interval1, const Interval* const interval2)
{
    Null();
    
    multimap<double, int> interval_map;
    int upval = +1;
    int dnval = -1;
    vector<double> interval_tstart;
    vector<double> interval_tstop;
  
    for(int iterm = 0; iterm < interval1->GetNterm(); iterm ++){
        interval_map.insert( make_pair(interval1->GetTstart()[iterm], upval));
        interval_map.insert( make_pair(interval1->GetTstop()[iterm], dnval));
    }
    for(int iterm = 0; iterm < interval2->GetNterm(); iterm ++){
        interval_map.insert( make_pair(interval2->GetTstart()[iterm], upval));
        interval_map.insert( make_pair(interval2->GetTstop()[iterm], dnval));
    }

    int sum = 0;
    int ival = 0;
    int find = 0;
    multimap<double, int>::iterator it;
    for(it = interval_map.begin(); it != interval_map.end(); ++it){
        sum += (*it).second;
        if(find == 0 && sum > 0){
            interval_tstart.push_back((*it).first);
            find = 1;
        }
        if(find == 1 && sum == 0){
            interval_tstop.push_back((*it).first);
            find = 0;
        }
        // printf("%f %d %d %d\n", (*it).first, (*it).second, sum, ival);
        ival ++;
    }
    if(interval_tstart.size() != interval_tstop.size()){
        printf("Interval::And: error: interval_tstart.size() != interval_tstop.size()\n");
        exit(1);
    }
    nterm_ = interval_tstart.size();
    tstart_ = new double [nterm_];
    tstop_ = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = interval_tstart[iterm];
        tstop_[iterm] = interval_tstop[iterm];
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Interval::And(const Interval* const* const interval_arr, int ninterval)
{
    Null();
    
    multimap<double, int> interval_map;
    int upval = +1;
    int dnval = -1;
    vector<double> interval_tstart;
    vector<double> interval_tstop;

    for(int iinterval = 0; iinterval < ninterval; iinterval++){
        for(int iterm = 0; iterm < interval_arr[iinterval]->GetNterm(); iterm ++){
            interval_map.insert( make_pair(interval_arr[iinterval]->GetTstart()[iterm], upval));
            interval_map.insert( make_pair(interval_arr[iinterval]->GetTstop()[iterm], dnval));
        }
    }

    int sum = 0;
    int ival = 0;
    int find = 0;
    multimap<double, int>::iterator it;
    for(it = interval_map.begin(); it != interval_map.end(); ++it){
        sum += (*it).second;
        if(find == 0 && sum == ninterval){
            interval_tstart.push_back((*it).first);
            find = 1;
        }
        if(find == 1 && sum < ninterval){
            interval_tstop.push_back((*it).first);
            find = 0;
        }
        // printf("%f %d %d %d\n", (*it).first, (*it).second, sum, ival);
        ival ++;
    }
    if(interval_tstart.size() != interval_tstop.size()){
        printf("Interval::And: error: interval_tstart.size() != interval_tstop.size()\n");
        exit(1);
    }
    nterm_ = interval_tstart.size();
    tstart_ = new double [nterm_];
    tstop_ = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = interval_tstart[iterm];
        tstop_[iterm] = interval_tstop[iterm];
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Interval::Or(const Interval* const* const interval_arr, int ninterval)
{
    Null();
    
    multimap<double, int> interval_map;
    int upval = +1;
    int dnval = -1;
    vector<double> interval_tstart;
    vector<double> interval_tstop;

    for(int iinterval = 0; iinterval < ninterval; iinterval++){
        for(int iterm = 0; iterm < interval_arr[iinterval]->GetNterm(); iterm ++){
            interval_map.insert( make_pair(interval_arr[iinterval]->GetTstart()[iterm], upval));
            interval_map.insert( make_pair(interval_arr[iinterval]->GetTstop()[iterm], dnval));
        }
    }

    int sum = 0;
    int ival = 0;
    int find = 0;
    multimap<double, int>::iterator it;
    for(it = interval_map.begin(); it != interval_map.end(); ++it){
        sum += (*it).second;
        if(find == 0 && sum > 0){
            interval_tstart.push_back((*it).first);
            find = 1;
        }
        if(find == 1 && sum == 0){
            interval_tstop.push_back((*it).first);
            find = 0;
        }
        // printf("%f %d %d %d\n", (*it).first, (*it).second, sum, ival);
        ival ++;
    }
    if(interval_tstart.size() != interval_tstop.size()){
        printf("Interval::And: error: interval_tstart.size() != interval_tstop.size()\n");
        exit(1);
    }
    nterm_ = interval_tstart.size();
    tstart_ = new double [nterm_];
    tstop_ = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = interval_tstart[iterm];
        tstop_[iterm] = interval_tstop[iterm];
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Interval::AddMargin(const Interval* const interval, double time_margin, double time_precision)
{
    nterm_ = interval->GetNterm();
    tstart_ = new double [nterm_];
    tstop_ = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = interval->GetTstart()[iterm] - time_margin;
        tstop_[iterm]  = interval->GetTstop()[iterm]  + time_margin;
    }

    Clean(time_precision);

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Interval::Split(const Interval* const interval_one, int ninterval)
{
    Null();
    
    long nterm = interval_one->GetNterm();
    if(1 != nterm){
        MPrintErrClass("bad interval");
        abort();
    }
    double delta_time = (interval_one->GetTstopElm(0)
                         - interval_one->GetTstartElm(0)) / ninterval;
    nterm_ = ninterval;
    tstart_ = new double [nterm_];
    tstop_  = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = interval_one->GetTstartElm(0)
            + delta_time * iterm;
        tstop_[iterm]  = tstart_[iterm] + delta_time;
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void Interval::Clean(double tdiff)
{
    // printf("Interval::Clean: tdiff = %e\n", tdiff);
  
    // sort and merge for overlap duration
  
    multimap<double, int> interval_map;
    int upval = +1;
    int dnval = -1;
    for(int iterm = 0; iterm < nterm_; iterm ++){
        interval_map.insert( make_pair(tstart_[iterm], upval));
        interval_map.insert( make_pair(tstop_[iterm],  dnval));
    }

    vector<double> interval_tstart;
    vector<double> interval_tstop;

    int sum = 0;
    int ival = 0;
    int find = 0;
    multimap<double, int>::iterator it;
    for(it = interval_map.begin(); it != interval_map.end(); ++it){
        sum += (*it).second;
        if(find == 0 && sum > 0){
            interval_tstart.push_back((*it).first);
            find = 1;
        }
        if(find == 1 && sum == 0){
            interval_tstop.push_back((*it).first);
            find = 0;
        }
        // printf("%f %+2d %+2d %+2d\n", (*it).first, (*it).second, sum, ival);
        ival ++;
    }
    if(interval_tstart.size() != interval_tstop.size()){
        printf("Interval::And: error: interval_tstart.size() != interval_tstop.size(): %d %d\n",
               (int) interval_tstart.size(), (int) interval_tstop.size());
        exit(1);
    }
    nterm_ = interval_tstart.size();

    delete [] tstart_;
    delete [] tstop_;
  
    tstart_ = new double [nterm_];
    tstop_ = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = interval_tstart[iterm];
        tstop_[iterm] = interval_tstop[iterm];
    }

    // merge for short gap within time resolution of telescope
  
    int imerge = 0;
    for(int iterm = 0; iterm < nterm_ - 1; iterm++){
        if(tstart_[iterm + 1] - tstop_[iterm] < tdiff){
            imerge ++;
        }
    }
    int nmerge = imerge;
    int nterm_new = nterm_ - nmerge;
    // printf("Interval::Clean: nterm_new: %d\n", nterm_new);

    double *tstart_new = new double [nterm_new];
    double *tstop_new = new double [nterm_new];

    tstart_new[0] = tstart_[0];
    int iterm_new = 0;
    for(int iterm = 0; iterm < nterm_ - 1; iterm++){
        if(tstart_[iterm + 1] - tstop_[iterm] >= tdiff){
            tstop_new[iterm_new] = tstop_[iterm];
            iterm_new ++;
            tstart_new[iterm_new] = tstart_[iterm + 1];
        }
    }
    tstop_new[iterm_new] = tstop_[nterm_ - 1];
    
    nterm_ = nterm_new;
    delete [] tstart_;
    delete [] tstop_;
    tstart_ = new double [nterm_];
    tstop_ = new double [nterm_];
    for(int iterm = 0; iterm < nterm_; iterm++){
        tstart_[iterm] = tstart_new[iterm];
        tstop_[iterm] = tstop_new[iterm];
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


//
// private
//

void Interval::Null()
{
    nterm_ = 0;
    if(NULL != tstart_) {delete [] tstart_; tstart_ = NULL;}
    if(NULL != tstop_)  {delete [] tstop_; tstop_ = NULL;}
}

int Interval::IsValid() const
{
    int valid = 1;
    if(nterm_ < 0){
        valid = 0;
        return valid;
    }
    for(long iterm = 0; iterm < nterm_; iterm++){
        if(tstart_[iterm] > tstop_[iterm]){
            valid = 0;
            return valid;
        }
    }
    return valid;
}


// 
// Interval2dim
// 

//
// public
//

void Interval2dim::Init()
{
    Null();
    interval_x_ = new Interval;
    interval_y_ = new Interval;
}

void Interval2dim::Set(const Interval* const interval_x,
                       const Interval* const interval_y)
{
    interval_x_->Copy(interval_x);
    interval_y_->Copy(interval_y);
}


void Interval2dim::InitSet(const Interval* const interval_x,
                           const Interval* const interval_y)
{
    Init();
    Set(interval_x, interval_y);
}

void Interval2dim::Copy(const Interval2dim* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    InitSet(org->GetIntervalX(),
            org->GetIntervalY());
}

Interval2dim* const Interval2dim::Clone() const
{
    Interval2dim* obj_new = new Interval2dim;
    obj_new->Copy(this);
    return obj_new;
}

int Interval2dim::IsIn(double xval, double yval) const
{
    int flag = 1;
    flag *= interval_x_->IsIn(xval);
    flag *= interval_y_->IsIn(yval);

    return flag;
}

void Interval2dim::Print(FILE* fp) const
{
    fprintf(fp, "Interval2dim::Print: \n");
    fprintf(fp, "------ x axis ------\n");
    interval_x_->Print(fp);

    fprintf(fp, "------ y axis ------\n");
    interval_y_->Print(fp);
}

//
// private
//

void Interval2dim::Null()
{
    if(NULL != interval_x_) {delete interval_x_; interval_x_ = NULL;}
    if(NULL != interval_y_) {delete interval_y_; interval_y_ = NULL;}
}



//
// IntervalNdim
//

//
// public
//

void IntervalNdim::Init(long ndim)
{
    Null();
    
    ndim_ = ndim;
    interval_arr_ = new Interval* [ndim_];
    for(long idim = 0; idim < ndim_; idim++){
        interval_arr_[idim] = new Interval;
    }
}

void IntervalNdim::Set(long ndim,
                       const Interval* const* const interval_arr)
{
    ndim_ = ndim;
    for(long idim = 0; idim < ndim_; idim++){
        interval_arr_[idim]->Copy(interval_arr[idim]);
    }
}


void IntervalNdim::InitSet(long ndim,
                           const Interval* const* const interval_arr)
{
    Init(ndim);
    Set(ndim, interval_arr);
}

void IntervalNdim::Copy(const IntervalNdim* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}

    CopyTitle(org);
    InitSet(org->GetNdim(),
            org->GetIntervalArr());
}

IntervalNdim* const IntervalNdim::Clone() const
{
    IntervalNdim* obj_new = new IntervalNdim;
    obj_new->Copy(this);
    return obj_new;
}

int IntervalNdim::IsIn(const double* const val_arr, long ndim) const
{
    if(ndim_ != ndim){
        MPrintErrClass("bad ndim");
        abort();
    }
    int flag = 1;
    for(long idim = 0; idim < ndim_; idim++){
        flag *= interval_arr_[idim]->IsIn(val_arr[idim]);
    }
    return flag;
}

void IntervalNdim::Print(FILE* fp) const
{
    fprintf(fp, "IntervalNdim::Print: ndim_ = %ld\n", ndim_);
    for(long idim = 0; idim < ndim_; idim++){
        fprintf(fp, "------ %ld / %ld ------\n", idim, ndim_);
        interval_arr_[idim]->Print(fp);
    }
}

//
// private
//

void IntervalNdim::Null()
{
    if(NULL != interval_arr_) {
        for(long idim = 0; idim < ndim_; idim++){
            delete interval_arr_[idim]; interval_arr_[idim] = NULL;
        }
        delete [] interval_arr_; interval_arr_ = NULL;
    }
    ndim_ = 0;
}
