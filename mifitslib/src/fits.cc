#include "mif_fits.h"

int MifFits::GetNaxis(string infile)
{
    fitsfile* fptr_in = NULL;
    int iomode = 0;
    int status = 0; // status for fitsIO
    fits_open_file(&fptr_in, infile.c_str(),
                   iomode, &status);
    int naxis = 0;
    fits_get_img_dim(fptr_in, &naxis, &status);

    return naxis;
}

int MifFits::GetAxisSize(string infile, int idim)
{
    fitsfile* fptr_in = NULL;
    int iomode = 0;
    int status = 0; // status for fitsIO
    fits_open_file(&fptr_in, infile.c_str(),
                   iomode, &status);
    int naxis = 0;
    fits_get_img_dim(fptr_in, &naxis, &status);
    // printf("naxis = %d\n", naxis);

    if(idim < 0 || naxis <= idim){
        abort();
    }
    long* naxes = new long [naxis];
    int maxdim = naxis;
    fits_get_img_size(fptr_in, maxdim, naxes, &status);

    int axis_size = naxes[idim];
    delete [] naxes;
    return axis_size;
}

int MifFits::InFitsImageF(string infile,
                          const MifImgInfo* const img_info,
                          int* const bitpix_ptr,
                          float** const data_arr_ptr)
{
    fitsfile* fptr_in = NULL;
    int iomode = 0;
    int status = 0; // status for fitsIO
    fits_open_file(&fptr_in, infile.c_str(),
                   iomode, &status);
    int hdunum = 0;
    fits_get_num_hdus(fptr_in, &hdunum, &status);
    printf("hdunum = %d\n", hdunum);

    int keysexist = 0;
    int morekeys = 0;
    fits_get_hdrspace(fptr_in, &keysexist, &morekeys, &status);
    printf("keysexist = %d\n", keysexist);

    int naxis = 0;
    fits_get_img_dim(fptr_in, &naxis, &status);
    printf("naxis = %d\n", naxis);
    if(2 != naxis){
        printf("bad naxis (= %d)\n", naxis);
        abort();
    }
    long* naxes = new long [naxis];
    int maxdim = naxis;
    fits_get_img_size(fptr_in, maxdim, naxes, &status);
    for(int idim = 0; idim < naxis; idim ++){
        printf("naxes[%d] = %ld\n", idim, naxes[idim]);
    }
    delete [] naxes;

    int bitpix = 0;
    fits_get_img_type(fptr_in, &bitpix, &status);
    printf("bitpix = %d\n", bitpix);
    
    // vectorized 2D image for sub image
    long naxes_sub[2];
    naxes_sub[0] = img_info->GetNaxesArrElm(0);
    naxes_sub[1] = img_info->GetNaxesArrElm(1);
    long npix_image_sub_vec = naxes_sub[0] * naxes_sub[1];

    float* data_arr = new float [npix_image_sub_vec];
    long inc[2] = {1,1};
    fits_read_subset(fptr_in, TFLOAT,
                     img_info->GetFpixelArr(), img_info->GetLpixelArr(),
                     inc, NULL, data_arr, NULL, &status);
    fits_close_file(fptr_in, &status);
    fits_report_error(stderr, status);

    for(long iarr = 0; iarr < npix_image_sub_vec; iarr++){
        if(isnan(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }
        if(isinf(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }        
    }

    *bitpix_ptr = bitpix;
    *data_arr_ptr = data_arr;
    
    return (status);
}

int MifFits::InFitsImageD(string infile,
                          const MifImgInfo* const img_info,
                          int* const bitpix_ptr,
                          double** const data_arr_ptr)
{
    fitsfile* fptr_in = NULL;
    int iomode = 0;
    int status = 0; // status for fitsIO
    fits_open_file(&fptr_in, infile.c_str(),
                   iomode, &status);
    int hdunum = 0;
    fits_get_num_hdus(fptr_in, &hdunum, &status);
    // printf("hdunum = %d\n", hdunum);

    int keysexist = 0;
    int morekeys = 0;
    fits_get_hdrspace(fptr_in, &keysexist, &morekeys, &status);
    // printf("keysexist = %d\n", keysexist);

    int naxis = 0;
    fits_get_img_dim(fptr_in, &naxis, &status);
    // printf("naxis = %d\n", naxis);
    if(2 != naxis){
        printf("bad naxis (= %d)\n", naxis);
        abort();
    }
    long* naxes = new long [naxis];
    int maxdim = naxis;
    fits_get_img_size(fptr_in, maxdim, naxes, &status);
    for(int idim = 0; idim < naxis; idim ++){
        // printf("naxes[%d] = %ld\n", idim, naxes[idim]);
    }
    delete [] naxes;

    int bitpix = 0;
    fits_get_img_type(fptr_in, &bitpix, &status);
    // printf("bitpix = %d\n", bitpix);
    
    // vectorized 2D image for sub image
    long naxes_sub[2];
    naxes_sub[0] = img_info->GetNaxesArrElm(0);
    naxes_sub[1] = img_info->GetNaxesArrElm(1);
    long npix_image_sub_vec = naxes_sub[0] * naxes_sub[1];

    double* data_arr = new double [npix_image_sub_vec];
    long inc[2] = {1,1};
    fits_read_subset(fptr_in, TDOUBLE,
                     img_info->GetFpixelArr(), img_info->GetLpixelArr(),
                     inc, NULL, data_arr, NULL, &status);
    fits_close_file(fptr_in, &status);
    fits_report_error(stderr, status);

    for(long iarr = 0; iarr < npix_image_sub_vec; iarr++){
        if(isnan(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }
        if(isinf(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }        
    }

    *bitpix_ptr = bitpix;
    *data_arr_ptr = data_arr;
    
    return (status);
}


int MifFits::InFitsCubeF(string infile,
                         const MifImgInfo* const img_info,
                         int* const bitpix_ptr,
                         float** const data_arr_ptr)
{
    fitsfile* fptr_in = NULL;
    int iomode = 0;
    int status = 0; // status for fitsIO
    fits_open_file(&fptr_in, infile.c_str(),
                   iomode, &status);
    int hdunum = 0;
    fits_get_num_hdus(fptr_in, &hdunum, &status);
    printf("hdunum = %d\n", hdunum);

    int keysexist = 0;
    int morekeys = 0;
    fits_get_hdrspace(fptr_in, &keysexist, &morekeys, &status);
    printf("keysexist = %d\n", keysexist);

    int naxis = 0;
    fits_get_img_dim(fptr_in, &naxis, &status);
    printf("naxis = %d\n", naxis);
    if(3 != naxis){
        printf("bad naxis (= %d)\n", naxis);
        abort();
    }
    long* naxes = new long [naxis];
    int maxdim = naxis;
    fits_get_img_size(fptr_in, maxdim, naxes, &status);
    for(int idim = 0; idim < naxis; idim ++){
        printf("naxes[%d] = %ld\n", idim, naxes[idim]);
    }
    delete [] naxes;

    int bitpix = 0;
    fits_get_img_type(fptr_in, &bitpix, &status);
    printf("bitpix = %d\n", bitpix);
    
    // vectorized 3D cube for sub image
    long naxes_sub[3];
    naxes_sub[0] = img_info->GetNaxesArrElm(0);
    naxes_sub[1] = img_info->GetNaxesArrElm(1);
    naxes_sub[2] = img_info->GetNaxesArrElm(2);
    long npix_cube_sub_vec = naxes_sub[0] * naxes_sub[1] * naxes_sub[2];

    float* data_arr = new float [npix_cube_sub_vec];
    long inc[3] = {1,1,1};
    fits_read_subset(fptr_in, TFLOAT,
                     img_info->GetFpixelArr(), img_info->GetLpixelArr(),
                     inc, NULL, data_arr, NULL, &status);
    fits_close_file(fptr_in, &status);
    fits_report_error(stderr, status);

    for(long iarr = 0; iarr < npix_cube_sub_vec; iarr++){
        if(isnan(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }
        if(isinf(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }        
    }

    *bitpix_ptr = bitpix;
    *data_arr_ptr = data_arr;

    return (status);
}


int MifFits::InFitsCubeD(string infile,
                         const MifImgInfo* const img_info,
                         int* const bitpix_ptr,
                         double** const data_arr_ptr)
{
    fitsfile* fptr_in = NULL;
    int iomode = 0;
    int status = 0; // status for fitsIO
    fits_open_file(&fptr_in, infile.c_str(),
                   iomode, &status);
    int hdunum = 0;
    fits_get_num_hdus(fptr_in, &hdunum, &status);
    printf("hdunum = %d\n", hdunum);

    int keysexist = 0;
    int morekeys = 0;
    fits_get_hdrspace(fptr_in, &keysexist, &morekeys, &status);
    printf("keysexist = %d\n", keysexist);

    int naxis = 0;
    fits_get_img_dim(fptr_in, &naxis, &status);
    printf("naxis = %d\n", naxis);
    if(3 != naxis){
        printf("bad naxis (= %d)\n", naxis);
        abort();
    }
    long* naxes = new long [naxis];
    int maxdim = naxis;
    fits_get_img_size(fptr_in, maxdim, naxes, &status);
    for(int idim = 0; idim < naxis; idim ++){
        printf("naxes[%d] = %ld\n", idim, naxes[idim]);
    }
    delete [] naxes;

    int bitpix = 0;
    fits_get_img_type(fptr_in, &bitpix, &status);
    printf("bitpix = %d\n", bitpix);
    
    // vectorized 3D cube for sub image
    long naxes_sub[3];
    naxes_sub[0] = img_info->GetNaxesArrElm(0);
    naxes_sub[1] = img_info->GetNaxesArrElm(1);
    naxes_sub[2] = img_info->GetNaxesArrElm(2);
    long npix_cube_sub_vec = naxes_sub[0] * naxes_sub[1] * naxes_sub[2];

    double* data_arr = new double [npix_cube_sub_vec];
    long inc[3] = {1,1,1};
    fits_read_subset(fptr_in, TDOUBLE,
                     img_info->GetFpixelArr(), img_info->GetLpixelArr(),
                     inc, NULL, data_arr, NULL, &status);
    fits_close_file(fptr_in, &status);
    fits_report_error(stderr, status);

    for(long iarr = 0; iarr < npix_cube_sub_vec; iarr++){
        if(isnan(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }
        if(isinf(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }        
    }

    *bitpix_ptr = bitpix;
    *data_arr_ptr = data_arr;

    return (status);
}


int MifFits::InFits4dF(string infile,
                       const MifImgInfo* const img_info,
                       int* const bitpix_ptr,
                       float** const data_arr_ptr)
{
    fitsfile* fptr_in = NULL;
    int iomode = 0;
    int status = 0; // status for fitsIO
    fits_open_file(&fptr_in, infile.c_str(),
                   iomode, &status);
    int hdunum = 0;
    fits_get_num_hdus(fptr_in, &hdunum, &status);
    printf("hdunum = %d\n", hdunum);

    int keysexist = 0;
    int morekeys = 0;
    fits_get_hdrspace(fptr_in, &keysexist, &morekeys, &status);
    printf("keysexist = %d\n", keysexist);

    int naxis = 0;
    fits_get_img_dim(fptr_in, &naxis, &status);
    printf("naxis = %d\n", naxis);
    if(4 != naxis){
        printf("bad naxis (= %d)\n", naxis);
        abort();
    }
    long* naxes = new long [naxis];
    int maxdim = naxis;
    fits_get_img_size(fptr_in, maxdim, naxes, &status);
    for(int idim = 0; idim < naxis; idim ++){
        printf("naxes[%d] = %ld\n", idim, naxes[idim]);
    }
    delete [] naxes;

    int bitpix = 0;
    fits_get_img_type(fptr_in, &bitpix, &status);
    printf("bitpix = %d\n", bitpix);
    
    // vectorized 4D data for sub data
    long naxes_sub[4];
    naxes_sub[0] = img_info->GetNaxesArrElm(0);
    naxes_sub[1] = img_info->GetNaxesArrElm(1);
    naxes_sub[2] = img_info->GetNaxesArrElm(2);
    naxes_sub[3] = img_info->GetNaxesArrElm(3);
    long npix_sub_vec = naxes_sub[0] * naxes_sub[1] * naxes_sub[2] * naxes_sub[3];
    float* data_arr = new float [npix_sub_vec];
    long inc[4] = {1,1,1,1};
    fits_read_subset(fptr_in, TFLOAT,
                     img_info->GetFpixelArr(), img_info->GetLpixelArr(),
                     inc, NULL, data_arr, NULL, &status);
    fits_close_file(fptr_in, &status);
    fits_report_error(stderr, status);
    
    for(long iarr = 0; iarr < npix_sub_vec; iarr++){
        if(isnan(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }
        if(isinf(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }        
    }
    *bitpix_ptr = bitpix;
    *data_arr_ptr = data_arr;
    return (status);
}

int MifFits::InFits4dD(string infile,
                       const MifImgInfo* const img_info,
                       int* const bitpix_ptr,
                       double** const data_arr_ptr)
{
    fitsfile* fptr_in = NULL;
    int iomode = 0;
    int status = 0; // status for fitsIO
    fits_open_file(&fptr_in, infile.c_str(),
                   iomode, &status);
    int hdunum = 0;
    fits_get_num_hdus(fptr_in, &hdunum, &status);
    printf("hdunum = %d\n", hdunum);

    int keysexist = 0;
    int morekeys = 0;
    fits_get_hdrspace(fptr_in, &keysexist, &morekeys, &status);
    printf("keysexist = %d\n", keysexist);

    int naxis = 0;
    fits_get_img_dim(fptr_in, &naxis, &status);
    printf("naxis = %d\n", naxis);
    if(4 != naxis){
        printf("bad naxis (= %d)\n", naxis);
        abort();
    }
    long* naxes = new long [naxis];
    int maxdim = naxis;
    fits_get_img_size(fptr_in, maxdim, naxes, &status);
    for(int idim = 0; idim < naxis; idim ++){
        printf("naxes[%d] = %ld\n", idim, naxes[idim]);
    }
    delete [] naxes;

    int bitpix = 0;
    fits_get_img_type(fptr_in, &bitpix, &status);
    printf("bitpix = %d\n", bitpix);
    
    // vectorized 4D data for sub data
    long naxes_sub[4];
    naxes_sub[0] = img_info->GetNaxesArrElm(0);
    naxes_sub[1] = img_info->GetNaxesArrElm(1);
    naxes_sub[2] = img_info->GetNaxesArrElm(2);
    naxes_sub[3] = img_info->GetNaxesArrElm(3);
    long npix_sub_vec = naxes_sub[0] * naxes_sub[1] * naxes_sub[2] * naxes_sub[3];
    double* data_arr = new double [npix_sub_vec];
    long inc[4] = {1,1,1,1};
    fits_read_subset(fptr_in, TDOUBLE,
                     img_info->GetFpixelArr(), img_info->GetLpixelArr(),
                     inc, NULL, data_arr, NULL, &status);
    fits_close_file(fptr_in, &status);
    fits_report_error(stderr, status);
    for(long iarr = 0; iarr < npix_sub_vec; iarr++){
        if(isnan(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }
        if(isinf(data_arr[iarr])){
            data_arr[iarr] = 0.0;
        }        
    }
    *bitpix_ptr = bitpix;
    *data_arr_ptr = data_arr;
    return (status);
}


int MifFits::OutFitsImageF(string outdir, string outfile_head, string tag,
                           int naxis,
                           int bitpix,
                           const long* const naxes,
                           const float* const data_arr)
{
    int status = 0;
    if(2 != naxis){
        abort();
    }
    long npix_image = naxes[0] * naxes[1];
    char outfile[kLineSize];
    sprintf(outfile, "!%s/%s_%s.fits",
            outdir.c_str(),
            outfile_head.c_str(),
            tag.c_str());
    fitsfile* fptr_out = NULL;
    fits_create_file(&fptr_out, outfile, &status);
    fits_create_img(fptr_out, bitpix, naxis, const_cast<long*>(naxes), &status);

    long firstpix[2] = {1,1};
    fits_write_pix(fptr_out, TFLOAT, firstpix,
                   npix_image, const_cast<float*>(data_arr), &status);
    fits_close_file(fptr_out, &status);
    fits_report_error(stderr, status);

    return status;
}

int MifFits::OutFitsImageD(string outdir, string outfile_head, string tag,
                           int naxis,
                           int bitpix,
                           const long* const naxes,
                           const double* const data_arr)
{
    int status = 0;
    if(2 != naxis){
        abort();
    }
    long npix_image = naxes[0] * naxes[1];
    char outfile[kLineSize];
    sprintf(outfile, "!%s/%s_%s.fits",
            outdir.c_str(),
            outfile_head.c_str(),
            tag.c_str());
    fitsfile* fptr_out = NULL;
    fits_create_file(&fptr_out, outfile, &status);
    fits_create_img(fptr_out, bitpix, naxis, const_cast<long*>(naxes), &status);

    long firstpix[2] = {1,1};
    fits_write_pix(fptr_out, TDOUBLE, firstpix,
                   npix_image, const_cast<double*>(data_arr), &status);
    fits_close_file(fptr_out, &status);
    fits_report_error(stderr, status);

    return status;
}


int MifFits::OutFitsCubeF(string outdir, string outfile_head, string tag,
                          int naxis,
                          int bitpix,
                          const long* const naxes,
                          const float* const data_arr)
{
    int status = 0;
    if(3 != naxis){
        abort();
    }
    long npix_cube = naxes[0] * naxes[1] * naxes[2];
    char outfile[kLineSize];
    sprintf(outfile, "!%s/%s_%s.fits",
            outdir.c_str(),
            outfile_head.c_str(),
            tag.c_str());
    fitsfile* fptr_out = NULL;
    fits_create_file(&fptr_out, outfile, &status);
    fits_create_img(fptr_out, bitpix, naxis, const_cast<long*>(naxes), &status);

    long firstpix[3] = {1,1,1};
    fits_write_pix(fptr_out, TFLOAT, firstpix,
                   npix_cube, const_cast<float*>(data_arr), &status);
    fits_close_file(fptr_out, &status);
    fits_report_error(stderr, status);

    return status;
}


int MifFits::OutFitsCubeD(string outdir, string outfile_head, string tag,
                          int naxis,
                          int bitpix,
                          const long* const naxes,
                          const double* const data_arr)
{
    int status = 0;
    if(3 != naxis){
        abort();
    }
    long npix_cube = naxes[0] * naxes[1] * naxes[2];
    char outfile[kLineSize];
    sprintf(outfile, "!%s/%s_%s.fits",
            outdir.c_str(),
            outfile_head.c_str(),
            tag.c_str());
    fitsfile* fptr_out = NULL;
    fits_create_file(&fptr_out, outfile, &status);
    fits_create_img(fptr_out, bitpix, naxis, const_cast<long*>(naxes), &status);

    long firstpix[3] = {1,1,1};
    fits_write_pix(fptr_out, TDOUBLE, firstpix,
                   npix_cube, const_cast<double*>(data_arr), &status);
    fits_close_file(fptr_out, &status);
    fits_report_error(stderr, status);

    return status;
}
