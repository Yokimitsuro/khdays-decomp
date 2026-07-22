/* True when func_02030670 reports ready and the mode func_02001030 returns is one of
 * 0, 1, 9 or 10.  The membership test is a switch -- an if-chain gives a different
 * compare tree. */
extern int func_02030670(void);
extern int func_02001030(void);

int func_020306b4(void) {
    int r = 0;
    if (func_02030670() == 0) {
        return r;
    }
    switch (func_02001030()) {
    case 0:
    case 1:
    case 9:
    case 10:
        r = 1;
        break;
    }
    return r;
}
