/* Allocate the size-0x28 render instance for this actor (kind 0x64, handler 020d2f9c),
 * back-link it, seed its timer field (+0x24=0x168) and store it at (param_1)+0x214. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, void *out);
extern void func_ov263_020d2f9c(void);
void func_ov263_020d2f44(int param_1) {
    int *out;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x28, (void *)&func_ov263_020d2f9c, 0, &out);
    *out = param_1;
    *(short *)((int)out + 0x24) = 0x168;
    *(int *)(param_1 + 0x214) = (int)out;
}
