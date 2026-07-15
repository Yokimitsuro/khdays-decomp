/* c634 reaction handler: proceed only if owner->+0x4ac is set AND
 * owner->+0x4a4->+0x4b0 is zero. Then advance via func_ov107_020c9264(owner, 6, 0)
 * and dispatch state with the func_ov237_020d043c callback. self->+0x20 = slot. */
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov237_020d043c(void);
void func_ov237_020d03e0(int self) {
    int ok = 0;
    int owner = *(int *)*(int *)(self + 4);
    if (*(int *)(owner + 0x4ac) != 0 && *(int *)(*(int *)(owner + 0x4a4) + 0x4b0) == 0) {
        ok = 1;
    }
    if (ok == 0) {
        return;
    }
    func_ov107_020c9264(owner, 6, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov237_020d043c);
}
