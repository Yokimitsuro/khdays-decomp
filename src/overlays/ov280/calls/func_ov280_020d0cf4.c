/* Pose helper: play anim param_2 on *child and anim param_3 on its owner node
 * *(*child+0x388) (both at speed param_4), then register the given handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
void func_ov280_020d0cf4(int param_1, int param_2, int param_3, int param_4, void *handler) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, param_2, param_4);
    func_ov107_020c9ee8(*(int *)(*(int *)child + 0x388), param_3, param_4);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), handler);
}
