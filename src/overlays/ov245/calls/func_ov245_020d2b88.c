/* func_ov245_020d2b88 -- release the held sub-object at +0x3a8 (unless the actor's kind byte is 1
 * or nothing is held) and then run the base teardown. Sibling of func_ov245_020d0abc, which does
 * the same for +0x3a0 and has no base call. */
extern void func_0203c650(int a, int b);
extern void func_ov107_020c7ca4(int self);

void func_ov245_020d2b88(int self) {
    if (*(signed char *)(self + 0x1c6) != 1 && *(int *)(self + 0x3a8) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x3a8));
        *(int *)(self + 0x3a8) = 0;
    }
    func_ov107_020c7ca4(self);
}
