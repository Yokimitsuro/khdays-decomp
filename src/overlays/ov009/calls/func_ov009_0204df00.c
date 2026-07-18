/*
 * func_ov009_0204df00 -- x3 (ov008/...). Commit the built page: unload the source overlay and push the
 * two half-screens. Context at data_02090f04[1]+0x9000. Clear the scroll counter *(u16)+0x9610=0, set
 * the "ready" flag +0x95f4=1, unload the resource overlay at +0x963e, and run the shared prep
 * 0204fc50. For each half whose enable flag (+0x9628 / +0x962c) is set, blit it via 02054390 with the
 * scroll counter (the second half's surface base is +0x4a80). Flush both command lists at +0x9500 and
 * +0x954c (020554e4), finalize (0204ffe4), and return the resulting page handle at +0x9614.
 */
extern void FS_UnloadOverlayImage_0x020362ec(unsigned short *p);
extern void func_ov009_0204d7f4(void);
extern void func_ov009_02051524(int surface, int scroll);
extern void func_ov009_020522a8(void *cmdlist);
extern void func_ov009_0204db88(void);
extern int data_ov009_020563e4[];

#define CTXV (*(volatile int *)((char *)data_ov009_020563e4 + 4))

int func_ov009_0204df00(void) {
    *(unsigned short *)(CTXV + 0x9610) = 0;
    *(int *)(CTXV + 0x95f4) = 1;
    FS_UnloadOverlayImage_0x020362ec((unsigned short *)(CTXV + 0x963e));
    func_ov009_0204d7f4();
    if (*(int *)(data_ov009_020563e4[1] + 0x9628) != 0) {
        func_ov009_02051524(data_ov009_020563e4[1],
                            *(unsigned short *)(data_ov009_020563e4[1] + 0x9610));
    }
    if (*(int *)(data_ov009_020563e4[1] + 0x962c) != 0) {
        func_ov009_02051524(data_ov009_020563e4[1] + 0x4a80,
                            *(unsigned short *)(data_ov009_020563e4[1] + 0x9610));
    }
    func_ov009_020522a8((void *)(data_ov009_020563e4[1] + 0x9500));
    func_ov009_020522a8((void *)(data_ov009_020563e4[1] + 0x954c));
    func_ov009_0204db88();
    return *(int *)(data_ov009_020563e4[1] + 0x9614);
}
