/* func_ov245_020cf7f4 -- release the held sub-object at +0x3f4 (unless the actor's kind byte is
 * 4 or nothing is held), zero the +0x3a4 placement's scale, then run the base teardown. */
extern void func_0203c650(int a, int b);
extern void func_0203ca9c(void *srt, int scale);
extern void func_ov107_020c7ca4(int self);

void func_ov245_020cf7f4(int self) {
    if (*(signed char *)(self + 0x1c6) != 4 && *(int *)(self + 0x3f4) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x3f4));
        *(int *)(self + 0x3f4) = 0;
        func_0203ca9c((void *)(self + 0x3a4), 0);
    }
    func_ov107_020c7ca4(self);
}
