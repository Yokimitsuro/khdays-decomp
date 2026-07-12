/* Accumulate the owner rate (+0x2c) into the child timer (+0x5c); once it reaches
 * 0x6ee, clear flag 7 in the high byte at (*child)+0x60, stop the anim, and dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov227_020d1fc4(void);
struct hi_020d1d28 { unsigned short pad : 8; unsigned short flags : 8; };
void func_ov227_020d1f44(int param_1) {
    int child = *(int *)(param_1 + 4);
    int c = *(int *)(child + 0x5c) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x5c) = c;
    if (c < 0x6ee) return;
    ((struct hi_020d1d28 *)(*(int *)child + 0x60))->flags &= ~0x80;
    func_ov107_020c9264(*(int *)child, 0, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov227_020d1fc4);
}
