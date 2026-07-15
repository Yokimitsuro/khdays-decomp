/* func_ov008_0204dc48 -- execute the pending main-menu confirm action, ov008 (one-shot).
 * Guarded by the live menu heap (data_ov008_02090f00 != 0). Reads the confirmed action code
 * (func_ov008_02050e44), tears down the menu UI (e130/da14) and starts the 0x1e-frame fade;
 * if in-game state is active, resets story flags 0xd/0xe. Then:
 *   action 7 -> full soft reset: func_02003948(-2) (OSi reset) + scene 1 (ov000/title).
 *   action 8 -> enter game: copy the selected save slot's 4-word config (overwriting word[1]
 *     with func_ov008_0204ed58), CopyConfig16 it, and switch to scene 2 (ov002/gameplay).
 * Clears the menu-heap guard afterward so it fires only once. */
struct Cfg4 { int w[4]; };
extern char *data_ov008_02090f00;
extern int  func_ov008_02050e44(void);
extern void func_ov008_0204e130(void);
extern void func_ov008_0204da14(void);
extern void func_020336a4(int frames);
extern int  func_02030640(void);
extern void func_020307b8(int a);
extern void func_02030d10(int flag);
extern void func_ov008_0207b8a8(void);
extern int *CARDi_GetRomAccessor_0x020315f4(void);
extern int  func_ov008_0204ed58(void);
extern void func_02031600(struct Cfg4 *cfg);
extern void func_02020a78(int scene, int arg);
extern void func_02030610(void);
extern void func_020352cc(void);
extern void func_02003948(int mode);

void func_ov008_0204dc48(void) {
    int action;
    struct Cfg4 cfg;
    if (data_ov008_02090f00 == 0) {
        return;
    }
    action = func_ov008_02050e44();
    func_ov008_0204e130();
    func_ov008_0204da14();
    func_020336a4(0x1e);
    if (func_02030640() != 0) {
        func_020307b8(1);
        func_02030d10(0xd);
        func_02030d10(0xe);
    }
    func_ov008_0207b8a8();
    if (action != 7) {
        if (action == 8) {
            cfg = *(struct Cfg4 *)CARDi_GetRomAccessor_0x020315f4();
            cfg.w[1] = func_ov008_0204ed58();
            func_02031600(&cfg);
            func_02020a78(2, 0);
        }
    } else {
        if (func_02030640() != 0) {
            func_02030610();
        }
        func_020352cc();
        func_02003948(-2);
        func_02020a78(1, 0);
    }
    data_ov008_02090f00 = 0;
}
