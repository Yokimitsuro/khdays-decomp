/* func_ov253_020cea60 -- teardown: releases the +0x3b0 sub-state's +0x24 object unless the
 * actor's kind byte is 5, and its +0x14 object unless the kind is 6 (0203c650), then the base
 * teardown (020c7ca4). */
extern void func_0203c650(int scene, int object);
extern void func_ov107_020c7ca4(int self);

void func_ov253_020cea60(int self) {
    if (*(signed char *)(self + 0x100 + 0xc6) != 5 && *(int *)(*(int *)(self + 0x3b0) + 0x24) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3b0) + 0x24));
        *(int *)(*(int *)(self + 0x3b0) + 0x24) = 0;
    }
    if (*(signed char *)(self + 0x100 + 0xc6) != 6 && *(int *)(*(int *)(self + 0x3b0) + 0x14) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3b0) + 0x14));
        *(int *)(*(int *)(self + 0x3b0) + 0x14) = 0;
    }
    func_ov107_020c7ca4(self);
}
