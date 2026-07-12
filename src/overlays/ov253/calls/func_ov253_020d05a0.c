/* Feed the linked emitter node; if 020d26c8 rejects, bail, otherwise store the 020d26e0 result
 * into +0x28 and dispatch 020d0610. */
extern int func_0202b450(int, int);
extern int func_ov253_020d26c8(int);
extern int func_ov253_020d26e0(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020d0610(int);
void func_ov253_020d05a0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int obj = *(int *)owner;
    int a = *(int *)(obj + 0x3bc);
    int b = *(int *)(obj + 0x384);
    int p = *(int *)(a + 0x18c);
    int save = *(int *)(b + 0x460);
    func_0202b450(*(int *)(p + 0x20), *(int *)(b + 0x394) + 0x14);
    if (func_ov253_020d26c8(save) != 0) return;
    *(unsigned short *)(owner + 0x28) = func_ov253_020d26e0(save, 0, *(int *)(*(int *)owner + 0x3bc));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d0610);
}
