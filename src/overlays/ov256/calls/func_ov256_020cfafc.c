/* Unless busy, tick +0x54: on 8 kick anim 0x11, clear +0x4c/+0x6a and dispatch, otherwise just
 * clear +0x6a and kick anim 0x10. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020cfb74(int);
void func_ov256_020cfafc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(int *)(owner + 0x54) += 1;
    if (*(int *)(owner + 0x54) == 8) {
        func_ov107_020c9264(*(int *)owner, 0x11, 0);
        *(int *)(owner + 0x4c) = 0;
        *(unsigned char *)(owner + 0x6a) = 0;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020cfb74);
    } else {
        *(unsigned char *)(owner + 0x6a) = 0;
        func_ov107_020c9264(*(int *)owner, 0x10, 0);
    }
}
