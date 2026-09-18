/* func_ov245_020d5a74 -- release the sub-object held by the +0x3a4 child's +0x1c slot (unless
 * the actor's kind byte is 6 or nothing is held) and then run the base teardown. Sibling of
 * func_ov245_020d0abc / func_ov245_020d2b88, which do the same for the actor's own slots. */
extern void func_0203c650(int a, int b);
extern void func_ov107_020c7ca4(int self);

void func_ov245_020d5a74(int self) {
    if (*(signed char *)(self + 0x1c6) != 6 && *(int *)(*(int *)(self + 0x3a4) + 0x1c) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3a4) + 0x1c));
        *(int *)(*(int *)(self + 0x3a4) + 0x1c) = 0;
    }
    func_ov107_020c7ca4(self);
}
