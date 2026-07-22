/* func_ov245_020d0abc -- release the held sub-object at +0x3a0, unless the actor's kind byte
 * (+0x1c6) is 1 or there is nothing held. */
extern void func_0203c650(int a, int b);

void func_ov245_020d0abc(int self) {
    if (*(signed char *)(self + 0x1c6) != 1 && *(int *)(self + 0x3a0) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x3a0));
        *(int *)(self + 0x3a0) = 0;
    }
}
