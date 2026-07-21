extern void func_ov002_0206e99c(int slot);
extern char *data_ov002_0207fa04;
/* Reset all 0x20 entries: run the per-slot teardown and clear its flag byte (+0x10c). */
void func_ov002_0206ed7c(void) {
    int base = (int)data_ov002_0207fa04;
    int i = 0;
    do {
        func_ov002_0206e99c(i);
        *(unsigned char *)(base + i + 0x10c) = 0;
        i++;
    } while (i < 0x20);
}
