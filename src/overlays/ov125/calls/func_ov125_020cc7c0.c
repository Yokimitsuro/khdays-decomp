/* Allocate the size-0x80 render instance for this actor (kind 0x64, handler 020cca50),
 * back-link it to the actor and store it at (param_1)+0x214. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, void *out);
extern void func_ov125_020cca50(void);
void func_ov125_020cc7c0(int param_1) {
    int *out;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x80, (void *)&func_ov125_020cca50, 0, &out);
    *out = param_1;
    *(int *)(param_1 + 0x214) = (int)out;
}
