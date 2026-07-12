/* Push animation params (4, 0) to the sprite, then dispatch via
 * func_0203c634 with handler func_ov146_020cecd4. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov146_020cecd4(void);
void func_ov146_020ceca0(int param_1) {
    func_ov107_020c9264(*(int *)(*(int *)(param_1 + 4)), 4, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020cecd4);
}
