/* Feed the linked emitter node, then only when the retimed 020d2824 count matches +0x28 clear
 * +0x1c and dispatch 020d0674. */
extern int func_0202b450(int, int);
extern int func_ov253_020d2824(int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020d0674(int);
void func_ov253_020d0610(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int obj = *(int *)owner;
    int a = *(int *)(obj + 0x3bc);
    int b = *(int *)(obj + 0x384);
    int p = *(int *)(a + 0x18c);
    int save = *(int *)(b + 0x460);
    func_0202b450(*(int *)(p + 0x20), *(int *)(b + 0x394) + 0x14);
    if (*(short *)(owner + 0x28) != func_ov253_020d2824(save)) return;
    *(int *)(owner + 0x1c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d0674);
}
