/* Unless busy, tick +0x30; dispatch 020d0540 when either the active node's sub-state hit 0xc or,
 * when idle, the counter reached 3; otherwise reset anim 0. */
extern int func_0203c634(int, int, void *);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov237_020d0540(int);
void func_ov237_020d04b0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(int *)(owner + 0x30) += 1;
    int flag = 0;
    int obj = *(int *)owner;
    int t = *(int *)(obj + 0x4ac);
    if (t != 0) {
        if (*(signed char *)(*(int *)(obj + 0x4a4) + 0x1c6) == 0xc) flag = 1;
    }
    if (t == 0) {
        if (*(int *)(owner + 0x30) >= 3) flag = 1;
    }
    if (flag != 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov237_020d0540);
    } else {
        func_ov107_020c9264(obj, 0, 0);
    }
}
