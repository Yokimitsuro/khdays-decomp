/* Advance the packed nibble state at +0x38: if flagged, clear the pending high nibble; unless the
 * high nibble is empty, copy it down and dispatch the matching handler; finally re-arm it to -1. */
extern int func_0203c634(int, int, void *);
extern int func_ov200_020d0764(int);
extern int func_ov200_020d07bc(int);
extern int func_ov200_020d0bf0(int);
struct nibs { int lo : 4, hi : 4; };
void func_ov200_020d06a4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)owner + 0x1c4) & 0xa) {
        if (((struct nibs *)(owner + 0x38))->lo != 0) {
            ((struct nibs *)(owner + 0x38))->hi = 0;
        }
    }
    if (((struct nibs *)(owner + 0x38))->hi != -1) {
        ((struct nibs *)(owner + 0x38))->lo = ((struct nibs *)(owner + 0x38))->hi;
        switch (((struct nibs *)(owner + 0x38))->lo) {
        case 0: func_0203c634(param_1, 1, (void *)&func_ov200_020d0764); break;
        case 1: func_0203c634(param_1, 1, (void *)&func_ov200_020d07bc); break;
        case 2: func_0203c634(param_1, 1, (void *)&func_ov200_020d0bf0); break;
        }
    }
    ((struct nibs *)(owner + 0x38))->hi = -1;
}
