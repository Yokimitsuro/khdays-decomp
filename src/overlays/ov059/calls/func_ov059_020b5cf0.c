/* Switch the actor's animation set (x4: ov040 + 3 twins). `mode` is absolute and
 * `mode - 0x2e` picks the arm; each arm no-ops if the mode did not actually change
 * (+0x6bc caches it). 0x2e re-inits; 0x2f clears the shared block's flag word and rebinds
 * its sub-slot; 0x32 sets the flag word, retunes channel 0xcb to 2 and rebinds the same
 * sub-slot; 0x33 rebuilds the block and retunes channel 0xce to 4; 0x30/0x31 pick between
 * two teardowns. 0x32 and 0x33 both report 0x2f upward while remembering the REAL mode in
 * +0x6bc.
 *
 * Note the flag-word stores in the 0x2f and 0x32 arms happen BEFORE the mode-changed
 * guard -- they are unconditional. Matched byte-exact on the first compile.
 *
 * Case order from tools/switchorder.py: 0x2e, 0x2f, 0x32, 0x33, {0x30, 0x31}. */
extern int data_ov059_020b7320;

extern void func_ov059_020b619c(int self);
extern void func_ov059_020b623c(void *p, int a);
extern void func_ov022_020a4490(int self, int a, int b);
extern void func_ov059_020b6518(int self, void *p);
extern void func_ov059_020b6578(int self, void *p);
extern void func_ov059_020b63cc(int self, void *p);
extern void func_ov022_020a384c(int self, int mode);

void func_ov059_020b5cf0(int self, int mode) {
    int *p = (int *)(data_ov059_020b7320 + 0x2c50);
    int id = -1;

    switch (mode - 0x2e) {
    case 0:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov059_020b619c(self);
        }
        break;
    case 1:
        *p = 0;
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov059_020b623c((char *)p + 8, 0);
        }
        break;
    case 4:
        *p = 1;
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov022_020a4490(self, 0xcb, 2);
            func_ov059_020b623c((char *)p + 8, 0);
        }
        mode = 0x2f;
        id = 0x32;
        break;
    case 5:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov059_020b6518(self, p);
            func_ov022_020a4490(self, 0xce, 4);
        }
        mode = 0x2f;
        id = 0x33;
        break;
    case 2:
    case 3:
        if (*(int *)(self + 0x6bc) != mode) {
            if (mode == 0x31) {
                func_ov059_020b6578(self, p);
            } else {
                func_ov059_020b63cc(self, p);
            }
        }
        break;
    }
    func_ov022_020a384c(self, mode);
    if (id >= 0) {
        *(int *)(self + 0x6bc) = id;
    }
}
