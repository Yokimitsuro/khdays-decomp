/*
 * Ov008_MainMenu_StateTick - per-frame state machine for the main menu scene (scene
 * 0x13), invoked through the scene's state-handler table (no direct caller).
 *
 * State 0 (first-time setup): records whether the menu context object is type 2 at
 * obj[0x538], primes the sub-object (func_ov008_0205a8e0), fills the object-list init
 * params (copied from the data_ov008_0208edd4 template, then slotCount=8 and listSize
 * 7 or 3 depending on func_ov008_0205a84c), builds the object list either directly
 * (ov008_InitObjectWithList) or via func_ov008_0205b19c when Ov008_GetCtxField967c is
 * set, loads the scene 0x13 layout resource, and picks a variant (4, or 0 once the
 * story counter GameState_GetField(0,9) reaches 0x165) stored at obj[0x53b]; then
 * advances the state.
 * State 1: runs the second-phase setup (func_ov008_0205ab5c, Ov008_SetupMenuBgCellsAlt,
 * func_ov008_0205af54), advances the state, stamps the 64-bit entry tick at obj[0x535],
 * and returns 1 to signal the transition happened this frame.
 * Every frame ends by drawing the menu panels (Ov008_DrawMenuPanels).
 *
 * Codegen: the outer state test is a switch (forward-jump dispatch). The a84c and
 * GetCtxField967c tests are written with `!=` and swapped bodies so mwcc lays out the
 * "else" block inline (fall-through) and jumps to the "then" block, matching the ROM;
 * the natural `== 0` spelling emits the opposite layout. Many callee args Ghidra shows
 * are leftover-register phantoms; only the registers set here are real.
 */

typedef unsigned int       u32;
typedef unsigned long long u64;

/* Object-list init parameters: a 3-word template copied from data_ov008_0208edd4, with
 * the last two words overwritten for the main-menu list geometry in state 0. */
typedef struct {
    int f0;
    int slotCount;
    int listSize;
} Ov008ObjListInitParams;

extern int  func_ov008_02050fc8(void);
extern void func_ov008_0205a8e0(void);
extern int  func_ov008_0205a84c(void);
extern int  func_ov008_020511e0(void);
extern void func_ov008_0205652c(u32 *list, Ov008ObjListInitParams *p);
extern void func_ov008_0205b19c(int obj, Ov008ObjListInitParams *p);
extern void func_ov008_0205a8c4(int obj);
extern int  func_ov008_02050c3c(void);
extern int  func_ov008_02050f08(int tag);
extern void func_ov008_02055534(int block, int ref);
extern u32  func_020235d0(int a, int b);
extern void func_ov008_0205c010(u32 *node, int a);
extern void func_ov008_0205c564(int *node, int v);
extern void func_ov008_0205ab5c(int obj);
extern void func_ov008_0205ada4(int *obj);
extern void func_ov008_0205af54(int obj);
extern u64  func_020031d4(void);
extern void func_ov008_0205c4c4(int *node);
extern Ov008ObjListInitParams data_ov008_0208edd4;

int func_ov008_0205b230(int *obj)
{
    Ov008ObjListInitParams p;
    int iVar1;
    int ref;
    u32 counter;
    u64 tick;
    int ret;

    p = data_ov008_0208edd4;
    ret = 0;
    switch (*obj) {
    case 0:
        iVar1 = func_ov008_02050fc8();
        obj[0x538] = (iVar1 == 2);
        func_ov008_0205a8e0();
        if (func_ov008_0205a84c() != 0) {
            p.listSize = 3;
            p.slotCount = 8;
        } else {
            p.listSize = 7;
            p.slotCount = 8;
        }
        if (func_ov008_020511e0() != 0) {
            func_ov008_0205b19c((int)obj, &p);
        } else {
            func_ov008_0205652c((u32 *)(obj + 0x4ff), &p);
        }
        func_ov008_0205a8c4((int)obj);
        iVar1 = func_ov008_02050c3c();
        ref = func_ov008_02050f08(0x13);
        func_ov008_02055534(iVar1, ref);
        iVar1 = 4;
        counter = func_020235d0(0, 9);
        if (0x165 <= counter) iVar1 = 0;
        func_ov008_0205c010((u32 *)(obj + 1), 0);
        func_ov008_0205c564(obj + 1, iVar1);
        obj[0x53b] = iVar1;
        *obj = *obj + 1;
        break;
    case 1:
        func_ov008_0205ab5c((int)obj);
        func_ov008_0205ada4(obj);
        func_ov008_0205af54((int)obj);
        *obj = *obj + 1;
        tick = func_020031d4();
        *(u64 *)(obj + 0x535) = tick;
        ret = 1;
        break;
    }
    func_ov008_0205c4c4(obj + 1);
    return ret;
}
