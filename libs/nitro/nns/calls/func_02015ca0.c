
#include "nitro/types.h"

typedef struct NNSG3dGlb {
    u8 pad00_8c[0x8c];
    u32 prmViewPort;
} NNSG3dGlb;

extern NNSG3dGlb NNS_G3dGlb;

void func_02015ca0(int *px1, int *py1, int *px2, int *py2)
{
    if (px1)
        *px1 = (int)(NNS_G3dGlb.prmViewPort & 0xff);
    if (py1)
        *py1 = (int)((NNS_G3dGlb.prmViewPort >> 8) & 0xff);
    if (px2)
        *px2 = (int)((NNS_G3dGlb.prmViewPort >> 16) & 0xff);
    if (py2)
        *py2 = (int)((NNS_G3dGlb.prmViewPort >> 24) & 0xff);
}
