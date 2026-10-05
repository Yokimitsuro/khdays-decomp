/*
 * NNS_G3dDraw (NitroSystem G3D): draw a render object. When its flag 0x10 says the animation hints
 * are stale, clear the three hint vectors (+0x3c/+0x44/+0x4c) and rebuild each from its animation
 * list (obj[2]/obj[4]/obj[6]: material, joint, visibility) with updateHintVec__2, then clear the
 * flag. Then run NNSi_G3dDrawInternal over it with the global render state NNS_G3dRS, or, when
 * there is none, with a 0x188-byte one on the stack that NNS_G3dRS points at for the call. The u16
 * at data_027e0654 is cleared on the way out.
 */

extern void INITi_CpuClear32_0x01ff86fc(int value, void *dest, int size);
extern void updateHintVec__2(unsigned int *bits, void *node);
extern void NNSi_G3dDrawInternal(void *buf, unsigned int *ctx);
extern unsigned int *NNS_G3dRS;
extern unsigned short data_027e0654;

void NNS_G3dDraw(char *pArg1)
{
    unsigned int *param_1 = (unsigned int *)pArg1;
    unsigned int scratch[98];

    if ((*param_1 & 0x10) == 0x10) {
        INITi_CpuClear32_0x01ff86fc(0, param_1 + 0xf, 8);
        INITi_CpuClear32_0x01ff86fc(0, param_1 + 0x11, 8);
        INITi_CpuClear32_0x01ff86fc(0, param_1 + 0x13, 8);
        if (param_1[2] != 0)
            updateHintVec__2(param_1 + 0xf, (void *)param_1[2]);
        if (param_1[4] != 0)
            updateHintVec__2(param_1 + 0x11, (void *)param_1[4]);
        if (param_1[6] != 0)
            updateHintVec__2(param_1 + 0x13, (void *)param_1[6]);
        *param_1 &= ~0x10;
    }
    if (NNS_G3dRS != 0) {
        NNSi_G3dDrawInternal(NNS_G3dRS, param_1);
    } else {
        NNS_G3dRS = scratch;
        NNSi_G3dDrawInternal(scratch, param_1);
        NNS_G3dRS = 0;
    }
    data_027e0654 = 0;
}
