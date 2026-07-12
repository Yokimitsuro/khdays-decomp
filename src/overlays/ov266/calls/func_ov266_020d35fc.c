/* Allocate the size-0xc render instance for this actor (kind 0x64, handler 020d192c),
 * seed it with the value at (param_1)+0x394 and return it. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, void *out);
extern void func_ov266_020d3724(int);
int func_ov266_020d35fc(int param_1) {
    int *out;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0xc, (void *)&func_ov266_020d3724, 0, &out);
    *out = *(int *)(param_1 + 0x394);
    return (int)out;
}
