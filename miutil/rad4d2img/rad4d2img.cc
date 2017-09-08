#include "fitsio.h"
#include "mi_str.h"
#include "mi_iolib.h"
#include "mif_fits.h"
#include "mif_img_info.h"
#include "arg_rad4d2img.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;
    
    ArgValRad4d2img* argval = new ArgValRad4d2img;
    argval->Init(argc, argv);
    argval->Print(stdout);

    printf("--- img_info ---\n");
    MifImgInfo* img_info = new MifImgInfo;
    img_info->Load(argval->GetSubimgDat());
    img_info->PrintInfo();
    printf("=== img_info ===\n");
    
    double* X_mat = NULL;
    int bitpix = 0;
    MifFits::InFits4dD(argval->GetInfile(),
                       img_info, &bitpix, &X_mat);

    MifImgInfo* img_info_out = new MifImgInfo;
    img_info_out->InitSetImg(1, 1,
                             img_info->GetNaxesArrElm(0),
                             img_info->GetNaxesArrElm(1));
    MifFits::OutFitsImageD(argval->GetOutdir(), argval->GetOutfileHead(), "img",
                           2, bitpix, img_info_out->GetNaxesArr(),
                           X_mat);
    
    return status_prog;
}
