/* Unless busy, advance the +0x54 counter; on 2 kick anim 0xe and dispatch, else kick anim 0xd. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov256_020cf9e0(int);
void func_ov256_020cf974(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(int *)(owner + 0x54) += 1;
    if (*(int *)(owner + 0x54) == 2) {
        *(int *)(owner + 0x4c) = 0;
        func_ov107_020c9264(*(int *)owner, 0xe, 0);
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov256_020cf9e0);
    } else {
        func_ov107_020c9264(*(int *)owner, 0xd, 0);
    }
}
