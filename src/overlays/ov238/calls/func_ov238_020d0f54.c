/* c634 reaction handler: forward two sub-updates —
 * func_ov107_020c9264(owner, param_2, param_4) and
 * func_ov107_020c9ee8(owner->+0x3e0, param_3, param_4) — then dispatch state with
 * the caller-supplied callback (5th arg). self->+0x20 = slot index. */
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_0203c634(int self, int index, void *cb);
void func_ov238_020d0f54(int self, int param_2, int param_3, int param_4, void *cb) {
    int obj = *(int *)(self + 4);
    func_ov107_020c9264(*(int *)obj, param_2, param_4);
    func_ov107_020c9ee8(*(int *)(*(int *)obj + 0x3e0), param_3, param_4);
    func_0203c634(self, *(signed char *)(self + 0x20), cb);
}
