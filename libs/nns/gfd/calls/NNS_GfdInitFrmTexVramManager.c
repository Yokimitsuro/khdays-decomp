

#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/gfd.h"

extern NNSGfdFuncAllocTexVram data_020423ec;
extern NNSGfdFuncFreeTexVram data_020423f0;
void NNSi_GfdSetTexNrmSearchArray(int idx1st, int idx2nd, int idx3rd, int idx4th, int idx5th);
NNSGfdTexKey NNS_GfdAllocFrmTexVram(u32 szByte, BOOL is4x4comp, u32 opt);
int NNS_GfdFreeFrmTexVram(NNSGfdTexKey memKey);
void NNS_GfdResetFrmTexVramState(void);
extern NNSGfdFrmTexVramMnager data_02047360;
extern void NNSi_GfdSetTexNrmSearchArray (int idx1st, int idx2nd, int idx3rd, int idx4th, int idx5th);
extern void NNS_GfdResetFrmTexVramState (void);
extern NNSGfdTexKey NNS_GfdAllocFrmTexVram (u32 szByte, BOOL is4x4comp, u32 opt);
extern int NNS_GfdFreeFrmTexVram (NNSGfdTexKey texKey);

/* NNS_GfdInitFrmTexVramManager -- NitroSystem gfd_FrameTexVramMan.c: NNS_GfdInitFrmTexVramManager. */
void NNS_GfdInitFrmTexVramManager (u16 numSlot, BOOL useAsDefault)
{

    if ( numSlot <= 2 ) {
        NNSi_GfdSetTexNrmSearchArray(4, 3, 2, 0, 1);
    } else {
        NNSi_GfdSetTexNrmSearchArray(4, 3, 0, 2, 1);
    }

    data_02047360.numSlot = numSlot;
    NNS_GfdResetFrmTexVramState();

    if (useAsDefault) {
        data_020423ec = NNS_GfdAllocFrmTexVram;
        data_020423f0 = NNS_GfdFreeFrmTexVram;
    }
}
