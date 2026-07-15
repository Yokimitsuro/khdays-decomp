/* func_ov000_0204ea68 -- Scene 1 (boot/logo) re-entry scene state, ov000.
 * The initial state fn the ctor returns on a non-fresh entry (arg != 0). Does the
 * one-time sub-screen bring-up: clears BG1/BG2 char, sets the sub graphics mode and
 * BG control regs, re-arms animation player 5, programs the sub blend-alpha, sets BG
 * priorities, runs the object/text init (func_ov000_0204cc90 / func_ov000_0204d208)
 * and the scroll-bounds setup (func_02023d70), then hands off to func_ov000_0204f250. */

typedef unsigned short u16;
typedef unsigned int   u32;
typedef volatile u16   vu16;
typedef volatile u32   vu32;
typedef void          *StateFn;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void *G2S_GetBG1CharPtr(void);
extern void *G2S_GetBG2CharPtr(void);
extern void  MIi_CpuClearFast(int val, void *dst, int size);
extern void  GXS_SetGraphicsMode(int);
extern void  func_02024a6c(int, void *, void *, int, int);
extern void  func_02024ae0(int, void *, int, int);
extern void  func_02024b04(int, void *, int, int);
extern void  G2x_SetBlendAlpha_(int reg, int a, int b, int c, int d);
extern void  func_ov000_0204cc90(void);
extern void  func_ov000_0204d208(void);
extern void  func_02023d70(void *, int, int, int, int);
extern void  func_0202aa9c(void *);
extern void  func_ov000_0204f250(void);

StateFn func_ov000_0204ea68(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    MIi_CpuClearFast(0, G2S_GetBG1CharPtr(), 0x20);
    MIi_CpuClearFast(0, G2S_GetBG2CharPtr(), 0x20);
    GXS_SetGraphicsMode(0);

    {
        vu16 *sub = (vu16 *)0x0400100a;
        vu32 *subd = (vu32 *)0x04001000;
        sub[0] = (sub[0] & 0x43) | 0x4084;
        sub[1] = (sub[1] & 0x43) | 0x4284;
        sub[2] = (sub[2] & 0x43) | 0x404;
        *subd = (*subd & ~0x1f00) | 0x1200;
    }

    func_02024a6c(5, (void *)h[0x5f], (void *)h[0x5d], 0, *(int *)(h[0x5f] + 8));
    func_02024ae0(5, (void *)h[0x5e], 0, *(int *)(h[0x5e] + 0x10));
    func_02024b04(5, (void *)h[0x5d], 0, *(int *)(h[0x5d] + 8));

    G2x_SetBlendAlpha_(0x04001050, 0x10, 0x22, 0x10, 0);

    {
        vu16 *sub = (vu16 *)0x0400100a;
        sub[0] = (sub[0] & ~3) | 3;
        sub[1] = (sub[1] & ~3) | 2;
        sub[2] = (sub[2] & ~3) | 1;
    }

    func_ov000_0204cc90();
    func_ov000_0204d208();
    func_02023d70((void *)(h + 0x45), 0x3b33, -0x3b33, -0x4d9a, 0x4d9a);
    func_0202aa9c((void *)(h + 3));
    return (StateFn)func_ov000_0204f250;
}
