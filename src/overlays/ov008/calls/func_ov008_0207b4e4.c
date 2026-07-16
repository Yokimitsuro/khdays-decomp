/* func_ov008_0207b4e4 -- menu-open tick, returns the next scene state (0 = stay).
 * While the scene is locked out (obj+0x4e8) it drives the sound and waits for the intro
 * jingle latch at obj+0x49c to clear, then clears the pending transition at obj+0x2c.
 * Otherwise an unselectable entry sends it straight to func_ov008_0207aad0. Once no
 * transition is pending it commits the entry and advances to func_ov008_0207b56c.
 *
 * PROVENANCE: byte-identical twin of func_ov006_0204f788 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern void func_ov008_02079a20(void);
extern int  func_ov008_02079274(void);
extern void func_ov008_02079f80(void);
extern void func_020307b8(int a);
extern void func_ov008_0207aad0(void);
extern void func_ov008_0207b56c(void);
extern int  data_ov008_02090f24;

#define OBJ (*(int **)&data_ov008_02090f24)

void *func_ov008_0207b4e4(void) {
    void *next = 0;
    if (OBJ[0x13a] != 0) {
        int *obj;
        func_ov008_02079a20();
        obj = OBJ;
        if (obj[0x127] != 0) {
            return next;
        }
        obj[0xb] = (int)next;
    } else if (func_ov008_02079274() == 0) {
        return (void *)func_ov008_0207aad0;
    }
    if (OBJ[0xb] == 0) {
        func_ov008_02079f80();
        func_020307b8(0);
        next = (void *)func_ov008_0207b56c;
    }
    return next;
}
