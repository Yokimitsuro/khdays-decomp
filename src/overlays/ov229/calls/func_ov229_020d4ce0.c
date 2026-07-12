/* Poll func_ov229_020d2f84: on failure dispatch immediately, otherwise clear +8, and while not busy kick anim
 * 0x11 and tick +0x61; once +0x61 reaches 3 advance to func_ov229_020d4d6c. */
extern int func_ov229_020d2f84(int);
extern int func_0203c634(int, int, void *);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov229_020d4d6c(int);
void func_ov229_020d4ce0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov229_020d2f84(param_1) < 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    } else {
        if (*(int *)(owner + 8) != 0) *(int *)(owner + 8) = 0;
        if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) == 0) {
            func_ov107_020c9264(*(int *)owner, 0x11, 0);
            *(unsigned char *)(owner + 0x61) += 1;
        }
        if (*(unsigned char *)(owner + 0x61) < 3) return;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov229_020d4d6c);
    }
}
