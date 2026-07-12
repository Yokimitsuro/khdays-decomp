/* If func_ov223_020d1240 fails (<0), dispatch with a null handler and return.
 * Otherwise, unless the grandchild is busy (+0xad), set anim 0x14 and dispatch. */
extern int func_ov223_020d1240(int a, int b);
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov223_020d34bc(void);
void func_ov223_020d3454(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (func_ov223_020d1240(param_1, 0) < 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
        return;
    }
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)child, 0x14, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov223_020d34bc);
}
