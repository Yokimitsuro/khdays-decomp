/* Release every sub-object of the ov002 panel set held at data_ov002_0207f628 --
 * fourteen of them, at fixed offsets -- then drop the pointer. A null pointer
 * skips straight to the (redundant) clear. */
extern int data_ov002_0207f628;

extern void func_0202a7dc(void *sub);

void func_ov002_020615fc(void) {
    char *self = *(char **)&data_ov002_0207f628;

    if (self != 0) {
        func_0202a7dc(self + 0xe8);
        func_0202a7dc(self + 0x508);
        func_0202a7dc(self + 0x1f0);
        func_0202a7dc(self + 0x2f8);
        func_0202a7dc(self + 0x400);
        func_0202a7dc(self + 0x8cc);
        func_0202a7dc(self + 0x9d4);
        func_0202a7dc(self + 0xdc0);
        func_0202a7dc(self + 0xec8);
        func_0202a7dc(self + 0x1068);
        func_0202a7dc(self + 0x1214);
        func_0202a7dc(self + 0x132c);
        func_0202a7dc(self + 0x610);
    }

    *(int *)&data_ov002_0207f628 = 0;
}
