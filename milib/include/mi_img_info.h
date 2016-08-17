#ifndef MORIIISM_MILIB_IMG_INFO_H_
#define MORIIISM_MILIB_IMG_INFO_H_

#include "mi_iolib.h"

// format of img_info file:
// image data :
//   # x(pixel)  y(pixel)
//   fpixel[0] fpixel[1]
//   lpixel[0] lpixel[1]
// cube data :
//   # x(pixel)  y(pixel)  t(frame)
//   fpixel[0] fpixel[1] fpixel[2]
//   lpixel[0] lpixel[1] lpixel[2]
//

class MiImgInfo : public MiObject{
public:
    explicit MiImgInfo(string title = "") :
        MiObject("MiImgInfo", title),
        naxis_(0),
        fpixel_arr_(NULL),
        lpixel_arr_(NULL),
        naxes_arr_(NULL) {}
    ~MiImgInfo() {
        Null();
    }
    // Init & Set
    void InitSetImg(long fpixel0, long fpixel1,
                    long lpixel0, long lpixel1);
    void InitSetCube(long fpixel0, long fpixel1, long fpixel2,
                     long lpixel0, long lpixel1, long lpixel2);
    // Load
    void Load(string file);

    // const func
    int GetNaxis() const {return naxis_;};
    long* GetFpixelArr() const {return fpixel_arr_;};
    long* GetLpixelArr() const {return lpixel_arr_;};
    long* GetNaxesArr() const {return naxes_arr_;};
    long GetFpixelArrElm(int iaxis) const {return fpixel_arr_[iaxis];};
    long GetLpixelArrElm(int iaxis) const {return lpixel_arr_[iaxis];};
    long GetNaxesArrElm(int iaxis) const {return naxes_arr_[iaxis];};
    
    long GetNpixelImg() const;
    long GetNframe() const;
    long GetNpixelTotal() const;

    void PrintInfo() const;
    
private:
    int naxis_;
    long* fpixel_arr_;
    long* lpixel_arr_;
    long* naxes_arr_;

    void Null();

    void Init(int naxis);
    void SetFpixelArrElm(int iaxis, long fpixel);
    void SetLpixelArrElm(int iaxis, long lpixel);
    void SetNaxesArrElm(int iaxis, long naxes);
    void SetNaxesArr();
};

#endif // MORIIISM_MILIB_IMG_INFO_H_
