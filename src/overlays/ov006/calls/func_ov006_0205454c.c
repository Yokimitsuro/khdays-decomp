/* func_ov006_0205454c -- character-select (Mission Mode) scene constructor, ov006.
 * Scene id 7 (ov000 is the title, id 1).
 *
 * Allocates the char-select manager context (0x97f8 bytes) and stores it in the scene-object
 * slot data_ov006_02056664, brings up the 2D display (POWCNT1, VRAM banks BG=3/subBG=4/
 * OBJ=0x70/subOBJ=8, graphics mode), programs the BG priority registers (main BG0..3 =
 * 1/3/2/0, sub BG1..3 = 2/1/0), allocates eight 0x600-byte cell buffers, loads the font into
 * both BG3 and BG7 (data_..540 and data_..55c are BOTH "/text/font_eu_10all.NFTR") and the
 * char-select UI pack (data_..578 = "UI/mlt/res.p2", data_..588 = "UI/mlt/res_&.p2", the
 * localised variant, via func_02024ee8), seeds the animation state, sets the display mode
 * bits, and boots the sub-state (id 0xd when arg!=0) before returning the next scene-state
 * function (func_ov006_02054a00).
 *
 * Resource paths confirmed by reading RAM at runtime. */
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;

struct S5 { int w[5]; };

extern int *data_ov006_02056664;
extern int data_ov006_02056540, data_ov006_0205655c;
extern int data_ov006_02056578, data_ov006_02056588;
extern struct S5 data_ov006_0205629c;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int data, unsigned int size);
extern void func_0201e1d0(void);
extern void func_02023c30(int a);
extern void GX_SetBankForBG(int a);
extern void GX_SetBankForSubBG(int a);
extern void GX_SetBankForOBJ(int a);
extern void GX_SetBankForSubOBJ(int a);
extern void GXS_SetGraphicsMode(int a);
extern void func_020056b4(int a, int b, int c);
extern int NNS_FndAllocFromDefaultExpHeapEx(int size, int align);
extern void MIi_CpuClear16(int val, int dst, int size);
extern void func_0202f7fc(int dst, int desc);
extern int func_02024ee8(int path, int mode);
extern void func_ov006_0204d098(int *dst, struct S5 *src);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern void func_02035fb0(int *p, int a, int b, int c, int d);
extern void func_02035f84(int *p);
extern long long func_020031d4(void);
extern void func_ov006_02053734(int state);
extern void func_ov006_0205341c(int state);
extern void func_ov006_02053b24(int state);
extern void func_ov006_02054a00(void);

#define OBJ ((char *)data_ov006_02056664)

void *func_ov006_0205454c(int arg) {
    unsigned int i;
    int *base;
    long long anim;
    struct S5 param;

    data_ov006_02056664 = (int *)NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov006_02056664, 0, 0x97f8);
    func_0201e1d0();
    func_02023c30(0);

    *(vu16 *)0x04000304 |= 0x8000;
    *(vu32 *)0x04000000 &= ~0x38000000;
    *(vu32 *)0x04000000 &= ~0x07000000;
    GX_SetBankForBG(3);
    GX_SetBankForSubBG(4);
    GX_SetBankForOBJ(0x70);
    GX_SetBankForSubOBJ(8);
    GXS_SetGraphicsMode(0);
    func_020056b4(1, 0, 0);

    {
        vu16 *bg1 = (vu16 *)0x0400000a;
        vu16 *bgs2 = (vu16 *)0x0400100c;
        vu16 *bg0 = (vu16 *)0x04000008;
        *bg1 = *bg1 & ~3 | 3;
        bg1[1] = bg1[1] & ~3 | 2;
        *bg0 = *bg0 & ~3 | 1;
        bg1[2] = bg1[2] & ~3;
        *(vu16 *)0x0400100a = *(vu16 *)0x0400100a & ~3 | 2;
        *bgs2 = *bgs2 & ~3 | 1;
        bgs2[1] = bgs2[1] & ~3;
    }

    i = 0;
    do {
        *(int *)(OBJ + i * 4 + 0x94cc) = NNS_FndAllocFromDefaultExpHeapEx(0x600, 2);
        MIi_CpuClear16(0, *(int *)(OBJ + i * 4 + 0x94cc), 0x600);
        i = i + 1 & 0xff;
    } while (i < 8);

    func_0202f7fc((int)(OBJ + 0x9760), (int)&data_ov006_02056540);
    func_0202f7fc((int)(OBJ + 0x97ac), (int)&data_ov006_0205655c);
    *(int *)OBJ = func_02024ee8((int)&data_ov006_02056578, 0xe);
    *(int *)(OBJ + 4) = func_02024ee8((int)&data_ov006_02056588, 0xe);

    param = data_ov006_0205629c;
    func_ov006_0204d098((int *)(OBJ + 8), &param);
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    func_02035fb0((int *)(OBJ + 0x9544), 0, -0x10000, -0x10000, 0);
    func_02035f84((int *)(OBJ + 0x9574));
    func_02035f84((int *)(OBJ + 0x9590));

    *(vu32 *)0x04001000 = *(vu32 *)0x04001000 & ~0x1f00 | 0x1e00;
    *(vu32 *)0x04000000 = *(vu32 *)0x04000000 & ~0x1f00 | 0x1f00;

    base = data_ov006_02056664;
    anim = func_020031d4();
    *(long long *)((char *)base + 0x94c4) = anim;
    *(signed char *)((char *)base + 0x950c) = -1;
    if (arg != 0) {
        *(int *)(OBJ + 0x94f4) = 0xd;
    }
    func_ov006_02053734(*(int *)(OBJ + 0x94f4));
    func_ov006_0205341c(*(int *)(OBJ + 0x94f4));
    func_ov006_02053b24(*(int *)(OBJ + 0x94f4));
    return (void *)func_ov006_02054a00;
}
