/* func_ov010_0204cb3c ? title-screen / 2D-engine setup (580B). PROVEN lookahead
 * register-allocation tie ? belongs in nonmatching/. The reconstruction is CORRECT:
 * the first ~0x180 bytes are byte-exact and all 24 relocs align. The remaining diff
 * is a back-half callee-saved allocation cascade: mwcc lookahead-holds the sub-engine
 * address 0x04001000 in r6 (computed in the first DISPCNT block, reused in the second),
 * which displaces `param` to r7 and re-materializes 0; the ROM instead keeps `param`
 * in r6 and 0 in r7, and RECOMPUTES 0x04001000 (add r2,r1,#0x1000) in each block.
 * Both are valid allocations. Unreachable across 25 mwcc builds (incl. retail-era
 * 3.0/136) and 8 source forms (zero-unify / separate-ptr / direct-const / sub-var /
 * flag-early / decl-reorder). Same unsteerable class as func_ov010_0204cac0. See memory
 * reference_mwcc136_unlock. NOTE: func_0202f7fc takes 2 args here (leftover r2/r3 at the
 * call site) ? passing more forces a callee-saved hold + extra mov.
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern int OS_IsThreadAvailable_0x02023650(void);
extern void func_0202362c(int a);
extern void func_0201e1d0(void);
extern void func_02023c30(int a);
extern void GX_SetBankForBG(int a);
extern void GX_SetBankForSubBG(int a);
extern void GX_SetBankForOBJ(int a);
extern void GX_SetBankForSubOBJ(int a);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int a, void *b, int n);
extern void GX_LoadBGPltt(void *p, int a, int b);
extern void func_ov010_0204cac0(int handle, char *name);
extern int *func_ov010_0204cb04(int heap, int flag);
extern void func_0202f7fc(int *p, char *name);
extern void func_0202f834(unsigned int *p, int a, unsigned int q, unsigned short *rect);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern unsigned short data_ov010_0204cf88[];
extern char data_ov010_0204cfb4[];
extern char data_ov010_0204cfc8[];
extern void func_ov010_0204ce60(void);

struct Frame {
    unsigned short v28;
    unsigned short v26;
    unsigned short rect[8];
};

void *func_ov010_0204cb3c(unsigned int param) {
    struct Frame f;
    unsigned int *heap;
    int iVar4;
    unsigned int u8;
    void *buf;
    int *node;

    heap = (unsigned int *)NNSi_FndGetCurrentRootHeap();
    f.v26 = data_ov010_0204cf88[1];
    f.v28 = data_ov010_0204cf88[0];
    iVar4 = OS_IsThreadAvailable_0x02023650();
    func_0202362c(0);
    {
        volatile unsigned short *pal = (volatile unsigned short *)0x05000000;
        volatile unsigned int *reg = (volatile unsigned int *)0x04000000;
        pal[0] = 0;
        pal[0x200] = 0;
        reg[0] &= 0xffffe0ff;
        reg[0x400] &= 0xffffe0ff;
    }
    func_0201e1d0();
    func_02023c30(0);
    {
        volatile unsigned int *reg = (volatile unsigned int *)0x04000000;
        *(volatile unsigned short *)0x04000304 |= 0x8000;
        reg[0] &= 0xc7ffffff;
        reg[0] &= 0xf8ffffff;
    }
    GX_SetBankForBG(3);
    GX_SetBankForSubBG(4);
    GX_SetBankForOBJ(0x70);
    GX_SetBankForSubOBJ(8);
    {
        volatile unsigned short *bg = (volatile unsigned short *)0x04000008;
        bg[0] = bg[0] & ~3 | 3;
        bg[1] = bg[1] & ~3 | 2;
        bg[2] = bg[2] & ~3 | 1;
        bg[3] = bg[3] & ~3;
        bg[0x17e] |= 0x8000;
    }
    buf = G2_GetBG3ScrPtr();
    MIi_CpuClearFast(0, buf, 0x600);
    u8 = *(volatile unsigned short *)0x0400000e & 0x43 | 0x304;
    *(volatile unsigned short *)0x0400000e = (unsigned short)u8;
    GX_LoadBGPltt(&f, 0, 4);
    func_ov010_0204cac0((int)heap, data_ov010_0204cfb4);
    if (param == 0xffffffff) {
        node = func_ov010_0204cb04((int)heap, 1);
    } else {
        node = func_ov010_0204cb04((int)heap, 0);
    }
    heap[0x1d] = (unsigned int)node;
    func_0202f7fc((int *)(heap + 3), data_ov010_0204cfc8);
    f.rect[2] = 0x20;
    f.rect[3] = 0x18;
    f.rect[0] = 0;
    f.rect[1] = 0;
    f.rect[4] = 0;
    f.rect[6] = 0;
    f.rect[7] = 6;
    f.rect[5] = 0;
    func_0202f834(heap + 6, 3, (unsigned int)(heap + 3), f.rect);
    {
        volatile unsigned int *reg = (volatile unsigned int *)0x04000000;
        reg[0] = reg[0] & 0xffffe0ff | 0x800;
        reg[0x400] = reg[0x400] & 0xffffe0ff | 0x800;
    }
    func_0201e374(0);
    func_0201e3cc(0);
    heap[0x1e] = 2;
    heap[0x1f] = param;
    func_0202362c(iVar4);
    return func_ov010_0204ce60;
}
