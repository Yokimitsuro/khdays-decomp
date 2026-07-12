/* Allocate the size-0x78 render instance for this actor (kind 0x64, handler 020cd2ac),
 * back-link it to the actor and store it at (param_1)+0x214. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, void *out);
extern void func_ov278_020d1c50(void);
void func_ov278_020d17fc(int param_1) {
    int *out;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x78, (void *)&func_ov278_020d1c50, 0, &out);
    *out = param_1;
    *(int *)(param_1 + 0x214) = (int)out;
}
