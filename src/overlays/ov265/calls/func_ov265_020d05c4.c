/* Allocate the size-0x5c render instance for this actor (kind 0x64, handler 020d0d78),
 * back-link it, store it at (param_1)+0x214, and seed its fields (+0x58=1, +0x50=0x168). */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, void *out);
extern void func_ov265_020d0d6c(void);
void func_ov265_020d05c4(int param_1) {
    int *out;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x5c, (void *)&func_ov265_020d0d6c, 0, &out);
    *out = param_1;
    *(int *)(param_1 + 0x214) = (int)out;
    *(int *)((int)out + 0x58) = 1;
    *(short *)((int)out + 0x50) = 0x168;
}
