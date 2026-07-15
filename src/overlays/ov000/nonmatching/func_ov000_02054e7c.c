#pragma thumb on
/* func_ov000_02054e7c -- Scene 1 (boot/logo) save-slot poll, ov000. THUMB.
 * NONMATCHING: our mwcc tail-merges the two `return 1` exits (r<0 path and the
 * reload path) into one shared block; the retail build keeps them separate (same
 * tail-merge / pool-dedup class of version difference). Logic is byte-exact
 * otherwise. Kept readable for the PC port.
 *
 * Classifies the save state into the code consumed by func_ov000_0204df98's switch:
 *   func_ov000_02054a50 < 0            -> 1 (busy; no tick)
 *   func_ov000_02054a50 > 0            -> 3 (ready)
 *   == 0, all 8 slot words empty       -> 2 (blank card)
 *   == 0, slot used, 02054a84 != 0     -> 0 (in place; publish record ptr @data_0204be18)
 *   == 0, slot used, retry count >= 2  -> 4 (give up)
 *   == 0, slot used, retry count < 2   -> kick a reload (func_ov000_020549fc) and return 1
 * The 0/2/3/4 paths first bump the shared frame counter (func_020208f0). */

extern void         *data_0204be14;
extern void         *data_0204be18;
extern unsigned char data_ov000_0205ac2c[];
extern int   func_ov000_02054a50(void);
extern int   func_ov000_02054a84(void);
extern void  func_ov000_020549fc(int arg, void *buf);
extern int   func_020208f0(void);

int func_ov000_02054e7c(void) {
    int mode;
    int r = func_ov000_02054a50();
    if (r < 0) {
        return 1;
    }
    if (r != 0) {
        mode = 3;
    } else {
        int i = 0;
        int *p = (int *)data_0204be14;
        do {
            if (*p++ != 0) {
                break;
            }
            i++;
        } while (i < 8);
        if (i == 8) {
            mode = 2;
        } else if (func_ov000_02054a84() != 0) {
            data_0204be18 = (char *)data_0204be14 + 0x18;
            mode = 0;
        } else {
            unsigned char *c = data_ov000_0205ac2c;
            c[0]++;
            if (c[0] < 2) {
                func_ov000_020549fc(0x2018 * (c[0] + (c[1] << 1)) + 0x20, data_0204be14);
                return 1;
            }
            mode = 4;
        }
    }
    func_020208f0();
    return mode;
}
