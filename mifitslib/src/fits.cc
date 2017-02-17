#include "mif_fits.h"

int MifFits::InFitsImageF(string infile,
                          const MifImgInfo* const img_info,
                          double** const data_arr_ptr)
{
    //
    // fitsfile
    //
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
    if(2 > naxis){
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
    
    // vectorized 2D image for sub image
    long naxes_sub[3];
    naxes_sub[0] = img_info->GetNaxesArrElm(0);
    naxes_sub[1] = img_info->GetNaxesArrElm(1);
    long npix_image_sub_vec = naxes_sub[0] * naxes_sub[1];
    
    float* image_sub_vec = new float [npix_image_sub_vec];
    long inc[2] = {1,1};
    // long inc[4] = {1,1,1,1};
    fits_read_subset(fptr_in, TFLOAT,
                     img_info->GetFpixelArr(), img_info->GetLpixelArr(),
                     inc, NULL, image_sub_vec, NULL, &status);
    
    fits_close_file(fptr_in, &status);
    fits_report_error(stderr, status);

    // float --> double
    double* data_arr = new double [npix_image_sub_vec];
    for(long ivec = 0; ivec < npix_image_sub_vec; ivec ++){
        data_arr[ivec] = image_sub_vec[ivec];
    }

    delete [] image_sub_vec;
    
    *data_arr_ptr = data_arr;
    
    return (status);
}


int MifFits::InFitsCubeF(string infile,
                         const MifImgInfo* const img_info,
                         double** const data_arr_ptr)
{
    //
    // fitsfile
    //
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
    
    // vectorized 3D cube for sub image
    long naxes_sub[3];
    naxes_sub[0] = img_info->GetNaxesArrElm(0);
    naxes_sub[1] = img_info->GetNaxesArrElm(1);
    naxes_sub[2] = img_info->GetNaxesArrElm(2);
    long npix_cube_sub_vec = naxes_sub[0] * naxes_sub[1] * naxes_sub[2];

    float* cube_sub_vec = new float [npix_cube_sub_vec];
    long inc[3] = {1,1,1};    
    fits_read_subset(fptr_in, TFLOAT,
                     img_info->GetFpixelArr(), img_info->GetLpixelArr(),
                     inc, NULL, cube_sub_vec, NULL, &status);
    fits_close_file(fptr_in, &status);
    fits_report_error(stderr, status);

    // float --> double
    double* data_arr = new double [npix_cube_sub_vec];
    for(long ivec = 0; ivec < npix_cube_sub_vec; ivec ++){
        data_arr[ivec] = cube_sub_vec[ivec];
    }

    delete [] cube_sub_vec;
    
    *data_arr_ptr = data_arr;

    return (status);
}



int MifFits::OutFitsImageF(string outdir, string outfile_head, string tag,
                           int naxis, const long* const naxes,
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
    fits_create_img(fptr_out, FLOAT_IMG, naxis, const_cast<long*>(naxes), &status);

    long firstpix[2] = {1,1};
    fits_write_pix(fptr_out, TFLOAT, firstpix,
                   npix_image, const_cast<float*>(data_arr), &status);
    fits_close_file(fptr_out, &status);
    fits_report_error(stderr, status);

    return status;
}

int MifFits::OutFitsCubeF(string outdir, string outfile_head, string tag,
                          int naxis, const long* const naxes,
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
    fits_create_img(fptr_out, FLOAT_IMG, naxis, const_cast<long*>(naxes), &status);

    long firstpix[3] = {1,1,1};
    fits_write_pix(fptr_out, TFLOAT, firstpix,
                   npix_cube, const_cast<float*>(data_arr), &status);
    fits_close_file(fptr_out, &status);
    fits_report_error(stderr, status);

    return status;
}
