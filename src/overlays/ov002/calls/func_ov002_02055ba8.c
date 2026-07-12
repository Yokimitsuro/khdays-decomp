/* If status bit 2 of (*global)+0x12c is set, run func_ov002_020554f0. */
extern void func_ov002_020554f0(void);
extern int data_ov002_0207f614;

void func_ov002_02055ba8(void) {
    int base = *(int *)&data_ov002_0207f614;
    if ((*(unsigned int *)(base + 0x12c) << 0x1d) >> 0x1f) {
        func_ov002_020554f0();
    }
}
