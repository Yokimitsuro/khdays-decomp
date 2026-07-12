/* Poll 020d303c: on failure dispatch, otherwise retire the live node via 020d2d90, and while not
 * busy kick anim 0x11 and tick +0x61; once +0x61 reaches 3 advance to 020d4de8. */
extern int func_ov230_020d303c(int);
extern int func_0203c634(int, int, void *);
extern int func_ov230_020d2d90(int);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov230_020d4de8(int);
void func_ov230_020d4d50(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov230_020d303c(param_1) < 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    } else {
        if (*(int *)(owner + 8) != 0) {
            func_ov230_020d2d90(owner);
            *(int *)(owner + 8) = 0;
        }
        if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) == 0) {
            func_ov107_020c9264(*(int *)owner, 0x11, 0);
            *(unsigned char *)(owner + 0x61) += 1;
        }
        if (*(unsigned char *)(owner + 0x61) < 3) return;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov230_020d4de8);
    }
}
