/* Unless busy, poll 020cd080: on success just dispatch, otherwise latch sub-state 4 first. */
extern int func_ov254_020cd080(int);
extern int func_0203c634(int, int, void *);
void func_ov254_020ce610(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    if (func_ov254_020cd080(param_1) != 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    } else {
        *(unsigned char *)(*(int *)owner + 0x1c7) = 4;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    }
}
