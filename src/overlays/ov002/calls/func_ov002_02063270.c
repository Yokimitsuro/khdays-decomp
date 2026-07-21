extern void func_020300f8(int list);
extern void func_ov002_02053cd4(int id);
extern char data_ov002_0207f62c[];
/* If the scene has a pending queue (+0x8c), drain it (+0xc0) and raise event 0x1a. */
void func_ov002_02063270(void) {
    int ctx = *(int *)(data_ov002_0207f62c + 4);
    if (*(int *)(ctx + 0x8c) != 0) {
        func_020300f8(ctx + 0xc0);
        func_ov002_02053cd4(0x1a);
    }
}
