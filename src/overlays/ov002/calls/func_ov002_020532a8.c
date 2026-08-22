/*
 * Ov002_CreateUiContext - build the overlay's UI context and publish it.
 *
 * Takes the whole 0x128-byte object from the root heap, wipes it, and wires up
 * everything the rest of the overlay reads through the global slot: the three
 * object lists, the script runner at +0xdc with its five-word setup and its two
 * callbacks, the blend tween at +0xc0, the hardware blend registers, the
 * vblank task, and the per-frame step - which is chosen by a global, one build
 * of the game getting a different one.
 *
 * Then each of the six map slots gets its enable flag from the caller's mask
 * and a cleared 0x800-byte buffer, and the item resource table is pointed at
 * the context's own +0x54 so the accessors reach the flags and buffers through
 * one indirection.
 *
 * THUMB. Returns the per-frame entry point the caller installs.
 */

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);
extern void NNS_FndInitList(void *pList, int nLinkOffset);
extern void func_ov002_020543b8(void *pRunner, int *pSetup);
extern void func_ov002_02054c38(void *pRunner, void *pfnA, void *pfnB);
extern void func_02035f84(void *pTween);
extern void G2x_SetBlendAlpha_(int nReg, int nFirst, int nSecond, int nEva,
                               int nEvb);
extern void func_02000f48(int nSlot, const char *pName, void *pfnTask);
extern int func_02020a9c(void);
extern void func_ov002_020538c0(void *pfnStep);
extern void func_ov002_02054480(void *pRunner, char *pName);
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int nSize, int nAlign);
extern void MIi_CpuClear16(int nValue, void *pDst, unsigned int nSize);

extern void func_ov002_02053048(void);
extern void func_ov002_02053060(void);
extern void func_ov002_020539f4(void);
extern void func_ov002_02053a4c(void);
extern void func_ov002_02052bd0(void);
extern void func_ov002_02052c28(void);
extern void func_ov002_02052ce4(void);
extern void func_ov002_02053484(void);

extern char data_ov002_0207e8a8[];
extern int data_ov002_0207f60c;

void *func_ov002_020532a8(int *pDesc)
{
    unsigned char *pUi;
    int i;
    unsigned char *pSlot;
    int aSetup[5];

    pUi = (unsigned char *)NNSi_FndGetCurrentRootHeap();
    *(unsigned char **)&data_ov002_0207f60c = pUi;
    MI_CpuFill8(pUi, 0, 0x128);
    *(int *)(pUi + 0xbc) = -1;

    NNS_FndInitList(pUi + 0x98, 0x34);
    NNS_FndInitList(pUi + 0xa4, 4);
    NNS_FndInitList(pUi + 0xb0, 8);

    aSetup[0] = 0x140;
    aSetup[1] = 0x1c;
    aSetup[2] = 0xc;
    aSetup[3] = (int)func_ov002_02053048;
    aSetup[4] = (int)func_ov002_02053060;
    func_ov002_020543b8(pUi + 0xdc, aSetup);
    func_ov002_02054c38(pUi + 0xdc, func_ov002_020539f4, func_ov002_02053a4c);

    *(int *)pUi = 0;
    pUi[0x11] = 0;
    *(int *)(pUi + 8) = pDesc[2];
    func_02035f84(pUi + 0xc0);

    G2x_SetBlendAlpha_(0x04000050, 8, 0x21, 0, 0x10);
    func_02000f48(1, data_ov002_0207e8a8, func_ov002_02052bd0);

    if (func_02020a9c() != 0x2a) {
        func_ov002_020538c0(func_ov002_02052c28);
    } else {
        func_ov002_020538c0(func_ov002_02052ce4);
    }

    if (pDesc[0] != 0) {
        func_ov002_02054480(pUi + 0xdc, (char *)pDesc[0]);
    }

    for (i = 0, pSlot = pUi; i < 6; i++) {
        *(int *)(pSlot + 0x70) = (*((unsigned char *)pDesc + 4) & 1 << i) != 0;
        *(int *)(pSlot + 0x58) = (int)NNS_FndAllocFromDefaultExpHeapEx(0x800, 2);
        MIi_CpuClear16(0, *(void **)(pSlot + 0x58), 0x800);
        pSlot = pSlot + 4;
    }

    *(int *)(pUi + 0x54) = -1;
    *(int *)(pUi + 0x94) = (int)(pUi + 0x54);
    return (void *)func_ov002_02053484;
}
