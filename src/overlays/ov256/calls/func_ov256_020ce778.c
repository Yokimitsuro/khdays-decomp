/* c634 reaction handler: advance the owner via func_ov107_020c9264(owner,
 * obj->f54 + 5, 0), bump the step counter obj->f54 (skipping value 1), then
 * dispatch state with the func_ov256_020ce7cc callback. self->+0x20 = slot index. */
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov256_020ce7cc(void);
void func_ov256_020ce778(int self) {
    int obj = *(int *)(self + 4);
    func_ov107_020c9264(*(int *)obj, *(int *)(obj + 0x54) + 5, 0);
    *(int *)(obj + 0x54) += 1;
    if (*(int *)(obj + 0x54) == 1) {
        *(int *)(obj + 0x54) = *(volatile int *)(obj + 0x54) + 1;
    }
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov256_020ce7cc);
}
