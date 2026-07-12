/* Kick anim (0, phase 1), snapshot the target, compute the travel delta, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov254_020cd840(int, int, int);
extern int func_ov254_020d0c94(int);
void func_ov254_020d0c28(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0, 1);
    *(int *)(owner + 0x10) = 0;
    *(int *)(owner + 0x44) = 0;
    int v = *(int *)(*(int *)(owner + 8) + 4);
    *(int *)(owner + 0x50) = v;
    int r = func_ov254_020cd840(owner, 0xb, v);
    *(int *)(owner + 0x54) = r - *(int *)(owner + 0x50);
    *(signed char *)(owner + 0x70) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov254_020d0c94);
}
