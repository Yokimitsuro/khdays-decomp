/* Teardown of the ov260 actor: outside move 6 the +0x49c and +0x4a4 effects are released from the
 * +0x3c task list, outside move 0xb the +0x4bc one too; then the base teardown runs (020c7ca4). */
extern void func_0203c650(void *taskList, void *handle);
extern void func_ov107_020c7ca4(char *self);

void func_ov260_020cc808(char *self)
{
    if (*(signed char *)(self + 0x1c6) != 6) {
        if (*(void **)(self + 0x49c) != 0) {
            func_0203c650(*(void **)(self + 0x3c), *(void **)(self + 0x49c));
            *(void **)(self + 0x49c) = 0;
        }
        if (*(void **)(self + 0x4a4) != 0) {
            func_0203c650(*(void **)(self + 0x3c), *(void **)(self + 0x4a4));
            *(void **)(self + 0x4a4) = 0;
        }
    }
    if (*(signed char *)(self + 0x1c6) != 0xb && *(void **)(self + 0x4bc) != 0) {
        func_0203c650(*(void **)(self + 0x3c), *(void **)(self + 0x4bc));
        *(void **)(self + 0x4bc) = 0;
    }
    func_ov107_020c7ca4(self);
}
