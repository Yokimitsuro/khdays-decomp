/* Switch the actor's animation set (x4: ov038 + 3 twins). `mode` is an absolute id and
 * `mode - 0x2e` selects the handler; every arm is a no-op if the mode did not actually
 * change (+0x6bc caches the last one). 0x2e re-inits; 0x31 rebinds the shared slot at
 * +0x2e54; 0x2f/0x32 clear the block's flag word, retune channel 200 to 4, rebuild the
 * marker at +0x3070 and release +0x2e54 -- and 0x32 additionally reports 0x2f upward while
 * remembering the REAL mode in +0x6bc; 0x30 sets the flag word, places the trail marker at
 * +0x2f64 (PlaceTrailMarker), releases +0x2e54 and retunes channel 200 to 0.
 *
 * ★ `flag` is ONE variable, not two constants, and that is the whole difference. It is 0
 * for the `*p = flag` store and then BECOMES the (mode == 0x32) result for the 020b3fe8
 * argument. Spelling the store as `*p = 0` and the argument as `mode == 0x32` is the same
 * size but leaves both as scratch temps -- the ROM keeps the single value live across the
 * 020a4490 call, which is what puts it in a callee-saved register (r8) and is visible in
 * the push list. Note it is initialised OUTSIDE the mode-changed guard.
 *
 * Case order from tools/switchorder.py: 0x2e, 0x31, {0x2f, 0x32}, 0x30. */
extern int data_ov094_020bc240;

extern void func_ov094_020baf18(int self);
extern void func_ov094_020bb068(int self, void *p);
extern void func_ov022_020a4490(int self, int a, int b);
extern void func_ov094_020bb588(int self, void *p, int flag);
extern void func_ov094_020bb0a4(int self, void *p);
extern void func_ov094_020bb3a0(int self, void *p);
extern void func_ov022_020a384c(int self, int mode);

void func_ov094_020baa90(int self, int mode) {
    char *p = (char *)(data_ov094_020bc240 + 0x2c2c);
    int id = -1;

    switch (mode - 0x2e) {
    case 0:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov094_020baf18(self);
        }
        break;
    case 3:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov094_020bb068(self, p + 0x228);
        }
        break;
    case 1:
    case 4:
        { int flag = 0;
        if (*(int *)(self + 0x6bc) != mode) {
            *(int *)p = flag;
            func_ov022_020a4490(self, 0xc8, 4);
            if (mode == 0x32) {
                flag = 1;
            }
            func_ov094_020bb588(self, p + 0x444, flag);
            func_ov094_020bb0a4(self, p + 0x228);
        } }
        if (mode == 0x32) {
            id = 0x32;
            mode = 0x2f;
        }
        break;
    case 2:
        if (*(int *)(self + 0x6bc) != mode) {
            *(int *)p = 1;
            func_ov094_020bb3a0(self, p + 0x338);
            func_ov094_020bb0a4(self, p + 0x228);
            func_ov022_020a4490(self, 0xc8, 0);
        }
        break;
    }
    func_ov022_020a384c(self, mode);
    if (id >= 0) {
        *(int *)(self + 0x6bc) = id;
    }
}
