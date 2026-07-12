/* Mark state 2, force +0x54 flags, run 020cfd20 on both sub-refs, then dispatch. */
extern int func_0203c634(int, int, void *);
extern int func_ov258_020cfd20(int);
void func_ov258_020cdbb8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(signed char *)(*(int *)owner + 0x1c7) = 2;
    *(unsigned char *)(owner + 0x54) |= 0xf0;
    func_ov258_020cfd20(*(int *)(*(int *)owner + 0x458));
    func_ov258_020cfd20(*(int *)(*(int *)owner + 0x45c));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
