/* Equivalent, readable C. NOT byte-exact YET (progress: 115->~103 diffs, size
 * within 4B). Structure, masks and per-region MMIO addressing now match; the
 * residual is register allocation:
 *   (1) param_1 must land in r6 (mine spills it to r7 because a disp-sub pointer
 *       grabs the callee-saved r6 in the first DISPCNT region);
 *   (2) the original preloads the DISPCNT base (mov r2,#0x4000000) EARLY,
 *       interleaved with the palette clears (scheduling), so region A uses r2/r1;
 *   (3) the palette-pair stack copy loads/stores high-half first ([2] then [0]);
 *   (4) bg[0x17e] wants add #0x2fc (one add) not a hoisted 0x200+0xfc split.
 * These are scheduling/coloring details; the asm stub keeps the blob byte-exact.
 * RESUME HERE for a focused register-tuning pass. */
extern int NNSi_FndGetCurrentRootHeap(void);
extern int OS_IsThreadAvailable_0x02023650(void);
extern void func_0202362c(int mode);
extern void func_0201e1d0(void);
extern void func_02023c30(int a);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForOBJ(int bank);
extern void GX_SetBankForSubOBJ(int bank);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int val, void *dst, int n);
extern void GX_LoadBGPltt(void *src, int off, int n);
extern void func_ov010_0204cac0(int handle, char *res);
extern int *func_ov010_0204cb04(int root, int flag);
extern void func_0202f7fc(int *dst, char *res);
extern void func_0202f834(int *a, int b, unsigned int c, unsigned short *d);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern int func_ov010_0204ce60(void);
extern unsigned short data_ov010_0204cf88[];
extern char data_ov010_0204cfb4[];
extern char data_ov010_0204cfc8[];

struct pltt_pair { unsigned short a, b; };

/* Full display/scene setup for the ov010 title screen: clear palettes, disable
 * BG layers, configure VRAM banks and BG control regs, load the palette, build
 * the root work object and its resources, then re-enable the BGs and hand back
 * the per-frame handler (func_ov010_0204ce60). */
int func_ov010_0204cb3c(unsigned int param_1) {
    int root = NNSi_FndGetCurrentRootHeap();
    struct pltt_pair pal = *(struct pltt_pair *)data_ov010_0204cf88;
    int saved;
    unsigned short attr[8];
    int *obj;

    saved = OS_IsThreadAvailable_0x02023650();
    func_0202362c(0);

    *(volatile unsigned short *)0x05000000 = 0;
    *(volatile unsigned short *)0x05000400 = 0;
    {
        volatile unsigned int *disp = (volatile unsigned int *)0x04000000;
        disp[0] &= ~0x1f00;
        disp[0x400] &= ~0x1f00;
    }
    func_0201e1d0();
    func_02023c30(0);
    {
        volatile unsigned short *pow = (volatile unsigned short *)0x04000304;
        volatile unsigned int *disp = (volatile unsigned int *)0x04000000;
        *pow |= 0x8000;
        disp[0] &= ~0x38000000;
        disp[0] &= ~0x7000000;
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
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x600);
    {
        volatile unsigned short *bg3 = (volatile unsigned short *)0x0400000e;
        *bg3 = *bg3 & 0x43 | 0x304;
    }
    GX_LoadBGPltt(&pal, 0, 4);
    func_ov010_0204cac0(root, data_ov010_0204cfb4);
    if (param_1 == 0xffffffff) {
        obj = func_ov010_0204cb04(root, 1);
    } else {
        obj = func_ov010_0204cb04(root, 0);
    }
    *(int *)(root + 0x74) = (int)obj;
    func_0202f7fc((int *)(root + 0xc), data_ov010_0204cfc8);
    attr[2] = 0x20;
    attr[3] = 0x18;
    attr[0] = 0;
    attr[1] = 0;
    attr[4] = 0;
    attr[6] = 0;
    attr[7] = 6;
    attr[5] = 0;
    func_0202f834((int *)(root + 0x18), 3, (unsigned int)(root + 0xc), attr);
    {
        volatile unsigned int *disp = (volatile unsigned int *)0x04000000;
        disp[0] = disp[0] & ~0x1f00 | 0x800;
        disp[0x400] = disp[0x400] & ~0x1f00 | 0x800;
    }
    func_0201e374(0);
    func_0201e3cc(0);
    *(int *)(root + 0x78) = 2;
    *(int *)(root + 0x7c) = param_1;
    func_0202362c(saved);
    return (int)func_ov010_0204ce60;
}
