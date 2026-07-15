/* func_ov000_0204d7c8 -- Scene 1 (boot/logo) fresh-boot graphics setup, ov000.
 * Reached from the scene-1 ctor func_ov000_0204d630 on a fresh boot. Brings up the
 * 2D/3D display for the first screen: assigns VRAM banks (tex/OBJ-ext-pltt/BG/subBG/
 * subOBJ), programs both display engines (DISPCNT, BG control regs), loads the logo
 * archive (func_0201ef9c) and 8 sub-resources into the scene heap, wires up the
 * animation/sequence players (func_02024a6c/ae0), copies a 0x200-byte palette, and
 * returns the scene's running state fn. arg selects the entry variant (0=fresh). */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef volatile u16   vu16;
typedef volatile u32   vu32;
typedef void          *StateFn;

#define reg_GX_DISPCNT  (*(vu32 *)0x04000000)
#define reg_G2_BG0CNT   (*(vu16 *)0x04000008)

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_ov000_0204d72c(void *heap);
extern void  func_0201e374(int);
extern void  func_0201e3cc(int);
extern void  GX_SetBankForTex(int);
extern void  GX_BeginLoadOBJExtPltt(int);
extern void  GX_SetBankForBG(int);
extern void  GX_SetBankForSubBG(int);
extern void  GX_SetBankForSubOBJ(int);
extern void  func_02010e80(int, int);
extern void  func_02011174(int, int);
extern void  func_020056b4(int, int, int);
extern void  GXS_SetGraphicsMode(int);
extern void  func_0202a634(void *, u32, int, int);
extern void  func_0202accc(void *, int, void *, int);
extern void  func_02023c60(void *);
extern u32   func_0201ef9c(u32 addr, int mode);
extern void  func_02024c94(void *slot, u32 handle, int, int, int);
extern void  func_02024a6c(int, void *, void *, int, int);
extern void  func_02024ae0(int, u32, int, u32);
extern void  MIi_CpuCopy32(void *src, void *dst, int size);
extern void  func_ov000_0204cac0(void);
extern void  func_02023c30(int);
extern void  func_02024d68(void);
extern void  func_02036298(void *, void *);
extern void  func_ov000_0204e0c8(void);
extern int   func_0202aef8(void *, int);
extern void  func_01fff774(void *, int, int);
extern int   func_02034014(int);
extern void  func_02033fb4(int, int);
extern void  func_ov000_0204df98(void);
extern void  func_ov000_0204dc38(void);
extern void  func_ov000_0204ea68(void);
extern signed char data_ov000_0205a9d4[];

StateFn func_ov000_0204d7c8(int arg) {
    u32 *h = (u32 *)NNSi_FndGetCurrentRootHeap();
    func_ov000_0204d72c(h);
    if (arg == 0) {
        func_0201e374(0x10);
        func_0201e3cc(0x10);
    } else {
        func_0201e374(-0x10);
        func_0201e3cc(-0x10);
    }
    GX_SetBankForTex(3);
    GX_BeginLoadOBJExtPltt(0x60);
    GX_SetBankForBG(0x10);
    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
    func_02010e80(2, 1);
    func_02011174(0x8000, 1);
    func_020056b4(1, 0, 1);

    {
        vu16 *bg1 = (vu16 *)0x0400000a;
        *bg1 = (*bg1 & 0x43) | 0x84;
        reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | 0x300;
        reg_G2_BG0CNT = reg_G2_BG0CNT & ~3;
        *bg1 = (*bg1 & ~3) | 1;
    }
    GXS_SetGraphicsMode(0);

    {
        vu16 *sub = (vu16 *)0x0400100a;
        vu32 *subd = (vu32 *)0x04001000;
        sub[0] = (sub[0] & 0x43) | 0x4084;
        sub[1] = (sub[1] & 0x43) | 0x4284;
        sub[2] = (sub[2] & 0x43) | 0x404;
        *subd = (*subd & ~0x1f00) | 0x1200;
        *subd = (*subd & 0xffcfffefu) | 0x10;
        sub[0] = (sub[0] & ~3) | 3;
        sub[1] = (sub[1] & ~3) | 2;
        sub[2] = (sub[2] & ~3) | 1;
    }

    func_0202a634((void *)(h + 3), ((h[1] + 0x8000 & 0xfffffc) << 7) | 0x80000000, 1, 0xe);
    func_0202accc((void *)(h + 3), 0, (void *)(h + 0x3b), 0);
    func_0202accc((void *)(h + 3), 2, (void *)(h + 0x3b), 0);
    func_02023c60((void *)(h + 0x45));
    h[0x53] = func_0201ef9c(((h[1] + 0x8000 & 0xfffffc) << 7) | 0x80000001, 0xe);

    {
        int i = 0;
        signed char *tbl = data_ov000_0205a9d4;
        u32 *slot = h + 0x54;
        do {
            func_02024c94(slot, h[0x53], tbl[0], tbl[1], tbl[2]);
            i++;
            tbl += 3;
            slot += 3;
        } while (i < 8);
    }

    func_02024a6c(1, (void *)h[0x62], (void *)h[0x60], 0, *(int *)(h[0x62] + 8));
    func_02024ae0(1, h[0x61], 0, *(u32 *)(h[0x61] + 0x10));
    func_02024a6c(5, (void *)h[0x56], (void *)h[0x54], 0, *(int *)(h[0x56] + 8));
    func_02024ae0(5, h[0x55], 0, *(u32 *)(h[0x55] + 0x10));

    MIi_CpuCopy32(*(void **)(h[0x6b] + 0xc), h + 0x131b, 0x200);

    if (arg != 1) {
        *((u8 *)h + 0x4c2e) = 0;
        *((u8 *)h + 0x4c2f) = 0;
    }
    if (arg == 2) {
        *((u8 *)h + 0x4c2d) = 0;
    }
    h[0x1316] = (arg != 0);

    func_ov000_0204cac0();
    func_02023c30(0);
    func_02024d68();
    h[0x130f] = 0;
    func_02036298(h + 0x12fa, 0);

    if (arg != 0) {
        int n;
        func_ov000_0204e0c8();
        n = func_0202aef8((void *)(h + 3), 0);
        func_01fff774((void *)(h + 3), 0, n - 1);
        n = func_0202aef8((void *)(h + 3), 2);
        func_01fff774((void *)(h + 3), 2, n - 1);
        reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | 0x300;
        if (func_02034014(0) == 0) {
            func_02033fb4(0, 0);
        }
    }

    if (h[0x1311] != 0) {
        h[0] = 0x38;
        return (StateFn)func_ov000_0204df98;
    }
    h[0] = 0;
    return (arg == 0) ? (StateFn)func_ov000_0204dc38 : (StateFn)func_ov000_0204ea68;
}
