/* Store the scaled approach delta into +0x10, advance the +0x44 timer, and dispatch once it expires. */
extern int func_ov254_020cd840(int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov254_020d140c(int);
void func_ov254_020d1384(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int base = func_ov254_020cd840(owner, -1);
    int v = *(int *)(*(int *)(owner + 8) + 4);
    *(int *)(owner + 0x10) = (int)((((long long)(base - v) << 7) + 0x800) >> 12);
    *(int *)(owner + 0x44) += *(int *)(*(int *)param_1 + 0x2c);
    if (*(int *)(owner + 0x44) < 0xa000) return;
    *(signed char *)(*(int *)(owner + 4) + 0xa8) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov254_020d140c);
}
