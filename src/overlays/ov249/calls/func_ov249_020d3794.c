/* Play the hit anim (ov107 mode 0x1a), set the recovery timer (+0x4c=0x13a8, +0x48=0)
 * and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov249_020d37dc(int);
void func_ov249_020d3794(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0x1a, 0);
    *(int *)(child + 0x4c) = 0x13a8;
    *(int *)(child + 0x48) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov249_020d37dc);
}
