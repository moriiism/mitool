#include "mi_iolib.h"
#include "mir_plot_conf.h"
#include "mir_root_tool.h"
#include "mifc_std.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Init(int ndim);    
    {
        printf("--- test Init\n");
        MirPlotConf* plot_conf = new MirPlotConf;
        int ndim = 3;
        plot_conf->Init(ndim);
        plot_conf->Print(stdout);

        delete plot_conf;
        
        printf("=== \n");
    }

//    void Load(string file);
    {
        printf("--- test Load\n");
        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Load("data/test_plot_conf3.dat");
        plot_conf->Print(stdout);

        delete plot_conf;
        
        printf("=== \n");
    }
    
//    void SetIdimElm(int idim, string lo_str, string up_str,
//                    string offset_tag, string scale, string label);
    {
        printf("--- test SetIdimElm\n");
        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Init(3);
        int idim = 1;
        string lo_str = "222";
        string up_str = "333";
        string offset_tag = "444";
        string scale = "555";
        string label = "666";
        plot_conf->SetIdimElm(idim, lo_str, up_str,
                              offset_tag, scale, label);
        plot_conf->Print(stdout);

        delete plot_conf;
        
        printf("=== \n");
    }
   
//    void Copy(const MirPlotConf* const org);
//    MirPlotConf* const Clone() const;
//    void Print(FILE* fp) const;    
    {
        printf("--- test Copy\n");
        printf("--- test Clone\n");
        printf("--- test Print\n");
        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Init(3);
        int idim = 1;
        string lo_str = "222";
        string up_str = "333";
        string offset_tag = "444";
        string scale = "555";
        string label = "666";
        plot_conf->SetIdimElm(idim, lo_str, up_str,
                              offset_tag, scale, label);
        plot_conf->Print(stdout);        

        printf("--- \n");
        MirPlotConf* plot_conf_new = new MirPlotConf;
        plot_conf_new->Copy(plot_conf);
        plot_conf_new->Print(stdout);

        printf("--- \n");
        MirPlotConf* plot_conf_clone = plot_conf->Clone();
        plot_conf_clone->Print(stdout);

        printf("--- \n");        
//    int GetNdim() const {return ndim_;};
        printf("test GetNdim()\n");
        printf("GetNdim() = %d\n", plot_conf->GetNdim());
//    const string* const GetLoStr() const {return lo_str_;};
        printf("--- \n");
        printf("test GetLoStr()\n");
        for(int idim = 0; idim < plot_conf->GetNdim(); idim ++){
            printf("GetLoStr()[%d] = %s\n", idim, plot_conf->GetLoStr()[idim].c_str());
        }
//    const string* const GetUpStr() const {return up_str_;};
        printf("--- \n");
        printf("test GetUpStr()\n");
        for(int idim = 0; idim < plot_conf->GetNdim(); idim ++){
            printf("GetUpStr()[%d] = %s\n", idim, plot_conf->GetUpStr()[idim].c_str());
        }
//    const string* const GetOffsetTag() const {return offset_tag_;};
        printf("--- \n");
        printf("test GetOffsetTag()\n");
        for(int idim = 0; idim < plot_conf->GetNdim(); idim ++){
            printf("GetOffsetTag()[%d] = %s\n", idim, plot_conf->GetOffsetTag()[idim].c_str());
        }
//    const string* const GetScale() const {return scale_;};
        printf("--- \n");
        printf("test GetScale()\n");
        for(int idim = 0; idim < plot_conf->GetNdim(); idim ++){
            printf("GetScale()[%d] = %s\n", idim, plot_conf->GetScale()[idim].c_str());
        }
//    const string* const GetLabel() const {return label_;};
        printf("--- \n");
        printf("test GetLabel()\n");
        for(int idim = 0; idim < plot_conf->GetNdim(); idim ++){
            printf("GetLabel()[%d] = %s\n", idim, plot_conf->GetLabel()[idim].c_str());
        }
//    string GetLoStrElm(int idim) const {return lo_str_[idim];};
        printf("--- \n");
        printf("test GetLoStrElm(int idim)\n");
        for(int idim = 0; idim < plot_conf->GetNdim(); idim ++){
            printf("GetLoStrElm(%d) = %s\n", idim, plot_conf->GetLoStrElm(idim).c_str());
        }
//    string GetUpStrElm(int idim) const {return up_str_[idim];};
        printf("--- \n");
        printf("test GetUpStrElm(int idim)\n");
        for(int idim = 0; idim < plot_conf->GetNdim(); idim ++){
            printf("GetUpStrElm(%d) = %s\n", idim, plot_conf->GetUpStrElm(idim).c_str());
        }
//    string GetOffsetTagElm(int idim) const {return offset_tag_[idim];};
        printf("--- \n");
        printf("test GetOffsetTagElm(int idim)\n");
        for(int idim = 0; idim < plot_conf->GetNdim(); idim ++){
            printf("GetOffsetTagElm(%d) = %s\n", idim, plot_conf->GetOffsetTagElm(idim).c_str());
        }
//    string GetScaleElm(int idim) const {return scale_[idim];};
        printf("--- \n");
        printf("test GetScaleElm(int idim)\n");
        for(int idim = 0; idim < plot_conf->GetNdim(); idim ++){
            printf("GetScaleElm(%d) = %s\n", idim, plot_conf->GetScaleElm(idim).c_str());
        }
//    string GetLabelElm(int idim) const {return label_[idim];};
        printf("--- \n");
        printf("test GetLabelElm(int idim)\n");
        for(int idim = 0; idim < plot_conf->GetNdim(); idim ++){
            printf("GetLabelElm(%d) = %s\n", idim, plot_conf->GetLabelElm(idim).c_str());
        }
        
        delete plot_conf;
        delete plot_conf_new;
        delete plot_conf_clone;
        
        printf("=== \n");
    }

//    static void GenPlotConf2(const MirPlotConf* const plot_conf,
//                             MirPlotConf** const plot_conf_val_ptr,
//                             MirPlotConf** const plot_conf_ratio_ptr);
    {
        printf("--- test GenPlotConf2\n");
        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Load("data/test_plot_conf2.dat");
        plot_conf->Print(stdout);

        MirPlotConf* plot_conf_val = NULL;
        MirPlotConf* plot_conf_ratio = NULL;
        MirPlotConf::GenPlotConf2(plot_conf,
                                  &plot_conf_val,
                                  &plot_conf_ratio);
        printf("--- \n");        
        plot_conf_val->Print(stdout);
        printf("--- \n");        
        plot_conf_ratio->Print(stdout);
        
        delete plot_conf;
        delete plot_conf_val;
        delete plot_conf_ratio;
        
        printf("=== \n");
    }
    
//    static void GenPlotConf3(const MirPlotConf* const plot_conf,
//                             MirPlotConf** const plot_conf_val_ptr,
//                             MirPlotConf** const plot_conf_chi_ptr,
//                             MirPlotConf** const plot_conf_ratio_ptr);
    {
        printf("--- test GenPlotConf3\n");
        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Load("data/test_plot_conf3.dat");
        plot_conf->Print(stdout);

        MirPlotConf* plot_conf_val = NULL;
        MirPlotConf* plot_conf_chi = NULL;
        MirPlotConf* plot_conf_ratio = NULL;
        MirPlotConf::GenPlotConf3(plot_conf,
                                  &plot_conf_val,
                                  &plot_conf_chi,
                                  &plot_conf_ratio);
        printf("--- \n");        
        plot_conf_val->Print(stdout);
        printf("--- \n");        
        plot_conf_chi->Print(stdout);
        printf("--- \n");        
        plot_conf_ratio->Print(stdout);
        
        delete plot_conf;
        delete plot_conf_val;
        delete plot_conf_chi;
        delete plot_conf_ratio;
        
        printf("=== \n");
    }

//    static void CopyPar(const MirPlotConf* const plot_conf, TF1* const tf1);
    {
        printf("--- test CopyPar\n");
        MirPlotConf* plot_conf = new MirPlotConf;
        plot_conf->Init(2);
        plot_conf->SetIdimElm(0, "-10.0", "10.0", "no", "lin", "ttttt");
        plot_conf->SetIdimElm(1, "-1", "10", "no", "lin", "yyyy");
        plot_conf->Print(stdout);

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        Gauss1dFunc* func = new Gauss1dFunc;
        TF1* tf1 = new TF1("title", func, &MirFunc::Eval,
                           -10.0, 10.0, func->GetNpar(),
                           func->GetClassName().c_str(), "Eval");
        tf1->SetParameters(1, 1, 10);
        MirPlotConf::CopyPar(plot_conf, tf1);

        tf1->Draw();
        root_tool->GetTCanvas()->Print("/home/morii/temp/plot_conf_copy_par.png");

        delete plot_conf;
        delete tf1;
        delete root_tool;
        
        printf("=== \n");
    }
    
    return status_prog;
}
