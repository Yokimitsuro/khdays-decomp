/* Allocate the size-0x3c render instance for this actor (kind 0x64, handler 020d2474),
 * back-link it to the actor and store it at (param_1)+0x214. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, void *out);
extern void func_ov253_020cd1bc(void);
void func_ov253_020ccef4(int param_1) {
    int *out;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x3c, (void *)&func_ov253_020cd1bc, 0, &out);
    *out = param_1;
    *(int *)(param_1 + 0x214) = (int)out;
}
