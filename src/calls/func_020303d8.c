/* Run one scene to completion: blank both engines, hand control to the ov105
 * per-frame driver until Game_PollSceneAlive says to stop, then restore the
 * displays and report the outcome.
 *
 * Two codegen facts this function pins down, both worth reusing:
 *
 * 1. A switch's dispatch COMPARES are emitted in value order (0, 1, 3) but the
 *    case BODIES are laid out in SOURCE order.  The ROM puts case 1's body
 *    before case 0's, so the source lists case 1 first -- writing them in
 *    numeric order compiles to the same size with the two blocks swapped.
 *
 * 2. `packed = a() << 16; packed |= b();` is not the same as
 *    `packed = (a() << 16) | b();`.  The ROM shifts the first result
 *    immediately (lsls r4,r0,#0x10 right after the bl); the single-expression
 *    form makes mwcc hold the value and shift later, costing two instructions.
 *
 * The `lsls r2, r0, #0x10` at the top is mwcc deriving 0x04000000 from the
 * 0x05000400 it already has in a register -- one pool entry doing double duty,
 * not a second address.
 *
 * The DISPCNT masks clear bits 8-12 (the four BG layers and OBJ) on both
 * engines; the closing GXx_SetMasterBrightness_ pair drives both MASTER_BRIGHT
 * registers to 0x10. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e1d0(void);
extern void func_02032f0c(void);
extern int func_02001030(void);              /* Game_PollSceneAlive */
extern void func_ov105_020bf9c0(void);
extern void func_ov105_020bf928(void);
extern void GXx_SetMasterBrightness_(unsigned int reg, int value);
extern unsigned short func_ov105_020bf25c(void);
extern unsigned short func_ov105_020bf26c(void);
extern void func_0202362c(int a);
extern void func_02003948(unsigned int a);

void func_020303d8(void) {
    int running;
    unsigned int packed;

    NNSi_FndGetCurrentRootHeap();
    *(unsigned short *)0x05000000 = 0;
    *(unsigned short *)0x05000400 = 0;
    *(unsigned int *)0x04000000 = *(unsigned int *)0x04000000 & 0xffffe0ff;
    *(unsigned int *)0x04001000 = *(unsigned int *)0x04001000 & 0xffffe0ff;
    func_0201e1d0();
    func_02032f0c();
    if (func_02001030() != 0) {
        running = 1;
        do {
            switch (func_02001030()) {
            case 1:
                func_ov105_020bf9c0();
                break;
            case 0:
                running = 0;
                break;
            case 3:
                break;
            default:
                func_ov105_020bf928();
                break;
            }
        } while (running != 0);
    }
    GXx_SetMasterBrightness_(0x400006c, 0x10);
    GXx_SetMasterBrightness_(0x400106c, 0x10);
    packed = func_ov105_020bf25c() << 16;
    packed |= func_ov105_020bf26c();
    func_0202362c(0);
    func_02003948(packed | 0x80000000);
}
