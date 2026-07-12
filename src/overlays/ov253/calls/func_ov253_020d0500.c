/* Store speed*30/15 into +0x18, feed the linked emitter node, then unless the node's +0xc is busy
 * feed a second socket and dispatch 020d05a0. */
extern int func_0202b450(int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020d05a0(int);
void func_ov253_020d0500(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x18) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 15;
    int obj = *(int *)owner;
    int a = *(int *)(obj + 0x3bc);
    int c = *(int *)(obj + 0x3b0);
    func_0202b450(*(int *)(*(int *)(a + 0x18c) + 0x20), *(int *)(c + 8) + 0x40);
    int obj2 = *(int *)owner;
    if (*(int *)(*(int *)(obj2 + 0x3b0) + 0xc) != 0) return;
    func_0202b450(*(int *)(*(int *)(*(int *)(obj2 + 0x3bc) + 0x18c) + 0x20),
        *(int *)(*(int *)(obj2 + 0x384) + 0x394) + 0x14);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d05a0);
}
