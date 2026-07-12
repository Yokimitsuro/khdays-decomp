/* Allocate the size-0xc render instance for this actor (kind 0x64, handler 020d192c),
 * seed it with the value at (param_1)+0x394 and return it. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, void *out);
extern void func_ov223_020d4f5c(int);
int func_ov223_020d4e24(int param_1) {
    int *out;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0xc, (void *)&func_ov223_020d4f5c, 0, &out);
    *out = *(int *)(param_1 + 0x394);
    return (int)out;
}
