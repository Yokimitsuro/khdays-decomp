/* Store speed*30/15 into +0x18, feed the linked emitter node, then unless busy reset anim 0 and
 * dispatch 020d0500. */
extern int func_0202b450(int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020d0500(int);
void func_ov253_020d0470(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x18) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 15;
    int obj = *(int *)owner;
    func_0202b450(*(int *)(*(int *)(*(int *)(obj + 0x3bc) + 0x18c) + 0x20),
        *(int *)(*(int *)(obj + 0x3b0) + 8) + 0x40);
    if (*(unsigned char *)(*(int *)(owner + 8)) != 0) return;
    func_ov107_020c9264(*(int *)owner, 0, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d0500);
}
